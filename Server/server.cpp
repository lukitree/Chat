#include "server.h"

Server::Server(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

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
}

Server::~Server()
{

}

void Server::newConnection()
{
	updateStatus("New connection established.");

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
		updateStatus("Connection terminated.");
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
		QString recipient = commandTokens.takeFirst();
		int rID = 0;
		for (auto i : userList)
		{
			if (i.second == recipient)
				rID = i.first;
		}

		if (rID == 0)
			message += "User not found.";
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
		message += "Invalid command";
	}


	// return to sender
	sendToID(message, ID);
}
