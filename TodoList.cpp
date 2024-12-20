#include "TodoList.h"
#include "ListItem.h"
#include <QCloseEvent>
#include "ui_ListItem.h"

TodoList::TodoList(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
    //setWindowIcon(QIcon("D:/C primer plus/TodoList/TodoList.ico"));

	//全局字体设置
	QFont font;
	font.setPointSize(12);
	font.setBold(true);
	setFont(font);

	//窗口置顶
	Qt::WindowFlags m_flags = windowFlags();
	setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);

	//菜单栏控制

	//加载待办和习惯文件
	m_src = new QFile(m_filename);
	m_hobby = new QFile(m_hobby_file);
	m_record = new QFile(m_record_file);
	if (!loadfile(m_src, m_todo_list) || !loadfile(m_hobby, m_hobby_list) || !loadfile(m_record, m_record_list))
	{
		QMessageBox::information(NULL, "提示", "请重启程序");
		exit(-1);
	}

	//菜单关联
	connect(ui.action_save, SIGNAL(triggered()), this, SLOT(sure_del()));
	connect(ui.action_success, SIGNAL(triggered()), this, SLOT(show_success()));

	//初始化左边的菜单
	for (int i = 0; i < ui.list_choose->count(); i++)
	{
		QListWidgetItem* note = ui.list_choose->item(i);
		QFont note_font;
		note_font.setBold(true);
		note_font.setFamily("KaiTi");
		note_font.setUnderline(true);
		note_font.setPointSize(15);
		note->setFont(note_font);
		note->setToolTip(list_lbl_content[i]);
		note->setTextAlignment(Qt::AlignCenter);
	}

	//获取下边的内容
	m_layout = new QVBoxLayout;
	m_layout->setAlignment(Qt::AlignTop);
	initlayout(0);//默认初始化待办
	ui.Content->setLayout(m_layout);
	ui.list_item->setWidget(ui.Content);

	//获取上面的菜单


	//关联按钮


	//设置窗口自定义伸缩
	QSizePolicy size(QSizePolicy::Preferred, QSizePolicy::Expanding);
	ui.centralWidget->setSizePolicy(size);
	ui.menuBar->setSizePolicy(size);
	ui.menu->setSizePolicy(size);
	ui.mainToolBar->setSizePolicy(size);

	//确定缩放条
}

TodoList::~TodoList()
{}

bool TodoList::loadfile(QFile*& file, QStringList& contain)
{
	//判断文件是否存在
	if(!file->exists())
	{
        qDebug() << "file not exist\n";
		file->open(QIODevice::WriteOnly | QIODevice::Text);
		file->close();
		return false;
	}

	QStringList Line;
	QString item;
	//刻度可写文件
	if (file->open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream stream(file);
		stream.setCodec("utf-8");
		while (!stream.atEnd())
		{
			Line = stream.readLine().split(",");
			if (Line.size() > 2)
			{
				m_hobby_line.push_back(hobby_line(Line[1], Line[2].toInt(), Line[3].toInt()));
			}
			item = Line[1];
			contain.push_back(item);
		}
		file->close();
		return true;
	}
	else
	{
		qDebug() << "file is open failed" << strerror(errno) << "file size is " << file->size() << endl;
		file->close();
	}
	return true;
}

void TodoList::initlayout(int choose)
{
	clearlayout(change == -1 ? TODO : HOBBY);
	if (choose == 0)
	{
		ListItem* todo_item = nullptr;
		for (int i = 0; i < m_todo_list.size(); i++)
		{
			todo_item = new ListItem(m_layout);
			todo_item->set_lbl_content(m_todo_list[i]);
			m_layout->addWidget(todo_item);
		}
	}
	else if (choose == 1)
	{
		Hobby* hobby_item = nullptr;
		for (int i = 0; i < m_hobby_list.size(); i++)
		{
			hobby_item = new Hobby();
			hobby_item->set_hobby(m_hobby_list[i]);
			hobby_item->set_target(m_hobby_line[i].m_target);
			hobby_item->set_process(m_hobby_line[i].m_process);
			hobby_item->set_point(m_hobby_line[i].m_process);
			m_layout->addWidget(hobby_item);
		}
	}
	flag = choose;
	ui.Content->setLayout(m_layout);
	ui.list_item->setWidget(ui.Content);
}

