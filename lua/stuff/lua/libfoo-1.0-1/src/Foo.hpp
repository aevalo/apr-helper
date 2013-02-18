#ifndef FOO_HPP_INCLUDED
#define FOO_HPP_INCLUDED

#include <iostream>
#include <sstream>

class Foo
{
  public:
    Foo(const std::string & name) : name(name)
    {
        std::cout << "Foo is born" << std::endl;
    }

    std::string Add(double a, double b)
    {
        std::stringstream ss;
        ss << name << ": " << a << " + " << b << " = " << (a+b);
        return ss.str();
    }

    ~Foo()
    {
        std::cout << "Foo is gone" << std::endl;
    }

  private:
    std::string name;
};

#endif // FOO_HPP_INCLUDED
