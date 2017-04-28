#ifndef FETCH_H
#define FETCH_H

#include <QThread>
#include "rcon.h"
#include <QThread>

class Fetch : public QThread
{
private:
    Rcon* cStream; //current stream
public:
    Fetch(Rcon *stream);
    int flag;
    QString strData;
    void run();
};

#endif // FETCH_H
