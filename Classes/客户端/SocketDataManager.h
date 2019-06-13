/*
	�ļ�����    SocketDataManager.h
	�衡����  
	�����ˣ�    ��ľͷ_�ӵ��� (���ͣ�http://www.benmutou.com)

	�������ڣ�  2014.6.26
*/
#ifndef SocketDataManager_H
#define SocketDataManager_H

#include "cocos2d.h"
USING_NS_CC;

class SocketDataManager : public Ref 
{
public:
	SocketDataManager();
	~SocketDataManager();
	static SocketDataManager* getInstance();
	CREATE_FUNC(SocketDataManager);
	virtual bool init();

    virtual void update(float dt);

    void pushMsg(const char* msg);  /* ���һ�����ݵ������� */
private:
	static SocketDataManager* m_SocketDataManager;

    std::mutex m_mutex;;
    ValueVector m_msgList; /* ������н��յ������� */
};

#endif