// CommandRetriever.h

#ifndef CommandRetriever_h
#define CommandRetriever_h

#include <string>


/**
 * CommandRetriever Interface Class
 */
class CommandRetriever {
private:
    virtual bool isCommandAvailableImpl() const = 0;
    virtual std::string retrieveCommandImpl() const = 0;

protected:
    explicit CommandRetriever();
    CommandRetriever(CommandRetriever const &other) = default;
    CommandRetriever(CommandRetriever &&other) noexcept;
    CommandRetriever& operator=(CommandRetriever const &other) = default;
    CommandRetriever& operator=(CommandRetriever &&other) noexcept;
    
public:
    bool isCommandAvailable() const;
    std::string retrieveCommand() const;

    virtual ~CommandRetriever() = default;
};

#endif /* CommandRetriever_h */
