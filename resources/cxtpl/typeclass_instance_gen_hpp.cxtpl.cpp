
              cxtpl_output
              += 
           R"raw(﻿)raw"
           ;
               // parameters begin

const auto headerGuard
  = GetWithDefault<std::string>(cxtpl_params, "headerGuard", "");

const auto generator_path
  = GetWithDefault<std::string>(cxtpl_params, "generator_path", "");

std::vector<std::string> generator_includes
  = GetWithDefault<std::vector<std::string>>
      (cxtpl_params, "generator_includes", std::vector<std::string>{});

reflection::ClassInfoPtr ReflectedBaseTypeclass
  = GetWithDefault<reflection::ClassInfoPtr>
      (cxtpl_params, "ReflectedBaseTypeclass", nullptr);

std::string ImplTypeclassName
  = GetWithDefault<std::string>
      (cxtpl_params, "ImplTypeclassName", "");

std::string BaseTypeclassName
  = GetWithDefault<std::string>
      (cxtpl_params, "BaseTypeclassName", "");

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
#include <memory>

namespace cxxctp {
namespace generated {

)raw"
           ;
                { // startscope
    for(const auto& method: ReflectedBaseTypeclass->methods) {
      const size_t methodParamsSize = method->params.size();
      const bool needPrint = !method->isImplicit
          && !method->isOperator
          && !method->isCtor
          && !method->isDtor;
      if(needPrint) {
              cxtpl_output
              += 
           R"raw(  template<>
)raw"
           ;
              
              cxtpl_output
              +=  method->isExplicitCtor ? "explicit " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->isConstexpr ? "constexpr " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->isStatic ? "static " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->returnType->getPrintedName() ;
              
 /* no newline */

              cxtpl_output
              +=  " " ;
              
 /* no newline */

              cxtpl_output
              +=  method->name ;
              
 /* no newline */
              cxtpl_output
              += 
           R"raw(< )raw"
           ;
              
              cxtpl_output
              +=  BaseTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(, )raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw( >
(const )raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(& data)raw"
           ;
               /* no newline */
 if(methodParamsSize) {

              cxtpl_output
              +=    ", " ;
              
 /* no newline */

              cxtpl_output
              +=  paramsFullDecls(method->params) ;
              
 /* no newline */
 } // methodParamsSize
              cxtpl_output
              += 
           R"raw() )raw"
           ;
               /* no newline */

              cxtpl_output
              +=  method->isNoExcept ? "noexcept " : "" ;
              
 /* no newline */
              cxtpl_output
              += 
           R"raw(;
)raw"
           ;
               /* newline */ 
              cxtpl_output
              += 
           R"raw(
)raw"
           ;
                    } // needPrint
    } // methods endfor
  } // endscope
              cxtpl_output
              += 
           R"raw(
/*template <>
)raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(& _tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  BaseTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>::ref_concrete<)raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>() noexcept;
*/

template<>
struct _tc_impl_t<)raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(, )raw"
           ;
              
              cxtpl_output
              +=  BaseTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>
    : public _tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  BaseTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(> {
    typedef )raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw( val_type_t;

    // Construct the embedded concrete type.
    template<typename... args_t>
    _tc_impl_t(args_t&&... args) noexcept : concrete(std::forward<args_t>(args)...) { }

    explicit _tc_impl_t(const )raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(& concrete_arg) noexcept
      : concrete(concrete_arg) {}

    /*const size_t getModelTypeIndex() const noexcept override final {
        return _tc_registry<)raw"
           ;
              
              cxtpl_output
              +=  BaseTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>::
            getTypeIndex<)raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>();
    }*/


)raw"
           ;
                { // startscope
    for(const auto& method: ReflectedBaseTypeclass->methods) {
      const size_t methodParamsSize = method->params.size();
      const bool needPrint = !method->isImplicit
          && !method->isOperator
          && !method->isCtor
          && !method->isDtor;
      if(method->isTemplate()) {
              cxtpl_output
              += 
           R"raw(template< )raw"
           ;
              
              cxtpl_output
              +=  templateParamsFullDecls(method->tplParams) ;
              
              cxtpl_output
              += 
           R"raw( >
)raw"
           ;
                    } // method->isTemplate
      if(needPrint) {

              cxtpl_output
              +=  method->isExplicitCtor ? "explicit " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->isConstexpr ? "constexpr " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->isStatic ? "static " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->returnType->getPrintedName() ;
              
 /* no newline */

              cxtpl_output
              +=  " __" ;
              
 /* no newline */

              cxtpl_output
              +=  method->name ;
              
 /* no newline */
              cxtpl_output
              += 
           R"raw((
)raw"
           ;
              
              cxtpl_output
              +=  paramsFullDecls(method->params) ;
              
 /* no newline */
              cxtpl_output
              += 
           R"raw() )raw"
           ;
               /* no newline */

              cxtpl_output
              +=  method->isConst ? "const " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->isNoExcept ? "noexcept " : "" ;
              
 /* no newline */
              cxtpl_output
              += 
           R"raw(override final
  {
    /// \note passes data, not ref
    return )raw"
           ;
              
              cxtpl_output
              +=  method->name ;
              
 /* no newline */
              cxtpl_output
              += 
           R"raw(< )raw"
           ;
              
              cxtpl_output
              +=  BaseTypeclassName ;
              
              cxtpl_output
              += 
           R"raw( >)raw"
           ;
               /* no newline */
              cxtpl_output
              += 
           R"raw(()raw"
           ;
               /* no newline */
              cxtpl_output
              += 
           R"raw(concrete)raw"
           ;
               /* no newline */

              cxtpl_output
              +=  methodParamsSize ? ", " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  paramsCallDecls(method->params) ;
              
 /* no newline */
              cxtpl_output
              += 
           R"raw();
  }
)raw"
           ;
               /* newline */ 
              cxtpl_output
              += 
           R"raw(
)raw"
           ;
                    } // needPrint
    } // methods endfor
  } // endscope
              cxtpl_output
              += 
           R"raw(
    std::unique_ptr<
        _tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  BaseTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>>
    clone() noexcept override final {
        // Copy-construct a new instance of _tc_impl_t on the heap.
        return std::make_unique<_tc_impl_t>(concrete);
    }

    std::unique_ptr<
        _tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  BaseTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>>
    move_clone() noexcept override final {
        return std::make_unique<_tc_impl_t>(std::move(concrete));
    }

    )raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(* operator->() {
        return &concrete;
    }

  // Our actual data.
  )raw"
           ;
              
              cxtpl_output
              +=  ImplTypeclassName ;
              
              cxtpl_output
              += 
           R"raw( concrete;
};

} // namespace cxxctp
} // namespace generated

)raw"
           ;
              
              cxtpl_output
              +=  endHeaderGuard(headerGuard) /* no newline */ ;
              

