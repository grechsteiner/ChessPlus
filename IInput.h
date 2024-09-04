// Input.h

#ifndef Input_h
#define Input_h

#include <string>


/**
 * Input Class
 * Abstract base class for retrieving input to the program
 */
class Input {
private:
    virtual bool isInputAvailableImpl() const = 0;
    virtual std::string getInputImpl() const = 0;
    
public:
    bool isInputAvailable() const;
    std::string getInput() const;

    virtual ~Input() = default;
};

#endif /* Input_h */
