#include "server.h"

Server::Server(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	filterWin = new FilterDialog(this);

	tcpServer = new QTcpServer(this);
	if (!tcpServer->listen(QHostAddress::Any, 12234))
	{
		QMessageBox::critical(this, tr("Chat Server"),
			tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
		close();
		return;
	}

	int port = tcpServer->serverPort();
	ui.statusText->setText(tr("Listening on port: %1").arg(port));

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SIGNAL(SEND_UserList()));
	timer->start(6000);

	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
	connect(this, SIGNAL(newConnection()), this, SLOT(getMessage()));
	connect(this, SIGNAL(SEND_UserList()), this, SLOT(sendUserList()));
	connect(ui.filterButton, SIGNAL(clicked()), this, SLOT(showFilteredResults()));
	connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(serverSendAll()));
}

Server::~Server()
{

}

void Server::newConnection()
{
	QTcpSocket *newSocket = tcpServer->nextPendingConnection();
	connect(newSocket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
	connect(newSocket, SIGNAL(disconnected()), this, SLOT(sendUserList()));
	connect(newSocket, SIGNAL(readyRead()), this, SLOT(getMessage()));
	clientConnections.append(newSocket);

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	QString message = "Server: Connected!";
	out << message;
	newSocket->write(block);
}

void Server::onDisconnect()
{
	QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

	if (socket != 0)
	{
		std::vector<int> currentSockets;

		// Look for sockets that aren't connected
		int socketID = 0;
		for (auto i : clientConnections)
		{
			currentSockets.push_back(i->socketDescriptor());
		}
		for (auto i : userList)
		{
			bool found = true;
			for (auto ii : currentSockets)
			{
				if (i.first == ii)
					found = false;
			}
			if (found == true)
			{
				socketID = i.first;
			}
		}

		QString username = getUsername(socketID);

		auto iter = userList.find(socketID);
		if (iter != userList.end())
			userList.erase(iter);

		ui.userList->clear();
		for (auto i : userList)
		{
			new QListWidgetItem(i.second, ui.userList);
		}

		clientConnections.removeAll(socket);
		socket->deleteLater();
		updateStatus("Connection terminated. (" + username + ":" + QString::number(socketID) + ")");
	}
}

void Server::sendMessage(QString message, QTcpSocket& socket)
{
	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << message;

	socket.write(msg);
}

void Server::sendToAll(QString message)
{
	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << message;

	for (auto i : clientConnections)
	{
		i->write(msg);
	}
}

void Server::sendToID(QString message, int ID)
{
	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << message;

	for (auto i : clientConnections)
	{
		if (i->socketDescriptor() == ID)
			i->write(msg);
	}
}

void Server::getMessage()
{
	QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
	QDataStream in(client);
	in.setVersion(QDataStream::Qt_4_0);

	QString message;
	in >> message;

	QStringList messageTokens;
	messageTokens = message.split(" ", QString::SkipEmptyParts);

	enum class COMMAND { NONE, USERNAME, USERCMD};
	COMMAND cmd = COMMAND::NONE;

	if (message == "_USR_")
		cmd = COMMAND::USERNAME;

	if (messageTokens.at(0) == "_UCD_")
	{
		cmd = COMMAND::USERCMD;
	}


	switch (cmd)
	{
	case COMMAND::USERNAME:
	{

		in >> message;

		QString username = message;
		QString tempname = username;
		int ID = client->socketDescriptor();

		//Check if username is taken
		int numInc = 0;
		bool isTaken = true;

		while (isTaken)
		{
			isTaken = false;
			for (auto i : userList)
			{
				if (i.second == tempname)
				{
					isTaken = true;
					++numInc;
				}
			}

			if (isTaken)
			{
				tempname = username + "(" + QString::number(numInc) + ")";
			}
		}

		username = tempname;

		userList.insert(std::make_pair(ID, username));
		new QListWidgetItem(username, ui.userList);
		ui.userList->scrollToBottom();

		QString address = getSocket(ID)->peerAddress().toString();
		QStringList addr = address.split(":", QString::SkipEmptyParts);
		address = addr.takeLast();

		QString newConnectionMsg = "New connection established. (" + username + ":" + QString::number(ID) + "->" + address + ")";
		updateStatus(newConnectionMsg);
		break;
	}
	case COMMAND::USERCMD:
	{
		messageTokens.removeFirst();
		message.clear();
		for (auto i : messageTokens)
		{
			message += i;
			message += " ";
		}
		doCommand(message, client->socketDescriptor());
		break;
	}
	default:
		std::map<int, QString>::iterator it;
		it = userList.find(client->socketDescriptor());
		updateStatus("MSG: (" + it->second + ") " + message);

		it = userList.find(client->socketDescriptor());
		QString usr = it->second;
		message = usr + ": " + message;
		sendToAll(message);
	}
}

void Server::updateStatus(QString message)
{
	message = timestamp() + " " + message;
	new QListWidgetItem(message, ui.statusList);
	ui.statusList->scrollToBottom();
}

void Server::sendUserList()
{
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);
	QString userlist;

	userlist = "_LST_";
	for (auto i : userList)
	{
		userlist += " ";
		userlist += i.second;
	}

	out << userlist;

	for (auto i : clientConnections)
	{
		i->write(block);
	}
}

