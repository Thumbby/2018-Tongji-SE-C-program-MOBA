#include "SocketManager.h"
#include "SocketDataManager.h"

SocketManager* SocketManager::m_SocketManager = NULL;

SocketManager::SocketManager()
{
}

SocketManager::~SocketManager()
{
}

SocketManager* SocketManager::getInstance()
{
    if (m_SocketManager == NULL)
    {
        m_SocketManager = SocketManager::create();
        m_SocketManager->retain();
    }

    return m_SocketManager;
}

bool SocketManager::init()
{

    return true;
}

void SocketManager::start()
{
    if (connectServer() == true)
    {
        /* 开启新线程，接收数据 */
        std::thread recvThread = std::thread(&SocketManager::recvData, this);
        recvThread.detach();
    }
}

bool SocketManager::connectServer(){
    cSocket.Init();
    cSocket.Create(AF_INET, SOCK_STREAM, 0);

    //const char* ip = "115.28.47.161";
    const char* ip = "127.0.0.1";
    int port = 8888;
    bool result = cSocket.Connect(ip, port);

    int retryTimes = 0;
    while (result == false && retryTimes < 7) {
        CCLOG("retry connecting...");

        result = cSocket.Connect(ip, port);
        retryTimes++;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        Sleep(500);
#else
        usleep(500);
#endif

    }
    if (result) {
        log("connect to server suc!");
    }
    else {
        log("can not connect to server");
    }

    return result;
}

void SocketManager::recvData()
{
    while (true) {
        /* 接收内容（实际中这部分逻辑可没那么简单，这里仅作为示例使用） */
        char recvBuf[MAX_LEN] = "";
        int iResult = cSocket.Recv(recvBuf, MAX_LEN, 0);
        if (iResult <= 0) {
            break;
        }

        /* 把消息存放到缓存中，等待处理 */
        SocketDataManager::getInstance()->pushMsg(recvBuf);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        Sleep(20);
#else
        usleep(20);
#endif

    }
}

void SocketManager::sendMsg(const char* msg)
{
    cSocket.Send(msg, sizeof(msg));
}
