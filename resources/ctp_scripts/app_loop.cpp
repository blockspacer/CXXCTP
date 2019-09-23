#include "app_loop.hpp"

#include "ctp_registry.hpp"

extern std::vector<cxxctp::parsed_func> split_to_funcs(std::string const& inStr);

using namespace std;
using namespace clang;
using namespace clang::driver;
using namespace clang::tooling;
using namespace llvm;
using namespace clang::ast_matchers;
using clang::tooling::CommonOptionsParser;
using clang::tooling::Replacement;
using llvm::StringRef;

class AppLoop
{
public:
    AppLoop()
    {
    }

    void run();

    void stop();

    // The acceptor receives incoming connections
    //tcp::acceptor acceptor;

    bool m_Running = true;

    //std::vector<std::function<void(bool,int)>> callbacks_;
    //std::function<void(void)> callback_;
};

AppLoop* appLoop = nullptr;

void AppLoop::run() {
        std::cout << "AppLoop::run(): " << std::endl;
}

void AppLoop::stop() {
    m_Running = false;
}


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
#if 0
  clang::SourceLocation LocationStart;
  clang::SourceLocation LocationEnd;

  /// Find the end of the parameter list.
  if (MethodDecl->param_empty()) {
    const unsigned Offset = MethodDecl->getName().size();
    LocationStart = MethodDecl->getLocation().getLocWithOffset(Offset);
  } else {
    const clang::ParmVarDecl *Last = *std::prev(MethodDecl->param_end());
    LocationStart = Last->getLocEnd(); // getEndLoc
  }

  LocationStart = LocationStart.getLocWithOffset(1);

  LocationEnd = clang::Lexer::findLocationAfterToken(
      LocationStart, clang::tok::r_brace, Context.getSourceManager(),
      Context.getLangOpts(),
      /*skipWhiteSpace=*/true);

  return clang::SourceRange(
    LocationStart,
    LocationEnd);
#endif
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


#if 0
  for (auto &attr : decl->attrs()) {
      if (attr->getKind() == attr::Annotate) {
        Attr a = *attr;
        auto annotate = static_cast<clang::AnnotateAttr>(*attr);

        std::cout << "isReflectable attr->getSpelling() " << attr->getSpelling() << std::endl;
        //
        const std::string gen_token = "{gen};{attr}";
        std:: string code =
          attr->getSpelling();
        const bool startsWithGen =
          code.rfind(gen_token, 0) == 0;
        code.erase(0, gen_token.size());
        if (startsWithGen) {
          std::string delimiter = ";";
          size_t pos = 0;
          std::string token;
          while ((pos = code.find(delimiter)) != std::string::npos) {
            token = code.substr(0, pos);
            std::cout << "isReflectable token " << token << std::endl;
            if(token == "reflectable") {
              res = true;
            }
            code.erase(0, pos + delimiter.length());
          }
        }
      }
  }
#endif
  return res;
}

/*const std::string
getFileContent(const std::string& path)
{
  std::ifstream file(path);
  if(!file.is_open()) {
    printf("ERROR: can`t read file %s\n", path.c_str());
    return "";
  }
  std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  //printf("loaded %s from file %s\n", content.c_str(), path.c_str());
  return content;
}

void writeToFile(const std::string& str, const std::string& path) {
  //printf("saving %s to file %s\n", str.c_str(), path.c_str());
  std::ofstream file(path);
  if(!file.is_open()) {
    printf("ERROR: can`t write to file %s\n", path.c_str());
    return;
  }
  file << str;
  file.close();
}*/

std::string wrapLocalInclude(const std::string& inStr) {
    std::string result = R"raw(#include ")raw";
    result += inStr;
    result += R"raw(")raw";
    return result;
};

struct ReflectedEnumItems {
  std::string name;
  int64_t value;
};

