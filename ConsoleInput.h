// ConsoleInputGetter.h

#ifndef ConsoleInputGetter_h
#define ConsoleInputGetter_h

#include <string>
#include <iostream>

#include "IInputGetter.h"


/**
 * ConsoleInputGetter Input Class
 */
class ConsoleInputGetter final : public IInputGetter {
private:
    std::istream &in;
    bool isInputAvailableImpl() const override;
    std::string getInputImpl() const override;
    
public:
    explicit ConsoleInputGetter(std::istream &in);
};


#endif /* ConsoleInputGetter_h */
