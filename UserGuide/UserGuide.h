#ifndef BLUEPRINT_USERGUIDE_H
#define BLUEPRINT_USERGUIDE_H

extern "C" void StartServer();

#include <cstdio>
#include <cstdlib>
#include <string>

class UserGuide {
private:
    int pid = -1;
public:
    UserGuide();
    ~UserGuide();

    void start();
    void exit();
};

#endif //BLUEPRINT_USERGUIDE_H
