---
typora-root-url: ./
---

# TodoList项目开发文档

### 项目介绍

一个待办系统，分为三个部分

1. 待办功能
2. 习惯功能
3. 计划功能，开发中



### 主界面解析

三个功能的大题布局一致，

菜单栏设计了文件，成就两个菜单

右下角为`scrollarea`功能区

设置左侧为`Listwidget`，然后将这个列表布局设置为`vboxlayout`布局，右侧为滚动条，禁用左右滚动。

右上角为一个起装饰作用的`qtoolbutton`，以及一个共同的添加按钮

### 待办功能

每行以一个widget为主，类构造为listitem，继承为widget

功能的数据存放在`data.txt`中，文件命名因为属于早期，不便更改。

| 功能           | 类名 | 下一步设想                                                   |
| -------------- | ---- | ------------------------------------------------------------ |
| 内容标签       |      | 双击可以修改                                                 |
| 修改按钮       |      | 最近的更改为双击弹出的框有默认内容，后期可能不需要按钮，可以直接修改 |
| 删除按钮       |      |                                                              |
| 右键菜单开发中 |      | 方便删除，修改                                               |

与待办功能相关的数据，类，方法

| 数据 | 对应的变量名 |
| ---- | ------------ |
|      |              |
|      |              |
|      |              |
|      |              |



### 习惯功能

跟待办的类结构一致

| 功能              | 类名 | 下一步设想                                                   |
| ----------------- | ---- | ------------------------------------------------------------ |
| 提示习惯标签      |      |                                                              |
| 进度条            |      |                                                              |
| 可以控制的spinbox |      | 没有单位和上限提示，打算设计为只能加一次的盒子，判断加一次的条件，每过一个时间间隔没有加那么直接减一。 |



### 计划功能

