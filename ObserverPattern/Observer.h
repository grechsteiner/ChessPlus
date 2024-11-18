// Observer.h

#ifndef Observer_h
#define Observer_h


/**
 * Abstract Observer Class (Observer Pattern)
 */
class Observer {
private:
    virtual void notifyImpl() = 0;

protected:
    explicit Observer();
    Observer(Observer const &other);
    Observer(Observer &&other) noexcept;
    Observer& operator=(Observer const &other);
    Observer& operator=(Observer &&other) noexcept;

public:
    virtual ~Observer() = default;

    void notify();
};


#endif /* Observer_h */
