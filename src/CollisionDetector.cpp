#include "CollisionDetector.hpp"
#include <iostream>
#include "util.hpp"
#include "CollisionHandler.hpp"

CollisionDetector::CollisionDetector() {
    //
}

// TODO: Move collision handling out and make groups param const
void CollisionDetector::detectGroupCollisions(std::vector<Group*> groups) {
    for(Group* group_a: groups) {
        for(Group* group_b: groups) {
            if (group_a == group_b) {
                continue;
            }
            
            // detect collision
            float dist = distance(group_a->getPosition(), group_b->getPosition());
            if (dist < group_a->getRadius() + group_b->getRadius()) {
                std::cout << "Collision" << std::endl;
                handleGroupCollision(group_a, group_b);
            } else {
                std::cout << "Nothing" << std::endl;
            }
        }
    }
}