void Server::doCommand(QString command, int ID)
{
	QString message = "Server: ";
	QStringList commandTokens = command.split(" ", QString::SkipEmptyParts);
	command = commandTokens.takeFirst();

	if (command == "/hello")
	{
		message += "Hi.";
	}
	else if (command == "/msg" || command == "/whisper" || command == "/pm")
	{
		if (!commandTokens.isEmpty())
		{
			QString recipient = commandTokens.takeFirst();
			int rID = 0;
			for (auto i : userList)
			{
				if (i.second == recipient)
					rID = i.first;
			}

			if (rID == 0)
				message += tr("User \"%1\" not found").arg(recipient);
			else if (rID == ID)
				message += "You cannot message yourself.";
			else
			{
				QString text;
				text.clear();
				for (auto i : commandTokens)
				{
					text += i;
					text += " ";
				}

				auto user = userList.find(ID);

				message = "* To: " + recipient + ": " + text;
				QString rMessage = "* From: " + user->second + ": " + text;
				sendToID(rMessage, rID);

				QString status = "PM: (" + user->second + " -> " + recipient + ") " + text;
				new QListWidgetItem(status, ui.statusList);
			}
		}
		else
		{
			message = "*** Error: Incorrect " + command + " syntax.\n"
				+ "*** Use: " + command + "[username] [message]";
		}
	}
	else if (command == "/help")
	{
		message = "** Help **\n";
		message += '**\n';

		// Private messaging
		message += "** Use /msg, /pm or /whisper to message another user privately.\n";
		message += "** Syntax: /msg [username] [message]";
		message += "** Example: /msg Lucky07 Hey, when did you get on?\n";
		message += '**\n';

		// Server reply
		message += "** Use /hello to check for a server reply.";
	}
	else
	{
		message += "Invalid command";
	}


	// return to sender
	sendToID(message, ID);
}

QTcpSocket* Server::getSocket(int ID)
{
	QTcpSocket* socket;

	for (auto i : clientConnections)
	{
		if (i->socketDescriptor() == ID)
			socket = i;
	}

	return socket;
}

QString Server::getUsername(int ID)
{
	auto itr = userList.find(ID);
	return itr->second;
}

void Server::showFilteredResults()
{
	filterWin->filterList->clear();
	QString filterText = ui.inputLine->text();

	for (int i = 0; i < ui.statusList->count(); ++i)
	{
		QString searchIn = ui.statusList->item(i)->text();
		if (searchIn.contains(filterText, Qt::CaseInsensitive))
		{
			new QListWidgetItem(searchIn, filterWin->filterList);
		}
	}

	filterWin->exec();
}

void Server::serverSendAll()
{
	QString inputText = "Server: " + ui.inputLine->text();
	sendToAll(inputText);
	updateStatus(inputText);
	ui.inputLine->clear();
}

QString Server::timestamp()
{
	QStringList time = QDateTime::currentDateTime().toString().split(" ", QString::SkipEmptyParts);
	time.removeLast();
	time.removeFirst();
	time.removeFirst();
	time.removeFirst();

	return "[" + time.takeFirst() + "]";
}
