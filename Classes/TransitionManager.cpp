#include "TransitionManager.h"

void TransitionManager::loadTransition(int level)
{
	experimental::AudioEngine::play2d("\\res\\sound\\sfx\\puzzle_solved.mp3");
	if (level == 1)
	{
		transitionSprite.clear();
		float winSizeWidth = Director::getInstance()->getWinSize().width / 2;
		float winSizeHeight = Director::getInstance()->getWinSize().height / 2;

		Sprite* screen = Sprite::create("res/sprites/ui/transition_screen.png");
		screen->getTexture()->setAliasTexParameters();
		screen->setPosition(Vec2(winSizeWidth, winSizeHeight));
		screen->setScale(1.0f);
		transitionSprite.push_back(screen);

	}
	if (level == 2)
	{
		transitionSprite.clear();
		float winSizeWidth = Director::getInstance()->getWinSize().width / 2;
		float winSizeHeight = Director::getInstance()->getWinSize().height / 2;

		Sprite* screen = Sprite::create("res/sprites/ui/transition_screen.png");
		screen->getTexture()->setAliasTexParameters();
		screen->setPosition(Vec2(winSizeWidth, winSizeHeight));
		screen->setScale(1.0f);
		transitionSprite.push_back(screen);

	}
	else if (level == 3)
	{
		transitionSprite.clear();
		float winSizeWidth = Director::getInstance()->getWinSize().width / 2;
		float winSizeHeight = Director::getInstance()->getWinSize().height / 2;

		Sprite* screen = Sprite::create("res/sprites/ui/transition_screen.png");
		screen->getTexture()->setAliasTexParameters();
		screen->setPosition(Vec2(winSizeWidth, winSizeHeight));
		screen->setScale(1.0f);
		transitionSprite.push_back(screen);
	}
	else if (level == 4)
	{
		transitionSprite.clear();
		float winSizeWidth = Director::getInstance()->getWinSize().width / 2;
		float winSizeHeight = Director::getInstance()->getWinSize().height / 2;

		Sprite* screen = Sprite::create("res/sprites/ui/transition_screen.png");
		screen->getTexture()->setAliasTexParameters();
		screen->setPosition(Vec2(winSizeWidth, winSizeHeight));
		screen->setScale(1.0f);
		transitionSprite.push_back(screen);
	}
	else
	{}

}

bool TransitionManager::timer_status()
{
	if (start_timer > 0)
	{
		start_timer--;
		return false;
	}
	else if (start_timer <= 0)
	{
		return true;
	}
}