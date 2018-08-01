#include <boost/archive/binary_oarchive.hpp>
#include <boost/asio.hpp>
#include <boost/serialization/serialization.hpp>
#include <iostream>

struct serializer {

  enum error_message { NONE, ERROR_NOT_FOUND };

  error_message error_;
  std::string message_;

  template <typename archive>
  void serialize(archive &ar, const unsigned /*version*/) {
    ar &error_;
    ar &message_;
  }
};
