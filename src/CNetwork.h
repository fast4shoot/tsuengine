#ifndef CNETWORK_H
#define CNETWORK_H

#include "utils/network.h"

class CNetwork{
  public:
    AsyncClient client;
    AsyncClient::response response;
};

#endif // CNETWORK_H
