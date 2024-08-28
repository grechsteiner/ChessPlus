// ErrorReporter.h

#ifndef ErrorReporter_h
#define ErrorReporter_h

#include <string>


class ErrorReporter {
private:
    virtual void outputError(std::string const &errorMessage) = 0;
public:
    ErrorReporter() = default;
    virtual ~ErrorReporter() = default;
    void reportError(std::string const &errorMessage);
};


#endif /* ErrorReporter_h */
