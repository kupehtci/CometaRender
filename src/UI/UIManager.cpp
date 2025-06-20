//
// Created by Daniel Laplana Gimeno on 26/5/25.
//

#include "UIManager.h"

void UIManager::Init() {
  std::cout << "UILayer::Init" << std::endl;

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(Renderer::GetInstancePtr()->GetWindow()->GetGlfwWindow(), true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();


    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // --- Backgrounds ---
    colors[ImGuiCol_WindowBg]         = ImVec4(0.09f, 0.10f, 0.13f, 1.00f); // #181A20
    colors[ImGuiCol_ChildBg]          = ImVec4(0.13f, 0.14f, 0.19f, 1.00f); // #232530
    colors[ImGuiCol_PopupBg]          = ImVec4(0.13f, 0.14f, 0.19f, 0.98f);
    colors[ImGuiCol_Border]           = ImVec4(0.18f, 0.20f, 0.25f, 0.60f); // subtle border
    colors[ImGuiCol_BorderShadow]     = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

    // --- Text ---
    colors[ImGuiCol_Text]             = ImVec4(0.88f, 0.88f, 0.90f, 1.00f); // #E0E0E0
    colors[ImGuiCol_TextDisabled]     = ImVec4(0.45f, 0.48f, 0.53f, 1.00f); // muted gray

    // --- Frames & Panels ---
    colors[ImGuiCol_FrameBg]          = ImVec4(0.16f, 0.18f, 0.23f, 1.00f); // #282A36
    colors[ImGuiCol_FrameBgHovered]   = ImVec4(0.20f, 0.22f, 0.29f, 1.00f);
    colors[ImGuiCol_FrameBgActive]    = ImVec4(0.22f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_TitleBg]          = ImVec4(0.13f, 0.14f, 0.19f, 1.00f);
    colors[ImGuiCol_TitleBgActive]    = ImVec4(0.16f, 0.18f, 0.23f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.14f, 0.19f, 0.75f);
    colors[ImGuiCol_MenuBarBg]        = ImVec4(0.13f, 0.14f, 0.19f, 1.00f);

    // --- Scrollbar ---
    colors[ImGuiCol_ScrollbarBg]      = ImVec4(0.13f, 0.14f, 0.19f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]    = ImVec4(0.22f, 0.24f, 0.32f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.27f, 0.29f, 0.39f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(0.32f, 0.35f, 0.47f, 1.00f);

    // --- Check/Radio/Slider ---
    colors[ImGuiCol_CheckMark]        = ImVec4(0.50f, 0.80f, 1.00f, 1.00f); // blue accent
    colors[ImGuiCol_SliderGrab]       = ImVec4(0.50f, 0.80f, 1.00f, 0.70f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);

    // --- Buttons ---
    colors[ImGuiCol_Button]           = ImVec4(0.16f, 0.18f, 0.23f, 1.00f);
    colors[ImGuiCol_ButtonHovered]    = ImVec4(0.31f, 0.49f, 0.67f, 0.80f); // blue highlight
    colors[ImGuiCol_ButtonActive]     = ImVec4(0.50f, 0.80f, 1.00f, 1.00f); // blue accent

    // --- Headers (tree, table, etc) ---
    colors[ImGuiCol_Header]           = ImVec4(0.20f, 0.22f, 0.29f, 1.00f);
    colors[ImGuiCol_HeaderHovered]    = ImVec4(0.31f, 0.49f, 0.67f, 0.80f);
    colors[ImGuiCol_HeaderActive]     = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);

    // --- Tabs ---
    colors[ImGuiCol_Tab]              = ImVec4(0.16f, 0.18f, 0.23f, 1.00f);
    colors[ImGuiCol_TabHovered]       = ImVec4(0.31f, 0.49f, 0.67f, 0.80f);
    colors[ImGuiCol_TabActive]        = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_TabUnfocused]     = ImVec4(0.13f, 0.14f, 0.19f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive]= ImVec4(0.16f, 0.18f, 0.23f, 1.00f);

    // --- Separators/Resize ---
    colors[ImGuiCol_Separator]        = ImVec4(0.18f, 0.20f, 0.25f, 0.60f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.31f, 0.49f, 0.67f, 0.80f);
    colors[ImGuiCol_SeparatorActive]  = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_ResizeGrip]       = ImVec4(0.31f, 0.49f, 0.67f, 0.25f);
    colors[ImGuiCol_ResizeGripHovered]= ImVec4(0.31f, 0.49f, 0.67f, 0.67f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);

    // --- Plots ---
    colors[ImGuiCol_PlotLines]        = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.31f, 0.49f, 0.67f, 1.00f);
    colors[ImGuiCol_PlotHistogram]    = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered]= ImVec4(0.31f, 0.49f, 0.67f, 1.00f);

    // --- Misc ---
    colors[ImGuiCol_TextSelectedBg]   = ImVec4(0.31f, 0.49f, 0.67f, 0.35f);
    colors[ImGuiCol_DragDropTarget]   = ImVec4(0.50f, 0.80f, 1.00f, 0.90f);
    colors[ImGuiCol_NavHighlight]     = ImVec4(0.50f, 0.80f, 1.00f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.50f, 0.80f, 1.00f, 0.70f);
    colors[ImGuiCol_NavWindowingDimBg]= ImVec4(0.09f, 0.10f, 0.13f, 0.20f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.09f, 0.10f, 0.13f, 0.35f);

    // --- Style tweaks for a modern look ---
    style.WindowRounding    = 6.0f;
    style.ChildRounding     = 4.0f;
    style.FrameRounding     = 4.0f;
    style.PopupRounding     = 4.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding      = 4.0f;
    style.TabRounding       = 4.0f;
    style.WindowBorderSize  = 1.0f;
    style.FrameBorderSize   = 1.0f;
    style.PopupBorderSize   = 1.0f;
    style.TabBorderSize     = 1.0f;
    style.WindowPadding     = ImVec2(8, 8);
    style.FramePadding      = ImVec2(5, 4);
    style.ItemSpacing       = ImVec2(6, 6);
    style.ItemInnerSpacing  = ImVec2(6, 6);
    style.IndentSpacing     = 21.0f;
    style.ScrollbarSize     = 12.0f;
    style.GrabMinSize       = 8.0f;
    style.WindowTitleAlign  = ImVec2(0.5f, 0.5f);
    style.WindowMenuButtonPosition = ImGuiDir_Right;

}

