// CommandLineErrorReporter.h

#ifndef CommandLineErrorReporter_h
#define CommandLineErrorReporter_h

#include <string>
#include <iostream>

#include "ErrorReporter.h"


class CommandLineErrorReporter : public ErrorReporter {
private:
    std::ostream &out;
    void reportErrorImpl(std::string const &errorMessage) override;
public:
    CommandLineErrorReporter(std::ostream &out);
};


#endif /* CommandLineErrorReporter_h */
