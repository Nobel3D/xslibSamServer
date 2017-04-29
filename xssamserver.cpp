#include "xssamserver.h"


xsSamServer::xsSamServer(const QString &address, int port)
{
    server = new Rcon(address, port);
}

int xsSamServer::Connect()
{
    if(server->Connect() == FAIL)
    {
        strStatus = server->getStatus();
        return FAIL;
    }
    return OK;
}
int xsSamServer::Login(const QString &passwd)
{
    if(iHit > iMaxHit)
        return FAIL;
    iHit++;
    return server->Login(passwd);
}

void xsSamServer::Start()
{
    input = new Fetch(server);
    input->start();
}
