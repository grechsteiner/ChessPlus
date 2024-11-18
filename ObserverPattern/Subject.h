// Subject.h

#ifndef Subject_h
#define Subject_h

#include <vector>

#include "Observer.h"


/**
 * Abstract Subject Class (Observer Pattern)
 */
class Subject {
private:
    std::vector<Observer*> observers;

protected:
    explicit Subject();
    Subject(Subject const &other);
    Subject(Subject &&other) noexcept;
    Subject& operator=(Subject const &other);
    Subject& operator=(Subject &&other) noexcept;

public:
    virtual ~Subject() = 0;

    void attach(Observer *observer);
    void detach(Observer *observer);
    void notifyObservers();
};


#endif /* Subject_h */
