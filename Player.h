//
//  Player.h
//  MyGame
//
//  Created by rinov
//
//

#ifndef __MyGame__Player__
#define __MyGame__Player__

#include "cocos2d.h"

class Player: public cocos2d::Layer
{
public:
    
    //create関数を生成するマクロ
    CREATE_FUNC(Player);
    
    //物理シーンを生成
    static cocos2d::Scene* createPhysicsScene();
    
    //初期化
    virtual bool init();
};


#endif /* defined(__MyGame__Player__) */
