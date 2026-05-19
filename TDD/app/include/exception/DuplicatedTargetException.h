#pragma once

// Standard includes
#include <stdexcept>

namespace TDD
{

  class DuplicatedTargetException : public std::runtime_error
  {
  public:
    // Constructors & destructors
    DuplicatedTargetException(const std::string &message = "Duplicated target");
    virtual ~DuplicatedTargetException();
  };

} // namespace TDD
