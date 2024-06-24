
#include <exception>
#include <string>

class Error : public std::exception {
private:
    std::string message;
public:
    Error(const std::string& s) : message(s){};
    virtual ~Error() throw() {}
    const char* what() const throw() { return message.c_str();}
    // 4P
};

