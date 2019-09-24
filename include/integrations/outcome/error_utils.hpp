#pragma once

#include "error_macros.hpp"
#include "outcome.hpp"

namespace outcome = OUTCOME_V2_NAMESPACE;

namespace error_utils {

  template <typename T>
  struct CategoryName {};

  template <typename T>
  class Category : public std::error_category {
   public:
    const char *name() const noexcept final {
      return CategoryName<T>::name();  // enum Errc -> 4Errc
    }

    std::string message(int c) const final {
      return toString(static_cast<T>(c));
    }

    static std::string toString(T t) {
      static_assert(
          !std::is_same<T, T>::value,
          "toString<T>() was not specialised for the type T supplied");
      return "";
    }

    static const Category<T> &get() {
      static const Category<T> c;
      return c;
    }

   private:
    Category() = default;
    Category(const Category &) = delete;
    Category(Category &&) = delete;
  }; /* end of class */

}  // namespace error_utils

