#pragma once
#include <vector>
#include <string>
#include "Packet.h"
#include "AllPackets.h"

template<typename T>
T deserialise(const std::vector<char>& bytes) { 
    if constexpr (std::is_trivially_copyable_v<T>) {
        T result;

        if (bytes.size() != sizeof(T)) {
            throw std::runtime_error("Invalid byte size for trivially copyable type.");
        }

        std::memcpy(&result, bytes.data(), sizeof(result));
        return result;
    }
    else {
        return deserialise(bytes);
    }
}

template<typename T>
std::vector<char> serialise(T data) {
    if constexpr (std::is_trivially_copyable_v<T>) {
        std::vector<char> buffer(sizeof(data));
        std::memcpy(buffer.data(), &data, sizeof(data));
        return buffer;
    }
    else {
        return serialise(data);
    }
}
