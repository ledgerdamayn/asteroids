#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vertex.h"

namespace Asteroids {

	class Triangle {

	public :

		Vertex ** v;
		float rgb[3];

		Triangle();
		Triangle( Vertex * , Vertex * , Vertex * );
		Triangle( Vertex * , Vertex * , Vertex * , float , float , float );
		~Triangle();

		void draw();

	};

}

#endif