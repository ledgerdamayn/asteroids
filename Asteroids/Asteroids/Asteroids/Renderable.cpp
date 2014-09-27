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

#include "Constants.h"
#include "Renderable.h"

namespace Asteroids {


	void Renderable :: translate( float x , float y , float z ) {
		position[0] += x;
		position[1] += y;
		position[2] += z;
	}

	
	void Renderable :: scale( float scalar ) {
		this->scalar *= scalar;
	}


	void Renderable :: rotate( float rotation ) {
		angle += rotation;
	}


	void Renderable :: setPosition( float x , float y , float z ) {
		position[0] = x;
		position[1] = y;
		position[2] = z;
	}


	void Renderable :: setScale( float scalar ) {
		this->scalar = scalar;
	}

	void Renderable :: setRotationAxis( float x , float y , float z ) {
		rotationAxis[0] = x;
		rotationAxis[1] = y;
		rotationAxis[2] = z;
	}

	void Renderable :: setRotationAngle( float angle ) {
		rotation_angle = angle;
	}

	void Renderable :: setRotationSpeed( float speed ) {
		rotation_speed = speed;
	}

	void Renderable :: setAngle( float angle ) {
		this->angle = angle;
	}

	void Renderable :: setSpinSpeed( float spin_speed ) {
		this->spin_speed = spin_speed;
	}

	void Renderable :: setSpeed( float speed ) {
		this->speed = speed;
	}

	void Renderable :: setAcceleration( float acceleration ) {
		this->acceleration = acceleration;
	}


	void Renderable :: wrapAround() {
		int min = ( 0 - SCREEN_SIZE ) / 2;
		int max = SCREEN_SIZE / 2;

		if ( position[0] < min )
			position[0] = max;
		else if ( position[0] > max )
			position[0] = min;

		if ( position[1] < min )
			position[1] = max;
		else if ( position[1] > max ) 
			position[1] = min;
	}


	void Renderable :: transform( int millis ) {
		rotation_angle += rotation_speed / 1000.0f * millis;
		angle += spin_speed / 1000.0f * millis;

		position[0] += speed * cos( angle * M_PI / 180.0 ) / 1000.0f * millis;
		position[1] += speed * sin( angle * M_PI / 180.0 ) / 1000.0f * millis;
	}
	
	void Renderable :: setColor( float r , float g , float b ) {
		rgb[0] = r;
		rgb[1] = g;
		rgb[2] = b;
	}


	void Renderable :: draw() {
		glPushMatrix();
		glColor3fv( rgb );
		
		glTranslatef( position[0] , position[1] , position[2] );
		glScalef( scalar , scalar , scalar );
		glRotatef( rotation_angle , rotationAxis[0] , rotationAxis[1] , rotationAxis[2] );
		model->draw();
		
		glPopMatrix();
	}

}
