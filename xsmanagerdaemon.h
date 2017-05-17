#ifndef XSMANAGERDAEMON_H
#define XSMANAGERDAEMON_H

#include "xslibsamserver_global.h"
#include <xslib/xslib.h>
#include <QThread>
#include <QDir>

class XSLIBSAMSERVERSHARED_EXPORT xsManagerDaemon : public QThread
{
public:
    xsManagerDaemon();
    int startServer(const QString &crt, const QString &key);
    int login(QString &hit, int port);
    int createConfiguration(QString passwd, const QString &filepw = QDir::homePath() + "/.xsam");
    void run();

    QString serverRead();
    int serverWrite(const QString &str);
    QString format(const QString &str);

    xsServerSsl* server;
    xsPassword* pw;
    xsClient* sam;

    int Connect();
    int Login(const QString &passwd);


    QString strBuffer;
    QString strStatus;

};

#endif // XSMANAGERDAEMON_H
