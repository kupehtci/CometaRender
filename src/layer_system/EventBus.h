#ifndef COMETA_EVENT_BUS_H
#define COMETA_EVENT_BUS_H

#include <vector>
#include <unordered_map>

#include "core/Singleton.h"

#include "Layer.h"
#include "Event.h"
#include "EventType.h"

class EventBus : Singleton<EventBus>{

private: 
    std::unordered_map<EventType, std::vector<Layer*>> _subscribers; 

public: 
    EventBus();

    void Subscribe(EventType eventType, Layer* layer);
    void Unsubscribe(EventType eventType, Layer* layer);

    void Notify(Event& event);
}; 

#endif