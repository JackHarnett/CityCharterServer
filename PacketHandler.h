#pragma once

#include "Packet.h"
#include "PacketCodec.h"
#include "AllPackets.h"

#include <iostream>
#include <stdexcept>
#include <format>
#include <optional>


class PacketHandler
{

private:
    static const size_t header_size = sizeof(PacketOpcode) + sizeof(uint16_t);

    static void handle_incoming(const Packet& packet);

public:
    static void read_packet(std::vector<char>& data);

};
