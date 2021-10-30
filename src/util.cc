#include <string>
#include <vector>
#include "fs.hh"
using std::string;
using std::vector;

vector <string> gamefilesExist(string gamepath) {
	vector <string> missing;
	vector <string> files = {
		"/icon.png",
		"/textures/1.png",
		"/textures/2.png",
		"/textures/3.png",
		"/textures/4.png",
		"/textures/5.png",
		"/textures/player.png"
	};
	for (size_t i = 0; i<files.size(); ++i) {
		if (!fexists(files[i]))
			missing.push_back(gamepath + files[i]);
	}
	return missing;
}