// IllegalCommandReporter.h

#ifndef IllegalCommandReporter_h
#define IllegalCommandReporter_h

#include <memory>
#include <string>


/**
 * Abstract IllegalCommandReporter Class
 */
class IllegalCommandReporter {
private:
    virtual void reportIllegalCommandImpl(std::string const &message) = 0;
    virtual std::unique_ptr<IllegalCommandReporter> cloneImpl() const = 0;

protected:
    explicit IllegalCommandReporter();
    IllegalCommandReporter(IllegalCommandReporter const &other);
    IllegalCommandReporter(IllegalCommandReporter &&other) noexcept;
    IllegalCommandReporter& operator=(IllegalCommandReporter const &other);
    IllegalCommandReporter& operator=(IllegalCommandReporter &&other) noexcept;

public:
    void reportIllegalCommand(std::string const &message);
    std::unique_ptr<IllegalCommandReporter> clone() const;

    virtual ~IllegalCommandReporter() = default;
};


#endif /* IllegalCommandReporter_h */
