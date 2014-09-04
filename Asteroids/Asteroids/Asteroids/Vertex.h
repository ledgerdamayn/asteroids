/*
*	A Vertex is a collection of three points.
*	Can represent either cartesian or spherical coordinates.
*
*	TO-DO: Create a vertex buffer to avoid memory allocation during game execution.
*/

namespace Asteroids {

	class Vertex {

	public :

		float position[3]; // (x,y,z) or (rho,phi,theta)

		Vertex();
		Vertex( float , float , float );
		~Vertex();
		
		void set( float , float , float );

		void toSpherical();
		void toCartesian();

		double toRadians( float );
		float toDegrees( double );

	};

}
