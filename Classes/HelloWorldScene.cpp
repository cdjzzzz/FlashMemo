#include "HelloWorldScene.h"
#include "conMacro.h"
#include "imgConst.h"
#include "randomSymbolScene.h"

USING_NS_CC;

#define SET_USERDEFAULT_VALUE(X, Y) \
{ \
if (UserDefault::getInstance()->getIntegerForKey((X), -2) == -2) \
	UserDefault::getInstance()->setIntegerForKey((X), (Y)); \
}

#define MUSIC_ON_POSX				(123)
#define MUSIC_OFF_POSX				(194)
#define SFX_ON_POSX					(292)
#define SFX_OFF_POSX				(360)


HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{

}

Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();


	auto layer = HelloWorld::create();

	scene->addChild(layer, 0);

	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	/////////////////////////////
	// 3. add your codes below...

	// init user default
	initUserDefault();

	// init bkg
	initBkg();

	//...init
	armatureLoading();

	//  sprite
	initSprite();

	//call this after all init is finish
	bootArmature();

	return true;
}



void HelloWorld::initUserDefault()
{
	struct timeval now;

	if (gettimeofday(&now, nullptr) != 0)
	{
		CCLOG("error in gettimeofday");
		return;
	}

	unsigned long int rand_seed = now.tv_sec * 1000 + now.tv_usec / 1000;
	srand(rand_seed);

}

void HelloWorld::initBkg()
{
	ui::Widget * wiget = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("HelloWorld/hellowordl_1.json");

	auto panel = (ui::Widget *)ui::Helper::seekWidgetByName(wiget, "Panel_14");
	auto imgBkg = static_cast<ui::ImageView*>(Helper::seekWidgetByName(panel, "Image_bkg"));
	_imgLogo = static_cast<ui::ImageView*>(Helper::seekWidgetByName(panel, "Image_logo"));
	_imgLogoBkg = static_cast<ui::ImageView*>(Helper::seekWidgetByName(panel, "Image_logoBkg"));
	_imgPlanetBig = static_cast<ui::ImageView*>(Helper::seekWidgetByName(panel, "Image_planet"));
	_imgPlanetGreen = static_cast<ui::ImageView*>(Helper::seekWidgetByName(panel, "Image_planetGreen"));
	_imgPlanetRed = static_cast<ui::ImageView*>(Helper::seekWidgetByName(panel, "Image_planetRed"));
	_imgPlanetBlue = static_cast<ui::ImageView*>(Helper::seekWidgetByName(panel, "Image_planetBlue"));

	auto start = static_cast<ui::Button*>(Helper::seekWidgetByName(imgBkg, "Button_start"));
	start->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnCallBack, this));
	auto setting = static_cast<ui::Button*>(Helper::seekWidgetByName(imgBkg, "Button_setting"));
	setting->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnCallBack, this));

	this->addChild(wiget);
}

void HelloWorld::initSprite()
{
	// rabbit
	// main armature
	auto armatureRabbit = Armature::create(RABBIT_ARMATURE);
	armatureRabbit->setAnchorPoint(Vec2(0.5, 0.5));
	armatureRabbit->setPosition(Vec2(360, 400));
	armatureRabbit->setScale(0.75f);
	this->addChild(armatureRabbit);
	armatureRabbit->getAnimation()->play("zou");

	// fox
	auto armatureFox = Armature::create(FOX_ARMATURE);
	armatureFox->setAnchorPoint(Vec2(0.5, 0.5));
	armatureFox->setPosition(Vec2(630, 380));
	armatureFox->setRotation(20);
	armatureFox->setScale(0.75f);
	this->addChild(armatureFox);
	armatureFox->getAnimation()->play("zoulu");

	/*
	//mushroom
	auto mushroom = Sprite::create(MUSHROOM_IMG);
	mushroom->setPosition(190, 380);
	mushroom->setRotation(-20);
	mushroom->setScaleX(0.36f);
	mushroom->setScaleY(0.40f);
	this->addChild(mushroom);*/
}

void HelloWorld::bootArmature()
{
	_imgPlanetBig->runAction(RepeatForever::create(RotateBy::create(124.0f, 360)));
}

void HelloWorld::onEnter()
{
	auto _touchListner = EventListenerTouchOneByOne::create();
	_touchListner->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	_touchListner->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

	_touchListner->setSwallowTouches(true); //no more dispatch to child
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListner, this);

	CCLayer::onEnter();
}

