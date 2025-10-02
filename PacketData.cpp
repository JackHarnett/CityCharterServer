#pragma once
#include <string>
#include <vector>

enum class GameOpcode : uint16_t {
    ChatMessage = 1,
    ClickObject = 2,
};

struct Packet
{
	uint16_t opcode;
	std::vector<char> data;
};

struct ChatPacketData
{
	int senderId;
	char message[256];
};



