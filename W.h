#ifndef __W__W
#define __W__W

#include <string>
#include <vector>
#include <fstream>
#include "mtrand.h"

namespace W {
	
	/* Logging */
	extern std::string logFilePath;
	extern std::string logFileName;
	extern std::ofstream log;
	
	void setLogPath(const char *);

	/* Mersenne Twister */
	unsigned int randUpTo(int);
	extern MTRand_int32 twister;
	
	class GameState;
	class Returny;
	class Event;
	
	/* GameState management */
	void pushState(GameState *);
	void popState(Returny &);
	void _performPop();
	extern std::vector<GameState*> _gs;
	void _addEvent(const Event &);
	extern std::vector<Event> _evqueue;
	extern bool _gsShouldPop;
	extern Returny _returny;
	
	/* Game loopery */
	void startGameLoop();
	extern bool _quit;
	extern void* _demon;
	void _runGameLoop();
	
	class Window;
	
	/* Maintain a list of windows */
	extern std::vector<Window*> _windows;
	void _updateAllViewPositions();
	
	/* Bollocks */
	extern int INFINITATION;
	
	struct _init;
	extern _init *_initializer;
}

#include "types.h"
#include "Colour.h"
#include "Event.h"
#include "Window.h"
#include "View.h"
#include "UIView.h"
#include "Positioner.h"
#include "EventHandler.h"
#include "GameState.h"
#include "Callback.h"
#include "MisterHeapy.h"
#include "NavMap.h"
#include "Timer.h"

#endif
