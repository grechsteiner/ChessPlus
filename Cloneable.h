// PieceCloneable.h

#ifndef PieceCloneable_h
#define PieceCloneable_h

#include <memory>


template <typename Base, typename Derived>
class Cloneable : public Base {
private:
    std::unique_ptr<Base> cloneImpl() const override {
        return std::make_unique<Derived>(static_cast<Derived const&>(*this));
    }
public:
    using Base::Base;
};

#endif /* PieceCloneable */
