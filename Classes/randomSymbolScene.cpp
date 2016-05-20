#include "randomSymbolScene.h"
#include "conMacro.h"
#include "myButton.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;


RandomSymbolScene::RandomSymbolScene()
{
	_newSymbol = NULL;
	_labelContent = NULL;
	_labelTips = NULL;
	m_vecTranlation.clear();
	_previouNum = 0;
	_currentNum = 0;
}

RandomSymbolScene::~RandomSymbolScene()
{
}

void RandomSymbolScene::onEnter()
{
	CCLayer::onEnter();
}

void RandomSymbolScene::onExit()
{

	CCLayer::onExit();
}

Scene* RandomSymbolScene::createScene()
{
	auto scene = Scene::create();

	auto layer = RandomSymbolScene::create();

	scene->addChild(layer, 0);
	return scene;
}

bool RandomSymbolScene::init()
{
	auto touchListner = EventListenerTouchOneByOne::create();
	touchListner->onTouchBegan = CC_CALLBACK_2(RandomSymbolScene::onTouchBegan, this);
	touchListner->onTouchMoved = CC_CALLBACK_2(RandomSymbolScene::onTouchMoved, this);
	touchListner->onTouchEnded = CC_CALLBACK_2(RandomSymbolScene::onTouchEnded, this);

	//touchListner->setSwallowTouches(true); //no more dispatch to child
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListner, this);

	_labelTips = Label::createWithTTF("tap right to change\ntap left to previous\ntap up to hint", FONT_CH_NAME, 30);
	_labelTips->setPosition(VISIBLE_MID_X, VISIBLE_SIZE_HEIGHT - 100);
	addChild(_labelTips);
	
	//ui
	MyButton* back = MyButton::create(PIC_PATH_BACK, PIC_PATH_BACK,CC_CALLBACK_1(RandomSymbolScene::menuBackCallback, this),nullptr,false);

	//MyButton* hint = MyButton::create(PIC_PATH_HINT, PIC_PATH_HINT,CC_CALLBACK_1(RandomSymbolScene::menuHintCallback, this),nullptr,false);
	//hint->setPosition(Vec2(VISIBLE_SIZE_WIDTH-30, VISIBLE_ORIGIN_Y-30));
	auto menu = Menu::create(back, NULL);
	menu->setPosition(Vec2(VISIBLE_ORIGIN_X+30, VISIBLE_SIZE_HEIGHT-30));
	this->addChild(menu, 1);

	// preload
	preloadTranslation();

	return true;
}


bool RandomSymbolScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void RandomSymbolScene::onTouchMoved(Touch *touch, Event *unused_event)
{

}

void RandomSymbolScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	if (_labelTips)
	{
		_labelTips->removeFromParentAndCleanup(true);
		_labelTips = NULL;
	}

	Vec2 pt = touch->getLocation();

	if(pt.x > VISIBLE_MID_X && pt.y < VISIBLE_MID_Y)
	{
		// right down corner
		randomOneSymbol();
	}
	else if(pt.x < VISIBLE_MID_X && pt.y < VISIBLE_MID_Y)
	{
		//left dwon corner
		previouseSymbol();
	}
	else if(pt.y > VISIBLE_MID_Y)
	{
		// up
		if(_labelContent)
			_labelContent->setVisible(true);
	}
}

void RandomSymbolScene::preloadTranslation()
{
	__Dictionary *dic = __Dictionary::createWithContentsOfFile(PLiST_TRANSLATE);

	auto dicSymbol = (__Dictionary *)dic->objectForKey(PLIST_KEY);

	for (int i = 0; i < dicSymbol->count(); i++)
	{
		__Dictionary *item = (__Dictionary *)dicSymbol->objectForKey(__String::createWithFormat("symbol_%d", i + 1)->getCString());
		std::string icon = item->valueForKey("icon")->getCString();
		std::string content = item->valueForKey("content")->getCString();

		stTranslate stTemp;
		stTemp.index = i+1;
		stTemp.imagePath = icon;
		stTemp.content = content;

		m_vecTranlation.push_back(stTemp);
	}

}

std::string RandomSymbolScene::findContentByImagePath(std::string szImagePath)
{
	for(unsigned int i=0; i<m_vecTranlation.size(); i++)
	{
		if(m_vecTranlation[i].imagePath == szImagePath)
		{
			return m_vecTranlation[i].content;
		}
	}

	return "";
}

void RandomSymbolScene::randomOneSymbol()
{
	int nRanNum = randomOneNumFromAll();
	_previouNum = _currentNum;
	_currentNum = nRanNum;

	showSpecificSymbol(_currentNum);
}

void RandomSymbolScene::previouseSymbol()
{
	if(_previouNum > 0)
		showSpecificSymbol(_previouNum);
}

void RandomSymbolScene::showSpecificSymbol(int index)
{
	if (_newSymbol)
	{
		_newSymbol->removeFromParentAndCleanup(true);
		_newSymbol = NULL;
	}

	if(_labelContent)
	{
		_labelContent->removeFromParentAndCleanup(true);
		_labelContent = NULL;
	}

	__String* strSymbolFileName = __String::createWithFormat("symbol/symbol%d.jpg", index);

	_newSymbol = Sprite::create(strSymbolFileName->getCString());
	_newSymbol->setPosition(VISIBLE_MID_X, VISIBLE_MID_Y);

	std::string content = findContentByImagePath(strSymbolFileName->getCString());
	if(content != "")
	{
		_labelContent = Label::createWithTTF(content, FONT_CH_NAME, 60);
		_labelContent->setPosition(VISIBLE_MID_X, VISIBLE_SIZE_HEIGHT - 150);
		addChild(_labelContent);
		_labelContent->setVisible(false);
	}

	addChild(_newSymbol);
}

int RandomSymbolScene::randomOneNumFromAll()
{
	return rand() % 22 + 1;
}

void RandomSymbolScene::menuBackCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->popScene();
}

void RandomSymbolScene::menuHintCallback(cocos2d::Ref* pSender)
{
	if(_labelContent)
	{
		_labelContent->setVisible(true);
	}
}