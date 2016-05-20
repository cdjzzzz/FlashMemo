#include "myButton.h"

MyButton::MyButton()
{
	_buttonEffect = NULL;
}

MyButton* MyButton::create(const char* spriteImg1,const char* spriteImg2, const ccMenuCallback& callback,char * effect,bool isScale)
{
	MyButton* mybutton =new (std::nothrow)MyButton();

	mybutton->setButtonEffect(effect);


	Sprite *pNormalSprite = Sprite::create(spriteImg1);


	if ( (spriteImg2==NULL ||spriteImg2=="") && isScale)
	{
		auto pSelectedSprite =ui:: Scale9Sprite::create(spriteImg1);
		pSelectedSprite->setScale(SCALETIME+1.0f);
		float dW = pNormalSprite->getContentSize().width*SCALETIME;
		float dH = pNormalSprite->getContentSize().height*SCALETIME;

		pSelectedSprite->setPosition(Vec2(-dW/2,-dH/2));	

		mybutton->initWithNormalSprite(pNormalSprite, pSelectedSprite, NULL, callback);


	}else
	{
		Sprite* pSelectedSprite ;
		if (spriteImg2==NULL ||spriteImg2=="")
		{
			pSelectedSprite = Sprite::create(spriteImg1);
		}else{
			pSelectedSprite = Sprite::create(spriteImg2);
		}
		auto disabledSprite = Sprite::create();

		mybutton->initWithNormalSprite(pNormalSprite, pSelectedSprite, disabledSprite, callback);


	}
	mybutton->autorelease();
	return mybutton;

}
void MyButton::selected()
{
	CCLOG("music!!!");
	if (_buttonEffect!=NULL)
	{
		//GameMusic::getInstance()->playEffect(_buttonEffect); 
	}else{
		//GameMusic::getInstance()->playButtonTouchSoundEffect();
	}
	for(auto child : _myButtonChildren) 
	{ 
		child->setScale(1.1f);
	} 


	MenuItemSprite::selected();
}

void MyButton::myButtonAddChild(Node* child)
{
	MenuItemImage::addChild(child);
	_myButtonChildren.pushBack(child);
}
void MyButton::unselected()
{
	for(auto child : _myButtonChildren) 
	{ 
		child->setScale(1.0f);
	}
	MenuItemSprite::unselected();
}


void MyButton::setButtonEffect(char * buttonEffect)
{
	_buttonEffect= buttonEffect;
}


bool MyUiButton::init()
{
	if (Button::init())
	{
		return true;
	}
	return false;
}

void MyUiButton::onPressStateChangedToPressed()
{
	CCLOG("--------");
	//GameMusic::getInstance()->playButtonTouchSoundEffect();
	Button::onPressStateChangedToPressed();
}