#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>
#include "ui_connectdialog.h"

class ConnectDialog : public QDialog, public Ui::ConnectDialog
{
	Q_OBJECT

public:
	ConnectDialog(QWidget *parent = 0);
	~ConnectDialog();
};

#endif // CONNECTDIALOG_H
