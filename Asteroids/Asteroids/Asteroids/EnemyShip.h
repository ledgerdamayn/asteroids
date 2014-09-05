
#include "Renderable.h"

namespace Asteroids {

	class EnemyShip : public Renderable {

	public :

		EnemyShip(); // Radius = 0.5 , Centered about origin , Oriented in +y direction (rotates about y) , White
		~EnemyShip();

		void draw();

	};

}