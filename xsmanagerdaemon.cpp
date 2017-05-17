#include "xsmanagerdaemon.h"

xsManagerDaemon::xsManagerDaemon(QObject *parent)
{
    sam = new xsClient;
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
    if(!pw->Check(hit))
    {
        strStatus = "Login failed!";
        return FAIL;
    }

    if(!sam->Connect("127.0.0.1", port))
        return FAIL;

    QString data;
    do
    {
        data = samRead();
    }
    while(data != "login: " && data != "");

    samRead();
    samRead();
    samWrite(hit); //gli invio la password
    samRead();
    data = samRead();//ottengo il risultato della connessione:
    if (data == "login: ")// se mi richiede il login: vuol dire che è sbagliata la password
        return FAIL;
    else
        return OK;

}

QString xsManagerDaemon::serverRead()
{
    QString offset;
    do {
        offset = server->Read(STREAM_SYNC).replace("\r", "").replace("\n", "");
    } while(offset.isEmpty());

    return offset;
}

int xsManagerDaemon::serverWrite(const QString &str)
{
    server->Write(str.toUtf8(), STREAM_SYNC);
    return OK;
}

QString xsManagerDaemon::samRead()
{
    QString offset;
    do {
        offset = sam->Read(STREAM_SYNC).replace("\r", "");
    } while(offset.isEmpty() || offset.startsWith('>'));

    return offset;
}

int xsManagerDaemon::samWrite(QString str)
{
    sam->Write(str.append('\r').toUtf8());
    return OK;
}

int xsManagerDaemon::createConfiguration(QString passwd, const QString &filepw)
{
    pw = new xsPassword(passwd);
    pw->Save(filepw);
}

void xsManagerDaemon::run()
{
    QString buffer;
     while(sam->isOpen())
     {
          buffer = samRead();
          if(!buffer.startsWith('>') && buffer != "")
              serverWrite(buffer.toUtf8());
    }
}
