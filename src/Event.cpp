#include "./Event.h"

Event::Event(EventType eventType, int sceneToLoad) {
    this->eventType = eventType;
    this->sceneToLoad = sceneToLoad;
}

Event::Event(EventType eventType, std::string colliderTagA, std::string colliderTagB, int sceneToLoad) {
    this->eventType = eventType;
    this->colliderTagA = colliderTagA;
    this->colliderTagB = colliderTagB;
    this->sceneToLoad = sceneToLoad;
}

Event::~Event() {

}

EventType Event::GetEventType() const {
    return eventType;
}