// CommandLineInput.h

#ifndef CommandLineInput_h
#define CommandLineInput_h

#include <string>
#include <iostream>

#include "Input.h"


/**
 * CommandLineInput Input Class
 * Derived Input Class for getting input from the console
 */
class CommandLineInput final : public Input {
private:
    std::istream &in;
    bool isInputAvailableImpl() const override;
    std::string getInputImpl() const override;
    
public:
    explicit CommandLineInput(std::istream &in);
};


#endif /* CommandLineInput_h */
