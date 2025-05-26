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


    ImGuiStyle* style = &ImGui::GetStyle();

    // Fonst assign
    float fontSize = 15.0f;
    io.Fonts->AddFontFromFileTTF("resources/Fonts/jetbrains/JetBrainsMonoNL-Regular.ttf", fontSize);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("resources/Fonts/jetbrains/JetBrainsMonoNL-Regular.ttf", fontSize);

    style->WindowPadding = ImVec2(15, 15);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(5, 5);
    style->FrameRounding = 4.0f;
    style->ItemSpacing = ImVec2(12, 8);
    style->ItemInnerSpacing = ImVec2(8, 6);
    style->IndentSpacing = 25.0f;
    style->ScrollbarSize = 15.0f;
    style->ScrollbarRounding = 9.0f;
    style->GrabMinSize = 5.0f;
    style->GrabRounding = 3.0f;

    style->ScaleAllSizes(0.3f);

    //style->ChildRounding = 3.0f;
    //style->ChildBorderSize = 15.0f;



    style->Colors[ImGuiCol_Text] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.40f, 0.39f, 0.38f, 0.77f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.70f);
    // style->Colors[ImGuiCol_ChildWindowBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.58f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.92f, 0.91f, 0.88f, 0.92f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.84f, 0.83f, 0.80f, 0.65f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.99f, 1.00f, 0.40f, 0.78f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(1.00f, 0.98f, 0.95f, 0.47f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.21f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.90f, 0.91f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    // style->Colors[ImGuiCol_ComboBg] = ImVec4(1.00f, 0.98f, 0.95f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.25f, 1.00f, 0.00f, 0.80f);

    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);

    style->Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 0.14f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.99f, 1.00f, 0.22f, 0.86f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);

    style->Colors[ImGuiCol_Header] = ImVec4(0.655f, 0.627f, 0.741f, 0.76f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.655f, 0.627f, 0.741f, 0.86f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.655f, 0.627f, 0.741f, 1.00f);

    // style->Colors[ImGuiCol_Column] = ImVec4(0.00f, 0.00f, 0.00f, 0.32f);
    /*style->Colors[ImGuiCol_ColumnHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ColumnActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);*/
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.04f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 1.00f, 0.00f, 0.78f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
   /* style->Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
    style->Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
    style->Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);*/
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    //style->Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);

    // Set viewport
    // ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
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

                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }



        ImGui::SeparatorText("Time");
        ImGui::Text("Current DeltaTime %f", Time::GetDeltaTime());
        ImGui::Text("Current Time Scale %f", Time::GetTimeScale());


        DrawHierarchyPanel();

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
    ImGuiWindowFlags windowFlags = ImGuiWindowFlags_None
    | ImGuiWindowFlags_NoCollapse
    | ImGuiWindowFlags_MenuBar;

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Framed |
                           ImGuiTreeNodeFlags_SpanAvailWidth |
                           ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_Framed;

    if (_sceneHierarchyOpen && ImGui::Begin("Scene Hierarchy", &_sceneHierarchyOpen, windowFlags))
    {


            // Create a tree node for each entity
            std::string entityName = entity.GetName();
            if (entityName.empty()) {
                entityName = "Entity " + std::to_string(entity.GetUID());
            }

            if (ImGui::TreeNodeEx(entityName.c_str(), flags))
            {
                // Display entity UID
                ImGui::Text("UID: %u", entity.GetUID());

                // Display Transform component if it exists
                Transform* transform = entity.GetComponent<Transform>();
                if (transform)
                {
                    if (ImGui::TreeNode("Transform"))
                    {

                        // POSITION
                        float position[3] = { transform->position.x, transform->position.y, transform->position.z };
                        if (ImGui::DragFloat3("Position", position, 0.1f))
                        {
                            transform->position.x = position[0];
                            transform->position.y = position[1];
                            transform->position.z = position[2];
                        }

                        // ROTATION
                        float rotation[3] = { transform->rotation.x, transform->rotation.y, transform->rotation.z };
                        if (ImGui::DragFloat3("Rotation", rotation, 0.1f))
                        {
                            transform->rotation.x = rotation[0];
                            transform->rotation.y = rotation[1];
                            transform->rotation.z = rotation[2];
                        }

                        // SCALE
                        float scale[3] = { transform->scale.x, transform->scale.y, transform->scale.z };
                        if (ImGui::DragFloat3("Scale", scale, 0.05f)) {
                            transform->scale.x = scale[0];
                            transform->scale.y = scale[1];
                            transform->scale.z = scale[2];
                        }

                        ImGui::Text("Parent Transform: ");
                        transform->GetParent() != nullptr ? ImGui::Text("Parent Transform UID: %u", transform->GetParent()->GetOwner()->GetUID()) : ImGui::Text("none");

                        ImGui::TreePop();
                    }
                }

                // Display MeshRenderable component if it exists
                MeshRenderable* meshRenderable = entity.GetComponent<MeshRenderable>();
                if (meshRenderable)
                {
                    if (ImGui::TreeNode("MeshRenderable"))
                    {
                        ImGui::Text("Has Material: %s", meshRenderable->GetMaterial() ? "Yes" : "No");
                        ImGui::Text("Has Mesh: %s", meshRenderable->GetMesh() ? "Yes" : "No");
                        ImGui::Dummy(ImVec2(0,10));

                        // Mesh Block
                        if (ImGui::TreeNode("Mesh"))
                        {
                            std::shared_ptr<Mesh> mesh = meshRenderable->GetMesh();
                            if (mesh)
                            {
                                ImGui::SeparatorText("Mesh properties");
                                ImGui::Text("Vertices: %d", mesh->GetNumVertices());
                                ImGui::Text("Indices: %d", mesh->GetNumIndices());
                                ImGui::Text("VAO ID: %u" , mesh->GetVertexArray()->GetUid());
                                ImGui::Text("EBO ID: %u" , mesh->GetVertexArray()->GetIndexBuffer()->GetUid());
                                std::vector<std::shared_ptr<VertexBuffer>> vbos = mesh->GetVertexArray()->GetVertexBuffers();
                                ImGui::Text("Vertex Buffers: %u", vbos.size());
                                unsigned int i = 0;
                                for (auto vbo : vbos)
                                {
                                    ImGui::Text("\t VBO [%u] UID: %u", i, vbo->GetUid());
                                }
                                ImGui::Dummy(ImVec2(0,10));

                                ImGui::SeparatorText("Layout Buffer");
                                ImGui::Text("%s", mesh->GetVertexArray()->GetLayoutBuffer().ToString().c_str());
                                ImGui::Dummy(ImVec2(0,10));

                                ImGui::TreePop();
                            }
                            else
                            {
                                ImGui::Text("No mesh");
                            }
                        }

                        // Material Block
                        if (ImGui::TreeNode("Material"))
                        {
                            std::shared_ptr<Material> material = meshRenderable->GetMaterial();
                            if (material)
                            {

                                // Texture properties
                                ImGui::SeparatorText("Material properties");

                                float color[3] = {material->GetColor().x, material->GetColor().y, material->GetColor().z};
                                if (ImGui::ColorPicker3("", color, ImGuiColorEditFlags_Float )){
                                    material->SetColor(glm::vec3(color[0], color[1], color[2]));
                                }

                                float shine = material->GetShininess();
                                if (ImGui::SliderFloat("Shininess", &shine, 0.0f, 256.0f))
                                {
                                    material->SetShininess(shine);
                                }

                                ImGui::Separator();

                                // ====== MATERIAL MAPS ======
                                ImGui::SeparatorText("DIFFUSE MAP");
                                ImGui::Text("Path: %s", material->GetDiffuseMap()->GetPath().c_str());
                                ImGui::Text("Resolution: %d x %d", material->GetDiffuseMap()->GetWidth(), material->GetDiffuseMap()->GetHeight());
                                ImGui::Image(material->GetDiffuseMap()->GetUID(), _thumbnailSize);
                                ImGui::Dummy(ImVec2(0,10));

                                ImGui::SeparatorText("SPECULAR MAP");
                                ImGui::Text("Path: %s", material->GetSpecularMap()->GetPath().c_str());
                                ImGui::Text("Resolution: %d x %d", material->GetSpecularMap()->GetWidth(), material->GetSpecularMap()->GetHeight());
                                ImGui::Image(material->GetSpecularMap()->GetUID(), _thumbnailSize);
                                ImGui::Dummy(ImVec2(0,10));

                                ImGui::SeparatorText("EMISSION MAP");
                                ImGui::Text("Path: %s", material->GetEmissionMap()->GetPath().c_str());
                                ImGui::Text("Resolution: %d x %d", material->GetEmissionMap()->GetWidth(), material->GetEmissionMap()->GetHeight());
                                ImGui::Image(material->GetEmissionMap()->GetUID(), _thumbnailSize);
                                ImGui::Dummy(ImVec2(0,10));

                                // ====== SHADER ======
                                std::shared_ptr<Shader> shader = material->GetShader();
                                if (shader)
                                {
                                    ImGui::SeparatorText("SHADER");
                                    ImGui::Text("Shader UID: %u", shader->GetShaderUID());

                                    ImGui::Text("Vertex Shader");
                                    // ImGui::TextUnformatted("%s", shader->GetFilePath(GL_VERTEX_SHADER).c_str());
                                    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.0f, 0.3f, 1.0f));
                                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
                                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
                                    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));

                                    ImGui::BeginChild("Vertex shader source code", ImVec2(0,300), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);
                                    ImGui::TextUnformatted(shader->GetSourceCode(GL_VERTEX_SHADER).c_str());
                                    ImGui::EndChild();

                                    ImGui::PopStyleColor(1);
                                    ImGui::Dummy(ImVec2(0,10));
                                    ImGui::Text("Fragment Shader");
                                    ImGui::Dummy(ImVec2(0,10));
                                    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

                                    // ImGui::TextUnformatted("%s", shader->GetFilePath(GL_FRAGMENT_SHADER).c_str());
                                    ImGui::BeginChild("Fragment shader source code", ImVec2(0,300), ImGuiChildFlags_Border, ImGuiWindowFlags_HorizontalScrollbar);
                                    ImGui::TextUnformatted(shader->GetSourceCode(GL_FRAGMENT_SHADER).c_str());
                                    ImGui::EndChild();

                                    ImGui::PopStyleColor(3);
                                    ImGui::PopStyleVar(1);
                                }
                            }
                            else
                            {
                                ImGui::Text("No material");
                            }

                            ImGui::TreePop();
                        }
                        ImGui::TreePop();
                        ImGui::Separator();
                    }
                }

                // Display PointLight component if it exists
                PointLight* pointLight = entity.GetComponent<PointLight>();
                if (pointLight)
                {
                    if (ImGui::TreeNode("PointLight"))
                    {
                        ImGui::SeparatorText("Light properties");

                        // ImGui::Text("Ambient: (%.2f, %.2f, %.2f)",
                        //     pointLight->GetAmbient().x, pointLight->GetAmbient().y, pointLight->GetAmbient().z);
                        float ambientPointLight[3] = {pointLight->GetAmbient().x, pointLight->GetAmbient().y, pointLight->GetAmbient().z};
                        if (ImGui::DragFloat3("Ambient", ambientPointLight, 0.01f)){
                            pointLight->SetAmbient(glm::vec3(ambientPointLight[0], ambientPointLight[1], ambientPointLight[2]));
                        }

                        // ImGui::Text("Diffuse: (%.2f, %.2f, %.2f)",
                        //     pointLight->GetDiffuse().x, pointLight->GetDiffuse().y, pointLight->GetDiffuse().z);
                        float diffusePointLight[3] = {pointLight->GetDiffuse().x, pointLight->GetDiffuse().y, pointLight->GetDiffuse().z};
                        if (ImGui::DragFloat3("Diffuse", diffusePointLight, 0.01f)){
                            pointLight->SetDiffuse(glm::vec3(diffusePointLight[0], diffusePointLight[1], diffusePointLight[2]));
                        }

                        // ImGui::Text("Specular: (%.2f, %.2f, %.2f)",
                        //     pointLight->GetSpecular().x, pointLight->GetSpecular().y, pointLight->GetSpecular().z);
                        float specularPointLight[3] = {pointLight->GetSpecular().x, pointLight->GetSpecular().y, pointLight->GetSpecular().z};
                        if (ImGui::DragFloat3("Specular", specularPointLight, 0.01f)){
                            pointLight->SetSpecular(glm::vec3(specularPointLight[0], specularPointLight[1], specularPointLight[2]));
                        }

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

                        ImGui::Separator();
                    }
                }

                // Display DirectionalLight component if it exists
                DirectionalLight* dirLight = entity.GetComponent<DirectionalLight>();
                if (dirLight)
                {
                    if (ImGui::TreeNode("DirectionalLight"))
                    {
                        // Directional Light direction
                        float direction[3] = {dirLight->GetDirection().x, dirLight->GetDirection().y , dirLight->GetDirection().z };
                        if (ImGui::DragFloat3("Direction", direction, 0.1f)) {
                            dirLight->SetDirection(glm::vec3(direction[0], direction[1], direction[2]));
                        }

                        // Directional Light ambient
                        float ambientDirLight[3] = { dirLight->GetAmbient().x, dirLight->GetAmbient().y, dirLight->GetAmbient().z};
                        if (ImGui::DragFloat3("Ambient", ambientDirLight, 0.01f, 0.0f, 1.0f)) {
                            dirLight->SetAmbient(glm::vec3(ambientDirLight[0], ambientDirLight[1], ambientDirLight[2]));
                        }

                        // Directional Light diffuse
                        float diffuseDirLight[3] = { dirLight->GetDiffuse().x, dirLight->GetDiffuse().y, dirLight->GetDiffuse().z };
                        if (ImGui::DragFloat3("Diffuse", diffuseDirLight, 0.01f, 0.0f, 1.0f)) {
                            dirLight->SetDiffuse(glm::vec3(diffuseDirLight[0], diffuseDirLight[1], diffuseDirLight[2]));
                        }

                        float specularDirLight[3] =  {dirLight->GetSpecular().x, dirLight->GetSpecular().y, dirLight->GetSpecular().z};
                        if (ImGui::DragFloat3("Specular", specularDirLight, 0.1f, 0.0f, 1.0f)){
                            dirLight->SetSpecular(glm::vec3(specularDirLight[0], specularDirLight[1], specularDirLight[2]));
                        }

                        ImGui::TreePop();

                        ImGui::Separator();
                    }
                }




                ImGui::TreePop();
            }
            ImGui::Separator();

        }

        ImGui::End();
    }
}
