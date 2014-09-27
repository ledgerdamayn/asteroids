#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include "Renderable.h"
#include "Laser.h"

namespace Asteroids {

	class PlayerShip : public Renderable {

	public :

		PlayerShip(); // Radius = 0.5 , Centered about origin , Oriented in +y direction (rotates about y) , White
		PlayerShip( float , float , float , float );
		~PlayerShip();
		
		Laser * shoot();
		void transform( int );
		void draw();

	};

}

#endif