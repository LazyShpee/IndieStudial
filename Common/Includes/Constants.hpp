#ifndef CONSTANTS_HPP_
# define CONSTANTS_HPP_

# define ERROR_CODE -1
# define OK_CODE 0

# define SHORT_BUFFER 32
# define LONG_BUFFER 1024

# define _USE_MATH_DEFINES
# include <math.h>
# include <cmath>

# ifdef _WIN32
#  define ASSETS_DIR "../../Assets"
#  define SLEEP(ms) Sleep(ms) 
# else
#  include <unistd.h>
#  define ASSETS_DIR "../Assets"
#  define SLEEP(ms) usleep(ms * 1000)
# endif

# define MISSILE_MESH_PATH	ASSETS_DIR"missils/missils.obj"	
# define MISSILE_SCALE		1.f
# define MAP_MESH_PATH		ASSETS_DIR"mp/arena2.obj"
# define CAR_1		ASSETS_DIR"car/car 1/car-1.obj"
# define CAR_2		ASSETS_DIR"car/car 2/car_2.obj"
# define CAR_3		ASSETS_DIR"car/car 3/car_3.obj"
# define CAR_4		ASSETS_DIR"car/car 4/car_4.obj"
# define CAR_5		ASSETS_DIR"car/car 5/car_5.obj"
# define CAR_6		ASSETS_DIR"car/car 6/car_6.obj"
# define CAR_7		ASSETS_DIR"car/car 7/f.obj"
# define ENEMY_MESH_PATH	ASSETS_DIR"truck/camion.obj"
# define SPAWNER_MESH_PATH	ASSETS_DIR"bear.obj"

# define NB_PLAYERS 2

#endif /* CONSTANTS_HPP_ */
