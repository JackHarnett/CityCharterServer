#pragma once

#include "Packet.h"
#include "PacketCodec.h"
#include "AllPackets.h"

#include <iostream>
#include <stdexcept>
#include <format>

Packet parse_packet(const char* data, size_t length) {
    if (length < sizeof(PacketOpcode)) {
        throw std::runtime_error("Data too short to contain opcode.");
    }

    Packet packet;

	std::memcpy(&packet.opcode, data, sizeof(PacketOpcode));
	packet.data.insert(packet.data.end(), data + sizeof(PacketOpcode), data + length);
	packet.data_length = static_cast<uint16_t>(packet.data.size());

    return packet;
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

