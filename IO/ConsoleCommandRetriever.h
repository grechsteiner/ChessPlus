// ConsoleCommandRetriever.h

#ifndef ConsoleCommandRetriever_h
#define ConsoleCommandRetriever_h

#include <iostream>
#include <optional>
#include <string>

#include "Cloneable.h"
#include "CommandRetriever.h"


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
    ConsoleCommandRetriever& operator=(ConsoleCommandRetriever const &other) = delete;
    ConsoleCommandRetriever& operator=(ConsoleCommandRetriever &&other) = delete;
    virtual ~ConsoleCommandRetriever() = default;
};


#endif /* ConsoleCommandRetriever_h */
