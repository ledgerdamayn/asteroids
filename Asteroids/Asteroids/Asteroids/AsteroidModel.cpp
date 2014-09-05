
#include "AsteroidModel.h"
#include <iostream>

namespace Asteroids {

	
	AsteroidModel :: AsteroidModel() {
		sphere = new Sphere();
		sphere->perturb( 50 );
		sphere->toCartesian();

		for ( int i = 0 ; i < sphere->points ; ++i ) {
			triangles.push_back( new Triangle( sphere->top , sphere->v[0][i] , sphere->v[0][ (i+1) % sphere->points ] ) );
		}
		
		for ( int i = 1 ; i <= sphere->points ; ++i )
			triangles.push_back( new Triangle( sphere->bottom , sphere->v[0][i % sphere->points] , sphere->v[0][i - 1] ) );
	}


	AsteroidModel :: AsteroidModel( float radius , int slices , int points , int perturb ) {
		sphere = new Sphere( radius , slices , points );
		sphere->perturb( perturb );
		sphere->toCartesian();

		for ( int i = 0 ; i < sphere->points ; ++i )
			triangles.push_back( new Triangle( sphere->top , sphere->v[0][i] , sphere->v[0][ (i+1) % points ] ) );
		
		for ( int i = 0 ; i < slices - 1 ; ++i ) {
			for ( int j = 1 ; j < points + 1 ; ++j ) {
				if ( i % 2 == 0 ) {
					triangles.push_back( new Triangle( sphere->v[i][ j % points ] , sphere->v[i+1][ j % points ] , sphere->v[i][ (j+1) % points ] ) );
				} else {
					triangles.push_back( new Triangle( sphere->v[i][ j % points ] , sphere->v[i+1][ (j-1) % points ] , sphere->v[i+1][ j % points ] ) );
				}
			}
		}

		for ( int i = 1 ; i <= sphere->points ; ++i )
			triangles.push_back( new Triangle( sphere->bottom , sphere->v[slices-1][i % points] , sphere->v[slices-1][i - 1] ) );
	}


	AsteroidModel :: ~AsteroidModel() {
		delete sphere;
	}

}