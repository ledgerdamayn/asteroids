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
#include <iostream>

namespace Asteroids {


	Triangle :: Triangle() {
		v = new Vertex * [3];
		v[0] = new Vertex();
		v[1] = new Vertex();
		v[2] = new Vertex();

		n = new Vertex();
	}


	Triangle :: Triangle( Vertex * v1 , Vertex * v2 , Vertex * v3 ) {
		v = new Vertex * [3];
		v[0] = v1;
		v[1] = v2;
		v[2] = v3;

		n = new Vertex();
		calculateNormal();

		rgb[0] = 255.0f;
		rgb[1] = 255.0f;
		rgb[2] = 255.0f;
	}


	Triangle :: Triangle( Vertex * v1 , Vertex * v2 , Vertex * v3 , float r , float g , float b ) {
		v = new Vertex * [3];
		v[0] = v1;
		v[1] = v2;
		v[2] = v3;

		n = new Vertex();
		calculateNormal();

		rgb[0] = r;
		rgb[1] = g;
		rgb[2] = b;
	}


	void Triangle :: draw() {
		/*
		std::cout << v[0]->position[0] << " " << v[0]->position[1] << " " << v[0]->position[2] << "\n";
		std::cout << v[1]->position[0] << " " << v[1]->position[1] << " " << v[1]->position[2] << "\n";
		std::cout << v[2]->position[0] << " " << v[2]->position[1] << " " << v[2]->position[2] << "\n\n";
		*/
		glBegin( GL_POLYGON );

		glVertex3fv( v[0]->position );
		glVertex3fv( v[1]->position ); 
		glVertex3fv( v[2]->position );
		glNormal3fv( n->position );
		
		glEnd();
	}


	void Triangle :: calculateNormal() {
		float d0_x = v[1]->x() - v[0]->x();
		float d0_y = v[1]->y() - v[0]->y();
		float d0_z = v[1]->z() - v[0]->z();
		float d1_x = v[2]->x() - v[1]->x();
		float d1_y = v[2]->y() - v[1]->y();
		float d1_z = v[2]->z() - v[1]->z();
		
		n->set( d0_y * d1_z - d0_z * d1_y ,
			    d0_z * d1_x - d0_x * d1_z ,
				d0_x * d1_y - d0_y * d1_x );
	}


	Triangle :: ~Triangle() {
		for ( int i = 0 ; i < 3 ; ++i )
			delete v[i];

		delete[] v;
		delete n;
	}


}