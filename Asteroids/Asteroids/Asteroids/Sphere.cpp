
#include "Sphere.h"
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

namespace Asteroids {
	
	Sphere :: Sphere() {
		radius = 0.5f;
		slices = 1;
		points = 3;

		top = new Vertex( radius , 0.0f , 0.0f );
		bottom = new Vertex( radius , M_PI , 0.0f );

		v = new Vertex ** [slices];
		
		for ( int i = 0 ; i < slices ; ++i )
			v[i] = new Vertex * [points];

		float sectionArcLength = M_PI / ( slices + 1 );
		float pointArcLength = 2 * M_PI / points; 

		v[0][0] = new Vertex( radius , sectionArcLength , 0.0f );
		v[0][1] = new Vertex( radius , sectionArcLength , pointArcLength );
		v[0][2] = new Vertex( radius , sectionArcLength , pointArcLength * 2 );
	}


	Sphere :: Sphere( float radius , int slices , int points ) {
		this->radius = radius;
		this->slices = slices;
		this->points = points;

		top = new Vertex( radius , 0.0f , 0.0f );
		bottom = new Vertex( radius , M_PI , 0.0f );

		v = new Vertex ** [slices];
		
		for ( int i = 0 ; i < slices ; ++i )
			v[i] = new Vertex * [points];

		float sectionArcLength = M_PI / ( slices + 1 );
		float pointArcLength = 2 * M_PI / points; 

		for ( int i = 0 ; i < slices ; ++i ) {
			for ( int j = 0 ; j < points ; ++j ) {
				if ( ( i % 2 ) == 0 ) {
					v[i][j] = new Vertex( radius , sectionArcLength * ( i + 1 ) , pointArcLength * j ); 
				} else { 
					v[i][j] = new Vertex( radius , sectionArcLength * ( i + 1 ) , pointArcLength / 2.0f + pointArcLength * j );
				}
			}
		}
	}


	Sphere :: ~Sphere() {
		for ( int i = 0 ; i < slices ; ++i ) { 
			for ( int j = 0 ; j < points ; ++j ) {
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

		for ( int i = 0 ; i < slices ; ++i ) {
			for ( int j = 0 ; j < points ; ++j ) {
				v[i][j]->perturb( percent );
			}
		}
	}


	void Sphere :: toCartesian() {
		top->toCartesian();
		bottom->toCartesian();

		for ( int i = 0 ; i < slices ; ++i ) {
			for ( int j = 0 ; j < points ; ++j ) {
				v[i][j]->toCartesian();
			}
		}
	}


}