#include "Onion.h"

void Onion::Init(){
    for(Layer* layer : _layers){
        layer->Init();
    }
}

void Onion::Update(){
    for(Layer* layer : _layers){
        layer->Update();
    }
}

void Onion::Close(){
    for(Layer* layer : _layers){
        layer->Close();
    }
}

// --------- Layer management ---------

void Onion::PushLayer(Layer* layer){
    _layers.push_back(layer);
}

void Onion::PopLayer(Layer* layer){
    _layers.erase(
        std::remove(_layers.begin(), _layers.end(), layer), 
        _layers.end()
    );
}