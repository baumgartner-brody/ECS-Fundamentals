#include "TemplateEntity.h"

/* Definitions for the non-template functions in templateEntity */
TemplateEntity::TemplateEntity() {}

/* Copy constructor for TemplateEntity (creates deep copy of old) */
TemplateEntity::TemplateEntity(const TemplateEntity &old) {
    this->copy(old);
}

/* Copy assignment for TemplateEntity (creates deep copy of old) */
const TemplateEntity& TemplateEntity::operator=(const TemplateEntity &old) {

    /* Guard against self assignment */
    if (*this == old) return *this;

    /* Clear and then copy */
    this->clear();
    this->copy(old);
    return *this;
}

/* Frees all of this TemplateEntity's data */
TemplateEntity::~TemplateEntity() { this->clear(); }

/* Clears all UDC's from this TemplateEntity */
void TemplateEntity::clear() {

    /* Do the actual deep deletion */
    for (auto & udc : this->classes) delete udc;
    this->classes.clear();

    /* NULL out the internal array used to access UDC's */
    for (auto & udc : this->classArray) udc = nullptr;

    /* Effectively sets every bit to false */
    this->classBitset.reset();
}

/* Turns *this into a deep copy of old */
void TemplateEntity::copy(const TemplateEntity &old) {
    /* Make a deep copy of every one of old's UDC's in *this */
    for (auto & udc : old.classes) udc->copy(*this, old);
}

/* Equality operators for template entity */
const bool operator==(const TemplateEntity &t1, const TemplateEntity &t2) noexcept {
    /* Check if t1 and t2 have an equal number of components */
    if (t1.classes.size() != t2.classes.size()) return false;

    /* Check if t1 and t2 have the same UDC types */
    for (unsigned int i = 0u; i < MAX_USER_DEFINED_CLASSES; ++i) 
        if (t1.classBitset[i] != t2.classBitset[i]) return false;
    
    /* If the have the same types now you have to check all types */
    for (unsigned int i = 0u; i < MAX_USER_DEFINED_CLASSES; ++i) 
        /* As per the above, if t1 has it, t2 also has it */
        if (t1.classBitset[i])
            if (!(t1.classArray[i]->equals(t2))) return false;
    
    /* If you've made it here, t1 == t2 */
    return true;
}

const bool operator!=(const TemplateEntity &t1, const TemplateEntity &t2) noexcept {
    return !(t1 == t2);
}

/* Prints the components of this TemplateEntity in order of the bitset */
std::ostream& operator<<(std::ostream &out, const TemplateEntity &t) {
    if (t.classes.empty()) out << "is empty";
    else { 
        out << " has " << t.classes.size() << " UDC's\n";

        /* Don't print a \n after the last derived */
        unsigned int num_printed = 0;

        /* Print each derived class in order of the bitset */
        for (unsigned int i = 0u; i < MAX_USER_DEFINED_CLASSES; ++i)
            if (t.classBitset[i]) {
                t.classArray[i]->print(out);

                ++num_printed;

                if (num_printed < t.classes.size())
                    out << '\n';
            }
    }
    
    return out;
}
