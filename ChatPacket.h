#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>

struct ChatPacket {
	int senderId;
	std::string message;
};

ChatPacket deserialise(const std::vector<char>& data) {
	ChatPacket msg;

	if(data.size() < sizeof(int) + sizeof(uint32_t)) {
		throw std::runtime_error("Data too short to contain ChatPacket");
	}

	// The first 32 bits are the length of the string
	uint32_t messageLength;
	std::memcpy(&messageLength, data.data(), sizeof(uint32_t));

	// The rest of the data is the string itself
	msg.message.assign(data.data() + sizeof(uint32_t), messageLength);

	return msg;
}

std::vector<char> serialise(const ChatPacket& packet) {
	std::vector<char> buffer;
	
	// Add the first 32 bits for the size of the string
	const char* messageLength = reinterpret_cast<const char*>(packet.message.size());
	buffer.insert(buffer.end(), messageLength, messageLength + sizeof(uint32_t));

	// Add the string data
	buffer.insert(buffer.end(), packet.message.begin(), packet.message.end());
}