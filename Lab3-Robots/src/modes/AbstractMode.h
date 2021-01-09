#ifndef LAB3_ROBOTS_ABSTRACTMODE_H
#define LAB3_ROBOTS_ABSTRACTMODE_H

#include <iostream>
#include <vector>

class Game;
class AbstractCommand;

class AbstractMode {
protected:
    Game* pGame{};
public:
    virtual ~AbstractMode() = default;
    virtual void init(Game*, std::vector<std::string> = {});
    virtual void executeCommand(AbstractCommand*) = 0;
};

#endif //LAB3_ROBOTS_ABSTRACTMODE_H
