#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

bool mod_enabled = true;

$execute {
	mod_enabled = Mod::get()->getSettingValue<bool>("enabled");
	listenForSettingChanges("enabled", [](bool val) {
		mod_enabled = val;
	});
}

class $modify(PlayLayer) {
	bool init(GJGameLevel* p1, bool p2, bool p3) {
		if(!PlayLayer::init(p1, p2, p3)) return false;

		if(!mod_enabled) return true;

		CCNode* main_node = getChildByID("main-node");
		CCDirector* director = CCDirector::get();
		CCSize winSize = director->getWinSize();
		float ratio = winSize.width / winSize.height;
		int ratio_width = ratio * 9;

		/* If it works, don't touch it. */
		if(ratio_width > 16) {
			CCSprite* right = CCSprite::create("square.png");
			right->setColor(ccc3(0, 0, 0));
			right->setScaleX(winSize.width / ratio_width * (ratio_width - 16) / 2 / right->getContentWidth());
			right->setScaleY(winSize.height / right->getContentHeight());
			right->setAnchorPoint(ccp(0, 0.5));
			right->setPosition(ccp(winSize.width - right->getScaledContentWidth(), winSize.height / 2));
			main_node->addChild(right, 1024);
	
			CCSprite* left = CCSprite::create("square.png");
			left->setColor(ccc3(0, 0, 0));
			left->setScaleX(winSize.width / ratio_width * (ratio_width - 16) / 2 / left->getContentWidth());
			left->setScaleY(winSize.height / left->getContentHeight());
			left->setAnchorPoint(ccp(1, 0.5));
			left->setPosition(ccp(left->getScaledContentWidth(), winSize.height / 2));
			main_node->addChild(left, 1024);
		} else if(ratio_width < 16) {
			CCSprite* top = CCSprite::create("square.png");
			top->setColor(ccc3(0, 0, 0));
			top->setScaleX(winSize.width / top->getContentWidth());
			top->setScaleY(winSize.height / 9 * (16 - ratio_width) / 4 / top->getContentHeight());
			top->setAnchorPoint(ccp(0.5, 0));
			top->setPosition(ccp(winSize.width / 2, winSize.height - top->getScaledContentHeight()));
			main_node->addChild(top, 1024);
	
			CCSprite* bottom = CCSprite::create("square.png");
			bottom->setColor(ccc3(0, 0, 0));
			bottom->setScaleX(winSize.width / top->getContentWidth());
			bottom->setScaleY(winSize.height / 9 * (16 - ratio_width) / 4 / top->getContentHeight());
			bottom->setAnchorPoint(ccp(0.5, 1));
			bottom->setPosition(ccp(winSize.width / 2, bottom->getScaledContentHeight()));
			main_node->addChild(bottom, 1024);
		}
		/* <==========================> */

		// Honestly I don't even know how this works
		// TODO: Make levels fit all devices (without any crops)

		return true;
	}
};