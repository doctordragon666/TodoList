#pragma once

/****************************************************
 * 文件说明：该文件是代办程序的主要核心代码，分为几个内容
 * 上面的menubar菜单栏，有一个成就系统，保存已经完成的习惯
 * 还有一个文件，可以保存结果（代码设计的失误，需要手动保存）
 *
 * 接下来分三个区域，一个区域是放置添加listitem, hobby子
 * 类的按钮，另外一个区域是存放子类的列表，还有一个区域是为
 * 了切换代办和习惯子类的一个listview
 *
 * 涉及了所有的文件，这些文件存放在example文件夹下
 *
 * 1. 读取保存文件
 * 2. 监听关闭事件，提醒保存
 * 3. 初始化存放子类的列表
****************************************************/

#include "global.h"
#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <qlistwidget.h>
#include <qstackedlayout.h>
#include "ui_TodoList.h"
#include "Hobby.h"
#include "ui_Hobby.h"
#include <vector>
#include <QInputDialog>
#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QLabel>

class TodoList : public QMainWindow
{
    Q_OBJECT

public:
    TodoList(QWidget* parent = nullptr);
    ~TodoList();
    bool loadfile(QFile*& file, QStringList& contain);
    void savefile(QFile*& file, QStringList& contain, int flag = 1);

    void initlayout(int choose);
    void clearlayout(layout_name name);

    void closeEvent(QCloseEvent* event);
private slots:
    void show_success();
    void sure_del();
    void on_btn_add_clicked();
    void on_list_choose_itemClicked(QListWidgetItem* item);

private:
    Ui::TodoListClass ui;

    QStringList m_todo_list;//待办列表
    QStringList m_hobby_list;//习惯列表
    QStringList m_record_list;//记录列表
    std::vector<hobby_line> m_hobby_line;//习惯写入文件的格式

    QFile* m_src;//待办文件句柄
    QFile* m_hobby;//习惯文件句柄
    QFile* m_record;//记录文件句柄
    const QString TODO_FILE = "./data.txt";//默认的待办文件名
    const QString HOBBY_FILE = "./hobby.txt";//默认的习惯文件名
    const QString RECORD_FILE = "./record.txt";//默认的记录文件名

    QVBoxLayout* m_layout;//内容（待办习惯）布局
    QStringList list_lbl_content = { "查看代办","养成习惯" };
    int flag = 0;//渲染那个布局，0待办，1习惯

    int change = 0;//是否切换了界面
};
