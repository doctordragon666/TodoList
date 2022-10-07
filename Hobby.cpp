#include "stdafx.h"
#include "Hobby.h"

Hobby::Hobby(QVBoxLayout* container, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_container = container;
	ui.process->setValue(10);
}

Hobby::~Hobby()
{}

void Hobby::set_hobby(QString hobby)
{
	ui.lbl_content->setText(hobby);
}

QString Hobby::get_hobby()
{
	return ui.lbl_content->text();
}

void Hobby::set_process(int now_process)
{
	ui.process->setValue(now_process);
}

int Hobby::get_process()
{
	return ui.days->value();
}

void Hobby::set_target(int time)
{
	target = time;
	ui.days->setMaximum(target);
}

void Hobby::set_point(int point)
{
	ui.days->setValue(point);
}

void Hobby::on_days_valueChanged(int arg1)
{
	if (target != 0)
	{
		ui.process->setValue(((double)arg1 / (double)target) * 100);
	}
	else
	{
		ui.process->setValue(100);
	}
}
