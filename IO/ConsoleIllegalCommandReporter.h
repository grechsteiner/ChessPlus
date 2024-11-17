// ConsoleIllegalCommandReporter.h

#ifndef ConsoleIllegalCommandReporter_h
#define ConsoleIllegalCommandReporter_h

#include <iostream>
#include <string>

#include "Cloneable.h"
#include "IllegalCommandReporter.h"


/**
 * ConsoleIllegalCommandReporter InvalidCommandReporter  Class
 */
class ConsoleIllegalCommandReporter final : public Cloneable<IllegalCommandReporter, ConsoleIllegalCommandReporter> {
private:
    std::ostream &out;

    void reportIllegalCommandImpl(std::string const &message) override;

public:
    explicit ConsoleIllegalCommandReporter(std::ostream &out);
    ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter const &other);
    ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter &&other) noexcept;
    IllegalCommandReporter& operator=(IllegalCommandReporter const &other) = delete;
    IllegalCommandReporter& operator=(IllegalCommandReporter &&other) = delete;
    virtual ~ConsoleIllegalCommandReporter() = default;
};


#endif /* ConsoleIllegalCommandReporter_h */