void UIManager::Update()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_MenuBar;
    // | ImGuiConfigFlags_DockingEnable;

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed |
                           ImGuiTreeNodeFlags_SpanAvailWidth |
                           ImGuiTreeNodeFlags_FramePadding;



    if (ImGui::Begin("Cometa", &_mainWindowOpen, windowFlags)){

        

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Scene utils"))
            {
                if (ImGui::MenuItem("Show scene hierarchy"))
                {
                    ImGui::Text("Hierarchy");
                    _sceneHierarchyOpen  = !_sceneHierarchyOpen;
                }
                if (ImGui::MenuItem("Toggle ImGui Demo", nullptr, _showDemoWindow))
                {
                    _showDemoWindow = !_showDemoWindow;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }



        ImGui::SeparatorText("Time");
        ImGui::Text("Current DeltaTime %f", Time::GetDeltaTime());
        ImGui::Text("Current Time Scale %f", Time::GetTimeScale());
        ImGui::Text("Current Accumulated Time %f", Time::GetAccumulatedTime());
        



        // --- FPS and DeltaTime stats ---
        static std::deque<float> frameTimes;
        static std::deque<float> frameTimestamps;
        static float minFPS = 0.0f, maxFPS = 0.0f, minDelta = 0.0f, maxDelta = 0.0f, avgFPS = 0.0f;
        float deltaTime = Time::GetDeltaTime();
        float t = Time::GetAccumulatedTime();
        frameTimes.push_back(deltaTime);
        frameTimestamps.push_back(t);
        // Remove frames older than 10 seconds
        while (!frameTimestamps.empty() && t - frameTimestamps.front() > 10.0f) {
            frameTimestamps.pop_front();
            frameTimes.pop_front();
        }
        if (!frameTimes.empty()) {
            minDelta = *std::min_element(frameTimes.begin(), frameTimes.end());
            maxDelta = *std::max_element(frameTimes.begin(), frameTimes.end());
            minFPS = 1.0f / maxDelta;
            maxFPS = 1.0f / minDelta;
            float sum = 0.0f;
            for (float dt : frameTimes) sum += dt;
            avgFPS = frameTimes.size() / sum;
        }

        ImGui::SeparatorText("Performance");
        ImGui::Text("FPS: %.1f", 1.0f / deltaTime);
        ImGui::Text("Avg FPS (10s): %.1f", avgFPS);
        ImGui::Text("Min FPS (10s): %.1f", minFPS);
        ImGui::Text("Max FPS (10s): %.1f", maxFPS);
        ImGui::Text("Avg Delta (10s): %.4f s", 1 / avgFPS);
        ImGui::Text("Min Delta (10s): %.4f s", minDelta);
        ImGui::Text("Max Delta (10s): %.4f s", maxDelta);



        DrawHierarchyPanel();

        if (_showDemoWindow) {
            ImGui::ShowDemoWindow(&_showDemoWindow);
        }

        ImGui::End();
    }


    // ------------ SCENE HIERARCHY ------------




    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::Close()
{

}

void UIManager::DrawHierarchyPanel()
{
   // Display Renderer information
        ImGui::SeparatorText("Renderer");

        // Get renderer instance
        Renderer* renderer = Renderer::GetInstancePtr();

        // Display Directional Light
        if (ImGui::TreeNode("Directional Light"))
        {
            std::shared_ptr<DirectionalLight>& dirLight = renderer->GetDirectionalLight();

            if (dirLight)
            {
                // Directional Light direction
                float direction[3] = {dirLight->GetDirection().x, dirLight->GetDirection().y, dirLight->GetDirection().z};
                if (ImGui::DragFloat3("Direction", direction, 0.1f)) {
                    dirLight->SetDirection(glm::vec3(direction[0], direction[1], direction[2]));
                }

                // Directional Light ambient
                float ambientDirLight[3] = {dirLight->GetAmbient().x, dirLight->GetAmbient().y, dirLight->GetAmbient().z};
                if (ImGui::DragFloat3("Ambient", ambientDirLight, 0.01f, 0.0f, 1.0f)) {
                    dirLight->SetAmbient(glm::vec3(ambientDirLight[0], ambientDirLight[1], ambientDirLight[2]));
                }

                // Directional Light diffuse
                float diffuseDirLight[3] = {dirLight->GetDiffuse().x, dirLight->GetDiffuse().y, dirLight->GetDiffuse().z};
                if (ImGui::DragFloat3("Diffuse", diffuseDirLight, 0.01f, 0.0f, 1.0f)) {
                    dirLight->SetDiffuse(glm::vec3(diffuseDirLight[0], diffuseDirLight[1], diffuseDirLight[2]));
                }

                // Directional Light specular
                float specularDirLight[3] = {dirLight->GetSpecular().x, dirLight->GetSpecular().y, dirLight->GetSpecular().z};
                if (ImGui::DragFloat3("Specular", specularDirLight, 0.1f, 0.0f, 1.0f)){
                    dirLight->SetSpecular(glm::vec3(specularDirLight[0], specularDirLight[1], specularDirLight[2]));
                }
            }
            else
            {
                ImGui::Text("No directional light in the scene");
            }

            ImGui::TreePop();
        }

        // Display Point Lights
        if (ImGui::TreeNode("Point Lights"))
        {
            std::vector<std::shared_ptr<PointLight>>& pointLights = renderer->GetPointLights();

            if (!pointLights.empty())
            {
                for (size_t i = 0; i < pointLights.size(); i++)
                {
                    std::string lightName = "Point Light " + std::to_string(i);
                    if (ImGui::TreeNode(lightName.c_str()))
                    {
                        auto& pointLight = pointLights[i];
                        Transform* transform = pointLight->GetTransform();

                        // Position (from transform)
                        if (transform)
                        {
                            float position[3] = {transform->position.x, transform->position.y, transform->position.z};
                            if (ImGui::DragFloat3("Position", position, 0.1f))
                            {
                                transform->position.x = position[0];
                                transform->position.y = position[1];
                                transform->position.z = position[2];
                            }
                        }

                        // Light properties
                        ImGui::SeparatorText("Light properties");

                        float ambientPointLight[3] = {pointLight->GetAmbient().x, pointLight->GetAmbient().y, pointLight->GetAmbient().z};
                        if (ImGui::DragFloat3("Ambient", ambientPointLight, 0.01f)){
                            pointLight->SetAmbient(glm::vec3(ambientPointLight[0], ambientPointLight[1], ambientPointLight[2]));
                        }

                        float diffusePointLight[3] = {pointLight->GetDiffuse().x, pointLight->GetDiffuse().y, pointLight->GetDiffuse().z};
                        if (ImGui::DragFloat3("Diffuse", diffusePointLight, 0.01f)){
                            pointLight->SetDiffuse(glm::vec3(diffusePointLight[0], diffusePointLight[1], diffusePointLight[2]));
                        }

                        float specularPointLight[3] = {pointLight->GetSpecular().x, pointLight->GetSpecular().y, pointLight->GetSpecular().z};
                        if (ImGui::DragFloat3("Specular", specularPointLight, 0.01f)){
                            pointLight->SetSpecular(glm::vec3(specularPointLight[0], specularPointLight[1], specularPointLight[2]));
                        }

                        // Attenuation
                        ImGui::SeparatorText("Attenuation");

                        float constant = pointLight->GetConstant();
                        if (ImGui::DragFloat("Constant", &constant, 0.01f)){
                            pointLight->SetConstant(constant);
                        }

                        float linear = pointLight->GetLinear();
                        if (ImGui::DragFloat("Linear", &linear, 0.01f)){
                            pointLight->SetLinear(linear);
                        }

                        float quadratic = pointLight->GetQuadratic();
                        if (ImGui::DragFloat("Quadratic", &quadratic, 0.01f)){
                            pointLight->SetQuadratic(quadratic);
                        }

                        // Plot graphical representation of the attenuation
                        float att[] = {constant + linear * 1 + quadratic * 1,
                                      constant + linear * 3 + quadratic * 9,
                                      constant + linear * 5 + quadratic * 25,
                                      constant + linear * 10 + quadratic * 100,
                                      constant + linear * 20 + quadratic * 400,
                                      constant + linear * 40 + quadratic * 1600,
                                      constant + linear * 60 + quadratic * 3600};
                        ImGui::PlotLines("Attenuation graph", att, IM_ARRAYSIZE(att));

                        ImGui::TreePop();
                    }
                }
            }
            else
            {
                ImGui::Text("No point lights in the scene");
            }

            ImGui::TreePop();
        }

        // Display Renderables
        if (ImGui::TreeNode("Renderables"))
        {
            std::vector<std::shared_ptr<Renderable>>& renderables = renderer->GetRenderables();

            if (!renderables.empty())
            {
                for (size_t i = 0; i < renderables.size(); i++)
                {
                    std::string renderableName = "Renderable " + std::to_string(i);
                    if (ImGui::TreeNode(renderableName.c_str()))
                    {
                        auto& renderable = renderables[i];
                        Transform* transform = renderable->GetTransform();

                        // Transform component
                        if (transform && ImGui::TreeNode("Transform"))
                        {
                            // Position
                            float position[3] = {transform->position.x, transform->position.y, transform->position.z};
                            if (ImGui::DragFloat3("Position", position, 0.1f))
                            {
                                transform->position.x = position[0];
                                transform->position.y = position[1];
                                transform->position.z = position[2];
                            }

                            // Rotation
                            float rotation[3] = {transform->rotation.x, transform->rotation.y, transform->rotation.z};
                            if (ImGui::DragFloat3("Rotation", rotation, 0.1f))
                            {
                                transform->rotation.x = rotation[0];
                                transform->rotation.y = rotation[1];
                                transform->rotation.z = rotation[2];
                            }

                            // Scale
                            float scale[3] = {transform->scale.x, transform->scale.y, transform->scale.z};
                            if (ImGui::DragFloat3("Scale", scale, 0.05f))
                            {
                                transform->scale.x = scale[0];
                                transform->scale.y = scale[1];
                                transform->scale.z = scale[2];
                            }

                            ImGui::Text("Parent Transform: ");
                            transform->GetParent() != nullptr ? ImGui::Text("Has parent") : ImGui::Text("none");

                            ImGui::TreePop();
                        }

                        // Mesh component
                        std::shared_ptr<Mesh> mesh = renderable->GetMesh();
                        if (mesh && ImGui::TreeNode("Mesh"))
                        {
                            ImGui::SeparatorText("Mesh properties");
                            ImGui::Text("Vertices: %d", mesh->GetNumVertices());
                            ImGui::Text("Indices: %d", mesh->GetNumIndices());
                            ImGui::Text("VAO ID: %u", mesh->GetVertexArray()->GetUid());
                            ImGui::Text("EBO ID: %u", mesh->GetVertexArray()->GetIndexBuffer()->GetUid());

                            std::vector<std::shared_ptr<VertexBuffer>> vbos = mesh->GetVertexArray()->GetVertexBuffers();
                            ImGui::Text("Vertex Buffers: %u", vbos.size());
                            for (unsigned int j = 0; j < vbos.size(); j++)
                            {
                                ImGui::Text("\t VBO [%u] UID: %u", j, vbos[j]->GetUid());
                            }

                            ImGui::Dummy(ImVec2(0, 10));
                            ImGui::SeparatorText("Layout Buffer");
                            ImGui::Text("%s", mesh->GetVertexArray()->GetLayoutBuffer().ToString().c_str());

                            ImGui::TreePop();
                        }

                        // Material component
                        std::shared_ptr<Material> material = renderable->GetMaterial();
                        if (material && ImGui::TreeNode("Material"))
                        {
                            ImGui::SeparatorText("Material properties");

                            float color[3] = {material->GetColor().x, material->GetColor().y, material->GetColor().z};
                            if (ImGui::ColorPicker3("", color, ImGuiColorEditFlags_Float)){
                                material->SetColor(glm::vec3(color[0], color[1], color[2]));
                            }

                            float shine = material->GetShininess();
                            if (ImGui::SliderFloat("Shininess", &shine, 0.0f, 256.0f))
                            {
                                material->SetShininess(shine);
                            }

                            // Material maps
                            if (material->GetDiffuseMap())
                            {
                                ImGui::SeparatorText("DIFFUSE MAP");
                                ImGui::Text("Path: %s", material->GetDiffuseMap()->GetPath().c_str());
                                ImGui::Text("Resolution: %d x %d", material->GetDiffuseMap()->GetWidth(), material->GetDiffuseMap()->GetHeight());
                                ImGui::Image(material->GetDiffuseMap()->GetUID(), _thumbnailSize);
                            }

                            if (material->GetSpecularMap())
                            {
                                ImGui::SeparatorText("SPECULAR MAP");
                                ImGui::Text("Path: %s", material->GetSpecularMap()->GetPath().c_str());
                                ImGui::Text("Resolution: %d x %d", material->GetSpecularMap()->GetWidth(), material->GetSpecularMap()->GetHeight());
                                ImGui::Image(material->GetSpecularMap()->GetUID(), _thumbnailSize);
                            }

                            if (material->GetEmissionMap())
                            {
                                ImGui::SeparatorText("EMISSION MAP");
                                ImGui::Text("Path: %s", material->GetEmissionMap()->GetPath().c_str());
                                ImGui::Text("Resolution: %d x %d", material->GetEmissionMap()->GetWidth(), material->GetEmissionMap()->GetHeight());
                                ImGui::Image(material->GetEmissionMap()->GetUID(), _thumbnailSize);
                            }

                            // Shader
                            std::shared_ptr<Shader> shader = material->GetShader();
                            if (shader)
                            {
                                ImGui::SeparatorText("SHADER");
                                ImGui::Text("Shader UID: %u", shader->GetShaderUID());

                                ImGui::Text("Vertex Shader");
                                ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.0f, 0.3f, 1.0f));
                                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
                                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));

                                ImGui::BeginChild("Vertex shader source code", ImVec2(0, 300), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);
                                ImGui::TextUnformatted(shader->GetSourceCode(GL_VERTEX_SHADER).c_str());
                                ImGui::EndChild();

                                ImGui::PopStyleColor(1);
                                ImGui::Dummy(ImVec2(0, 10));
                                ImGui::Text("Fragment Shader");
                                ImGui::Dummy(ImVec2(0, 10));
                                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

                                ImGui::BeginChild("Fragment shader source code", ImVec2(0, 300), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);
                                ImGui::TextUnformatted(shader->GetSourceCode(GL_FRAGMENT_SHADER).c_str());
                                ImGui::EndChild();

                                ImGui::PopStyleColor(3);
                                ImGui::PopStyleVar(1);
                            }

                            ImGui::TreePop();
                        }

                        ImGui::TreePop();
                    }
                }
            }
            else
            {
                ImGui::Text("No renderables in the scene");
            }

            ImGui::TreePop();
        }
}
