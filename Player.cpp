#include "Player.h"

Player::Player(){
	numVoie = 3;
	pos = Vector3D(2.5f,0.1f,100.0f);
	isJumping = false;
	speed = Vector3D();
	isInvincible = false;
	playerIsMoving = false;
	canBeInvincible = true;
}

//Retour au début du jeu
void Player::reset(){
	numVoie = 3;
	pos = Vector3D(2.5f,0.1f,100.0f);
	isJumping = false;
	speed = Vector3D();
	isInvincible = false;
	playerIsMoving = false;
	canBeInvincible = true;
}


//getters and setters
int Player::getNumVoie() const{
	return(numVoie);
}


Vector3D Player::getPos() const{
	return(pos);
}

void Player::setPos(Vector3D position){
	pos = position;
}

void Player::setY(double posY){
	pos.setVy(posY);
}

bool Player::getIsJumping() const{
	return(isJumping);
}

void Player::setIsJumping(bool jump){
	isJumping=jump;
}

Vector3D Player::getSpeed() const{
	return(speed);
}

void Player::setSpeedY(double speedY){
	speed.setVy(speedY);
}

bool Player::getInvincible(){
	return isInvincible;
}


bool Player::getCanInvincible(){
	return canBeInvincible;
}

void Player::updateInvincible(){
	isInvincible=!isInvincible;
	canBeInvincible = false;
}


bool Player::getIsMoving(){
	return playerIsMoving;
}

void Player::setIsMoving(bool newState){
	playerIsMoving = newState;
}

//gestion du déplacement
void Player::deplacement(unsigned char key){
	switch(key) {
		//cas déplacement vers la gauche
		case 'q':
		case'Q':
			if(numVoie>1){
				numVoie--;
				pos.setVx(pos.getVx()-5);
			}
			break;
		//cas déplacement vers la droite
		case 'd':
		case'D':
			if(numVoie<4){
				numVoie++;
				pos.setVx(pos.getVx()+5);
			}
			break;
		//cas saut
		case 32:
			jump();
			isJumping = true;
			break;
		default:
			break;
	}
}

void Player::accelerate(float vit){
	//le déplacement se fait sur les z négatifs
	speed.setVz(speed.getVz() - vit);
}

void Player::stop(){
	speed = Vector3D();
}

void Player::jump(){
	if(!isJumping){
		speed.setVy(speed.getVy() + 2.5);
	}
}

void Player::drawPlayer() {
    glPushMatrix();
    glTranslatef(pos.getVx(),pos.getVy(),pos.getVz());
	if(!isInvincible){
		//A l'etat normal, on va dessiner en blanc
		glColor3f(1.0f, 1.0f, 1.0f);
	}
	else{
		//Si le joueur est invincible, on va desiner en rouge
		glColor3f(1.0f,0.0f,0.0f);
	}
   // Corps du joueur : une sphere
   glTranslatef(0.0f ,0.5f, 0.0f);
   glutSolidSphere(0.5f,20,20);
   
   // Tete du joueur : une sphere
   glTranslatef(0.0f, 0.7f, 0.0f);
   glutSolidSphere(0.2f,20,20);
    glPopMatrix();
}