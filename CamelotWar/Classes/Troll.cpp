#include "Troll.h"
#include "Defines.h"


Troll::Troll()
{
	
}

Troll::~Troll()
{

}

Troll::Troll(cocos2d::Scene * scene) : Character::Character(scene)
{
	mSprite = cocos2d::Sprite::create(NAME_SPRITE_TROLL);
	scene->addChild(mSprite);

	init();
}

void Troll::trollWalk()
{
	setPos(mSprite->getPosition() + cocos2d::Vec2(mSpeed/10, 0));
	setPosHp(cocos2d::Vec2(getPos().x, getPos().y + mSprite->getContentSize().height / 2));
}
void Troll::trollATK()
{
	if (changeStatus == 0)
	{
		mSprite->stopAllActions();
		setAnimation(NAME_PLIST_TROLL_ATK, NAME_PNG_TROLL_ATK, COUNT_IMG_TROLL_ATK, mSpeed, 0);
		changeStatus++;
	}
	mloadingHpBar->setPercent(mloadingHpBar->getPercent() - 1);
}

void Troll::trollDie()
{
	mAlive = 0 ;
	if (changeStatus == 0)
	{
		mSprite->stopAllActions();
		setAnimation(NAME_PLIST_TROLL_DIE, NAME_PNG_TROLL_DIE, COUNT_IMG_TROLL_DIE, mSpeed, 1);
		changeStatus+= 2;
	}
	if (changeStatus == 1)
	{
		mSprite->stopAllActions();
		setAnimation(NAME_PLIST_TROLL_DIE, NAME_PNG_TROLL_DIE, COUNT_IMG_TROLL_DIE, mSpeed, 1);
		changeStatus += 1;
	}
	setPos(getPos() - cocos2d::Vec2(0, 1));
	setPosHp(cocos2d::Vec2(getPos().x, getPos().y + mSprite->getContentSize().height / 2));

}

void Troll::update()
{
	if (getPos().x >= SCREEN_W/2 && mAlive == 1)
	{
		trollATK();
	}
	if (getPos().x < SCREEN_W / 2 && mAlive == 1)
	{
		trollWalk();
	}
	if (mloadingHpBar->getPercent() == 0 )
	{
		trollDie();
	}
	//mloadingHpBar->setPercent(mloadingHpBar->getPercent() - 0.5);
}

void Troll::init()
{
	changeStatus = 0;
	mSpeed = 10;
	mAlive = 1;
	setPos(cocos2d::Vec2(MONSTER_APPEAR, SCREEN_H / 3));
	setPosHp(cocos2d::Vec2(getPos().x, getPos().y + mSprite->getContentSize().height / 2));
	setAnimation(NAME_PLIST_TROLL_WALK, NAME_PNG_TROLL_WALK, COUNT_IMG_TROLL_WALK,mSpeed,0);

}
