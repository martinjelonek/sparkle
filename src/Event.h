#ifndef EVENT_H
#define EVENT_H

#include <string>
#include "./Constants.h"

class Event {
    private:
        EventType eventType;
    public:
        std::string colliderTagA;
        std::string colliderTagB;
        Event(EventType eventType, std::string colliderTagA, std::string colliderTagB);
        ~Event();
        EventType GetEventType() const;
};

#endif