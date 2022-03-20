#include "Box.h"

/* Definitions for the Box class */

/* Value constructor for box */
Box::Box(const int &x, const int &y, const int &z) {
    this->_x = x;
    this->_y = y;
    this->_z = z;
}

/* The copy constructor and assignment operator for Box */
Box::Box(const Box &old) {
    this->_copy(old);
}

/* Assignment operator for Box */
const Box& Box::operator=(const Box &old) {
    /* Guard self assignment */
    if (*this == old) return *this;

    /* Copy old */
    this->_copy(old);
    return *this;
}

/* Since there is no dynamic memory, this does nothing. */
Box::~Box() {}

void Box::copy(TemplateEntity &dst, const TemplateEntity &src) {
    dst.addUserDefinedClass<Box>(src.getUserDefinedClass<Box>());
}

const bool Box::equals(const TemplateEntity &t) {
    return (*this == t.getUserDefinedClass<Box>());
}

void Box::print(std::ostream &out) {
    out << *this;
}

/* Equality operators for Bag class */
const bool operator==(const Box &b1, const Box &b2) noexcept {
    return (b1._x == b2._x) && (b1._y == b2._y) && (b1._z == b2._z);
}

const bool operator!=(const Box &b1, const Box &b2) noexcept {
    return !(b1 == b2);
}

/* Operator << for Box - Prints "Box: x y z " */
std::ostream& operator<<(std::ostream &out, const Box &b) {
    out << "Box: " << b._x << ' ' << b._y << ' ' << b._z;
    return out;
}

/* Copies old into *this */
void Box::_copy(const Box &old) {
    this->_x = old._x;
    this->_y = old._y;
    this->_z = old._z;
}