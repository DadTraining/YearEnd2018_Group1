#include "Fire.h"
#include "cocos2d.h"
#include "Defines.h"
#include <Math.h>


Fire::Fire(cocos2d::Scene * scene)
{
	mSprite = cocos2d::Sprite::create(IMG_FIRE);
	scene->addChild(mSprite);
	mSpeed = 10;
	init();
}


Fire::~Fire()
{
}

void Fire::init()
{
}

void Fire::fly(cocos2d::Vec2 pos)
{
	a = (pos.y - getPos().y) / (pos.x - getPos().x);
	b = pos.y - (a * pos.x);
}

void Fire::update()
{
	float y = getPos().y - mSpeed;
	float x = (y - b) / a;
	setPos(cocos2d::Vec2(x, y));
	mSprite->setRotation(mSprite->getRotation() + 80);
}

void Fire::setVisible(bool visible)
{
	mSprite->setVisible(visible);
}

bool Fire::isVisible()
{
	return mSprite->isVisible();
}

void Fire::setMShoot(bool shoot)
{
	mShoot = shoot;
}

void Fire::setSpeed(int)
{
	mSpeed = mSpeed;
}

int Fire::getSpeed()
{
	return mSpeed;
}