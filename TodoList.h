#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/qpushbutton.h>
#include <qlabel.h>
#include <qlistwidget.h>
#include <qstackedlayout.h>
#include "ui_TodoList.h"
#include "Hobby.h"
#include "ui_Hobby.h"


class TodoList : public QMainWindow
{
    Q_OBJECT

public:
    TodoList(QWidget *parent = nullptr);
    ~TodoList();
    bool loadfile();
    void initlayout();
private:
    Ui::TodoListClass ui;
    QStringList m_todo_list;
    QStringList m_hobby_list;
    QFile* m_src;
    const QString m_filename = "./data.txt";
    QVBoxLayout* m_layout;
};
