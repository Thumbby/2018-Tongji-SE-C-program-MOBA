#ifndef __SecondScene_H__
#define __SecondScene_H__
#include"cocos2d.h"
using namespace cocos2d;
class SecondScene:public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SecondScene);
	void menuModeChoice(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);
};
#endif
