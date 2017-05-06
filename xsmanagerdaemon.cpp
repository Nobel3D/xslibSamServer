#include "xsmanagerdaemon.h"

xsManagerDaemon::xsManagerDaemon()
{

}

int xsManagerDaemon::startServer(const QString &crt, const QString &key)
{
    server = new xsServerSsl(crt,key);
    server->Start(QHostAddress::Any, MANAGER_PORT);
    server->waitConnection();
    return OK;
}

int xsManagerDaemon::login(QString &hit, int port)
{
    if(pw->Check(hit) == FAIL)
    {
        strStatus = "Login failed!";
        return FAIL;
    }

    sam = new Rcon("127.0.0.1", port);

    if(sam->Connect() == FAIL)
    {
        strStatus = sam->getStatus();
        return FAIL;
    }

    return sam->Login(hit);

}

QString xsManagerDaemon::format(const QString &str)
{
    QString offset = str;
    return offset.replace("\r", "").replace("\n", "");
}

int xsManagerDaemon::createConfiguration(QString &passwd, const QString &filepw)
{
    pw = new xsPassword(passwd);
    pw->Save(filepw);
}

void xsManagerDaemon::run()
{
    QString buffer;
     while(sam->isOnline())
     {
          buffer = sam->ReadStream();
          if(!buffer.startsWith('>') && buffer != "")
              server->Write(buffer.toUtf8());
    }
}
