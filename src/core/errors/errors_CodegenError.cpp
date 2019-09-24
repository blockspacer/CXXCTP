#include "core/errors/errors.hpp"

OUTCOME_CPP_DEFINE_CATEGORY(CXXCTP::core::errors, GeneratorError, e) {
  using CXXCTP::core::errors::GeneratorError;
  switch (e) {
    case GeneratorError::UNKNOWN_TAG:
      return "you need to specify valid key type";
    case GeneratorError::FILE_NOT_FOUND:
      return "file not found";
    case GeneratorError::FAILED_TO_READ_FILE:
      return "failed to read file";
    case GeneratorError::FAILED_TO_WRITE_FILE:
      return "failed to write file";
    case GeneratorError::EMPTY_INPUT:
      return "no input data";
    case GeneratorError::UNCLOSED_TAG:
      return "starting tag without ending tag";
  }
  return "unknown error";
}
