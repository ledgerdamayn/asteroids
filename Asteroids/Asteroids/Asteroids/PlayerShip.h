
#include "Renderable.h"

namespace Asteroids {

	class PlayerShip : Renderable {

	public :

		PlayerShip(); // Radius = 0.5 , Centered about origin , Oriented in +y direction (rotates about y) , White
		~PlayerShip();

		void draw();

	};

}