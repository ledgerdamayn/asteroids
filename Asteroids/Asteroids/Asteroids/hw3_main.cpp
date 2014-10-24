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
#include "Collision.h"

#include <iostream>
#include <list>
	

// Prototypes

void init( void );
void display( void );
void render( void );
void handleMenu( int );
void checkCollisions();
void transform( int );
void keyDown( unsigned char , int , int );
void keyUp( unsigned char , int , int );
void specialDown( int , int , int );
void specialUp( int , int , int );
	


// Global Variables

int asteroid_count = 4;
int laser_count = 0;

Asteroids::Asteroid * asteroid_buffer[100];
std::list<int> free_asteroids;
std::list<int> active_asteroids;

Asteroids::Laser * laser_buffer[100];
std::list<int> free_lasers;
std::list<int> active_lasers;

Asteroids::PlayerShip * playerShip;
Asteroids::EnemyShip * enemyShip;


// Methods

void init() {
	srand( time( NULL ) );

	for ( int i = 0 ; i < 100 ; ++i ) {
		asteroid_buffer[i] = new Asteroids::Asteroid();
		free_asteroids.push_back( i );
	}

	for ( int i = 0 ; i < 4 ; ++i ) {
		asteroid_buffer[free_asteroids.front()]->spawn();
		active_asteroids.push_back( free_asteroids.front() );
		free_asteroids.pop_front();
	}

	for ( int i = 0 ; i < 100 ; ++ i ) {
		laser_buffer[i] = new Asteroids::Laser();
		free_lasers.push_back( i );
	}

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
	for ( std::list<int>::iterator i = active_asteroids.begin() ; i != active_asteroids.end() ; ++i ) {
		asteroid_buffer[*i]->draw();
	}

//	playerShip->current_bound->draw();
	playerShip->draw();

	for ( std::list<int>::iterator i = active_lasers.begin() ; i != active_lasers.end() ; ++i )
		laser_buffer[ *i ]->draw();

}

void handleMenu( int id ) {
	switch( id ) {
	case 0 :		// Quit
		exit( 0 );
	}
}


void checkCollisions() {
	bool collision = false;
	std::list<int> removed;

	// Laser with asteroid
	for ( std::list<int>::iterator i = active_lasers.begin() ; i != active_lasers.end() ; ++i ) {
		for ( std::list<int>::iterator j = active_asteroids.begin() ; j != active_asteroids.end() ; ++j ) {			
			if ( Asteroids::point_in_circle( laser_buffer[*i]->position , asteroid_buffer[*j]->position , asteroid_buffer[*j]->radius ) ) {
				removed.push_back( *i );

				if ( asteroid_buffer[*j]->type == SMALL ) {
					active_asteroids.remove( *j );
					free_asteroids.push_back( *j );
				} else {
					int a = free_asteroids.front();
					free_asteroids.pop_front();
					int b = free_asteroids.front();
					free_asteroids.pop_front();

					active_asteroids.push_back( a );
					active_asteroids.push_back( b );

					asteroid_buffer[*j]->fragment( asteroid_buffer[a] , asteroid_buffer[b] );	
					active_asteroids.remove( *j );
					free_asteroids.push_back( *j );
				}

				collision = true;
				break;
			}
		}

		if ( collision )
			break;
	}

	for ( std::list<int>::iterator i = removed.begin() ; i != removed.end() ; ++i ) {
		free_lasers.push_back( *i );
		active_lasers.remove( *i );
		laser_count--;
	}


	// Ship with asteroid
	collision = false;
	playerShip->updateBounds();

	for ( std::list<int>::iterator i = active_asteroids.begin() ; i != active_asteroids.end() ; ++i ) {			
		
	//	std::cout << "\n";

		for ( int j = 0 ; j < 3 ; ++j ) {
			
		//	std::cout << playerShip->current_bound->v[j]->x() << " " <<
		//			     playerShip->current_bound->v[j]->y() << " " <<
		//				 " " << 
		//				 playerShip->current_bound->v[ (j+1) % 3 ]->x() << " " <<
		//				 playerShip->current_bound->v[ (j+1) % 3 ]->y() << "\n";

			if ( Asteroids::line_segment_in_circle( playerShip->current_bound->v[j] , 
													playerShip->current_bound->v[ (j+1) % 3 ] ,
													asteroid_buffer[*i]->position ,
													asteroid_buffer[*i]->radius ) ) {
				if ( asteroid_buffer[*i]->type == SMALL ) {
					active_asteroids.remove( *i );
					free_asteroids.push_back( *i );
				} else {
					int a = free_asteroids.front();
					free_asteroids.pop_front();
					int b = free_asteroids.front();
					free_asteroids.pop_front();

					active_asteroids.push_back( a );
					active_asteroids.push_back( b );

					asteroid_buffer[*i]->fragment( asteroid_buffer[a] , asteroid_buffer[b] );	
					active_asteroids.remove( *i );
					free_asteroids.push_back( *i );
				}

				playerShip->reset();

				collision = true;
				break;
			}
		}

		if ( collision )
			break;
	}

}

void transform( int x ) {
	for ( std::list<int>::iterator i = active_asteroids.begin() ; i != active_asteroids.end() ; ++i ) {
		asteroid_buffer[*i]->transform( TIMER_FREQUENCY );
		asteroid_buffer[*i]->wrapAround();
	}

	playerShip->transform( TIMER_FREQUENCY );
	playerShip->wrapAround();

	std::list<int> removed;

	for ( std::list<int>::iterator i = active_lasers.begin() ; i != active_lasers.end() ; ++i ) {
		laser_buffer[*i]->transform( TIMER_FREQUENCY );
		laser_buffer[*i]->wrapAround();

		if ( laser_buffer[*i]->time > LASER_DURATION ) {
			removed.push_back( *i );
		}
	}

	for ( std::list<int>::iterator i = removed.begin() ; i != removed.end() ; ++i ) {
		free_lasers.push_back( *i );
		active_lasers.remove( *i );
		laser_count--;
	}

	checkCollisions();

	// Win condition
	if ( active_asteroids.size() == 0 )
		init();

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
			active_lasers.push_back( free_lasers.front() );
			playerShip->shoot( laser_buffer[ free_lasers.front() ] );
			free_lasers.pop_front();
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

