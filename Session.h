#pragma once
#include <asio.hpp>
#include <iostream>

class Session
{

private:

	static constexpr size_t BUF_SIZE = 1024;

	asio::ip::tcp::socket m_socket;

	char m_data[BUF_SIZE];

	bool m_needsClose = false;

public:

	Session(asio::ip::tcp::socket socket) : m_socket(std::move(socket)) {};

	void disconnect();

	void read_data();

	void write_data(size_t len);

	bool needsClose() const { return m_needsClose; }

};

