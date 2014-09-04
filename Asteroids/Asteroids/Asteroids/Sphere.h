/*
*	A Sphere is a container for information that can be utilized by models to make
*	approximations of spheres.
*
*	Spheres cannot be drawn directly.  They construct vertices in the form:
*	
*	[ slice ][ point ]
*	
*	within an array with dimensions ( slices ) x points, plus references to the top and bottom vertices.
*
*
*	TO-DO: Use a 1-d array
*/

#include "Vertex.h"

namespace Asteroids {

	class Sphere {

	public :

		float radius;
		int slices , points;
		Vertex *** v;
		Vertex * top , * bottom;

		Sphere(); // Radius = 0.5 , Slices = 1 , Points = 3
		Sphere( float , int , int );
		~Sphere();

		void perturb( int );
		void toCartesian();

	};

}
