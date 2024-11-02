// Observer.h

#ifndef Observer_h
#define Observer_h

class Observer {
private:
    virtual void notifyImpl() = 0;
public:
    void notify();
    virtual ~Observer() = default;
};

#endif /* Observer_h */
