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

	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));
	connect(this, SIGNAL(newConnection()), this, SLOT(getMessage()));
}

Server::~Server()
{

}

void Server::newConnection()
{
	updateStatus("New connection established.");

	QTcpSocket *newSocket = tcpServer->nextPendingConnection();
	connect(newSocket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
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
		//auto itr = userList.find(socket->socketDescriptor());
		//auto i = ui.userList->findItems(itr->second, Qt::MatchExactly);
		//ui.userList->takeItem(i);

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

void Server::getMessage()
{
	QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
	QDataStream in(client);
	in.setVersion(QDataStream::Qt_4_0);

	QString message;
	in >> message;

	enum class COMMAND { USERNAME, };
	COMMAND cmd;

	if (message == "_USR_")
		cmd = COMMAND::USERNAME;

	QString username;
	QString userAddress;
	int ID;
	std::map<int, QString>::iterator it;

	switch (cmd)
	{
	case COMMAND::USERNAME:

		in >> message;

		username = message;
		ID = client->socketDescriptor();

		userList.insert(std::make_pair(ID, username));
		new QListWidgetItem(username, ui.userList);
		ui.userList->scrollToBottom();
		break;
	default:
		it = userList.find(client->socketDescriptor());
		updateStatus("MSG: (" + it->second + ") " + message);

		std::map<int, QString>::iterator it;
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

/* not implemented
void Server::sendUserList()
{
	QTcpSocket *newSocket = qobject_cast<QTcpSocket*>(sender());

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << "_LST_";
	for (auto i : userList)
	{
		out << i.second;
	}
	out << "_END_";
	newSocket->write(block);
}
*/