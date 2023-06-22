#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

void writecodeEnumNamesANDFeatures(string inputFileName, string outputFileName);
void writecodeAllFormatsANDFeatures(string inputFileName, string outputFileName);

int main() {
	//writecodeEnumNamesANDFeatures("input.txt", "output.txt");
	writecodeAllFormatsANDFeatures("input.txt", "output.txt");

	return 0;
}