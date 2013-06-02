/*
 *This is an example of Qt5Memo.
 *You can use this code under the GPLv3 license.
 */

#include "example.h"

Example::Example(QObject *parent) :
    QObject(parent)
{
}

void Example::connect123()
{
    connection_handle[0]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot1()));
    connection_handle[1]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot2()));
    connection_handle[2]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot3()));
}

void Example::connect132()
{
    connection_handle[0]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot1()));
    connection_handle[1]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot3()));
    connection_handle[2]=connect(this,SIGNAL(signal_emited()),this,SLOT(slot2()));
}

void Example::break_connection()
{
    for(int i=0;i<3;i++)
        disconnect(connection_handle[i]);
}
