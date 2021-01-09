#ifndef LAB3_ROBOTS_EXCEPTIONS_H
#define LAB3_ROBOTS_EXCEPTIONS_H

#include <exception>

class descriptive_exception : public std::exception {
private:
    std::string msg;
public:
    descriptive_exception(std::string const &message) : msg(message) {}
    virtual char const *what() const noexcept {
        return msg.c_str();
    }
};

class end_exception : public descriptive_exception {
public:
    end_exception(std::string const &message)
    : descriptive_exception(message) {}
};

#endif //LAB3_ROBOTS_EXCEPTIONS_H
