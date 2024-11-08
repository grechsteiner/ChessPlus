// IllegalCommandReporter.h

#ifndef IllegalCommandReporter_h
#define IllegalCommandReporter_h

#include <string>


/**
 * IllegalCommandReporter Interface Class
 */
class IllegalCommandReporter {
private:
    virtual void reportErrorImpl(std::string const &errorMessage) = 0;
public:
    void reportError(std::string const &errorMessage);

    virtual ~IllegalCommandReporter() = default;
};


#endif /* IllegalCommandReporter_h */
