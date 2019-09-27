#include "generated/Printable.typeclass.generated.hpp"
#include "generated/WaterSpell_Printable.typeclass_instance.generated.hpp"
#include <vector>

namespace cxxctp {
namespace generated {

template<>
void print<Printable, WaterSpell>
    (const WaterSpell& data) noexcept {
    std::cout << "(lib1) print for WaterSpell "
      << data.title << " " << data.description << std::endl;
}

} // namespace cxxctp
} // namespace generated
