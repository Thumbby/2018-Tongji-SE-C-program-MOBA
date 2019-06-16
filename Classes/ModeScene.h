#ifndef __ModeScene_H__
#define __ModeScene_H__
#include"cocos2d.h"
using namespace cocos2d;
class ModeScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ModeScene);
	void menuMultiplayer5(cocos2d::Ref* pSender);
	void menuSingle1(cocos2d::Ref* pSender);
	void menuSingle2(cocos2d::Ref* pSender);
};
#endif
