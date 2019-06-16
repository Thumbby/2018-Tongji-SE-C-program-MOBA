#pragma once
#ifndef TimeCounter_H_
#define TimeCounter_H_
#include"cocos2d.h"
USING_NS_CC;
class TimeCounter :public Node

{
public:
	CREATE_FUNC(TimeCounter);
	virtual bool init();
	virtual void update(float dt);
	void start();
	float getfCurTime();
private:
	float m_mftime;
};
#endif // !TimeCounter_H_

