#ifndef BLUEPRINT_X11_H
#define BLUEPRINT_X11_H
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <functional>
#include <thread>
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <map>

#ifndef XINITTHREADS_CALLED
#define XINITTHREADS_CALLED \
static bool XlibThreadsInitialized = XInitThreads();
#endif

#define CHECK_X_ERROR(call) \
    if ((call) == 0) { \
        throw std::runtime_error("X11 error: " #call " failed."); \
    }

class X11Window {
public:
    using ExposeCallback = std::function<void(const XExposeEvent&)>;
    using KeyCallback = std::function<void(const XKeyEvent&)>;
    using MouseButtonCallback = std::function<void(const XButtonEvent&)>;
    using MouseMotionCallback = std::function<void(const XMotionEvent&)>;
    using ConfigureCallback = std::function<void(const XConfigureEvent&)>;
    using ClientMessageCallback = std::function<void(const XClientMessageEvent&)>;
    using GenericEventCallback = std::function<void(const XEvent&)>;

    X11Window(int width, int height, const std::string& title);
    virtual ~X11Window();

    X11Window(const X11Window&) = delete;
    X11Window& operator=(const X11Window&) = delete;

    void show();
    void hide();
    void setTitle(const std::string& title);
    Window getWindowHandle() const;
    Display* getDisplay() const;
    GC getGraphicsContext() const;
    int getScreen() const;
    int getWidth() const;
    int getHeight() const;
    void getWindowSize(int& width, int& height) const;
    void startEventThread();
    void stopEventThread();
    bool hasQuitRequested() const;

    void addExposeCallback(ExposeCallback callback) {
        exposeCallbacks_.push_back(std::move(callback));
    }

    // 注册 KeyPress 事件回调
    void addKeyPressCallback(KeyCallback callback) {
        keyPressCallbacks_.push_back(std::move(callback));
    }

    // 注册 KeyRelease 事件回调
    void addKeyReleaseCallback(KeyCallback callback) {
        keyReleaseCallbacks_.push_back(std::move(callback));
    }

    // 注册 ButtonPress 事件回调
    void addButtonPressCallback(MouseButtonCallback callback) {
        buttonPressCallbacks_.push_back(std::move(callback));
    }

    // 注册 ButtonRelease 事件回调
    void addButtonReleaseCallback(MouseButtonCallback callback) {
        buttonReleaseCallbacks_.push_back(std::move(callback));
    }

    // 注册 MotionNotify (鼠标移动) 事件回调
    void addMouseMotionCallback(MouseMotionCallback callback) {
        mouseMotionCallbacks_.push_back(std::move(callback));
    }

    // 注册 ConfigureNotify (窗口大小/位置改变) 事件回调
    void addConfigureCallback(ConfigureCallback callback) {
        configureCallbacks_.push_back(std::move(callback));
    }

    // 注册 ClientMessage (自定义客户端消息，如窗口关闭) 事件回调
    void addClientMessageCallback(ClientMessageCallback callback) {
        clientMessageCallbacks_.push_back(std::move(callback));
    }

    // 注册通用事件回调 (会收到所有事件)
    void addGenericEventCallback(GenericEventCallback callback) {
        genericEventCallbacks_.push_back(std::move(callback));
    }

    // --- 绘制功能 (非Vulkan，用于调试) ---
    void drawRectangle(int x, int y, int width, int height, unsigned long color) {
        if (!gc_) return;
        // XLockDisplay(display_); // 如果在多线程中频繁使用Xlib绘制，可能需要加锁
        XSetForeground(display_, gc_, color);
        XFillRectangle(display_, window_, gc_, x, y, width, height);
        XFlush(display_);
        // XUnlockDisplay(display_);
    }

    void drawText(int x, int y, const std::string& text, unsigned long color) {
        if (!gc_) return;
        // XLockDisplay(display_);
        XSetForeground(display_, gc_, color);
        XDrawString(display_, window_, gc_, x, y, text.c_str(), text.length());
        XFlush(display_);
        // XUnlockDisplay(display_);
    }

private:
    Display* display_;
    int screen_;
    Window window_;
    GC gc_;
    int width_;
    int height_;
    std::string title_;

    std::thread eventThread_;
    std::atomic_bool eventThreadRunning_;
    std::atomic_bool quitRequested_;

    std::vector<ExposeCallback> exposeCallbacks_;
    std::vector<KeyCallback> keyPressCallbacks_;
    std::vector<KeyCallback> keyReleaseCallbacks_;
    std::vector<MouseButtonCallback> buttonPressCallbacks_;
    std::vector<MouseButtonCallback> buttonReleaseCallbacks_;
    std::vector<MouseMotionCallback> mouseMotionCallbacks_;
    std::vector<ConfigureCallback> configureCallbacks_;
    std::vector<ClientMessageCallback> clientMessageCallbacks_;
    std::vector<GenericEventCallback> genericEventCallbacks_;
    
    void init() {
        display_ = XOpenDisplay(nullptr);
        if (!display_) {
            throw std::runtime_error("Cannot open display.");
        }
        std::cout << "Connected to X server." << std::endl;

        screen_ = DefaultScreen(display_);

        XSetWindowAttributes attributes;
        attributes.background_pixel = XBlackPixel(display_, screen_);
        attributes.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
                                ButtonPressMask | ButtonReleaseMask | PointerMotionMask |
                                StructureNotifyMask ;
        attributes.override_redirect = False;

        window_ = XCreateWindow(display_, RootWindow(display_, screen_),
                                0, 0, width_, height_, 0,
                                DefaultDepth(display_, screen_), InputOutput,
                                DefaultVisual(display_, screen_),
                                CWBackPixel | CWEventMask | CWOverrideRedirect, &attributes);
        CHECK_X_ERROR(window_);
        std::cout << "Window created with ID: " << window_ << std::endl;

        XStoreName(display_, window_, title_.c_str());

        Atom wmDelete = XInternAtom(display_, "WM_DELETE_WINDOW", False);
        XSetWMProtocols(display_, window_, &wmDelete, 1);

        gc_ = XCreateGC(display_, window_, 0, nullptr);
        CHECK_X_ERROR(gc_);
        std::cout << "Graphics Context created." << std::endl;
        XSetForeground(display_, gc_, XWhitePixel(display_, screen_));
    }

    void cleanup() {
        if (gc_) {
            XFreeGC(display_, gc_);
            std::cout << "Graphics Context freed." << std::endl;
        }
        if (window_) {
            XDestroyWindow(display_, window_);
            std::cout << "Window destroyed." << std::endl;
        }
        if (display_) {
            XCloseDisplay(display_);
            std::cout << "Disconnected from X server." << std::endl;
        }
    }

    void eventLoopThread() {
        XEvent event;
        while (eventThreadRunning_) {
            XNextEvent(display_, &event);

            distributeEvent(event);
        }
    }

    void distributeEvent(const XEvent& event) {
        for (const auto& callback : genericEventCallbacks_) {
            if (callback) {
                callback(event);
            }
        }

        switch (event.type) {
            case Expose:
                for (const auto& callback : exposeCallbacks_) {
                    if (callback) {
                        callback(event.xexpose);
                    }
                }
                break;
            case KeyPress:
                for (const auto& callback : keyPressCallbacks_) {
                    if (callback) {
                        callback(event.xkey);
                    }
                }
                break;
            case KeyRelease:
                for (const auto& callback : keyReleaseCallbacks_) {
                    if (callback) {
                        callback(event.xkey);
                    }
                }
                break;
            case ButtonPress:
                for (const auto& callback : buttonPressCallbacks_) {
                    if (callback) {
                        callback(event.xbutton);
                    }
                }
                break;
            case ButtonRelease:
                for (const auto& callback : buttonReleaseCallbacks_) {
                    if (callback) {
                        callback(event.xbutton);
                    }
                }
                break;
            case MotionNotify:
                for (const auto& callback : mouseMotionCallbacks_) {
                    if (callback) {
                        callback(event.xmotion);
                    }
                }
                break;
            case ConfigureNotify:
                width_ = event.xconfigure.width;
                height_ = event.xconfigure.height;
                for (const auto& callback : configureCallbacks_) {
                    if (callback) {
                        callback(event.xconfigure);
                    }
                }
                break;
            case ClientMessage:
                if (event.xclient.data.l[0] == XInternAtom(display_, "WM_DELETE_WINDOW", False)) {
                    quitRequested_.store(true); // 设置退出标志
                }
                for (const auto& callback : clientMessageCallbacks_) {
                    if (callback) {
                        callback(event.xclient);
                    }
                }
                break;
            default:
                break;
        }
    }
};



#endif //BLUEPRINT_X11_H
