#include "stdafx.h"
#include "ListItem.h"

ListItem::ListItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//setGeometry(parent->x(), parent->y(), parent->width(), parent->height());
	//this->show();
	ui.lbl_content->setText("加油读取QT教程");

	//ui.lbl_content->setStyleSheet("color:white; ");
}

ListItem::~ListItem()
{}

void ListItem::set_lbl_content(QString lblcontent)
{
	ui.lbl_content->setText(lblcontent);
}


void ListItem::on_btn_add_clicked()
{

}

void ListItem::on_btn_del_clicked()
{

}
