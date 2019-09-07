#include "network_util.hpp"

sf::Packet& operator <<(sf::Packet& packet, const UnreliableCommand& realtime_command) {
    return packet
        << realtime_command.client_id
        << realtime_command.command
        << realtime_command.tick;
}

sf::Packet& operator >>(sf::Packet& packet, UnreliableCommand& realtime_command) {
    return packet
        >> realtime_command.client_id
        >> realtime_command.command
        >> realtime_command.tick;
}


sf::Packet& operator <<(sf::Packet& packet, const ReliableCommand& api_command) {
    return packet
        << api_command.client_id
        << api_command.command
        << api_command.tick;
}

sf::Packet& operator >>(sf::Packet& packet, ReliableCommand& api_command) {
    return packet
        >> api_command.client_id
        >> api_command.command
        >> api_command.tick;
}

sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2f& vector_2f) {
    return packet
        << vector_2f.x
        << vector_2f.y;
}

sf::Packet& operator >>(sf::Packet& packet, sf::Vector2f& vector_2f) {
    return packet
        >> vector_2f.x
        >> vector_2f.y;
}


sf::Packet& operator <<(sf::Packet& packet, const PlayerId& player_id) {
    return packet
        << player_id.player_id;
}

sf::Packet& operator >>(sf::Packet& packet, PlayerId& player_id) {
    return packet
        >> player_id.player_id;
}
