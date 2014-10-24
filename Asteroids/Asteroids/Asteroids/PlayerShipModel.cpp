
#include "PlayerShipModel.h"

namespace Asteroids {


	PlayerShipModel :: PlayerShipModel() {
		head = new Vertex( 0.5 , 0.0 , 0 );
		base = new Vertex * [4];
		
		base[0] = new Vertex( -0.5f , 0 , 0.25f );
		base[1] = new Vertex( -0.4f , -0.5f , 0 );
		base[2] = new Vertex( -0.5f , 0 , -0.25f );
		base[3] = new Vertex( -0.4f , 0.5f , 0 );

		for ( int i = 0 ; i < 4 ; ++i )
			triangles.push_back( new Triangle( head , base[i] , base[ (i+1) % 4 ] ) );
	}


	PlayerShipModel :: ~PlayerShipModel() {
		delete head;
		for ( int i = 0 ; i < 4 ; ++i )
			delete base[i];
		delete[] base;
	}


}