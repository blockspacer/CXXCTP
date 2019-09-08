#pragma once

#include "ReflTypes.h"
#include "ReflectAST.h"
#include "../clangPipeline.h"

namespace reflection {

typedef std::string reflectionID;

/*class ReflectionCXXMethodRegistry {
    //reflectionID id_;
};*/

class ReflectionCXXRecordRegistry {
public:
    ReflectionCXXRecordRegistry(const reflectionID& id,
                                //clang::CXXRecordDecl const *node,
                                ClassInfoPtr classInfoPtr,
                                const jinja2::Value& reflectedJinjaClass);
    reflectionID id_;
    //clang::CXXRecordDecl const *node_;
    ClassInfoPtr classInfoPtr_;
    jinja2::Value reflectedJinjaClass_;
};

class ReflectionRegistry {
public:
    static ReflectionRegistry *instance;
public:
    static ReflectionRegistry *getInstance();
    std::map<reflectionID, std::unique_ptr<ReflectionCXXRecordRegistry>> reflectionCXXRecordRegistry;
};

} // namespace reflection
