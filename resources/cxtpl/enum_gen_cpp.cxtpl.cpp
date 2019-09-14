
              cxtpl_output
              += 
           R"raw(﻿)raw"
           ;
               // parameters begin

const auto GeneratedEnumName
  = GetWithDefault<std::string>(cxtpl_params, "GeneratedEnumName", "");

const auto generator_path
  = GetWithDefault<std::string>(cxtpl_params, "generator_path", "");

std::vector<std::string> generator_includes
  = GetWithDefault<std::vector<std::string>>
      (cxtpl_params, "generator_includes", std::vector<std::string>{});

// parameters end
/* no newline */ 

              cxtpl_output
              += 
           R"raw(// This is generated file. Do not modify directly.
// Path to the code generator: )raw"
           ;
              
              cxtpl_output
              +=  generator_path ;
              
              cxtpl_output
              += 
           R"raw(.

)raw"
           ;
               for(const auto& fileName: generator_includes) {

              cxtpl_output
              +=  fileName ;
              
              cxtpl_output
              += 
           R"raw(
)raw"
           ;
               } // end for
              cxtpl_output
              += 
           R"raw(
#include <iostream>
#include <cstring>
#include <type_traits>

namespace cxxctp {
namespace generated {

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated operator & (
  const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& rhs )
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated>(
    static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(lhs)
      & static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(rhs));
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated operator ^ (
  const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& rhs )
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated>(
    static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(lhs)
      ^ static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(rhs));
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated operator ~ (
  const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& rhs )
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated>(
    ~static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(rhs));
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated operator | (
  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& rhs )
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated>(
    static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(lhs)
      | static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(rhs));
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated operator &= (
  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& rhs )
{
  lhs
    = lhs & rhs;
  return lhs;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated operator ^= (
  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& rhs )
{
  lhs
    = lhs ^ rhs;
  return lhs;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated operator |= (
  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated& rhs )
{
  lhs
    = lhs | rhs;
  return lhs;
}

/*bool operator ==(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &b)
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(a)
          == static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(b);
}

bool operator !=(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &b)
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(a)
          != static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(b);
}

bool operator <(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &b)
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(a)
          < static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(b);
}

bool operator <=(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &b)
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(a)
          <= static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(b);
}

bool operator >(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &b)
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(a)
          > static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(b);
}

bool operator >=(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated &b)
{
  return static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(a)
          >= static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(b);
}*/

// Stream extraction operator: read from stream
std::istream& operator >> ( std::istream& ins, )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& val ) /*noexcept*/
{
  std::string str;
  ins >> str;
  val = )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::FromString( str.c_str() );
  if (val == )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::TOTAL)
    ins.setstate( ins.rdstate() | std::ios::failbit );
  return ins;
}

// Stream insertion operator: write to stream
std::ostream& operator << ( std::ostream& outs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& val ) /*noexcept*/
{
  const auto str = val.ToString();
  if(str) {
    return outs << str;
  }
  return outs;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::const_value_iterator )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::values_begin() const { return values_.begin(); }

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::const_value_iterator )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::values_end() const { return values_.end(); }

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::const_name_iterator )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::names_begin() const { return names_.begin(); }

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::const_name_iterator )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::names_end() const { return names_.end(); }

bool )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::test_flag()raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated flag) const noexcept {
  return static_cast<bool>(
        static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(value_)
        & static_cast<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t>(flag));
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw((const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated value)
  : value_(value) { }

const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::operator =(const char *dummy) noexcept {
  value_ = )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::FromString(dummy);
  return *this;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator & (
  const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& rhs )
{
  return lhs.value_
    & rhs.value_;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator ^ (
  const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& rhs )
{
  return lhs.value_
    ^ rhs.value_;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator ~ ( const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& rhs )
{
  return ~rhs.value_;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator | (
  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& rhs )
{
  return lhs.value_
    | rhs.value_;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator &= (
  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& rhs )
{
  lhs.value_
    &= rhs.value_;
  return lhs;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator ^= (
  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& rhs )
{
 lhs.value_
    ^= rhs.value_;
  return lhs;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator |= (
  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& lhs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& rhs )
{
  lhs.value_
    |= rhs.value_;
  return lhs;
}

/*bool operator ==(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &b)
{
  return a.value_ == b.value_;
}

bool operator !=(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &b)
{
  return a.value_ != b.value_;
}*/

bool operator <(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &b)
{
  return a.value_ < b.value_;
}

bool operator <=(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &b)
{
  return a.value_ <= b.value_;
}

bool operator >(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &b)
{
  return a.value_ > b.value_;
}

bool operator >=(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &a, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &b)
{
  return a.value_ >= b.value_;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::FromString(const char *txt) noexcept {
  for (size_t index = 0; index < _count; ++index) {
    if (names_[index] == txt)
      return static_cast<_enumerated>(values_[index]);
  }
  return _enumerated::TOTAL; // TODO: use optional
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::ToNumber(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated val) noexcept {
  return
      static_cast<_enumerated_t>(val);
}

const char *)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::ToString(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated val) noexcept {
  for (size_t index = 0; index < _count; ++index) {
    if (values_[index] == static_cast<_enumerated_t>(val))
      return names_[index];
  }
  return nullptr;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::FromNumber(const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t val) noexcept {
  auto val_to_type = static_cast<std::underlying_type_t<_enumerated>>(val);
  for (size_t index = 0; index < _count; ++index) {
    if (values_[index] == val_to_type)
      return static_cast<_enumerated>(values_[index]);
  }
  return _enumerated::TOTAL; // TODO: use optional
}

const char *)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::ToString() const noexcept {
  return ToString(value_);
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::ToNumber() const noexcept {
  return ToNumber(value_);
}

const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::operator =()raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::_enumerated_t dummy) noexcept {
  value_ = FromNumber(dummy);
  return *this;
}

const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( &)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::operator =()raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( dummy) noexcept {
  value_ = dummy.value_;
  return *this;
}

)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(::operator _enumerated() const { return value_; }

} // namespace cxxctp
} // namespace generated

// Support using as key in dictionaries and maps
size_t std::hash<cxxctp::generated::)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(>::operator()(
  const cxxctp::generated::)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& x) const
{
  return std::hash<size_t>()(
    static_cast<size_t>(x.ToNumber()));
}
)raw"
           ;
              