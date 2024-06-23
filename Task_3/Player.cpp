//
// Created by anton on 6/22/2024.
//


#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class Player {
private:
    std::string name;
    int points;
    int time;

public:
    Player(std::string name, int p, int t) : name(name), points(p), time(t) {
    }

    int getPoints() const { return points; }
    int getTime() const { return time; }

    std::string toString() const {
        std::stringstream buffer;
        buffer << "Name: " << name << ", Points: " << points << ", Time:" << time;
        return buffer.str();
    }

    bool operator>(const Player &other) const {
        return this->points > other.points;
    }

    bool operator<(const Player &other) const {
        return this->points < other.points;
    }
};

std::ostream &operator<<(std::ostream &os, const Player &player) {
    return os << player.toString();
}

struct CompareScore {
    // Default constructor:
    // CompareScore() = default;

    static int score(const Player &p) {
        return 2 * p.getPoints() / p.getTime();
    }

    // Overloaded () operator:
    bool operator()(const Player &p1, const Player &p2) const {
        // It is not a constructor, but it is a operator().
        // It is called when you create an object of this class,
        // and use it as a function.
        return score(p1) > score(p2);
    }
};

template<class InIter, class OutIter, class UnOp> // 3 types, because InIter and OutIter are iterators:
                                                    // std::vector<Player>::iterator Iter
OutIter my_copy_if( // 4 arguments
    InIter first,
    InIter last,
    OutIter dest,
    UnOp op
) {
    for (InIter i = first; i != last; ++i) {
        if (op(*i)) {
            *dest++ = *i;
        }
    }
    return dest; // todo Why should be return dest? It is better to return void, having a dest as reference.
}


template<class Operation, class T>
class Compare // public std::unary_function<T, bool>
{
public:
    Compare(const Operation &o, const T &t) : op(o), y(t) {}
    bool operator()(const T &x) const { return op(x, y); }
private:
    const Operation op;
    const T y;
};

void testCompareScore() {
    Player player1("Red", 10, 15);
    Player player2("Purple", 20, 25);

    CompareScore compareScore;

    bool result = compareScore(player1, player2);
    std::cout << "result = " << result << std::endl;
}


void testTask3() {
    std::vector<Player> scorelist;
    std::vector<Player> top;
    Player *Red = new Player("Red", 10, 15);
    Player *Purple = new Player("Purple", 20, 25);
    Player *Blue = new Player("Blue", 30, 25);
    Player *Yellow = new Player("Yellow", 40, 40);
    scorelist.push_back(*Red);
    scorelist.push_back(*Purple);
    scorelist.push_back(*Blue);
    scorelist.push_back(*Yellow);
    typedef std::vector<Player>::iterator Iter;
    std::ostream_iterator<Player> Output(std::cout, "\n");
    Iter start = scorelist.begin();
    Iter end = scorelist.end();
    Iter max = std::max_element(start, end, CompareScore()); // TODO
    std::cout << (*max) << std::endl;
    my_copy_if( // todo 4 arguments
        start,
        end,
        std::back_inserter(top),
        Compare<std::greater<Player>, Player &>(std::greater<Player>(), *Purple)
    );
    copy(start, end, Output);
    copy(top.begin(), top.end(), Output);
}

// int main() {
//     // testCompareScore(); // todo uncomment to test functional object CompareScore
//     testTask3(); // todo uncomment to testTask3 Baer's code
//     return 0;
// }
