#include "Session.h"
#include "PacketHandler.h"

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

				// If we have too much data stored already, clear the buffer
				if (m_receive_buffer.size() + len > BUF_SIZE * 2) {
					m_receive_buffer.clear();
					std::cout << "Receive buffer overflow, clearing buffer" << std::endl;
				}

				m_receive_buffer.insert(m_receive_buffer.end(), m_data, m_data + len);

				// Parse and handle the packet
				if (parse_packet(m_receive_buffer)) {
					// If a packet has been parsed, clear the buffer. //todo: handle multiple packets in buffer
					m_receive_buffer.clear();
				}

				read_data();
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
			}
			else {
				std::cout << "Read error: " << ec.message() << std::endl;
			}
		}
	);
}
