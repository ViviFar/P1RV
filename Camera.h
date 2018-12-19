#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Player.h"

class Camera
{
	private:
		Player * player;
		Vector3D posCam;

	public:
		Camera(Player * p);
		Vector3D getPosCam();
		void setPosCam(Vector3D pos);
		void updateCamera();
};