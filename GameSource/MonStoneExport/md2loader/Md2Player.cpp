/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Md2Player.cpp -- Copyright (c) 2006 David Henry
// last modification: feb. 25, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Implementation of MD2 Player class.
//
/////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>

#else
#include "dirent.h"
#endif


#include <stdio.h>
#include <GL/gl.h>
#include <iostream>
#include <fstream>
#include <sys/types.h>

#include "../../Opengl2Md2/MarxWorld.h"
#include "Texture.h"


using std::cout;
using std::cerr;
using std::endl;


/////////////////////////////////////////////////////////////////////////////
//
// class Md2Player implementation.
//
/////////////////////////////////////////////////////////////////////////////


// --------------------------------------------------------------------------
// Md2Player::Md2Player
//
// Constructor.  Read a MD2 player from directory.
// --------------------------------------------------------------------------

MarxWorld::MarxWorld (const string &dirname)
	throw (std::runtime_error)
	: _playerMesh (NULL), _weaponMesh (NULL)
{
	std::ifstream ifs;
	string path;

#ifndef _WIN32
	dirent *dit;
	DIR *dd;


	// Open the directory
	dd = opendir (dirname.c_str ());

	if (!dd)
		throw std::runtime_error ("Couldn't open dir");
#else
	HANDLE hSrch;
	WIN32_FIND_DATA wfd;
	BOOL bResult=TRUE;
	char drive[_MAX_DRIVE];
	char dir[MAX_PATH];
	char newpath[MAX_PATH];

	hSrch=FindFirstFile(dirname.c_str(),&wfd);
	if (hSrch == INVALID_HANDLE_VALUE) 
	{
		throw std::runtime_error ("Couldn't open dir");
	}

#endif

	// Test if player mesh exists
	//path = dirname + "/tris.md2";
	path = dirname + "/tris.md2";
	ifs.open (path.c_str (), std::ios::binary);

	if (!ifs.fail ())
	{
		ifs.close ();
		_playerMesh = Md2ModelPtr(new Md2Model (path));
	}

	// Test if weapon mesh exists

	path = dirname + "/weapon1.md2";
	ifs.open (path.c_str (), std::ios::binary);

	if (!ifs.fail ())
	{
		ifs.close ();
		_weaponMesh = Md2ModelPtr(new Md2Model (path));
	}

	// If we haven't found any model, this is not a success...
	if (!_playerMesh.get () && !_weaponMesh.get ())
		throw std::runtime_error ("No model found");

	_name.assign (dirname, dirname.find_last_of ('/') + 1,
		dirname.length ());

#ifndef _WIN32
	// Read directory for textures
	while ((dit = readdir (dd)) != NULL)
	{
		const string filename (dit->d_name);
		path = dirname + "/" + filename;

		const char *str = filename.c_str ();
		string::size_type l = filename.find_last_of ('.');

		// Skip directories
		if (l > filename.length ())
			continue;

		// Skip files beginning with "<char>_" and files
		// ending with "_i.<char*>"
		if ((str[1] != '_') &&
			!((str[l-1] == 'i') && (str[l-2] == '_')))
		{
			// Check if it's a known image file format
			if (filename.compare (l, 4, ".pcx") == 0 ||
				filename.compare (l, 4, ".tga") == 0 ||
				filename.compare (l, 4, ".PCX") == 0 ||
				filename.compare (l, 4, ".TGA") == 0)
			{
				if (filename.compare (0, 7, "weapon.") == 0)
				{
					// We've got the weapon skin
					_weaponMesh->loadTexture (path);
					_weaponMesh->setTexture (path);
				}
				else
				{
					// Assume this is a player skin
					_playerMesh->loadTexture (path);
				}
			}
		}
	}

	// Close directory
	closedir (dd);
#else
	hSrch=FindFirstFile(std::string(dirname + "\\*.*").c_str(),&wfd);
	//sprintf(newpath,"%s\\*.*",drive,dir,wfd.cFileName);
	//_splitpath(path,drive,dir,NULL,NULL);
	while (bResult) 
	{

		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
		{
			//Do Nothing
		}
		else 
		{
			//char ch[260];
			//char DefChar = ' ';
			//WideCharToMultiByte(CP_ACP,0,wfd.cFileName,-1, ch,260,&DefChar, NULL);

			const string filename = (wfd.cFileName);
			path = dirname + "/" + filename;

			const char *str = filename.c_str ();
			string::size_type l = filename.find_last_of ('.');

			// Skip directories
			if (l > filename.length ())
				continue;

			// Skip files beginning with "<char>_" and files
			// ending with "_i.<char*>"
			if ((str[1] != '_') &&
				!((str[l-1] == 'i') && (str[l-2] == '_')))
			{
				// Check if it's a known image file format
				if (filename.compare (l, 4, ".pcx") == 0 ||
					filename.compare (l, 4, ".tga") == 0 ||
					filename.compare (l, 4, ".PCX") == 0 ||
					filename.compare (l, 4, ".TGA") == 0)
				{
					if (filename.compare (0, 7, "weapon.") == 0)
					{
						// We've got the weapon skin
						//_weaponMesh->loadTexture (path);
						//_weaponMesh->setTexture (path);
					}
					else
					{
						// Assume this is a player skin
						_playerMesh->loadTexture (path);
					}
				}
			}
			//printf("%s%s%s\n",drive,dir,wfd.cFileName);
		}
		bResult=FindNextFile(hSrch,&wfd);
	}
	FindClose(hSrch);
#endif

	// Attach models to MD2 objects
	if (_playerMesh.get ())
	{

		_playerObject.setName(100);
		_playerObject.setModel (_playerMesh.get ());

		// Set first skin as default skin
		_currentSkin = _playerMesh->skins ().begin ()->first;
		_currentAnim = _playerObject.currentAnim ();
	}

	if (_weaponMesh.get ())
	{
		_weaponObject.setModel (_weaponMesh.get ());

		if (!_playerMesh.get ())
			_currentAnim = _weaponObject.currentAnim ();
	}
}


