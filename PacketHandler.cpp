#include "PacketHandler.h"

 void PacketHandler::handle_incoming(const Packet& packet) {
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

void PacketHandler::read_packet(std::vector<char>& data) {
    try {
        // Check that there is enough data to read the opcode and length
        if (data.size() < sizeof(PacketOpcode) + sizeof(uint16_t)) {
            return;
        }

        // Read the opcode and length
        Packet packet;
        std::memcpy(&packet.opcode, data.data(), sizeof(uint16_t));
        std::memcpy(&packet.data_length, data.data() + sizeof(PacketOpcode), sizeof(uint16_t));

        // Check if there is enough data to read the packet data
        if (data.size() < header_size + packet.data_length) {
            return;
        }

        // Move data from the input buffer to the packet
        packet.data.assign(data.begin() + header_size, data.begin() + header_size + packet.data_length);

        // Remove the processed data from the input buffer
        data.erase(data.begin(), data.begin() + header_size + packet.data_length);

        handle_incoming(packet);
    }
    catch (const std::exception& e) {
        std::cerr << "Error reading packet: " << e.what() << std::endl;
    }
}
