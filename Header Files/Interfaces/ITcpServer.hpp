//
// Created by wmatveev on 18.09.2023.
//

#ifndef WAILYSCORE_ITCP_SERVER
#define WAILYSCORE_ITCP_SERVER


class ITcpServer
{
    public:
        virtual int AcceptNewConnection() = 0;
        virtual int AcceptDataFromClient() = 0;
        virtual int HandleClientDisconnection() = 0;
};

#endif //WAILYSCORE_ITCP_SERVER