// --------------------------------------------------------------------------
// Md2Player::~Md2Player
//
// Destructor.
// --------------------------------------------------------------------------

MarxWorld::~MarxWorld ()
{
}


// --------------------------------------------------------------------------
// Md2Player::drawPlayerItp
//
// Draw player objects with interpolation.
// --------------------------------------------------------------------------

void
	MarxWorld::drawPlayerItp (bool animated, Md2Object::Md2RenderMode renderMode)
{
	if (_playerMesh.get ())
	{
		_playerMesh->setTexture (_currentSkin);
		_playerObject.drawObjectItp (animated, renderMode);
	}

	if (_weaponMesh.get ())
		_weaponObject.drawObjectItp (animated, renderMode);
}


// --------------------------------------------------------------------------
// Md2Player::drawPlayerFrame
//
// Draw player objects at a given frame.
// --------------------------------------------------------------------------

void
	MarxWorld::drawPlayerFrame (int frame, Md2Object::Md2RenderMode renderMode)
{
	if (_playerMesh.get ())
	{
		_playerMesh->setTexture (_currentSkin);
		_playerObject.drawObjectFrame (frame, renderMode);
	}

	if (_weaponMesh.get ())
		_weaponObject.drawObjectFrame (frame, renderMode);
}


// --------------------------------------------------------------------------
// Md2Player::animate
//
// Animate player objects.
// --------------------------------------------------------------------------

void
	MarxWorld::animate (GLfloat percent)
{
	if (_playerMesh.get ())
		_playerObject.animate (percent);

	if (_weaponMesh.get ())
		_weaponObject.animate (percent);
}


// --------------------------------------------------------------------------
// Md2Player::setScale
//
// Scale model objects.
// --------------------------------------------------------------------------

void
	MarxWorld::setScale (GLfloat scale)
{
	if (_playerMesh.get ())
		_playerObject.setScale (scale);

	if (_weaponMesh.get ())
		_weaponObject.setScale (scale);
}


// --------------------------------------------------------------------------
// Md2Player::setSkin
//
// Set player skin.
// --------------------------------------------------------------------------

void
	MarxWorld::setSkin (const string &name)
{
	_currentSkin = name;
}


// --------------------------------------------------------------------------
// Md2Player::setAnim
//
// Set current player animation.
// --------------------------------------------------------------------------

void MarxWorld::setAnim (const string &name)
{
	if (_weaponMesh.get ())
	{

		_weaponObject.setAnim (name);
		_currentAnim = name;
	}

	if (_playerMesh.get ())
	{
		_playerObject.setAnim (name);
		_currentAnim = name;
	}
}

void MarxWorld::setRotate(vec3_t angle)
{
	if (_weaponMesh.get ())
	{
		_weaponObject.setRotate (angle);
	}

	if (_playerMesh.get ())
	{
		_playerObject.setRotate (angle);
	}
}

void MarxWorld::setTranslate(vec3_t trance )
{
	if (_weaponMesh.get ())
	{
		_weaponObject.setTranslate (trance);
	}

	if (_playerMesh.get ())
	{
		_playerObject.setTranslate (trance);
	}
}