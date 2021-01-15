#ifndef LAB3_ROBOTS_TOGGLESAPPERCOMMAND_H
#define LAB3_ROBOTS_TOGGLESAPPERCOMMAND_H

#include "AbstractCommand.h"

class ToggleSapperCommand : public AbstractCommand {
private:
    const int argc = 2;
    bool action;
public:
    void validate(std::vector<std::string>) override;
    void execute(Game *) override;
};


#endif //LAB3_ROBOTS_TOGGLESAPPERCOMMAND_H
