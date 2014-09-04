/*
*	An AsteroidModel generates a randomized unit model given parameters:
*		sphere - contains vertices comprising a sphere approximation in space
*		perturb - the minimum percentage that a particular vertex can be "perturbed," or have
*			it's distance from the center of sphere (rho) reduced.
*/


#include "Model.h"
#include "Sphere.h"

namespace Asteroids {

	class AsteroidModel : Model {

	public :

		Sphere * sphere;
		int perturb;

		AsteroidModel(); // Default sphere, Perturb = 50
		AsteroidModel( float , int , int , int );
		~AsteroidModel();

	};

}