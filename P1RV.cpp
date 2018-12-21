// P1RV.cpp : définit le point d'entrée pour l'application console.
//

#include <stdlib.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif



#include "vector3D.h"
#include "Player.h"
#include "Obstacle.h"
#include "Camera.h"

int numeroAcceleration = 1;

// Camera viewing vectors
Vector3D forwardView;
// On garde le vecteur "up" du monde : 0 1 0
Vector3D upWorld;

// booléens d'état du jeu: est ce que le joueur a terminé sa partie. Si oui, a-t-il gagné ou perdu
bool hasLost = false;
bool hasWin= false;

// Camera position
Vector3D targetPos;


int compteurInvincibilite = 0;

Player player = Player();
Camera cam = Camera(&player);


vector<Obstacle> obstacles;

//messages de fin
std::string loseMessage = "Tu dois eviter les obstacles, pas leur rentrer dedans";
std::string winMessage = "Congratulations ! You win !";


//fonction d'affichage des messages
void renderString(GLdouble x, GLdouble y,  std::string  message){
	glColor3f(1.0f,0.0f,0.0f);
	glRasterPos2f(x,y);
	
	for(std::string::iterator i=message.begin(); i!=message.end(); i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *i);
	}
}

// Fonction de redimensionnement de la fenetre
void redimensionner(int w, int h) {
   
   // On evite une division par 0
   // la fenetre ne peut avoir une largeur de 0
   if (h == 0)
      h = 1;
   
   // Calcul du ratio
   float ratio =  (w * 1.0) / h;
   
   // On passe en mode "matrice de projection"
   glMatrixMode(GL_PROJECTION);
   
   // on charge la matrice identite
   glLoadIdentity();
   
   // on definit le viewport pour prendre toute la fenetre
   glViewport(0, 0, w, h);
   
   // on definit la projection perspective
   gluPerspective(65.0f, ratio, 0.1f, 100.0f);
   
   // on repasse en mode "matrice modelview"
   glMatrixMode(GL_MODELVIEW);
}

// fonction d'affichage de notre scene 3D
void affichageScene() {
   // On efface les tampons de couleur et de profondeur
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   
   // On passe en matice modelview
   glMatrixMode(GL_MODELVIEW);
   
   // on charge la matrice identite
   glLoadIdentity();
   
   
   // on definit la position de la camera et ou elle regarde
   gluLookAt(cam.getPosCam().getVx(),cam.getPosCam().getVy(),cam.getPosCam().getVz(),targetPos.getVx(),targetPos.getVy(),targetPos.getVz(),upWorld.getVx(),upWorld.getVy(),upWorld.getVz());
   
   if(!hasLost && !hasWin){
   // On dessine le "sol" : un plan gris
   glColor3f(0.0f, 0.5f, 0.9f);
   glBegin(GL_QUADS);
   glVertex3f(-100.0f, 0.0f, -12000.0f);
   glVertex3f(-100.0f, 0.0f,  120.0f);
   glVertex3f( 100.0f, 0.0f,  120.0f);
   glVertex3f( 100.0f, 0.0f, -12000.0f);
   glEnd();
   

   //on dessine la route;
   glColor3f(0.1f, 0.1f, 0.1f);
   glBegin(GL_QUADS);
   glVertex3f(-10.0f, 0.1f, -12000.0f);
   glVertex3f(-10.0f, 0.1f,  120.0f);
   glVertex3f( 10.0f, 0.1f,  120.0f);
   glVertex3f( 10.0f, 0.1f, -12000.0f);
   glEnd();
   }


   //on affiche les obstacles
   for(int i=0; i < obstacles.size(); i++){
	    if(!player.getInvincible()){
			//on vérifie que le joueur n'a pas perdu
			hasLost = hasLost || obstacles[i].estEnContact();
	    }
		glPushMatrix();
		glTranslatef(obstacles[i].getPos().getVx(), obstacles[i].getPos().getVy(),obstacles[i].getPos().getVz());
		obstacles[i].drawObstacle();
		glPopMatrix();
   }
   
   //Si le joueur n'est pas en mouvement, on est au début du jeu donc on affiche l'instruction pour commencer
   if(!player.getIsMoving()){
		renderString(-15,10, "Press S to Start");
   }
   
   if(player.getIsMoving()){
		player.setPos(player.getPos() + player.getSpeed()/10);
		cam.updateCamera();
		//cas de victoire
		if(player.getPos().getVz() < -12000){
			cam.setPosCam(Vector3D(0,10,105));
			renderString(-25,10,winMessage);
			renderString(-20,0, "Press R to restart");
			player.stop();
			hasWin = true;
		}

		//cas de defaite
		if(hasLost){
			player.stop();
			cam.setPosCam(Vector3D(0,10,105));
			renderString(-50,10,loseMessage);
			renderString(-20,0, "Press R to restart");
		}

		//cas lorsque le joueur est invincible
		if(player.getInvincible()){
			compteurInvincibilite++;
			if(compteurInvincibilite==250){
				player.updateInvincible();
			}
		}

		//accélérations programmées pour rendre le jeu moins linéaire
		if(player.getPos().getVz() < -1500 && numeroAcceleration==1){
			numeroAcceleration ++;
			player.accelerate(2);
		}
		else if(player.getPos().getVz() < -4500 && numeroAcceleration==2){
			numeroAcceleration ++;
			player.accelerate(2);
		}
		else if(player.getPos().getVz() < -9000 && numeroAcceleration==3){
			numeroAcceleration ++;
			player.accelerate(2);
		}


   }
   else
   {
		cam.updateCamera();
   }

   //gestion du saut
   double posEnY = player.getPos().getVy();
   double speedEnY = player.getSpeed().getVy();
   if(posEnY>0.1){
		speedEnY-=0.981/10;
		posEnY+=speedEnY/10;
   }
   else{
		speedEnY=0;
		posEnY=0.1;
		player.setIsJumping(false);
   }
	player.setY(posEnY);
	player.setSpeedY(speedEnY);

	//affichage du joueur
    player.drawPlayer();
   
	// Mettre a jour la cible
	targetPos = cam.getPosCam()+forwardView;

   // on echange les tampons d'affichage
   glutSwapBuffers();
}

