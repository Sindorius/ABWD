//
//  EventJoystick.h
//  cocos2d_libs
//
//  Created by Chad Ata on 5/21/14.
//
//

#ifndef __cocos2d_libs__EventJoystick__
#define __cocos2d_libs__EventJoystick__
#include "glfw3.h"
#include "base/CCEvent.h"


NS_CC_BEGIN
/**
 * Data returned in this class is based off of the GLFW joystick API
 * http://www.glfw.org/docs/latest/group__input.html#gaffcbd9ac8ee737fcdd25475123a3c790
 */
class EventJoystick : public Event
{
public:
enum BUTTON_STATES
{
RELEASED = GLFW_RELEASE
};

EventJoystick();

void setPresent(bool present);
void setName(const char* name);
void setId(int id);
void setButtonValues(int count, const unsigned char* buttonValues);
void setAxes(int count, const float* axes);

bool isPresent();
const char* getName();
int getId();
const unsigned char* getButtonValues(int* count);
const float* getAxes(int* count);

private:
bool _isPresent;
const char* name;
int id;
int buttonValuesCount;
const unsigned char* buttonValues;
// e.g. ps3: left: x,y right:x,y x (left)-1<=x<=1(right) (up)-1<=y<=1(down)
int axesCount;
const float* axes;
};
NS_CC_END
#endif /* defined(__cocos2d_libs__EventJoystick__) */
