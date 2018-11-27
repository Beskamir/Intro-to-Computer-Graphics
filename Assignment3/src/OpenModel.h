#ifndef OBJMODEL_H
#define OBJMODEL_H

/***************************************************************************
 *
 * OBJmodel, a helper class for loading 3D data from OBJ files. This isn't
 *  designed to be a complete loader, so for instance the output isn't ideal
 *  for use with OpenGL. Still, it should be enough to get you started.
 *
 *  Author: Haysn Hornbeck
 */

#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
//#include <boost/tokenizer.hpp>

using namespace std;

//***** DATA DECLARATIONS

typedef unsigned char uchar;
typedef unsigned int uint;

// build up what we need to create a triangle
typedef struct {

	float x;
	float y;
	float z;
	float w;

	} Position;

typedef struct {

	float x;
	float y;
	float z;

	} Normal;

typedef struct {

	float s;
	float t;
	float u;

	} TexCoord;

typedef struct {

	Position pos;
	Normal norm;
	TexCoord tex;

	} Vertex;

typedef struct {

	array<Vertex,3> vertex;

	} Triangle;


//***** CLASSES

// load up an OBJ file, and provide a friendly interface
class OBJmodel {

	private:
	string filename;		// the name of the current object
	vector<Triangle> contents;	//  and its contents

	vector<Position> pos;		// caches used during the reading process
	vector<Normal> norm;
	vector<TexCoord> tex;
	vector<Triangle> tempContents;	//  including the future "contents"

	string buffer;			// a buffer to store lines in, and separators
	char_separator<char> whitespace;
	char_separator<char> faceSeparator;

	bool readVertex();		// a helper to read in vertex data
	bool readFace();		//  and the same for faces

	public:
	OBJmodel();

	bool load( string filename );	// load up an OBJ file

					// basic setters/getters
	bool isLoaded() { return contents.size() > 0; }
	string getFilename() { return filename; }
	uint triangleCount() { return contents.size(); }

					// retrieve some geometry
	Triangle& operator[]( size_t index );
	const Triangle& operator[]( size_t index ) const;

	};


#endif
