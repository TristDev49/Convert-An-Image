#ifndef CONVERTER_H
#define CONVERTER_H

#include <windows.h>
#include <string>
#include <vector>
#include <iostream>
#include "base64.h"
using namespace std;

// Forward declaration only
extern HWND mainWindow;

// Function to open Save File Dialog
string OpenSaveFileDialog(const string& defaultFileName, const string& fileExtension) {
    OPENFILENAMEA ofn;
    char szFile[260] = {0};
    strcpy_s(szFile, defaultFileName.c_str());
    
    string filter;
    if (fileExtension == "png") {
        filter = "PNG Files (*.png)\0*.png\0All Files (*.*)\0*.*\0";
    } 
    else if (fileExtension == "jpg") 
    {
        filter = "JPG Files (*.jpg)\0*.jpg\0All Files (*.*)\0*.*\0";
    } 
    else if (fileExtension == "jpeg") 
    {
        filter = "JPEG Files (*.jpeg)\0*.jpeg\0All Files (*.*)\0*.*\0";
    } 
    else {
        filter = "All Files (*.*)\0*.*\0";
    }
    
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = mainWindow;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filter.c_str();
    ofn.nFilterIndex = 1;
    ofn.lpstrTitle = "Save File Conversion Result";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
    
    if (GetSaveFileNameA(&ofn)) {
        string selectedPath = szFile;
        if (selectedPath.find('.') == string::npos) {
            selectedPath += "." + fileExtension;
        }
        return selectedPath;
    }
    return "";
}

// Image conversion function
void ConvertImage(const string& base64Data, const string& defaultOutputName, const string& format) {
    int width, height, channels;
    unsigned char* data = nullptr;
    
    cout << "[Info] Processing image data..." << endl;
    
    vector<unsigned char> imageData = base64_decode(base64Data);
    
    if (imageData.empty()) {
        cout << "[Failed] Cannot decode base64 data" << endl;
        MessageBoxA(mainWindow, "Cannot decode image data", "Error", MB_OK | MB_ICONERROR);
        return;
    }
    
    cout << "[Info] Data successfully decoded, size: " << imageData.size() << " bytes" << endl;
    
    data = stbi_load_from_memory(imageData.data(), imageData.size(), &width, &height, &channels, 0);

    if (!data) {
        cout << "[Failed] Cannot process image data" << endl;
        MessageBoxA(mainWindow, "Cannot process image data", "Error", MB_OK | MB_ICONERROR);
        return;
    }

    cout << "[Info] Image successfully loaded! Dimensions: " << width << "x" << height << ", Channels: " << channels << endl;

    string outputPath = OpenSaveFileDialog(defaultOutputName, format);
    
    if (outputPath.empty()) {
        cout << "[Info] Conversion cancelled by user" << endl;
        stbi_image_free(data);
        return;
    }

    cout << "[Info] Saving to: " << outputPath << endl;

    string ext = outputPath.substr(outputPath.find_last_of(".") + 1);
    for (auto& c : ext) c = tolower(c);

    bool success = false;
    
    if (ext == "jpg" || ext == "jpeg") {
        success = stbi_write_jpg(outputPath.c_str(), width, height, channels, data, 100);
    } else if (ext == "png") {
        success = stbi_write_png(outputPath.c_str(), width, height, channels, data, width * channels);
    } else {
        cout << "[Failed] Output format not supported: " << ext << endl;
        MessageBoxA(mainWindow, ("Format not supported: " + ext).c_str(), "Error", MB_OK | MB_ICONERROR);
        stbi_image_free(data);
        return;
    }

    stbi_image_free(data);
    
    if (success) {
        cout << "[Success] Conversion to " << ext << " completed!" << endl;
        cout << "[Success] File saved at: " << outputPath << endl;
        
        string successMessage = "Conversion successful!\n\nFile saved at:\n" + outputPath;
        MessageBoxA(mainWindow, successMessage.c_str(), "Success", MB_OK | MB_ICONINFORMATION);
    } else {
        cout << "[Failed] Cannot save file: " << outputPath << endl;
        MessageBoxA(mainWindow, ("Cannot save file: " + outputPath).c_str(), "Error", MB_OK | MB_ICONERROR);
    }
}

#endif // CONVERTER_H

