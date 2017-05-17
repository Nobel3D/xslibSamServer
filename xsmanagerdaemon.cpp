#include "xsmanagerdaemon.h"

xsManagerDaemon::xsManagerDaemon()
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
        data = sam->Read();
    }
    while(data != "login: \r" && data != "");
    sam->Read();
    sam->Read();
    sam->Read();
    sam->Write(hit.append('\r')); //gli invio la password
    sam->Read();
    data = sam->Read();//ottengo il risultato della connessione:
    if (data == "login: \r")// se mi richiede il login: vuol dire che è sbagliata la password
        return FAIL;
    else
        return OK;

}

QString xsManagerDaemon::serverRead()
{
    return server->Read().replace("\r", "").replace("\n", "");
}

int xsManagerDaemon::serverWrite(const QString &str)
{
    server->Write(str.toUtf8());
    return OK;
}

QString xsManagerDaemon::format(const QString &str)
{
    QString offset = str;
    return offset;
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
          buffer = sam->Read();
          if(!buffer.startsWith('>') && buffer != "")
              server->Write(buffer.toUtf8());
    }
}
