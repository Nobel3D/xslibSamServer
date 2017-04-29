#ifndef RCON_H
#define RCON_H
#include <QCoreApplication>
#include <QTcpSocket>
#include <QMessageLogger>
#include <xslib/xslog.h>

#define SEC_TIMEOUT 5000
#define LOG(mesg){ xsLog::addLog("sm.log", mesg); }
class Rcon
{
private:
    QString strAddress;
    int iPort;
    QString strStatus;
    bool bConnected;
    QTcpSocket socket;
public:
    Rcon();
    Rcon(QString _address, int _port);
    int Connect();
    int Login(const QString &passwd);

    QString ReadStream();
    int WriteStream(const QString &send);
    void Close();

    QString getAddress();
    QString getPort();
    QString getStatus();

    bool isOnline();
};

#endif // RCON_H
