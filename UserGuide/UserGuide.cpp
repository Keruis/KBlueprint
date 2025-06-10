#include "UserGuide.h"

UserGuide::UserGuide() {

}

UserGuide::~UserGuide() {

}

void UserGuide::start() {
    StartServer();
}

void UserGuide::exit() {
    ShutdownServer();
}