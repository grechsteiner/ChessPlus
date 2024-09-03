// CommandLineInput.h

#ifndef CommandLineInput_h
#define CommandLineInput_h

#include <iostream>
#include <string>

#include "Input.h"


class CommandLineInput : public Input {
private:
    std::istream &in;
    std::string getInputImpl() override;
    bool isInputAvailableImpl() const override;
public:
    CommandLineInput(std::istream &in);
};


#endif /* CommandLineInput_h */
