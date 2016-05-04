#include "GameMenu.h"

#define DEFAULT_OPACITY 220
#define SELECTED_OPACITY 255

GameMenu* GameMenu::createGameMenu()
{
	//auto ptScene = Scene::create();
	auto ptlayer = GameMenu::create();

	//ptScene->addChild(ptlayer);

	return ptlayer;
}


bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//listeners init
	joyListener1 = EventListenerJoystick::create();
	joyListener1->onEvent = CC_CALLBACK_1(GameMenu::Joystick, this);
	_eventDispatcher->addEventListenerWithFixedPriority(joyListener1, 3);

	//keyListener1 = EventListenerKeyboard::create();
	//keyListener1->onKeyPressed = CC_CALLBACK_2(GameMenu::KeyDown, this);
	//keyListener1->onKeyReleased = CC_CALLBACK_2(GameMenu::KeyRelease, this);

	//_eventDispatcher->addEventListenerWithFixedPriority(keyListener1, 4);
	//listeners init end

	float winSizeWidth = Director::sharedDirector()->getWinSize().width / 2;
	float winSizeHeight = Director::sharedDirector()->getWinSize().height / 2;

	background = Sprite::create("\\res\\sprites\\ui\\black_screen.png");
	background->getTexture()->setAliasTexParameters();
	background->setPosition(Vec2(winSizeWidth, winSizeHeight));
	background->setScale(1.5f);
	background->setOpacity(150);
	this->addChild(background, 1);

	auto music_button = MenuItemImage::create("res//sprites//ui//music_on_button.png", "res//sprites//ui//music_on_button_p.png", CC_CALLBACK_1(GameMenu::music, this));
	music_button->setScale(0.5f);
	music_button->setOpacity(DEFAULT_OPACITY);
	buttons.push_back(music_button);

	auto sfx_button = MenuItemImage::create("res//sprites//ui//sfx_on_button.png", "res//sprites//ui//sfx_on_button_p.png", CC_CALLBACK_1(GameMenu::sfx, this));
	sfx_button->setScale(0.5f);
	sfx_button->setOpacity(DEFAULT_OPACITY);
	buttons.push_back(sfx_button);

	//below is only going to work as long as zoomfactor is a whole number between 1-3
	auto video_button = MenuItemImage::create("res//sprites//ui//video_button_" + std::to_string((int)zoomFactor) + ".png",
		"res//sprites//ui//video_button_" + std::to_string((int)zoomFactor) + "_p.png", CC_CALLBACK_1(GameMenu::video, this));
	video_button->setScale(0.5f);
	video_button->setOpacity(DEFAULT_OPACITY);
	buttons.push_back(video_button);

	auto exit_button = MenuItemImage::create("res//sprites//ui//exit_button.png", "res//sprites//ui//exit_button_p.png", CC_CALLBACK_1(GameMenu::exit, this));
	exit_button->setScale(0.5f);
	exit_button->setOpacity(DEFAULT_OPACITY);
	buttons.push_back(exit_button);

	auto resume_button = MenuItemImage::create("res//sprites//ui//resume_button.png", "res//sprites//ui//resume_button_p.png", CC_CALLBACK_1(GameMenu::resume, this));
	resume_button->setScale(0.5f);
	resume_button->setOpacity(DEFAULT_OPACITY);
	buttons.push_back(resume_button);

	menu = Menu::create(buttons[0], buttons[1], buttons[2], buttons[3], buttons[4], NULL);
	menu->alignItemsVerticallyWithPadding(5.0f);
	this->addChild(menu, 2);

	left_selector = Sprite::create("\\res\\sprites\\ui\\selection_arrow.png");
	left_selector->getTexture()->setAliasTexParameters();
	left_selector->setScale(0.5f);
	left_selector->setRotation(-180.0f);
	left_selector->setVisible(false);
	this->addChild(left_selector, 3);

	right_selector = Sprite::create("\\res\\sprites\\ui\\selection_arrow.png");
	right_selector->getTexture()->setAliasTexParameters();
	right_selector->setScale(0.5f);
	right_selector->setVisible(false);
	this->addChild(right_selector, 4);

	if (MUSIC_ON)
	{
		//create pause menu music...
		//experimental::AudioEngine::play2d("\\res\\sound\\music\\menu_music.mp3", true, 0.4f);
	}

	HideGameMenu();

	return true;
}

