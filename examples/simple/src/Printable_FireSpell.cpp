#include "generated/Printable.typeclass.generated.hpp"
#include "generated/FireSpell_Printable.typeclass_instance.generated.hpp"

#include <vector>

namespace cxxctp {
namespace generated {

template<>
void print<Printable, FireSpell>
    (const FireSpell& data) noexcept {
    std::cout << "(lib1) print for FireSpell "
      << data.title << " " << data.description << std::endl;
}

} // namespace cxxctp
} // namespace generated
