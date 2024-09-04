// ErrorReporter.h

#ifndef ErrorReporter_h
#define ErrorReporter_h

#include <string>


/**
 * 
 * Abstract base class for reporting invalid commands
 */
class ErrorReporter {
private:
    virtual void reportErrorImpl(std::string const &errorMessage) = 0;
public:
    void reportError(std::string const &errorMessage);

    virtual ~ErrorReporter() = default;
};


#endif /* ErrorReporter_h */
