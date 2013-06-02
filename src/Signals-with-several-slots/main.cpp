/*
 *This is an example of Qt5Memo.
 *You can use this code under the GPLv3 license.
 */

#include <QCoreApplication>
#include <QObject>

#include "example.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Example e;
    //first,we connect the signal with the slots.in a order.
    //And emit the signal
    e.connect123();
    e.emit_signal();

    e.break_connection();

    //then,we connect the signal with the slots.in another order.
    //And emit the signal
    e.connect132();
    e.emit_signal();

    e.break_connection();
    
    return a.exec();
}
