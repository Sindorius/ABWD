#include "AnimationManager.hpp"

USING_NS_CC;

AnimationManager::AnimationManager()
{
	//player 1 animations
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<SpriteFrame*> walkupanimFrames;
	walkupanimFrames.reserve(4);
	Vector<SpriteFrame*> walkdownanimFrames;
	walkdownanimFrames.reserve(4);
	Vector<SpriteFrame*> walkleftanimFrames;
	walkleftanimFrames.reserve(4);
	Vector<SpriteFrame*> walkrightanimFrames;
	walkrightanimFrames.reserve(4);
	Vector<SpriteFrame*> paintFrames;
	paintFrames.reserve(1);
	
	walkupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_up0.png", Rect(0, 0, 24, 48)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_up1.png", Rect(0, 0, 24, 48)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_up2.png", Rect(0, 0, 24, 48)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_up3.png", Rect(0, 0, 24, 48)));
	walkupanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_down0.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_down1.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_down2.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_down3.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_left0.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_left1.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_left2.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_left3.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_right0.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_right1.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_right2.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_right3.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(3)->getTexture()->setAliasTexParameters();

	paintFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_painting_left0.png", Rect(0, 0, 24, 48)));
	paintFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_painting_left1.png", Rect(0, 0, 24, 48)));
	paintFrames.at(0)->getTexture()->setAliasTexParameters();
	paintFrames.at(1)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* upanimation = Animation::createWithSpriteFrames(walkupanimFrames, 0.1f);
	cocos2d::Animate* walkupanim = Animate::create(upanimation);
	walkupanim->retain();
	Animation* downanimation = Animation::createWithSpriteFrames(walkdownanimFrames, 0.1f);
	cocos2d::Animate* walkdownanim = Animate::create(downanimation);
	walkdownanim->retain();
	Animation* leftanimation = Animation::createWithSpriteFrames(walkleftanimFrames, 0.1f);
	cocos2d::Animate* walkleftanim = Animate::create(leftanimation);
	walkleftanim->retain();
	Animation* rightanimation = Animation::createWithSpriteFrames(walkrightanimFrames, 0.1f);
	cocos2d::Animate* walkrightanim = Animate::create(rightanimation);
	walkrightanim->retain();


	Animation* paintanimation = Animation::createWithSpriteFrames(paintFrames, 0.1f);
	cocos2d::Animate* paintanim = Animate::create(paintanimation);
	paintanim->retain();

	animationmap.insert(std::pair<std::string,Animate*>(std::string("p1up"), walkupanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1down"), walkdownanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1left"), walkleftanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1right"), walkrightanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1paint"), paintanim));


	//player2 animations
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<SpriteFrame*> walkupanimFrames2;
	walkupanimFrames2.reserve(4);
	Vector<SpriteFrame*> walkdownanimFrames2;
	walkdownanimFrames2.reserve(4);
	Vector<SpriteFrame*> walkleftanimFrames2;
	walkleftanimFrames2.reserve(4);
	Vector<SpriteFrame*> walkrightanimFrames2;
	walkrightanimFrames2.reserve(4);
	Vector<SpriteFrame*> paintFrames2;
	paintFrames2.reserve(1);
	

	walkupanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_up0.png", Rect(0, 0, 24, 48)));
	walkupanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_up1.png", Rect(0, 0, 24, 48)));
	walkupanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_up2.png", Rect(0, 0, 24, 48)));
	walkupanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_up3.png", Rect(0, 0, 24, 48)));
	walkupanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames2.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down0.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down1.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down2.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down3.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames2.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_left0.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_left1.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_left2.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_left3.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames2.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_right0.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_right1.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_right2.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_right3.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames2.at(3)->getTexture()->setAliasTexParameters();

	paintFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_painting_left0.png", Rect(0, 0, 24, 48)));
	paintFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_painting_left1.png", Rect(0, 0, 24, 48)));
	paintFrames2.at(0)->getTexture()->setAliasTexParameters();
	paintFrames2.at(1)->getTexture()->setAliasTexParameters();


	// create the animation out of the frames
	Animation* upanimation2 = Animation::createWithSpriteFrames(walkupanimFrames2, 0.1f);
	cocos2d::Animate* walkupanim2 = Animate::create(upanimation2);
	walkupanim2->retain();
	Animation* downanimation2 = Animation::createWithSpriteFrames(walkdownanimFrames2, 0.1f);
	cocos2d::Animate* walkdownanim2 = Animate::create(downanimation2);
	walkdownanim2->retain();
	Animation* leftanimation2 = Animation::createWithSpriteFrames(walkleftanimFrames2, 0.1f);
	cocos2d::Animate* walkleftanim2 = Animate::create(leftanimation2);
	walkleftanim2->retain();
	Animation* rightanimation2 = Animation::createWithSpriteFrames(walkrightanimFrames2, 0.1f);
	cocos2d::Animate* walkrightanim2 = Animate::create(rightanimation2);
	walkrightanim2->retain();


	Animation* paintanimation2 = Animation::createWithSpriteFrames(paintFrames2, 0.1f);
	cocos2d::Animate* paintanim2 = Animate::create(paintanimation2);
	paintanim2->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2up"), walkupanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2down"), walkdownanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2left"), walkleftanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2right"), walkrightanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2paint"), paintanim2));



	//player3 animations
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<SpriteFrame*> walkupanimFrames3;
	walkupanimFrames3.reserve(4);
	Vector<SpriteFrame*> walkdownanimFrames3;
	walkdownanimFrames3.reserve(4);
	Vector<SpriteFrame*> walkleftanimFrames3;
	walkleftanimFrames3.reserve(4);
	Vector<SpriteFrame*> walkrightanimFrames3;
	walkrightanimFrames3.reserve(4);
	Vector<SpriteFrame*> paintFrames3;
	paintFrames3.reserve(1);
	//animFrames.reserve(4);

	walkupanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_up0.png", Rect(0, 0, 24, 48)));
	walkupanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_up1.png", Rect(0, 0, 24, 48)));
	walkupanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_up2.png", Rect(0, 0, 24, 48)));
	walkupanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_up3.png", Rect(0, 0, 24, 48)));
	walkupanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames3.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_down0.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_down1.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_down2.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_down3.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames3.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_left0.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_left1.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_left2.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_left3.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames3.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_right0.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_right1.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_right2.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_right3.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames3.at(3)->getTexture()->setAliasTexParameters();

	paintFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_painting_left0.png", Rect(0, 0, 24, 48)));
	paintFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_painting_left1.png", Rect(0, 0, 24, 48)));
	paintFrames3.at(0)->getTexture()->setAliasTexParameters();
	paintFrames3.at(1)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* upanimation3 = Animation::createWithSpriteFrames(walkupanimFrames3, 0.1f);
	cocos2d::Animate* walkupanim3 = Animate::create(upanimation3);
	walkupanim3->retain();
	Animation* downanimation3 = Animation::createWithSpriteFrames(walkdownanimFrames3, 0.1f);
	cocos2d::Animate* walkdownanim3 = Animate::create(downanimation3);
	walkdownanim3->retain();
	Animation* leftanimation3 = Animation::createWithSpriteFrames(walkleftanimFrames3, 0.1f);
	cocos2d::Animate* walkleftanim3 = Animate::create(leftanimation3);
	walkleftanim3->retain();
	Animation* rightanimation3 = Animation::createWithSpriteFrames(walkrightanimFrames3, 0.1f);
	cocos2d::Animate* walkrightanim3 = Animate::create(rightanimation3);
	walkrightanim3->retain();


	Animation* paintanimation3 = Animation::createWithSpriteFrames(paintFrames3, 0.1f);
	Animate* paintanim3 = Animate::create(paintanimation3);
	paintanim3->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3up"), walkupanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3down"), walkdownanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3left"), walkleftanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3right"), walkrightanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3paint"), paintanim3));



	//player4 animations
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Vector<SpriteFrame*> walkupanimFrames4;
	walkupanimFrames4.reserve(4);
	Vector<SpriteFrame*> walkdownanimFrames4;
	walkdownanimFrames4.reserve(4);
	Vector<SpriteFrame*> walkleftanimFrames4;
	walkleftanimFrames4.reserve(4);
	Vector<SpriteFrame*> walkrightanimFrames4;
	walkrightanimFrames4.reserve(4);
	Vector<SpriteFrame*> paintFrames4;
	paintFrames4.reserve(1);
	
	walkupanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_up0.png", Rect(0, 0, 24, 48)));
	walkupanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_up1.png", Rect(0, 0, 24, 48)));
	walkupanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_up2.png", Rect(0, 0, 24, 48)));
	walkupanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_up3.png", Rect(0, 0, 24, 48)));
	walkupanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down0.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down1.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down2.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down3.png", Rect(0, 0, 24, 48)));
	walkdownanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_left0.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_left1.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_left2.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_left3.png", Rect(0, 0, 24, 48)));
	walkleftanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_right0.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_right1.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_right2.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_right3.png", Rect(0, 0, 24, 48)));
	walkrightanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	paintFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_painting_left0.png", Rect(0, 0, 24, 48)));
	paintFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_painting_left1.png", Rect(0, 0, 24, 48)));
	paintFrames4.at(0)->getTexture()->setAliasTexParameters();
	paintFrames4.at(1)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* upanimation4 = Animation::createWithSpriteFrames(walkupanimFrames4, 0.1f);
	cocos2d::Animate* walkupanim4 = Animate::create(upanimation4);
	walkupanim4->retain();
	Animation* downanimation4 = Animation::createWithSpriteFrames(walkdownanimFrames4, 0.1f);
	cocos2d::Animate* walkdownanim4 = Animate::create(downanimation4);
	walkdownanim4->retain();
	Animation* leftanimation4 = Animation::createWithSpriteFrames(walkleftanimFrames4, 0.1f);
	cocos2d::Animate* walkleftanim4 = Animate::create(leftanimation4);
	walkleftanim4->retain();
	Animation* rightanimation4 = Animation::createWithSpriteFrames(walkrightanimFrames4, 0.1f);
	cocos2d::Animate* walkrightanim4 = Animate::create(rightanimation4);
	walkrightanim4->retain();


	Animation* paintanimation4 = Animation::createWithSpriteFrames(paintFrames4, 0.1f);
	Animate* paintanim4 = Animate::create(paintanimation4);
	paintanim4->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4up"), walkupanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4down"), walkdownanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4left"), walkleftanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4right"), walkrightanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4paint"), paintanim4));


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//sam animations
	Vector<SpriteFrame*> samupanimFrames;
	samupanimFrames.reserve(4);
	Vector<SpriteFrame*> samdownanimFrames;
	samdownanimFrames.reserve(4);
	Vector<SpriteFrame*> samleftanimFrames;
	samleftanimFrames.reserve(4);
	Vector<SpriteFrame*> samrightanimFrames;
	samrightanimFrames.reserve(4);
	
	samupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_back_0.png", Rect(0, 0, 24, 48)));
	samupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_back_1.png", Rect(0, 0, 24, 48)));
	samupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_back_2.png", Rect(0, 0, 24, 48)));
	samupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_back_3.png", Rect(0, 0, 24, 48)));
	samupanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_front_0.png", Rect(0, 0, 24, 48)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_front_1.png", Rect(0, 0, 24, 48)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_front_2.png", Rect(0, 0, 24, 48)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_front_3.png", Rect(0, 0, 24, 48)));
	samdownanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_left_0.png", Rect(0, 0, 24, 48)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_left_1.png", Rect(0, 0, 24, 48)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_left_2.png", Rect(0, 0, 24, 48)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_left_3.png", Rect(0, 0, 24, 48)));
	samleftanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_right_0.png", Rect(0, 0, 24, 48)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_right_1.png", Rect(0, 0, 24, 48)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_right_2.png", Rect(0, 0, 24, 48)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_right_3.png", Rect(0, 0, 24, 48)));
	samrightanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(3)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* samupanimation = Animation::createWithSpriteFrames(samupanimFrames, 0.1f);
	cocos2d::Animate* samupanim = Animate::create(samupanimation);
	samupanim->retain();
	Animation* samdownanimation = Animation::createWithSpriteFrames(samdownanimFrames, 0.1f);
	cocos2d::Animate* samdownanim = Animate::create(samdownanimation);
	samdownanim->retain();
	Animation* samleftanimation = Animation::createWithSpriteFrames(samleftanimFrames, 0.1f);
	cocos2d::Animate* samleftanim = Animate::create(samleftanimation);
	samleftanim->retain();
	Animation* samrightanimation = Animation::createWithSpriteFrames(samrightanimFrames, 0.1f);
	cocos2d::Animate* samrightanim = Animate::create(samrightanimation);
	samrightanim->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("samup"), samupanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samdown"), samdownanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samleft"), samleftanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samright"), samrightanim));
	

	charstringmap.insert(boost::bimap<char, std::string>::value_type(0, ""));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(1, "p1up"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(2, "p1down"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(3, "p1left"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(4, "p1right"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(5, "p1paint"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(6, "p1hit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(7, "p2up"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(8, "p2down"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(9, "p2left"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(10, "p2right"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(11, "p2paint"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(12, "p2hit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(13, "p3up"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(14, "p3down"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(15, "p3left"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(16, "p3right"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(17, "p3paint"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(18, "p3hit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(19, "p4up"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(20, "p4down"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(21, "p4left"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(22, "p4right"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(23, "p4paint"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(24, "p4hit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(19, "samup"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(20, "samdown"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(21, "samleft"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(22, "samright"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(23, "samwarp"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(24, "samhit"));




}