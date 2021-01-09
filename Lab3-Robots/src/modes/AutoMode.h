#ifndef LAB3_ROBOTS_AUTOMODE_H
#define LAB3_ROBOTS_AUTOMODE_H

#include "AbstractMode.h"

class AutoMode : public AbstractMode {
public:
    void executeCommand(AbstractCommand*) override;
};


#endif //LAB3_ROBOTS_AUTOMODE_H
