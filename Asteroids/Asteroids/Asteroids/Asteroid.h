#ifndef ASTEROID_H
#define ASTEROID_H

#include "Renderable.h"

namespace Asteroids {

	class Asteroid : public Renderable {

	public :

		Asteroid(); // Radius = 0.5 , Centered about origin, Perturb = 50, Rotates about z-axis, White
		Asteroid( float , float , float , float , int ); // Scale , Color , Perturb
		~Asteroid();

		void draw();

	};

}

#endif