#pragma once
#include <vector>
#include <string>
#include "Packet.h"

template<typename T>
T deserialise(const std::vector<char>& data) {
    if (constexpr (std::is_trivially_copyable_v<T>)) {
        T data;
        std::memcpy(&data, data.data(), sizeof(data));
        return data;
    }
    else {
        return deserialise(data);
    }
}

template<typename T>
std::vector<char> serialise(T data) {
    if (constexpr (std::is_trivially_copyable_v<T>)) {
        std::vector<char> buffer(sizeof(data));
        std::memcpy(buffer.data(), &data, sizeof(data));
        return buffer;
    }
    else {
        return serialise(data);
    }
}
