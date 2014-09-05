#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>

#include "Vertex.h"
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>


namespace Asteroids {


	Vertex :: Vertex() {
		position = new float [3];
		set( 0.0f , 0.0f , 0.0f );
	}


	Vertex :: Vertex( float x , float y , float z ) {
		position = new float [3];
		set( x , y , z );
	}


	Vertex :: ~Vertex() {
		delete[] position;
	}


	void Vertex :: set( float x , float y , float z ) {
		position[0] = x;
		position[1] = y;
		position[2] = z;
	}


	void Vertex :: toCartesian() {
		float z = position[0] * sin( position[1] ) * cos( position[2] );
		float x = position[0] * sin( position[1] ) * sin( position[2] );
		float y = position[0] * cos( position[1] );
		
		set( x , y , z );
	}

	/* Untested */
	void Vertex :: toSpherical() {
		float rho = (float) sqrt( pow(position[0],2) + pow(position[1],2) + pow(position[2],2) ); 
		float phi = (float) atan( sqrt( pow(position[2],2) + pow(position[0],2) ) / position[2] );
		float theta = (float) atan( position[0] / position[2] );

		set( rho , phi , theta );
	}


	double Vertex :: toRadians( float degrees ) {
		return (double) degrees * M_PI / 180.0;
	}


	float Vertex :: toDegrees( double radians ) {
		return (float) radians * 180.0f / M_PI;
	}


	void Vertex :: perturb( int percent ) {
		position[0] *= 1.0f - ( rand() % percent + 1 ) / 100.f;
	}


}