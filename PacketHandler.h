#pragma once

#include "Packet.h"
#include "PacketCodec.h"
#include "AllPackets.h"

#include <iostream>
#include <stdexcept>
#include <format>

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
            throw std::runtime_error(std::format("No packet decoder for opcode {}.", packet.opcode));
            break;
        }
    }
}

