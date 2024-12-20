#ifndef GLOBAL_H
#define GLOBAL_H


/****************************************************
 * 文件说明：该文件是其他所有文件都要用到的头文件
 * 例如qstring和C语言的标准库
****************************************************/

#include <vector>
#include <QString>
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

#endif // GLOBAL_H
