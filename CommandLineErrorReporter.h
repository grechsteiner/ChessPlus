// CommandLineErrorReporter.h

#ifndef CommandLineErrorReporter_h
#define CommandLineErrorReporter_h

#include <iostream>
#include <string>

#include "ErrorReporter.h"


/**
 * CommandLineErrorReporter ErrorReporter Class
 * Derived ErrorReporter Class for reporting errors to the console
 */
class CommandLineErrorReporter final : public ErrorReporter {
private:
    std::ostream &out;
    void reportErrorImpl(std::string const &errorMessage) override;
public:
    explicit CommandLineErrorReporter(std::ostream &out);
};


#endif /* CommandLineErrorReporter_h */
