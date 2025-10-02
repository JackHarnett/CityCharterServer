#include "Server.h"
#include <algorithm>
#include <iostream>

void Server::accept_connection() {
	m_acceptor.async_accept([this](const asio::error_code& ec, asio::ip::tcp::socket socket) {
		if (!ec) {
			std::cout << "Client Connected" << std::endl;
			m_sessions.push_back(std::make_unique<Session>(m_ioContext, std::move(socket)));
			m_sessions.back()->read_data();

			accept_connection();
		}
		else {
			std::cout << "Accept error: " << ec.message() << std::endl;
		}
	});
}

 void Server::start() {
	std::cout << "Server started, waiting for connections..." << std::endl;
	accept_connection();
}
