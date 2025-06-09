#include "UserGuide.h"

UserGuide::UserGuide() {

}

UserGuide::~UserGuide() {

}

void UserGuide::start() {
    StartServer();
}

void UserGuide::exit() {
    if (pid > 0) {
        std::string cmd = "kill " + std::to_string(pid);
        std::system(cmd.c_str());
    }
}