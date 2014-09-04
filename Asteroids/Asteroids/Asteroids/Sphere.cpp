
#include "Sphere.h"
#include <stdlib.h>

#define PI 3.14159265

namespace Asteroids {
	
	Sphere :: Sphere() {
		radius = 0.5;
		slices = 1;
		points = 3;

		v = new Vertex ** [slices];
		
		for ( int i = 0 ; i < slices ; i++ )
			v[i] = new Vertex * [points];

		float sectionArcLength = PI / ( slices + 1 );
		float pointArcLength = 2 * PI / points; 

		top->set( 0.5f , 0.0f , 0.0f );
		bottom->set( 0.5f , PI , 0.0f );

		v[0][0]->set( 0.5f , sectionArcLength , 0.0f );
		v[0][1]->set( 0.5f , sectionArcLength , pointArcLength );
		v[0][2]->set( 0.5f , sectionArcLength , pointArcLength * 2 );
	}


	Sphere :: Sphere( float radius , int slices , int points ) {

	}


	Sphere :: ~Sphere() {
		for ( int i = 0 ; i < slices ; i++ ) { 
			for ( int j = 0 ; j < points ; j++ ) {
				delete v[i][j];
			}

			delete[] v[i];
		}

		delete[] v;
		delete top;
		delete bottom;
	}


	void Sphere :: perturb( int percent ) {
		top->perturb( percent );
		bottom->perturb( percent );

		for ( int i = 0 ; i < slices ; i++ ) {
			for ( int j = 0 ; j < points ; j++ ) {
				v[i][j]->perturb( percent );
			}
		}
	}


	void Sphere :: toCartesian() {
		top->toCartesian();
		bottom->toCartesian();

		for ( int i = 0 ; i < slices ; i++ ) {
			for ( int j = 0 ; j < points ; j++ ) {
				v[i][j]->toCartesian();
			}
		}
	}


}