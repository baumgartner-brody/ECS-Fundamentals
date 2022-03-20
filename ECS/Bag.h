#ifndef _BAG_H_
#define _BAG_H_

#include "TemplateEntity.h"

#include <string>
#include <vector>

class Bag : public Base {
public:
    /* Default constructor for Bag - just makes _data empty */
    Bag();

    /* https://stackoverflow.com/questions/11030517/unknown-number-of-arguments-in-function */
    /*  Unknown number of known type (std::string) args */
    template <typename... SArgs>
    Bag(SArgs...sArgs) {
        this->variableNumberOfStrings({sArgs...});
    }

    /* Copy constructor and operator= for Bag */
    Bag(const Bag &old);
    const Bag& operator=(const Bag &old);

    /* Deletes all internal data */
    ~Bag();

    /* Returns this->_data.size() */
    const unsigned int size() const { return this->_data.size(); }

    /* Returns this->_data.empty() */
    const bool empty() const { return this->_data.empty(); }

    /* Clears the internal data of this Bag */
    void clear();

    /* The derived overrides */
    void copy(TemplateEntity &dst, const TemplateEntity &src) override;
    const bool equals(const TemplateEntity &t) override;
    void print(std::ostream &out) override;

    friend const bool operator==(const Bag &b1, const Bag &b2) noexcept;
    friend const bool operator!=(const Bag &b1, const Bag &b2) noexcept;

    friend std::ostream& operator<<(std::ostream &out, const Bag &b);
private:
    std::vector<std::string> _data;

    /* Initialize a Bag with any number of strings */
    void variableNumberOfStrings(const std::initializer_list<std::string> &sArgs);

    /* The backend work for making deep copies of a Bag */
    void _copy(const Bag &old);
};

#endif /* _BAG_H_ */