std::string get_func_arg(const std::vector<cxxctp::parsed_func>& args, const std::string& funcName, const int index) {
    std::string result;
    for (auto const& seg : args) {
        /*llvm::outs() << "segment: " << seg.func_with_args_as_string_ << "\n";
        llvm::outs() << "funcs_to_call2  func_name_: " << seg.parsed_func_.func_name_ << "\n";*/
        if(!seg.parsed_func_.func_name_.empty() && seg.parsed_func_.func_name_ == funcName) {
            if(index < seg.parsed_func_.args_.as_vec_.size()) {
                result = seg.parsed_func_.args_.as_vec_.at(index).value_;
            }
            break;
        }
    }
    return result;
}

const char* typeclass_instance(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
    printf("typeclass_instance called...\n");

    std::map<std::string, std::any> cxtpl_params;

    std::string typeclassBaseName = get_func_arg(args, "typeclass_instance", 0);

    printf("typeclassBaseName = %s...\n", typeclassBaseName.c_str());
    if(typeclassBaseName.empty()) {
        return "";
    }

    if(reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry.find(typeclassBaseName) == reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry.end())
    {
        printf("typeclassBaseName = %s not found!\n", typeclassBaseName.c_str());
        return "";
    }

    const reflection::ReflectionCXXRecordRegistry* ReflectedBaseTypeclass = reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry[typeclassBaseName].get();
    /*const clang::CXXRecordDecl* typeclassBaseNode = ReflectedBaseTypeclass->node_;
    if(!typeclassBaseNode) {
        printf("typeclassBaseNode not found for typeclassBaseNode = %s!\n", typeclassBaseName.c_str());
        return "";
    }*/

    /*if(ReflectedBaseTypeclass->reflectedJinjaClass_.isEmpty()) {
        printf("ReflectedBaseTypeclass not found for typeclassBaseNode = %s!\n", typeclassBaseName.c_str());
        return "";
    }*/

    const clang::CXXRecordDecl *node =
        matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");

    if (!node) {
        printf("CXXRecordDecl not found for typeclassBaseNode = %s!\n", typeclassBaseName.c_str());
        return "";
    }

    printf("reflect is record %s\n", node->getNameAsString().c_str());

    cxtpl_params.emplace("ReflectedBaseTypeclass",
                         std::make_any<reflection::ClassInfoPtr>(ReflectedBaseTypeclass->classInfoPtr_));

    cxtpl_params.emplace("ImplTypeclassName",
                         std::make_any<std::string>(node->getNameAsString()));

    cxtpl_params.emplace("BaseTypeclassName",
                         std::make_any<std::string>(ReflectedBaseTypeclass->classInfoPtr_->name));

    SourceManager &SM = rewriter.getSourceMgr();
    const auto fileID = SM.getMainFileID();
    const auto fileEntry = SM.getFileEntryForID(SM.getMainFileID());
    std::string original_full_file_path = fileEntry->getName();

    std::cout << "original_full_file_path is " << original_full_file_path << "\n";

    /*auto wrapLocalInclude = [](const std::string& inStr) {
        std::string result = R"raw(#include ")raw";
        result += inStr;
        result += R"raw(")raw";
        return result;
    };*/

    {
        std::string gen_hpp_name
            = node->getNameAsString() + ".typeclass_instance.generated.hpp";
        std::string gen_base_typeclass_hpp_name
            = ReflectedBaseTypeclass->classInfoPtr_->name + ".typeclass.generated.hpp";
        cxtpl_params.emplace("generator_path",
                             std::make_any<std::string>("typeclass_instance_gen_hpp.cxtpl"));
        cxtpl_params.emplace("generator_includes",
                             std::make_any<std::vector<std::string>>(
                                 std::vector<std::string>{
                                     /// \TODO
                                     R"raw(#include "../resources/type_erasure_common.hpp")raw",
                                     wrapLocalInclude(gen_base_typeclass_hpp_name).c_str(),
                                     wrapLocalInclude(original_full_file_path).c_str()
                                 })
                             );

        std::string cxtpl_output;

#include "../../resources/cxtpl/generated/typeclass_instance_gen_hpp.cxtpl.cpp"

        cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);

        /*
        std::string typeclassHppConvertor =
            getFileContent("../resources/typeclass_instance_gen_hpp.cxtpl");
        params.emplace("generator_includes",
                       jinja2::Value{
                           jinja2::ValuesList{
                               /// \TODO
                               R"raw(#include "../resources/type_erasure_common.hpp")raw",
                               wrapLocalInclude(gen_base_typeclass_hpp_name).c_str(),
                               wrapLocalInclude(original_full_file_path).c_str()
                           }
                       });
        jinja2::Template tpl;
        auto parseResult = tpl.Load(typeclassHppConvertor);
        if(!parseResult) {
            printf("ERROR: can`t load jinja2 template from %s [%s]\n",
                   typeclassHppConvertor.c_str(),
                   parseResult.error().GetLocationDescr().c_str());
        }
        writeToFile(tpl.RenderAsString(params).value(), gen_hpp_name);*/
    }
  return ""; // TODO
}

