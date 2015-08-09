#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_client.h"
#include "connectdialog.h"
#include <QTcpSocket>
#include <QMessageBox>
#include <QHostAddress>

class Client : public QMainWindow
{
	Q_OBJECT

public:
	Client(QWidget *parent = 0);
	~Client();

private slots:
	void on_sendButton_clicked();
	void on_actionConnect_triggered();
	void on_actionDisconnect_triggered();
	void on_actionReconnect_triggered();
	void displayError(QAbstractSocket::SocketError socketError);
	void getMessage();
	void sendCredentials();
	void onDisconnect();
	void onConnect();
	void whisperOnClick(QListWidgetItem* user);

private:
	Ui::ClientClass ui;

	ConnectDialog *promptConnect;
	QTcpSocket *tcpSocket;
	quint16 blockSize;

	bool credentialsSent;

	void sendUserCommand(QString command);
	QString replaceWhiteSpace(QString text);
	QString getIP();
};

#endif // CLIENT_H
