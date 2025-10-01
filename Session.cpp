#include "Session.h"

 void Session::disconnect() {
	if (m_socket.is_open()) {
		asio::error_code ec;
		m_socket.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
		m_socket.close(ec);
	}
}

void Session::read_data() {
	m_socket.async_read_some(asio::buffer(m_data, BUF_SIZE),
		[this](const asio::error_code& ec, size_t len) {
			if (!ec) {
				std::cout << "Read " << len << " bytes from channel " << std::endl;
				write_data(len);
			}
			else {
				std::cout << "Read error: " << ec.message() << std::endl;
			}
		}
	);
}
 
void Session::write_data(size_t len) {
	asio::async_write(m_socket, asio::buffer(m_data, len),
		[this](const asio::error_code& ec, size_t l) {
			if (!ec) {
				std::cout << "Wrote " << l << " bytes to channel " << std::endl;
				read_data();
			}
			else {
				std::cout << "Read error: " << ec.message() << std::endl;
			}
		}
	);
}
