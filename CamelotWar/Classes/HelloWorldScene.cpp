#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Archer.h"
#include "Troll.h"
#include "HammerTroll.h"
#include "Defines.h"
#include "Archer_knife.h"
#include "Archer_Fire.h"
#include "BoneTroll.h"
#include "HammerOrk.h"
#include "SwordOrk.h"
#include "AxeOrk.h"
#include "SpearKnight.h"
#include "AxeKnight.h"
#include "SwordKnight.h"
#include "Boat.h"
#include "pedestal.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = cocos2d::Sprite::create(BACKGROUND_PLAYSCENE);
	background->setContentSize(visibleSize);
	background->setPosition(cocos2d::Vec2(SCREEN_W / 2, SCREEN_H / 2));
	addChild(background);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	countFrame = 0;

	boat = new Boat(this);
	boat->setListMonster(mListMonsters);

	mCastle = new Castle(this);

	check = 0;

	createMonster();

	createIconHero();

	createPedestal();
	
	scheduleUpdate();

    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	for (int i = 0; i < mListIconHero.size(); i++)
	{
		if (mListIconHero[i]->getBoundingBox().containsPoint(touch->getLocation()))
		{
			switch (i)
			{
				case 0:
				{
					auto archer = new Archer(this);
					archer->setListMonster(mListMonsters);
					archer->setListPedestal(mListPedestal);
					archer->setPosAll(touch->getLocation());
					mListCharacters.push_back(archer);
					check = 1;
					break;
				}
				case 1:
				{
					auto archer_knight = new Archer_knife(this);
					archer_knight->setListMonster(mListMonsters);
					archer_knight->setListPedestal(mListPedestal);
					archer_knight->setPosAll(touch->getLocation());
					mListCharacters.push_back(archer_knight);
					check = 1;
					break;
				}
				case 2:
				{
					auto archer_fire = new Archer_Fire(this);
					archer_fire->setListMonster(mListMonsters);
					archer_fire->setListPedestal(mListPedestal);
					archer_fire->setPosAll(touch->getLocation());
					mListCharacters.push_back(archer_fire);
					check = 1;
					break;
				}
				case 3:
				{
					auto axe_knight = new AxeKnight(this);
					axe_knight->setListMonster(mListMonsters);
					mListCharacters.push_back(axe_knight);
					check = 1;
					return false;
					break;
				}
				case 4:
				{
					auto spear_knight = new SpearKnight(this);
					spear_knight->setListMonster(mListMonsters);
					mListCharacters.push_back(spear_knight);
					check = 1;
					return false;
					break;
				}
				case 5:
				{
					auto sword_Knight = new SwordKnight(this);
					sword_Knight->setListMonster(mListMonsters);
					mListCharacters.push_back(sword_Knight);
					check = 1;
					return false;
					break;
				}
			}
			return true;
		}
	}
	
	
	if (boat->BoatTouchBegan(touch, event))
	{
		check = 2;
		return true;
	}
	else
	{
		if (touchCharacter(touch))
		{
			return true;
		}
		else
		{

		return false;
		}
	}
}

void HelloWorld::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
{
	if (check == 1)
	{
		mListCharacters[mListCharacters.size() - 1]->setPos(touch->getLocation());
		//mListCharacters[mListCharacters.size() - 1]->setpos();
	}
	if (check == 2)
	{
		boat->BoatTouchMoved(touch, event);
	}
}

void HelloWorld::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
{
	if (check == 1)
	{
		mListCharacters[mListCharacters.size() - 1]->setAlive(1);
		//mListCharacters[mListCharacters.size() - 1]->setPosRange();
		mListCharacters[mListCharacters.size() - 1]->setAppear(false);
	}
	if(check > 2)
	{ 
		mListMonsters[check -3]->setVisibleHP(false);
	}
}

bool HelloWorld::touchCharacter(cocos2d::Touch * touch)
{
	for (int  i = 0; i < mListMonsters.size(); i++)
	{
		if (mListMonsters[i]->getSprite()->getBoundingBox().containsPoint(touch->getLocation()))
		{
			mListMonsters[i]->setVisibleHP(true);
			check = i + 3;
			return true;
			break;
		}
	}
	if (check >= 3)
	{
		return false;
	}
}

