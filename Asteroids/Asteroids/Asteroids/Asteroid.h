
#include "Renderable.h"

namespace Asteroids {

	class Asteroid : Renderable {

	public :

		Asteroid(); // Radius = 0.5 , Centered about origin, Perturb = 50, Rotates about z-axis, White
		Asteroid( float , float , float , float , int ); // Scale , Color , Perturb
		~Asteroid();

		void draw();

	};

}