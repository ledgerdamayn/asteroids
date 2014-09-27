#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Asteroid.h"
#include "AsteroidModel.h"
#include "Constants.h"


namespace Asteroids {

	Asteroid :: Asteroid() {
		setPosition( 0.0f , 0.0f , 0.0f );
		setScale( 1.0f );
		setAngle( 0.0f );
		setRotationAxis( 0.0f , 0.0f , 1.0f );
		setRotationAngle( 0.0f );
		setRotationSpeed( 0.0f );
		setColor( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );
		setSpinSpeed( 0.0f );
		setSpeed( 0.0f );
		setAcceleration( 0.0f );

		model = new AsteroidModel();
	}


	Asteroid :: Asteroid( int perturb ) {
		setPosition( 0.0f , 0.0f , 0.0f );
		setScale( 1.0f );
		setAngle( 0.0f );
		setRotationAxis( 0.0f , 0.0f , 1.0f );
		setRotationAngle( 0.0f );
		setRotationSpeed( 0.0f );
		setColor( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
				  static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );
		setSpinSpeed( 0.0f );
		setSpeed( 0.0f );
		setAcceleration( 0.0f );

		model = new AsteroidModel( 0.5 , 5 , 7 , perturb );
	}


	Asteroid :: ~Asteroid() {
		delete model;
	}


	void Asteroid :: draw() {
		glPushMatrix();
		glColor3fv( rgb );
		
		glTranslatef( position[0] , position[1] , position[2] );
		glScalef( scalar , scalar , scalar );
		glRotatef( rotation_angle , rotationAxis[0] , rotationAxis[1] , rotationAxis[2] );
		model->draw();
		
		glPopMatrix();
	}


	void Asteroid :: initialize( int index ) {
		this->index = index;
		int side = rand() % 4;
		int min = ( 0 - SCREEN_SIZE ) / 2;
		int max = SCREEN_SIZE / 2;
		int offset = min + rand() % SCREEN_SIZE;

		switch (side) {
		case 0 : // Top
			setPosition( offset , max , 0 );						 
			break;
		case 1 : // Bottom
			setPosition( offset , min , 0 );
			break;
		case 2 : // Left
			setPosition( min , offset , 0 );
			break;
		case 3 : // Right
			setPosition( max , offset , 0 );
			break;
		}

		setScale( SCREEN_SIZE * ( ASTEROID_BASE_SIZE + ( rand() % ( ASTEROID_SIZE_RANGE * 2 + 1 ) - ASTEROID_SIZE_RANGE ) ) / 100.0f );
		setRotationAxis( 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f , 
					     2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f ,
						 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f );
		setRotationSpeed( ASTEROID_BASE_SPIN + ( rand() % ( ASTEROID_SPIN_RANGE * 2 + 1 ) - ASTEROID_SPIN_RANGE ) );

		setAngle( rand() % 360 );
		setSpeed( ASTEROID_BASE_SPEED * SCREEN_SIZE / 100.0f );

	}


}