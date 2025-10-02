#pragma once

#include "Packet.h"
#include "PacketCodec.h"
#include "AllPackets.h"

#include <iostream>
#include <stdexcept>
#include <format>

bool parse_packet(const std::vector<char>& data) {

	std::cout << "Parsing packet of length " << data.size() << std::endl;
	// If the length is less than the size of the opcode and data length, don't process it
    if (data.size() < sizeof(PacketOpcode) + sizeof(uint16_t)) {
        return false;
    }

    Packet packet;
    std::memcpy(&packet.opcode, data.data(), sizeof(uint16_t));
	std::cout << "Packet opcode: " << static_cast<uint16_t>(packet.opcode) << std::endl;

	// Read the packet size
	std::memcpy(&packet.data_length, data.data() + sizeof(PacketOpcode), sizeof(uint16_t));
	std::cout << "Packet data length: " << packet.data_length << std::endl;

    if (data.size() - 2 * sizeof(uint16_t) < packet.data_length) {
        return false; // Not enough data for the full packet
	}

    // Copy the packet payload
    packet.data.assign(data.data() + 2 * sizeof(uint16_t), data.data() + packet.data_length + 2 * sizeof(uint16_t));

    return true;
}

void handle_incoming(const Packet& packet) {
    switch (static_cast<PacketOpcode>(packet.opcode)) {
        case PacketOpcode::ChatMessage: {
            ChatPacket chat = deserialise<ChatPacket>(packet.data);
			std::cout << "Received chat message from " << chat.senderId << ": " << chat.message << std::endl;
            break;
        }
        case PacketOpcode::ClickObject: {
            ClickObjectPacket click = deserialise<ClickObjectPacket>(packet.data);
            break;
        }

        default: {
            throw std::runtime_error(std::format("No packet decoder for opcode {}.", static_cast<uint16_t>(packet.opcode)));
            break;
        }
    }
}

