#include "generated/Spell.typeclass.generated.hpp"
#include "generated/FireSpell.typeclass_instance.generated.hpp"

#include <vector>

int main(int /*argc*/, const char* const* /*argv*/) {
    using namespace cxxctp::generated;

    // TODO: better example https://blog.rust-lang.org/2015/05/11/traits.html

    _tc_combined_t<Spell> myspell{FireSpell{"title1", "description1"}};

    myspell.set_spell_power(/*spellname*/ "spellname1", /*spellpower*/ 3);
    myspell.cast(/*spellname*/ "spellname1", /*spellpower*/ 3, /*target*/ "target1");

    _tc_combined_t<Spell> myspellcopy = myspell;

    //_tc_impl_t<FireSpell, Spell> someFireSpell{FireSpell{"title1", "description1"}};

    //_tc_combined_t<Spell> someFireSpellmove = std::move(someFireSpell);

    //FireSpell& data = myspell.ref_model()->ref_concrete<FireSpell>();
    //FireSpell a = data;

    /*_tc_impl_t<FireSpell, Spell> myFireSpell{FireSpell{"title1", "description1"}};
    _tc_combined_t<Spell> myFireSpellref = std::ref(myFireSpell);*/

    _tc_combined_t<Spell> someFireSpell{FireSpell{"someFireSpellTitle", "someFireSpelldescription1"}};

    std::vector<_tc_combined_t<Spell>> spells;
    spells.push_back(myspell);
    spells.push_back(someFireSpell);

    for(const _tc_combined_t<Spell>& it : spells) {
      it.cast("", 1, "");
    }

    return 0;
}
