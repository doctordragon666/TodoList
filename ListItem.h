#pragma once

#include <QWidget>
#include "ui_ListItem.h"

class ListItem : public QWidget
{
	Q_OBJECT

public:
	ListItem(QWidget *parent = nullptr);
	~ListItem();

private:
	Ui::ListItemClass ui;
};
