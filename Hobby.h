#ifndef HOBBY_H
#define HOBBY_H

/****************************************************
 * 文件说明：该文件是TodoList的中的一个list_item的填充物
 * 仅提供渲染习惯标签渲染功能，以及提供代办的进度的获取和查询。
****************************************************/
#include <QWidget>
#include "ui_Hobby.h"

class Hobby : public QWidget
{
	Q_OBJECT

public:
    Hobby(QWidget* parent = nullptr);
	~Hobby();
	void set_hobby(QString hobby);
	void set_process(int now_process);
    int get_process() const;
	void set_target(int time);
private slots:
    void on_days_valueChanged(int arg1);

private:
    int target = 21;
	Ui::HobbyClass ui;
};
#endif // HOBBY_H
