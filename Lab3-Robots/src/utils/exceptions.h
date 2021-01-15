#ifndef LAB3_ROBOTS_EXCEPTIONS_H
#define LAB3_ROBOTS_EXCEPTIONS_H

#include <exception>

#include "../variables/global.h"

class simple_exception : public std::exception {
private:
    std::string msg;
public:
    simple_exception(std::string const& message) : msg(message) {}
    virtual char const *what() const noexcept {
        return msg.c_str();
    }
};

class error_exception : public simple_exception {
    using simple_exception::simple_exception;
};

class info_exception : public simple_exception {
    using simple_exception::simple_exception;
};

class collide_exeption : public error_exception {
private:
    direction_t dir;
public:
    collide_exeption(std::string const& message, direction_t dir)
    : error_exception(message), dir(dir) {}
    direction_t where() const noexcept {
        return dir;
    }
};

class way_not_found_exception : public error_exception {
    using error_exception::error_exception;
};

class end_exception : public simple_exception {
    using simple_exception::simple_exception;
};

#endif //LAB3_ROBOTS_EXCEPTIONS_H
