#pragma once

#include <string>
#include <vector>
#include <map>

/*#include <boost/spirit/home/x3/core.hpp>
#include <boost/spirit/home/x3/operator.hpp>
#include <boost/spirit/home/x3/char.hpp>*/

namespace cxxctp {

struct func_arg {
  std::string name_;
  std::string value_;
};

struct args {
  std::vector<func_arg> as_vec_;
  std::map<std::string, std::vector<std::string>> as_name_to_value_;
};

struct parsed_func_detail {
  std::string func_name_;
  //std::string func_name_normalized_; // no need to remove ws, we ignored all ws
  args args_;
};

struct parsed_func {
  std::string func_with_args_as_string_;
  parsed_func_detail parsed_func_;
};

func_arg extract_func_arg(std::string const& inStr);

std::vector<parsed_func> split_to_funcs(std::string const& inStr);

} // namespace cxxctp
