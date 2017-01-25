#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <bits/stdc++.h>

class Exception : public std::exception {
    std::string error;

  public:
    Exception(std::string error) { this->error = error; }
    const char *what() const noexcept override { return this->error.c_str(); }
};

#endif // EXCEPTION_H
