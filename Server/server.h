#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QList>

class Server : public QMainWindow
{
	Q_OBJECT

public:
	Server(QWidget *parent = 0);
	~Server();

private slots:
	void sendMessage(QString message, QTcpSocket& socket);
	void sendToAll(QString message);
	void getMessage();
	void newConnection();
	void onDisconnect();
	// void sendUserList(); // not implemented

private:
	Ui::ServerClass ui;

	QTcpServer *tcpServer;
	QList<QTcpSocket*> clientConnections;
	std::map<int, QString> userList;

	void updateStatus(QString message);
};

#endif // SERVER_H
