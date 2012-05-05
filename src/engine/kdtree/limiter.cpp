#include "limiter.hpp"

Limiter::Limiter(const std::string& property_name, const Type* bound, bool is_upper_bound, bool is_inclusive)
    : property_name_(property_name), bound_(bound->clone()), is_upper_bound_(is_upper_bound), is_inclusive_(is_inclusive)
{ }

Limiter::~Limiter() {}

bool Limiter::is_more_strict(const Limiter& rhs) const
{
    if (is_upper_bound_ != rhs.is_upper_bound()) {
        assert(!"Limiter::is_more_strict error. Please report this as a bug. Stacktrace will be very appriciated.");
    }

    if (bound_->equals(rhs.get_bound_value())) {
        bool left = is_inclusive();
        bool right = rhs.is_inclusive();

        if (left == right) return false;
        return (left == false);
    }

    if (is_upper_bound_) return bound_->is_smaller(rhs.get_bound_value());
    else return bound_->is_greater(rhs.get_bound_value());
}

bool Limiter::is_value_matching(const Type* rhs) const
{
    if (!is_upper_bound_ && is_inclusive_) return bound_->is_smaller_or_equal(rhs);
    if (!is_upper_bound_ && !is_inclusive_) return bound_->is_smaller(rhs);
    if (is_upper_bound_ && is_inclusive_) return bound_->is_greater_or_equal(rhs);
    if (is_upper_bound_ && !is_inclusive_) return bound_->is_greater(rhs);
    assert(!"Not possible to get here");
    return false;
}

bool Limiter::is_disjoint(const Limiter& rhs) const
{
    if (rhs.is_upper_bound() == is_upper_bound()) return false;

    if (bound_->equals(rhs.get_bound_value())) {
        return !rhs.is_inclusive() || !is_inclusive();
    }

    if (is_upper_bound()) return bound_->is_smaller(rhs.get_bound_value());
    else return bound_->is_greater(rhs.get_bound_value());
}

Limiter Limiter::createReverseLimiter() const
{
    return Limiter(property_name_, bound_, !is_upper_bound_, !is_inclusive_);
}

const Type* Limiter::get_bound_value() const
{
    return bound_;
}

bool Limiter::is_upper_bound() const
{
    return is_upper_bound_;
}

bool Limiter::is_inclusive() const
{
    return is_inclusive_;
}


const std::string& Limiter::get_property_name() const
{
    return property_name_;
}

void Limiter::debug() const
{
    std::cerr << "LIMITER " << property_name_;
    std::cerr << (is_upper_bound() ? "<" : ">");
    std::cerr << (is_inclusive() ? "=" : "");
    std::cerr << get_bound_value()->to_string() << "\n";
}
