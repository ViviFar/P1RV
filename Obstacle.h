#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "Vector3D.h"
#include "Player.h"
class Obstacle{
	private:
		Player * player;
		Vector3D pos;
		int hauteur;
		int numVoie;

	public:
		Obstacle(Player * p, int voie, int profondeur);//on créé et on place l'obstacle selon le numero 
											//de la voie à la distance z = profondeur 
											//(le joueur commence en 120 et se deplace vers les negatifs)
		Vector3D getPos() const;
		int getHauteur() const;
		bool estEnContact();
		void drawObstacle();
};