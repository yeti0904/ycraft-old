#include <fstream>
#include <string>
using std::ifstream;
using std::string;

bool fexists(string fname) {
		ifstream fhnd(fname);

		return fhnd.good();
}