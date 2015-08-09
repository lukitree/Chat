#ifndef CLIENT_H
#define CLIENT_H

#include <QtWidgets/QMainWindow>
#include "ui_client.h"
#include "connectdialog.h"
#include <QTcpSocket>
#include <QMessageBox>

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

	QString username;
	ConnectDialog *promptConnect;
	QTcpSocket *tcpSocket;
	quint16 blockSize;

	bool credentialsSent;

	void setUserName(QString name);
	void sendUserCommand(QString command);
};

#endif // CLIENT_H
