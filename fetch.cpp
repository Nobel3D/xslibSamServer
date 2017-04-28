#include "fetch.h"

Fetch::Fetch(Rcon* stream)
{
    //QMessageLogger("")
    cStream = stream;
}

void Fetch::run()
{
    while(cStream->isOnline())
    {
         strData = cStream->ReadStream();
         if(!strData.startsWith('>') && strData != "")
             flag = 1;
    }
}
