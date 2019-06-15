#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual  void update(float dt);
    CREATE_FUNC(HelloWorld);
	Point pos;
};

#endif // __HELLOWORLD_SCENE_H__
