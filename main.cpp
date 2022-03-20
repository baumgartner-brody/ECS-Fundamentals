#include "ECS/UserDefinedClasses.h"

#include <iostream>

constexpr const char * ANSI_BRIGHTRED = "\33[91m";
constexpr const char * ANSI_BRIGHTGREEN = "\33[92m";
constexpr const char * ANSI_BRIGHTCYAN = "\33[96m";

constexpr const char * ANSI_RESET = "\33[0m";

/* Prints TemplateEntity in bright cyan letters and then resets terminal back to white */
constexpr const char * TE = "\33[96mTemplateEntity\33[0m";

/* General walkthrough of TemplateEntity usage */
void demonstrateTemplateEntityUsage();

/* Main driver code to demonstrate/test TemplateEntity */
int main() {
    
    demonstrateTemplateEntityUsage();

    return 0;
}

void demonstrateTemplateEntityUsage() {

    std::cout << '\n';
    std::cout << "Demonstrating " << TE << " Basic Usage\n";
    std::cout << '\n';

    /* Create a default templateEntity */
    std::cout << "Using the default constructor to say \"" << TE << " t\"\n";
    TemplateEntity t;
    std::cout << "t: " << t << '\n';

    /* Adding two UDC's to T Box and Bag */
    std::cout << "t.addComponent<" << ANSI_BRIGHTGREEN << "Box" << ANSI_RESET << ">(1, 2, 3);\n";
    std::cout << "t.addComponent<" << ANSI_BRIGHTGREEN << "Bag" << ANSI_RESET << ">(\"Variable\", \"number\", \"of\", \"strings\");\n";
    t.addUserDefinedClass<Box>(1, 2, 3);
    t.addUserDefinedClass<Bag>("Variable", "number", "of", "strings");

    /* Un-note this to cause an Error */
    //t.addUserDefinedClass<Bag>();

    std::cout << "t: " << t << '\n';
    std::cout << '\n';

    /* Something to note about the print order of the UDC's and the order the UDC's get added: */
    /*  The first time the program calls addUDC<T>() for any specific T, it's place in the bitset */
    /*  is set-in-stone. Thus, switching the two lines above would cause all objects (from that point onwards) */
    /*  in the program to have differently ordered innards. In cases where T needs to have one specified ID */
    /*  regardless of how the first TemplateEntity is built, use */
    /*  "virtual unsigned int getID() { return 0u; }"  */
    /*  in the Base class, and override it in all derived UDC's. */
    /*  (E.g. This technicality might come in handy if your code has multiple versions) */
    std::cout << "Using the default constructor to say \"" << TE << " t2\"\n";
    TemplateEntity t2;
    std::cout << "t2: " << t2 << '\n';

    std::cout << "t.addComponent<" << ANSI_BRIGHTGREEN << "Bag" << ANSI_RESET << ">(\"Variable\", \"number\", \"of\", \"strings\");\n";
    std::cout << "t.addComponent<" << ANSI_BRIGHTGREEN << "Box" << ANSI_RESET << ">(1, 2, 3);\n";

    t2.addUserDefinedClass<Bag>("Variable", "number", "of", "strings");
    t2.addUserDefinedClass<Box>(1, 2, 3);

    std::cout << "t2: " << t2 << '\n';
    std::cout << '\n';

    std::cout << "Testing == while we're at it...\n";
    std::cout << "(t == t2) : " << (t == t2) << '\n';
    std::cout << '\n';

    std::cout << "Deleting t2's Bag UDC\n";
    std::cout << "t2.delUserDefinedComponent<" << ANSI_BRIGHTGREEN << "Bag" << ANSI_RESET << ">();\n";

    /* Safe to call regardless of whether or not hasUDC<T>() is true */
    t2.delUserDefinedClass<Bag>();

    std::cout << "t2: " << t2 << '\n';
    std::cout << '\n';

    std::cout << "Testing != while we're at it...\n";
    std::cout << "(t != t2) : " << (t != t2) << '\n';

    std::cout << '\n';
    std::cout << "Demonstrating copy constructor for both TemplateEntity and individual UDC's\n";
    std::cout << TE << " t3(t);\n";
    std::cout << TE << " t4;\n";
    std::cout << "t4.addUserDefinedClass<" << ANSI_BRIGHTGREEN << "Bag" << ANSI_RESET 
        << ">(t.getUserDefinedClass<" << ANSI_BRIGHTGREEN << "Bag" << ANSI_RESET << ">());\n";
    std::cout << "t4.addUserDefinedClass<" << ANSI_BRIGHTGREEN << "Box" << ANSI_RESET 
        << ">(t.getUserDefinedClass<" << ANSI_BRIGHTGREEN << "Box" << ANSI_RESET << ">());\n";
    TemplateEntity t3(t);
    TemplateEntity t4;
    t4.addUserDefinedClass<Bag>(t.getUserDefinedClass<Bag>());
    t4.addUserDefinedClass<Box>(t.getUserDefinedClass<Box>());

    std::cout << "t3 : " << t3 << '\n';
    std::cout << '\n';

    std::cout << "t4 == t3 ? " << (t3 == t4) << '\n';
    std::cout << "t2.clear() & then t3 = t2\n";
    t2.clear();
    t3 = t2;
    std::cout << "t3 : " << t3 << '\n';
    std::cout << '\n';

    std::cout << "t2 == t3 ? " << (t2 == t3) << '\n';

    /* Un-note this to cause a different Error */
    //t2.getComponent<Bag>();


}

