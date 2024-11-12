// ConsoleCommandRetriever.h

#ifndef ConsoleCommandRetriever_h
#define ConsoleCommandRetriever_h

#include <string>
#include <iostream>

#include "CommandRetriever.h"
#include "Cloneable.h"


/**
 * ConsoleCommandRetriever CommandRetriever Class
 */
class ConsoleCommandRetriever final : public Cloneable<CommandRetriever, ConsoleCommandRetriever> {
private:
    std::istream &in;
    bool isCommandAvailableImpl() const override;
    std::optional<std::string> retrieveCommandImpl() const override;
    
public:
    explicit ConsoleCommandRetriever(std::istream &in);
    ConsoleCommandRetriever(ConsoleCommandRetriever const &other);
    ConsoleCommandRetriever(ConsoleCommandRetriever &&other) noexcept;
    // Copy assignment not enabled (can't copy streams)
    // Move assignment not enabled (can't move streams)
    virtual ~ConsoleCommandRetriever() = default;
};


#endif /* ConsoleCommandRetriever_h */
