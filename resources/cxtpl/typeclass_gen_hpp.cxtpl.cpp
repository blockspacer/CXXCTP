
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

std::string OriginalTypeclassBaseCode
  = GetWithDefault<std::string>
      (cxtpl_params, "OriginalTypeclassBaseCode", std::string{});

std::string GeneratedTypeclassName
  = GetWithDefault<std::string>
      (cxtpl_params, "GeneratedTypeclassName", std::string{});

reflection::ClassInfoPtr ReflectedStructInfo
  = GetWithDefault<reflection::ClassInfoPtr>
      (cxtpl_params, "ReflectedStructInfo", nullptr);

const size_t ReflectedStructInfoMethodsSize =
    ReflectedStructInfo->methods.size();

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
              
              cxtpl_output
              +=  OriginalTypeclassBaseCode ;
              
              cxtpl_output
              += 
           R"raw(;

)raw"
           ;
                { // startscope
    for(const auto& method: ReflectedStructInfo->methods) {
      const size_t methodParamsSize = method->params.size();
      const bool needPrint = !method->isImplicit
          && !method->isOperator
          && !method->isCtor
          && !method->isDtor;
      if(needPrint) {
              cxtpl_output
              += 
           R"raw(  template<
    typename T,
    typename V,
    typename std::enable_if<std::is_same<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(, T>::value>::type* = nullptr
  >
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
           R"raw((const V&)raw"
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
template<>
struct _tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(> {
  virtual ~_tc_model_t() noexcept { }

  virtual std::unique_ptr<_tc_model_t> clone() noexcept = 0;

  virtual std::unique_ptr<_tc_model_t> move_clone() noexcept = 0;

  //virtual const size_t getModelTypeIndex() const noexcept = 0;

)raw"
           ;
                { // startscope
    for(const auto& method: ReflectedStructInfo->methods) {
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
              +=  method->isVirtual ? "virtual " : "" ;
              
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
              +=  method->isPure ? "= 0 " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->isDeleted ? "= delete " : "" ;
              
 /* no newline */

              cxtpl_output
              +=  method->isDefault ? "= default " : "" ;
              
 /* no newline */
      if(method->isDefined && method->isClassScopeInlined) {

              cxtpl_output
              +=  method->body ;
              
              cxtpl_output
              += 
           R"raw(
)raw"
           ;
                    } else {
              cxtpl_output
              += 
           R"raw(;
)raw"
           ;
                    } // method->isDefined && method->isClassScopeInlined
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
  /*template <typename T>
  T& ref_concrete() noexcept;

  template <typename U>
  _tc_impl_t<U, )raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>* as() noexcept
  {
    return nullptr;
  }*/
};

template<>
struct _tc_combined_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(> {
    // Default initializer creates an empty _tc_combined_t.
    _tc_combined_t() = default;

    _tc_combined_t(std::reference_wrapper<_tc_combined_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>>&& rhs) noexcept {
        puts("_tc_combined_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(> ref copy ctor");
        if(rhs.get())
            my_interface_model = rhs.get().my_interface_model;
    }

    /// \note moves passed argument
    template <
        class T,
        typename = IsNotReference<T>,
        typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
        >
    _tc_combined_t(std::shared_ptr<T>&& u) noexcept :
                                                      my_interface_model(std::move(u)) {
        static_assert(!std::is_const<typename std::remove_reference<T>::type>::value,
                      "You've attempted a cast to a const rvalue reference. "
                      "Make sure you're not trying to move a const object, "
                      "as this would likely result in a copy not a move. "
                      "If you need it for real, call std::move(...) instead.");
        puts("_tc_combined_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(> called, moves passed argument");
    }

    template <
        class T,
        typename = IsNotReference<T>,
        typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
        >
    _tc_combined_t(const std::shared_ptr<T>& u) noexcept :
                                                           my_interface_model(u) {
        puts("_tc_combined_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(> called, shares passed argument");
    }

    template <
        class T,
        typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
        >
    _tc_combined_t(const std::reference_wrapper<T>& u) noexcept :
                                                                  my_interface_model(
                                                                      std::make_shared<
                                                                          _tc_impl_t<std::reference_wrapper<T>, )raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>>
                                                                      (std::forward<const std::reference_wrapper<std::decay_t<T>>>(u))) {
        puts("_tc_combined_t{T} reference_wrapper called");
    }

    template<
        typename T,
        typename = IsNotReference<T>,
        typename std::enable_if<!std::is_same<_tc_combined_t, T>::value>::type* = nullptr
        >
    _tc_combined_t(const T&& u) noexcept :
                                           my_interface_model(
                                               std::make_shared<
                                                   _tc_impl_t<T, )raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>>
                                               (std::forward<const std::decay_t<T>>(u))) {
        puts("_tc_combined_t{T} called");
    }

    // Call clone for copy ctor/assign.
    explicit _tc_combined_t(const _tc_combined_t& rhs) noexcept {
        puts("_tc_combined_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(> copy ctor");
        if(rhs)
            my_interface_model = rhs.my_interface_model->clone();
    }

    // Call move_clone for move ctor/assign.
    explicit _tc_combined_t(_tc_combined_t&& rhs) noexcept {
        if(rhs)
            my_interface_model = rhs.my_interface_model->move_clone();
    }

    // The preferred initializer for a _tc_combined_t. This constructs an _tc_impl_t of
    // type_t on the heap, and stores the pointer in a new _tc_combined_t.
    template<
        typename type_t,
        typename... args_t,
        typename = IsNotReference<type_t>
        >
    static _tc_combined_t construct(args_t&&... args) noexcept {
        return _tc_combined_t(std::make_shared<_tc_impl_t<type_t, )raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(> >(
            std::forward<args_t>(args)...
            ));
    }

    _tc_combined_t& operator=(_tc_combined_t&& rhs) noexcept {
        my_interface_model.reset();
        if(rhs)
            my_interface_model = rhs.my_interface_model->move_clone();
        return *this;
    }

    _tc_combined_t& operator=(const _tc_combined_t& rhs) noexcept {
        my_interface_model.reset();
        if(rhs)
            my_interface_model = rhs.my_interface_model->clone();
        return *this;
    }

    void reset() noexcept {
        my_interface_model.reset();
    }

    // A virtual dtor triggers the dtor in the impl.
    virtual ~_tc_combined_t() noexcept { }

)raw"
           ;
                { // startscope
    for(const auto& method: ReflectedStructInfo->methods) {
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
              +=  method->isVirtual ? "virtual " : "" ;
              
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
           R"raw(  {
    if(!my_interface_model) {
        std::terminate();
    }
    my_interface_model->__)raw"
           ;
              
              cxtpl_output
              +=  method->name ;
              
              cxtpl_output
              += 
           R"raw(()raw"
           ;
              
              cxtpl_output
              +=  paramsCallDecls(method->params) ;
              
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
    explicit operator bool() const noexcept {
        return (bool)my_interface_model;
    }

    std::shared_ptr<_tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>> ref_model() const noexcept {
        return my_interface_model;
    }

    std::unique_ptr<_tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>> clone_model() const noexcept {
        if(!my_interface_model) {
            std::terminate();
        }
        return my_interface_model->clone();
    }

    const _tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>* raw_model() const noexcept {
        return my_interface_model.get();
    }

    void replace_model(
        const std::shared_ptr<_tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>> rhs) noexcept {
        my_interface_model = rhs;
    }

    /*const size_t getModelTypeIndex() {
        if(!my_interface_model) {
            std::terminate();
        }
        return my_interface_model->getModelTypeIndex();
    }

    template <typename T>
    static const size_t getGlobalTypeIndex() {
        return _tc_registry<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>
            ::getTypeIndex<T>();
    }

    template <typename T>
    T& ref_concrete() noexcept {
        if(!my_interface_model || my_interface_model->getModelTypeIndex()
                != getGlobalTypeIndex<T>()) {
            std::terminate();
        }
        return my_interface_model->ref_concrete<T>();
    }*/

    template <typename U>
    bool can_convert() const
    {
        return false;
    }

    // This is actually a unique_ptr to an impl type. We store a pointer to
    // the base type and rely on _tc_model_t's virtual dtor to free the object.
private:
    std::shared_ptr<_tc_model_t<)raw"
           ;
              
              cxtpl_output
              +=  GeneratedTypeclassName ;
              
              cxtpl_output
              += 
           R"raw(>> my_interface_model;
};

} // namespace cxxctp
} // namespace generated

)raw"
           ;
              
              cxtpl_output
              +=  endHeaderGuard(headerGuard) /* no newline */ ;
              

