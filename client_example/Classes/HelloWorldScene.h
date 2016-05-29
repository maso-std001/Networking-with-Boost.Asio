#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Server.hpp"

class HelloWorld : public cocos2d::Layer
{
    
public:
    
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    virtual void update(float dt) override;
    
    CREATE_FUNC(HelloWorld);
    
private:
    
    Server _server;
    
    cocos2d::Node* _players;
    
};

#endif // __HELLOWORLD_SCENE_H__
