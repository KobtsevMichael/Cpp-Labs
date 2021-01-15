#ifndef LAB3_ROBOTS_MANUALMODE_H
#define LAB3_ROBOTS_MANUALMODE_H

#include "../commands/manual_mode/AbstractManualModeCommand.h"

#include "AbstractMode.h"

class ManualMode : public AbstractMode {
public:
    void sendCommand(AbstractCommand*) override;
};


#endif //LAB3_ROBOTS_MANUALMODE_H
