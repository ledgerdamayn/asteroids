#ifndef LASER_H
#define LASER_H

#include "Renderable.h"

namespace Asteroids {

	class Laser : public Renderable {

	public :

		int time;

		Laser();
		Laser( float , float , float , float , float );
		~Laser();

		void transform( int );
		void draw();

	};

}


#endif