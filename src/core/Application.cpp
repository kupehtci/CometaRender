//
// Created by Daniel Laplana Gimeno on 18/11/24.
//

#include "core/Application.h"

#include "layer_system/layers/MapsLayer.h"

#include "layer_system/layers/CometaLayer.h"
#include "layer_system/layers/MaterialLayer.h"

Application::Application(){
    this->_isRunning = true;
    _worldManager = nullptr;
    _renderer = nullptr; 
    _time = nullptr;
    _onion = Onion();
}

Application::~Application(){

}

void Application::Init(){
    // Create managers
    Time::Create();
    _time = Time::GetInstancePtr();

    WorldManager::Create();
    _worldManager = WorldManager::GetInstancePtr();

    Renderer::Create();
    _renderer = Renderer::GetInstancePtr();

    Input::Create(); 
    _input = Input::GetInstancePtr();

    // Push the layers
    // // Push cometa layer previous implementation
    //CometaLayer* cometaLayer = new CometaLayer();
    //_onion.PushLayer(cometaLayer);

    // // Push material layer used for materials
    // MaterialLayer* matLayer = new MaterialLayer();
    // _onion.PushLayer(matLayer);

    // Light maps testing
    MapsLayer* mapsLayer = new MapsLayer();
    _onion.PushLayer(mapsLayer);


    // Initialize managers
    _worldManager->Init();
    _renderer->Init();
    _time->Init();
    _input->Init();

    _onion.Init();
}

void Application::Running() {
    while(this->_isRunning){

        // Update the managers
        _time->Update();
        _worldManager->Update();
        _renderer->Update();
        _input->Update();

        _onion.Update();

        // Check if window must close
        if (_isRunning)
        {
            _isRunning = !_renderer->GetWindow()->ShouldHandleCloseWindow();
        }
    }
}

void Application::Close() {
    _input->Update();
    _renderer->Close();
    _worldManager->Close();
    _time->Close();

    COMETA_ASSERT("Application closed correctly");
}
