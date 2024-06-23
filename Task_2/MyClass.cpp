#include <iostream>

class MyClass {
public:
    MyClass(int value) : memberVariable(value) {}

    void setValue(int value) {
        memberVariable = value;
    }

    int getValue() const {
        return memberVariable;
    }

    void printValue() const {
        std::cout << memberVariable << std::endl;
    }

private:
    int memberVariable;
};

int main() {
    // const MyClass obj(10);
    // MyClass obj = 10;
    const MyClass* ptrObj = new MyClass(10);
    const MyClass& obj = *ptrObj;

    obj.printValue(); // OK: const member function
    int value = obj.getValue(); // OK: const member function

    // obj.setValue(20); // Error: cannot call non-const function on a const object

    return 0;
}
