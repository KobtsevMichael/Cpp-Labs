#ifndef LAB3_ROBOTS_SCANMODE_H
#define LAB3_ROBOTS_SCANMODE_H

#include "AbstractMode.h"

class ScanMode : public AbstractMode {
private:
    int stepsN;
public:
    void init(Game*, std::vector<std::string> = {}) override;
    void executeCommand(AbstractCommand*) override;
};


#endif //LAB3_ROBOTS_SCANMODE_H
