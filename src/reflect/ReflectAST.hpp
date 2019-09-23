#pragma once

#include "ReflTypes.hpp"

namespace reflection
{

using namespace clang;

class AstReflector
{
public:
    explicit AstReflector(const clang::ASTContext* context)
        : m_astContext(context)
    {
    }

    EnumInfoPtr ReflectEnum(const clang::EnumDecl* decl, NamespacesTree* nsTree);
    TypedefInfoPtr ReflectTypedef(const clang::TypedefNameDecl* decl, NamespacesTree* nsTree);
    ClassInfoPtr ReflectClass(const clang::CXXRecordDecl* decl, NamespacesTree* nsTree);
    MethodInfoPtr ReflectMethod(const clang::FunctionDecl* decl, NamespacesTree* nsTree);

    static void SetupNamedDeclInfo(const clang::NamedDecl* decl, NamedDeclInfo* info, const clang::ASTContext* astContext);

private:

    const clang::NamedDecl* FindEnclosingOpaqueDecl(const clang::DeclContext* decl);
    void ReflectImplicitSpecialMembers(const clang::CXXRecordDecl* decl, ClassInfo* classInfo, NamespacesTree* nsTree);

private:
    const clang::ASTContext* m_astContext;
};

} // namespace reflection
