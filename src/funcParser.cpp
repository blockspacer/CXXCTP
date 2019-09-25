#include "funcParser.hpp"

#include <cassert>
#include <sstream>
#include <iomanip>
//#include <iostream>

namespace cxxctp {

func_arg extract_func_arg(std::string const& inStr) {
  std::string arg_value_ = inStr;
  std::string arg_name_ = "";
  auto delim_pos = inStr.find('=');
  if(delim_pos != std::string::npos) {
    arg_name_ = inStr.substr(0, delim_pos);
    if(!arg_name_.empty()) {
      assert(arg_name_.length() + 1 <= inStr.length());
      arg_value_ = inStr.substr(arg_name_.length() + 1, inStr.length());
    }
  }
  return {arg_name_, arg_value_};
}

std::vector<cxxctp::parsed_func> split_to_funcs(std::string const& inStr) {
  std::vector<cxxctp::parsed_func> result;
  std::stringstream ss;
  ss << inStr
    << ";"; // close funcs list with ';'

  std::string func_with_args_;
  std::string func_name_unprocessed_;
  std::string func_arg_as_str;
  bool is_in_args = false;
  std::vector<func_arg> func_args_vec_;
  std::map<std::string, std::vector<std::string>> func_args_as_name_to_value_;
  while (ss >> std::ws) {
      if (ss.peek() == '"') { // TODO: inner "
          std::string quoted;
          ss >> std::quoted(quoted);
          //std::cout << "quoted " << quoted << "\n";
          func_with_args_ += '"' + quoted + '"';
          if(is_in_args) {
            func_arg_as_str += '"' + quoted + '"';
          }
      }
      else if (ss.peek() == '(') {
          is_in_args = true;
          func_name_unprocessed_ = func_with_args_;
          char c;
          ss >> c;
          func_with_args_ += c;
          func_arg_as_str.clear();
      }
      else if (ss.peek() == ')') {
          is_in_args = false;

          func_arg arg_parsed = extract_func_arg(func_arg_as_str);
          func_args_vec_.push_back(arg_parsed);
          if(!arg_parsed.name_.empty()) {
            if(func_args_as_name_to_value_.find(arg_parsed.name_) != func_args_as_name_to_value_.end()) {
              func_args_as_name_to_value_[arg_parsed.name_].push_back(arg_parsed.value_);
            } else {
              func_args_as_name_to_value_[arg_parsed.name_] = std::vector{arg_parsed.value_};
            }
          }

          char c;
          ss >> c;
          func_with_args_ += c;
          func_arg_as_str.clear();
      }
      else if (ss.peek() == ',') {
          assert(is_in_args);

          func_arg arg_parsed = extract_func_arg(func_arg_as_str);
          func_args_vec_.push_back(arg_parsed);
          if(!arg_parsed.name_.empty()) {
            if(func_args_as_name_to_value_.find(arg_parsed.name_) != func_args_as_name_to_value_.end()) {
              func_args_as_name_to_value_[arg_parsed.name_].push_back(arg_parsed.value_);
            } else {
              func_args_as_name_to_value_[arg_parsed.name_] = std::vector{arg_parsed.value_};
            }
          }

          char c;
          ss >> c;
          func_with_args_ += c;
          func_arg_as_str.clear();
      }
      else if (ss.peek() == ';') {
          char c;
          ss >> c;

          if(func_with_args_.empty()) {
            continue;
          }

          //std::string func_name_normalized_ = func_name_unprocessed_;
          /// \note space, tabulator, newline, or the like will be removed
          //std::remove_if(func_name_normalized_.begin(), func_name_normalized_.end(),
          //  ::isspace);
          if(func_name_unprocessed_.empty()) {
            // func without args and without ()
            func_name_unprocessed_ = func_with_args_;
          }
          result.push_back(
            cxxctp::parsed_func{
              func_with_args_,
              {
                func_name_unprocessed_,
                //func_name_normalized_,
                args{
                  func_args_vec_,
                  func_args_as_name_to_value_
                },
              }
            });
          func_with_args_.clear();
          func_name_unprocessed_.clear();
          func_args_vec_.clear();
          func_arg_as_str.clear();
          func_args_as_name_to_value_.clear();
      } else {
          char c;
          ss >> c;
          func_with_args_ += c;
          if(is_in_args) {
            func_arg_as_str += c;
          }
      }

      //std::cout << func_with_args_ << "\n";
  }
  return result;
}

} // namespace cxxctp
