#pragma once

#include "clangUtils.h"
#include "ClingInterpreterModule.h"
#include "utils.h"

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
