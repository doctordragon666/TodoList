#pragma once

#include <QWidget>
#include "ui_Hobby.h"

class Hobby : public QWidget
{
	Q_OBJECT

public:
	Hobby(QWidget *parent = nullptr);
	~Hobby();

private:
	Ui::HobbyClass ui;
};
