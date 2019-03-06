#include "Model.h"
#include "Character.h"
#include "Defines.h"

Character::Character()
{

}

Character::~Character()
{

}

Character::Character(cocos2d::Scene * scene)
{
	for (int i = 0; i < 3; i++)
	{
		auto coin = new CoinModel(scene);
		coins.push_back(coin);
	}

	init();
	scene->addChild(mRangeLeft);
	scene->addChild(mRangeRight);
	scene->addChild(mHpBar);
	scene->addChild(mloadingHpBar);
	scene->addChild(mStarOfHero,9999);
}

void Character::deCreaseHP(int hp)
{
	float percentHpDecrease =( (float) hp / (float)mHP) * 100;
	mloadingHpBar->setPercent(mloadingHpBar->getPercent() - percentHpDecrease);
}

void Character::reBorn()
{
	auto FadeOut = cocos2d::FadeOut::create(0.2);
	auto FadeIn = cocos2d::FadeIn::create(0.2);
	auto sequence = cocos2d::Sequence::create(FadeOut, FadeIn,FadeOut->clone(),FadeIn->clone(),nullptr);
	mSprite->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	setPos(cocos2d::Vec2(getPos().x, SCREEN_H / 3 - mSprite->getContentSize().height));
	mloadingHpBar->setPercent(100);
	mAlive = 1;
	/*mDamage = mDamage * 2 ;
	mHP = mHP + 100;
	mSpeed = mSpeed * 2 ;*/
	mSprite->runAction(sequence);
	if (mPhysicsBody != nullptr)
	{
		mPhysicsBody->setDynamic(false);
	}
}

void Character::setPosAll(cocos2d::Vec2 pos)
{
	setPos(pos);
	setPosHp(cocos2d::Vec2(pos.x, pos.y + mSprite->getContentSize().height + 10));
}

void Character::setPosRange()
{
	mRangeLeft->setPosition(cocos2d::Vec2(getPos().x - mRange,SCREEN_H /3 - 85));
	mRangeRight->setPosition(cocos2d::Vec2(getPos().x + mRange, SCREEN_H / 3 - 85));
}

void Character::levleUp()
{
	lvOfHero += 1;
	switch (lvOfHero)
	{
	case 0:
	{
		break;
	}
	case 1:
	{
		priceToUpLv += 50;
		mDamage = mDamage + 10;
		mSpeed = mSpeed + 1;
		mRange = mRange + 20;
		mStarOfHero->setTexture("Star/1star.png");
		break;
	}
	case 2:
	{
		priceToUpLv += 100;
		mDamage = mDamage +10;
		mSpeed = mSpeed + 2;
		mRange = mRange + 30;
		mStarOfHero->setTexture("Star/2star.png");
		break;
	}
	case 3:
	{
		mDamage = mDamage + 20;
		mSpeed = mSpeed + 2;
		mRange = mRange + 20;
		mStarOfHero->setTexture("Star/3star.png");
		break;
	}
	default:
		break;
	}

	//mStarOfHero->setPosition(cocos2d::Vec2(200,300));
	mStarOfHero->setPosition(cocos2d::Vec2(getPos().x, getPos().y + mSprite->getContentSize().height + 10));
}

void Character::setLevle(int lv)
{
	lvOfHero = lv;
}

int Character::getpriceToUpLv()
{
	return priceToUpLv;
}

void Character::setStarOfHero()
{
}

void Character::init()
{
	mHpBar = cocos2d::Sprite::create("loading_bg.png");

	mloadingHpBar = cocos2d::ui::LoadingBar::create("loadingbar.png");
	mloadingHpBar->setDirection(cocos2d::ui::LoadingBar::Direction::LEFT);
	mloadingHpBar->setPercent(100);

	setVisibleHP(false);
	//coin
	for (int i = 0; i < 3; i++)
	{
		setVisibleCoin(false,i);
	}
	mAppear = false;
	mCheckAtk = false;
	checkBuff = false;
	checkFallDone = false;
	lvOfHero = 0;

	//range hero
	mRangeLeft = cocos2d::Sprite::create("range.png");
	mRangeRight = cocos2d::Sprite::create("range.png");
	mRangeLeft->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	mRangeRight->setAnchorPoint(cocos2d::Vec2(0.5, 0));
	setvisibleRange(false);

	//star of hero
	mStarOfHero = cocos2d::Sprite::create();
}

std::vector<CoinModel*> Character::getCoin()
{
	return coins;
}

int Character::getPrice()
{
	return mPrice;
}

int Character::getLvOfHero()
{
	return lvOfHero;
}

void Character::setVisibleCoin(bool visible , int i)
{
	coins[i]->getSprite()->setVisible(visible);
}

void Character::setVisibleHP(bool visible)
{
	mHpBar->setVisible(visible);
	mloadingHpBar->setVisible(visible);
}

void Character::setAlive(int alive)
{
	mAlive = alive;
}

int Character::getAlive()
{
	return mAlive;
}

void Character::setCastle(Castle * castle)
{
	mCastle = castle;
}

void Character::setAppear(bool appear)
{
	mAppear = appear;
}

bool Character::getCheckFallDone()
{
	return checkFallDone;
}

void Character::setCheckFallDone(bool check)
{
	checkFallDone = check;
}

bool Character::getAppear()
{
	return mAppear;
}

cocos2d::Rect Character::getBoudingBoxCoin(int i)
{
	return coins[i]->getSprite()->getBoundingBox();
}

void Character::setcheckAppear(bool appear)
{
	checkAppear = appear;
	
}

bool Character::getcheckAppear()
{
	return checkAppear;
}

void Character::setCheckATK(bool checkATK)
{
	mCheckAtk = checkATK;
}

bool Character::getCheckATK()
{
	return  mCheckAtk;
}

void Character::setPosHp(cocos2d::Vec2 pos)
{
	mHpBar->setPosition(pos);
	mloadingHpBar->setPosition(pos);
}

void Character::addPhysicsBody()
{
	// Initialize physics body
	mPhysicsBody = cocos2d::PhysicsBody::createBox(mSprite->getContentSize(), cocos2d::PhysicsMaterial(0.1f, 1.0f, 0.0f));
	mPhysicsBody->setDynamic(false);
	mPhysicsBody->setCategoryBitmask(false);
	mSprite->addComponent(mPhysicsBody);
}

void Character::setvisibleRange(bool visible)
{
	mRangeLeft->setVisible(visible);
	mRangeRight->setVisible(visible);
}
