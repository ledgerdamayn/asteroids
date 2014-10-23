#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Model.h"

namespace Asteroids {

	class Renderable {

	public :

		int index;

		float position[3];

		float rotationAxis[3];
		float rotation_angle , rotation_speed;
		
		float angle , spin_speed , speed , acceleration , scalar;
		
		float rgb[3]; // Global/default color
		
		Model * model;

		virtual void draw();

		void translate( float , float , float );
		void scale( float );
		void rotate( float );

		void setPosition( float , float , float );
		void setScale( float );
		
		void setRotationAxis( float , float , float );
		void setRotationAngle( float );
		void setRotationSpeed( float );

		void setAngle( float );
		void setSpinSpeed( float );
		void setSpeed( float );
		void setAcceleration( float );

		void wrapAround();
		void transform( int );

		void setColor( float , float , float );

	};


}

#endif