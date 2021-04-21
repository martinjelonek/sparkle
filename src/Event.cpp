#include "./Event.h"

Event::Event(EventType eventType, std::string colliderTagA, std::string colliderTagB) {
    this->eventType = eventType;
    this->colliderTagA = colliderTagA;
    this->colliderTagB = colliderTagB;
}

Event::~Event() {

}

EventType Event::GetEventType() const {
    return eventType;
}