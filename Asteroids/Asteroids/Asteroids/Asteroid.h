#ifndef ASTEROID_H
#define ASTEROID_H

#include "Renderable.h"

namespace Asteroids {

	class Asteroid : public Renderable {

	public :
		
		float radius;
		int type;

		Asteroid();
		~Asteroid();

		void draw();

		void spawn();
		void fragment( Asteroid * , Asteroid * );

	};

}

#endif