#pragma once
#include "cocos2d.h"
#include "Character.h"
#include <vector>

class SwordKnight :
	public Character
{
public:
	SwordKnight();
	~SwordKnight();
	SwordKnight(cocos2d::Scene *scene);

	void walk() override;
	void attack() override;
	void die() override;

	void setListMonster(std::vector<Character*> listMonsters);
	void collision();
	void update();
	void init();
private:
	std::vector< Character*> mListMonsters;
	int mFrameCount;
	bool hasAnimated;
	int countFrame = 0;
};

