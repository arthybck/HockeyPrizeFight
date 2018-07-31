#ifndef TCP_SERVER_HPP_
#define TCP_SERVER_HPP_
#include "./tcp_connection.hpp"

class tcp_server {
public:
  tcp_server(boost::asio::io_context &);

private:
  void start_accept();

  void handle_accept(tcp_connection::pointer,
                     const boost::system::error_code &);

  tcp::acceptor acceptor_;
};

#endif /* !TCP_SERVER_HPP_ */
