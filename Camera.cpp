#include "Camera.h"

Camera::Camera(Player * p){
	player = p;
	posCam = Vector3D(0, 10, (*player).getPos().getVz()+10);
}

Vector3D Camera::getPosCam(){
	return posCam;
}

void Camera::setPosCam(Vector3D pos){
	posCam = pos;
}

void Camera::updateCamera(){
	posCam = Vector3D(0, 10, (*player).getPos().getVz()+10);
}