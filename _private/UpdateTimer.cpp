/*
 * W - a tiny 2D game development library
 *
 * ===================
 *  UpdateTimer.cpp
 * ===================
 *
 * Copyright (C) 2012 - Ben Hallstein - http://ben.am
 * Published under the MIT license: http://opensource.org/licenses/MIT
 *
 */

#include "UpdateTimer.h"
#include "types.h"
#include "W.h"

/******************************************/
/*** UpdateTimer: common implementation ***/
/******************************************/

W::UpdateTimer::UpdateTimer(vdfncb _fp) : objs(NULL), running(false), fp(_fp)
{
	createTimer();
}
W::UpdateTimer::~UpdateTimer()
{
	destroyTimer();
}


/********************************************************/
/*** UpdateTimer: Mac- & iOS- specific implementation ***/
/********************************************************/

#if defined WTARGET_MAC || defined WTARGET_IOS
#pragma mark - Mac/iOS impl

#ifdef WTARGET_MAC
	#include "MacOSXClasses.h"
#else
	#include "iOSClasses.h"
#endif

struct W::UpdateTimer::Objs {
	W_UpdateTimer *timer;
};

void W::UpdateTimer::createTimer() {
	if (objs) {
		W::log << "UpdateTimer: createTimer() called but 'objs' already exists";
		return;
	}
	objs = new Objs();
	objs->timer = [[W_UpdateTimer alloc] initWithCallback:fp];
}
void W::UpdateTimer::destroyTimer() {
	if (objs) {
		delete objs;
		objs = NULL;
	}
}
void W::UpdateTimer::start() { [objs->timer start]; }
void W::UpdateTimer::stop() { [objs->timer stop]; }


/************************************************/
/*** UpdateTimer: Win-specific implementation ***/
/************************************************/

#elif defined WTARGET_WIN
#pragma mark - Windows impl

struct W::UpdateTimer::Objs {
	UINT timer;
};

typedef void (*vdfncb)(void);
vdfncb _controllerUpdateFn = NULL;
void CALLBACK _mmtCallback(UINT timerid, UINT uMsg, DWORD userdata, DWORD d1, DWORD d2) {
	if (_controllerUpdateFn)
		(*_controllerUpdateFn)();
}
struct W::UpdateTimer::Init {
	Init() {
		MMRESULT mmr = timeBeginPeriod(2);
		if (mmr != TIMERR_NOERROR)
			throw Exception("UpdateTimer: Error setting timer resolution");
	}
};
W::UpdateTimer::Init *W::UpdateTimer::init = new W::UpdateTimer::Init();

void W::UpdateTimer::createTimer() {
	if (objs) {
		W::log << "UpdateTimer: createTimer() called but 'objs' already exists";
		return;
	}
	objs = new Objs();
	_controllerUpdateFn = fp;
}
void W::UpdateTimer::destroyTimer() {
	if (objs) {
		delete objs;
		objs = NULL;
	}
	_controllerUpdateFn = NULL;
}
void W::UpdateTimer::start() {
	// Create mmt
	MMRESULT mmr = timeSetEvent(20, 40, &_mmtCallback, NULL, TIME_PERIODIC);
	if (mmr == NULL)
		throw Exception("UpdateTimer: Error starting multimedia timer");
	objs->timer = mmr;
}
void W::UpdateTimer::stop() {
	timeKillEvent(objs->timer);
}

#endif
