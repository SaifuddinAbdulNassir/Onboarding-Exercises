#pragma once

// Standard includes
#include <stdexcept>

namespace TDD
{

  class DuplicatedTargetException : public std::runtime_error
  {
  public:
    DuplicatedTargetException(const std::string &message = "Duplicated target");
  };

} // namespace TDD
