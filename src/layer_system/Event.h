#ifndef COMETA_EVENT_H
#define COMETA_EVENT_H

#include "EventType.h"

class Event{

private: 
    bool _handled = false;
    EventType _type;
public: 
    EventType GetEventType() { return _type; }
    bool HasBeenHandled() { return _handled; }

    void SetHandled() { _handled = true; }
}; 

#endif