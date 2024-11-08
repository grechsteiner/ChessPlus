// CommandRetriever.h

#ifndef CommandRetriever_h
#define CommandRetriever_h

#include <string>


/**
 * CommandRetriever Interface Class
 */
class CommandRetriever {
private:
    virtual bool isInputAvailableImpl() const = 0;
    virtual std::string getInputImpl() const = 0;
    
public:
    bool isInputAvailable() const;
    std::string getInput() const;

    virtual ~CommandRetriever() = default;
};

#endif /* CommandRetriever_h */
