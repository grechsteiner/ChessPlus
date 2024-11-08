// ConsoleCommandRetriever.h

#ifndef ConsoleCommandRetriever_h
#define ConsoleCommandRetriever_h

#include <string>
#include <iostream>

#include "CommandRetriever.h"


/**
 * ConsoleCommandRetriever CommandRetriever Class
 */
class ConsoleCommandRetriever final : public CommandRetriever {
private:
    std::istream &in;
    bool isInputAvailableImpl() const override;
    std::string getInputImpl() const override;
    
public:
    explicit ConsoleCommandRetriever(std::istream &in);
};


#endif /* ConsoleCommandRetriever_h */
