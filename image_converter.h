#ifndef IMAGE_CONVERTER_H
#define IMAGE_CONVERTER_H

#include <string>
#include <vector>
using namespace std;

// Function to decode base64
vector<unsigned char> base64_decode(const string& encoded_string);

// Function to open Save File Dialog
string OpenSaveFileDialog(const string& defaultFileName, const string& fileExtension);

// Main image conversion function
void ConvertImage(const string& base64Data, const string& defaultOutputName, const string& format);

#endif // IMAGE_CONVERTER_H

