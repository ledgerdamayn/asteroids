/*
*	A Vertex is a collection of three points.
*	Can represent either cartesian or spherical coordinates.
*
*	Traditional spherical coordinates are usually defined with respect to the z-axis, however,
*	for the purposes of rendering in OpenGL, the coordinates have been rotated to be about the y-axis.
*	
*	Phi = Angle from +y-axis to line connecting origin to point
*	Theta = Angle from +z-axis to line connecting origin to point, projected onto the xz-plane
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
