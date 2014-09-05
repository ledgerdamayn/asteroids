#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>

#include "Asteroid.h"
#include "AsteroidModel.h"

namespace Asteroids {

	Asteroid :: Asteroid() {
		setPosition( 0.0f , 0.0f , 0.0f );
		setScale( 1.0f );
		setAngle( 0.0f );
		setRotationAxis( 0.0f , 0.0f , 1.0f );
		setColor( 1.0f , 1.0f , 1.0f );

		model = new AsteroidModel();
	}


	Asteroid :: Asteroid( float scalar , float r , float g , float b , int perturb ) {
		setPosition( 0.0f , 0.0f , 0.0f );
		setScale( scalar );
		setAngle( 0.0f );
		setRotationAxis( 0.0f , 0.0f , 1.0f );
		setColor( r , g , b );

		model = new AsteroidModel( 0.5 , 5 , 5 , perturb );
	}


	Asteroid :: ~Asteroid() {
		delete model;
	}


	void Asteroid :: draw() {
		glPushMatrix();
		glColor3fv( rgb );
		
		glTranslatef( position[0] , position[1] , position[2] );
		glScalef( scalar , scalar , scalar );
		glRotatef( angle , rotationAxis[0] , rotationAxis[1] , rotationAxis[2] );
		model->draw();
		
		glPopMatrix();
	}


}