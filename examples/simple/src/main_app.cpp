#if 0
#include "../../build/Spell.typeclass.generated.hpp"
#include "../../build/SpellBook.typeclass_instance.generated.hpp"
#endif

#include <vector>

#if 0
namespace cxxctp {
namespace generated {

template<>
void cast<Spell, SpellBook>
    (const SpellBook& data, const char* spellname, const int spellpower,
     const char* target) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(lib1) cast on " << target << " by " << data.title << " " << spellname
              << " with " << spellpower << std::endl;
}

template<>
void has_spell<Spell, SpellBook>(const SpellBook&, const char *spellname ) noexcept {
    // TODO
}

template<>
void add_spell<Spell, SpellBook>(const SpellBook&, const char *spellname ) noexcept {
    // TODO
}

template<>
void remove_spell<Spell, SpellBook>(const SpellBook&, const char *spellname ) noexcept {
    // TODO
}

template<>
void set_spell_power<Spell, SpellBook>
    (const SpellBook& data, const char *spellname, const int spellpower) noexcept {
    /// \note don`t use get_concrete<type> here, it may be get_concrete<ref_type>
    std::cout << "(lib1) set_spell_power by " << data.title << " " << spellname
              << " with " << spellpower << std::endl;
}

} // namespace cxxctp
} // namespace generated
#endif

int main(int /*argc*/, const char* const* /*argv*/) {
#if 0
    using namespace cxxctp::generated;

    // TODO: better example https://blog.rust-lang.org/2015/05/11/traits.html

    _tc_combined_t<Spell> myspell{SpellBook{"title1", "description1"}};

    myspell.set_spell_power(/*spellname*/ "spellname1", /*spellpower*/ 3);
    myspell.cast(/*spellname*/ "spellname1", /*spellpower*/ 3, /*target*/ "target1");

    _tc_combined_t<Spell> myspellcopy = myspell;

    _tc_impl_t<SpellBook, Spell> somespellbook{SpellBook{"title1", "description1"}};

    //_tc_combined_t<Spell> somespellbookmove = std::move(somespellbook);

    //SpellBook& data = myspell.ref_model()->ref_concrete<SpellBook>();
    //SpellBook a = data;

    /*_tc_impl_t<SpellBook, Spell> myspellbook{SpellBook{"title1", "description1"}};
    _tc_combined_t<Spell> myspellbookref = std::ref(myspellbook);*/
#endif

    return 0;
}
