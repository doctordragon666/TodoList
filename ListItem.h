#pragma once

#include <QWidget>
#include "ui_ListItem.h"

class ListItem : public QWidget
{
	Q_OBJECT

public:
	ListItem(QWidget *parent = nullptr);
	~ListItem();
	void set_lbl_content(QString lblcontent);
private slots:
    void on_btn_add_clicked();

    void on_btn_del_clicked();

private:
	Ui::ListItemClass ui;
};
