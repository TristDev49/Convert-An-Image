# C++ Image Conversion Desktop Application

A desktop application built with C++ and WebView2 that converts images between different formats (PNG, JPG, JPEG) using a modern web-based UI.

---

## 📋 Table of Contents

- [Microsoft WebView2 SDK](https://developer.microsoft.com/en-us/microsoft-edge/webview2/) - Official WebView2 documentation and downloads
- [STB Image Library](https://github.com/nothings/stb) - Single-file public domain image loading library
- [Visual Studio Build Tools](https://visualstudio.microsoft.com/downloads/) - C++ compiler and build tools
- [WebView2 Runtime](https://developer.microsoft.com/en-us/microsoft-edge/webview2/#download-section) - Required runtime for WebView2 applications
- [MSVC Compiler Documentation](https://docs.microsoft.com/en-us/cpp/) - Microsoft C++ documentation
- [STB Image Documentation](https://github.com/nothings/stb/blob/master/stb_image.h) - STB image header file and usage
- [Base64 Encoding Reference](https://en.cppreference.com/w/cpp) - C++ reference documentation
- [Windows API Documentation](https://docs.microsoft.com/en-us/windows/win32/) - Windows API reference
- [WebView2 Samples](https://github.com/MicrosoftEdge/WebView2Samples) - Official WebView2 sample projects
- [CMake Documentation](https://cmake.org/documentation/) - Build system documentation

---

## 🎯 Overview

This project demonstrates how to create a desktop application using C++ with a web-based user interface powered by Microsoft Edge WebView2. It's an excellent learning resource for developers who want to:

- Build cross-platform desktop apps with C++
- Integrate web technologies (HTML/CSS/JavaScript) with native C++ code
- Handle image processing using the STB library
- Communicate between JavaScript and C++ using WebView2
- Work with Windows API and file dialogs

---

## ✨ Features

- **Image Format Conversion**: Convert between PNG, JPG, and JPEG formats
- **Modern Web UI**: User-friendly interface built with HTML/CSS/JavaScript
- **Native File Dialogs**: Windows native Save File Dialog for selecting output location
- **Base64 Support**: Process images from base64-encoded strings
- **Real-time Feedback**: Console logging and message boxes for operation status
- **Firewall-friendly**: All processing happens locally, no internet required

---

## 🔧 Prerequisites

Before building this project, ensure you have:

1. **Visual Studio 2022** (Community Edition or higher)
   - C++ Desktop Development workload installed
   - Windows 10 SDK (version 10.0.26100.0 or compatible)

2. **vcpkg** (C++ Package Manager)
   - Install location: `C:\vcpkg`
   - WebView2 package installed

3. **Windows 10/11** Operating System

### Installing vcpkg and WebView2

```bash
# Clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg

# Bootstrap vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat

# Install WebView2
.\vcpkg install webview2:x64-windows

# Integrate with Visual Studio (optional)
.\vcpkg integrate install
```

---

## 📁 Project Structure

```
New folder/
├── main.cpp              # Main application entry point
├── converter.h           # Image conversion logic and file dialogs
├── base64.h              # Base64 decoding utilities
├── image_converter.h     # Function declarations/interface
├── stb_image.h           # STB library for image loading
├── stb_image_write.h     # STB library for image writing
├── compile.bat           # Build script for compilation
└── README.md             # This file
```

---

## 📄 File Descriptions

### `main.cpp`
**Purpose**: Application entry point and WebView2 initialization.

**Key Components**:
- `wWinMain()`: Windows application entry point
- `WindowProc()`: Handles window messages (resize, close, etc.)
- `InisialisasiWebView()`: Initializes Microsoft Edge WebView2 control
- `SetWebViewBounds()`: Manages WebView2 sizing within the window
- `konversiGambar()`: Basic image conversion function (legacy)

**What you'll learn**:
- Creating Windows desktop applications
- Working with Windows API (HWND, messages, window classes)
- Initializing and managing WebView2 control
- Communicating between JavaScript and C++ using `WebMessageReceived`

---

### `converter.h`
**Purpose**: Core image conversion functionality with native file dialogs.

**Key Functions**:
- `OpenSaveFileDialog()`: Opens Windows native Save File Dialog
- `konversiGambar()`: Main conversion function that:
  - Decodes base64 image data
  - Loads image using STB library
  - Opens save dialog for user to choose output location
  - Writes image in the selected format

**What you'll learn**:
- Using Windows Common Dialogs (OPENFILENAMEA structure)
- Processing binary image data
- Working with STB image library
- Error handling and user feedback

---

### `base64.h`
**Purpose**: Base64 encoding/decoding utilities.

**Key Functions**:
- `base64_decode()`: Converts base64 string to binary data

**What you'll learn**:
- Base64 decoding algorithm
- Working with binary data in C++
- String manipulation and character arrays

---

### `image_converter.h`
**Purpose**: Header file with function declarations.

**What you'll learn**:
- Creating header files for code organization
- Forward declarations
- Separating interface from implementation

---

### `stb_image.h` & `stb_image_write.h`
**Purpose**: Header-only libraries for image loading and writing.

**Key Features**:
- `stb_image.h`: Load JPG, PNG, BMP, GIF, and other formats
- `stb_image_write.h`: Write PNG, JPG, BMP, TGA files

**What you'll learn**:
- Using header-only libraries in C++
- Image processing basics (width, height, channels)
- Memory management with image data

---

### `compile.bat`
**Purpose**: Automated build script for compiling the application.

**What it does**:
1. Sets up paths to vcpkg and Visual Studio compiler
2. Compiles `main.cpp` with all necessary flags
3. Links required libraries (WebView2, Windows API)
4. Copies WebView2Loader.dll to output directory

**What you'll learn**:
- Command-line compilation with MSVC
- Linking external libraries
- Compiler flags and options (`/EHsc`, `/W4`, `/std:c++17`, etc.)

---

## 🔨 How to Build

### Method 1: Using the Batch Script (Recommended)

1. Open the project folder in File Explorer
2. Double-click `compile.bat`
3. Wait for compilation to complete
4. If successful, you'll see `app.exe` in the same folder

### Method 2: Manual Compilation

Open **Developer Command Prompt for VS 2022** and run:

```bash
cd "C:\C++ PROJECT"

"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe" ^
/EHsc /W4 /Zi /std:c++17 /DUNICODE /D_UNICODE /MD main.cpp ^
/I"C:\vcpkg\installed\x64-windows\include" ^
/link "C:\vcpkg\installed\x64-windows\lib\WebView2Loader.dll.lib" ^
/LIBPATH:"C:\vcpkg\installed\x64-windows\lib" ^
user32.lib gdi32.lib ole32.lib oleaut32.lib kernel32.lib Comdlg32.lib ^
/Fe:app.exe
```

---

## 🚀 How to Run

### Prerequisites Before Running
1. Ensure you have **Microsoft Edge** installed (comes with Windows 10/11)
2. Update the HTML file path in `main.cpp` line 67:
   ```cpp
   webview->Navigate(L"file:///C:/path/to/your/index.html");
   ```

### Running the Application

1. **Double-click** `app.exe` or run from command line:
   ```bash
   .\app.exe
   ```

2. The application window will open with your web interface

3. **Console Output**: A console window will show real-time logs:
   ```
   [Info] Processing image data...
   [Info] Data successfully decoded, size: 45678 bytes
   [Info] Image successfully loaded! Dimensions: 800x600, Channels: 3
   [Info] Saving to: C:\Users\...\output.png
   [Success] Conversion to png completed!
   ```

---

## 🔄 How It Works

### Architecture Flow

```
┌─────────────────┐
│  WebView2 Host  │
│   (C++ Side)    │
└────────┬────────┘
         │ WebMessageReceived
         ▼
┌─────────────────┐
│ ConvertImage()│
│  (converter.h)  │
└────────┬────────┘
         │
         ├─► base64_decode()
         ├─► stbi_load_from_memory()
         ├─► OpenSaveFileDialog()
         └─► stbi_write_png/jpg()
```

### Step-by-Step Process

1. **User Action**: User selects an image in the web UI
2. **JavaScript**: Converts image to base64 and sends to C++ via:
   ```javascript
   window.chrome.webview.postMessage(base64Data);
   ```
3. **C++ Receives**: `WebMessageReceived` event handler captures the message
4. **Decode**: `base64_decode()` converts string to binary data
5. **Load Image**: `stbi_load_from_memory()` creates image object
6. **User Selects Output**: `OpenSaveFileDialog()` shows native dialog
7. **Convert & Save**: `stbi_write_*()` saves in chosen format
8. **Feedback**: Success/error messages via MessageBox and console

---

## 📚 Learning Resources

### Key Concepts Demonstrated

1. **Win32 API Programming**
   - Window creation and management
   - Message loops and event handling
   - Common dialogs (Save File Dialog)

2. **WebView2 Integration**
   - Embedding web content in native apps
   - JavaScript ↔ C++ communication
   - Event handling and callbacks

3. **Image Processing**
   - Binary data manipulation
   - Image format conversion
   - Memory management with image buffers

4. **Modern C++ Features**
   - Smart pointers (`wil::com_ptr`)
   - Lambda functions
   - Standard library containers

### Recommended Next Steps

- Add support for more formats (BMP, WEBP, TIFF)
- Implement drag-and-drop functionality
- Add image preview before conversion
- Create batch conversion feature
- Add image resize/crop options
- Package as installer with NSIS or WiX

---

## 🐛 Troubleshooting

### Compilation Errors

**Error**: `Cannot open include file: 'WebView2.h'`
- **Solution**: Install WebView2 via vcpkg: `vcpkg install webview2:x64-windows`

**Error**: `LNK2019: unresolved external symbol`
- **Solution**: Ensure all required `.lib` files are linked in `compile.bat`

### Runtime Errors

**Error**: Application crashes on startup
- **Solution**: Ensure `WebView2Loader.dll` is in the same folder as `app.exe`

**Error**: WebView shows blank white screen
- **Solution**: Check the HTML file path in `main.cpp` is correct and accessible

**Error**: "Cannot decode image data"
- **Solution**: Verify the base64 string is valid and properly formatted

### Performance Issues

**Issue**: Large images take too long
- **Solution**: Add progress indicators or async processing

---

## 📝 License

This project is provided for educational purposes. Feel free to modify and use for learning.

---

## 🤝 Contributing

This is a learning project. Feel free to:
- Report issues
- Suggest improvements
- Share your modifications
- Create tutorials based on this code

---

## 📧 Contact

For questions or discussions about this educational project, please open an issue in the repository.

---

**Happy Learning! 🎓**
