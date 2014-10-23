#ifndef ASTEROID_H
#define ASTEROID_H

#include "Renderable.h"

namespace Asteroids {

	class Asteroid : public Renderable {

	public :

		Asteroid(); // Radius = 0.5 , Centered about origin, Perturb = 50, Rotates about z-axis
		Asteroid( int ); // Perturb
		~Asteroid();

		void draw();

		void initialize( int );

	};

}

#endif