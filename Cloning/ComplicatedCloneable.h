// ComplicatedCloneable.h

#ifndef ComplicatedCloneable_h
#define ComplicatedCloneable_h

#include <memory>


/**
 * Complicated Cloneable Class
 * - CRTP Cloning
 * - Abstract --> Abstract --> ComplicatedCloneable --> Concrete
 */
template <typename Clone, typename Base, typename Derived>
class ComplicatedCloneable : public Base {
private:
    std::unique_ptr<Clone> cloneImpl() const override;

public:
    using Base::Base;
    virtual ~ComplicatedCloneable() = 0;
};


template <typename Clone, typename Base, typename Derived>
std::unique_ptr<Clone> ComplicatedCloneable<Clone, Base, Derived>::cloneImpl() const {
        return std::make_unique<Derived>(static_cast<Derived const&>(*this));
    }

template <typename Clone, typename Base, typename Derived>
ComplicatedCloneable<Clone, Base, Derived>::~ComplicatedCloneable() {}


#endif /* ComplicatedCloneable_h */
