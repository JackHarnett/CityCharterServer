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

	void accept_connection();

public:

	Server(asio::io_context& context, unsigned int port) :
		m_ioContext(context),
		m_acceptor(context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port))
	{};

	void start();

};