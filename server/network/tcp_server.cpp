#include "tcp_server.hpp"

tcp_server::tcp_server(boost::asio::io_context &io_context)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), 27015)) {
  start_accept();
}

void tcp_server::start_accept() {
  tcp_connection::pointer new_connection =
      tcp_connection::create(acceptor_.get_executor().context());
  acceptor_.async_accept(new_connection->socket(),
                         boost::bind(&tcp_server::handle_accept, this,
                                     new_connection,
                                     boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection,
                               const boost::system::error_code &error) {
  if (!error) {
    new_connection->start();
    this->connection_list.push_back(new_connection);
    broadcast("broadcast\n");
  }

  start_accept();
}

void tcp_server::broadcast(const std::string &message_) {
  for (auto connection : this->connection_list) {
    connection->tcp_write(message_);
  }
}
