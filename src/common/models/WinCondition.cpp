#include "WinCondition.hpp"

#include <iostream>

WinCondition::~WinCondition() {
}

WinCondition::WinCondition() {
    auto total_resource_requirements = WIN_CONDITION_RESOURCE_TOTAL;
    srand(time(NULL));

    // define amount of resources required for "primary" required resource
    size_t quantity_required_for_primary_resource =
        (total_resource_requirements / RESOURCE_TYPE_COUNT) * 2;
    total_resource_requirements -= quantity_required_for_primary_resource;
    // pick which resource player will need the most of
    size_t primary_resource = (rand() % RESOURCE_TYPE_COUNT);
    for (size_t i = 0; i < RESOURCE_TYPE_COUNT; i++) {
        if (i == primary_resource) {
            m_resourceCountsToWin[i] = quantity_required_for_primary_resource;
        } else {
            // make all other resources equal split (-1 is to exclude the primary resource)
            m_resourceCountsToWin[i] = total_resource_requirements / (RESOURCE_TYPE_COUNT - 1);
        }
    }
}

bool WinCondition::satisfiesCondition(
    std::array<uint32_t, RESOURCE_TYPE_COUNT> current_resources) const {
    for (size_t i = 0; i < RESOURCE_TYPE_COUNT; i++) {
        if (current_resources[i] < m_resourceCountsToWin[i]) {
            return false;
        }
    }
    return true;
}

const std::array<uint32_t, RESOURCE_TYPE_COUNT>& WinCondition::getResourceCountsToWin() const {
    return m_resourceCountsToWin;
}

void WinCondition::setResourceCountToWin(ResourceType resource_type, uint32_t count) {
    m_resourceCountsToWin[resource_type] = count;
}

sf::Packet& operator<<(sf::Packet& packet, WinCondition wc) {
    auto resourceCountsToWin = wc.getResourceCountsToWin();
    for (auto& count : resourceCountsToWin) {
        packet << static_cast<sf::Uint32>(count);
    }
    return packet;
}

sf::Packet& operator>>(sf::Packet& packet, WinCondition& wc) {
    for (size_t i = 0; i < RESOURCE_TYPE_COUNT; i++) {
        sf::Uint32 count;
        packet >> count;
        wc.setResourceCountToWin(ResourceType(i), count);
    }
    return packet;
}