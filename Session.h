#pragma once
#include <asio.hpp>
#include <iostream>

class Session
{

private:

	static constexpr size_t BUF_SIZE = 1024;

	asio::ip::tcp::socket m_socket;

	asio::strand<asio::io_context::executor_type> m_strand;

	char m_data[BUF_SIZE];

	bool m_needsClose = false;


public:

	Session(asio::io_context& context, asio::ip::tcp::socket socket) : m_socket(std::move(socket)), m_strand(asio::make_strand(context)) {};

	void disconnect();

	void read_data();

	void write_data(size_t len);

	bool needsClose() const { return m_needsClose; }

};

