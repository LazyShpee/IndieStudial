#ifndef CONSTANTS_HPP_
# define CONSTANTS_HPP_

# define ERROR_CODE -1
# define OK_CODE 0

# ifdef _WIN32
#  define ASSETS_DIR "../../IndieGameAssets"
# else
#  define ASSETS_DIR "../IndieGameAssets"
# endif

# define MISSILE_MESH_PATH ASSETS_DIR"/bear.obj"
# define SPAWNER_MESH_PATH ASSETS_DIR"/bear.obj"

#endif /* CONSTANTS_HPP_ */
