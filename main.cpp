#include <windows.h>
#include <wrl.h>
#include <wil/com.h>
#include <WebView2.h>
#include <iostream>
#include <string>

// image conversion library (header-only)
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#pragma warning(disable: 4244)

using namespace Microsoft::WRL;
using namespace std;

wil::com_ptr<ICoreWebView2Controller> webviewController;
wil::com_ptr<ICoreWebView2> webview;

// Set WebView2 bounds to only fill the client area of the window
static void SetWebViewBounds(HWND hWnd) {
    if (webviewController == nullptr) return;

    RECT bounds;
    GetClientRect(hWnd, &bounds);
    webviewController->put_Bounds(bounds);
}

// ====== Image conversion function ======
void convertImage(const string& input, const string& output) {
    int width, height, channels;
    unsigned char* data = stbi_load(input.c_str(), &width, &height, &channels, 0);

    if (!data) {
        cout << "[Failed] Cannot open file: " << input << endl;
        return;
    }

    string ext = output.substr(output.find_last_of(".") + 1);
    for (auto& c : ext) c = tolower(c); // convert to lowercase

    if (ext == "jpg" || ext == "jpeg") {
        stbi_write_jpg(output.c_str(), width, height, channels, data, 100);
    } else if (ext == "png") {
        stbi_write_png(output.c_str(), width, height, channels, data, width * channels);
    } else {
        cout << "[Failed] Output format not supported: " << ext << endl;
        stbi_image_free(data);
        return;
    }

    stbi_image_free(data);
    cout << "[Success] Conversion " << input << " → " << output << endl;
}

// ====== WebView initialization function ======
void InitializeWebView(HWND hWnd) {
    CreateCoreWebView2EnvironmentWithOptions(
        nullptr, nullptr, nullptr,
        Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
            [hWnd](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
                env->CreateCoreWebView2Controller(
                    hWnd,
                    Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
                        [hWnd](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
                            if (controller != nullptr)
                                webviewController = controller;

                            webviewController->get_CoreWebView2(&webview);

                            // Set WebView display size (avoid overlapping title-bar)
                            SetWebViewBounds(hWnd);

                            // Navigate to HTML file
                            webview->Navigate(L"file:///C:/path/to/your/index.html");

                            // Capture messages from JavaScript
                            EventRegistrationToken token;
                            webview->add_WebMessageReceived(
                                Callback<ICoreWebView2WebMessageReceivedEventHandler>(
                                    [](ICoreWebView2* sender, ICoreWebView2WebMessageReceivedEventArgs* args) -> HRESULT {
                                        wil::unique_cotaskmem_string message;
                                        args->TryGetWebMessageAsString(&message);
                                        wstring wmsg(message.get());
                                        string msg(wmsg.begin(), wmsg.end());

                                        // Message format from JS: input|output
                                        size_t pos = msg.find('|');
                                        if (pos != string::npos) {
                                            string input = msg.substr(0, pos);
                                            string output = msg.substr(pos + 1);
                                            convertImage(input, output);
                                        }
                                        return S_OK;
                                    })
                                    .Get(),
                                &token);

                            return S_OK;
                        })
                        .Get());
                return S_OK;
            })
            .Get());
}

// ====== Main Window Function ======
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_SIZE:
            SetWebViewBounds(hWnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// ====== Main function ======
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    const wchar_t * CLASS_NAME = L"ImageConverterApp";
    
    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClassW(&wc);

    HWND hWnd = CreateWindowExW(
        0, CLASS_NAME, L"Image Conversion Application (C++)",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 900, 600,
        nullptr, nullptr, hInstance, nullptr);

    if (hWnd == nullptr) return 0;

    ShowWindow(hWnd, nCmdShow);

    InitializeWebView(hWnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}