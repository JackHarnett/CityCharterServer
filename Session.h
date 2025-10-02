#pragma once
#include <asio.hpp>
#include <iostream>
#include <vector>

class Session
{

private:

	static constexpr size_t BUF_SIZE = 1024;

	asio::ip::tcp::socket m_socket;

	asio::strand<asio::io_context::executor_type> m_strand;

	// Buffer for single read operations
	char m_data[BUF_SIZE];

	// Buffer for assembling received data
	std::vector<char> m_receive_buffer;

public:
	 
	Session(asio::io_context& context, asio::ip::tcp::socket socket) :
		m_socket(std::move(socket)),
		m_strand(asio::make_strand(context)) { 
		m_receive_buffer.reserve(BUF_SIZE * 2); 
	}

	void read_data();

	void write_data(size_t len);

	void disconnect();

};

