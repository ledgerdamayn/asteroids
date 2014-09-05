#ifndef TRIANGLEMODEL_H
#define TRIANGLEMODEL_H

#include "Model.h"
#include "Triangle.h"
#include <list>

namespace Asteroids {

	class TriangleModel : public Model {

	public :

		std::list<Triangle *> triangles;
				
		// Draws model, assuming transformations have already been performed.
		virtual void draw();

	};

}

#endif
