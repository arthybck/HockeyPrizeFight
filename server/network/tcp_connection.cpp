#include "tcp_connection.hpp"

tcp_connection::pointer
tcp_connection::create(boost::asio::io_context &io_context) {
  return tcp_connection::pointer(new tcp_connection(io_context));
}

tcp::socket &tcp_connection::socket() { return socket_; }

void tcp_connection::start() { this->tcp_write("salut pédale\n"); }

tcp_connection::tcp_connection(boost::asio::io_context &io_context)
    : socket_(io_context) {}

void tcp_connection::handle_write(const boost::system::error_code &error,
                                  size_t bytes_transferred) {
  std::cout << "Sent " << bytes_transferred << " bytes. Error:: " << error
            << std::endl;
}

void tcp_connection::tcp_write(const std::string &message_) {
  boost::asio::async_write(
      socket_, boost::asio::buffer(message_),
      boost::bind(&tcp_connection::handle_write, shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}
