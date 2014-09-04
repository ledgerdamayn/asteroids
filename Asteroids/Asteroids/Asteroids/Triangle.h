
#include "Vertex.h"

namespace Asteroids {

	class Triangle {

	public :

		Vertex * v[3];
		float rgb[3];

		Triangle();
		Triangle( Vertex * , Vertex * , Vertex * );
		Triangle( Vertex * , Vertex * , Vertex * , float , float , float );
		~Triangle();

		void draw();

	};

}