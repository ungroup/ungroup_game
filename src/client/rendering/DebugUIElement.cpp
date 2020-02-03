#include "DebugUIElement.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "RenderingDef.hpp"

DebugUIElement::DebugUIElement(sf::Vector2u window_size, sf::Vector2f size,
                               RenderingDef::Align align, RenderingDef::Padding padding,
                               ResourceStore& rs) :
    BaseUIElement(window_size, size, align, padding),
    m_windowSize(window_size), m_align(align), m_padding(padding) {
    m_text.setFont(*rs.getFont(RenderingDef::FontKey::monogram));
    m_text.setString("NO DATA");
    m_text.setCharacterSize(RenderingDef::DEBUG_UI_TEXT_SIZE);
    m_text.setFillColor(RenderingDef::DEBUG_UI_TEXT_COLOR);
    m_text.setPosition(m_position);
}

void DebugUIElement::update(const UIData& ui_data) {
    std::stringstream stream;
    stream << "FPS: " << std::fixed << std::setprecision(0) << ui_data.game_steps_per_second << "\n"
           << "UPS: " << std::fixed << std::setprecision(0) << ui_data.game_updates_per_second
           << "\n"
           << "XPS: " << std::fixed << std::setprecision(0) << ui_data.network_updates_per_second
           << "\n"
           << "TDA: " << std::fixed << std::setprecision(0) << ui_data.tick_delta_average << "\n"
           << "TIK: " << ui_data.tick;
    m_text.setString(stream.str());

    // Update position according to text size
    sf::FloatRect bounds = m_text.getLocalBounds();
    BaseUIElement::setPosition(
        m_windowSize, {bounds.left + bounds.width, bounds.height + bounds.top}, m_align, m_padding);
    m_text.setPosition(m_position);
}

void DebugUIElement::draw(sf::RenderTarget& render_target) {
    render_target.draw(m_text);
}