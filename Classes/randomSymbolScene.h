#ifndef __RANDOM_SYMBOL_SCENE__
#define __RANDOM_SYMBOL_SCENE__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

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
	void randomOneSymbol();
	int randomOneNumFromAll();


private:
	Node* _listnerNode;
	Sprite* _newSymbol;
	Label* _labelTips;
};


#endif