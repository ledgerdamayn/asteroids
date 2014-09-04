
#include "AsteroidModel.h"

namespace Asteroids {

	
	AsteroidModel :: AsteroidModel() {
		sphere = new Sphere();
		sphere->perturb( 50 );
		sphere->toCartesian();

		for ( int i = 0 ; i < sphere->points ; i++ )
			triangles.push_back( new Triangle( sphere->top , sphere->v[1][i] , sphere->v[1][ (i+1) % sphere->points ] ) );

		
		for ( int i = 1 ; i <= sphere->points ; i++ )
			triangles.push_back( new Triangle( sphere->bottom , sphere->v[1][i % sphere->points] , sphere->v[1][i - 1] ) );
	}


	AsteroidModel :: AsteroidModel( float radius , int slices , int points , int perturb ) {

	}


	AsteroidModel :: ~AsteroidModel() {
		delete sphere;
	}

}