#ifndef COLLISION_H
#define COLLISION_H

#include "Vertex.h"
#include "Triangle.h"

namespace Asteroids {

	bool point_in_circle( float * , float * , float );
	bool line_segment_in_circle( Vertex * , Vertex * , float * , float );
	bool point_on_line_segment( float , float , Vertex * , Vertex * );
	bool line_segment_intersection( Vertex * , Vertex * , Vertex * , Vertex * );
	bool point_in_triangle( Vertex * , Triangle * );

}

#endif