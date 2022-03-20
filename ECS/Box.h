#ifndef _BOX_H_
#define _BOX_H_

#include "TemplateEntity.h"

class Box : public Base {
public:
    /* Value constructor for Box */
    Box(const int &x, const int &y, const int &z);

    /* Copy constructor and assignment for Box */
    Box(const Box &old);
    const Box& operator=(const Box &old);

    ~Box();

    /* The derived overrides */
    void copy(TemplateEntity &dst, const TemplateEntity &src) override;
    const bool equals(const TemplateEntity &t) override;
    void print(std::ostream &out) override;

    friend const bool operator==(const Box &b1, const Box &b2) noexcept;
    friend const bool operator!=(const Box &b1, const Box &b2) noexcept;

    friend std::ostream& operator<<(std::ostream &out, const Box &b);

private:
    unsigned int _x, _y, _z;

    /* Copies old into *this */
    void _copy(const Box &old);
};

#endif /* _BOX_H_ */