// see https://github.com/tlatkdgus1/llvm-code_obfuscate/blob/c4d0641f95704fb9909e2ac09500df1b6bc5d017/tools/clang/lib/AST/DeclPrinter.cpp#L447
// see https://github.com/root-project/root/blob/331efa4c00fefc38980eaaf7b41b8e95fcd1a23b/interpreter/llvm/src/tools/clang/lib/AST/DeclPrinter.cpp#L474
const char* typeclass(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {

  reflection::NamespacesTree m_namespaces; // TODO

  printf("typeclass called...\n");

  const clang::CXXRecordDecl *node =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");

  if (node) {
    printf("reflect is record %s\n", node->getNameAsString().c_str());

    std::map<std::string, std::any> cxtpl_params;

    {
        printf("reflector... for record %s\n", node->getNameAsString().c_str());
        reflection::AstReflector reflector(matchResult.Context);

        printf("ClassInfoPtr... for record %s\n", node->getNameAsString().c_str());
        reflection::ClassInfoPtr structInfo = reflector.ReflectClass(node, &m_namespaces);

        printf("reflectClassInfoPtr... for record %s\n", node->getNameAsString().c_str());
        //jinja2::Value reflectedJinjaClass = reflectClassInfoPtr(structInfo);
        cxtpl_params.emplace("ReflectedStructInfo",
                       std::make_any<reflection::ClassInfoPtr>(structInfo));
        std::cout << "methods: " << structInfo->methods.size() << "\n";

        for(auto mit : structInfo->methods){
            std::cout << "methods: " << mit->name << "\n";
            for(auto it : mit->params){
                std::cout << "methods params: " << it.name << it.fullDecl << "\n";
            }
        }

        printf("ReflectionRegistry... for record %s\n", node->getNameAsString().c_str());
        reflection::ReflectionRegistry::getInstance()->reflectionCXXRecordRegistry[node->getNameAsString()] = std::make_unique<reflection::ReflectionCXXRecordRegistry>(node->getNameAsString(), /*node,*/ structInfo);

      //jinja2::ValuesList GeneratedTypeclassFuncs;

      // see https://github.com/asutton/clang/blob/master/lib/AST/DeclPrinter.cpp#L502
      /*for(auto fct = node->method_begin();
        fct != node->method_end(); ++fct)
      {
        CXXMethodDecl* tf = *fct;
        std::string methodDecl = reflectMethodDecl(decl, node, tf);

        if(!methodDecl.empty()) {
          GeneratedTypeclassFuncs.push_back(jinja2::Value{methodDecl.c_str()});
        }
      }*/

      SourceLocation startLoc = decl->getLocStart();
      SourceLocation endLoc = decl->getLocEnd();
      clang_utils::expandLocations(startLoc, endLoc, rewriter);

      auto codeRange = SourceRange{startLoc, endLoc};

      std::string OriginalTypeclassBaseCode =
        rewriter.getRewrittenText(codeRange);

      // removes $apply(typeclass, e.t.c.)
      std::string CleanOriginalTypeclassBaseCode
        = std::regex_replace(OriginalTypeclassBaseCode,
            std::regex("\\$apply([^(]*)\\([^)]*\\)(.*)"), "$1$2");

      cxtpl_params.emplace("OriginalTypeclassBaseCode",
                           std::make_any<std::string>(CleanOriginalTypeclassBaseCode));

      cxtpl_params.emplace("GeneratedTypeclassName",
                     std::make_any<std::string>(node->getNameAsString()));

      //params.emplace("GeneratedTypeclassFuncs",
      //               jinja2::Value{GeneratedTypeclassFuncs});

      /*auto wrapLocalInclude = [](const std::string& inStr) {
          std::string result = R"raw(#include ")raw";
          result += inStr;
          result += R"raw(")raw";
          return result;
      };*/

      {
        std::string gen_hpp_name
            = node->getNameAsString() + ".typeclass.generated.hpp";
        cxtpl_params.emplace("generator_path",
                       std::make_any<std::string>("typeclass_gen_hpp.cxtpl"));
        cxtpl_params.emplace("generator_includes",
                             std::make_any<std::vector<std::string>>(
                                 std::vector<std::string>{
                                     wrapLocalInclude(R"raw(../resources/type_erasure_common.hpp)raw")
                                 })
                             );

        std::string cxtpl_output;

#include "../../resources/cxtpl/generated/typeclass_gen_hpp.cxtpl.cpp"

        cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);

        /*
        std::string typeclassHppConvertor =
          getFileContent("../resources/typeclass_gen_hpp.cxtpl");
        jinja2::Template tpl;
        auto parseResult = tpl.Load(typeclassHppConvertor);
        if(!parseResult) {
          printf("ERROR: can`t load jinja2 template from %s [%s]\n",
            typeclassHppConvertor.c_str(),
            parseResult.error().GetLocationDescr().c_str());
        }
        writeToFile(tpl.RenderAsString(params).value(), gen_hpp_name);*/
      }
    }
  }

  return "";
}

