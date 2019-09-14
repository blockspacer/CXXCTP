
              cxtpl_output
              += 
           R"raw(﻿)raw"
           ;
               // parameters begin

const auto headerGuard
  = GetWithDefault<std::string>(cxtpl_params, "headerGuard", "");

const auto GeneratedEnumName
  = GetWithDefault<std::string>(cxtpl_params, "GeneratedEnumName", "");

const auto generator_path
  = GetWithDefault<std::string>(cxtpl_params, "generator_path", "");

const auto GeneratedEnumType
  = GetWithDefault<std::string>(cxtpl_params, "GeneratedEnumType", "");

const auto GeneratedEnumItems
  = GetWithDefault<std::unordered_map<std::string, std::string>>(cxtpl_params, "GeneratedEnumItems", std::unordered_map<std::string, std::string>{});

const size_t GeneratedEnumItemsSize = GeneratedEnumItems.size();
if(!GeneratedEnumItemsSize) {
  // TODO: report error
}

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
              
              cxtpl_output
              +=  startHeaderGuard(headerGuard) /* no newline */ ;
              

              cxtpl_output
              += 
           R"raw(
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
#include <array>
#include <functional>

namespace cxxctp {
namespace generated {

struct )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(
{
  typedef )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumType ;
              
              cxtpl_output
              += 
           R"raw( _enumerated_t;
  typedef _enumerated_t _value_t; // alias
  typedef const char* const _name_t;

  enum class _enumerated : _enumerated_t {
)raw"
           ;
                { // startscope
    size_t elemIter = 0;
    for(const auto& [name, value]: GeneratedEnumItems) {
      const std::string delim  =
        (elemIter != GeneratedEnumItemsSize) ? "," : "";
      const std::string comment  =
        name + " = " + value + " at " + std::to_string(elemIter);
              cxtpl_output
              += 
           R"raw(    )raw"
           ;
              
              cxtpl_output
              += name;
              
              cxtpl_output
              += 
           R"raw( = )raw"
           ;
              
              cxtpl_output
              += value;
              
              cxtpl_output
              += 
           R"raw( )raw"
           ;
              
              cxtpl_output
              += delim;
              
              cxtpl_output
              += 
           R"raw( // )raw"
           ;
              
              cxtpl_output
              += comment;
              
              cxtpl_output
              += 
           R"raw(
)raw"
           ;
                    elemIter++;
    } // endfor
  } // endscope
              cxtpl_output
              += 
           R"raw(  };

  // allows to hide some enum values
  static constexpr auto NONE     = _enumerated::NONE;
  static constexpr auto Box     = _enumerated::Box;
  static constexpr auto Sphere  = _enumerated::Sphere;
  static constexpr auto TOTAL  = _enumerated::TOTAL;

  _enumerated value_;

  static constexpr size_t _count = )raw"
           ;
              
              cxtpl_output
              += 
           std::to_string(  GeneratedEnumItemsSize  )
           ;
              
              cxtpl_output
              += 
           R"raw(;

  using value_container =
    std::array<_enumerated_t, _count>;
  using value_iterator =
    typename value_container::iterator;
  using const_value_iterator =
    typename value_container::const_iterator;

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

  friend std::ostream& operator << ( std::ostream& outs, const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& val ); /*noexcept*/
  friend std::istream& operator >> ( std::istream& ins, )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& val ); /*noexcept*/

  friend )raw"
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
           R"raw(& rhs ); /*noexcept*/
  friend )raw"
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
           R"raw(& rhs ); /*noexcept*/
  friend )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator ~ (
    const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& rhs ); /*noexcept*/
  friend )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( operator | (
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
           R"raw(& rhs ); /*noexcept*/
  friend )raw"
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
           R"raw(& rhs ); /*noexcept*/
  friend )raw"
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
           R"raw(& rhs ); /*noexcept*/
  friend )raw"
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
           R"raw(& rhs ); /*noexcept*/

  friend bool operator <(const )raw"
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
           R"raw( &b);
  friend bool operator <=(const )raw"
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
           R"raw( &b);
  friend bool operator >(const )raw"
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
           R"raw( &b);
  friend bool operator >=(const )raw"
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
           R"raw( &b);

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

  bool test_flag ( _enumerated flag ) const noexcept;

  )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw((const _enumerated value = _enumerated::TOTAL);

  operator _enumerated() const;

  ~)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(() {}

  const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& operator =()raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw( /*todo: support NOT only int*/ dummy) /*override*/ noexcept;

  const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& operator =(_enumerated_t /*todo: support NOT only int*/ dummy) /*override*/ noexcept;

  const )raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& operator =(const char* dummy) noexcept;

  static _enumerated FromString(const char* txt) noexcept;

  static _enumerated_t ToNumber(const _enumerated val) noexcept;

  static const char* ToString(const _enumerated val) /*override*/ noexcept;

  static _enumerated FromNumber(const _enumerated_t val) noexcept;

  const char* ToString() const /*override*/ noexcept;

  _enumerated_t ToNumber() const noexcept;

  /// \note for large number of elements
  /// consider <map> containing string hashes
  static constexpr std::array<_enumerated_t, _count> values_ =
      {
)raw"
           ;
                { // startscope
    size_t elemIter = 0;
    for(const auto& [name, value]: GeneratedEnumItems) {
      const std::string delim  =
        (elemIter != GeneratedEnumItemsSize) ? "," : "";
              cxtpl_output
              += 
           R"raw(        )raw"
           ;
              
              cxtpl_output
              += value;
              
              cxtpl_output
              += 
           R"raw( )raw"
           ;
              
              cxtpl_output
              += delim;
              
              cxtpl_output
              += 
           R"raw( // )raw"
           ;
              
              cxtpl_output
              += name;
              
              cxtpl_output
              += 
           R"raw(
)raw"
           ;
                    elemIter++;
    } // endfor
  } // endscope
              cxtpl_output
              += 
           R"raw(      };

  static constexpr std::array<_name_t, _count> names_ =
      {
)raw"
           ;
                { // startscope
    size_t elemIter = 0;
    for(const auto& [name, value]: GeneratedEnumItems) {
      const std::string delim  =
        (elemIter != GeneratedEnumItemsSize) ? "," : "";
              cxtpl_output
              += 
           R"raw(        ")raw"
           ;
              
              cxtpl_output
              += name;
              
              cxtpl_output
              += 
           R"raw(" )raw"
           ;
              
              cxtpl_output
              += delim;
              
              cxtpl_output
              += 
           R"raw( // )raw"
           ;
              
              cxtpl_output
              += value;
              
              cxtpl_output
              += 
           R"raw(
)raw"
           ;
                    elemIter++;
    } // endfor
  } // endscope
              cxtpl_output
              += 
           R"raw(      };
};

} // namespace cxxctp
} // namespace generated

// Support using as key in dictionaries and maps
namespace std {
    template <>
    struct hash<cxxctp::generated::)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(> {
        size_t operator()(const cxxctp::generated::)raw"
           ;
              
              cxtpl_output
              +=  GeneratedEnumName ;
              
              cxtpl_output
              += 
           R"raw(& ) const;
    };
}

)raw"
           ;
              
              cxtpl_output
              +=  endHeaderGuard(headerGuard) /* no newline */ ;
              

