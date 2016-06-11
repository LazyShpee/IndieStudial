#ifndef CONSTANTS_HPP_
# define CONSTANTS_HPP_

# define ERROR_CODE -1
# define OK_CODE 0

# define _USE_MATH_DEFINES
# include <math.h>
# include <cmath>

# ifdef _WIN32
//#  include <windows.h>
#  define ASSETS_DIR "../../IndieGameAssets"
#  define SLEEP(ms) Sleep(ms) 
# else
#  include <unistd.h>
#  define ASSETS_DIR "../IndieGameAssets"
#  define SLEEP(ms) usleep(ms * 1000)
# endif

# define MISSILE_MESH_PATH ASSETS_DIR"/bear.obj"
# define SPAWNER_MESH_PATH ASSETS_DIR"/bear.obj"

# define NB_PLAYERS 2

#endif /* CONSTANTS_HPP_ */
