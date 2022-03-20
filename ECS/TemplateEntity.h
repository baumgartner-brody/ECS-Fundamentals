#ifndef _TEMPLATE_ENTITY_H_
#define _TEMPLATE_ENTITY_H_

#include <algorithm> /* remove_if */
#include <array>
#include <bitset>
#include <iostream> /* size_t */
#include <vector>

#define MAX_USER_DEFINED_CLASSES 32u

/* Forward declaration of TemplateEntity so Base can hold a pointer to it */
class TemplateEntity;

/* We use a base class as a skeleton for our user defined classes */
class Base {
public:
    TemplateEntity *owner;

    /* Calls (*this == t2.getComponent<Derived>()) */
    virtual const bool equals(const TemplateEntity &t2) { return false; }

    /* Calls dst.addComponent<Derived>(src.getComponent<Derived>()) */
    virtual void copy(TemplateEntity &dst, const TemplateEntity &src) {}

    /* Prints information unique to each derived class */
    virtual void print(std::ostream &out) {}
    
    virtual ~Base() {}
};

/* An Entity capable of holding a mixed amount of T's */
class TemplateEntity {
public:
    /* Default constructor for TemplateEntity - */
    TemplateEntity();

    /* Copy constructor for TemplateEntity (creates deep copy of old) */
    TemplateEntity(const TemplateEntity &old);

    /* Copy assignment for TemplateEntity (creates deep copy of old) */
    const TemplateEntity& operator=(const TemplateEntity &old);

    /* Frees all of this TemplateEntity's data */
    ~TemplateEntity();

    /* Clears all UDC's from this TemplateEntity */
    void clear();

    /* Attempts to invoke a constructor for T that takes in TArgs */
    /*  Allows you to call any valid constructor for the T you are creating */
    template <typename T, typename... TArgs>
    T& addUserDefinedClass(TArgs&&... mArgs) {

        /* If the user attempts to add an existing component print a warning then exit(-1); */
        if (this->hasUserDefinedClass<T>()) {
            std::cerr << "\33[91mError" << "\33[0m" << ": Tried to add a component that this TemplateEntity already has\n";
            exit(-1);
        }

        T* udc(new T(std::forward<TArgs>(mArgs)...));
        udc->owner = this;

        this->classArray[getClassTypeID<T>()] = udc;
        this->classBitset[getClassTypeID<T>()] = true;

        this->classes.emplace_back(udc);
        return *udc;
    }

    /* Determines whether or not this TemplateEntity contains an instance of T */
    template <typename T>
    const bool hasUserDefinedClass() const {
        return this->classBitset[getClassTypeID<T>()];
    }

    /* Attempt to get this TemplateEntity's T UDC. */
    /*  Return a reference if valid or exit(-1) if invalid */
    template <typename T>
    T& getUserDefinedClass() const {
        /* If the user attempts to get an invalid component print a warning then exit(-1); */
        if (!this->hasUserDefinedClass<T>()) {
            std::cerr << "\33[91mError" << "\33[0m" << ": Tried to get a component that this TemplateEntity does not have\n";
            exit(-1);
        }

        return *static_cast<T*>(this->classArray[getClassTypeID<T>()]);
    }

    /* Delete the UDC of type T from this templateEntity */
    /*  Safe to call even if the templateEntity does not have a T */
    template <typename T>
    void delUserDefinedClass() noexcept {
        /* Delete iff exists */
        if (this->hasUserDefinedClass<T>()) {
            
            /* Remove the pointer to the element of type T within the TemplateEntity's classes vector */
            this->classes.erase(std::remove_if(classes.begin(), classes.end(), 
                /* A lambda used to find the Base* of type T* */
                /*  Note that since Base is a skeleton, you could always */
                /*  add methods for determining if this component should be deleted. */
                [](Base *mBase) {
                    return typeid(*mBase) == typeid(T);
                }),
                    classes.end()
            ); 

            /* Do the actual deep delete for the UDC */
            delete this->classArray[getClassTypeID<T>()];
            
            /* Update the array and bitset so we dont accidentally try and access the deleted T* */
            this->classArray[getClassTypeID<T>()] = nullptr;
            this->classBitset[getClassTypeID<T>()] = false;
        }
    }

    /* Equality operators for template entity */
    friend const bool operator==(const TemplateEntity &t1, const TemplateEntity &t2) noexcept;
    friend const bool operator!=(const TemplateEntity &t1, const TemplateEntity &t2) noexcept;

    /* Ability to print a templateEntity for easy visualization */
    friend std::ostream& operator<<(std::ostream &out, const TemplateEntity &t);
private:

    /* A way of holding our classes in fixed positions */
    std::array<Base*, MAX_USER_DEFINED_CLASSES> classArray;

    /* A quick way of saying true/false we have this type of class */
    std::bitset<MAX_USER_DEFINED_CLASSES> classBitset;

    /* The raw Base* for when we need to iterate */
    std::vector<Base*> classes;

    /* We need a way of getting a numeric index for each (Derived*) */
    /*  This method is only accessible from inside a TemplateEntity,  */
    /*  but not unique to any one TemplateEntity object. */

    /*  It's easy to confuse these two functions, so I'm going to put a Penn & Teller */
    /*  label on each to explain what its role is. */

    /* This is the Raymond Teller function */
    /*  It creates, maintains and gives the numeric ID to the Penn function. */
    static unsigned int getClassID() {
        static unsigned int ID = 0u;
        return ++ID;
    }
    
    /* This is the Penn Gilette function. */
    /*  It asks Teller what numeric ID the type of T should have and reports it back to the */
    /*  TemplateEntity. This is exclusively the one that will "do the talking." */
    template <typename T> 
    static unsigned int getClassTypeID() noexcept {
        static unsigned int typeID = getClassID();
        return typeID;
    }

    /* Does the actual deep copy backend work */
    void copy(const TemplateEntity &old);    
};

#endif /* _TEMPLATE_ENTITY_H_ */