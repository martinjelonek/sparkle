#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "./Constants.h"
#include "./Entity.h"

class Event {
    private:
        EventType eventType;
        Entity* pEntityA;
        Entity* pEntityB;
    public:
        Event(EventType eventType, Entity& entityA, Entity& entityB);
        ~Event();
        EventType GetEventType() const;
};

#endif