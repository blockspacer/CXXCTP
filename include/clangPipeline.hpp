#pragma once

#include "clangUtils.hpp"

#include "funcParser.hpp"

#if defined(CLING_IS_ON)
#include "ClingInterpreterModule.hpp"
#endif // CLING_IS_ON

#include "utils.hpp"

#include "ctp_scripts/1_utils/CXXCTP_STD/CXXCTP_STD.hpp"

#include <clang/Rewrite/Core/Rewriter.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchersMacros.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/ASTConsumers.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Basic/SourceManager.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Rewrite/Core/Rewriter.h>

namespace clang_utils {

namespace UseOverride {
class Checker : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
    using MatchResult = clang::ast_matchers::MatchFinder::MatchResult;

    Checker(/*bool RewriteOption, */clang::Rewriter &Rewriter)
        : /*RewriteOption(RewriteOption),*/ rewriter_(Rewriter) {}

    void run(const MatchResult &Result);

private:
//bool RewriteOption;

clang::Rewriter &rewriter_;
};

class Consumer : public clang::ASTConsumer {
public:
    explicit Consumer(clang::Rewriter &Rewriter);

    void HandleTranslationUnit(clang::ASTContext &Context) override;

private:
    clang::ast_matchers::MatchFinder Finder_;
    Checker Checker_;
};

class Action : public clang::ASTFrontendAction {
public:
    using ASTConsumerPointer = std::unique_ptr<clang::ASTConsumer>;

    explicit Action() {}

    ASTConsumerPointer CreateASTConsumer(clang::CompilerInstance &Compiler,
                                         llvm::StringRef /*Filename*/) override;

    bool BeginSourceFileAction(clang::CompilerInstance &/*Compiler*/) override;

    void EndSourceFileAction() override;

private:
    clang::Rewriter Rewriter;
};
} // namespace UseOverride

struct ToolFactory : public clang::tooling::FrontendActionFactory {
    //ToolFactory(/*clang::FrontendAction* act, std::unique_ptr<clang::ASTConsumer> consumer*/)
    //  /*: m_act(act), m_consumer(std::move(consumer))*/ {};
    clang::FrontendAction *create() override;
    //clang::FrontendAction* m_act;
    //std::unique_ptr<clang::ASTConsumer> m_consumer;
};

void add_default_clang_args(std::vector<std::string>& args);

/**
  * \brief callback that will be called then parser
  * found custom attribute.
  * Used only in compile-mode, because in Cling-mode
  * we can call and interpret functions by name.
  * \arg return value (const char*) - used to replace original code, if needed.
  * \arg func_with_args - currently executed function from list `all_funcs_with_args` (see below)
  * \arg clang::ast_matchers::MatchFinder::MatchResult - see https://xinhuang.github.io/posts/2015-02-08-clang-tutorial-the-ast-matcher.html
  * \arg clang::Rewriter - see https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-3-rewriting-code-with-clang-tidy/
  * \arg clang::Decl - found by MatchFinder, see https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-2-examining-the-clang-ast-with-clang-query/
  * \arg std::vector<parsed_func> - all arguments extracted from attribute. Example: $apply(interface, foo_with_args(1, "2")) becomes two `parsed_func` - `interface` and `foo_with_args`.
**/
typedef std::function<cxxctp_callback_result(
      const cxxctp_callback_args& callback_args)> cxxctp_callback;

void add_cxxctp_callback(const std::string& id, const cxxctp_callback& func);

cxxctp_callback get_cxxctp_callback(const std::string& id);

std::map<std::string, cxxctp_callback> get_cxxctp_callbacks();

/*typedef const char* make_removefuncbody(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    std::vector<cxxctp::parsed_func>& args)*/

} // namespace clang_utils
