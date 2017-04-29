#ifndef XSSAMSERVER_H
#define XSSAMSERVER_H

#include "xslibsamserver_global.h"
#include "rcon.h"
#include "fetch.h"

#define CERROR(check, text) { if(check) { qWarning() << "[ERR] " << text << endl; \
                                          return -1; }                      }

#define endl "\n"

class XSLIBSAMSERVERSHARED_EXPORT xsSamServer
{

public:
    xsSamServer(const QString &address, int port);

    int Connect();
    int Login(const QString &passwd);
    void Start();

    Rcon* server;
    Fetch* input;

    QString strBuffer;
    QString strStatus;

    int iHit;
    const int iMaxHit = 6;
};

#endif // XSSAMSERVER_H
