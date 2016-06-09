#include "Vehicle.hpp"
#include <cstdio>

Vehicle::Car::Car(float x, float y, float heading) {
	this->position = Vector::Vec2(x, y);
	this->heading = heading;
	this->absVel = 0.f;
	this->yawRate = 0.f;
	this->steer = 0.f;
	this->steerAngle = 0.f;

	this->smoothSteer = true;
	this->safeSteer = true;

	this->inertia = 0.f;
	this->wheelBase = 0.f;
	this->axleWeightRatioFront = 0.f;
	this->axleWeightRatioRear = 0.f;

	this->cfg = NULL;
}

Vehicle::Car::~Car() {}

void Vehicle::Car::doPhysics(float dt) {
	float sn = sin(this->heading);
	float cs = cos(this->heading);

		// Get velocity in local car coordinates
	this->velocity_c.x = cs * this->velocity.x + sn * this->velocity.y;
	this->velocity_c.y = cs * this->velocity.y - sn * this->velocity.x;

	// Weight on axles based on centre of gravity and weight shift due to forward/reverse acceleration
	float axleWeightFront = cfg->mass * (this->axleWeightRatioFront * cfg->gravity - cfg->weightTransfer * this->accel_c.x * cfg->cgHeight / this->wheelBase);
	float axleWeightRear = cfg->mass * (this->axleWeightRatioRear * cfg->gravity + cfg->weightTransfer * this->accel_c.x * cfg->cgHeight / this->wheelBase);

	// Resulting velocity of the wheels as result of the yaw rate of the car body.
	// v = yawrate * r where r is distance from axle to CG and yawRate (angular velocity) in rad/s.
	float yawSpeedFront = cfg->cgToFrontAxle * this->yawRate;
	float yawSpeedRear = -cfg->cgToRearAxle * this->yawRate;

	// Calculate slip angles for front and rear wheels (a.k.a. alpha)
	float slipAngleFront = atan2(this->velocity_c.y + yawSpeedFront, std::abs(this->velocity_c.x)) - GMath::sign(this->velocity_c.x) * this->steerAngle;
	float slipAngleRear  = atan2(this->velocity_c.y + yawSpeedRear,  std::abs(this->velocity_c.x));

	float tireGripFront = cfg->tireGrip;
	float tireGripRear = cfg->tireGrip * (1.0 - !!(this->_inputs & I_EBRAKE) * (1.0 - cfg->lockGrip)); // reduce rear grip when ebrake is on

	float frictionForceFront_cy = GMath::clamp(-cfg->cornerStiffnessFront * slipAngleFront, -tireGripFront, tireGripFront) * axleWeightFront;
	float frictionForceRear_cy = GMath::clamp(-cfg->cornerStiffnessRear * slipAngleRear, -tireGripRear, tireGripRear) * axleWeightRear;

	//  Get amount of brake/throttle from our inputs
	float brake = GMath::min(!!(this->_inputs & I_BRAKE) * cfg->brakeForce + !!(this->_inputs & I_EBRAKE) * cfg->eBrakeForce, cfg->brakeForce);
	float throttle = !!(this->_inputs & I_THROTTLE) * (cfg->engineForce) - (cfg->engineForce / cfg->reverseForce) * !!(this->_inputs & I_REVERSE);

	//  Resulting force in local car coordinates.
	//  This is implemented as a RWD car only.
	float tractionForce_cx = throttle - brake * GMath::sign(this->velocity_c.x);
	float tractionForce_cy = 0;

	float dragForce_cx = -cfg->rollResist * this->velocity_c.x - cfg->airResist * this->velocity_c.x * std::abs(this->velocity_c.x);
	float dragForce_cy = -cfg->rollResist * this->velocity_c.y - cfg->airResist * this->velocity_c.y * std::abs(this->velocity_c.y);

	// total force in car coordinates
	float totalForce_cx = dragForce_cx + tractionForce_cx;
	float totalForce_cy = dragForce_cy + tractionForce_cy + cos(this->steerAngle) * frictionForceFront_cy + frictionForceRear_cy;

	// acceleration along car axes
	this->accel_c.x = totalForce_cx / cfg->mass;  // forward/reverse accel
	this->accel_c.y = totalForce_cy / cfg->mass;  // sideways accel

	// acceleration in world coordinates
	this->accel.x = cs * this->accel_c.x - sn * this->accel_c.y;
	this->accel.y = sn * this->accel_c.x + cs * this->accel_c.y;

	// update velocity
	this->velocity.x += this->accel.x * dt;
	this->velocity.y += this->accel.y * dt;

	this->absVel = this->velocity.len();

	// calculate rotational forces
	float angularTorque = (frictionForceFront_cy + tractionForce_cy) * cfg->cgToFrontAxle - frictionForceRear_cy * cfg->cgToRearAxle;

	//  Sim gets unstable at very slow speeds, so just stop the car
	if( std::abs(this->absVel) < 0.5 && !throttle )
	{
		this->velocity.x = this->velocity.y = this->absVel = 0;
		angularTorque = this->yawRate = 0;
	}

	float angularAccel = angularTorque / this->inertia;

	this->yawRate += angularAccel * dt;
	this->heading += this->yawRate * dt;

	//  finally we can update position
	this->position.x += this->velocity.x * dt;
	this->position.y += this->velocity.y * dt;
}

