// ConsoleIllegalCommandReporter.h

#ifndef ConsoleIllegalCommandReporter_h
#define ConsoleIllegalCommandReporter_h

#include <iostream>
#include <string>

#include "IllegalCommandReporter.h"
#include "Cloneable.h"


/**
 * ConsoleIllegalCommandReporter InvalidCommandReporter  Class
 */
class ConsoleIllegalCommandReporter final : public Cloneable<IllegalCommandReporter,ConsoleIllegalCommandReporter> {
private:
    std::ostream &out;
    void reportIllegalCommandImpl(std::string const &message) override;
public:
    explicit ConsoleIllegalCommandReporter(std::ostream &out);
    ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter const &other);
    ConsoleIllegalCommandReporter(ConsoleIllegalCommandReporter &&other) noexcept;
    // Copy assignment not enabled (can't copy streams)
    // Move assignment not enabled (can't move streams)
    virtual ~ConsoleIllegalCommandReporter() = default;
};


#endif /* ConsoleIllegalCommandReporter_h */
