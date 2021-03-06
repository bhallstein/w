/*
 * W - a tiny 2D game development library
 *
 * =================
 *  UIElement.cpp
 * =================
 *
 * Copyright (C) 2012 - Ben Hallstein - http://ben.am
 * Published under the MIT license: http://opensource.org/licenses/MIT
 *
 */

#include "UIElement.h"
#include "Messenger.h"
#include "Callback.h"
#include "DrawingClasses.h"
#include "Drawable.h"

W::UIElement::UIElement(const std::string &_name, W::Positioner _pos, View *_v) :
	name(_name), positioner(_pos), view(_v)
{
	//
}
W::UIElement::~UIElement()
{
  //
}

void W::UIElement::_updatePosition(v2i _s) {
	rct = positioner.refresh(_s);
	updatePosition();
}


/**********/
/* Button */
/**********/

W::Button::Button(std::string _name, W::Positioner _pos, View *_v) :
	UIElement(_name, _pos, _v),
	hover(false), active(false),
	buttonClickEvent(EventType::ButtonClick),
	btnrect(NULL)
{
	buttonClickEvent.payload = name;
	
	Callback cb(&Button::recEv, this);
	Messenger::subscribeInView(view, EventType::MouseMove, cb, &rct);
	Messenger::subscribeInView(view, EventType::LMouseDown, cb, &rct);
	Messenger::subscribeInView(view, EventType::LMouseUp, cb, &rct);
}
W::Button::~Button()
{
	if (btnrect) delete btnrect;
	Messenger::unsubscribeInView(view, EventType::MouseMove, this);
	Messenger::unsubscribeInView(view, EventType::LMouseDown, this);
	Messenger::unsubscribeInView(view, EventType::LMouseUp, this);
}
W::EventPropagation::T W::Button::recEv(W::Event ev) {
	using namespace EventType;
	
	if (ev.type == LMouseDown) {
		active = true;
		Messenger::requestPrivilegedEventResponderStatus(view, MouseMove, Callback(&Button::recEv, this));
		Messenger::requestPrivilegedEventResponderStatus(view, LMouseUp, Callback(&Button::recEv, this));
		btnrect->setCol(W::Colour::Red);
	}
	else if (ev.type == MouseMove) {
		if (active) {
			if (!rct.overlapsWith(ev.pos)) {
				hover = false;
				Messenger::relinquishPrivilegedEventResponderStatus(view, MouseMove, this);
				Messenger::relinquishPrivilegedEventResponderStatus(view, LMouseUp, this);
				btnrect->setCol(W::Colour::Black);
			}
		}
		else {
			hover = true;
		}
	}
	else if (ev.type == LMouseUp) {
		if (active) {
			active = false;
			Messenger::relinquishPrivilegedEventResponderStatus(view, MouseMove, this);
			Messenger::relinquishPrivilegedEventResponderStatus(view, LMouseUp, this);
			btnrect->setCol(W::Colour::Black);
			if (rct.overlapsWith(ev.pos)) {
				Messenger::dispatchEvent(buttonClickEvent);
			}
		}
	}
	
	return EventPropagation::ShouldStop;
}
void W::Button::updatePosition() {
  if (btnrect) {
    btnrect->setPos(rct.position);
    btnrect->setSz(rct.size);
  }
}
void W::Button::activate() {
	btnrect = new Rectangle(view, rct.position, rct.size, Colour::Black);
}
void W::Button::deactivate() {
	if (btnrect) {
		delete btnrect;
		btnrect = NULL;
	}
}


/**************/
/* TextButton */
/**************/

W::TextButton::TextButton(std::string _text, std::string name, W::Positioner pos, View *v) :
  W::Button(name, pos, v),
  str(_text)
{
  positioner.sizing_method_x = PosType::Fixed;
  positioner.sizing_method_y = PosType::Fixed;

  positioner.w = DRetroText::widthForStr(str) + 20;
  positioner.h = 24;
}
W::TextButton::~TextButton()
{
  if (btntext) {
    delete btntext;
  }
}

void W::TextButton::updatePosition() {
  Button::updatePosition();
  if (btntext) {
    btntext->setPos(rct.position + v2i{10, 6});
  }
}
void W::TextButton::activate() {
  Button::activate();
  btntext = new RetroText(view,
                          rct.position,
                          str,
                          Colour::White,
                          TextAlign::Left);
}
void W::TextButton::deactivate() {
  Button::deactivate();
  if (btntext) {
    delete btntext;
    btntext = NULL;
  }
}
