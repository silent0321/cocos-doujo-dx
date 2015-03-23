//
//  Player.cpp
//  MyGame
//
//  Created by rinov
//

#include "Player.h"

USING_NS_CC;

Scene* Player::createPhysicsScene()
{
    //物理演算のできるシーンを生成
    auto scene=Scene::createWithPhysics();
    
    //物理法則の設定を取得
    auto world=scene->getPhysicsWorld();
    
    //重力設定
    world->setGravity(Vec2(0,-10));
    
    //速度設定
    world->setSpeed(10.0f);
    
    //レイヤー生成
    auto layer=Player::create();
    
    //物理シーンにレイヤー貼り付け
    scene->addChild(layer);
    
    //物理オブジェクトの当たり判定などを可視化できる設定
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    return scene;
}

bool Player::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    //画面サイズの取得
    auto size=Director::getInstance()->getWinSize();
    
    //まずは画像を読み込む
    auto player=Sprite::create("player.png");
    
    //位置を設定
    player->setPosition(Vec2(size.width/2,size.height/2));
    
    //接触判定を円で生成 (半径:画像サイズの半分)
    auto body=PhysicsBody::createCircle(player->getContentSize().width/2);

    //重力の影響を受けるか(trueだと下へ落ちていってしまう)
    body->setDynamic(true);
    
    //回転運動が可能か
    body->setRotationEnable(true);
    
    //自分の所属カテゴリーを設定
    //body->setCategoryBitmask(static_cast<int>(1<<0));
    
    //当たり判定を行う相手のカテゴリーを設定
    //body->setCollisionBitmask(static_cast<int>(1<<1));
    
    //接触判定を全てのものを行う(デバッグモードなら当たり判定なし)
    //body->setContactTestBitmask(INT_MAX);
    
    //物理法則を画像に適用させる
    player->setPhysicsBody(body);

    //貼り付け
    this->addChild(player);
    
    //床
    auto wall = Sprite::create();
    wall->setPosition(Vec2(size.width/2,0));
    wall->setTextureRect(Rect(0,0,size.width,size.height/8));
    wall->setColor(Color3B::BLACK);
    wall->setRotation(3.0f);//3度の傾斜

    //反発係数と摩擦係数の設定
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    material.restitution = 0.0f;
    material.friction = 2.0f;
    
    //物理法則の設定
    auto pWall = PhysicsBody::createBox(wall->getContentSize(), material);
    pWall->setDynamic(false);//重力を受けない
    pWall->setRotationEnable(false);//回転運動不可
    wall->setPhysicsBody(pWall);

    //貼り付け
    this->addChild(wall);


    return true;
}