#include "generated/Spell.typeclass.generated.hpp"
#include "generated/FireSpell_MagicItem.typeclass_instance.generated.hpp"

#include <vector>

namespace cxxctp {
namespace generated {

template<>
void has_enough_mana<MagicItem, FireSpell>
    (const FireSpell& data, const char* spellname) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(lib1) has_enough_mana " << " by "
      << data.title << " " << spellname << std::endl;
}

} // namespace cxxctp
} // namespace generated