void HelloWorld::onExit()
{

	CCLayer::onExit();
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto location = touch->getLocation();
	Director::getInstance()->replaceScene(RandomSymbolScene::createScene());
}

void HelloWorld::armatureLoading()
{
	ArmatureDataManager::getInstance()->removeArmatureFileInfo(RABBIT_ARMATURE_FILEPATH);
	ArmatureDataManager::getInstance()->removeAnimationData(FOX_ARMATURE_FILEPATH);

	// load from binary
	ArmatureDataManager::getInstance()->addArmatureFileInfo(RABBIT_ARMATURE_FILEPATH);
	ArmatureDataManager::getInstance()->addArmatureFileInfo(FOX_ARMATURE_FILEPATH);
}


void HelloWorld::btnCallBack(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		ui::Button* btn = (ui::Button*)pSender;

		if (btn->getName() == "Button_start")
		{
			Director::getInstance()->replaceScene(RandomSymbolScene::createScene());
		}
		else if (btn->getName() == "Button_setting")
		{
			//
			showSettings();
		}
	}
}


// settings
void HelloWorld::showSettings()
{
	//mask
	_spSettingMask = Sprite::create("mapMask.png");
	_spSettingMask->setPosition(Vec2(VISIBLE_MID_X, VISIBLE_MID_Y));
	addChild(_spSettingMask);

	_widgetSetting = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("settings/Setting_1.json");

	auto panel = (ui::Widget *)ui::Helper::seekWidgetByName(_widgetSetting, "Panel_14");
	auto imgBkg = static_cast<ui::ImageView*>(Helper::seekWidgetByName(panel, "Image_settingBkg"));

	_btnMusicThumb = static_cast<ui::Button*>(Helper::seekWidgetByName(panel, "Button_music"));
	_btnMusicThumb->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchMusicIcon, this));
	//if (GameMusic::getInstance()->getBackgroundMuted() == true)
	{
		_btnMusicThumb->setPositionX(MUSIC_OFF_POSX);
	}
	//else
	{
		_btnMusicThumb->setPositionX(MUSIC_ON_POSX);
	}


	_btnSfxThumb = static_cast<ui::Button*>(Helper::seekWidgetByName(panel, "Button_sfx"));
	_btnSfxThumb->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchSfxIcon, this));
	//if (GameMusic::getInstance()->getSoundEffectMute() == true)
	{
		_btnSfxThumb->setPositionX(SFX_OFF_POSX);
	}
	//else
	{
		_btnSfxThumb->setPositionX(SFX_ON_POSX);
	}

	auto credit = static_cast<ui::Button*>(Helper::seekWidgetByName(imgBkg, "Button_credit"));
	//credit->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnCallBack, this));
	auto howtoPlay = static_cast<ui::Button*>(Helper::seekWidgetByName(imgBkg, "Button_howToPlay"));
	//howtoPlay->addTouchEventListener(CC_CALLBACK_2(HelloWorld::btnCallBack, this));

	auto exitSettings = static_cast<ui::Button*>(Helper::seekWidgetByName(imgBkg, "Button_exit"));
	exitSettings->addTouchEventListener(CC_CALLBACK_2(HelloWorld::closeSettings, this));

	this->addChild(_widgetSetting);
}

void HelloWorld::closeSettings(Ref *pSender, Widget::TouchEventType type)
{
	_widgetSetting->removeFromParentAndCleanup(true);
	_spSettingMask->removeFromParentAndCleanup(true);
}

void HelloWorld::touchMusicIcon(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//if (GameMusic::getInstance()->getBackgroundMuted() == true)
		{
			// turn on
			_btnMusicThumb->setPositionX(MUSIC_ON_POSX);

			//GameMusic::getInstance()->UnmuteBackground();
		}
		//else
		{
			//turn off
			_btnMusicThumb->setPositionX(MUSIC_OFF_POSX);
			//GameMusic::getInstance()->MuteBackground();
		}
	}
}

void HelloWorld::touchSfxIcon(Ref *pSender, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED)
	{
		//if (GameMusic::getInstance()->getSoundEffectMute() == true)
		{
			// turn on
			_btnSfxThumb->setPositionX(SFX_ON_POSX);

		//	GameMusic::getInstance()->UnmuteSoundEffect();
		}
		//else
		{
			//turn off
			_btnSfxThumb->setPositionX(SFX_OFF_POSX);
		//	GameMusic::getInstance()->MuteSoundEffect();
		}
	}
}