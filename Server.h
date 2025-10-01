#pragma once
#include <vector>
#include <asio.hpp>
#include "Session.h"
#include <iostream>

class Server
{
private:

	std::vector<std::unique_ptr<Session>>  m_sessions;

	asio::io_context& m_ioContext;

	asio::ip::tcp::acceptor m_acceptor;

	void accept_connection() {
		m_acceptor.async_accept([this](const asio::error_code& ec, asio::ip::tcp::socket socket) {
			if (!ec) {
					std::cout << "Client Connected" << std::endl;
					m_sessions.push_back(std::make_unique<Session>(std::move(socket)));

					m_sessions.back()->read_data();

					// Start accepting sessions again
					accept_connection();
				}
				else {
					std::cout << "Accept error: " << ec.message() << std::endl;
				}
			}
		);
	}

public:

	Server(asio::io_context& context, unsigned int port) : m_ioContext(context), m_acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {}

	void start() {
		accept_connection();
	}

};

