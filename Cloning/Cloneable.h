// Cloneable.h

#ifndef Cloneable_h
#define Cloneable_h

#include <memory>


/**
 * Cloneable Class
 * - CRTP Cloning
 * - Abstract --> ComplicatedCloneable --> Concrete
 */
template <typename Base, typename Derived>
class Cloneable : public Base {
private:
    std::unique_ptr<Base> cloneImpl() const override;

public:
    using Base::Base;
    virtual ~Cloneable() = 0;
};


template <typename Base, typename Derived>
std::unique_ptr<Base> Cloneable<Base, Derived>::cloneImpl() const {
    return std::make_unique<Derived>(static_cast<Derived const&>(*this));
}

template <typename Base, typename Derived>
Cloneable<Base, Derived>::~Cloneable() {}


#endif /* Cloneable_h */
