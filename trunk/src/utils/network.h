#ifndef NETWORK_H
#define NETWORK_H

#include "datatypes.h"
#include <boost/network/include/http/client.hpp>

std::string urlencode(const std::string &c);
std::string char2hex( char dec );

namespace net = boost::network;

typedef net::http::basic_client<net::http::tags::http_async_8bit_udp_resolve, 1, 1> AsyncClient;

#endif // NETWORK_H_INCLUDED
