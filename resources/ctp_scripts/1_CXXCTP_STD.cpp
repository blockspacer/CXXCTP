#include "CXXCTP_STD.hpp"

clang::SourceLocation
findPureInsertionPoint(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context) {
  clang::SourceLocation Location;

  /// Find the end of the parameter list.
  if (MethodDecl->param_empty()) {
    const unsigned Offset = MethodDecl->getName().size();
    Location = MethodDecl->getLocation().getLocWithOffset(Offset);
  } else {
    const clang::ParmVarDecl *Last = *std::prev(MethodDecl->param_end());
    Location = Last->getLocEnd(); // getEndLoc
  }

  Location = clang::Lexer::findLocationAfterToken(
      Location, clang::tok::r_paren, Context.getSourceManager(),
      Context.getLangOpts(),
      /*skipWhiteSpace=*/true);

  return Location.getLocWithOffset(0);
}

clang::SourceRange
findFuncBodyRange(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context) {
  return MethodDecl->getBody()->getSourceRange();
}

clang::SourceLocation
findVirtualInsertionPoint(clang::CXXMethodDecl *MethodDecl,
                   const clang::ASTContext &Context) {
  clang::SourceLocation Location;

  Location = MethodDecl->getLocStart();

  return Location.getLocWithOffset(0);
}

clang::SourceLocation
findCXXRecordNameEndPoint(clang::CXXRecordDecl const *decl,
                   const clang::ASTContext &Context) {
  clang::SourceLocation Location;

  /// Find the end of name.
  const unsigned Offset = decl->getName().size();
  Location = decl->getLocation().getLocWithOffset(Offset);

  return Location.getLocWithOffset(0);
}

const bool isReflectable(DeclaratorDecl* decl) {
  bool res = false;
  if ( auto annotate = decl->getAttr<clang::AnnotateAttr>() )
  {
    //
    const std::string gen_token = "{gen};{attr};";
    std:: string code =
      annotate->getAnnotation().str();
    const bool startsWithGen =
      code.rfind(gen_token, 0) == 0;
    code.erase(0, gen_token.size());
    if (startsWithGen) {
      std::cout << "isReflectable code() " << code << std::endl;
      std::string delimiter = ";";
      size_t pos = 0;
      std::string token;
      while ((pos = code.find(delimiter)) != std::string::npos) {
        token = code.substr(0, pos);
        std::cout << "isReflectable token " << token << std::endl;
        if(token == "reflectable") {
          res = true;
          break;
        }
        code.erase(0, pos + delimiter.length());
      }
      if(!code.empty()
         && code == "reflectable") {
        res = true;
      }
    }
  }

  std::cout << "isReflectable attr() "
    << decl->getNameAsString()
    << "is " << res << std::endl;

  return res;
}

std::string wrapLocalInclude(const std::string& inStr) {
    std::string result = R"raw(#include ")raw";
    result += inStr;
    result += R"raw(")raw";
    return result;
};

std::string get_func_arg(const std::vector<cxxctp::parsed_func>& args, const std::string& funcName, const int index) {
    std::string result;
    for (auto const& seg : args) {
        if(!seg.parsed_func_.func_name_.empty() && seg.parsed_func_.func_name_ == funcName) {
            if(index < seg.parsed_func_.args_.as_vec_.size()) {
                result = seg.parsed_func_.args_.as_vec_.at(index).value_;
            }
            break;
        }
    }
    return result;
}
