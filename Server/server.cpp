#include "server.h"

Server::Server(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	tcpServer = new QTcpServer(this);
	clientConnection = nullptr;
	if (!tcpServer->listen(QHostAddress::Any, 12234))
	{
		QMessageBox::critical(this, tr("Chat Server"),
			tr("Unable to start the server: %1.").arg(tcpServer->errorString()));
		close();
		return;
	}

	int port = tcpServer->serverPort();
	ui.statusText->setText(tr("Listening on port: %1").arg(port));

	connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendTest()));
	connect(clientConnection, SIGNAL(readyRead()), this, SLOT(sendMsg()));
}

Server::~Server()
{

}

void Server::sendTest()
{
	ui.statusText->setText("Connection Made!");
	new QListWidgetItem("Connection Made!", ui.statusList);

	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	QString message;
	message = "Server: Connected!";

	out << message;

	clientConnection = tcpServer->nextPendingConnection();
	connect(clientConnection, SIGNAL(disconnected()), clientConnection, SLOT(deleteLater()));
	connect(clientConnection, SIGNAL(readyRead()), SLOT(getMessage()));

	clientConnection->write(block);
	//clientConnection->disconnectFromHost();
}

void Server::userDisconnected()
{
	ui.statusText->setText("User Disconnected.");
	new QListWidgetItem("User Disconnected.", ui.statusList);
}

void Server::sendMessage(QString message)
{
	QByteArray msg;
	QDataStream out(&msg, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	out << message;

	clientConnection->write(msg);
}

void Server::getMessage()
{
	QDataStream in(clientConnection);
	in.setVersion(QDataStream::Qt_4_0);

	QString message;
	in >> message;

	new QListWidgetItem("Recieved: " + message, ui.statusList);
	sendMessage(message);
}