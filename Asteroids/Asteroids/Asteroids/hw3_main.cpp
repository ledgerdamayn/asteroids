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

#include "Model.h"
#include "Asteroid.h"
#include "PlayerShip.h"
#include "EnemyShip.h"
#include "Constants.h"
#include "Laser.h"

#include <iostream>
#include <list>
	

// Prototypes

void init( void );
void display( void );
void render( void );
void handleMenu( int );
void transform( int );
void keyDown( unsigned char , int , int );
void keyUp( unsigned char , int , int );
void specialDown( int , int , int );
void specialUp( int , int , int );
	


// Global Variables

int asteroid_count = 4;
int laser_count = 0;

std::list<Asteroids::Asteroid *> asteroids;
std::list<Asteroids::Laser *> lasers;

Asteroids::PlayerShip * playerShip;
Asteroids::EnemyShip * enemyShip;


// Methods

void init() {
	srand( time( NULL ) );

	for ( int i = 0 ; i < asteroid_count ; ++i )
		asteroids.push_back( new Asteroids::Asteroid( 75 , LARGE ) );

	for ( std::list<Asteroids::Asteroid *>::iterator i = asteroids.begin() ; i != asteroids.end() ; ++i )
		(*i)->spawn();

	playerShip = new Asteroids::PlayerShip( SCREEN_SIZE * SHIP_SIZE / 100.0f ,
											static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
											static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ,
											static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) );
}



// Callback functions

void display() {
	glMatrixMode( GL_MODELVIEW );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glLoadIdentity();
	gluLookAt( 0 , 0 , 10 , 0 , 0 , -1 , 0 , 1 , 0 );

	render();

	glPushMatrix();
		glTranslatef( SCREEN_SIZE , 0 , 0 );
		render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef( 0 - SCREEN_SIZE , 0 , 0 );
		render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef( 0 , SCREEN_SIZE , 0 );
		render();
	glPopMatrix();

	glPushMatrix();
		glTranslatef( 0 , 0 - SCREEN_SIZE , 0 );
		render();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}


void render() {
	for ( std::list<Asteroids::Asteroid *>::iterator i = asteroids.begin() ; i != asteroids.end() ; ++i )
		(*i)->draw();

	playerShip->draw();

	for ( std::list<Asteroids::Laser *>::iterator i = lasers.begin() ; i != lasers.end() ; ++i )
		(*i)->draw();

}

void handleMenu( int id ) {
	switch( id ) {
	case 0 :		// Quit
		exit( 0 );
	}
}


void transform( int x ) {
	for ( std::list<Asteroids::Asteroid *>::iterator i = asteroids.begin() ; i != asteroids.end() ; ++i ) {
		(*i)->transform( TIMER_FREQUENCY );
		(*i)->wrapAround();
	}

	playerShip->transform( TIMER_FREQUENCY );
	playerShip->wrapAround();

	for ( std::list<Asteroids::Laser *>::iterator i = lasers.begin() ; i != lasers.end() ; ++i ) {
		(*i)->transform( TIMER_FREQUENCY );
		(*i)->wrapAround();
	}

	if ( ! lasers.empty() && lasers.front()->time > LASER_DURATION ) {
		lasers.pop_front();
		laser_count--;
	}
	
	glutPostRedisplay();
	glutTimerFunc( TIMER_FREQUENCY , transform , 1 );
}


void keyDown( unsigned char key , int mouseX , int mouseY ) {
	switch( key ) {
	case 'x' :
		playerShip->acceleration = SHIP_ACCELERATION;
		break;
	case 'z' :
		if ( laser_count < MAX_LASERS ) {
			lasers.push_back( playerShip->shoot() );
			laser_count++;
		}
			
		break;
	}
}


void keyUp( unsigned char key , int mouseX , int mouseY ) {
	switch( key ) {
	case 'x' :
		playerShip->acceleration = 0.0f;
		break;
	}
}


void specialDown( int key , int mouseX , int mouseY ) {
	switch( key ) {
	case GLUT_KEY_LEFT :
		playerShip->spin_speed = SHIP_ROTATION_SPEED;
		break;
	case GLUT_KEY_RIGHT :
		playerShip->spin_speed = 0.0f - SHIP_ROTATION_SPEED;
		break;
	}
}


void specialUp( int key , int mouseX , int mouseY ) {
	switch( key ) {
	case GLUT_KEY_LEFT :
		playerShip->spin_speed = 0.0f;
		break;
	case GLUT_KEY_RIGHT :
		playerShip->spin_speed = 0.0f;
		break;
	}
}


// Main method

void main( int argc , char * argv[] ) {
	glutInit( &argc , argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize( 500 , 500 );
	glutCreateWindow( "Homework 1 - Modelling and Rendering" );

	init();
	glutDisplayFunc( display );
	glutTimerFunc( TIMER_FREQUENCY , transform , 1 );

	glutCreateMenu( handleMenu );
	glutAddMenuEntry( "Quit" , 0 );
	glutAttachMenu( GLUT_RIGHT_BUTTON );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( -100 , 100 , -100 , 100 , -50 , 100 );

	glShadeModel( GL_FLAT );
	glClearDepth( 1.0 );
	glClearColor( 0 , 0 , 0 , 0 );
	glEnable( GL_DEPTH_TEST );

	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	GLfloat light_position[] = { 0.0 , 0.0 , 10.0 , 0.0 };
	glLightfv( GL_LIGHT0 , GL_POSITION , light_position );

	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );

	glEnable( GL_DEPTH );
	glEnable( GL_NORMALIZE );

	glutKeyboardFunc( keyDown );
	glutKeyboardUpFunc( keyUp );
	glutSpecialFunc( specialDown );
	glutSpecialUpFunc( specialUp );

	glutMainLoop();
}

