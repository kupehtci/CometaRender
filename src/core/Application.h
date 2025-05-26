#ifndef AURAGL_APPLICATION_H
#define AURAGL_APPLICATION_H

//#include "Singleton.h"
#include "render/Renderer.h"
#include "Time.h"
#include "input/Input.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "layer_system/Onion.h"
#include "world/WorldManager.h"

class Application : public Singleton<Application>{
    friend class Window;
    friend class Input;
    friend class Renderer;
    friend class WorldManager;

private :
    bool _isRunning;

    // references to singletons managers
    WorldManager* _worldManager;
    Renderer* _renderer;
    Time* _time; 
    Input* _input; 

    Onion _onion;

public:
    Application();
    ~Application();

public:
    void Init();
    void Running();
    void Close();

private:
    /**
     * Set isRunning to false so in next frame, application should close
     */
    void MustClose()
    {
        _isRunning = false;
    }
};


#endif //AURAGL_APPLICATION_H
