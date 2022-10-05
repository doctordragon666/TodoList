#include "stdafx.h"
#include "ListItem.h"

ListItem::ListItem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//setGeometry(parent->x(), parent->y(), parent->width(), parent->height());
	//this->show();
	ui.lbl_content->setText("加油读取QT教程");

	this->setStyleSheet("background-color:lightgreen;");
	ui.btn_add->setStyleSheet("background-color:lightgreen;");
	ui.btn_mark->setStyleSheet("background-color:yellow;");
	ui.lbl_content->setStyleSheet("color:white; ");
	ui.btn_del->setStyleSheet("background-color:red;");
}

ListItem::~ListItem()
{}

