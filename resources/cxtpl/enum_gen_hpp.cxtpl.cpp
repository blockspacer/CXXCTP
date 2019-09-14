
              output
              += 
           R"raw(﻿)raw"
           ;
               // parameters begin

std::string headerGuard
  = GetWithDefault<std::string>(dictionary, "headerGuard", "");

std::string GeneratedEnumName
  = GetWithDefault<std::string>(dictionary, "GeneratedEnumName", "");

std::string GeneratedEnumType
  = GetWithDefault<std::string>(dictionary, "GeneratedEnumType", "");

std::map<std::string, std::string> GeneratedEnumItems
  = GetWithDefault<std::map<std::string, std::string>>(dictionary, "GeneratedEnumItems", std::map<std::string, std::string>{});

const size_t GeneratedEnumItemsSize = GeneratedEnumItems.size();
if(!GeneratedEnumItemsSize) {
  // TODO: report error
}

std::vector<std::string> generator_includes
  = GetWithDefault<std::vector<std::string>>
      (dictionary, "generator_includes", std::vector<std::string>{});

// parameters end

              output
              += 
           R"raw(
// This is generated file. Do not modify directly.
// Path to the code generator: {{generator_path}}.

)raw"
           ;
               if(!headerGuard.empty()) {
              output
              += 
           R"raw(#ifndef {{headerGuard}}
#define {{headerGuard}}
)raw"
           ;
               } else {
              output
              += 
           R"raw(#pragma once
)raw"
           ;
               } // !headerGuard.empty()
              output
              += 
           R"raw()raw"
           ;
               printf("headerGuard4 \n");
              output
              += 
           R"raw(
)raw"
           ;
               for(const auto& fileName: generator_includes) {
              output
              += 
           R"raw()raw"
           ;
              
              output
              +=  fileName ;
              
              output
              += 
           R"raw(
)raw"
           ;
               } // end for
              output
              += 
           R"raw(
#include <array>
#include <functional>

namespace cxxctp {
namespace generated {


} // namespace cxxctp
} // namespace generated

// Support using as key in dictionaries and maps
namespace std {
    template <>
    struct hash<cxxctp::generated::)raw"
           ;
              
              output
              +=  GeneratedEnumName ;
              
              output
              += 
           R"raw(> {
        size_t operator()(const cxxctp::generated::)raw"
           ;
              
              output
              +=  GeneratedEnumName ;
              
              output
              += 
           R"raw(& ) const;
    };
}

)raw"
           ;
               if(!headerGuard.empty()) {
              output
              += 
           R"raw(#endif // {{headerGuard}}
)raw"
           ;
               } // !headerGuard.empty()
              output
              += 
           R"raw()raw"
           ;
              