//
// Created by Daniel Laplana Gimeno on 26/5/25.
//

#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "core/Singleton.h"
#include "render/Renderer.h"


#include "imgui_internal.h"
#include "misc/cpp/imgui_stdlib.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

class UIManager : public SingletonManager<UIManager> {
private:
    bool _mainWindowOpen = true;
    bool _sceneHierarchyOpen = false;
    bool _showDemoWindow = false;
    ImVec2 _thumbnailSize = ImVec2(128, 128);

public:
    void Init() override;
    void Update() override;
    void Close() override;

    void DrawHierarchyPanel();
};



#endif //UIMANAGER_H
