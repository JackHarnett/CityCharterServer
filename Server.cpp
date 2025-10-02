#include "Server.h"
#include <algorithm>

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
 void Server::cleanup_sessions() {
	m_sessions.erase(std::remove_if(m_sessions.begin(), m_sessions.end(),
		[](const std::unique_ptr<Session>& session) {
			return session->needsClose();
		}),
		m_sessions.end()
	);
}

 void Server::start() {
	accept_connection();
}
