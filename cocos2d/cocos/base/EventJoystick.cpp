//
//  EventJoystick.cpp
//  cocos2d_libs
//
//  Created by Chad Ata on 5/21/14.
//
//

#include "EventJoystick.h"
//#include "cocos2d.h"
NS_CC_BEGIN
EventJoystick::EventJoystick() : Event(Type::JOYSTICK)
{
_isPresent = false;
name = NULL;
buttonValuesCount = 0;
buttonValues = NULL;
axesCount = 0;
axes = NULL;

}

void EventJoystick::setPresent(bool present)
{
this->_isPresent = present;
}

void EventJoystick::setName(const char* n)
{
this->name = n;
}

void EventJoystick::setId(int i)
{
this->id = i;
}

void EventJoystick::setButtonValues(int count, const unsigned char* bv)
{
this->buttonValuesCount = count;
this->buttonValues = bv;
}

void EventJoystick::setAxes(int count, const float* a)
{
this->axesCount = count;
this->axes = a;
}

bool EventJoystick::isPresent()
{
return _isPresent;
}

const char* EventJoystick::getName()
{
return name;
}

int EventJoystick::getId()
{
return id;
}

const unsigned char* EventJoystick::getButtonValues(int* count)
{
*count = buttonValuesCount;
return buttonValues;
}

const float* EventJoystick::getAxes(int* count)
 {
*count = axesCount;
return axes;
}

NS_CC_END
