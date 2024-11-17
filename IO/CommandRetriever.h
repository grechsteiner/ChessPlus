// CommandRetriever.h

#ifndef CommandRetriever_h
#define CommandRetriever_h

#include <memory>
#include <optional>
#include <string>


/**
 * Abstract CommandRetriever Class
 */
class CommandRetriever {
private:
    virtual bool isCommandAvailableImpl() const = 0;
    virtual std::optional<std::string> retrieveCommandImpl() const = 0;
    virtual std::unique_ptr<CommandRetriever> cloneImpl() const = 0;

protected:
    explicit CommandRetriever();
    CommandRetriever(CommandRetriever const &other);
    CommandRetriever(CommandRetriever &&other) noexcept;
    CommandRetriever& operator=(CommandRetriever const &other);
    CommandRetriever& operator=(CommandRetriever &&other) noexcept;
    
public:
    bool isCommandAvailable() const;
    std::optional<std::string> retrieveCommand() const;
    std::unique_ptr<CommandRetriever> clone() const;

    virtual ~CommandRetriever() = default;
};


#endif /* CommandRetriever_h */
