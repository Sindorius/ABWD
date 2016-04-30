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
	Vector<SpriteFrame*> idleanimFrames;
	idleanimFrames.reserve(4);
	
	walkupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_up0.png", Rect(0, 0, 24, 48)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_up1.png", Rect(0, 0, 24, 48)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_up2.png", Rect(0, 0, 24, 48)));
	walkupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_up3.png", Rect(0, 0, 24, 48)));
	walkupanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_down0.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_down1.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_down2.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_down3.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_left0.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_left1.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_left2.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_left3.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_right0.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_right1.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_right2.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_walking_right3.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames.at(3)->getTexture()->setAliasTexParameters();

	paintFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_painting_left0.png", Rect(0, 0, 23, 33)));
	paintFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_painting_left1.png", Rect(0, 0, 23, 33)));
	paintFrames.at(0)->getTexture()->setAliasTexParameters();
	paintFrames.at(1)->getTexture()->setAliasTexParameters();

	idleanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_idle_front0.png", Rect(0, 0, 25, 47)));
	idleanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_idle_front1.png", Rect(0, 0, 25, 47)));
	idleanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_idle_front2.png", Rect(0, 0, 25, 47)));
	idleanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_red_idle_front3.png", Rect(0, 0, 25, 47)));
	idleanimFrames.at(0)->getTexture()->setAliasTexParameters();
	idleanimFrames.at(1)->getTexture()->setAliasTexParameters();
	idleanimFrames.at(2)->getTexture()->setAliasTexParameters();
	idleanimFrames.at(3)->getTexture()->setAliasTexParameters();


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

	Animation* idleanimation = Animation::createWithSpriteFrames(idleanimFrames, 0.2f);
	cocos2d::Animate* idleanim = Animate::create(idleanimation);
	idleanim->retain();

	animationmap.insert(std::pair<std::string,Animate*>(std::string("p1up"), walkupanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1down"), walkdownanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1left"), walkleftanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1right"), walkrightanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1paint"), paintanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p1idle"), idleanim));



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
	Vector<SpriteFrame*> idleanimFrames2;
	idleanimFrames2.reserve(4);
	

	walkupanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_up0.png", Rect(0, 0, 24, 48)));
	walkupanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_up1.png", Rect(0, 0, 24, 48)));
	walkupanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_up2.png", Rect(0, 0, 24, 48)));
	walkupanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_up3.png", Rect(0, 0, 24, 48)));
	walkupanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames2.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down0.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down1.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down2.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_down3.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames2.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_left0.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_left1.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_left2.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_left3.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames2.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_right0.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_right1.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_right2.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_walking_right3.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames2.at(3)->getTexture()->setAliasTexParameters();

	paintFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_painting_left0.png", Rect(0, 0, 23, 33)));
	paintFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_painting_left1.png", Rect(0, 0, 23, 33)));
	paintFrames2.at(0)->getTexture()->setAliasTexParameters();
	paintFrames2.at(1)->getTexture()->setAliasTexParameters();

	idleanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_idle_front0.png", Rect(0, 0, 25, 47)));
	idleanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_idle_front1.png", Rect(0, 0, 25, 47)));
	idleanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_idle_front2.png", Rect(0, 0, 25, 47)));
	idleanimFrames2.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_blue_idle_front3.png", Rect(0, 0, 25, 47)));
	idleanimFrames2.at(0)->getTexture()->setAliasTexParameters();
	idleanimFrames2.at(1)->getTexture()->setAliasTexParameters();
	idleanimFrames2.at(2)->getTexture()->setAliasTexParameters();
	idleanimFrames2.at(3)->getTexture()->setAliasTexParameters();


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

	Animation* idleanimation2 = Animation::createWithSpriteFrames(idleanimFrames2, 0.2f);
	cocos2d::Animate* idleanim2 = Animate::create(idleanimation2);
	idleanim2->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2up"), walkupanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2down"), walkdownanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2left"), walkleftanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2right"), walkrightanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2paint"), paintanim2));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p2idle"), idleanim2));




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
	Vector<SpriteFrame*> idleanimFrames3;
	idleanimFrames3.reserve(4);

	walkupanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_up0.png", Rect(0, 0, 24, 48)));
	walkupanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_up1.png", Rect(0, 0, 24, 48)));
	walkupanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_up2.png", Rect(0, 0, 24, 48)));
	walkupanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_up3.png", Rect(0, 0, 24, 48)));
	walkupanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames3.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_down0.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_down1.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_down2.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_down3.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames3.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_left0.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_left1.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_left2.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_left3.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames3.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_right0.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_right1.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_right2.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_walking_right3.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames3.at(3)->getTexture()->setAliasTexParameters();

	paintFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_painting_left0.png", Rect(0, 0, 23, 33)));
	paintFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_painting_left1.png", Rect(0, 0, 23, 33)));
	paintFrames3.at(0)->getTexture()->setAliasTexParameters();
	paintFrames3.at(1)->getTexture()->setAliasTexParameters();

	idleanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_idle_front0.png", Rect(0, 0, 25, 47)));
	idleanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_idle_front1.png", Rect(0, 0, 25, 47)));
	idleanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_idle_front2.png", Rect(0, 0, 25, 47)));
	idleanimFrames3.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_green_idle_front3.png", Rect(0, 0, 25, 47)));
	idleanimFrames3.at(0)->getTexture()->setAliasTexParameters();
	idleanimFrames3.at(1)->getTexture()->setAliasTexParameters();
	idleanimFrames3.at(2)->getTexture()->setAliasTexParameters();
	idleanimFrames3.at(3)->getTexture()->setAliasTexParameters();



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

	Animation* idleanimation3 = Animation::createWithSpriteFrames(idleanimFrames3, 0.2f);
	cocos2d::Animate* idleanim3 = Animate::create(idleanimation3);
	idleanim3->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3up"), walkupanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3down"), walkdownanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3left"), walkleftanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3right"), walkrightanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3paint"), paintanim3));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p3idle"), idleanim3));




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
	Vector<SpriteFrame*> idleanimFrames4;
	idleanimFrames4.reserve(4);
	
	walkupanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_up0.png", Rect(0, 0, 24, 48)));
	walkupanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_up1.png", Rect(0, 0, 24, 48)));
	walkupanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_up2.png", Rect(0, 0, 24, 48)));
	walkupanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_up3.png", Rect(0, 0, 24, 48)));
	walkupanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkupanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkupanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkupanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walkdownanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down0.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down1.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down2.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_down3.png", Rect(0, 0, 24, 46)));
	walkdownanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkdownanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkdownanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkdownanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walkleftanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_left0.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_left1.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_left2.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_left3.png", Rect(0, 0, 22, 47)));
	walkleftanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkleftanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkleftanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkleftanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walkrightanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_right0.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_right1.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_right2.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_walking_right3.png", Rect(0, 0, 22, 47)));
	walkrightanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkrightanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkrightanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkrightanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	paintFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_painting_left0.png", Rect(0, 0, 23, 33)));
	paintFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_painting_left1.png", Rect(0, 0, 23, 33)));
	paintFrames4.at(0)->getTexture()->setAliasTexParameters();
	paintFrames4.at(1)->getTexture()->setAliasTexParameters();

	idleanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_idle_front0.png", Rect(0, 0, 25, 47)));
	idleanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_idle_front1.png", Rect(0, 0, 25, 47)));
	idleanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_idle_front2.png", Rect(0, 0, 25, 47)));
	idleanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\char_yellow_idle_front3.png", Rect(0, 0, 25, 47)));
	idleanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	idleanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	idleanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	idleanimFrames4.at(3)->getTexture()->setAliasTexParameters();

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

	Animation* idleanimation4 = Animation::createWithSpriteFrames(idleanimFrames4, 0.2f);
	cocos2d::Animate* idleanim4 = Animate::create(idleanimation4);
	idleanim4->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4up"), walkupanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4down"), walkdownanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4left"), walkleftanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4right"), walkrightanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4paint"), paintanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("p4idle"), idleanim4));

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//inverted/hit player anims

	Vector<SpriteFrame*> walkuphitanimFrames4;
	walkuphitanimFrames4.reserve(4);
	Vector<SpriteFrame*> walkdownhitanimFrames4;
	walkdownhitanimFrames4.reserve(4);
	Vector<SpriteFrame*> walklefthitanimFrames4;
	walklefthitanimFrames4.reserve(4);
	Vector<SpriteFrame*> walkrighthitanimFrames4;
	walkrighthitanimFrames4.reserve(4);
	Vector<SpriteFrame*> painthitFrames4;
	painthitFrames4.reserve(1);
	Vector<SpriteFrame*> idlehitanimFrames4;
	idlehitanimFrames4.reserve(4);

	walkuphitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_up0.png", Rect(0, 0, 24, 48)));
	walkuphitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_up1.png", Rect(0, 0, 24, 48)));
	walkuphitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_up2.png", Rect(0, 0, 24, 48)));
	walkuphitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_up3.png", Rect(0, 0, 24, 48)));
	walkuphitanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkuphitanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkuphitanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkuphitanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walkdownhitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_down0.png", Rect(0, 0, 24, 46)));
	walkdownhitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_down1.png", Rect(0, 0, 24, 46)));
	walkdownhitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_down2.png", Rect(0, 0, 24, 46)));
	walkdownhitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_down3.png", Rect(0, 0, 24, 46)));
	walkdownhitanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkdownhitanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkdownhitanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkdownhitanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walklefthitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_left0.png", Rect(0, 0, 22, 47)));
	walklefthitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_left1.png", Rect(0, 0, 22, 47)));
	walklefthitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_left2.png", Rect(0, 0, 22, 47)));
	walklefthitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_left3.png", Rect(0, 0, 22, 47)));
	walklefthitanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walklefthitanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walklefthitanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walklefthitanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	walkrighthitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_right0.png", Rect(0, 0, 22, 47)));
	walkrighthitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_right1.png", Rect(0, 0, 22, 47)));
	walkrighthitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_right2.png", Rect(0, 0, 22, 47)));
	walkrighthitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_walking_right3.png", Rect(0, 0, 22, 47)));
	walkrighthitanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	walkrighthitanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	walkrighthitanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	walkrighthitanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	painthitFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_painting_left0.png", Rect(0, 0, 23, 33)));
	painthitFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_painting_left1.png", Rect(0, 0, 23, 33)));
	painthitFrames4.at(0)->getTexture()->setAliasTexParameters();
	painthitFrames4.at(1)->getTexture()->setAliasTexParameters();

	idlehitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_idle_front0.png", Rect(0, 0, 25, 47)));
	idlehitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_idle_front1.png", Rect(0, 0, 25, 47)));
	idlehitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_idle_front2.png", Rect(0, 0, 25, 47)));
	idlehitanimFrames4.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\main_characters\\inv\\char_default_idle_front3.png", Rect(0, 0, 25, 47)));
	idlehitanimFrames4.at(0)->getTexture()->setAliasTexParameters();
	idlehitanimFrames4.at(1)->getTexture()->setAliasTexParameters();
	idlehitanimFrames4.at(2)->getTexture()->setAliasTexParameters();
	idlehitanimFrames4.at(3)->getTexture()->setAliasTexParameters();

	// create the animation out of the frames
	Animation* uphitanimation4 = Animation::createWithSpriteFrames(walkuphitanimFrames4, 0.1f);
	cocos2d::Animate* walkuphitanim4 = Animate::create(uphitanimation4);
	walkuphitanim4->retain();
	Animation* downhitanimation4 = Animation::createWithSpriteFrames(walkdownhitanimFrames4, 0.1f);
	cocos2d::Animate* walkdownhitanim4 = Animate::create(downhitanimation4);
	walkdownhitanim4->retain();
	Animation* lefthitanimation4 = Animation::createWithSpriteFrames(walklefthitanimFrames4, 0.1f);
	cocos2d::Animate* walklefthitanim4 = Animate::create(lefthitanimation4);
	walklefthitanim4->retain();
	Animation* righthitanimation4 = Animation::createWithSpriteFrames(walkrighthitanimFrames4, 0.1f);
	cocos2d::Animate* walkrighthitanim4 = Animate::create(righthitanimation4);
	walkrighthitanim4->retain();


	Animation* painthitanimation4 = Animation::createWithSpriteFrames(painthitFrames4, 0.1f);
	Animate* painthitanim4 = Animate::create(painthitanimation4);
	painthitanim4->retain();

	Animation* idlehitanimation4 = Animation::createWithSpriteFrames(idlehitanimFrames4, 0.2f);
	cocos2d::Animate* idlehitanim4 = Animate::create(idlehitanimation4);
	idlehitanim4->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("puphit"), walkuphitanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("pdownhit"), walkdownhitanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("plefthit"), walklefthitanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("prighthit"), walkrighthitanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("ppainthit"), painthitanim4));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("pidlehit"), idlehitanim4));


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
	Vector<SpriteFrame*> samTeleportFrames;
	samTeleportFrames.reserve(11);
	Vector<SpriteFrame*> samAppearFrames;
	samAppearFrames.reserve(5);
	Vector<SpriteFrame*> samWhistleFrames;
	samWhistleFrames.reserve(2);
	Vector<SpriteFrame*> samMunchFrames;
	samMunchFrames.reserve(2);
	
	samupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_back0.png", Rect(0, 0, 21, 38)));
	samupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_back1.png", Rect(0, 0, 21, 38)));
	samupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_back2.png", Rect(0, 0, 21, 38)));
	samupanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_back3.png", Rect(0, 0, 21, 38)));
	samupanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samupanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_front0.png", Rect(0, 0, 24, 48)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_front1.png", Rect(0, 0, 24, 48)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_front2.png", Rect(0, 0, 24, 48)));
	samdownanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_front3.png", Rect(0, 0, 24, 48)));
	samdownanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samdownanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_left0.png", Rect(0, 0, 15, 38)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_left1.png", Rect(0, 0, 15, 38)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_left2.png", Rect(0, 0, 15, 38)));
	samleftanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_left3.png", Rect(0, 0, 15, 38)));
	samleftanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samleftanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_right0.png", Rect(0, 0, 15, 38)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_right1.png", Rect(0, 0, 15, 38)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_right2.png", Rect(0, 0, 15, 38)));
	samrightanimFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_walk_right3.png", Rect(0, 0, 15, 38)));
	samrightanimFrames.at(0)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(1)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(2)->getTexture()->setAliasTexParameters();
	samrightanimFrames.at(3)->getTexture()->setAliasTexParameters();

	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport0.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport1.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport2.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport3.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport4.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport5.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport6.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport7.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport8.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport9.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport10.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport11.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport12.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport13.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport14.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport15.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport16.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport17.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport18.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport19.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport20.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport21.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport22.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport23.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport24.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport25.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport26.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport27.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport28.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport29.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport30.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport31.png", Rect(0, 0, 24, 48)));
	samTeleportFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_teleport32.png", Rect(0, 0, 24, 48)));

	samTeleportFrames.at(0)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(1)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(2)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(3)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(4)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(5)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(6)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(7)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(8)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(9)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(10)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(11)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(12)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(13)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(14)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(15)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(16)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(17)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(18)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(19)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(20)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(21)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(22)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(23)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(24)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(25)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(26)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(27)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(28)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(29)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(30)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(31)->getTexture()->setAliasTexParameters();
	samTeleportFrames.at(32)->getTexture()->setAliasTexParameters();

	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear0.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear1.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear2.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear3.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear4.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear5.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear6.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear7.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear8.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear9.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear10.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear11.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear12.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear13.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear14.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear15.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear16.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear17.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear18.png", Rect(0, 0, 24, 48)));
	samAppearFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_reappear19.png", Rect(0, 0, 24, 48)));


	samAppearFrames.at(0)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(1)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(2)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(3)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(4)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(5)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(6)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(7)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(8)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(9)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(10)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(11)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(12)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(13)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(14)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(15)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(16)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(17)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(18)->getTexture()->setAliasTexParameters();
	samAppearFrames.at(19)->getTexture()->setAliasTexParameters();


	samWhistleFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_whistle0.png", Rect(0, 0, 24, 48)));
	samWhistleFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_whistle1.png", Rect(0, 0, 24, 48)));

	samWhistleFrames.at(0)->getTexture()->setAliasTexParameters();
	samWhistleFrames.at(1)->getTexture()->setAliasTexParameters();


	samMunchFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_eating0.png", Rect(0, 0, 21, 37)));
	samMunchFrames.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\sam\\sam_eating1.png", Rect(0, 0, 21, 37)));

	samMunchFrames.at(0)->getTexture()->setAliasTexParameters();
	samMunchFrames.at(1)->getTexture()->setAliasTexParameters();

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
	Animation* samteleportanimation = Animation::createWithSpriteFrames(samTeleportFrames, 0.05f);
	cocos2d::Animate* samteleportanim = Animate::create(samteleportanimation);
	samteleportanim->retain();
	Animation* samappearanimation = Animation::createWithSpriteFrames(samAppearFrames, 0.05f);
	cocos2d::Animate* samappearanim = Animate::create(samappearanimation);
	samappearanim->retain();
	Animation* samwhistleanimation = Animation::createWithSpriteFrames(samWhistleFrames, 0.2f);
	cocos2d::Animate* samwhistleanim = Animate::create(samwhistleanimation);
	samwhistleanim->retain();
	Animation* sammunchanimation = Animation::createWithSpriteFrames(samMunchFrames, 0.2f);
	cocos2d::Animate* sammunchanim = Animate::create(sammunchanimation);
	sammunchanim->retain();



	animationmap.insert(std::pair<std::string, Animate*>(std::string("samup"), samupanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samdown"), samdownanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samleft"), samleftanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samright"), samrightanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samwarp"), samteleportanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samappear"), samappearanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("samwhistle"), samwhistleanim));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("sammunch"), sammunchanim));

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Pterodactyl animations
	Vector<SpriteFrame*> pteraLeft;
	samupanimFrames.reserve(7);
	Vector<SpriteFrame*> pteraRight;
	samdownanimFrames.reserve(7);
	Vector<SpriteFrame*> pteraANGRYLeft;
	samupanimFrames.reserve(7);
	Vector<SpriteFrame*> pteraANGRYRight;
	samdownanimFrames.reserve(7);

	pteraLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_left0.png", Rect(0, 0, 25, 22)));
	pteraLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_left1.png", Rect(0, 0, 25, 22)));
	pteraLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_left2.png", Rect(0, 0, 25, 22)));
	pteraLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_left3.png", Rect(0, 0, 25, 22)));
	pteraLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_left4.png", Rect(0, 0, 25, 22)));
	pteraLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_left5.png", Rect(0, 0, 25, 22)));
	pteraLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_left6.png", Rect(0, 0, 25, 22)));

	pteraLeft.at(0)->getTexture()->setAliasTexParameters();
	pteraLeft.at(1)->getTexture()->setAliasTexParameters();
	pteraLeft.at(2)->getTexture()->setAliasTexParameters();
	pteraLeft.at(3)->getTexture()->setAliasTexParameters();
	pteraLeft.at(4)->getTexture()->setAliasTexParameters();
	pteraLeft.at(5)->getTexture()->setAliasTexParameters();
	pteraLeft.at(6)->getTexture()->setAliasTexParameters();

	pteraRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_right0.png", Rect(0, 0, 25, 22)));
	pteraRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_right1.png", Rect(0, 0, 25, 22)));
	pteraRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_right2.png", Rect(0, 0, 25, 22)));
	pteraRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_right3.png", Rect(0, 0, 25, 22)));
	pteraRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_right4.png", Rect(0, 0, 25, 22)));
	pteraRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_right5.png", Rect(0, 0, 25, 22)));
	pteraRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\pteradactyl_right6.png", Rect(0, 0, 25, 22)));

	pteraRight.at(0)->getTexture()->setAliasTexParameters();
	pteraRight.at(1)->getTexture()->setAliasTexParameters();
	pteraRight.at(2)->getTexture()->setAliasTexParameters();
	pteraRight.at(3)->getTexture()->setAliasTexParameters();
	pteraRight.at(4)->getTexture()->setAliasTexParameters();
	pteraRight.at(5)->getTexture()->setAliasTexParameters();
	pteraRight.at(6)->getTexture()->setAliasTexParameters();

	pteraANGRYLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_left0.png", Rect(0, 0, 25, 22)));
	pteraANGRYLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_left1.png", Rect(0, 0, 25, 22)));
	pteraANGRYLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_left2.png", Rect(0, 0, 25, 22)));
	pteraANGRYLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_left3.png", Rect(0, 0, 25, 22)));
	pteraANGRYLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_left4.png", Rect(0, 0, 25, 22)));
	pteraANGRYLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_left5.png", Rect(0, 0, 25, 22)));
	pteraANGRYLeft.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_left6.png", Rect(0, 0, 25, 22)));

	pteraANGRYLeft.at(0)->getTexture()->setAliasTexParameters();
	pteraANGRYLeft.at(1)->getTexture()->setAliasTexParameters();
	pteraANGRYLeft.at(2)->getTexture()->setAliasTexParameters();
	pteraANGRYLeft.at(3)->getTexture()->setAliasTexParameters();
	pteraANGRYLeft.at(4)->getTexture()->setAliasTexParameters();
	pteraANGRYLeft.at(5)->getTexture()->setAliasTexParameters();
	pteraANGRYLeft.at(6)->getTexture()->setAliasTexParameters();

	pteraANGRYRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_right0.png", Rect(0, 0, 25, 22)));
	pteraANGRYRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_right1.png", Rect(0, 0, 25, 22)));
	pteraANGRYRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_right2.png", Rect(0, 0, 25, 22)));
	pteraANGRYRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_right3.png", Rect(0, 0, 25, 22)));
	pteraANGRYRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_right4.png", Rect(0, 0, 25, 22)));
	pteraANGRYRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_right5.png", Rect(0, 0, 25, 22)));
	pteraANGRYRight.pushBack(SpriteFrame::create("\\res\\sprites\\animations\\pteradactyl\\angry_pteradactyl_right6.png", Rect(0, 0, 25, 22)));

	pteraANGRYRight.at(0)->getTexture()->setAliasTexParameters();
	pteraANGRYRight.at(1)->getTexture()->setAliasTexParameters();
	pteraANGRYRight.at(2)->getTexture()->setAliasTexParameters();
	pteraANGRYRight.at(3)->getTexture()->setAliasTexParameters();
	pteraANGRYRight.at(4)->getTexture()->setAliasTexParameters();
	pteraANGRYRight.at(5)->getTexture()->setAliasTexParameters();
	pteraANGRYRight.at(6)->getTexture()->setAliasTexParameters();

	Animation* pteraleftanim = Animation::createWithSpriteFrames(pteraLeft, 0.1f);
	cocos2d::Animate* pteraleftanimation = Animate::create(pteraleftanim);
	pteraleftanimation->retain();
	Animation* pterarightanim = Animation::createWithSpriteFrames(pteraRight, 0.1f);
	cocos2d::Animate* pterarightanimation = Animate::create(pterarightanim);
	pterarightanimation->retain();
	Animation* pteraANGRYleftanim = Animation::createWithSpriteFrames(pteraANGRYLeft, 0.1f);
	cocos2d::Animate* pteraANGRYleftanimation = Animate::create(pteraANGRYleftanim);
	pteraANGRYleftanimation->retain();
	Animation* pteraANGRYrightanim = Animation::createWithSpriteFrames(pteraANGRYRight, 0.1f);
	cocos2d::Animate* pteraANGRYrightanimation = Animate::create(pteraANGRYrightanim);
	pteraANGRYrightanimation->retain();


	animationmap.insert(std::pair<std::string, Animate*>(std::string("pteraleft"), pteraleftanimation));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("pteraright"), pterarightanimation));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("pteraANGRYleft"), pteraANGRYleftanimation));
	animationmap.insert(std::pair<std::string, Animate*>(std::string("pteraANGRYright"), pteraANGRYrightanimation));


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//altogether now


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
	charstringmap.insert(boost::bimap<char, std::string>::value_type(25, "samup"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(26, "samdown"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(27, "samleft"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(28, "samright"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(29, "samwarp"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(30, "samappear"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(31, "samwhistle"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(32, "samhit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(33, "pteraleft"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(34, "pteraright"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(35, "p1idle"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(36, "p2idle"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(37, "p3idle"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(38, "p4idle"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(39, "sammunch"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(40, "pteraANGRYleft"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(41, "pteraANGRYright"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(42, "puphit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(43, "pdownhit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(44, "plefthit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(45, "prighthit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(46, "ppainthit"));
	charstringmap.insert(boost::bimap<char, std::string>::value_type(47, "pidlehit"));






}