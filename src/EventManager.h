#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "./Game.h"
#include "./Event.h"
#include <vector>

class EventManager {
    private:
        std::vector<Event*> events;
        void CollisionEventCheck(Event& event);
    public:
        EventManager();
        ~EventManager();
        void AddEvent(Event& event);
        void HandleEvent();
};

#endif