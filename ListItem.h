#ifndef LISTITEM_H
#define LISTITEM_H

/****************************************************
 * 文件说明：该文件是TodoList的中的另一个list_item的填充物
 * 仅能设置和获取标签内容，并且添加和删除代办。
****************************************************/

#include <QWidget>
#include "ui_ListItem.h"

class ListItem : public QWidget
{
	Q_OBJECT

public:
    ListItem(QWidget *parent = nullptr);
	~ListItem();
	void set_lbl_content(QString lblcontent);
	QString get_lbl_content();
private slots:
    void on_btn_add_clicked();

    void on_btn_del_clicked();

private:
	Ui::ListItemClass ui;
};
#endif
