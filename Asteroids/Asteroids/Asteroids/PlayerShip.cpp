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
#include "PlayerShipModel.h"

namespace Asteroids {


	PlayerShip :: PlayerShip( float scalar , float r , float g , float b ) {
		setPosition( 0.0f , 0.0f , 0.0f );
		setScale( scalar );
		setAngle( 0.0f );
		setRotationAxis( 0.0f , 0.0f , 1.0f );
		setRotationAngle( 0.0f );
		setRotationSpeed( 0.0f );
		setColor( r , g , b );
		setSpinSpeed( 0.0f );

		setSpeed( 0.0f );
		setAcceleration( 0.0f );
		
		model = new PlayerShipModel();
		start_bound = new Triangle( new Vertex( 0.5f * scalar , 0 , 0 ) ,
									new Vertex( -0.5f * scalar , 0.5f * scalar , 0 ) ,
									new Vertex( -0.5f * scalar , -0.5f * scalar , 0 ) );
		current_bound =  new Triangle( new Vertex( 0.5f * scalar , 0 , 0 ) ,
									new Vertex( -0.5f * scalar , 0.5f * scalar , 0 ) ,
									new Vertex( -0.5f * scalar , -0.5f * scalar , 0 ) );
	}


	PlayerShip :: ~PlayerShip() {
		delete model;
		delete start_bound;
		delete current_bound;
	}


	void PlayerShip :: reset() {
		setPosition( 0.0f , 0.0f , 0.0f );
		setAngle( 0.0f );
		setRotationAxis( 0.0f , 0.0f , 1.0f );
		setRotationAngle( 0.0f );
		setRotationSpeed( 0.0f );
		setSpinSpeed( 0.0f );
		setSpeed( 0.0f );
		setAcceleration( 0.0f );

		current_bound =  new Triangle( new Vertex( 0.5f * scalar , 0 , 0 ) ,
									new Vertex( -0.5f * scalar , 0.5f * scalar , 0 ) ,
									new Vertex( -0.5f * scalar , -0.5f * scalar , 0 ) );
	}


	void PlayerShip :: shoot( Laser * laser ) {
		laser->angle = angle;
		laser->speed = LASER_SPEED;
		laser->setPosition( position[0] , position[1] , position[2] );
		laser->time = 0;
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

		model->draw();
		
		glPopMatrix();
	}


	void PlayerShip :: updateBounds() {
		double radians = angle * M_PI / 180.0;
		current_bound->v[0]->set( start_bound->v[0]->x() * cos( radians ) - start_bound->v[0]->y() * sin( radians ) + position[0] ,
								  start_bound->v[0]->y() * cos( radians ) + start_bound->v[0]->x() * sin( radians ) + position[1] ,
								  0 );
		current_bound->v[1]->set( start_bound->v[1]->x() * cos( radians ) - start_bound->v[1]->y() * sin( radians ) + position[0] ,
								  start_bound->v[1]->y() * cos( radians ) + start_bound->v[1]->x() * sin( radians ) + position[1] ,
								  0 );
		current_bound->v[2]->set( start_bound->v[2]->x() * cos( radians ) - start_bound->v[2]->y() * sin( radians ) + position[0] ,
								  start_bound->v[2]->y() * cos( radians ) + start_bound->v[2]->x() * sin( radians ) + position[1] ,
								  0 );
	}

}