#include "./EventManager.h"

EventManager::EventManager() {

}

EventManager::~EventManager() {

}

void EventManager::AddCollisionEvent(EventType COLLISION, std::string colliderTagA, std::string colliderTagB) {
    Event *event = new Event(COLLISION, colliderTagA, colliderTagB);
    events.push_back(event);
}

void EventManager::HandleEvents() {
    for (unsigned int i = 0; i < events.size(); ) {
        if(events[i]->GetEventType() == COLLISION) {
            if ((events[i]->colliderTagA.compare("player") == 0 && events[i]->colliderTagB.compare("enemy") == 0) 
            || (events[i]->colliderTagA.compare("enemy") == 0 && events[i]->colliderTagB.compare("player") == 0)
            || (events[i]->colliderTagA.compare("player") == 0 && events[i]->colliderTagB.compare("enemy-projectile") == 0)
            || (events[i]->colliderTagA.compare("enemy-projectile") == 0 && events[i]->colliderTagB.compare("player") == 0)) {
                gameStop = true;    
            }
            delete events[i];
            events.erase(events.begin() + i);
        } else {
            ++i;
        }
    }
}

void EventManager::DestroyAllEvents() {
    for (auto& event: events) delete event;
    events.clear();
}

unsigned int EventManager::GetEventsSize() const {
    return events.size();
}

