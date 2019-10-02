#ifndef game_def_hpp
#define game_def_hpp

#include <SFML/Graphics.hpp>

struct Keys {
    sf::Keyboard::Key up, down, left, right, group;
};

struct UnreliableCommand {
    sf::Uint32 client_id;
    sf::Uint32 command;
    sf::Uint32 tick;
};

struct ReliableCommand {
    sf::Uint32 client_id;
    sf::Uint32 command;
    sf::Uint32 tick;
};

struct PlayerId {
    sf::Uint32 player_id;
};

enum ReliableCommandType {register_client, player_id, client_reliable_update};
enum UnreliableCommandType {client_unreliable_update, fetch_state};

#endif /* game_def_hpp */