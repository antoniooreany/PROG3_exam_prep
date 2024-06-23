//
// Created by anton on 6/17/2024.
//

#include <iostream>

class Part {
public:
    Part() { std::cout << "cPart "; }
    Part(const Part &p) { std::cout << "copyPart "; }
    ~Part() { std::cout << "~Part "; }
};

class Base {
private:
    Part part;
public:
    Base() { std::cout << "cBase "; }
    Base(const Base &b) { std::cout << "copyBase "; }
    ~Base() { std::cout << "~Base "; }
    void method1(Base b) { std::cout << "m1Base "; }
};

class Child : public Base {
private:
    Part *ptrP;
public:
    Child() { std::cout << "cChild "; }
    Child(const Child &c) { std::cout << "copyChild "; }
    ~Child() { std::cout << "~Child "; }

    void method1(Base b) { std::cout << "m1Child "; }
    void method1(Base *b) {std::cout << "m1_Child "; b->method1(*b);}
    void method2() {std::cout << "m2Child "; ptrP = new Part();}
    };


void testTask() {

    Child c1;                               std::cout << std::endl;  // cPart cBase cChild
    Child c2 = c1;                          std::cout << std::endl;  // cPart cBase copyChild

    Base b1;                                std::cout << std::endl;  // cPart cBase
    Base* ptrB = &c2;                       std::cout << std::endl;  // NO OUTPUT

    ptrB->method1(c1);                    std::cout << std::endl;  // cPart copyBase m1Base ~Base ~Part
    ptrB = new Child();                     std::cout << std::endl;  // cPart cBase cChild

    static_cast<Child *>(ptrB)->method2();  std::cout << std::endl;  // m2Child cPart
    c1.method2();                           std::cout << std::endl;  // m2Child cPart

    delete ptrB;                            std::cout << std::endl;  // ~Part ~Base

    Child *ptrC = &c1;                      std::cout << std::endl;  // NO OUTPUT
    ptrC->method1(&c2);                     std::cout << std::endl;  // m1_Child cPart copyBase m1Base ~Base ~Part

    delete ptrC;                            std::cout << std::endl;  // ~Child ~Base ~Part
    // Error: Process finished with exit code -1073740940 (0xC0000374)
}                                          // todo NO OUTPUT like:   // ~Base ~Part ~Child ~Base ~Part ~Child ~Base ~Part

// todo The objects, created on stack, is not deleted by delete operator, meaning no destructor is called,
// todo therefore no output of ~Object is printed.
// todo QUESTION TO BAER: Am I wrong? If not, what should I answer on the exam?


// todo Uncomment main() to test the code
// int main() {
//     testTask1();
//     return 0;
// }
