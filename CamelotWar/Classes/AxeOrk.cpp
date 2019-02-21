#include "AxeOrk.h"
#include "Defines.h"


AxeOrk::AxeOrk()
{
}


AxeOrk::~AxeOrk()
{
}

AxeOrk::AxeOrk(cocos2d::Scene * scene) : Character::Character(scene)
{
	mSprite = cocos2d::Sprite::create(NAME_SPRITE_AXEORK);
	scene->addChild(mSprite);

	init();
}

void AxeOrk::walk()
{
	setPos(mSprite->getPosition() + cocos2d::Vec2(mSpeed / 10, 0));
	setPosHp(cocos2d::Vec2(getPos().x, getPos().y + mSprite->getContentSize().height / 2));
}

void AxeOrk::attack()
{
	countFrame = countFrame + 1;
	if (changeStatus == 0)
	{
		mSprite->stopAllActions();
		setAnimation(NAME_PLIST_AXEORK_ATK, NAME_PNG_AXEORK_ATK, COUNT_IMG_AXEORK_ATK, mSpeed, 0);
		changeStatus++;
	}
	int a = (COUNT_IMG_AXEORK_ATK * FPS) / mSpeed;
	if (countFrame % a == 0)
	{
		deCreaseHP(100);
	}
}

void AxeOrk::die()
{
	mAlive = 0;
	if (changeStatus == 0)
	{
		mSprite->stopAllActions();
		setAnimation(NAME_PLIST_AXEORK_DIE, NAME_PNG_AXEORK_DIE, COUNT_IMG_AXEORK_DIE, mSpeed, 1);
		changeStatus += 2;
	}
	if (changeStatus == 1)
	{
		mSprite->stopAllActions();
		setAnimation(NAME_PLIST_AXEORK_DIE, NAME_PNG_AXEORK_DIE, COUNT_IMG_AXEORK_DIE, mSpeed, 1);
		changeStatus += 1;
	}
	setPos(getPos() - cocos2d::Vec2(0, 1));
	setPosHp(cocos2d::Vec2(getPos().x, getPos().y + mSprite->getContentSize().height / 2));
}

void AxeOrk::update()
{
	if (getPos().x >= SCREEN_W / 2 && mAlive == 1)
	{
		attack();
	}
	if (getPos().x < SCREEN_W / 2 && mAlive == 1)
	{
		walk();
	}
	if (mloadingHpBar->getPercent() == 0)
	{
		die();
	}
}

void AxeOrk::init()
{
	changeStatus = 0;
	mSpeed = 15;
	mAlive = 1;
	mHP = 1000;
	mPrice = 100;
	mDamage = 100;
	mRange = 10;
	setPos(cocos2d::Vec2(MONSTER_APPEAR, SCREEN_H / 2 + 225));
	setPosHp(cocos2d::Vec2(getPos().x, getPos().y + mSprite->getContentSize().height / 2));
	setAnimation(NAME_PLIST_AXEORK_WALK, NAME_PNG_AXEORK_WALK, COUNT_IMG_AXEORK_WALK, mSpeed, 0);
}