void GameMenu::music(Ref* pSender)
{
	Node* newNormal;
	Node* newSelected;
	//if music is on, change music button to "music off"
	if (bMusic) 
	{
		newNormal = Sprite::create("res//sprites//ui//music_off_button.png");
		newSelected = Sprite::create("res//sprites//ui//music_off_button_p.png");
		bMusic = false;
	}
	else
	{
		newNormal = Sprite::create("res//sprites//ui//music_on_button.png");
		newSelected = Sprite::create("res//sprites//ui//music_on_button_p.png");
		bMusic = true;
	}
	buttons[0]->setNormalImage(newNormal);
	buttons[0]->setSelectedImage(newSelected);
	//buttons[0]->selected();
}

void GameMenu::sfx(Ref* pSender)
{
	Node* newNormal;
	Node* newSelected;
	if (bSFX)
	{
		newNormal = Sprite::create("res//sprites//ui//sfx_off_button.png");
		newSelected = Sprite::create("res//sprites//ui//sfx_off_button_p.png");
		bSFX = false;
	}
	else
	{
		newNormal = Sprite::create("res//sprites//ui//sfx_on_button.png");
		newSelected = Sprite::create("res//sprites//ui//sfx_on_button_p.png");
		bSFX = true;
	}
	buttons[1]->setNormalImage(newNormal);
	buttons[1]->setSelectedImage(newSelected);
	//buttons[1]->selected();
}

void GameMenu::video(Ref* pSender)
{
	Node* newNormal;
	Node* newSelected;
	//if music is on, change music button to "music off"
	if (zoomFactor == 1.0f || zoomFactor == 2.0f)
	{
		zoomFactor += 1;
		newNormal = Sprite::create("res//sprites//ui//video_button_" + std::to_string((int)zoomFactor) + ".png");
		newSelected = Sprite::create("res//sprites//ui//video_button_" + std::to_string((int)zoomFactor) + "_p.png");
	}
	else if (zoomFactor == 3.0f)
	{
		zoomFactor = 1.0f;
		newNormal = Sprite::create("res//sprites//ui//video_button_" + std::to_string((int)zoomFactor) + ".png");
		newSelected = Sprite::create("res//sprites//ui//video_button_" + std::to_string((int)zoomFactor) + "_p.png");
	}
	//Director::getInstance()->getOpenGLView()->setFrameZoomFactor((float)zoomFactor);
	buttons[2]->setNormalImage(newNormal);
	buttons[2]->setSelectedImage(newSelected);
	//buttons[2]->selected();
}

void GameMenu::resume(Ref* pSender)
{
	bResume = !bResume;
}

void GameMenu::exit(Ref* pSender)
{
	bExit = !bExit;
}

void GameMenu::ShowGameMenu()
{
	//menu->setPosition(Camera::getDefaultCamera()->getPosition());
	//make the game menu visible 
	menu->setEnabled(true);
	menu->setVisible(true);
	background->setVisible(true);
	//this->setTouchEnabled(true);
	this->setVisible(true);
}

void GameMenu::HideGameMenu()
{
	//make the game menu visible 
	menu->setEnabled(false);
	menu->setVisible(false);
	background->setVisible(false);
	//this->setTouchEnabled(false);
	this->setVisible(false);
}

void GameMenu::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void GameMenu::Joystick(cocos2d::Event* event)
{
	if (menu->isEnabled())
	{
		EventJoystick* e = (EventJoystick*)event;
		//CCLOG("JOYSTICK PRESENT");
		bool present = e->isPresent();
		//CCLOG(std::to_string(present).c_str());
		if (present)
		{
			left_selector->setVisible(true);
			right_selector->setVisible(true);
			//default to top bottom 0
			//if (current_button == 999)
			//{
			//	current_button = 0; //set currently selected button to first button
				//buttons[current_button]->selected();
			//}
			if (timeDelay == 0) //so you dont skip screens if you hold down button too long on previous screen
			{
				//CCLOG(e->getName());
				int foraxis;
				const float* axisval = e->getAxes(&foraxis);
				float yval = axisval[1];
				//CCLOG(std::to_string(xval).c_str());
				bool nox = false;
				bool noy = false;
				//below if/else-if statements should check for d-pad too...
				//positive yval = down
				if (yval > 0.6)
				{
					CycleButtonsDown();
				}
				else if (yval < -0.6)
				{
					CycleButtonsUp();
				}
				int forbutton;
				const unsigned char* buttonval = e->getButtonValues(&forbutton);
				unsigned char b0 = buttonval[0];
				unsigned char b1 = buttonval[1];
				unsigned char b2 = buttonval[2];
				unsigned char b3 = buttonval[3];

				if (b0 || b1 || b2 || b3)
				{
					button1 = true; //for key_release code
					buttons[current_button]->selected();
				}

				if (button1 == true && !b0 && !b1 && !b2 && !b3) //button was pushed then released
				{
					//buttons[current_button]->unselected();
					buttons[current_button]->activate();
					buttons[current_button]->unselected();
					//buttons[current_button]->selected();
					button1 = false;
				}

			}
			if (timeDelay > 0)
			{
				timeDelay--;
			}
			event->stopPropagation();
		}
	}
}


