#ifndef TCP_connection_HPP_
#define TCP_connection_HPP_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {
public:
  typedef boost::shared_ptr<tcp_connection> pointer;

  static pointer create(boost::asio::io_context &);
  tcp::socket &socket();
  void start();
  void tcp_write(const std::string &);

private:
  void tcp_read();
  tcp_connection(boost::asio::io_context &);
  void handle_write(const boost::system::error_code &, size_t);
  void handle_read(const boost::system::error_code &, size_t);

  tcp::socket socket_;
  boost::asio::streambuf read_message_;
  boost::asio::streambuf buf;
};

#endif /* !TCP_connection_HPP_ */
