#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>

#include "Triangle.h"

namespace Asteroids {


	Triangle :: Triangle() {
		v[0] = new Vertex();
		v[1] = new Vertex();
		v[2] = new Vertex();
	}


	Triangle :: Triangle( Vertex * v1 , Vertex * v2 , Vertex * v3 ) {
		v[0] = v1;
		v[1] = v2;
		v[2] = v3;
		rgb[0] = 255.0f;
		rgb[1] = 255.0f;
		rgb[2] = 255.0f;
	}


	Triangle :: Triangle( Vertex * v1 , Vertex * v2 , Vertex * v3 , float r , float g , float b ) {
		v[0] = v1;
		v[1] = v2;
		v[2] = v3;
		rgb[0] = r;
		rgb[1] = g;
		rgb[2] = b;
	}


	void Triangle :: draw() {
		glVertex3fv( v[0]->position );
		glVertex3fv( v[1]->position ); 
		glVertex3fv( v[2]->position );
	}


}