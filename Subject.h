// Subject.h

#ifndef Subject_h
#define Subject_h

#include <vector>


// Forward Declaration
class Observer;

class Subject {
private:
    std::vector<Observer*> observers;
public:
    void attach(Observer *observer);
    void detach(Observer *observer);
    void notifyObservers();
    virtual ~Subject() = 0;
};

#endif /* Subject_h */
