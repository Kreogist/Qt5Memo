/*
 *This is an example of Qt5Memo.
 *You can use this code under the GPLv3 license.
 */

#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QObject>
#include <iostream>

using namespace std;

class Example : public QObject
{
    Q_OBJECT
public:
    explicit Example(QObject *parent = 0);

    void emit_signal(){emit signal_emited();}
    void connect123();
    void connect132();
    void break_connection();

public slots:
    void slot1(){cout<<"slot1"<<endl;}
    void slot2(){cout<<"slot2"<<endl;}
    void slot3(){cout<<"slot3"<<endl;}

signals:
    void signal_emited();

private:
    QMetaObject::Connection connection_handle[3];
    
};

#endif // EXAMPLE_H
