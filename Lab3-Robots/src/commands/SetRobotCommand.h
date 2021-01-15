#ifndef LAB3_ROBOTS_SETROBOTCOMMAND_H
#define LAB3_ROBOTS_SETROBOTCOMMAND_H

#include "AbstractCommand.h"

class SetRobotCommand : public AbstractCommand {
private:
    const int argc = 2;
    int newId;
public:
    void validate(std::vector<std::string>) override;
    void execute(Game *) override;
};


#endif //LAB3_ROBOTS_SETROBOTCOMMAND_H