// Fonction de gestion du clavier (touche enfoncee)
void clavier(unsigned char key, int xx, int yy) {
   
   // Quelle touche a ete appuyee ?
   switch(key) {
         // Q et D on change de voie
      case 'q' :
      case 'Q' :
      case 'd' :
      case 'D' :
		  if(player.getIsMoving()){
			player.deplacement(key);
		  }
		  break;
		  // S pour lancer le jeu
      case 's' :
      case 'S' :
		  if(!player.getIsMoving()){
			player.accelerate(10);
			player.setIsMoving(true);
		  }
         break;
		 // A pour etre invincible
	  case 'a':
	  case 'A':
		  if(player.getCanInvincible()){
			player.updateInvincible();
			compteurInvincibilite = 0;
		  }
		  break;
		  // R pour relancer le jeu si l'on a gagné ou perdu
	  case 'r':
	  case 'R':
		  if(hasLost || hasWin){
			player.reset();
			numeroAcceleration=1;
			hasLost = false;
			hasWin = false;
		  }
		  // Space pour sauter
	  case 32:
		  player.deplacement(key);
		  break;

     // ESCAPE on termine l'application
      case 27 :
         exit(0);
         break;
   }
   
}





// Le main
int main(int argc, char **argv) {
	srand(time(NULL));

	// creation des obstacles
	for(int i=-400; i<0; i++){
		int voie = rand()%4 + 1;
		obstacles.push_back(Obstacle(&player, voie, i*30));
		voie = rand()%4 + 1;
		obstacles.push_back(Obstacle(&player, voie, i*30));
		voie = rand()%4 + 1;
		obstacles.push_back(Obstacle(&player, voie, i*30));
	}
   
   // init GLUT and create window
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
   glutInitWindowPosition(100,100);
   glutInitWindowSize(600,600);
   glutCreateWindow("P1RV");
   
   // enregistrement des callbacks d'affichage
   // de redimensionnement et d'idle
   glutDisplayFunc(affichageScene);
   glutReshapeFunc(redimensionner);
   glutIdleFunc(affichageScene);
   
   // pour que l'on puisse rester appuye sur les touches
   glutIgnoreKeyRepeat(1);
   
   // Declaration des callbacks clavier
   glutKeyboardFunc(clavier);
   
   
   // on active le tampon de profondeur
   glEnable(GL_DEPTH_TEST);
   
   // on initialise la position de la camera
   cam.setPosCam(Vector3D(0, 10, 106));
   
   // on initialise les vecteurs 'view'
   forwardView = Vector3D(0,-0.5,-1);
   upWorld = Vector3D(0,1,0);
   
   
   // on initialise la cible a partir de la camera et du vecteur vision
   targetPos = cam.getPosCam() + forwardView;
   
   
   // enter GLUT event processing cycle
   glutMainLoop();
   
   return 1;
}