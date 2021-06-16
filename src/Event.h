#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "./Constants.h"

class Event {
    private:
        EventType eventType;
    public:
        int sceneToLoad;
        std::string colliderTagA;
        std::string colliderTagB;
        Event(EventType eventType, int sceneToLoad);
        Event(EventType eventType, std::string colliderTagA, std::string colliderTagB, int sceneToLoad);
        ~Event();
        EventType GetEventType() const;
};

#endif