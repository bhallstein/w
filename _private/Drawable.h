/*
 * W - a tiny 2D game development library
 *
 * ==============
 *  Drawable.h
 * ==============
 *
 * Copyright (C) 2012 - Ben Hallstein - http://ben.am
 * Published under the MIT license: http://opensource.org/licenses/MIT
 *
 */

// Classes for use by user-facing, Cheshire Cat drawing classes

#ifndef __W__Drawable
#define __W__Drawable

#include "types.h"

namespace W {

  class View;
  class Texture;
  class StorageObjForColouredShapes;
  class StorageObjForTexturedShapes;

  class Drawable {
  public:
    Drawable(View *, int length, int layer, BlendMode::T);
    ~Drawable();

    int length;
    int index;
    int preceding_free_space;

    int layer;
    BlendMode::T blendMode;

    View *view;

    v3f *vptr, *v_array;
    v4f *cptr, *c_array;
    // xptr: ptr to chunk of managed storage
    // x_array: local copy (modify this then recopy)

    void recopyV();
    void recopyC();
  };


  class DColouredShape : public Drawable {
  public:
    DColouredShape(View *, int _len, int _lay, BlendMode::T _bMode);
    ~DColouredShape();
    // NB: the constructor only adds D to the view, setting D's
    // properties. It doesn't copy anything in - this is the subclass's job.

    void updateLength(int);

    void setLayer(int);
    void setBlendMode(BlendMode::T);

    void recopyBoth();

    StorageObjForColouredShapes *storageObj;

    DColouredShape *prev, *next;
  };


  class DTri : public DColouredShape {
  public:
    DTri(View *, const v2f &p1, const v2f &p2, const v2f &p3, const Colour &, int layer, BlendMode::T);

    void setP123(const v2f &, const v2f &, const v2f &);
    void setCol(const Colour &);
  };


  class DRect : public DColouredShape {
  public:
    DRect(View *, const v2f &pos, const v2f &sz, const Colour &, float rot, int layer, BlendMode::T);

    void setPosSzRot(const v2f &pos, const v2f &sz, float);
    void setCol(const Colour &);
  };


  class DLine : public DColouredShape {
  public:
    DLine(View *, const v2f &p1, const v2f &p2, const v2f &delta, const Colour &, int layer, BlendMode::T);

    void setP1P2Delta(const v2f &p1, const v2f &p2, const v2f &d);
    void setCol(const Colour &);

    // The "delta" param to DLine is a vector that is added to/subtracted from points P1
    // and P2 to give the corners of a rect used to draw the line
  };


  class DCircle : public DColouredShape {
  public:
    DCircle(View *, v2f _center, float _radius, W::Colour, int layer = DEFAULT_LAYER, BlendMode::T blendMode = BlendMode::Normal);

    void setPosRadius(v2f pos, float radius);
    void setCol(Colour);
  };


  class DTexturedShape : public Drawable {
  public:
    DTexturedShape(View *, Texture *, int _len, int _lay, BlendMode::T _bMode);
    ~DTexturedShape();
    // NB: the constructor only adds D to the view, setting D's
    // properties. It doesn't copy anything in - this is the subclass's job.
    // (Except for texcoords, which the subclass won't generally touch.)

    void setLayer(int);
    void setBlendMode(BlendMode::T);

    StorageObjForTexturedShapes *storageObj;
    Texture *tex;

    v2f *tptr, *t_array;

    void recopyT();
    void recopyAll();

    DTexturedShape *prev, *next;
  };


  class DSprite : public DTexturedShape {
  public:
    DSprite(View *, Texture *, const v2f &pos, const v2f &scale, float opacity, float rot, int layer = DEFAULT_LAYER, BlendMode::T bm = BlendMode::Normal);

    void setPosScaleRot(const v2f &pos, const v2f &sc, float rot);
    void setOpac(float);

    void regenAndCopyTexCoords();
    // Generate texcoords from tex in local array & call recopyT()
  };


  class DRetroText : public DColouredShape {
  public:
    DRetroText(View*, v2f pos, std::string txt, Colour, TextAlign::T, int layer = DEFAULT_LAYER, BlendMode::T blendMode = BlendMode::Normal);
    void setPosTxtAlignmentCol(v2f, std::string, TextAlign::T, Colour);

    static int widthForStr(std::string);

  private:
    void updateVertices(v2f, std::string);

  };
}

#endif

