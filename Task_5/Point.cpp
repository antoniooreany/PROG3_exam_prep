#include <sstream>

#include "Error.cpp"

class Point {
private:
    double *compontents;
    int len;

public:
    Point(int lenght) : len(lenght) {
        compontents = new double[len];
    }

    Point(const Point &other) {
        len = other.len;
        compontents = new double[len];
        for (int i = 0; i < len; i++) {
            compontents[i] = other.compontents[i];
        }
    }

    virtual ~Point() {
        if (compontents) {
            delete[] compontents;
        }
    }

    Point &operator=(const Point &other) {
        if (this == &other) {
            return *this;
        }
        if (other.len > this->len) {
            throw Error("Dimension mismatch");
        } else {
            for (int i = 0; i < other.len; ++i) {
                compontents[i] = other.compontents[i];
            }
        }
        return *this;
    }

    double operator[](int dim) const {
        if (dim < 0 || dim >= len) {
            throw Error("Out of dimension");
        }
        return compontents[dim];
    }

    std::string toString() const {
        std::stringstream buffer;
        buffer << "(";
        for (int i = 0; i < len; ++i) {
            buffer << compontents[i] << " ";
        }
        buffer << ")";
        return buffer.str();
    }
};

std::ostream &operator<<(std::ostream &os, const Point &point) {
    return os << point.toString();
}
