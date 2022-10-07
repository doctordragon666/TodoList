#pragma once

#include <QWidget>
#include <qlayout.h>
#include <qstring.h>
#include <qfile.h>

#include "ui_ListItem.h"

class ListItem : public QWidget
{
	Q_OBJECT

public:
	ListItem(QVBoxLayout* container=nullptr, QWidget *parent = nullptr);
	~ListItem();
	void set_lbl_content(QString lblcontent);
	QString get_lbl_content();
	bool delete_flag = false;
private slots:
    void on_btn_add_clicked();

    void on_btn_del_clicked();

private:
	Ui::ListItemClass ui;
	QVBoxLayout* m_container;
};
