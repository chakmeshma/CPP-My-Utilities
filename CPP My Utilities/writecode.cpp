#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

static vector<string> parseEnumGetNames(string inputFileName) {
	vector<string> names;
	ifstream inputF(inputFileName.c_str());
	string line;

	if (!inputF.is_open())
		return names;

	while (getline(inputF, line)) {
		if (!line.size())
			continue;

		int posSpace = line.find(' ');
		int posComma = line.find(',');

		int lnName = -1;

		if (posComma == string::npos && posSpace == string::npos)
			lnName = line.size();
		else if (posComma == string::npos)
			lnName = posSpace;
		else if (posSpace == string::npos)
			lnName = posComma;
		else
			lnName = std::min(posComma, posSpace);

		names.push_back(line.substr(0, lnName));
	}

	inputF.close();

	return names;
}

void writecodeEnumNamesANDFeatures(string inputFileName, string outputFileName) {
	vector<string> names = parseEnumGetNames(inputFileName);

	ofstream outputF(outputFileName.c_str());

	if (!outputF.is_open())
		return;

	for (int i = 0; i < names.size(); i++) {
		string name = names[i];

		outputF << "if (featureFlags & VkFormatFeatureFlagBits::" << name << ")" << endl;
		outputF << "\tfeatureNames.push_back(std::string(\"" << name << "\"));" << endl;
	}

	outputF.close();

}

void writecodeAllFormatsANDFeatures(string inputFileName, string outputFileName) {
	vector<string> names = parseEnumGetNames(inputFileName);

	ofstream outputF(outputFileName.c_str());

	if (!outputF.is_open())
		return;

	outputF << "std::cout << \"Supported formats in buffers:\" << std::endl;";
	for (int i = 0; i < names.size(); i++) {
		string name = names[i];

		outputF << "vkGetPhysicalDeviceFormatProperties(physicalDevice, VkFormat::" << name << ", &formatProperties);" << endl;
		outputF << "if (formatProperties.bufferFeatures & features)" << endl;
		outputF << "\tstd::cout << \"\\t" << name << "\" << std::endl;" << endl;
	}

	outputF << "std::cout << std::endl;";

	outputF << "std::cout << \"Supported formats in linear-tiled images:\" << std::endl;";
	for (int i = 0; i < names.size(); i++) {
		string name = names[i];

		outputF << "vkGetPhysicalDeviceFormatProperties(physicalDevice, VkFormat::" << name << ", &formatProperties);" << endl;
		outputF << "if (formatProperties.linearTilingFeatures & features)" << endl;
		outputF << "\tstd::cout << \"\\t" << name << "\" << std::endl;" << endl;
	}

	outputF << "std::cout << std::endl;";

	outputF << "std::cout << \"Supported formats in optimal-tiled images:\" << std::endl;";
	for (int i = 0; i < names.size(); i++) {
		string name = names[i];

		outputF << "vkGetPhysicalDeviceFormatProperties(physicalDevice, VkFormat::" << name << ", &formatProperties);" << endl;
		outputF << "if (formatProperties.optimalTilingFeatures & features)" << endl;
		outputF << "\tstd::cout << \"\\t" << name << "\" << std::endl;" << endl;
	}

	outputF << "std::cout << std::endl;";


	outputF.close();
}