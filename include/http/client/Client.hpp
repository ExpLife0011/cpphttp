#pragma once
#include "SocketFactory.hpp"
#include "ClientConnection.hpp"
#include "../Request.hpp"
#include "../Response.hpp"
#include "../Headers.hpp"

namespace http
{
    /**@brief Simple HTTP client that manages the socket, parser, etc. components.*/
    class Client
    {
    public:
        Client(const std::string &host, uint16_t port, bool tls);
        ~Client();

        /**Get the default headers object. Any headers added will be included in any request,
         * if that request does not already have a header by that name.
         * 
         * This can be useful for adding headers such as User-Agent.
         * 
         * Note that Host, Date, Content-Length and Transfer-Encoding are always set by the
         * request as needed.
         */
        Headers& def_headers() { return _def_headers; }

        /**Set the socket factory for creating connections.
         * Does not take ownership.
         */
        void socket_factory(SocketFactory *factory) { _factory = factory; }

        /**Make a HTTP request.
         * Additional headers may be added to the request.
         */
        Response make_request(Request &request);
    private:
        Headers _def_headers;
        SocketFactory *_factory;
        ClientConnection conn;
        const std::string &host;
        uint16_t port;
        bool tls;
    };
}
