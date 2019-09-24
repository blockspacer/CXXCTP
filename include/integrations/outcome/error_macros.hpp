#pragma once

#include <string>
#include <system_error>

#define OUTCOME_USE_STD_IN_PLACE_TYPE 1

#define __OUTCOME_DEFINE_MAKE_ERROR_CODE(Enum)                     \
  extern std::error_code make_error_code(Enum e) {                 \
    return {static_cast<int>(e), error_utils::Category<Enum>::get()}; \
  }

#define __OUTCOME_DECLARE_MAKE_ERROR_CODE(Enum) \
  std::error_code make_error_code(Enum e);

/// MUST BE EXECUTED A FILE LEVEL (no namespace) in HPP
// ns - fully qualified enum namespace.
// Enum - enum name. Example: EncodeError
#define OUTCOME_HPP_DECLARE_ERROR_2(ns, Enum) \
  namespace ns {                              \
    __OUTCOME_DECLARE_MAKE_ERROR_CODE(Enum)   \
  }                                           \
                                              \
  template <>                                 \
  struct std::is_error_code_enum<ns::Enum> : std::true_type {};

/// MUST BE EXECUTED A FILE LEVEL (global namespace) in HPP
// Enum - enum name. Example: EncodeError
#define OUTCOME_HPP_DECLARE_ERROR_1(Enum) \
  __OUTCOME_DECLARE_MAKE_ERROR_CODE(Enum) \
  template <>                             \
  struct std::is_error_code_enum<Enum> : std::true_type {};

/// MUST BE EXECUTED AT FILE LEVEL(no namespace) IN CPP
// ns - fully qualified enum namespace.
// Enum - enum name. Example: EncodeError
// Name - variable name. Example: e
#define OUTCOME_CPP_DEFINE_CATEGORY_3(ns, Enum, Name) \
  namespace ns {                                      \
    __OUTCOME_DEFINE_MAKE_ERROR_CODE(Enum)            \
  };                                                  \
  template <>                                         \
  std::string error_utils::Category<ns::Enum>::toString(ns::Enum Name)

/// MUST BE EXECUTED AT FILE LEVEL(global namespace) IN CPP
// Enum - enum name. Example: EncodeError
// Name - variable name. Example: e
#define OUTCOME_CPP_DEFINE_CATEGORY_2(Enum, Name) \
  __OUTCOME_DEFINE_MAKE_ERROR_CODE(Enum)          \
  template <>                                     \
  std::string error_utils::Category<Enum>::toString(Enum Name)

// kind of "macro overloading"
#define __GET_MACRO_3(_1, _2, _3, NAME, ...) NAME
#define __GET_MACRO_2(_1, _2, NAME, ...) NAME

#define __FIRST_ARG(NAME, ...) NAME
#define FIRST_ARG(args) __FIRST_ARG args

#define __SECOND_ARG(_1, NAME, ...) NAME
#define SECOND_ARG(args) __SECOND_ARG args

#define __TWO_ARGS(_1, _2, ...) _1#_2
#define TWO_ARGS(args) __TWO_ARGS args

/// with 3 args: OUTCOME_CPP_DEFINE_CATEGORY_3
/// with 2 args: OUTCOME_CPP_DEFINE_CATEGORY_2
#define OUTCOME_CPP_DEFINE_CATEGORY(...)                    \
  __GET_MACRO_3(__VA_ARGS__, OUTCOME_CPP_DEFINE_CATEGORY_3, \
                OUTCOME_CPP_DEFINE_CATEGORY_2)              \
  (__VA_ARGS__)

#define OUTCOME_HPP_DECLARE_ERROR_EXTRA_INFO(namespacename, extrainfoname)                    \
  namespace namespacename { \
    inline const std::error_code make_error_code(const extrainfoname &fi) { \
      return fi.ec; \
    } \
    inline void outcome_throw_as_system_error_with_payload(extrainfoname fi) \
    { \
      outcome::try_throw_std_exception_from_error(fi.ec); \
      std::terminate(); \
    } \
  }

#define OUTCOME_HPP_DECLARE_CATEGORY_NAME(categorytype, categoryname)                    \
  namespace error_utils { \
    template <> \
    struct CategoryName< categorytype > { \
      static const char *name() noexcept { \
        return ""#categoryname; \
      } \
    }; \
  }

#define OUTCOME_HPP_DECLARE_CATEGORY(categoryname)                    \
  OUTCOME_HPP_DECLARE_CATEGORY_NAME(categoryname, #categoryname)

/// with 2 args: OUTCOME_CPP_DEFINE_CATEGORY_2
/// with 1 arg : OUTCOME_CPP_DEFINE_CATEGORY_1
#define OUTCOME_HPP_DECLARE_ERROR(...)                    \
  __GET_MACRO_2(__VA_ARGS__, OUTCOME_HPP_DECLARE_ERROR_2, \
                OUTCOME_HPP_DECLARE_ERROR_1)              \
  (__VA_ARGS__)
