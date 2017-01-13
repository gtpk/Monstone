/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Texture.h -- Copyright (c) 2006-2007 David Henry
// last modification: july 13, 2007
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Definition of an OpenGL texture classes.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // _WIN32

#include <gl/gl.h>
#include <gl/glu.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

#include "Image.h"

using std::string;
using std::vector;
using std::map;
using std::auto_ptr;

/////////////////////////////////////////////////////////////////////////////
// Texture class diagram:
//
//     +--------- (abs)
//     |  Texture  |
//     +-----------+
//          ^
//          |
//    +-------------+
//    |  Texture2D  |
//    +-------------+
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//
// class Texture -- OpenGL texture base class.  This is an abstract
// class for more specialized OpenGL texture classes.
//
/////////////////////////////////////////////////////////////////////////////

class Texture
{
public:
  // Constructor/destructor
  Texture ();
  virtual ~Texture ();

public:
  // Constants
  enum  {
    //Default behaviour
    kDefault  = 0,

    // Use texture compression
    kCompress = (1 << 0),
  };

  typedef int TextureFlags;

public:
  // Public interface
  void bind () const;
  bool fail () const { return _fail; }
  bool stdCoordSystem () const { return _standardCoordSystem; }

  // Accessors
  const string &name () const { return _name; }
  const string &GetTexturePath () const { return _TextureRealPath; }
  const string &GetAlphaTexturePath () const { return _AlphaTextureRealPath; }

  const GLuint handle () const { return _handle; }
  const GLuint Alphahandle () const { return _Alphahandle; }

  virtual GLenum target () const = 0;

private:
  // Copy operations are not allowed for textures, because
  // when the source texture is destroyed, it releases
  // its texture handle and so dest texture's handle is
  // not valid anymore.
  Texture (const Texture &);
  Texture &operator= (const Texture &);

protected:
  // Internal functions
  GLubyte *loadImageFile (const string &filename);
  GLint getCompressionFormat (GLint internalFormat);
  GLint getInternalFormat (GLint components);

protected:
  // Member variables
  string _name;
  string _TextureRealPath;
  string _AlphaTextureRealPath;
  GLuint _handle;
  GLuint _Alphahandle;

  TextureFlags _flags;
  bool _standardCoordSystem;
  bool _fail;
};


/////////////////////////////////////////////////////////////////////////////
//
// class Texture2D -- OpenGL texture 2D object.
//
/////////////////////////////////////////////////////////////////////////////

class Texture2D : public Texture
{
public:
  // Constructors
  Texture2D (const string &filename, TextureFlags flags = kDefault);
  Texture2D (const string &filename,  const string &alphaTexture, TextureFlags flags = kDefault);
  Texture2D (const Image *img, TextureFlags flags = kDefault);

protected:
  // Default constructor is not public
  Texture2D ();

  // Internal functions
  virtual void create (const Image *img, TextureFlags flags);
  virtual void create (const Image *img, const Image *ImageAlpha, TextureFlags flags);

public:
  // Accessors
  virtual GLenum target () const { return GL_TEXTURE_2D; }
};

#endif // __TEXTURE_H__
