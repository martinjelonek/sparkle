#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "./Event.h"
#include "./Constants.h"
#include <vector>
#include <string>

class Evant;

class EventManager {
    private:
        std::vector<Event*> events;
        void CollisionEventCheck(Event& event);
        bool CollisionResolve(std::string tagA, std::string tagB);
        void HandleCollisionEvent();
    public:
        bool gameStop = false;
        EventManager();
        ~EventManager();
        void AddCollisionEvent(EventType COLLISION, std::string colliderTagA, std::string colliderTagB);
        void HandleEvents();
        void DestroyAllEvents();
        unsigned int GetEventsSize() const;
};

#endif