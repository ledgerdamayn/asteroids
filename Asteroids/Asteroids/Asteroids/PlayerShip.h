#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "Renderable.h"
#include "Laser.h"
#include "Triangle.h"


namespace Asteroids {

	class PlayerShip : public Renderable {

	public :
		
		Triangle * start_bound; // Absolute positions
		Triangle * current_bound;

		PlayerShip( float , float , float , float );
		~PlayerShip();
		
		void reset();
		void shoot( Laser * );
		void transform( int );
		void draw();

		void updateBounds();

	};

}

#endif