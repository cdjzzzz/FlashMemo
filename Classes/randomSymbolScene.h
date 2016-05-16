#ifndef __RANDOM_SYMBOL_SCENE__
#define __RANDOM_SYMBOL_SCENE__

#include "cocos2d.h"

#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;
USING_NS_CC_EXT;

using namespace std;

typedef struct stTranslate
{
	int index;
	std::string content;
}stTranslate;

class RandomSymbolScene : public cocos2d::Layer
{
public:
	RandomSymbolScene();
	~RandomSymbolScene();
	static Scene* createScene();
	bool init();

	void onEnter();
	void onExit();

	bool onTouchBegan(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch, Event *unused_event);
	void onTouchEnded(Touch *touch, Event *unused_event);

	CREATE_FUNC(RandomSymbolScene);

	// my funciton
	void preloadTranslation();

	void randomOneSymbol();
	int randomOneNumFromAll();


private:
	Node* _listnerNode;
	Sprite* _newSymbol;
	Label* _labelTips;

	vector<stTranslate> m_vecTranlation;
};


#endif