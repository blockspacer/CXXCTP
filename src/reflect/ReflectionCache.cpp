#include "ReflectionCache.h"

namespace reflection {

ReflectionRegistry *ReflectionRegistry::instance;

ReflectionRegistry *ReflectionRegistry::getInstance() {
    if (!instance)
        instance = new ReflectionRegistry;
    return instance;
}

ReflectionCXXRecordRegistry::ReflectionCXXRecordRegistry(const reflectionID &id/*, const CXXRecordDecl *node*/, ClassInfoPtr classInfoPtr, const jinja2::Value& reflectedJinjaClass)
    : id_(id)/*, node_(node)*/, classInfoPtr_(classInfoPtr), reflectedJinjaClass_(reflectedJinjaClass) {
}

} // namespace reflection