/*void GameMenu::KeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (menu->isEnabled())
	{
		//default to top bottom 0
		if (current_button == 999)
		{
			current_button = 0; //set currently selected button to first button
		}
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_SPACE:
			buttons[current_button]->selected();
			break;
		case EventKeyboard::KeyCode::KEY_ENTER:
			buttons[current_button]->selected();
			break;
		default: break;
		}
		event->stopPropagation();
	}
}

void GameMenu::KeyRelease(EventKeyboard::KeyCode keyCode, Event* event)
{

switch (keyCode) {
case EventKeyboard::KeyCode::KEY_UP_ARROW:
	CycleButtonsUp();
	break;
case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	CycleButtonsDown();
	break;
case EventKeyboard::KeyCode::KEY_W:
	CycleButtonsUp();
	break;
case EventKeyboard::KeyCode::KEY_S:
	CycleButtonsDown();
	break;
case EventKeyboard::KeyCode::KEY_SPACE:
	buttons[current_button]->unselected();
	buttons[current_button]->activate();
	break;
case EventKeyboard::KeyCode::KEY_ENTER:
	buttons[current_button]->unselected();
	buttons[current_button]->activate();
	break;
}

event->stopPropagation();

}*/

//selects button above current, cycles to bottom button if currently at top button
void GameMenu::CycleButtonsUp(void)
{
	//unselect previous button
	buttons[current_button]->unselected();

	if (current_button > 0)
	{
		buttons[current_button]->setOpacity(DEFAULT_OPACITY);
		current_button--;
		buttons[current_button]->setOpacity(SELECTED_OPACITY);
		//buttons[current_button]->selected();
	}
	else if (current_button == 0) //start of menu reached, loop back to last menu item
	{
		//buttons[current_button]->unselected();
		buttons[current_button]->setOpacity(DEFAULT_OPACITY);
		current_button = buttons.size() - 1;
		buttons[current_button]->setOpacity(SELECTED_OPACITY);
		//buttons[current_button]->selected();
	}
	timeDelay = 8; //8 frames
}

//selects button below current, cycles to top button if currently at bottom button
void GameMenu::CycleButtonsDown(void)
{
	//unselect previous button
	buttons[current_button]->unselected();

	if (current_button < buttons.size() - 1)
	{
		buttons[current_button]->setOpacity(DEFAULT_OPACITY);
		current_button++;
		buttons[current_button]->setOpacity(SELECTED_OPACITY);
		//buttons[current_button]->selected();
	}
	else if (current_button == buttons.size() - 1) //end of menu reached, loop back to first menu item
	{
		//buttons[current_button]->unselected();
		buttons[current_button]->setOpacity(DEFAULT_OPACITY);
		current_button = 0;
		buttons[current_button]->setOpacity(SELECTED_OPACITY);
		//buttons[current_button]->selected();
	}
	timeDelay = 8; //8 frames
}

void GameMenu::SetMenuCamera(Vec2 pos)
{
	menu->setPosition(pos);
	background->setPosition(pos);

	Rect r = buttons[current_button]->getBoundingBox();

	//add menu coords below since button coords are relative to menu's
	left_selector->setPosition(Vec2(menu->getPositionX() + buttons[current_button]->getPositionX() - r.getMaxX() - 15, menu->getPositionY() + buttons[current_button]->getPositionY()));
	right_selector->setPosition(Vec2(menu->getPositionX() + buttons[current_button]->getPositionX() + r.getMaxX() + 15, menu->getPositionY() + buttons[current_button]->getPositionY()));
}

