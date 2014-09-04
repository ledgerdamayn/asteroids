/*
*	A Vertex is a collection of three points.
*	Can represent either cartesian or spherical coordinates.
*
*	TO-DO: Create a vertex buffer to avoid memory allocation during game execution.
*/

namespace Asteroids {

	class Vertex {

	public :

		float position[3];

		Vertex();
		Vertex( float , float , float );
		~Vertex();
		
		void toSpherical();
		void toCartesian();

	};

}