void Vehicle::Car::update(float dtms) {
	float dt = dtms;

	int steerInput = !!(this->_inputs & I_LEFT) - !!(this->_inputs & I_RIGHT);

	if (this->smoothSteer)
		this->steer = this->applySmoothSteer(steerInput, dt);
	else
		this->steer = steerInput;

	if (this->safeSteer)
		this->steer = this->applySafeSteer(this->steer);

	this->steerAngle = this->steer * this->cfg->maxSteer;
	this->doPhysics(dt);
}

float Vehicle::Car::applySmoothSteer(float steerInput, float dt) {
	float steer = 0.f;

	if (std::abs(steerInput) > 0.001)
		steer = GMath::clamp(this->steer + steerInput * dt * 2.0, -1.0, 1.0);
	else
	{
		if (this->steer > 0.f)
			steer = GMath::max(this->steer - dt * 1.f, 0.f);
		else if (this->steer < 0.f)
			steer = GMath::min(this->steer + dt * 1.f, 0.f);
	}
	return (steer);
}

float Vehicle::Car::applySafeSteer(float steerInput) {
	float avel = GMath::min(this->absVel, 250.f);
	float steer = steerInput * (1.0 - (avel / 280.f));
	return (steer);
}

Vehicle::Config *Vehicle::Car::getConfig() const {
	return (this->cfg);
}

void Vehicle::Car::setConfig(Vehicle::Config *cfg) {
	this->cfg = cfg;
	this->inertia = this->cfg->mass * this->cfg->inertiaScale;
	this->wheelBase = this->cfg->cgToFrontAxle + this->cfg->cgToRearAxle;
	this->axleWeightRatioFront = this->cfg->cgToRearAxle / this->wheelBase; // % car weight on the front axle
	this->axleWeightRatioRear = this->cfg->cgToFrontAxle / this->wheelBase; // % car weight on the rear axle
}

Vehicle::Config *Vehicle::getDefaultConfig() {
	Config *cfg = new Vehicle::Config;

	cfg->gravity = 9.81;  // m/s^2
	cfg->mass = 1200.f;  // kg
	cfg->inertiaScale = 1.0;  // Multiply by mass for inertia
	cfg->halfWidth = 0.8; // Centre to side of chassis (metres)
	cfg->cgToFront = 2.0; // Centre of gravity to front of chassis (metres)
	cfg->cgToRear = 2.0;   // Centre of gravity to rear of chassis
	cfg->cgToFrontAxle = 1.25;  // Centre gravity to front axle
	cfg->cgToRearAxle = 1.25;  // Centre gravity to rear axle
	cfg->cgHeight = 0.55;  // Centre gravity height
	cfg->wheelRadius = 0.3;  // Includes tire (also represents height of axle)
	cfg->wheelWidth = 0.2;  // Used for render only
	cfg->tireGrip = 2.0;  // How much grip tires have
	cfg->lockGrip = 0.7;  // % of grip available when wheel is locked
	cfg->engineForce = 8000.f;
	cfg->reverseForce = 3.f;
	cfg->brakeForce = 12000.f;
	cfg->eBrakeForce = cfg->brakeForce / 2.5;
	cfg->weightTransfer = 0.2;  // How much weight is transferred during acceleration/braking
	cfg->maxSteer = 0.6;  // Maximum steering angle in radians
	cfg->cornerStiffnessFront = 5.0;
	cfg->cornerStiffnessRear = 5.2;
	cfg->airResist = 2.5;	// air resistance (* vel)
	cfg->rollResist = 8.0;
	return (cfg);
}

void			Vehicle::Car::setPosition(const Vector::Vec2 & pos)
{
	this->position = pos;
}

void			Vehicle::Car::setHeading(float heading)
{
	this->heading = heading;
}

Vector::Vec2	Vehicle::Car::getPosition() const
{
	return (this->position);
}

float			Vehicle::Car::getHeading() const
{
	return (this->heading);
}

void			Vehicle::Car::calmezVous(float, float force)
{
	this->velocity.x /= -force;
	this->velocity.y /= -force;
}
