#ifndef MODEL_H
#define MODEL_H

namespace Asteroids {

	class Model {

	public :

		// Draws model, assuming transformations have already been performed.
		virtual void draw() = 0;

	};

}

#endif