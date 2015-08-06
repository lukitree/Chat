#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QList>
#include <QTimer>

class Server : public QMainWindow
{
	Q_OBJECT

public:
	Server(QWidget *parent = 0);
	~Server();

signals:
	void SEND_UserList();

private slots:
	void sendMessage(QString message, QTcpSocket& socket);
	void sendToAll(QString message);
	void getMessage();
	void newConnection();
	void onDisconnect();
	void sendUserList();

private:
	Ui::ServerClass ui;

	QTcpServer *tcpServer;
	QList<QTcpSocket*> clientConnections;
	std::map<const int, QString> userList;

	void updateStatus(QString message);
};

#endif // SERVER_H
