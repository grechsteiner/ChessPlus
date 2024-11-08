// IInvalidCommandReporter.h

#ifndef IInvalidCommandReporter_h
#define IInvalidCommandReporter_h

#include <string>


/**
 * InvalidCommandReporter Interface Class
 */
class IInvalidCommandReporter {
private:
    virtual void reportErrorImpl(std::string const &errorMessage) = 0;
public:
    void reportError(std::string const &errorMessage);

    virtual ~IInvalidCommandReporter() = default;
};


#endif /* IInvalidCommandReporter_h */
