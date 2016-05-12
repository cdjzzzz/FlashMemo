#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
USING_NS_CC_EXT;

class HelloWorld : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	HelloWorld();
	~HelloWorld();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	void initUserDefault();
	void initBkg();
	void initSprite();

	void armatureLoading();

	// start armature
	void bootArmature();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	void onEnter();
	void onExit();

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	void btnCallBack(Ref *pSender, Widget::TouchEventType type);

	// settings ui
	void showSettings();
	void closeSettings(Ref *pSender, Widget::TouchEventType type);
	void touchMusicIcon(Ref *pSender, Widget::TouchEventType type);
	void touchSfxIcon(Ref *pSender, Widget::TouchEventType type);

private:
	ui::ImageView* _imgLogo;
	ui::ImageView* _imgLogoBkg;
	ui::ImageView* _imgPlanetRed;
	ui::ImageView* _imgPlanetGreen;
	ui::ImageView* _imgPlanetBlue;
	ui::ImageView* _imgPlanetBig;

	ui::Widget * _widgetSetting;
	Sprite* _spSettingMask;
	ui::Button* _btnMusicThumb;
	ui::Button* _btnSfxThumb;
};

#endif // __HELLOWORLD_SCENE_H__
