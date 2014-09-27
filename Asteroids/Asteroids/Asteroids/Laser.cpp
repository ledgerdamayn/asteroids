#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#define _USE_MATH_DEFINES

#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Laser.h"
#include "Constants.h"


namespace Asteroids {

	Laser :: Laser() {
		setPosition( 0.0f , 0.0f , 0.0f );
		setScale( 1.0f );

		time = 0;
		setColor( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );
	}


	Laser :: Laser( float angle , float speed , float x , float y , float z ) {
		setPosition( x , y , z );
		setScale( 1.0f );
		
		time = 0;
		setColor( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );

		this->angle = angle;
		this->speed = speed;
	}


	void Laser :: transform( int millis ) {
		position[0] += speed * cos( angle * M_PI / 180.0 ) / 1000.0f * millis;
		position[1] += speed * sin( angle * M_PI / 180.0 ) / 1000.0f * millis;
		time += millis;
	}


	void Laser :: draw() {
		glPushMatrix();
		glColor3fv( rgb );

		glBegin( GL_POINTS );
		glVertex3fv( position );
		glEnd();

		glPopMatrix();
	}

}