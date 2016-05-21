#ifndef CON_MACRA_H
#define CON_MACRA_H

#define FONT_NAME					"fonts/Marker Felt.ttf"
#define FONT_CH_NAME				"fonts/crazyTrans.ttf"

/////////////////////////////////////////////////////////////////////
//
//			Plist const define
//
////////////////////////////////////////////////////////////////////
#define PLiST_TRANSLATE				"symbol/translate.plist"
#define PLIST_KEY					"symbol"
/////////////////////////////////////////////////////////////////////
//
//			Plist const define end
//
////////////////////////////////////////////////////////////////////

#define PIC_PATH_BACK					"commonUI/btnHome.png"
#define PIC_PATH_HINT					"item/safeBub.png"

#define VISIBLE_SIZE				Director::getInstance()->getVisibleSize()
#define VISIBLE_SIZE_WIDTH			Director::getInstance()->getVisibleSize().width
#define VISIBLE_SIZE_HEIGHT			Director::getInstance()->getVisibleSize().height

#define VISIBLE_ORIGIN				Director::getInstance()->getVisibleOrigin()
#define VISIBLE_ORIGIN_X			Director::getInstance()->getVisibleOrigin().x
#define VISIBLE_ORIGIN_Y			Director::getInstance()->getVisibleOrigin().y

#define VISIBLE_MID_X			(VISIBLE_ORIGIN_X + VISIBLE_SIZE_WIDTH/2)
#define VISIBLE_MID_Y			(VISIBLE_ORIGIN_Y + VISIBLE_SIZE_HEIGHT/2)
#define CENTER_POINT			Vec2(VISIBLE_MID_X,VISIBLE_MID_Y)

#define	IF_X_NOT_NULL_Y(x, y)	\
{ \
	if( (x) != NULL) \
	(y) ; \
}


#define MAX_SYMBOL_NUM		227

#endif // !CON_MACRA_H
