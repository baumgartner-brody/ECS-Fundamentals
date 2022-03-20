#include "Bag.h"

/* Definitions for Bag.h */

/* Default constructor - no internal data */
Bag::Bag() {}

/* The backend function that takes a variable number of string args */
void Bag::variableNumberOfStrings(const std::initializer_list<std::string> &sArgs) {
    for (auto & s : sArgs)
        this->_data.emplace_back(s);
}

/* Create a deep copy of old in *this */
Bag::Bag(const Bag &old) { 
    this->_copy(old);
}

/* Create a deep copy of old in *this */
const Bag& Bag::operator=(const Bag &old) {
    /* Guard self assignment */
    if (*this == old) return *this;

    /* Clear this and then copy old */
    this->clear();
    this->_copy(old);
    return *this;
}

Bag::~Bag() { 
    this->clear();
}   

/* Clears the internal data of this Bag */
void Bag::clear() {
    for (auto & s : this->_data)
        s.clear();
    this->_data.clear();
}

/* The two overridden methods for each derived class */
void Bag::copy(TemplateEntity &dst, const TemplateEntity &src) {
    dst.addUserDefinedClass<Bag>(src.getUserDefinedClass<Bag>());
}

const bool Bag::equals(const TemplateEntity &t) {
    return (*this == t.getUserDefinedClass<Bag>());
}

void Bag::print(std::ostream &out) {
    out << *this;
}

/* Equality operators for Bag class */
const bool operator==(const Bag &b1, const Bag &b2) noexcept {
    /* Check if the sizes are equal */
    if (b1.size() != b2.size()) return false;

    /* Check the _data */
    std::vector<std::string>::const_iterator s1(b1._data.begin());
    std::vector<std::string>::const_iterator s2(b2._data.begin());
    while (s1 != b1._data.end()) {
        /* Check if *s1 == *s2 */
        if (*s1 != *s2) return false;

        /* Increment both iterators */
        ++s1; ++s2;
    }

    /* If you've made it here the Bags are equal */
    return true;
}

const bool operator!=(const Bag &b1, const Bag &b2) noexcept {
    return !(b1 == b2);
}

/* Operator<< for Bag */
/*  Prints the size of the _data and then each element */
std::ostream& operator<<(std::ostream &out, const Bag &b) {
    out << "Bag (";
    /* If bag is empty just print Bag (empty)*/
    if (b.empty()) out << "empty)";
    /* Otherwise print the Bag(size): {elements} */
    else {
        out << b.size() << "): { ";
            for (unsigned int i = 0u; i < b.size() - 1; ++i)
                out << '\"' << b._data[i] << "\", ";
            out << '\"' << b._data.back() << "\" }";
    }
    return out;
}

/* Backend copy operator for Bag's _data */
void Bag::_copy(const Bag &old) {
    for (auto & s : old._data)
        this->_data.emplace_back(s);
}
