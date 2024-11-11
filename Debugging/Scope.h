
#ifndef Scope_h
#define Scope_h

#include <string>
#include <iostream>

class Scope {
    std::string s;

public:
    Scope(std::string str) : s(str) { std::cout << "Starting: " << s << std::endl; }
    ~Scope() { std::cout << "Ending: " << s << std::endl; }

};

#endif
