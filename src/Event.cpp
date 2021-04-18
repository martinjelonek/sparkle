#include "./Event.h"

Event::Event(EventType eventType, Entity& entityA, Entity& entityB) {
    this->eventType = eventType;
    this->pEntityA = &entityA;
    this->pEntityB = &entityB;
}

Event::~Event() {

}

EventType Event::GetEventType() const {
    return eventType;
}