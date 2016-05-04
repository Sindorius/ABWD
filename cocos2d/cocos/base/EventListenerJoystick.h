//  EventListenerJoystick.h
//  cocos2d_libs
//
//  Created by Chad Ata on 5/21/14.
//
//

#ifndef __cocos2d_libs__EventListenerJoystick__
#define __cocos2d_libs__EventListenerJoystick__

#include "base/CCEventListener.h"
#include "base/EventJoystick.h"

NS_CC_BEGIN

class Event;

class EventListenerJoystick : public EventListener
{
public:
static const std::string LISTENER_ID;
static EventListenerJoystick* create();

    /// Overrides
virtual EventListenerJoystick* clone() override;
virtual bool checkAvailable() override;

std::function<void(Event* event)> onEvent;

private:
EventListenerJoystick();
bool init();
};

NS_CC_END



#endif /* defined(__cocos2d_libs__EventListenerJoystick__) */
