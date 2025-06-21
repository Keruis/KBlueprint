#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_

#include <cstring>
#include <unordered_set>

#ifdef _WIN32
#include <dinput.h>
#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#else
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XInput2.h>
#endif

class Input {
public:
    Input();
    ~Input();

    bool Initialize(void* windowHandle, int screenWidth, int screenHeight);
    void Shutdown();
    bool Frame();

    bool IsKeyDown(unsigned int key) noexcept;
    void KeyDown(unsigned int) noexcept ;
    void KeyUp(unsigned int) noexcept ;

    bool IsEscapePressed();
    bool IsLeftArrowPressed();
    bool IsRightArrowPressed();
    bool IsMousePressed();
    void GetMouseLocation(int& x, int& y);

private:
    bool ReadKeyboard();
    bool ReadMouse();
    void ProcessInput();

private:
    std::unordered_set<unsigned int> m_pressedKeys;
    int m_screenWidth, m_screenHeight;
    int m_mouseX, m_mouseY;

#ifdef _WIN32
    LPDIRECTINPUT8       m_directInput;
    LPDIRECTINPUTDEVICE8 m_keyboard;
    LPDIRECTINPUTDEVICE8 m_mouse;
    BYTE                 m_keyboardState[256];
    DIMOUSESTATE         m_mouseState;
#else
    Display* m_display;
    Window   m_window;
    char     m_keyboardState[32];
    int      m_mouseDeltaX, m_mouseDeltaY;
    bool     m_mouseButtons[3];
#endif
};

#endif