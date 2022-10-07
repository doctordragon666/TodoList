#pragma once

#include <QWidget>
#include "ui_Hobby.h"

class Hobby : public QWidget
{
	Q_OBJECT

public:
	Hobby(QVBoxLayout* container = nullptr, QWidget* parent = nullptr);
	~Hobby();
	void set_hobby(QString hobby);
	QString get_hobby();
	void set_process(int now_process);
	int get_process();
	void set_target(int time);
	void set_point(int point);
private slots:
    void on_days_valueChanged(int arg1);

private:
    int target = 21;
	Ui::HobbyClass ui;
	QVBoxLayout* m_container;
};
