#include "someEnum.hpp"

#include <iostream>
#include <cstring>
#include <type_traits>

// see https://michael-thomas-greer.com/faq/enum/macro-trick/

// ==============

namespace cxxctp {
namespace generated {

ShapeKind::_enumerated operator & (
  const ShapeKind::_enumerated& lhs, const ShapeKind::_enumerated& rhs )
{
  return static_cast<ShapeKind::_enumerated>(
    static_cast<ShapeKind::_enumerated_t>(lhs)
      & static_cast<ShapeKind::_enumerated_t>(rhs));
}

ShapeKind::_enumerated operator ^ (
  const ShapeKind::_enumerated& lhs, const ShapeKind::_enumerated& rhs )
{
  return static_cast<ShapeKind::_enumerated>(
    static_cast<ShapeKind::_enumerated_t>(lhs)
      ^ static_cast<ShapeKind::_enumerated_t>(rhs));
}

ShapeKind::_enumerated operator ~ (
  const ShapeKind::_enumerated& rhs )
{
  return static_cast<ShapeKind::_enumerated>(
    ~static_cast<ShapeKind::_enumerated_t>(rhs));
}

ShapeKind::_enumerated operator | (
  ShapeKind::_enumerated& lhs, const ShapeKind::_enumerated& rhs )
{
  return static_cast<ShapeKind::_enumerated>(
    static_cast<ShapeKind::_enumerated_t>(lhs)
      | static_cast<ShapeKind::_enumerated_t>(rhs));
}

ShapeKind::_enumerated operator &= (
  ShapeKind::_enumerated& lhs, const ShapeKind::_enumerated& rhs )
{
  lhs
    = lhs & rhs;
  return lhs;
}

ShapeKind::_enumerated operator ^= (
  ShapeKind::_enumerated& lhs, const ShapeKind::_enumerated& rhs )
{
  lhs
    = lhs ^ rhs;
  return lhs;
}

ShapeKind::_enumerated operator |= (
  ShapeKind::_enumerated& lhs, const ShapeKind::_enumerated& rhs )
{
  lhs
    = lhs | rhs;
  return lhs;
}

/*bool operator ==(const ShapeKind::_enumerated &a, const ShapeKind::_enumerated &b)
{
  return static_cast<ShapeKind::_enumerated_t>(a)
          == static_cast<ShapeKind::_enumerated_t>(b);
}

bool operator !=(const ShapeKind::_enumerated &a, const ShapeKind::_enumerated &b)
{
  return static_cast<ShapeKind::_enumerated_t>(a)
          != static_cast<ShapeKind::_enumerated_t>(b);
}

bool operator <(const ShapeKind::_enumerated &a, const ShapeKind::_enumerated &b)
{
  return static_cast<ShapeKind::_enumerated_t>(a)
          < static_cast<ShapeKind::_enumerated_t>(b);
}

bool operator <=(const ShapeKind::_enumerated &a, const ShapeKind::_enumerated &b)
{
  return static_cast<ShapeKind::_enumerated_t>(a)
          <= static_cast<ShapeKind::_enumerated_t>(b);
}

bool operator >(const ShapeKind::_enumerated &a, const ShapeKind::_enumerated &b)
{
  return static_cast<ShapeKind::_enumerated_t>(a)
          > static_cast<ShapeKind::_enumerated_t>(b);
}

bool operator >=(const ShapeKind::_enumerated &a, const ShapeKind::_enumerated &b)
{
  return static_cast<ShapeKind::_enumerated_t>(a)
          >= static_cast<ShapeKind::_enumerated_t>(b);
}*/

// Stream extraction operator: read from stream
std::istream& operator >> ( std::istream& ins, ShapeKind& val ) /*noexcept*/
{
  std::string str;
  ins >> str;
  val = ShapeKind::FromString( str.c_str() );
  if (val == ShapeKind::TOTAL)
    ins.setstate( ins.rdstate() | std::ios::failbit );
  return ins;
}

// Stream insertion operator: write to stream
std::ostream& operator << ( std::ostream& outs, const ShapeKind& val ) /*noexcept*/
{
  const auto str = val.ToString();
  if(str) {
    return outs << str;
  }
  return outs;
}

ShapeKind::const_value_iterator ShapeKind::values_begin() const { return values_.begin(); }

ShapeKind::const_value_iterator ShapeKind::values_end() const { return values_.end(); }

ShapeKind::const_name_iterator ShapeKind::names_begin() const { return names_.begin(); }

ShapeKind::const_name_iterator ShapeKind::names_end() const { return names_.end(); }

bool ShapeKind::test_flag(ShapeKind::_enumerated flag) const noexcept {
  return static_cast<bool>(
        static_cast<ShapeKind::_enumerated_t>(value_)
        & static_cast<ShapeKind::_enumerated_t>(flag));
}

ShapeKind::ShapeKind(const ShapeKind::_enumerated value)
  : value_(value) { }

const ShapeKind &ShapeKind::operator =(const char *dummy) noexcept {
  value_ = ShapeKind::FromString(dummy);
  return *this;
}

ShapeKind operator & (
  const ShapeKind& lhs, const ShapeKind& rhs )
{
  return lhs.value_
    & rhs.value_;
}

ShapeKind operator ^ (
  const ShapeKind& lhs, const ShapeKind& rhs )
{
  return lhs.value_
    ^ rhs.value_;
}

ShapeKind operator ~ ( const ShapeKind& rhs )
{
  return ~rhs.value_;
}

ShapeKind operator | (
  ShapeKind& lhs, const ShapeKind& rhs )
{
  return lhs.value_
    | rhs.value_;
}

ShapeKind operator &= (
  ShapeKind& lhs, const ShapeKind& rhs )
{
  lhs.value_
    &= rhs.value_;
  return lhs;
}

ShapeKind operator ^= (
  ShapeKind& lhs, const ShapeKind& rhs )
{
 lhs.value_
    ^= rhs.value_;
  return lhs;
}

ShapeKind operator |= (
  ShapeKind& lhs, const ShapeKind& rhs )
{
  lhs.value_
    |= rhs.value_;
  return lhs;
}

/*bool operator ==(const ShapeKind &a, const ShapeKind &b)
{
  return a.value_ == b.value_;
}

bool operator !=(const ShapeKind &a, const ShapeKind &b)
{
  return a.value_ != b.value_;
}*/

bool operator <(const ShapeKind &a, const ShapeKind &b)
{
  return a.value_ < b.value_;
}

bool operator <=(const ShapeKind &a, const ShapeKind &b)
{
  return a.value_ <= b.value_;
}

bool operator >(const ShapeKind &a, const ShapeKind &b)
{
  return a.value_ > b.value_;
}

bool operator >=(const ShapeKind &a, const ShapeKind &b)
{
  return a.value_ >= b.value_;
}

ShapeKind::_enumerated ShapeKind::FromString(const char *txt) noexcept {
  for (size_t index = 0; index < _count; ++index) {
    if (names_[index] == txt)
      return static_cast<_enumerated>(values_[index]);
  }
  return _enumerated::TOTAL; // TODO: use optional
}

ShapeKind::_enumerated_t ShapeKind::ToNumber(const ShapeKind::_enumerated val) noexcept {
  return
      static_cast<_enumerated_t>(val);
}

const char *ShapeKind::ToString(const ShapeKind::_enumerated val) noexcept {
  for (size_t index = 0; index < _count; ++index) {
    if (values_[index] == static_cast<_enumerated_t>(val))
      return names_[index];
  }
  return nullptr;
}

ShapeKind::_enumerated ShapeKind::FromNumber(const ShapeKind::_enumerated_t val) noexcept {
  auto val_to_type = static_cast<std::underlying_type_t<_enumerated>>(val);
  for (size_t index = 0; index < _count; ++index) {
    if (values_[index] == val_to_type)
      return static_cast<_enumerated>(values_[index]);
  }
  return _enumerated::TOTAL; // TODO: use optional
}

const char *ShapeKind::ToString() const noexcept {
  return ToString(value_);
}

ShapeKind::_enumerated_t ShapeKind::ToNumber() const noexcept {
  return ToNumber(value_);
}

const ShapeKind &ShapeKind::operator =(ShapeKind::_enumerated_t dummy) noexcept {
  value_ = FromNumber(dummy);
  return *this;
}

const ShapeKind &ShapeKind::operator =(ShapeKind dummy) noexcept {
  value_ = dummy.value_;
  return *this;
}

ShapeKind::operator _enumerated() const { return value_; }

} // namespace cxxctp
} // namespace generated

// Support using as key in dictionaries and maps
size_t std::hash<cxxctp::generated::ShapeKind>::operator()(
  const cxxctp::generated::ShapeKind& x) const
{
  return std::hash<size_t>()(
    static_cast<size_t>(x.ToNumber()));
}
