#pragma once
#include <vector>
#include <string>

enum class PacketOpcode : uint16_t {
    ChatMessage = 1,
    ClickObject = 2,
};

struct Packet {
    PacketOpcode opcode;
    uint16_t data_length;
    std::vector<char> data;
};
