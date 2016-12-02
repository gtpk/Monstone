/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// TextureManager.h -- Copyright (c) 2006 David Henry
// last modification: feb. 25, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Definitions of a texture manager class.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __TEXTUREMANAGER_H__
#define __TEXTUREMANAGER_H__

#include "DataManager.h"
#include "Texture.h"
#include "Md2Player.h"


/////////////////////////////////////////////////////////////////////////////
//
// class Texture2DManager -- a texture manager which can register/unregister
// Texture2D objects.  Destroy all registred textures at death.
//
// The texture manager is a singleton.
//
/////////////////////////////////////////////////////////////////////////////

class Texture2DManager :
	public DataManager<Texture2D, Texture2DManager>
{
	friend class DataManager<Texture2D, Texture2DManager>;

public:
	// Public interface

	// Load and register a texture.  If the texture has already been
	// loaded previously, return it instead of loading it.
	Texture2D *load (const string &filename)
	{
		string AbsoluteFileName = Md2Player::getInstance()._RootDirctory + "\\" + filename;

		// Look for the texture in the registry
		Texture2D *tex = request (AbsoluteFileName);

		// If not found, load the texture
		if (tex == NULL)
		{
			tex = new Texture2D (AbsoluteFileName,1);

			// If the texture creation failed, delete the
			// unusable object and return NULL
			if (tex->fail ())
			{
				delete tex;
				tex = NULL;
			}
			else
			{
				// The texture has been successfully loaded,
				// register it.
				registerObject (tex->name (), tex);
			}
		}

		return tex;
	}

	Texture2D *load (const string &filename,const string &Alphafilename)
	{
		string AbsoluteFileName = Md2Player::getInstance()._RootDirctory + "\\" + filename;
		string AlphaAbsoluteFileName = Md2Player::getInstance()._RootDirctory + "\\" + Alphafilename;

		string AlphaBlendingTextureName = filename + Alphafilename;

		// Look for the texture in the registry
		Texture2D *tex = request (AlphaBlendingTextureName);

		// If not found, load the texture
		if (tex == NULL)
		{
			tex = new Texture2D (AbsoluteFileName,AlphaAbsoluteFileName,1);

			// If the texture creation failed, delete the
			// unusable object and return NULL
			if (tex->fail ())
			{
				delete tex;
				tex = NULL;
			}
			else
			{
				// The texture has been successfully loaded,
				// register it.
				registerObject (AlphaBlendingTextureName, tex);
			}
		}

		return tex;
	}
};

#endif // __TEXTUREMANAGER_H__

