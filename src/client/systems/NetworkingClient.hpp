#ifndef NetworkingClient_hpp
#define NetworkingClient_hpp

#include <time.h>

#include <atomic>
#include <memory>
#include <mutex>
#include <queue>
#include <stdio.h>
#include <thread>
#include <vector>

#include <SFML/Network.hpp>

#include "../../common/util/InputDef.hpp"
#include "../../common/util/StateDef.hpp"
#include "../../common/util/game_def.hpp"

class NetworkingClient {

  public:
    NetworkingClient(const std::string& server_ip, uint32_t server_tcp_port);
    ~NetworkingClient();

    /**
     * Establish a connection with the server and get back client's player id.
     * This function will stall until the player id is recieved.
     */
    uint32_t registerClientAndFetchPlayerId();

    /**
     * Get copy of latest game state recieved from the server.
     * Note that since game state packets can come out of order this value won't always be the
     * latest game state on the server.
     */
    GameState getLatestGameState();

    /**
     * Get latest game state tick.
     * Note that since game state packets can come out of order this value won't always be the
     * latest game state tick on the server.
     */
    uint32_t getLatestGameStateTick();

    int getClientId() const;

    /**
     * Push an unreliable input onto the stack to be sent to the server.
     */
    void pushUnreliableInput(InputDef::UnreliableInput unreliable_input);

    /**
     * Push a reliable input onto the stack to be sent to the server.
     */
    void pushReliableInput(InputDef::ReliableInput reliable_input);

    void incrementTick();
    uint32_t getTick() const;
    void setTick(uint32_t tick);

  private:
    // Sockets
    void createTcpSocket(unsigned short port);
    void createInputUdpSocket();
    void createStateUdpSocket();

    std::string m_serverIp;

    std::mutex m_tcpSocket_lock;
    std::unique_ptr<sf::TcpSocket> m_tcpSocket_t;

    std::mutex m_stateUdpSocket_lock;
    std::unique_ptr<sf::UdpSocket> m_stateUdpSocket;

    std::unique_ptr<sf::UdpSocket> m_inputUdpSocket;

    // Threads
    void unreliableSend();
    void unreliableRecv();
    void reliableSend();
    void reliableRecv();
    void natSend();

    std::thread m_reliableRecv;
    std::thread m_reliableSend;
    std::thread m_unreliableRecv;
    std::thread m_unreliableSend;
    std::thread m_natSend;

    std::atomic<bool> m_stopThreads_ta{false};

    // Methods
    /**
     * Send noop UDP to server for NAT table population.
     * Otherwise, in scenario where client has sent no UDP packets
     * server game state broadcasts will never reach client.
     */
    void sendNatPunch();

    /**
     * Send client inputs to server via UDP.
     */
    void sendUnreliableInput();

    /**
     * Send client inputs to server via TCP.
     */
    void sendReliableInput();

    /**
     * Establish a TCP connection with the server and get back a client id and tick.
     */
    void registerClient();
    void readRegistrationResponse();
    uint32_t fetchPlayerId();

    /**
     * Register callbacks for events.
     */
    void addEventListeners();

    // Misc
    std::atomic<int> m_clientId_ta{-1};
    std::atomic<uint32_t> m_tick_ta{0};

    std::mutex m_gameState_lock;
    GameState m_gameState_t;

    std::mutex m_unreliableInput_lock;
    InputDef::UnreliableInput m_unreliableInput_t;

    std::mutex m_reliableInputs_lock;
    std::queue<InputDef::ReliableInput> m_reliableInputs_t; // FIFO

    sf::Uint16 m_serverStateUdpPort = 0;
    sf::Uint16 m_serverInputUdpPort = 0;
};

#endif /* NetworkingClient_hpp */
