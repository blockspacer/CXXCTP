#include "CXXCTP_STD.hpp"

#include <clang/Lex/Lexer.h>

#include <folly/logging/xlog.h>

#include <algorithm>
#include <string>

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

const bool isReflectable(clang::DeclaratorDecl* decl) {
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
      XLOG(DBG9) << "isReflectable code() " << code;
      std::string delimiter = ";";
      size_t pos = 0;
      std::string token;
      while ((pos = code.find(delimiter)) != std::string::npos) {
        token = code.substr(0, pos);
        XLOG(DBG9) << "isReflectable token " << token;
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

  XLOG(DBG9) << "isReflectable attr() "
    << decl->getNameAsString()
    << "is " << res;

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

cxxctp::args get_func_args(const std::vector<cxxctp::parsed_func>& args, const std::string& funcName) {
    for (auto const& seg : args) {
        if(!seg.parsed_func_.func_name_.empty() && seg.parsed_func_.func_name_ == funcName) {
            return seg.parsed_func_.args_;
        }
    }
    return cxxctp::args{};
}

void prepareTplArg(std::string &in)
{
  // remove quotes
  in.erase(
    std::remove( in.begin(), in.end(), '\"' ),
    in.end());

  // remove space
  /*in.erase(
    std::remove( in.begin(), in.end(), ' ' ),
    in.end());*/
}
