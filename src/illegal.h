#ifndef ILLEGAL_H
#define ILLEGAL_H

#include <string>
#include <iostream>

class illegalParameterValue{
private:
    std::string message;
public:
    illegalParameterValue() : message("Illegal parameter value") {};
    illegalParameterValue(std::string theMessage) : message(theMessage) {};
    void outputMessage() {std::cout << message << std::endl;}
};

#endif