// IInputGetter.h

#ifndef IInputGetter_h
#define IInputGetter_h

#include <string>


/**
 * InputGetter Interface Class
 */
class IInputGetter {
private:
    virtual bool isInputAvailableImpl() const = 0;
    virtual std::string getInputImpl() const = 0;
    
public:
    bool isInputAvailable() const;
    std::string getInput() const;

    virtual ~IInputGetter() = default;
};

#endif /* IInputGetter_h */
