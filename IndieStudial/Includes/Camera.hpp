#ifndef CAMERA_H
# define CAMERA_H

# include "IncludeIrrlicht.hpp"
# include "Player.hpp"

# define MAX_DIST 200.f
# define MIN_DIST 10.f
# define STEP_DIST 5.f

class Camera
{
private:
	irr::IrrlichtDevice*			_device;

	float							_distance;
	float							_angle;
	float							_angleOffset;

	float							_curX;
	float							_curY;
	float							_curZ;

public:
	Camera(irr::IrrlichtDevice *device);
	void					updateCamera(Player *player);

	void					setDevice(irr::IrrlichtDevice *device);
	irr::IrrlichtDevice*	getDevice() const;

	void					addDistance(float);
	float					getDistance() const;
};

#endif
