#include "Entity.h"

uint32_t Entity::AvailableUid = 1;

Entity::Entity() {
    _uid = AvailableUid;
    AvailableUid++;
    _name = "Cometa" + _uid;
    // std::cout << "Entity::Entity() with UID: " << _uid << " Next available UID: " << AvailableUid << std::endl;
}

Entity::Entity(const std::string& name) {
    _uid = AvailableUid;
    AvailableUid++;
    _name = name;
    // std::cout << "Entity::Entity() name: " << _name << " with UID: " << _uid << " Next available UID: " << AvailableUid << std::endl;
}

Entity::~Entity()
{

}

