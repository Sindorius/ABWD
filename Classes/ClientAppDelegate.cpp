#include "ClientAppDelegate.h"
#include "ClientDemoScene.h"
#include "MenuScene.h"

#define FULLSCREEN 0

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(640, 360);


ClientAppDelegate::ClientAppDelegate() {

}

ClientAppDelegate::~ClientAppDelegate() 
{
	
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void ClientAppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use packages manager to install more packages, 
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool ClientAppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		if (FULLSCREEN)
		{
			glview = GLViewImpl::createWithFullScreen("A Brush with Danger");
		}
		else
		{
			glview = GLViewImpl::create("A Brush with Danger");
		}
        director->setOpenGLView(glview);
    }
	auto screenSize = glview->getVisibleSize();

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 30.0f);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);

	glview->setFrameSize(designResolutionSize.width, designResolutionSize.height);

	if (FULLSCREEN)
	{
		//adjusts zoom factor for all resolutions, though for resolutions above 1080p might have too much aliasing
		director->getOpenGLView()->setFrameZoomFactor(screenSize.height/designResolutionSize.height);
	}
	else
	{
		director->getOpenGLView()->setFrameZoomFactor(2.0f);
	}
	//director->setProjection(cocos2d::Director::Projection::_2D);
    register_all_packages();

    // create a scene. it's an autorelease object
    //auto scene = ClientDemo::createScene();
	auto scene = MenuScene::createMenu();


	// run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void ClientAppDelegate::applicationDidEnterBackground() {
    //Director::getInstance()->stopAnimation();
	CCDirector::sharedDirector()->pause();
	experimental::AudioEngine::pauseAll();
}

// this function will be called when the app is active again
void ClientAppDelegate::applicationWillEnterForeground() {
    //Director::getInstance()->startAnimation();
	CCDirector::sharedDirector()->resume();
	experimental::AudioEngine::resumeAll();
}
