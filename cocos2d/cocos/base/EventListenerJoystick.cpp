//  EventListenerJoystick.cpp
//  cocos2d_libs
//
//  Created by Chad Ata on 5/21/14.
//
//
//#include "glew.h"
#include "EventListenerJoystick.h"
//#include "cocos2d.h"
NS_CC_BEGIN

const std::string EventListenerJoystick::LISTENER_ID = "__cc_joystick";

bool EventListenerJoystick::checkAvailable()
{
return true;
}

EventListenerJoystick* EventListenerJoystick::clone()
{
auto ret = new EventListenerJoystick();
if (ret && ret->init())
{
ret->autorelease();
ret->onEvent = onEvent;
}
else
{
CC_SAFE_DELETE(ret);
}
return ret;
}
EventListenerJoystick* EventListenerJoystick::create()
{
auto ret = new EventListenerJoystick();
if (ret && ret->init())
{
ret->autorelease();
}
else
{
CC_SAFE_DELETE(ret);
}
return ret;
}


EventListenerJoystick::EventListenerJoystick() : onEvent(nullptr)
{
}

bool EventListenerJoystick::init()
{
auto listener = [this](Event* event){
if (onEvent != nullptr)
onEvent(event);
};

if (EventListener::init(Type::JOYSTICK, LISTENER_ID, listener))
{
return true;
}

return false;
}

NS_CC_END
