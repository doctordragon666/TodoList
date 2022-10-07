#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qstackedlayout.h>
#include "ui_TodoList.h"
#include "Hobby.h"
#include "ui_Hobby.h"
#include <vector>

struct todo_line
{
    int index;
    QString todo;
};//文件中todo_line

struct hobby_line
{
    QString m_hobby;//习惯
    int m_target;//习惯的坚持时间
    int m_process;//目标当前进度
    hobby_line(QString hobby, int target, int process) :m_hobby(hobby), m_target(target), m_process(process) {}
};//文件中todo_list的每一行

class TodoList : public QMainWindow
{
    Q_OBJECT

public:
    TodoList(QWidget *parent = nullptr);
    ~TodoList();
    bool loadfile(QFile*& file, QStringList& contain);
    void initlayout(int choose);
    void savefile(QFile*& file, QStringList& contain, int flag = 1);
    void closeEvent(QCloseEvent* event);
private slots:
    void on_btn_add_clicked();
    void sure_del();
    void on_list_choose_itemClicked(QListWidgetItem *item);

private:
    Ui::TodoListClass ui;

    QStringList m_todo_list;
    QStringList m_hobby_list;
    QStringList m_record_list;
    std::vector<hobby_line> m_hobby_line;

    QFile* m_src;
    QFile* m_hobby;
    QFile* m_record;
    const QString m_filename = "./data.txt";
    const QString m_hobby_file = "./hobby.txt";
    const QString m_record_file = "./record.txt";

    QVBoxLayout* m_layout;
    QStringList list_lbl_content = { "查看代办","养成习惯" };
    int flag = 0;//默认待办

    int change = 0;
};
