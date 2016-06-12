#ifndef CONFIGSELECTOR_HPP_
# define CONFIGSELECTOR_HPP_

# include <string>
# include <fstream>
# include "Vehicle.hpp"

namespace ConfigSelector
{
	struct Config
	{
		int vie;
		std::string car_name;
		irr::u32 car_model;
		std::string car_desc;
		struct Vehicle::Config* cfg;
	};

        Config getConfigFromIni(const std::string &);
}

#endif /* !CONFIGSELECTOR_HPP_ */
