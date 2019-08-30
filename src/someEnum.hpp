#pragma once

//#include <iterator> // see https://vjordan.info/log/fpga/c-enum-range-based-for-loop.html
#include <array>

namespace cxxctp {
namespace generated {

// note supports non-continuous enum value range,
// unlike bitset approach https://softwareengineering.stackexchange.com/a/338472
// see https://www.codeproject.com/Articles/1002895/Clean-Reflective-Enums-Enum-to-String-with-Nice-Sy
/*$apply(
  reflect_enum(
    _enumerated,
    $DISABLE = ToString)
)*/
struct ShapeKind
  /*: public MetaProperty*/
  // TODO: https://www.fluentcpp.com/2018/05/08/std-iterator-deprecated/
  //: public std::iterator<std::forward_iterator_tag, /*TODO: _enumerated_t*/ int>
{
  //$attr(nogen=Sphere2, nogen=Sphere3)
  //using _enumerated_t = int;
  typedef int _enumerated_t;
  typedef _enumerated_t _value_t; // alias
  typedef const char* const _name_t;

  enum class _enumerated : _enumerated_t {
    NONE = 0,

    // Convex shapes, see ConvexBegin and ConvexEnd below.
    Box = 3,

    // TODO: annotate with different name, like "one" vs "1"
    Sphere = 6,

    Sphere2 = 7,

    Sphere3,

    // Non-convex shapes.
    //Donut = 2,
    //Banana = 3,

    TOTAL = Sphere3 + 1,

    // TODO: Non-reflected aliases.
    //ConvexBegin = Box,
    //ConvexEnd = Sphere + 1,

    // TODO: generate TOTAL
  };

  // allows to hide some enum values
  static constexpr auto NONE     = _enumerated::NONE;
  static constexpr auto Box     = _enumerated::Box;
  static constexpr auto Sphere  = _enumerated::Sphere;
  static constexpr auto TOTAL  = _enumerated::TOTAL;

  _enumerated value_;

  static constexpr size_t _count = 3; // IDENTITY(COUNT(__VA_ARGS__));

  using value_container =
    std::array<_enumerated_t, _count>;
  using value_iterator =
    typename value_container::iterator;//_enumerated_t*;
  using const_value_iterator =
    typename value_container::const_iterator;//_enumerated_t const*;

  /*iterator begin() { return values_.data(); }
  iterator end() { return values_.data() + values_.size(); }
  const_iterator begin() const { return values_.data(); }
  const_iterator end() const { return values_.data() + values_.size(); }*/

  /*iterator begin() { return values_.begin(); }
  iterator end() { return values_.end(); }*/

  const_value_iterator values_begin() const;
  const_value_iterator values_end() const;

  using name_container =
    std::array<_name_t, _count>;
  using name_iterator =
    typename name_container::iterator;
  using const_name_iterator =
    typename name_container::const_iterator;

  const_name_iterator names_begin() const;
  const_name_iterator names_end() const;

  friend std::ostream& operator << ( std::ostream& outs, const ShapeKind& val ); /*noexcept*/
  friend std::istream& operator >> ( std::istream& ins, ShapeKind& val ); /*noexcept*/

  /* TODO: generate bitwise masks https://stackoverflow.com/a/18841220:
   *
   * NONE                = 0,
   * 1<<0
   * 1<<1
   * 1<<2
   * ...
   */
  friend ShapeKind operator & (
    const ShapeKind& lhs, const ShapeKind& rhs ); /*noexcept*/
  friend ShapeKind operator ^ (
    const ShapeKind& lhs, const ShapeKind& rhs ); /*noexcept*/
  friend ShapeKind operator ~ (
    const ShapeKind& rhs ); /*noexcept*/
  friend ShapeKind operator | (
    const ShapeKind& lhs, const ShapeKind& rhs ); /*noexcept*/
  friend ShapeKind operator &= (
    ShapeKind& lhs, const ShapeKind& rhs ); /*noexcept*/
  friend ShapeKind operator ^= (
    ShapeKind& lhs, const ShapeKind& rhs ); /*noexcept*/
  friend ShapeKind operator |= (
    ShapeKind& lhs, const ShapeKind& rhs ); /*noexcept*/

  /*friend bool operator ==(const ShapeKind &a, const ShapeKind &b);
  friend bool operator !=(const ShapeKind &a, const ShapeKind &b);*/
  friend bool operator <(const ShapeKind &a, const ShapeKind &b);
  friend bool operator <=(const ShapeKind &a, const ShapeKind &b);
  friend bool operator >(const ShapeKind &a, const ShapeKind &b);
  friend bool operator >=(const ShapeKind &a, const ShapeKind &b);

  friend _enumerated operator & (
    const _enumerated& lhs, const _enumerated& rhs ); /*noexcept*/
  friend _enumerated operator ^ (
    const _enumerated& lhs, const _enumerated& rhs ); /*noexcept*/
  friend _enumerated operator ~ (
    const _enumerated& rhs ); /*noexcept*/
  friend _enumerated operator | (
    const _enumerated& lhs, const _enumerated& rhs ); /*noexcept*/
  friend _enumerated operator &= (
    _enumerated& lhs, const _enumerated& rhs ); /*noexcept*/
  friend _enumerated operator ^= (
    _enumerated& lhs, const _enumerated& rhs ); /*noexcept*/
  friend _enumerated operator |= (
    _enumerated& lhs, const _enumerated& rhs ); /*noexcept*/

  /*friend bool operator ==(const _enumerated &a, const _enumerated &b);
  friend bool operator !=(const _enumerated &a, const _enumerated &b);
  friend bool operator <(const _enumerated &a, const _enumerated &b);
  friend bool operator <=(const _enumerated &a, const _enumerated &b);
  friend bool operator >(const _enumerated &a, const _enumerated &b);
  friend bool operator >=(const _enumerated &a, const _enumerated &b);*/

  // There's no reason to overload operator!, we can use bool()
  /*operator bool() const noexcept {
    return value_ != _enumerated::NONE;
  }*/

  // TODO: disable operator== and operator!= for bitmasks
  // https://dalzhim.github.io/2017/08/11/Improving-the-enum-class-bitmask/

  bool test_flag ( _enumerated flag ) const noexcept;

  //ShapeKind() : value_(_enumerated::TOTAL) { }

  ShapeKind(const _enumerated value = _enumerated::TOTAL);

  /*explicit ShapeKind(_enumerated value) : value_(value) { }

  explicit ShapeKind(_enumerated_t value) : value_(FromNumber(value)) { }*/

  operator _enumerated() const;

  ~ShapeKind() {}

  /*operator int()
  {
    return m_state;
  }*/

  const ShapeKind& operator =(ShapeKind /*todo: support NOT only int*/ dummy) /*override*/ noexcept;

  const ShapeKind& operator =(_enumerated_t /*todo: support NOT only int*/ dummy) /*override*/ noexcept;

  const ShapeKind& operator =(const char* dummy) noexcept;

  /*class Box : public EnumValue {
    const char* ToString() {
      return "Box";
    }
    operator int()
    {
      return 0;
    }
  };

  class Sphere : public EnumValue {
    const char* ToString() {
      return "Box";
    }
    operator int()
    {
      return 1;
    }
  };*/

  // TODO: more operators
  // operator>>
  // https://github.com/shaovoon/EnumConvGen/blob/master/ParseEnum/ParseEnum/EnumStrConv.cpp#L192

  // fromNumber

  // GetNames

  // is the given integer value a valid enumeration member?
  // IsValid(int inProbableEnum);

  // is the given String value a valid enumeration member?
  // IsValid(String inProbableEnum);

  static _enumerated FromString(const char* txt) noexcept;

  static _enumerated_t ToNumber(const _enumerated val) noexcept;

  static const char* ToString(const _enumerated val) /*override*/ noexcept;

  static _enumerated FromNumber(const _enumerated_t val) noexcept;

  const char* ToString() const /*override*/ noexcept;

  _enumerated_t ToNumber() const noexcept;

  /// \note for large number of elements
  /// consider <map> containing string hashes
  static constexpr std::array<_enumerated_t, _count> values_
      {
        3, // Box
        6, // Sphere
        7  // TOTAL
      };
      //{ IDENTITY(IGNORE_ASSIGN(__VA_ARGS__)) };

  static constexpr std::array<_name_t, _count> names_ =
      //{ IDENTITY(STRINGIZE(__VA_ARGS__)) };
      {
        "Box",
        "Circle",
        "TOTAL"
      };

  /*static char*                processed_names[_count];
  static bool                 initialized = false;

  if (!initialized) {
      for (size_t index = 0; index < _count; ++index) {
          size_t length =
              std::strcspn(raw_names[index], " =\t\n\r");

          processed_names[index] = new char[length + 1];

          std::strncpy(
              processed_names[index], raw_names[index], length);
          processed_names[index][length] = '\0';
      }
  }*/
};

} // namespace cxxctp
} // namespace generated

// Support using as key in dictionaries and maps
namespace std {
    template <>
    struct hash<cxxctp::generated::ShapeKind> {
        size_t operator()(const cxxctp::generated::ShapeKind& ) const;
    };
}
