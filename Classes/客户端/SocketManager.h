/*
	文件名：    SocketManager.h
	描　述：  
	创建人：    笨木头_钟迪龙 (博客：http://www.benmutou.com)

	创建日期：  2014.6.26
*/
#ifndef SocketManager_H
#define SocketManager_H

#include "cocos2d.h"
#include "ODSocket\ODSocket.h"
USING_NS_CC;

#define MAX_LEN 512
class SocketManager : public Ref 
{
public:
	SocketManager();
	~SocketManager();
	static SocketManager* getInstance();
	CREATE_FUNC(SocketManager);
	virtual bool init();

    void start();   /* 开始连接服务器 */
    void sendMsg(const char* msg);  /* 发送数据到服务器 */
private:
	static SocketManager* m_SocketManager;

    ODSocket cSocket;

    bool connectServer();   /* 连接服务器 */
    void recvData();        /* 接收数据 */
};

#endif