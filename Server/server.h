#ifndef SERVER_H
#define SERVER_H

#include <QtWidgets/QMainWindow>
#include "ui_server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QList>
#include <QTimer>
#include <QDateTime>
#include "filterdialog.h"

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
	void getMessage();
	void newConnection();
	void onDisconnect();
	void sendUserList();
	void showFilteredResults();
	void serverSendAll();

private:
	Ui::ServerClass ui;

	QTcpServer *tcpServer;
	QList<QTcpSocket*> clientConnections;
	std::map<const int, QString> userList;
	FilterDialog *filterWin;

	void updateStatus(QString message);
	void doCommand(QString command, int ID);
	void sendToID(QString message, int ID);
	void sendToAll(QString message);

	QTcpSocket* getSocket(int ID);
	QString getUsername(int ID);
	QString timestamp();
};

#endif // SERVER_H
