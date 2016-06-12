#include "ConfigSelector.hpp"

struct ConfigSelector::Config ConfigSelector::getConfigFromIni(const std::string &file)
{
	struct ConfigSelector::Config conf;
	std::ifstream ifs;
	std::string line;
	conf.cfg = Vehicle::getDefaultConfig();
	float *cfgF = (float *)conf.cfg;
	int i = 0;

	conf.vie = 100;
	conf.car_name = std::string("name");
	conf.car_model = 0;
	conf.car_desc = std::string("desc");
	ifs.open(file.c_str());
	if (!std::getline(ifs, line))
		return (conf);
	try {
		conf.vie = std::stoi(line);
	}
	catch (std::exception e) {}
	if (!std::getline(ifs, line))
		return (conf);
	try {
		conf.car_name = line;
	}
	catch (std::exception e) {}
	if (!std::getline(ifs, line))
		return (conf);
	try {
		conf.car_model = (irr::u32)std::stoi(line);
	}
	catch (std::exception e) {}
	if (!std::getline(ifs, line))
		return (conf);
	try {
		conf.car_desc = line;
	}
	catch (std::exception e) {}
	while (std::getline(ifs, line) && i < 23)
	{
		try {
			cfgF[i] = std::stof(line);
		}
		catch (std::exception e) {}
		i++;
	}
	ifs.close();
	return (conf);
}