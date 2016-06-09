#ifndef CAR_HPP_
# define CAR_HPP_

# include <cmath>
# include "Vector.hpp"
# include "GMath.hpp"
# include "IncludeIrrlicht.hpp"

# define I_THROTTLE core::MOVE_FOWARD
# define I_BRAKE core::MOVE_BACK
# define I_EBRAKE core::MOVE_STAP
# define I_LEFT core::MOVE_LEFT
# define I_RIGHT core::MOVE_RIGHT
# define I_REVERSE core::MOVE_REVERSE

namespace Vehicle {
	struct Config
	{
		float	gravity;
		float	mass;
		float	inertiaScale;
		float	halfWidth;
		float	cgToFront;
		float	cgToRear;
		float	cgToFrontAxle;
		float	cgToRearAxle;
		float	cgHeight;
		float	wheelRadius;
		float	wheelWidth;
		float	tireGrip;
		float	lockGrip;
		float	engineForce;
		float	reverseForce;
		float	brakeForce;
		float	eBrakeForce;
		float	weightTransfer;
		float	maxSteer;
		float	cornerStiffnessFront;
		float	cornerStiffnessRear;
		float	airResist;
		float	rollResist;
	};

	Config *getDefaultConfig();

	class Car {
	private:
		Config			*cfg;
		int				inputs;

		float 			heading;
		Vector::Vec2 	position;
		Vector::Vec2	velocity;
		Vector::Vec2	velocity_c;
		Vector::Vec2	accel;
		Vector::Vec2	accel_c;
		float			absVel;
		float 			yawRate;
		float			steer;
		float 			steerAngle;

		float			inertia;
		float			wheelBase;
		float			axleWeightRatioFront;
		float			axleWeightRatioRear;

		void			doPhysics(float dt);
		float			applySmoothSteer(float steerInput, float dt);
		float			applySafeSteer(float steerInput);
	public:
		bool			smoothSteer;
		bool			safeSteer;

		Car(float x = 0.f, float y = 0.f, float heading = 0.f);
		~Car();
		void			update(float dtms);
		void			setConfig(Config *cfg);
		Config			*getConfig() const;
		void			setPosition(const Vector::Vec2 & pos);
		void			setHeading(float heading);
		Vector::Vec2	getPosition() const;
		float			getHeading() const;
		void			calmezVous(float angle, float force);
	};
}

#endif
