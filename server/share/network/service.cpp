#ifdef __linux__
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif //__linux__

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include "service.h"
#include "networkmanager.h"
#include "protocol/protocol.pb.h"

// ListenService::ListenService(IpAddr ipAddr)
//     : _ip(ipAddr.ip)
//     , _port(ipAddr.port)
// {
// }

// ListenService::~ListenService()
// {
//     //
// }

// bool ListenService::Init()
// {
//     LOG_DEBUG("ListenService::Init at ip:%s port:%d", _ip.c_str(), _port);

// #ifdef __linux__
//     uint32 listenSocketfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (listenSocketfd < 0)
//     {
//         return false;
//     }

//     int flags = fcntl(listenSocketfd, F_GETFL, 0);
//     fcntl(listenSocketfd, F_SETFL, flags | O_NONBLOCK);

//     struct sockaddr_in sockaddr;
//     memset(&sockaddr, 0, sizeof(sockaddr));
//     sockaddr.sin_family = AF_INET;
//     sockaddr.sin_addr.s_addr = INADDR_ANY;//inet_addr(_ip.c_str());
//     sockaddr.sin_port = htons(_port);

//     int32 res = bind(listenSocketfd, (struct sockaddr *)&sockaddr, sizeof(struct sockaddr));
//     if (res < 0)
//     {
//         LOG_ERROR("ListenService::Start bind error");
//         return false;
//     }

//     res = listen(listenSocketfd, 512);
//     if (res < 0)
//     {
//         LOG_ERROR("ListenService::Start listen error");
//         return false;
//     }
// #endif //__linux__

//     //ADDEVENT
//     CtrlEvent event;
//     event.type = CtrlEventType_AddListen;
//     event.eventInfo.addListenEvent.socketfd = listenSocketfd;
//     //event.socketfd = listenSocketfd;
//     NetworkManager::getInstance().PushEvent(event);

//     return true;
// }

// /*
// void ListenService::Stop()
// {
// #ifdef __linux__
//     close(_listenSocketfd);
//     for(auto it:_socketfdVec)
//     {
//         close(it);
//     }

//     _isRun =false;
// #endif //__linux__
// }
// */

// /*
// void ListenService::SendMsg(char* msg)
// {
//     if (!IsRun())
//     {
//         return;
//     }
    
//     //send(_socketfd, msg, sizeof(*msg), 0);
// }
// */

// bool ListenService::IsRun()
// {
//     return _isRun;
// }

