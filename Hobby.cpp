#include "Hobby.h"

Hobby::Hobby(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

Hobby::~Hobby()
{
}

void Hobby::set_hobby(QString hobby)
{
	ui.lbl_content->setText(hobby);
}

void Hobby::set_process(int now_process)
{
	ui.process->setValue(now_process);
	ui.days->setValue(now_process);//同时设置spinbox的值
}

int Hobby::get_process() const
{
	return ui.days->value();
}

void Hobby::set_target(int time)
{
	target = time;
	ui.days->setMaximum(time);
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
