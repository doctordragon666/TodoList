#include "stdafx.h"
#include "TodoList.h"
#include "ListItem.h"
#include "ui_ListItem.h"

TodoList::TodoList(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QFont font;
    font.setPointSize(12);
    setFont(font);

    Qt::WindowFlags m_flags = windowFlags();
    setWindowFlags(m_flags | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    //菜单栏控制

    //加载文件
    m_src = new QFile(m_filename);
    if (!loadfile())
    {
        QMessageBox::information(NULL, "提示", "请重启程序");
        exit(-1);
    }

    //加载主文件
    connect(ui.action_save, SIGNAL(triggered()), this, SLOT(sure_del()));

    //初始化左边的菜单
    QStringList list_content = { "查看代办","养成习惯" };
    for (int i=0; i< ui.list_choose->count();i++)
    {
        QListWidgetItem* note = ui.list_choose->item(i);
        QFont note_font;
        note_font.setBold(true);
        note_font.setFamily("KaiTi");
        note_font.setUnderline(true);
        note_font.setPointSize(15);
        note->setFont(note_font);
        note->setToolTip(list_content[i]);
        note->setTextAlignment(Qt::AlignCenter);
    }

    //获取下边的菜单
    m_layout = new QVBoxLayout;
    m_layout->setAlignment(Qt::AlignTop);
    initlayout();
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

bool TodoList::loadfile()
{
    //判断文件是否存在
    if (!m_src->exists())
    {
        qDebug() << "file not exist" << endl;
        m_src->open(QIODevice::WriteOnly | QIODevice::Text);
        m_src->close();
        return false;
    }

    QString Line;
    QString todo;
    //刻度可写文件
    if (m_src->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(m_src);
        stream.setCodec("utf-8"); 
        while (!stream.atEnd())
        {
            Line = stream.readLine();
            todo = Line.split(",")[1];
            m_todo_list.push_back(todo);
        }
        m_src->close();
        return true;
    }
    qDebug() << "file is open failed" << strerror(errno) << "file size is " << m_src->size() << endl;
    m_src->close();
    return true;
}

void TodoList::initlayout()
{
    ListItem* todo_item = nullptr;
    for (int i = 0; i < m_todo_list.size(); i++)
    {
        todo_item = new ListItem(m_layout);
        todo_item->set_lbl_content(m_todo_list[i]);
        m_layout->addWidget(todo_item);
    }
}

void TodoList::savefile()
{
    QString s;
    m_src->open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream stream(m_src);
    stream.setCodec("utf-8");
    stream.setFieldAlignment(QTextStream::AlignLeft);
    for (int i = 0; i < m_todo_list.size(); i++)
    {
        stream << i << "," << m_todo_list[i] << "\n";
    }
    m_src->close();
}

void TodoList::sure_del()
{
    //判断当前有多少个项目
    m_layout->update();
    m_todo_list.clear();
    for (int i = 0; i < m_layout->count(); i++)
    {
        ListItem* todo_item = (ListItem*)m_layout->itemAt(i)->widget();
        todo_item->isHidden();
        if (todo_item != nullptr)
        {
            QString item = todo_item->get_lbl_content();
            m_todo_list.push_back(item);
        }
    }
    savefile();
}

/// <summary>
/// 添加按钮处理
/// </summary>
void TodoList::on_btn_add_clicked()
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
    savefile();
}
