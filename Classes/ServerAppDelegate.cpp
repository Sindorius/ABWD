#include "ServerAppDelegate.h"
#include "ServerDemoScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(640, 360);


ServerAppDelegate::ServerAppDelegate() {

}

ServerAppDelegate::~ServerAppDelegate() 
{
	
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void ServerAppDelegate::initGLContextAttrs()
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

bool ServerAppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("A Brush With Danger Server");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::SHOW_ALL);
	glview->setFrameSize(designResolutionSize.width, designResolutionSize.height);
	director->getOpenGLView()->setFrameZoomFactor(2.0f);


    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = ServerDemo::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void ServerAppDelegate::applicationDidEnterBackground() {
    //Director::getInstance()->stopAnimation();

}

// this function will be called when the app is active again
void ServerAppDelegate::applicationWillEnterForeground() {
    //Director::getInstance()->startAnimation();

}
