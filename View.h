/*
 * W - a tiny 2D game development library
 *
 * ==========
 *  View.h
 * ==========
 *
 * Copyright (C) 2012 - Ben Hallstein - http://ben.am
 * Published under the MIT license: http://opensource.org/licenses/MIT
 *
 */

#ifndef __W__View
#define __W__View

#include "Colour.h"
#include "Callback.h"
#include "Positioner.h"

#include <map>

#define MR_CURRENCY '$'

namespace W {
	
	class Window;
	class Event;
	class GameState;
	class DColouredShape;
	class DTexturedShape;
	class TextureAtlas;
	class StorageObjForColouredShapes;
	class StorageObjForTexturedShapes;
	
	
	struct Layer {
		Layer();
		~Layer();
		std::map<BlendMode::T, StorageObjForColouredShapes*> cGroups;
		std::map<BlendMode::T, std::map<TextureAtlas*, StorageObjForTexturedShapes*>> tGroups;
		void compact();
	};

	
	class View {
	public:
		View(Positioner);
		View();
		~View();
			// If NULL is supplied for positioner, subclass must
			// set one up and call _updatePosition.
		
		void _updatePosition();	// Gets the window size automatically
		void _updatePosition(v2i winsize);
		
		void _convertEventCoords(Event&);				// Converts to view's coordinates, and calls convertEventCoords() virtual
		virtual void convertEventCoords(Event&) { }	// Override to perform further conversion of mouse events
		
		virtual void mouseEvent(Event) { }
		virtual void touchDown(Event) { }
		
		void _draw(v2i winSz);
		
		const iRect& getRct() { return rct; }
		
		// New Drawable Stuff
		void addDrawable(DColouredShape *);
		void addDrawable(DTexturedShape *);
		void removeDrawable(DColouredShape *);
		void removeDrawable(DTexturedShape *);
		void compactAllLayers();
		
		std::map<int, Layer> layers;
		
	protected:
		bool use_positioner;
		Positioner _positioner;
		iRect rct;
		
		v2i _offset;	// Def 0. Used by scrolling subviews. Undocumented!
		
		virtual void updatePosition(v2i winsize) { }	// Override to implement subclass position update behaviours
		virtual void customOpenGLDrawing() { }
		
	private:
		int frameCounter;
		
	};
	
}

#endif
