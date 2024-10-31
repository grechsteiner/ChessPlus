// ComplicatedCloneable.h

#ifndef ComplicatedCloneable_h
#define ComplicatedCloneable_h

#include <memory>

/**
 * Used when clone type is not base type
 * Unique ptrs can't implicitly upcast via covariance
 * Ex: Abstract --> Abstract --> Concrete
 */
template <typename Clone, typename Base, typename Derived>
class ComplicatedCloneable : public Base {
private:
    std::unique_ptr<Clone> cloneImpl() const override {
        return std::make_unique<Derived>(static_cast<Derived const&>(*this));
    }
public:
    using Base::Base;
    virtual ~ComplicatedCloneable() = 0;
};

template <typename Clone, typename Base, typename Derived>
ComplicatedCloneable<Clone, Base, Derived>::~ComplicatedCloneable() {}


#endif /* ComplicatedCloneable_h */
