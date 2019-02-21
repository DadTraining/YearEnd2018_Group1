#include "Arrow.h"
#include "cocos2d.h"
#include "Defines.h"
#include <Math.h>

Arrow::Arrow(cocos2d::Scene * scene)
{
	mSprite = cocos2d::Sprite::create(IMG_Weapons);
	scene->addChild(mSprite);
	mSpeed = 20;
	init();
}

Arrow::~Arrow()
{
}

void Arrow::init()
{

}

void Arrow::fly(cocos2d::Vec2 pos)
{
	 a = (pos.y - getPos().y)  / (pos.x - getPos().x);
	 b = pos.y - (a * pos.x);	

	 //set the rotatuion for the arrow
	 cocos2d::Vec2 delta = pos - getPos();
	 mSprite->setRotation(atan2(delta.x, delta.y) * 180 / M_PI - 90);
}

void Arrow::update()
{

	float y = getPos().y -mSpeed;
	float x = (y - b) / a ;
	setPos(cocos2d::Vec2(x,y));
}

void Arrow::setVisible(boolean visible)
{
	mSprite->setVisible(visible);
}

boolean Arrow::isVisible()
{
	return mSprite->isVisible();
}

void Arrow::setMShoot(boolean shoot)
{
	mShoot = shoot;
}

void Arrow::setSpeed(int)
{
	mSpeed = mSpeed;
}

int Arrow::getSpeed()
{
	return mSpeed;
}
