// Observer.h

#ifndef Observer_h
#define Observer_h

#include <memory>


class Observer {
private:
    virtual void notifyImpl() = 0;
    virtual std::unique_ptr<Observer> cloneImpl() const = 0;
protected:
    explicit Observer();
    Observer(Observer const &other) = default;
    Observer(Observer &&other) noexcept;
    Observer& operator=(Observer const &other) = default;
    Observer& operator=(Observer &&other) noexcept;

public:
    void notify();
    std::unique_ptr<Observer> clone() const;

    virtual ~Observer() = default;
};


#endif /* Observer_h */
