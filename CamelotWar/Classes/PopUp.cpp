#include "PopUp.h"
#include "Defines.h"
#include "ui\CocosGUI.h"

bool PopUp::init()
{
	if (!Node::init()) return false;

	mLayer = cocos2d::Layer::create();
	mLayer->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	mLayer->setPosition(SCREEN_W / 2, SCREEN_H / 2);
	addChild(mLayer);
	return true;
}

//void PopUp::onExit()
//{
//	Node::onExit();
//}

void PopUp::setBackground()
{
	mBackground = cocos2d::Sprite::create(DIALOG_MAP);
	mBackground->setPosition(0, 0);


	mLayer->addChild(mBackground);

	//auto btnExit = cocos2d::ui::Button::create(BUTTON_EXIT);
	//btnExit->setScale(0.75);
	//btnExit->setPosition(cocos2d::Vec2(mBackground->getContentSize().width / 7, -mBackground->getContentSize().height / 4
	//	+ mBackground->getContentSize().height / 22));

	//mLayer->addChild(btnExit);
	//btnExit->addTouchEventListener([=](Ref* sender, cocos2d::ui::Widget::TouchEventType t) {
	//	switch (t)
	//	{
	//	case cocos2d::ui::Widget::TouchEventType::BEGAN:

	//		break;
	//	case cocos2d::ui::Widget::TouchEventType::ENDED:
	//		//disappear();
	//		mLayer->setVisible(false);
	//		//mLayer->removeFromParentAndCleanup(true);
	//		break;

	//	}
	//});
}

void PopUp::disappear()
{
	auto dis = cocos2d::TargetedAction::create(mLayer, cocos2d::FadeOut::create(3));
	this->runAction(dis);
}

cocos2d::Layer* PopUp::getLayer()
{
	return mLayer;
}