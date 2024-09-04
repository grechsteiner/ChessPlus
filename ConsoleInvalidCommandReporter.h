// ConsoleInvalidCommandReporter.h

#ifndef ConsoleInvalidCommandReporter_h
#define ConsoleInvalidCommandReporter_h

#include <iostream>
#include <string>

#include "IInvalidCommandReporter.h"


/**
 * ConsoleInvalidCommandReporter InvalidCommandReporter  Class
 */
class ConsoleInvalidCommandReporter final : public IInvalidCommandReporter {
private:
    std::ostream &out;
    void reportErrorImpl(std::string const &errorMessage) override;
public:
    explicit ConsoleInvalidCommandReporter(std::ostream &out);
};


#endif /* ConsoleInvalidCommandReporter_h */
