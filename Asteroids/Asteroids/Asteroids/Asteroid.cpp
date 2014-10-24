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


	Asteroid :: Asteroid( int perturb , int type ) {
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

		this->type = type;
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


	void Asteroid :: spawn() {
		int side = rand() % 4;
		int min = ( 0 - SCREEN_SIZE ) / 2;
		int max = SCREEN_SIZE / 2;
		int offset = min + rand() % SCREEN_SIZE;

		switch ( side ) {
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
		
		radius = scalar * 0.5;

		setRotationAxis( 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f , 
					     2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f ,
						 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f );
		setRotationSpeed( ASTEROID_BASE_SPIN + ( rand() % ( ASTEROID_SPIN_RANGE * 2 + 1 ) - ASTEROID_SPIN_RANGE ) );

		setAngle( rand() % 360 );
		setSpeed( ASTEROID_BASE_SPEED * SCREEN_SIZE / 100.0f );
	}


	Asteroid ** Asteroid :: fragment( Asteroid * parent ) {
		Asteroid ** children = new Asteroid * [ASTEROID_FRAGMENT_COUNT];

		if ( parent->type = LARGE ) {
			for ( int i = 0 ; i < ASTEROID_FRAGMENT_COUNT ; ++i ) {
				children[i] = new Asteroid( ASTEROID_PERTURB , MEDIUM );
				children[i]->setScale( SCREEN_SIZE * ( ASTEROID_BASE_SIZE * ASTEROID_MEDIUM_RATIO + ( rand() % ( ASTEROID_SIZE_RANGE * 2 + 1 ) - ASTEROID_SIZE_RANGE ) ) / 100.0f );
				children[i]->radius = children[i]->scalar * 0.5;
			}
		} else if ( parent->type = MEDIUM ) {
			for ( int i = 0 ; i < ASTEROID_FRAGMENT_COUNT ; ++i ) {
				children[i] = new Asteroid( ASTEROID_PERTURB , SMALL );
				children[i]->setScale( SCREEN_SIZE * ( ASTEROID_BASE_SIZE * ASTEROID_SMALL_RATIO + ( rand() % ( ASTEROID_SIZE_RANGE * 2 + 1 ) - ASTEROID_SIZE_RANGE ) ) / 100.0f );
				children[i]->radius = children[i]->scalar * 0.5;
			}
		}

		for ( int i = 0 ; i < ASTEROID_FRAGMENT_COUNT ; ++i ) {
			children[i]->setPosition( parent->position[0] , parent->position[1] , parent->position[2] );
			children[i]->setRotationAxis( 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f , 
						     2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f ,
							 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f );
			children[i]->setRotationSpeed( ASTEROID_BASE_SPIN + ( rand() % ( ASTEROID_SPIN_RANGE * 2 + 1 ) - ASTEROID_SPIN_RANGE ) );

			children[i]->setAngle( rand() % 360 );
			children[i]->setSpeed( ASTEROID_BASE_SPEED * SCREEN_SIZE / 100.0f );
		}
	}

}