const char* reflect_enum(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  printf("reflect_enum called...\n");

  clang::EnumDecl const *node =
      matchResult.Nodes.getNodeAs<clang::EnumDecl>("bind_gen");

  if (node) {
    printf("reflect is record %s\n", node->getNameAsString().c_str());

    std::map<std::string, std::any> cxtpl_params;

    std::unordered_map<std::string, std::string> GeneratedEnumItems;

    GeneratedEnumItems.emplace("NONE", std::to_string(0));

    LangOptions LO;
    PrintingPolicy PrintPolicy(LO);
    PrintPolicy.AnonymousTagLocations = false;
    PrintPolicy.SuppressTagKeyword = true;

    PresumedLoc pLoc = node->getASTContext()
                           .getSourceManager()
                           .getPresumedLoc(node->getLocation());

    std::string nameString = node->getNameAsString();
    if(nameString.empty()) {
      printf("ERROR (reflect_enum): "
             "can`t handle enum without name [%s:%d]\n",
              pLoc.getFilename(), pLoc.getLine());
    }
    std::string typeString = "int";
    const QualType QT = node->getIntegerType();
    if(!QT.isNull()) {
      typeString = QT.getAsString(); // getTypeClassName
    }
    printf("%s : %s [%s:%d]\n",
      nameString.c_str(), typeString.c_str(),
      pLoc.getFilename(), pLoc.getLine());

    int64_t maxval = std::numeric_limits<int64_t>::min();
    for (auto iter = node->enumerator_begin();
         iter != node->enumerator_end(); iter++)
    {
        printf("    %s %ld\n", iter->getNameAsString().c_str(),
          iter->getInitVal().getExtValue());
        GeneratedEnumItems.emplace(
            iter->getNameAsString(),
            std::to_string(
                iter->getInitVal().getExtValue()));
        maxval = std::max(maxval, iter->getInitVal().getExtValue());
    }
    printf("\n");

    GeneratedEnumItems.emplace(
        "TOTAL", std::to_string(maxval + 1));

      cxtpl_params["GeneratedEnumItems"] =
        std::make_any<std::unordered_map<std::string, std::string>>(GeneratedEnumItems);
      cxtpl_params["GeneratedEnumName"] =
          std::make_any<std::string>(nameString);
      cxtpl_params["GeneratedEnumType"] =
          std::make_any<std::string>(typeString);

    std::string gen_hpp_name = node->getNameAsString() + ".enum.generated.hpp";
    /*std::string gen_hpp_inc_code =  R"raw(#include ")raw";
    gen_hpp_inc_code += node->getNameAsString() + ".enum.generated.hpp";
    gen_hpp_inc_code += R"raw(")raw";*/
    {
      cxtpl_params["generator_path"] =
          std::make_any<std::string>("enum_gen_cpp.cxtpl");
      cxtpl_params["generator_includes"] =
          std::make_any<std::vector<std::string>>(
              std::vector<std::string>{
                  wrapLocalInclude(gen_hpp_name)
              });

      std::string cxtpl_output;

#include "../../resources/cxtpl/generated/enum_gen_cpp.cxtpl.cpp"

      cxxctp::utils::writeToFile(cxtpl_output, node->getNameAsString() + ".enum.generated.cpp");
    }

    {
      cxtpl_params["generator_path"] =
          std::make_any<std::string>("enum_gen_hpp.cxtpl");
      cxtpl_params["generator_includes"] =
          std::make_any<std::vector<std::string>>(
              std::vector<std::string>{});

      std::string cxtpl_output;

#include "../../resources/cxtpl/generated/enum_gen_hpp.cxtpl.cpp"

      cxxctp::utils::writeToFile(cxtpl_output, gen_hpp_name);
    }
  }

  return "";
}

