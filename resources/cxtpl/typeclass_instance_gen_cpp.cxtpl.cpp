
              cxtpl_output
              += 
           R"raw(﻿)raw"
           ;
               // parameters begin

const auto generator_path
  = GetWithDefault<std::string>(cxtpl_params, "generator_path", "");

std::vector<std::string> generator_includes
  = GetWithDefault<std::vector<std::string>>
      (cxtpl_params, "generator_includes", std::vector<std::string>{});

// parameters end
/* no newline */ 

              cxtpl_output
              += 
           R"raw(// This is generated file. Do not modify directly.
// Path to the code generator: )raw"
           ;
              
              cxtpl_output
              +=  generator_path ;
              
              cxtpl_output
              += 
           R"raw(.

)raw"
           ;
               for(const auto& fileName: generator_includes) {

              cxtpl_output
              +=  fileName /* no newline */ ;
              

 } // end for
              cxtpl_output
              += 
           R"raw(
#include <iostream>
#include <cstring>
#include <type_traits>

namespace cxxctp {
namespace generated {

// TODO
//{{GeneratedTypeclassName}}

} // namespace cxxctp
} // namespace generated
)raw"
           ;
              