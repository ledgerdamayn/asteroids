
#include "Renderable.h"

namespace Asteroids {


	void Renderable :: translate( float x , float y , float z ) {
		position[0] += x;
		position[1] += y;
		position[2] += z;
	}

	
	void Renderable :: scale( float scalar ) {
		this->scalar *= scalar;
	}


	void Renderable :: rotate( float rotation ) {
		angle += rotation;
	}


	void Renderable :: setPosition( float x , float y , float z ) {
		position[0] = x;
		position[1] = y;
		position[2] = z;
	}


	void Renderable :: setScale( float scalar ) {
		this->scalar = scalar;
	}


	void Renderable :: setAngle( float angle ) {
		this->angle = angle;
	}


	void Renderable :: setRotationAxis( float x , float y , float z ) {
		rotationAxis[0] = x;
		rotationAxis[1] = y;
		rotationAxis[2] = z;
	}


	void Renderable :: setColor( float r , float g , float b ) {
		rgb[0] = r;
		rgb[1] = g;
		rgb[2] = b;
	}


}
