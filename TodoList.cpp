#include "stdafx.h"
#include "TodoList.h"
#include "ListItem.h"
#include "ui_ListItem.h"

TodoList::TodoList(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    //菜单栏控制

    //加载文件
    m_src = new QFile(m_filename);
    if (!loadfile())
    {
        QMessageBox::information(NULL, "提示", "请重启程序");
        exit(-1);
    }

    //加载主文件
    

    //初始化右边的菜单
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
    }

    //获取下边的菜单
    m_layout = ui.centralWidget->findChild<QVBoxLayout*>("list_layout");
    initlayout();

    //获取上面的菜单

    //关联按钮

    ui.main_layout->update();

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
    //刻度可写文件
    if (m_src->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream stream(m_src);
        while (!stream.atEnd())
        {
            Line = stream.readLine();
            
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
    ListItem* lst_1 = new ListItem();
    m_layout->addWidget(lst_1);
    ui.list_layout->addWidget(lst_1);
}
