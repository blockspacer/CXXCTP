#include "generated/Spell.typeclass.generated.hpp"

#include "generated/MagicItem.typeclass.generated.hpp"

#include "generated/Printable.typeclass.generated.hpp"

#include "generated/Spell_MagicItem.typeclass_combo.generated.hpp"

#include "generated/FireSpell_MagicItem.typeclass_instance.generated.hpp"

#include "generated/FireSpell_Spell.typeclass_instance.generated.hpp"

#include "generated/WaterSpell_MagicItem.typeclass_instance.generated.hpp"

#include "generated/WaterSpell_Spell.typeclass_instance.generated.hpp"

#include "generated/WaterSpell_Printable.typeclass_instance.generated.hpp"

#include "generated/FireSpell_Printable.typeclass_instance.generated.hpp"

#include "generated/MagicTemplated_std__string__int_.typeclass.generated.hpp"

#include "generated/WaterSpell_MagicTemplated_std__string__int_.typeclass_instance.generated.hpp"

#include "generated/FireSpell_MagicTemplated_std__string__int_.typeclass_instance.generated.hpp"

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

    std::vector<_tc_combined_t<MagicItem>> magicItems;
    magicItems.push_back(FireSpell{"FireSpelltitle1", "description1"});
    magicItems.push_back(WaterSpell{"WaterSpelltitle1", "description1"});

    for(const _tc_combined_t<MagicItem>& it : magicItems) {
      it.has_enough_mana("");
    }

    std::vector<_tc_combined_t<Spell, MagicItem>> spellMagicItems;
    {
      _tc_combined_t<Spell, MagicItem> pushed{};
      pushed = magicItems.at(0); // copy
      spellMagicItems.push_back(std::move(pushed));
    }
    {
      _tc_combined_t<Spell, MagicItem> pushed{};
      _tc_combined_t<Spell> someTmpSpell{
        FireSpell{"someTmpSpell", "someTmpSpell"}};
      pushed = std::move(someTmpSpell); // move
      spellMagicItems.push_back(std::move(pushed));
    }
    //spellMagicItems.push_back(someFireSpell.raw_model());
    //spellMagicItems.push_back(
    //  someFireSpell.ref_model()); // shared data
    //spellMagicItems.push_back(someFireSpell.clone_model());

    for(const _tc_combined_t<Spell, MagicItem>& it : spellMagicItems) {
      if(it.has_model<Spell>()) {
        it.cast("", 1, "");
      }
      if(it.has_model<MagicItem>()) {
        it.has_enough_mana("");
      }
    }

    /*_tc_combined_t<Spell, MagicItem> combined1 {
        _tc_combined_t<Spell>{FireSpell{"someFireSpellTitle", "someFireSpelldescription1"}}
    };*/

    _tc_combined_t<Spell, MagicItem> combined1 {
        FireSpell{"someFireSpellTitle", "someFireSpelldescription1"}
    };

    if(combined1.has_model<MagicItem>()) {
      combined1.has_enough_mana("");
    }

    //combined1 = WaterSpell{"WaterSpell", "WaterSpell"};

    if(combined1.has_model<MagicItem>()) {
      combined1.has_enough_mana("");
    }

    if(combined1.has_model<Spell>()) {
      combined1.add_spell("");
    }

    combined1 = magicItems.at(0);

    if(combined1.has_model<MagicItem>()) {
      combined1.has_enough_mana("");
    }

    if(combined1.has_model<Spell>()) {
      combined1.add_spell("");
    }

    /*combined1 = _tc_combined_t<Spell>{
      FireSpell{"someFireSpellTitle", "someFireSpelldescription1"}
    };*/

    _tc_combined_t<Spell, MagicItem> combined2 {
        FireSpell{"someFireSpellTitle", "someFireSpelldescription1"}
    };

    if(combined2.has_model<MagicItem>()) {
      combined1.has_enough_mana("");
    }

    if(combined2.has_model<Spell>()) {
      combined1.add_spell("");
    }

    std::vector<_tc_combined_t<Printable>> printables;
    printables.push_back(FireSpell{"someFireSpellTitle", "someFireSpelldescription1"});
    printables.push_back(WaterSpell{"WaterSpell", "WaterSpell"});

    for(const _tc_combined_t<Printable>& it : printables) {
      it.print();
    }

    std::vector<_tc_combined_t<MagicTemplated<std::string, int>>> tpls;
    tpls.push_back({
        WaterSpell{"WaterSpell", "WaterSpell"}
    });
    tpls.push_back({
        FireSpell{"FireSpell", "FireSpell"}
    });

    int idx = 0;
    for(const _tc_combined_t<MagicTemplated<std::string, int>>& it : tpls) {
      it.has_T("name1", idx++);
    }

    return 0;
}
