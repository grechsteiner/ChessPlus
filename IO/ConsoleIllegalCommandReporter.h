// ConsoleIllegalCommandReporter.h

#ifndef ConsoleIllegalCommandReporter_h
#define ConsoleIllegalCommandReporter_h

#include <iostream>
#include <string>

#include "IllegalCommandReporter.h"


/**
 * ConsoleIllegalCommandReporter InvalidCommandReporter  Class
 */
class ConsoleIllegalCommandReporter final : public IllegalCommandReporter {
private:
    std::ostream &out;
    void reportErrorImpl(std::string const &errorMessage) override;
public:
    explicit ConsoleIllegalCommandReporter(std::ostream &out);
};


#endif /* ConsoleIllegalCommandReporter_h */
