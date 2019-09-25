#pragma once

#include <clang/Basic/SourceManager.h>
#include <clang/AST/PrettyPrinter.h>
#include <clang/AST/ASTContext.h>

#include <llvm/ADT/APSInt.h>

#include <string>
#include <type_traits>

#include "ReflTypes.hpp"

namespace reflection
{

inline auto GetLocation(const clang::SourceLocation& loc, const clang::ASTContext* context)
{
    SourceLocation result;
    clang::PresumedLoc ploc = context->getSourceManager().getPresumedLoc(loc, false);
    result.fileName = ploc.getFilename();
    result.line = ploc.getLine();
    result.column = ploc.getColumn();

    return result;
}

template<typename Entity>
auto GetLocation(const Entity* decl, const clang::ASTContext* context)
{
    return GetLocation(decl->getLocation(), context);
}

inline void SetupDefaultPrintingPolicy(clang::PrintingPolicy& policy)
{
    policy.Bool = true;
    policy.AnonymousTagLocations = false;
    policy.SuppressUnwrittenScope = true;
    policy.Indentation = 4;
    policy.UseVoidForZeroParams = false;
    policy.SuppressInitializers = true;
}

template<typename Entity>
std::string EntityToString(const Entity* decl, const clang::ASTContext* context)
{
    clang::PrintingPolicy policy(context->getLangOpts());

    SetupDefaultPrintingPolicy(policy);

    std::string result;
    {
        llvm::raw_string_ostream os(result);

        decl->print(os, policy);
    }
    return result;
}


/*template<typename Fn>
void WriteNamespaceContents(codegen::CppSourceStream &hdrOs, reflection::NamespaceInfoPtr ns, Fn&& fn)
{
    using namespace codegen;

    out::BracedStreamScope nsScope("namespace " + ns->name, "", 0);
    if (!ns->isRootNamespace)
        hdrOs << out::new_line(1) << nsScope;

    fn(hdrOs, ns);
    for (auto& inner : ns->innerNamespaces)
        WriteNamespaceContents(hdrOs, inner, std::forward<Fn>(fn));
}*/

struct IntegerValue
{
    bool isSigned = false;
    union
    {
        uint64_t uintValue;
        int64_t intValue;
    };

    uint64_t AsUnsigned() const {return uintValue;}
    int64_t AsSigned() const {return intValue;}

    template<typename T>
    auto GetAs() -> std::enable_if_t<std::is_signed<T>::value, T>
    {
        return static_cast<T>(intValue);
    }

    template<typename T>
    auto GetAs() -> std::enable_if_t<std::is_unsigned<T>::value, T>
    {
        return static_cast<T>(uintValue);
    }
};

inline IntegerValue ConvertAPSInt(llvm::APSInt intValue)
{
    IntegerValue result;
    result.isSigned = intValue.isSigned();
    result.intValue = intValue.getExtValue();

    return result;
}

inline IntegerValue ConvertAPInt(llvm::APInt intValue)
{
    IntegerValue result;
    result.isSigned = false;
    result.uintValue = intValue.getZExtValue();

    return result;
}

} // reflection
