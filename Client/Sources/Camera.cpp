#include "Camera.hpp"
#include "GMath.hpp"
#include "Entity.hpp"

Camera::Camera(irr::IrrlichtDevice *device)
{
	this->_device = device;
	this->_distance = 40;
	this->_angle = 30.f;
	this->_angleOffset = 90.f;
	this->_curX = 0;
	this->_curY = 0;
	this->_curZ = 0;
}

void					Camera::updateCamera(Entity *player)
{
	iscene::ICameraSceneNode	*camera = this->_device->getSceneManager()->getActiveCamera();
	iscene::ISceneNode			*node = player->getNode();

	float yf = node->getAbsolutePosition().Y + this->_distance * sin(this->_angle / 180.f * M_PI);
	float d = this->_distance * cos(this->_angle / 180.f * M_PI);

	float a = (node->getRotation().Y - this->_angleOffset) / 180.0f * M_PI;

	float xf = node->getAbsolutePosition().X + sin(a) * d;
	float zf = node->getAbsolutePosition().Z + cos(a) * d;

	this->_curX = (this->_curX + xf) / 2;
	this->_curY = (this->_curY * 4 + yf) / 5;
	this->_curZ = (this->_curZ + zf) / 2;
	camera->setPosition(icore::vector3df(this->_curX, this->_curY, this->_curZ));
	camera->setTarget(node->getPosition());
}

void					Camera::setDevice(irr::IrrlichtDevice *device)
{
	this->_device = device;
}

irr::IrrlichtDevice*	Camera::getDevice() const
{
	return (this->_device);
}

void					Camera::addDistance(float d) {
	float sd = this->_distance - d;
	
	this->_distance = GMath::clamp(sd, MIN_DIST, MAX_DIST);
}

float					Camera::getDistance() const {
	return this->_distance;
}
