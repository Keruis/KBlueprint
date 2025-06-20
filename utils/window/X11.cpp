#include "X11.h"

X11Window::X11Window(int width, int height, const std::string& title)
    : display_(nullptr),
      screen_(0),
      window_(0),
      gc_(nullptr),
      width_(width),
      height_(height),
      title_(title),
      eventThreadRunning_(false),
      quitRequested_(false)
{
    init();
}

X11Window::~X11Window() {
    stopEventThread();
    cleanup();
}

void X11Window::show() {
    XMapWindow(display_, window_);
    XFlush(display_);
}

void X11Window::hide() {
    XUnmapWindow(display_, window_);
    XFlush(display_);
}

void X11Window::setTitle(const std::string& title) {
    title_ = title;
    XStoreName(display_, window_, title_.c_str());
    XFlush(display_);
}

Window X11Window::getWindowHandle() const {
    return window_;
}

Display* X11Window::getDisplay() const {
    return display_;
}

GC X11Window::getGraphicsContext() const {
    return gc_;
}

int X11Window::getScreen() const {
    return screen_;
}

int X11Window::getWidth() const {
    return width_;
}

int X11Window::getHeight() const {
    return height_;
}

void X11Window::getWindowSize(int& width, int& height) const {
    width = width_;
    height = height_;
}

void X11Window::startEventThread() {
    if (!eventThreadRunning_) {
        eventThreadRunning_ = true;
        eventThread_ = std::thread(&X11Window::eventLoopThread, this);
        std::cout << "X11 event thread started." << std::endl;
    }
}

void X11Window::stopEventThread() {
    if (eventThreadRunning_) {
        eventThreadRunning_ = false;
        if (eventThread_.joinable()) {
            eventThread_.join();
        }
        std::cout << "X11 event thread stopped." << std::endl;
    }
}

bool X11Window::hasQuitRequested() const {
    return quitRequested_.load();
}