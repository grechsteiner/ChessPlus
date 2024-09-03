// Input.h

#ifndef Input_h
#define Input_h

#include <string>


class Input {
private:
    virtual std::string getInputImpl() = 0;
    virtual bool isInputAvailableImpl() const = 0;
public:
    Input() = default;
    virtual ~Input() = default;
    std::string getInput();
    bool isInputAvailable() const;
};

#endif /* Input_h */
