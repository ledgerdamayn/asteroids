
#include "Vertex.h"
#include <math.h>

#define PI 3.14159265

namespace Asteroids {


	Vertex :: Vertex() {
		set( 0.0f , 0.0f , 0.0f );
	}


	Vertex :: Vertex( float x , float y , float z ) {
		set( x , y , z );
	}


	Vertex :: ~Vertex() {
		delete[] position;
	}


	void Vertex :: toSpherical() {
		float x = position[0] * sin( toRadians( position[1] ) ) * cos( toRadians( position[2] ) );
		float y = position[0] * sin( toRadians( position[1] ) ) * sin( toRadians( position[2] ) );
		float z = position[0] * cos( toRadians( position[1] ) );
		
		set( x , y , z );
	}


	void Vertex :: toCartesian() {
		float rho = (float) sqrt( pow(position[0],2) + pow(position[1],2) + pow(position[2],2) ); 
		float phi = (float) atan( sqrt( pow(position[0],2) + pow(position[1],2) ) / position[0] );
		float theta = (float) atan( position[1] / position[0] );

		set( rho , phi , theta );
	}


	double Vertex :: toRadians( float degrees ) {
		return (double) degrees * PI / 180.0;
	}


	float Vertex :: toDegrees( double radians ) {
		return (float) radians * 180.0f / PI;
	}


}