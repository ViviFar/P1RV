#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include"Vector3D.h"


class Player{
	private:
		int numVoie; // il y a 4 voies numérotées de 1 à 4, le joueur est sur l'une d'entre elle
		Vector3D pos;
		bool isJumping; //le joueur peut sauter au dessus des obstacles mais n'a pas de double saut
		Vector3D speed;
		bool isInvincible;
		bool playerIsMoving;
		bool canBeInvincible;

	public:
		Player();
		
		void reset(); //to restart the game


		int getNumVoie() const;
		Vector3D getPos() const;
		void setPos(Vector3D position);
		void setY(double posY);
		bool getIsJumping() const;
		void setIsJumping(bool jump);
		Vector3D getSpeed() const;
		void setSpeedY(double speedY);
		bool getInvincible();
		void updateInvincible();
		bool getIsMoving();
		void setIsMoving(bool newState);
		bool getCanInvincible();

		void deplacement(unsigned char key);
		void accelerate(float vit);
		void stop();
		void jump();

		void drawPlayer();
};

/**/