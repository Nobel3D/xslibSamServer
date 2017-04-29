#include "fetch.h"

Fetch::Fetch(Rcon* stream)
{
    //QMessageLogger("")
    cStream = stream;
}

void Fetch::run()
{
    QString buffer;
    while(cStream->isOnline())
    {
         buffer = cStream->ReadStream();
         if(!buffer.startsWith('>') && buffer != "\r" && !buffer.isEmpty())
             strData = buffer;
    }
}
