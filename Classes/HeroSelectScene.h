#include"cocos2d.h"
using namespace cocos2d;
class HeroSelectScene :public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HeroSelectScene);
	void warrierSelect(cocos2d::Ref* pSender);
	void mageSelect(cocos2d::Ref* pSender);
	void archerSelect(cocos2d::Ref* pSender);
};



