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

class illegalIndex 
{
   public:
      illegalIndex(std::string theMessage = "Illegal index") : message(theMessage) {};
      void outputMessage() {std::cout << message << std::endl;}
   private:
      std::string message;
};

class matrixIndexOutOfBounds 
{
   public:
      matrixIndexOutOfBounds(std::string theMessage = "Matrix index out of bounds") {message = theMessage;}
      void outputMessage() {std::cout << message << std::endl;}
   private:
      std::string message;
};

// matrix size mismatch
class matrixSizeMismatch 
{
   public:
      matrixSizeMismatch(std::string theMessage = 
                   "The size of the two matrics doesn't match")
            {message = theMessage;}
      void outputMessage() {std::cout << message << std::endl;}
   private:
      std::string message;
};

#endif