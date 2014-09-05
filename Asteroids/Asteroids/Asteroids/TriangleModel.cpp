#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>

#include "TriangleModel.h"
#include <iostream>

namespace Asteroids {

	void TriangleModel :: draw() {
		// glBegin( GL_TRIANGLES );
		glBegin( GL_LINES );

		for( std::list<Triangle *>::iterator i = triangles.begin() ; i != triangles.end() ; ++i ) {
			(*i)->draw();
		}
		
		glEnd();
	}

}