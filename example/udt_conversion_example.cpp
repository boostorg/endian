//  udt_conversion_example.cpp  --------------------------------------------------------//

//  Copyright Beman Dawes 2013

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

//--------------------------------------------------------------------------------------//

#define _CRT_SECURE_NO_WARNINGS

#include <boost/endian/detail/disable_warnings.hpp>

#include <boost/endian/conversion.hpp>
#include <iostream>
#include <cstring>

using namespace boost::endian;
using std::cout;
using std::endl;
using boost::int32_t;

class UDT
{
public:
  UDT() : id_(0), value_(0.0) {desc_[0] = '\0';}
  UDT(int32_t id, float value, const char* desc) : id_(id), value_(value)
  {
    std::strncpy(desc_, desc, sizeof(desc_)-1);
    desc_[sizeof(desc_)-1] = '\0';
  }
  int32_t     id() const          {return id_;}
  float       value() const       {return value_;}
  const char* desc() const        {return desc_;}
  void        id(int32_t x)       {id_ = x;}
  void        value(float v)      {value_ = v;}
  void        desc(const char* s)
  {
    std::strncpy(desc_, s, sizeof(desc_)-1);
    desc_[sizeof(desc_-1)] = '\0';
  }

  friend void reverse(UDT&);

private:
  int32_t id_;
  float   value_;
  char    desc_[56];  // '/0'
};

void reverse(UDT& x)
{
  reverse(x.id_);
  reverse(x.value_);
}

int main(int, char* [])
{
  UDT x(1, 1.2345f, "Bingo!");
  cout << std::hex;
  cout << x.id() << ' ' << x.value() << ' ' << x.desc() << endl;

  reverse(x);
  cout << x.id() << ' ' << x.value() << ' ' << x.desc() << endl;

  reverse(x);
  cout << x.id() << ' ' << x.value() << ' ' << x.desc() << endl;

  big_endian(x);
  cout << x.id() << ' ' << x.value() << ' ' << x.desc() << endl;

  little_endian(x);
  cout << x.id() << ' ' << x.value() << ' ' << x.desc() << endl;

  convert<order::little, order::big>(x);
  cout << x.id() << ' ' << x.value() << ' ' << x.desc() << endl;

  convert(x, order::big, order::little);
  cout << x.id() << ' ' << x.value() << ' ' << x.desc() << endl;
}

#include <boost/endian/detail/disable_warnings_pop.hpp>
