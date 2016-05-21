#ifndef MY_BUUTOBN_H
#define MY_BUUTOBN_H

#include "cocos2d.h"
using namespace cocos2d;
//#include "GameMusic.h"

#include "cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <vector>

using namespace cocostudio;
using namespace cocos2d::ui;

#define SCALETIME	0.1f


class  MyButton :public MenuItemImage
{

public:
	MyButton();

	static MyButton* create(const char* spriteImg1,const char* spriteImg2="", const ccMenuCallback& callback=(const ccMenuCallback&)nullptr,char * effect=NULL,bool isScale=true);
	
	void selected();
	void unselected();


	void setButtonEffect(char * buttonEffect);

	void myButtonAddChild(Node* child);
private:
	char * _buttonEffect;
	 Vector<Node*> _myButtonChildren;  

};

class MyUiButton :public ui::Button
{
public:
protected:
	virtual bool init()override;
protected:
	virtual void onPressStateChangedToPressed()override;	
};

#endif // !MY_BUUTOBN_H
