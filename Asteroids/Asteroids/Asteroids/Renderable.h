#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "Model.h"

namespace Asteroids {

	class Renderable {

	public :

		float position[3];
		float rotationAxis[3];
		float angle , scalar;
		float rgb[3]; // Global/default color
		
		Model * model;

		virtual void draw();

		void translate( float , float , float );
		void scale( float );
		void rotate( float );

		void setPosition( float , float , float );
		void setScale( float );
		void setAngle( float );
		void setRotationAxis( float , float , float );

		void setColor( float , float , float );

	};


}

#endif