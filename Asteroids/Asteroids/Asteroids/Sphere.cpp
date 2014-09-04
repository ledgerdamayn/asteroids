
#include "Sphere.h"

#define PI 3.14159265

namespace Asteroids {
	
	Sphere :: Sphere() {
		v = new Vertex ** [3];
		
		for ( int i = 0 ; i < 3 ; i++ )
			v[i] = new Vertex * [3];

		float sectionArcLength = PI / 2;
		float pointArcLength = PI * 2.0f / 3; 

		v[0][0]->set( 0.5f , 0.0f , 0.0f );
		v[2][0]->set( 0.5f , PI , 0.0f );

		v[1][0]->set( 0.5f , sectionArcLength , 0.0f );
		v[1][0]->set( 0.5f , sectionArcLength , pointArcLength );
		v[1][0]->set( 0.5f , sectionArcLength , pointArcLength * 2 );
	}


	Sphere :: Sphere( float radius , int slices , int points ) {

	}


	Sphere :: ~Sphere() {
		for ( int i = 0 ; i < slices + 2 ; i++ ) { 
			for ( int j = 0 ; j < points ; j++ ) {
				delete v[i][j];
			}

			delete[] v[i];
		}

		delete[] v;
	}

}