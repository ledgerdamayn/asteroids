#ifdef _M_IX86
#include <windows.h>
#else
#include <stream.h>
#endif

#define _USE_MATH_DEFINES

#include <GL/gl.h>
#include <GL/glu.h>
#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "Collision.h"
#include <iostream>


namespace Asteroids {


	bool point_in_circle( float point[3] , float center[3] , float radius ) {
		float distance = sqrt( pow( point[0] - center[0] , 2 ) + pow( point[1] - center[1] , 2 ) );
		return ( distance <= radius );
	}


	bool line_segment_in_circle( Vertex * v1 , Vertex * v2 , float center[3] , float radius ) {
		float d_x = v2->x() - v1->x();
		float d_y = v2->y() - v1->y();
		float d = pow( d_x , 2 ) + pow( d_y , 2 );
		float d2 = ( v1->x() - center[0] ) * ( v2->y() - center[1] ) - ( v2->x() - center[0] ) * ( v1->y() - center[1] );
		float delta = pow( radius , 2 ) * d - pow( d2 , 2 );

	//	if ( delta >= 0.0f )
	//		std::cout << delta << " " << center[0] << " " << center[1] << " " << radius << "\n";

		if ( delta < 0.0f )
			return false;
		else {
			float sign_d_y = ( d_y < 0.0f ) ? -1.0f : 1.0f;
			float x1 = ( d2 * d_y + sign_d_y * d_x * sqrt( delta ) ) / d;
			float x2 = ( d2 * d_y - sign_d_y * d_x * sqrt( delta ) ) / d;
			float y1 = ( -1.0f * d2 * d_x + abs( d_y ) * sqrt( delta ) ) / d;
			float y2 = ( -1.0f * d2 * d_x - abs( d_y ) * sqrt( delta ) ) / d;

			if ( point_on_line_segment( x1 , y1 , v1 , v2 ) || point_on_line_segment( x2 , y2 , v1 , v2 ) )
				return true;
		}	

		return false;
	}


	bool point_on_line_segment( float x , float y , Vertex * v1 , Vertex * v2 ) {
		float cross_product = ( y - v1->y() ) * ( v2->x() - v1->x() ) - ( x - v1->x() ) * ( v2->y() - v1->y() );
		// std::cout << x << " " << y << "\n";
		// std::cout << cross_product << "\n";
		if ( abs( cross_product ) > 0.0000001f )
			return false;

		float dot_product = ( x - v1->x() ) * ( v2->x() - x ) + ( y - v1->y() ) * ( v2->y() - y );
		if ( dot_product < 0.0f )
			return false;

		float squared_length = pow( ( v2->x() - v1->x() ) , 2 ) + pow( ( v2->y() - v1->y() ) , 2 );
		if ( dot_product > squared_length ) 
			return false;

		return true;
	}


	bool line_segment_intersection( Vertex * v1_1 , Vertex * v1_2 , Vertex * v2_1 , Vertex * v2_2 ) {
		float d = ( v2_2->y() - v2_1->y() ) * ( v1_2->x() - v1_1->x() ) - ( v2_2->x() - v2_1->x() ) * ( v1_2->y() - v1_1->y() ); 
		float t1 = ( v2_2->x() - v2_1->x() ) * ( v1_1->y() - v2_1->y() ) - ( v2_2->y() - v2_1->y() ) * ( v1_1->x() - v2_1->x() ); 
		float t2 = ( v1_2->x() - v1_1->x() ) * ( v1_1->y() - v2_1->y() ) - ( v1_2->y() - v1_1->y() ) * ( v1_1->x() - v2_1->x() );

		if ( d == 0 )
			return ( t1 == 0 || t2 == 0 );

		t1 /= d;
		t2 /= d;

		return ( t1 > 0 && t1 < 1 && t2 > 0 && t2 < 1 );
	}


	// TO-DO: Prevent creation of repeated Vertex objects
	bool point_in_triangle( Vertex * point , Triangle * triangle ) {
		int intersections = 0;
		Vertex * v = new Vertex( 100000.0f , 100000.0f , 0 );
		
		if ( line_segment_intersection( point , v , triangle->v[0] , triangle->v[1] ) )
			intersections += 1;

		if ( line_segment_intersection( point , v , triangle->v[1] , triangle->v[2] ) )
			intersections += 1;

		if ( line_segment_intersection( point , v , triangle->v[2] , triangle->v[0] ) )
			intersections += 1;

		return ( intersections % 2 != 0 );
	}


}