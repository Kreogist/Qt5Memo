#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    //这里可以添加一些初始化代码
    //用于进行所有应该在QApplication创建之前进行的初始化
    //比如：使用`setColorSpec()`分配颜色之类的

    QApplication a(argc, argv);

    //在QApplication初始化后，所有基于QWidget的类才能正常使用
    //例如下面的QLabel什么的。

    QLabel label("Hello World!");
    label.show();

    return a.exec();
}
