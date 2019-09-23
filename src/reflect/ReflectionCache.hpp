#pragma once

#include "ReflTypes.hpp"
#include "ReflectAST.hpp"
#include "../clangPipeline.hpp"

namespace reflection {

typedef std::string reflectionID;

/*class ReflectionCXXMethodRegistry {
    //reflectionID id_;
};*/

class ReflectionCXXRecordRegistry {
public:
    ReflectionCXXRecordRegistry(const reflectionID& id,
                                //clang::CXXRecordDecl const *node,
                                ClassInfoPtr classInfoPtr);
    reflectionID id_;
    //clang::CXXRecordDecl const *node_;
    ClassInfoPtr classInfoPtr_;
};

class ReflectionRegistry {
public:
    static ReflectionRegistry *instance;
public:
    static ReflectionRegistry *getInstance();
    std::map<reflectionID, std::unique_ptr<ReflectionCXXRecordRegistry>> reflectionCXXRecordRegistry;
};

} // namespace reflection
