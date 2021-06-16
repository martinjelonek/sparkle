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
    public:
        bool gameLost = false;
        bool gameWin = false;
        int sceneToLoad = 0;
        EventManager();
        ~EventManager();
        void AddCollisionEvent(EventType COLLISION, std::string colliderTagA, std::string colliderTagB, int sceneToLoad);
        void AddWinEvent(EventType WIN, int sceneToLoad);
        void HandleEvents();
        void DestroyAllEvents();
        unsigned int GetEventsSize() const;
};

#endif