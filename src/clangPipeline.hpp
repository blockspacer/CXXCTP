#pragma once

#include "clangUtils.hpp"
#include "ClingInterpreterModule.hpp"
#include "utils.hpp"

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

typedef std::function<const char*(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args)> cxxctp_callback;

void add_cxxctp_callback(const std::string& id, const cxxctp_callback& func);

cxxctp_callback get_cxxctp_callback(const std::string& id);

/*typedef const char* make_removefuncbody(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    std::vector<cxxctp::parsed_func>& args)*/

} // namespace clang_utils
