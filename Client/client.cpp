#include "client.h"

Client::Client(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	tcpSocket = new QTcpSocket(this);

	username = "NoName";
	credentialsSent = false;

	connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(getMessage()));
	connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
}

Client::~Client()
{

}

void Client::setUserName(QString name)
{
	this->username = name;
}

void Client::on_sendButton_clicked()
{
	QString message = ui.messageEdit->text();
	ui.messageEdit->clear();

	blockSize = 0;

	if (!message.isEmpty())
	{
		QByteArray msg;
		QDataStream out(&msg, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);

		out << message;

		tcpSocket->write(msg);
	}
}

void Client::on_actionConnect_triggered()
{
	QDataStream in(tcpSocket);

	if (promptConnect.exec())
	{
		QString hostname = promptConnect.hostnameEdit->text();
		quint16 port = promptConnect.portEdit->text().toInt();
		setUserName(promptConnect.usernameEdit->text());

		QString status = tr("-> Connecting to %1 on port %2.").arg(hostname).arg(port);
		new QListWidgetItem(status, ui.messageList);
		ui.messageList->scrollToBottom();

		tcpSocket->abort();
		tcpSocket->connectToHost(hostname, port);

		connect(tcpSocket, SIGNAL(connected()), this, SLOT(sendCredentials()));
		connect(tcpSocket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
	}
}

void Client::on_actionDisconnect_triggered()
{
	tcpSocket->abort();

	QString status = tr("-> Disconnecting from %1.").arg(promptConnect.hostnameEdit->text());
	new QListWidgetItem(status, ui.messageList);
	ui.messageList->scrollToBottom();
}

void Client::getMessage()
{
	QDataStream in(tcpSocket);
	in.setVersion(QDataStream::Qt_4_0);

	QString message;
	in >> message;

	enum class COMMAND { NONE, USERLIST};
	COMMAND cmd = COMMAND::NONE;

	QStringRef checkCmd(&message, 0, 5);
	if (checkCmd == "_LST_")
		cmd = COMMAND::USERLIST;

	QStringList commandList;

	switch (cmd)
	{
	case COMMAND::USERLIST:
		commandList = message.split(" ", QString::SkipEmptyParts);
		commandList.removeFirst();
		ui.userList->clear();
		for (auto i : commandList)
		{
			new QListWidgetItem(i, ui.userList);
		}
		break;
	default:
		//in >> message;

		new QListWidgetItem(message, ui.messageList);
		ui.messageList->scrollToBottom();
	}

}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
	switch (socketError)
	{
	case QAbstractSocket::RemoteHostClosedError:
		QMessageBox::information(this, tr("Chat Client"),
			tr("Disconnected from Server."));
		break;
	case QAbstractSocket::HostNotFoundError:
		QMessageBox::information(this, tr("Chat Client"),
			tr("The host was not found.\nPlease check the hostname and port settings."));
		break;
		case QAbstractSocket::ConnectionRefusedError:
			QMessageBox::information(this, tr("Chat Client"),
				tr("The connection was refused by the peer.\n"
				"Make sure the server is running,\n"
				"and check that the host name and port\n"
				"settings are correct."));
			break;
		default:
			QMessageBox::information(this, tr("Chat Client"),
				tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
	}
}

void Client::sendCredentials()
{
	if (!credentialsSent)
	{
		credentialsSent = true;

		new QListWidgetItem("-> Sending Credentials...", ui.messageList);
		ui.messageList->scrollToBottom();

		QByteArray block;
		QDataStream out(&block, QIODevice::WriteOnly);
		out.setVersion(QDataStream::Qt_4_0);

		QString command = "_USR_";
		out << command;
		out << username;
		tcpSocket->write(block);
	}
}

void Client::onDisconnect()
{
	new QListWidgetItem("-> Disconnected.", ui.messageList);
	ui.messageList->scrollToBottom();
	ui.userList->clear();
	credentialsSent = false;
}
