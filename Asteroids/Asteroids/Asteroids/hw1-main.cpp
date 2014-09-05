#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Asteroid.h"
#include "PlayerShip.h"
#include "EnemyShip.h" 

namespace Asteroids {

	
	// Prototypes

	void init( void );
	void display( void );
	void handleMenu( int );
	void transform( int );


	// Global Variables

	int timerFrequency = 50; // 20 times/sec
	int rotationSpeed = 0.5f; // Full rotations/second


	Asteroid * asteroid;
	PlayerShip * playerShip;
	EnemyShip * enemyShip;


	// Methods

	void init() {
		srand( time( NULL ) );

		asteroid = new Asteroid();
		asteroid->setRotationAxis( 1.0f , 0.0f , 0.0f );
		asteroid->setPosition( 0.0f , -3.0f , 0.0f );
		asteroid->setColor( rand() % 255 , rand() % 255 , rand() % 255 );
	}


	void transform() {
		
	}


	// Callback functions

	void display() {
		glMatrixMode( GL_MODELVIEW );
		
		asteroid->draw();
	}


	void handleMenu( int id ) {
		switch( id ) {
		case 0 :		// Quit
			exit( 0 );
		}
	}


	void transform( int x ) {

	}


	// Main method

	void main( int argc , char * argv[] ) {
		init();
		
		glutInit( &argc , argv );
		glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
		glutCreateWindow( "Homework 1 - Modelling and Rendering" );

		glutDisplayFunc( display );
		glutTimerFunc( timerFrequency , transform , 1 );

		glutCreateMenu( handleMenu );
		glutAddMenuEntry( "Quit" , 0 );
		glutAttachMenu( GLUT_RIGHT_BUTTON );

		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluLookAt( 0 , 0 , 5 , 0 , 0 , -1 , 0 , 1 , 0 );

		glShadeModel( GL_SMOOTH );
		glClearDepth( 1.0 );
		glClearColor( 0 , 0 , 0 , 0 );
		glEnable( GL_DEPTH_TEST );

		glutMainLoop();
	}

}
