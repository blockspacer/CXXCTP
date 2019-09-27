#include "generated/Spell.typeclass.generated.hpp"
#include "generated/FireSpell_Spell.typeclass_instance.generated.hpp"

#include <vector>

namespace cxxctp {
namespace generated {

template<>
void cast<Spell, FireSpell>
    (const FireSpell& data, const char* spellname, const int spellpower,
     const char* target) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(lib1) cast on " << target << " by " << data.title << " " << spellname
              << " with " << spellpower << std::endl;
}

template<>
void has_spell<Spell, FireSpell>(const FireSpell& data, const char *spellname ) noexcept {
    std::cout << "(lib1) has_spell by " << data.title << " " << spellname
              << " with " << spellname << std::endl;
}

template<>
void add_spell<Spell, FireSpell>(const FireSpell& data, const char *spellname ) noexcept {
    std::cout << "(lib1) add_spell by " << data.title << " " << spellname
              << " with " << spellname << std::endl;
}

template<>
void remove_spell<Spell, FireSpell>(const FireSpell& data, const char *spellname ) noexcept {
    std::cout << "(lib1) remove_spell by " << data.title << " " << spellname
              << " with " << spellname << std::endl;
}

template<>
void set_spell_power<Spell, FireSpell>
    (const FireSpell& data, const char *spellname, const int spellpower) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(lib1) set_spell_power by " << data.title << " " << spellname
              << " with " << spellpower << std::endl;
}

} // namespace cxxctp
} // namespace generated
