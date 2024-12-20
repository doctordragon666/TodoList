#include "ListItem.h"
#include <QInputDialog>

ListItem::ListItem(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

ListItem::~ListItem()
{
}

void ListItem::set_lbl_content(QString lblcontent)
{
	ui.lbl_content->setText(lblcontent);
}

QString ListItem::get_lbl_content()
{
	return ui.lbl_content->text();
}

void ListItem::on_btn_add_clicked()
{
	QString content = QInputDialog::getText(this, "提示", "重命名待办为", QLineEdit::Normal, this->get_lbl_content());
	if (content.isEmpty())
	{
		return;
	}
	ui.lbl_content->setText(content);
}

void ListItem::on_btn_del_clicked()
{
    deleteLater();
}