void HelloWorld::createIconHero()
{
	for (int i = 0; i < 6; i++)
	{
		char str[100];
		sprintf(str, "iconhero/hero%d.png", i+1);
		auto iconHero = cocos2d::Sprite::create(str);
		if (i==0)
		{
			float posX = iconHero->getContentSize().width / 2 + 80;
			float posY = SCREEN_H - iconHero->getContentSize().height / 2 - iconHero->getContentSize().height / 3 -5;
			iconHero->setPosition(cocos2d::Vec2(posX,posY));
		}
		else
		{
			float posX = mListIconHero[i - 1]->getPosition().x + mListIconHero[i - 1]->getContentSize().width/2 + iconHero->getContentSize().width / 2;
			float posY = mListIconHero[i - 1]->getPosition().y;
			iconHero->setPosition(cocos2d::Vec2(posX, posY));
		}
		mListIconHero.push_back(iconHero);
		addChild(iconHero);
	}
}

void HelloWorld::createMonster()
{
	for (int i = 0; i < 5; i++)
	{
		Troll *troll = new Troll(this);
		troll->setCastle(mCastle);
		mListMonsters.push_back(troll);
	}
	/*for (int i = 0; i < 5; i++)
	{
		HammerOrk *hammerOrk = new HammerOrk(this);
		hammerOrk->setCastle(mCastle);
		mListMonsters.push_back(hammerOrk);
	}*/
	for (int  i = 0; i < mListMonsters.size(); i++)
	{
		mListMonsters[i]->setPos(cocos2d::Vec2(MONSTER_APPEAR, SCREEN_H / 3 - mListMonsters[i]->getSprite()->getContentSize().height));
	}
}

void HelloWorld::createPedestal()
{
	auto pedestal1 = new Pedestal(this);
	mListPedestal.push_back(pedestal1);
	pedestal1->setPos(cocos2d::Vec2(100, 350));

	auto pedestal2 = new Pedestal(this);
	mListPedestal.push_back(pedestal2);
	pedestal2->setPos(cocos2d::Vec2(250, 500));

	auto pedestal3 = new Pedestal(this);
	mListPedestal.push_back(pedestal3);
	pedestal3->setPos(cocos2d::Vec2(450, 400));

	auto pedestal4 = new Pedestal(this);
	mListPedestal.push_back(pedestal4);
	pedestal4->setPos(cocos2d::Vec2(650, 600));

	auto pedestal5 = new Pedestal(this);
	mListPedestal.push_back(pedestal5);
	pedestal5->setPos(cocos2d::Vec2(850, 350));

	auto pedestal6 = new Pedestal(this);
	mListPedestal.push_back(pedestal6);
	pedestal6->setPos(cocos2d::Vec2(1050, 530));
}

void HelloWorld::checkDuplicate()
{
	if (mListCharacters.size() > 1)
	{
		for (int i = 0; i < mListCharacters.size(); i++)
		{
			for (int j = i + 1; j < mListCharacters.size(); j++)
			{
				if (mListCharacters[j]->getAlive() == 1 && !mListCharacters[j]->getAppear() )
				{
					
					if (mListCharacters[i]->getSprite()->getBoundingBox().intersectsRect(mListCharacters[j]->getSprite()->getBoundingBox()))
					{
						mListCharacters[j]->setAlive(2);
						mListCharacters[j]->setAppear(false);
						break;
					}
					else
					{
						mListCharacters[j]->setAppear(true);
						break;
					}
				}
			}
		}
	}
}

void HelloWorld::update(float delta)
{
	countFrame += 1;
	for (int i = 0; i < mListCharacters.size(); i++)
	{
		if (mListCharacters[i]->getAlive() == 1)
		{
			mListCharacters[i]->update();
		}
		if (mListCharacters[i]->getAlive() == 2 && !mListCharacters[i]->getAppear())
		{
			mListCharacters[i]->getSprite()->removeFromParent();
			mListCharacters.erase(mListCharacters.begin() + i);
		}
	}

	if (countFrame % (FPS) == 0)
	{
		for (int i = 0; i < mListMonsters.size(); i++)	
		{
			if (mListMonsters[i]->getAppear() == false)
			{
				mListMonsters[i]->setAppear(true);
				countFrame = 0;
				break;
			}
		}
	}

	for (int i = 0; i < mListMonsters.size(); i++)
	{
		if (mListMonsters[i]->getAppear() == true)
		{
			mListMonsters[i]->update();
		}
	}

	boat->update();
	boat->setListMonster(mListMonsters);
	checkDuplicate();

	if (mCastle->getLoadingbar()->getPercent() == 0)
	{
		Director::getInstance()->pause();
	}
}
