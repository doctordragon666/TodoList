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

enum layout_name
{
    TODO,
    HOBBY
};

class TodoList : public QMainWindow
{
    Q_OBJECT

public:
    TodoList(QWidget *parent = nullptr);
    ~TodoList();
    bool loadfile(QFile*& file, QStringList& contain);
    void initlayout(int choose);
    /// <summary>
    /// 清空布局
    /// </summary>
    /// <param name="choose">指定清空的布局</param>
    void clearlayout(layout_name name);
    /// <summary>
    /// 保存文件
    /// </summary>
    /// <param name="file">保存的文件</param>
    /// <param name="contain">保存内容的容器</param>
    /// <param name="flag">标志，1表示默认待办</param>
    void savefile(QFile*& file, QStringList& contain, int flag = 1);
    /// <summary>
    /// 重载的退出事件，提示用户是否真退出
    /// </summary>
    /// <param name="event">事件句柄</param>
    void closeEvent(QCloseEvent* event);
private slots:
    void show_success();
    /// <summary>
    /// 确定删除，绑定了保存和退出事件
    /// </summary>
    void sure_del();
    /// <summary>
    /// 根据当前的flag设置不同的添加界面
    /// </summary>
    void on_btn_add_clicked();
    /// <summary>
    /// 找到这个item属于哪个标签，然后判断flag和choose是否相等
    /// 如果相等则设置change=0，否则就将change设置为两者的差值，并且更新布局
    /// </summary>
    /// <param name="item"></param>
    void on_list_choose_itemClicked(QListWidgetItem *item);

private:
    Ui::TodoListClass ui;

    QStringList m_todo_list;//待办列表
    QStringList m_hobby_list;//习惯列表
    QStringList m_record_list;//记录列表
    std::vector<hobby_line> m_hobby_line;//习惯写入文件的格式

    QFile* m_src;//待办文件句柄
    QFile* m_hobby;//习惯文件句柄
    QFile* m_record;//记录文件句柄
    const QString m_filename = "./data.txt";//默认的待办文件名
    const QString m_hobby_file = "./hobby.txt";//默认的习惯文件名
    const QString m_record_file = "./record.txt";//默认的记录文件名

    QVBoxLayout* m_layout;//下方菜单布局
    QStringList list_lbl_content = { "查看代办","养成习惯" };
    int flag = 0;//渲染那个布局，0待办，1习惯

    int change = 0;//是否切换了界面
};
