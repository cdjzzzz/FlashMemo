#include "randomSymbolScene.h"
#include "conMacro.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio;


RandomSymbolScene::RandomSymbolScene()
{
	_newSymbol = NULL;
	_labelTips = NULL;
	m_vecTranlation.clear();
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

	_labelTips = Label::createWithTTF("tap to change", FONT_CH_NAME, 30);
	_labelTips->setPosition(VISIBLE_MID_X, VISIBLE_SIZE_HEIGHT - 100);
	addChild(_labelTips);
	
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

	randomOneSymbol();
}

void RandomSymbolScene::preloadTranslation()
{
	//json 文档
	rapidjson::Document doc;
	bool bRet = false;
	ssize_t size = 0;
	unsigned char *pBytes = NULL;
	do {
		pBytes = cocos2d::CCFileUtils::sharedFileUtils()->getFileData("symbol/translate.json", "r", &size);
		CC_BREAK_IF(pBytes == NULL || strcmp((char*)pBytes, "") == 0);
		std::string load_str((const char*)pBytes, size);
		CC_SAFE_DELETE_ARRAY(pBytes);
		doc.Parse<0>(load_str.c_str());
		CC_BREAK_IF(doc.HasParseError());			
		//生成json文档对像



		// 通过[]取成员值,再根据需要转为array,int,double,string
		const rapidjson::Value &pArray = doc;

		//是否是数组
		if(!pArray.IsArray())
			return;

		for (rapidjson::SizeType i = 0; i < pArray.Size(); i++)
		{
			const rapidjson::Value &p = pArray[i];				
			if(p.HasMember("entity"))
			{
				const rapidjson::Value &valueEnt = p["index"];
				if(valueEnt.HasMember("TapOpposite") && valueEnt.HasMember("Interval") && valueEnt.HasMember("BallNum"))
				{
					const rapidjson::Value &tapOpposite = valueEnt["TapOpposite"];
					int tapOp = tapOpposite.GetInt();      //得到int值

					const rapidjson::Value &interval = valueEnt["Interval"];
					float inter = interval.GetDouble();  //得到float,double值

					const rapidjson::Value &ballNum = valueEnt["BallNum"];
					int ball = ballNum.GetInt();      //得到int值

					stTranslate param;
					//param.index = ;
					m_vecTranlation.push_back(param);
				}
			}
			else
			{
				return;
			}

		}
		bRet = true;

	} while (0);

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