const char* make_reflect(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  printf("make_removefuncbody called...\n");

  std::string indent = "  ";
  std::string output{};
  output.append("\n");
  output.append(indent
                  + "public:");
  indent.append("  ");
  output.append("\n");

  std::map<std::string, std::string> fields;
  std::map<std::string, std::string> methods;

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    //printf("reflect is record %s\n", record->getNameAsString().c_str());

    // see https://github.com/Papierkorb/bindgen/blob/b55578e517a308778f5a510de02af499b353f15d/clang/src/record_match_handler.cpp
    for (clang::Decl *decl : record->decls()) {
      if (clang::CXXMethodDecl *method
            = llvm::dyn_cast<clang::CXXMethodDecl>(decl)) {
        //runOnMethod(method, isSignal);
        printf("reflect is CXXMethodDecl %s %s %s %s\n",
          method->getNameInfo().getName().getAsString().c_str(),
          method->getReturnType().getAsString().c_str(),
          method->getType().getUnqualifiedType().getAsString().c_str(),
          method->getNameAsString().c_str());
        if(isReflectable(method)) {
          methods[method->getNameInfo().getName().getAsString()] =
            method->getReturnType().getAsString().c_str();
        }
      } else if (clang::AccessSpecDecl *spec
                    = llvm::dyn_cast<clang::AccessSpecDecl>(decl)) {
        //isSignal = AccessSpecDecl(spec);
        //printf("is CXXMethodDecl %s\n", spec->getNameAsString().c_str());
      } else if (clang::FieldDecl *field
                    = llvm::dyn_cast<clang::FieldDecl>(decl)) {
        //runOnField(field);
        printf("reflect is FieldDecl %s %s\n",
          field->getType().getUnqualifiedType().getAsString().c_str(),
          field->getNameAsString().c_str());
        if(isReflectable(field)) {
          fields[field->getNameAsString()] =
            field->getType().getUnqualifiedType().getAsString().c_str();
        }
      }
    }

    // TODO: use template

    output.append(indent
                    + "static std::map<std::string, std::string> fields");
    output.append(" = {");
    output.append("\n");
    for(const auto& [key, value] : fields) {
      output.append(indent
                      + indent + "{ ");
      output.append("\"" + key + "\"");
      output.append(", ");
      output.append("\"" + value + "\"");
      output.append(" }");
      output.append("\n");
    }
    output.append("\n");
    output.append(indent
                  + "};");
    output.append("\n");
    // methods
    output.append("\n");
    output.append(indent
                    + "static std::map<std::string, std::string> methods");
    output.append(" = {");
    output.append("\n");
    for(const auto& [key, value] : methods) {
      output.append(indent + indent
                      + "{ ");
      output.append("\"" + key + "\"");
      output.append(", ");
      output.append("\"" + value + "\"");
      output.append(" }");
      output.append("\n");
    }
    output.append("\n");
    output.append(indent +
                    "};");
    output.append("\n");
    auto locEnd = record->getLocEnd();
    rewriter.InsertText(locEnd, output,
      /*InsertAfter=*/true, /*IndentNewLines*/ false);
#if 0
    rewriter.InsertText(locEnd.getLocWithOffset(-1), "\nsdfsdfsdff",
      /*InsertAfter=*/true, /*IndentNewLines*/ true);
    rewriter.InsertText(locEnd.getLocWithOffset(-1), "\nfgfgfgfgf",
      /*InsertAfter=*/true, /*IndentNewLines*/ true);
#endif

    /*for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(fct->hasBody() && !fct->getNameAsString().empty()) {
          printf("INFO: removed body from function %s in CXXRecordDecl %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
          rewriter.RemoveText(findFuncBodyRange(*fct, *matchResult.Context));
        }
    }*/
  }
  return "";
}

