#ifndef LAB3_ROBOTS_COLLECTOR_H
#define LAB3_ROBOTS_COLLECTOR_H

#include "AbstractRobot.h"

class Collector : public AbstractRobot {
private:
    int apples;
public:
    explicit Collector(int id);
    [[nodiscard]] int getApples() const;
    void addApple();
};


#endif //LAB3_ROBOTS_COLLECTOR_H
