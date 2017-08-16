/*
 * W - a tiny 2D game development library
 *
 * ====================
 *  DrawingClasses.h
 * ====================
 *
 * Copyright (C) 2012 - Ben Hallstein - http://ben.am
 * Published under the MIT license: http://opensource.org/licenses/MIT
 *
 */

#ifndef __W__DrawableObj
#define __W__DrawableObj

#include "types.h"
#include "Colour.h"
#include "View.h"
#include "Texture.h"

namespace W {
	
	class DColouredShape;
	class DTri;
	class DRect;
	class DSprite;
	
	class Triangle {
	public:
		Triangle(View *, const position &p1, const position &p2, const position &p3, const Colour &, int layer = DEFAULT_LAYER, BlendMode::T = BlendMode::Normal);
		~Triangle();
		
		void setP1(const position &);
		void setP2(const position &);
		void setP3(const position &);
		
		void nudge(const position &);
		
		void setCol(const Colour &);
		
		void setLayer(int);
		void setBlendMode(BlendMode::T);
		
		position p1, p2, p3;
		Colour col;
		
	private:
		DTri *dTri;
		
	};
	
	
	class Rectangle {
	public:
		Rectangle(View *, const position &, const size &, const Colour &, float rotInDegrees = 0, int layer = DEFAULT_LAYER, BlendMode::T = BlendMode::Normal);
		~Rectangle();
		
		void setPos(const position &);
		void setSz(const size &);
		void setRot(float);
		void setAll(const position &, const size &, float);
		void nudge(const position &);
		
		void setCol(const Colour &);
		
		void setLayer(int);
		void setBlendMode(BlendMode::T);
		
		position pos;
		size sz;
		float rot;
		Colour col;
		
	protected:
		DRect *dRect;

	};
	
	
	class Line {
	public:
		Line(View *, const position &p1, const position &p2, const W::Colour, float width, int layer = DEFAULT_LAYER, BlendMode::T = BlendMode::Normal);
		~Line();
		
		void setP1(const position &);
		void setP2(const position &);
		void setP1And2(const position &p1, const position &p2);
		void nudge(const position &);
		
		void setCol(const Colour &);
		
		void setLayer(int);
		void setBlendMode(BlendMode::T);
		
		position p1, p2;
		float lineWidth;
		Colour col;
		
	private:
		void genRectProperties(position &, size &, float &rot);
		Rectangle *rectangle;
	};
	
	
	class Sprite {
	public:
		Sprite(View *, Texture *, const position &, const size &, float opacity = 1, float rotInDegrees = 0, int layer = DEFAULT_LAYER, BlendMode::T = BlendMode::Normal);
		~Sprite();
		
		void setPos(const position &);
		void setSz(const size &);
		void setRot(float);
		void setAll(const position &, const size &, float);
		void nudge(const position &);
		
		void setOpacity(float);
		
		void setLayer(int);
		void setBlendMode(BlendMode::T);
		
		position pos;
		size sz;
		float rot;
		
		float opac;
		
	private:
		DSprite *dSprite;
	};

	
	/***
		DEquiTri draws an equilateral triangle
	 ***/
	
//	class DEquiTri : public DObj {
//	public:
//		DEquiTri(View *, const position &, float _radius, const W::Colour &, float rotation = 0);
//		~DEquiTri();
//		void setPos(const position &_p) { pos = _p; updateVertices(); }
//		void setRadius(float _r) { radius = _r; updateVertices(); }
//		void setRot(float _r) { rotation = _r; updateVertices(); }
//		
//		position pos;
//		float radius;
//		Colour col;
//		float rotation;
//		Texture *tex;
//		
//	protected:
//		void updateVertices();
//		void updateTexcoords();
//	};
//
//	
//	/***
//		DCircle
//	 ***/
//	
//	class DCircle : public DObj {
//	public:
//		DCircle(View *, const W::position &_centrePos, int _radius, const W::Colour &);
//		void setCentrePos(const W::position &_p) { centrePos = _p; setNeedsRecopy(); }
//		void setRadius(int _r) { radius = _r; setNeedsRecopy(); }
//		void setCol(const W::Colour &_c) { col = _c; setNeedsRecopy(); }
//		
//		position centrePos;
//		int radius;
//		Colour col;
//		
//	protected:
//		void _recopy(v3f*, c4f*, t2f*);	// Recopy geom data into supplied arrays
//
//	private:
//		static v3f *circleGeom;
//		struct Init;
//		static Init *initializer;
//	};


	/***
		DText draws... text
	 ***/
	
//	namespace TextAlign {
//		enum T { Left, Right, Centre };
//	}
//	
//	class DText : public DObj {
//	public:
//		DText(View *, const W::position &, const std::string &_txt, const W::Colour &, TextAlign::T _al = TextAlign::Left);
//		~DText();
//		
//		void setPos(const W::position &);
//		void setAlignment(TextAlign::T);
//		void setTxt(const char *);
//		
//		std::string txt;
//		
//		position pos;
//		W::Colour col;
//		TextAlign::T alignment;
//		
//	protected:
//		void updateVertices();
//		void updateTexcoords();
//		
//	private:
//		Texture *tex;
//		int texA, texB, texC, texD;
//
//		static int _geomLengthForText(const std::string &);
//		static int widthForStr(const std::string &);
//		static int widthForChar(char c);
//		
//	};
	
}

#endif
