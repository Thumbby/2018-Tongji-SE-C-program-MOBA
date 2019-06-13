/*
	�ļ�����    SocketManager.h
	�衡����  
	�����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

	�������ڣ�  2014.6.26
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

    void start();   /* ��ʼ���ӷ����� */
    void sendMsg(const char* msg);  /* �������ݵ������� */
private:
	static SocketManager* m_SocketManager;

    ODSocket cSocket;

    bool connectServer();   /* ���ӷ����� */
    void recvData();        /* �������� */
};

#endif