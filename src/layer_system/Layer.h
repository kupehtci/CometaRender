#ifndef COMETA_LAYER_H
#define COMETA_LAYER_H

#include <string>

#include "Event.h"

class Layer{
    // friend class Onion; 

protected: 
    std::string _name; 

public:

    ~Layer() {};

    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Close() = 0;

    virtual void HandleEvent(Event& event) = 0;
}; 

#endif
