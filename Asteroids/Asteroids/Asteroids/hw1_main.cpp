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

#include "Model.h"
#include "Asteroid.h"
#include "PlayerShip.h"
#include "EnemyShip.h" 

#include <iostream>
	
// Prototypes

void init( void );
void display( void );
void handleMenu( int );
void transform( int );
	

// Global Variables

int timerFrequency = 50; // 20 times/sec
float rotationSpeed = 0.1f; // Full rotations/second
int windowSize = 500;

Asteroids::Asteroid * asteroid;
Asteroids::PlayerShip * playerShip;
Asteroids::EnemyShip * enemyShip;


// Methods

void init() {
	srand( time( NULL ) );

	asteroid = new Asteroids::Asteroid( 2.0f , 
						                static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
										static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
										static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
										75 );
	asteroid->setRotationAxis( 1.0f , 0.0f , 0.0f );
	asteroid->setPosition( 0.0f , 50.0f , 0.0f );
	asteroid->setColor( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) , 
					    static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
						static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );
	asteroid->setScale( 100.0f );

	playerShip = new Asteroids::PlayerShip();
	playerShip->setRotationAxis( 1.0f , 0.0f , 0.0f );
	playerShip->setPosition( -50.0f , -50.0f , 0.0f );
	playerShip->setColor( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) , 
					    static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
						static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );
	playerShip->setScale( 50.0f );

	enemyShip = new Asteroids::EnemyShip();
	enemyShip->setRotationAxis( 1.0f , 0.0f , 0.0f );
	enemyShip->setPosition( 50.0f , -50.0f , 0.0f );
	enemyShip->setColor( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) , 
					    static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
						static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );
	enemyShip->setScale( 50.0f );
}

// Callback functions

void display() {
	glMatrixMode( GL_MODELVIEW );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt( 0 , 0 , 10 , 0 , 0 , -1 , 0 , 1 , 0 );

	asteroid->draw();
	playerShip->draw();
	enemyShip->draw();

	glFlush();
	glutSwapBuffers();
}


void handleMenu( int id ) {
	switch( id ) {
	case 0 :		// Quit
		exit( 0 );
	}
}


void transform( int x ) {
	asteroid->angle += rotationSpeed * 360.0f / 1000.0f * timerFrequency;
	playerShip->angle += rotationSpeed * 360.0f / 1000.0f * timerFrequency;
	enemyShip->angle += rotationSpeed * 360.0f / 1000.0f * timerFrequency;

	glutPostRedisplay();
	glutTimerFunc( timerFrequency , transform , 1 );
}


// Main method
/*
void main( int argc , char * argv[] ) {
	glutInit( &argc , argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize( 500 , 500 );
	glutCreateWindow( "Homework 1 - Modelling and Rendering" );

	init();
	glutDisplayFunc( display );
	glutTimerFunc( timerFrequency , transform , 1 );

	glutCreateMenu( handleMenu );
	glutAddMenuEntry( "Quit" , 0 );
	glutAttachMenu( GLUT_RIGHT_BUTTON );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -100 , 100 , -100 , 100 , -50 , 100 );

	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0 );
	glClearColor( 0 , 0 , 0 , 0 );
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

//	GLfloat light_position[] = { 1.0 , 1.0 , 1.0 , 0.0 };
//	glLightfv( GL_LIGHT0 , GL_POSITION , light_position );

//	glEnable( GL_LIGHTING );
//	glEnable( GL_LIGHT0 );
//	glEnable( GL_COLOR_MATERIAL );

	glutMainLoop();
}
*/
