
#include <iostream>
#include "Point.cpp"

void test() {
    Point x(1);
    Point q(3);

    try {
        Point p = q;

        std::cout << x << std::endl;
        std::cout << q << std::endl;
        std::cout << p << std::endl;

        p[0] = 100.0; // cannot assign the value

        p[1] = 5.0;
        x[0] += p[0];

        std::cout << x << std::endl;
        std::cout << p << std::endl;
        std::cout << q << std::endl;

        Point p1(2), p2(2), q(3);
        // ...
        p1 = p2;  // OK
        q = p1;   // Error: Dimension mismatch
        p2 = q;   // Error: Dimension mismatch
    } catch (std::exception &e) {
        std::cout << e.what();
    }
}
