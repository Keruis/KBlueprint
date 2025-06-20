#ifndef BLUEPRINT_SYSTEM_H
#define BLUEPRINT_SYSTEM_H

#include "../../utils/window/X11.h"

class System : public X11Window {
public:
    System(int width, int height, const std::string& title);
    ~System() override;
};


#endif //BLUEPRINT_SYSTEM_H