const char* make_removefuncbody(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  printf("make_removefuncbody called...\n");

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {
    printf("is record %s\n", record->getNameAsString().c_str());
    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(fct->hasBody() && !fct->getNameAsString().empty()) {
          printf("INFO: removed body from function %s in CXXRecordDecl %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
          rewriter.RemoveText(findFuncBodyRange(*fct, *matchResult.Context));
        }
    }
  }
  return "";
}

/*void expandLocations(SourceLocation& startLoc,
      SourceLocation& endLoc,
      Rewriter& rewriter_) {
  if( startLoc.isMacroID() ) {
      // Get the start/end expansion locations
      std::pair< SourceLocation, SourceLocation > expansionRange =
               rewriter_.getSourceMgr().getImmediateExpansionRange( startLoc );

      // We're just interested in the start location
      startLoc = expansionRange.first;
      endLoc = expansionRange.second;
  }
}*/

// see https://blog.jetbrains.com/clion/2017/11/towards-a-more-powerful-and-simpler-cpp-with-herb-sutter/
// see https://herbsutter.com/2017/07/26/metaclasses-thoughts-on-generative-c/
// see https://www.fluentcpp.com/2018/03/09/c-metaclasses-proposal-less-5-minutes/
const char* make_interface(
    const clang::ast_matchers::MatchFinder::MatchResult& matchResult,
    clang::Rewriter& rewriter,
    const clang::Decl* decl,
    const std::vector<cxxctp::parsed_func>& args) {
  printf("make_interface called...\n");

  clang::CXXRecordDecl const *record =
      matchResult.Nodes.getNodeAs<clang::CXXRecordDecl>("bind_gen");
  if (record) {

    /*SourceLocation startLoc = record->getLocStart();
    SourceLocation endLoc = record->getLocEnd();
    clang_utils::expandLocations(startLoc, endLoc, rewriter);
    rewriter.InsertText(startLoc, " startLoc1 ");
    rewriter.InsertText(endLoc, " endLoc2 ");*/

    printf("is record %s\n", record->getNameAsString().c_str());
#if 0
    {
        clang::SourceLocation ClassRenamePoint =
            findCXXRecordNameEndPoint(record, *matchResult.Context);
        /*rewriter.ReplaceText(ClassRenamePoint,
          record->getName().size(), "asdsadads ");*/
        rewriter.InsertText(record->getLocation(), "ClassRenamePoint ");
    }
#endif // 0

    // TODO:
    // see https://stackoverflow.com/questions/24706053/how-to-find-move-constructors-in-codebase-using-clang-ast-tools/32082812#32082812
    // compiler.require(!f.is_copy() && !f.is_move(), "interfaces may not copy or move; consider a virtual clone() instead"); // 3.1

    // see https://github.com/crdelozier/ironclad/blob/master/tools/refactoring-tool/Translator.hpp#L327
    // see https://dl.khadas.com/test/github/external/v8/tools/clang/plugins/FindBadConstructsConsumer.cpp
    // see https://github.com/crosswalk-project/chromium-crosswalk/blob/master/tools/clang/plugins/FindBadConstructsConsumer.cpp
    // see https://github.com/csmith-project/creduce/blob/master/clang_delta/RemoveUnusedOuterClass.cpp#L68
    if (!record->hasUserDeclaredDestructor()) {
      printf("ERROR: found interface %s without virtual destructor\n",
        record->getNameAsString().c_str());
      //rewriter.InsertText(PureInsertionPoint,
      //  "\nvirtual ~CLASSNAME_HERE() noexcept {}\n");
    } else if (!record->getDestructor()->isVirtual()) {
      printf("ERROR: found not-virtual destructor in interface %s\n",
        record->getNameAsString().c_str());
    }

    for(auto fld = record->fields().begin();
      fld!= record->fields().end(); ++fld)
    {
        printf("ERROR: found data %s in interface %s\n",
          fld->getNameAsString().c_str(),
          record->getNameAsString().c_str());
    }


    for(auto fct = record->method_begin();
      fct!= record->method_end(); ++fct)
    {
      if(!fct->isInvalidDecl() && !fct->getNameAsString().empty()) {
        // check
        if(fct->isModulePrivate()) {
          printf("ERROR: found private function %s in interface %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
        }

        // check
        if(fct->hasBody()) {
          printf("ERROR: found function %s with body in interface %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
        }

        // modify
        if(!fct->isPure()) {
          //fct->setPure(true);
          printf("INFO: made pure function %s in interface %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
          //clang::CXXMethodDecl f =
          //findInsertionPoint()

          clang::SourceLocation PureInsertionPoint =
              findPureInsertionPoint(*fct, *matchResult.Context);
          rewriter.InsertText(PureInsertionPoint, " = 0");
        }

        // modify
        if(!fct->isVirtual()) {
          //fct->setPure(true);
          printf("INFO: made virtual function %s in interface %s\n",
            fct->getNameAsString().c_str(),
            record->getNameAsString().c_str());
          //clang::CXXMethodDecl f =
          //findInsertionPoint()

          clang::SourceLocation VirtualInsertionPoint =
              findVirtualInsertionPoint(*fct, *matchResult.Context);
          rewriter.InsertText(VirtualInsertionPoint, "virtual ");
        }
      }
    }
  }

  clang::FieldDecl const *field =
    matchResult.Nodes.getNodeAs<clang::FieldDecl>("bind_gen");
  if (field) {
    printf("is field\n");
  }

  clang::FunctionDecl const *function =
      matchResult.Nodes.getNodeAs<clang::FunctionDecl>("bind_gen");
  if (function) {
    printf("is function\n");
  }

  return "";
}

#if defined(CLING_IS_ON)

static void main_module_cling_prepare() {
    printf("called app_loop_prepare\n");
    //MyTest1();

    try
    {
        appLoop = new AppLoop();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

/*static void main_module_cling_run_update() {
    printf("called app_loop_run_update\n");
}*/

static void main_module_cling_run() {
    printf("called app_loop_run\n");

    appLoop->run();
}

static void main_module_cling_shutdown() {
    printf("called app_loop_shutdown\n");
    appLoop->stop();
    delete appLoop;
}

void app_loop() {
    printf("loaded app_loop with CLING\n");
    /*std::scoped_lock<std::mutex> lock(lock_);
    auto globVar =
          ::std::optional<std::string>
          {"asdasdcout123123"};*/
}

#endif // CLING_IS_ON
