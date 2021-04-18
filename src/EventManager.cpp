#include "./EventManager.h"
#include "./Constants.h"

EventManager::EventManager() {

}

EventManager::~EventManager() {

}

void EventManager::AddEvent(Event& event) {
    events.push_back(&event);
}

void EventManager::HandleEvent() {
    for (auto& event: events) {
        
    }
}