void TodoList::clearlayout(layout_name name)
{
	if (!change)
		return;
	for (int i = 0; i < m_layout->count(); i++)
	{
		switch (name)
		{
		case TODO:
		{
			ListItem* todo_item = (ListItem*)m_layout->itemAt(i)->widget();
			if (todo_item != nullptr)
			{
				todo_item->deleteLater();
			}
		}
		break;
		case HOBBY:
		{
			Hobby* hobby_item = (Hobby*)m_layout->itemAt(i)->widget();
			if (hobby_item != nullptr)
			{
				m_hobby_line[i].m_process = hobby_item->get_process();
				hobby_item->deleteLater();
			}
		}
		break;
		default:
			break;
		}
	}
}

void TodoList::savefile(QFile*& file, QStringList& contain, int flag_f)
{
	QString s;
	file->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
	QTextStream stream(file);
	stream.setCodec("utf-8");
	stream.setFieldAlignment(QTextStream::AlignLeft);
	for (int i = 0; i < contain.size(); i++)
	{
		if (flag_f == 1)
		{
			stream << i << "," << contain[i] << "\n";
		}
		else if (flag_f == 2)
		{
			if (m_hobby_line[i].m_target != m_hobby_line[i].m_process)
			{
				stream << i << "," << contain[i] << "," << m_hobby_line[i].m_target << "," << m_hobby_line[i].m_process << "\n";
			}
			else
			{
				m_record->open(QIODevice::Append | QIODevice::Text);
				QTextStream record_s(m_record);
				record_s.setCodec("utf-8");
				record_s.setFieldAlignment(QTextStream::AlignLeft);
				record_s << m_record_list.size() << "," << m_hobby_line[i].m_hobby << "\n";
				m_record->close();
			}
		}
	}
	file->close();
}

void TodoList::closeEvent(QCloseEvent* event)
{
	if (QMessageBox::question(this, "提示", "你确定要退出吗, 点击确定保存当前待办") == QMessageBox::Yes)
	{
		this->sure_del();
		this->close();
		event->accept();
	}
	else
	{
		event->ignore();
	}
}

void TodoList::show_success()
{
	QString text;
	for (auto i : m_record_list)
	{
		text += i + "\n";
	}
	//QMessageBox::aboutQt(this);
	
	QMessageBox::about(this, "你已经达成的习惯", text);
}

void TodoList::sure_del()
{
	//判断当前有多少个项目
	m_layout->update();
	if (flag == 0)
	{
		m_todo_list.clear();
		for (int i = 0; i < m_layout->count(); i++)
		{
			ListItem* todo_item = (ListItem*)m_layout->itemAt(i)->widget();
			if (todo_item != nullptr)
			{
				QString item = todo_item->get_lbl_content();
				m_todo_list.push_back(item);
			}
		}
	}
	savefile(m_src, m_todo_list);
	savefile(m_hobby, m_hobby_list, 2);
}

void TodoList::on_btn_add_clicked()
{
	if (flag == 0)
	{
		QString content = QInputDialog::getText(this, "提示", "请输入代办事项");
		if (content.isEmpty())
		{
			return;
		}
		ListItem* item = new ListItem(m_layout);
		item->set_lbl_content(content);

		//保存并更新布局
		m_todo_list.push_back(content);
		m_layout->addWidget(item);
		savefile(m_src, m_todo_list);
	}
	else if (flag == 1)
	{
		QString content = QInputDialog::getText(this, "提示", "请输入你的习惯, 以及你需要多少(默认21)天完成，中间用逗号隔开");
		if (content.isEmpty())
		{
			return;
		}
		QStringList way = content.split(",");
		Hobby* item = new Hobby(m_layout);
		item->set_process(0);
		if (way.size() <= 1)
		{
			item->set_hobby(content);
			item->set_target(21);
			m_hobby_list.push_back(content);
			m_hobby_line.push_back(hobby_line(content, 21, 0));
		}
		else
		{
			item->set_hobby(way[0]);
			item->set_target(way[1].toInt());
			m_hobby_list.push_back(way[0]);
			m_hobby_line.push_back(hobby_line(way[0], way[1].toInt(), 0));
		}

		//保存并更新布局
		m_layout->addWidget(item);
		savefile(m_hobby, m_hobby_list, 2);
	}
}

void TodoList::on_list_choose_itemClicked(QListWidgetItem* item)
{
	int index;
	for (index = 0; index < list_lbl_content.size(); index++)
	{
		if (item->toolTip() == list_lbl_content[index])
			break;
	}
	change = (index == flag) ? 0 : flag - index;
	if (change == 0)
		return;
	initlayout(index);
}
