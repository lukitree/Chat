#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>

class Server : public QMainWindow
{
	Q_OBJECT

public:
	Server(QWidget *parent = 0);
	~Server();

private slots:
	void sendTest();
	void userDisconnected();
	void sendMessage(QString message);
	void getMessage();

private:
	Ui::ServerClass ui;

	QTcpServer *tcpServer;
	QTcpSocket *clientConnection;
};

#endif // SERVER_H
