#ifndef CollisionUtil_hpp
#define CollisionUtil_hpp

#include <memory>
#include <stdio.h>

#include <SFML/Graphics.hpp>

#include "../objects/CircleRigidBody.hpp"
#include "PhysicsDef.hpp"

/**
 * Details of collision between two rigid bodies.
 * @ids: ids of the two rigid bodies.
 * @position: point of contact between the rigid bodies after collision is resolved.
 * @normal: normal of the collision from the latter body to the former.
 * @resolution: the amount by which the bodies should be displaced to resolve the collision.
 */
struct Collision {
    std::pair<uint32_t, uint32_t> ids;
    sf::Vector2f position;
    sf::Vector2f normal;
    std::pair<sf::Vector2f, sf::Vector2f> resolution;
    bool collided;
};

enum Orientation { above, below, left, right, inside };

namespace CollisionUtil {
    /**
     * Returns true if the two circle rigid bodies are intersecting (colliding).
     */
    bool areIntersecting(const CircleRigidBody& circle_a, const CircleRigidBody& circle_b);

    /**
     * Returns true if the circle and the rectangle are intersecting (colliding).
     */
    bool areIntersecting(const CircleRigidBody& circle, const sf::FloatRect& rectangle);

    /**
     * Returns true if the cricle and the line are intersecting.
     */
    bool areIntersecting(const CircleRigidBody& circle, std::pair<sf::Vector2f, sf::Vector2f> line);

    /**
     * Returns minimum distance between line segment vw and point p
     */
    float minimumDistance(const sf::Vector2f& v, const sf::Vector2f& w, const sf::Vector2f& p);

    /**
     * Returns where a point is located relative to a rectangle.
     * Precedence is given in the order inside, above, right, under, left.
     */
    Orientation getOrientation(const sf::Vector2f p, const sf::FloatRect& rectangle);

    /**
     * Returns infromation about the collision and how it should be resolved.
     * To resolve the collision between circle A and B, circle B should be moved in the
     * direction of the vector spanning from the center of cirlce A to the center of circle B by
     * the amount needed such that the circles are touching but not intersecting.
     */
    Collision getCollision(const CircleRigidBody& circle_a, const CircleRigidBody& circle_b);

    /**
     * The impulse generated by the circle rigid bodies colliding.
     * This impulse assumes a perfect elastic collision.
     * Formulas taken from http://www.chrishecker.com/Rigid_Body_Dynamics
     */
    std::pair<PhysicsDef::Impulse, PhysicsDef::Impulse> getImpulses(const CircleRigidBody& circle_a,
                                                                    const CircleRigidBody& circle_b,
                                                                    const Collision& collision);

    /**
     * Returns true if the entire circle is inside the "bounds" circle defined by bounds center and
     * radius.
     */
    bool isInBounds(const CircleRigidBody& circle, sf::Vector2f bounds_center, float bounds_radius);

    /**
     * Returns the amount to move a circle to get it back in bounds.
     */
    sf::Vector2f getBoundsCorrection(const CircleRigidBody& circle, sf::Vector2f bounds_center,
                                     float bounds_radius);
} // namespace CollisionUtil

#endif /* CollisionUtil_hpp */