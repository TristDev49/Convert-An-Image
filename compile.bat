@echo off
echo Compiling image conversion application...

REM Make sure the path to vcpkg is correct
set VCPKG_PATH=C:\vcpkg

REM Compile with WebView2
REM Use 64-bit compiler with correct runtime library
REM "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe" /EHsc /W4 /Zi /std:c++17 /MD /Fe:app.exe test.cpp /I"%VCPKG_PATH%\installed\x64-windows\include" /link "%VCPKG_PATH%\installed\x64-windows\lib\WebView2Loader.dll.lib" /LIBPATH:"%VCPKG_PATH%\installed\x64-windows\lib" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\um\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\ucrt\x64" /LIBPATH:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\lib\x64" user32.lib gdi32.lib ole32.lib oleaut32.lib kernel32.lib
REM "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe" /EHsc /W4 /Zi /std:c++17 /DUNICODE /D_UNICODE /MD main.cpp /I"C:\vcpkg\installed\x64-windows\include" /link "C:\vcpkg\installed\x64-windows\lib\WebView2Loader.dll.lib" /LIBPATH:"C:\vcpkg\installed\x64-windows\lib" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\um\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\ucrt\x64" /LIBPATH:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\lib\x64" user32.lib gdi32.lib ole32.lib oleaut32.lib kernel32.lib /Fe:app.exe
"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\bin\Hostx64\x64\cl.exe" /EHsc /W4 /Zi /std:c++17 /DUNICODE /D_UNICODE /MD main.cpp /I"C:\vcpkg\installed\x64-windows\include" /link "C:\vcpkg\installed\x64-windows\lib\WebView2Loader.dll.lib" /LIBPATH:"C:\vcpkg\installed\x64-windows\lib" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\um\x64" /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\ucrt\x64" /LIBPATH:"C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.44.35207\lib\x64" user32.lib gdi32.lib ole32.lib oleaut32.lib kernel32.lib Comdlg32.lib /Fe:app.exe

if %ERRORLEVEL% EQU 0 (
    echo Compilation successful! Copying WebView2Loader.dll...
    copy "%VCPKG_PATH%\installed\x64-windows\bin\WebView2Loader.dll" .
    echo Done. Run the .exe file to start the application.
) else (
    echo Compilation failed! Please check the error messages above.
)

pause
