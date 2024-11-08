// IllegalCommandReporter.h

#ifndef IllegalCommandReporter_h
#define IllegalCommandReporter_h

#include <string>


/**
 * IllegalCommandReporter Interface Class
 */
class IllegalCommandReporter {
private:
    virtual void reportIllegalCommandImpl(std::string const &illegalCommand) = 0;

protected:
    explicit IllegalCommandReporter();
    IllegalCommandReporter(IllegalCommandReporter const &other) = default;
    IllegalCommandReporter(IllegalCommandReporter &&other) noexcept;
    IllegalCommandReporter& operator=(IllegalCommandReporter const &other) = default;
    IllegalCommandReporter& operator=(IllegalCommandReporter &&other) noexcept;

public:
    void reportIllegalCommand(std::string const &illegalCommand);

    virtual ~IllegalCommandReporter() = default;
};


#endif /* IllegalCommandReporter_h */
