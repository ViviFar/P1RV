#include "Obstacle.h"

Obstacle::Obstacle(Player * p,int voie, int profondeur){
	player = p;
	pos = Vector3D(-12.5+5*voie, 0.1, profondeur);
	hauteur = 2;
	numVoie = voie;
}

Vector3D Obstacle::getPos() const{
	return(pos);
}

int Obstacle::getHauteur() const{
	return(hauteur);
}


// Calcule si le joueur est rentré dans l'obstacle. La hitbox de l'obstacle est plus petite que l'obstacle en lui même pour
// laisser une marge de manoeuvre au joueur.
bool Obstacle::estEnContact(){
	bool res = false;
	if((*player).getPos().getVz()>pos.getVz() -0.5 && (*player).getPos().getVz()<pos.getVz()+0.5 && (*player).getPos().getVy()<2 && ((*player).getNumVoie() == numVoie)){
		res = true;
	}
	return res;
}

void Obstacle::drawObstacle(){
   glColor3f(0.5f, 0.5f, 0.5f);
   glTranslatef(0.0f,-1.0f,0.0f);
   glutSolidCube(5);
}
