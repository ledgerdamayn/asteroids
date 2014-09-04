
#include "Model.h"

namespace Asteroids {

	class Renderable {

	public :

		float position[3];
		float rotationAxis[3];
		float angle , scale;
		float rgb[3]; // Global/default color
		
		Model * model;

		virtual void draw() = 0;

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