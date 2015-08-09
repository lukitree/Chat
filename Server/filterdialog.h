#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>
#include "ui_filterdialog.h"

class FilterDialog : public QDialog, public Ui::FilterDialog
{
	Q_OBJECT

public:
	FilterDialog(QWidget *parent = 0);
	~FilterDialog();
};

#endif // FILTERDIALOG_H
