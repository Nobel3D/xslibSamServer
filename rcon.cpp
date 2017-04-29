#include "rcon.h"
#include <xslib/xsconsole.h>
#include <QtNetwork>

Rcon::Rcon()
{
}

Rcon::Rcon(QString _address, int _port)
{
    strAddress = _address;
    iPort = _port;
}

int Rcon::Connect()
{
    if (!bConnected)  //Disconnected
    {
        socket.connectToHost(strAddress, iPort);

        if (!socket.waitForConnected(SEC_TIMEOUT))
        {
            strStatus = "Impossible reach host!";
            return FAIL;
        }
        LOG("[NET] Connected to server!");
        bConnected = true; //Connected
        return OK;
    }
    strStatus = "Already connected!";
    return FAIL;
}

int Rcon::Login(const QString &passwd)
{
    QString data;
    do
    {
        data = ReadStream();
    }while(data != "login: \r" && data != "");
    ReadStream();
    ReadStream();
    ReadStream();
    WriteStream(passwd); //gli invio la password
    ReadStream();
    data = ReadStream();//ottengo il risultato della connessione:
    if (data == "login: \r")// se mi richiede il login: vuol dire che è sbagliata la password
    {
        strStatus = "Wrong Password!";
        return FAIL;
    }
    return OK;
}

QString Rcon::ReadStream()
{
    char buffer;
    QString strout;
    socket.waitForReadyRead(100);
    while(socket.bytesAvailable() != 0 && buffer != '\r')
    {
    socket.read(&buffer, 1);
    if (buffer >= 0 && buffer <= 127)
        strout.append(buffer);
    }
    return strout;
}

int Rcon::WriteStream(const QString &send)
{
    QString cpy = send;
    cpy.append("\r");
    socket.write( cpy.toUtf8() );
    socket.waitForBytesWritten();
    return OK;
}

void Rcon::Close()
{
     LOG("[NET] Closing socket!");
    socket.close();
}

bool Rcon::isOnline()
{
    return bConnected;
}

QString Rcon::getAddress() { return strAddress; }
QString Rcon::getPort() { return QString::number(iPort); }
QString Rcon::getStatus() { return strStatus; }
