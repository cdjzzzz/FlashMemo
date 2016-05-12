#include "randomSymbolScene.h"
#include "conMacro.h"

RandomSymbolScene::RandomSymbolScene()
{
	_newSymbol = NULL;
	_labelTips = NULL;
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

	_labelTips = Label::createWithTTF("tap to switch the symbol", FONT_CH_NAME, 30);
	_labelTips->setPosition(VISIBLE_MID_X, VISIBLE_SIZE_HEIGHT - 100);
	addChild(_labelTips);
	
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

	randomOneSymbol();
}


void RandomSymbolScene::randomOneSymbol()
{
	if (_newSymbol)
	{
		_newSymbol->removeFromParentAndCleanup(true);
		_newSymbol = NULL;
	}

	int nRanNum = randomOneNumFromAll();

	__String* strSymbolFileName = __String::createWithFormat("symbol\\symbol%d.jpg", nRanNum);

	_newSymbol = Sprite::create(strSymbolFileName->getCString());
	_newSymbol->setPosition(VISIBLE_MID_X, VISIBLE_MID_Y);
	addChild(_newSymbol);
}


int RandomSymbolScene::randomOneNumFromAll()
{
	return rand() % MAX_SYMBOL_NUM + 1;
}