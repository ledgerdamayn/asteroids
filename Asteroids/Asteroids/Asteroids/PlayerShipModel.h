#ifndef PLAYERSHIPMODEL_H
#define PLAYERSHIPMODEL_H

#include "TriangleModel.h"

namespace Asteroids {

	class PlayerShipModel : public TriangleModel {

	public :
	
		Vertex * head;
		Vertex ** base;

		PlayerShipModel();
		~PlayerShipModel();

	};

}

#endif