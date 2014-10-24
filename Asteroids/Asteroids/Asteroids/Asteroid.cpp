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

		type = LARGE;
		model = new AsteroidModel( 0.5 , 5 , 7 , ASTEROID_PERTURB );
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
		
		radius = float(scalar) * 0.5f;

		setRotationAxis( 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f , 
					     2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f ,
						 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f );
		setRotationSpeed( ASTEROID_BASE_SPIN + ( rand() % ( ASTEROID_SPIN_RANGE * 2 + 1 ) - ASTEROID_SPIN_RANGE ) );

		setAngle( rand() % 360 );
		setSpeed( ASTEROID_BASE_SPEED * SCREEN_SIZE / 100.0f );
	}


	void Asteroid :: fragment( Asteroid * a , Asteroid * b ) {
		if ( type == LARGE ) {
			a->type = MEDIUM;
			a->setScale( SCREEN_SIZE * ( ASTEROID_BASE_SIZE * ASTEROID_MEDIUM_RATIO + ( rand() % ( ASTEROID_SIZE_RANGE * 2 + 1 ) - ASTEROID_SIZE_RANGE ) ) / 100.0f );
			
			b->type = MEDIUM;
			b->setScale( SCREEN_SIZE * ( ASTEROID_BASE_SIZE * ASTEROID_MEDIUM_RATIO + ( rand() % ( ASTEROID_SIZE_RANGE * 2 + 1 ) - ASTEROID_SIZE_RANGE ) ) / 100.0f );
		} else if ( type == MEDIUM ) {
			a->type = SMALL;
			a->setScale( SCREEN_SIZE * ( ASTEROID_BASE_SIZE * ASTEROID_SMALL_RATIO + ( rand() % ( ASTEROID_SIZE_RANGE * 2 + 1 ) - ASTEROID_SIZE_RANGE ) ) / 100.0f );
			
			b->type = SMALL;
			b->setScale( SCREEN_SIZE * ( ASTEROID_BASE_SIZE * ASTEROID_SMALL_RATIO + ( rand() % ( ASTEROID_SIZE_RANGE * 2 + 1 ) - ASTEROID_SIZE_RANGE ) ) / 100.0f );
		}

		a->radius = float(a->scalar) * 0.5f;
		b->radius = float(b->scalar) * 0.5f;
		
		a->setPosition( position[0] , position[1] , position[2] );
		b->setPosition( position[0] , position[1] , position[2] );
		
		a->setRotationAxis( 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f , 
		                    2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f ,
							2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f );
		b->setRotationAxis( 2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f , 
		                    2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f ,
							2.0f * ( static_cast <float> (rand()) / static_cast <float> (RAND_MAX) ) - 1.0f );
		
		a->setRotationSpeed( ASTEROID_BASE_SPIN + ( rand() % ( ASTEROID_SPIN_RANGE * 2 + 1 ) - ASTEROID_SPIN_RANGE ) );
		b->setRotationSpeed( ASTEROID_BASE_SPIN + ( rand() % ( ASTEROID_SPIN_RANGE * 2 + 1 ) - ASTEROID_SPIN_RANGE ) );
		
		a->setAngle( rand() % 360 );
		b->setAngle( rand() % 360 );
		
		a->setSpeed( ASTEROID_BASE_SPEED * SCREEN_SIZE / 100.0f );
		b->setSpeed( ASTEROID_BASE_SPEED * SCREEN_SIZE / 100.0f );
	}

}