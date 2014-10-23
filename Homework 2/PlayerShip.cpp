#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#define _USE_MATH_DEFINES

#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Constants.h"
#include "PlayerShip.h"

namespace Asteroids {


	PlayerShip :: PlayerShip() {
		setPosition( 0.0f , 0.0f , 0.0f );
		setScale( 1.0f );
		setAngle( 90.0f );
		setRotationAxis( 0.0f , 0.0f , 1.0f );
		setRotationAngle( 0.0f );
		setRotationSpeed( 0.0f );
		setColor( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );
		setSpinSpeed( 0.0f );

		setSpeed( 0.0f );
		setAcceleration( 0.0f );

	//	model = new PlayerShipModel();
	}


	PlayerShip :: PlayerShip( float scalar , float r , float g , float b ) {
		setPosition( 0.0f , 0.0f , 0.0f );
		setScale( scalar );
		setAngle( 90.0f );
		setRotationAxis( 0.0f , 0.0f , 1.0f );
		setRotationAngle( 0.0f );
		setRotationSpeed( 0.0f );
		setColor( r , g , b );
		setSpinSpeed( 0.0f );

		setSpeed( 0.0f );
		setAcceleration( 0.0f );

	//	model = new PlayerShipModel();
	}


	PlayerShip :: ~PlayerShip() {
		delete model;
	}


	Laser * PlayerShip :: shoot() {
		return new Laser( angle , LASER_SPEED , position[0] , position[1] , position[2] );
	}


	void PlayerShip :: transform( int millis ) {
		rotation_angle += rotation_speed / 1000.0f * millis;
		angle += spin_speed / 1000.0f * millis;

		if ( acceleration != 0.0f )
			speed += acceleration / 1000.0f * millis;
		else {
			speed *= SHIP_SPEED_DECAY;

			if ( speed < SHIP_SPEED_LAMBDA )
				speed = 0.0f;
		}
		
		position[0] += speed * cos( angle * M_PI / 180.0 ) / 1000.0f * millis;
		position[1] += speed * sin( angle * M_PI / 180.0 ) / 1000.0f * millis;
	}


	void PlayerShip :: draw() {
		glPushMatrix();
		glColor3fv( rgb );
		
		glTranslatef( position[0] , position[1] , position[2] );
		glScalef( scalar , scalar , scalar );
		glRotatef( angle , 0 , 0 , 1 );
	//	glRotatef( 90 , 0 , 1 , 0 );

		glutSolidCone( 1 , 2 , 5 , 10 );
		
		glPopMatrix();
	}

}