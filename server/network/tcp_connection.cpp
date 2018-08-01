#include "./serializer.cpp"
#include "./tcp_connection.hpp"

tcp_connection::pointer
tcp_connection::create(boost::asio::io_context &io_context) {
  return tcp_connection::pointer(new tcp_connection(io_context));
}

tcp::socket &tcp_connection::socket() { return socket_; }

void tcp_connection::start() {
  tcp_read();
  tcp_write("Welcome\n");
}

tcp_connection::tcp_connection(boost::asio::io_context &io_context)
    : socket_(io_context) {}

void tcp_connection::handle_write(const boost::system::error_code &error,
                                  size_t bytes_transferred) {
  if (error)
    std::cout << "Send failed: " << error.message() << "\n";
  else
    std::cout << "Send succesful (" << bytes_transferred << " bytes)\n";
}

void tcp_connection::handle_read(const boost::system::error_code &error,
                                 size_t bytes_transferred) {

  if (error && error != boost::asio::error::eof) {
    std::cout << "Error: " << error.message() << "\n";
    return;
  }

  std::string messageP;
  {
    std::stringstream ss;
    ss << &read_message_;
    ss.flush();
    messageP = ss.str();
  }

  std::cout << "Received data from "
            << socket_.remote_endpoint().address().to_string() << " > "
            << messageP << std::endl;
  if (messageP == "test\n") {
    tcp_write("bien ouej le test mon gars\n");
  }
  tcp_read();
}

void tcp_connection::tcp_write(const std::string &message_) {
  serializer info;
  info.error_ = serializer::error_message::NONE;
  info.message_ = message_;

  {
    std::ostream os(&buf);
    boost::archive::binary_oarchive out_archive(os);
    out_archive << info;
  }

  boost::asio::async_write(
      socket_, buf,
      boost::bind(&tcp_connection::handle_write, shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::tcp_read() {
  boost::asio::async_read(
      socket_, read_message_, boost::asio::transfer_at_least(1),
      boost::bind(&tcp_connection::handle_read, shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}
