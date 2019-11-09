#ifndef game_def_hpp
#define game_def_hpp

#include <SFML/Graphics.hpp>

struct ClientInputKeys {
    sf::Keyboard::Key up, down, right, left, joinable, ungroup, stop;
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

enum ReliableCommandType { register_client, player_id, client_reliable_update };
enum UnreliableCommandType { client_unreliable_update, fetch_state };

enum GameObjectType { group, mine, player };

#endif /* game_def_hpp */
