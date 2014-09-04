
#include "Triangle.h"

namespace Asteroids {

	class Model {

	public :

		Triangle ** triangles;
		
		Model();
		~Model();
		
		// Draws model, assuming transformations have already been performed.
		virtual void draw();

	};

}
