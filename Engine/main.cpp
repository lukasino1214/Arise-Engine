#include <iostream>

#include "../Arise/Engine.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "ImGuizmo.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <glm/gtx/string_cast.hpp>

using namespace Engine;

int main() {

    Ref<Window> windowHandler = CreateRef<Window>(1280, 720);
    Ref<ImGuiRenderer> ImGuiLayer = CreateRef<ImGuiRenderer>(windowHandler->GetWindow());
    RenderCommand::Init();

    Ref<Shader> ourShader = Shader::Create("assets/shaders/cube.shader");

    Ref<Scene> m_ActiveScene = CreateRef<Scene>();

    SceneSerializer serializer(m_ActiveScene);
    serializer.Deserialize("assets/scene/Example.scene");

    SceneHierarchyPanel m_SceneHierarchyPanel;
    m_SceneHierarchyPanel.SetContext(m_ActiveScene);

    ContentBrowserPanel m_ContentBrowserPanel;

    bool p_open = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    ImVec2 windowSize = { 925, 450 };
    FramebufferSpecification fbSpec;
    fbSpec.Height = windowSize.x;
    fbSpec.Width = windowSize.y;
    fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
    Ref<Framebuffer> m_Framebuffer;
    m_Framebuffer = Framebuffer::Create(fbSpec);

    Ref<Camera> m_Camera = CreateRef<Camera>(1280, 720, glm::vec3( 5.0f, 5.0f, 5.0f ));

    int mouseX, mouseY;
    glm::vec2 m_ViewportBounds[2];
    glm::vec2 m_ViewportSize = {};

    int m_GizmoType;
    bool snap = false;

    Entity m_HoveredEntity;
    uint64_t pixelData = 0;

    bool DoNotTouch = true;

    while (!glfwWindowShouldClose(windowHandler->GetWindow())) {
        snap = false;

        if (FramebufferSpecification spec = m_Framebuffer->GetSpecification(); m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y)) {
            m_Framebuffer->Resize((uint32_t)m_ViewportSize.x, (uint32_t)m_ViewportSize.y);
            m_Camera->SetProjection(m_ViewportSize.x, m_ViewportSize.y);
        }

        if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(windowHandler->GetWindow(), true);

        auto[mx, my] = ImGui::GetMousePos();
        mx -= m_ViewportBounds[0].x;
        my -= m_ViewportBounds[0].y;
        glm::vec2 viewportSize = m_ViewportBounds[1] - m_ViewportBounds[0];
        my = viewportSize.y - my;
        mouseX = (int)mx;
        mouseY = (int)my;

        m_Framebuffer->Bind();
        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        if(mouseX >= 0 && mouseY >=0 && mouseX < (int)viewportSize.x && mouseY << (int)viewportSize.y) {
            if(glfwGetMouseButton(windowHandler->GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && DoNotTouch) {
                uint32_t pixelData1 = m_Framebuffer->ReadPixel(1, mouseX, mouseY);
                uint32_t pixelData2 = m_Framebuffer->ReadPixel(2, mouseX, mouseY);
                pixelData = (((uint64_t)pixelData1) << 32 | pixelData2);
                m_HoveredEntity = pixelData == 0 ? Entity() : Entity((entt::entity)pixelData, m_ActiveScene.get());
                m_SceneHierarchyPanel.SetSelectedEntity(m_HoveredEntity);
            }
        }
        RenderCommand::Clear();
        //m_Framebuffer->ClearAttachment(0, -1);
        m_Framebuffer->ClearAttachment(1, 0);
        m_Framebuffer->ClearAttachment(2, 0);



        m_ActiveScene->m_Registry.each([&](auto entityID) {
            Entity entity{ entityID , m_ActiveScene.get() };
            if(entity.HasComponent<CubeComponent>()) {
                uint64_t UUID = entity.GetUUID();
                //INFO("######### {}", UUID);
                uint32_t firstHalf = (uint32_t)(UUID>>32);
                uint32_t secondHalf = (uint32_t)UUID;
                ourShader->Bind();
                ourShader->SetMat4("view", m_Camera->GetView());
                ourShader->SetMat4("projection", m_Camera->GetProjection());
                ourShader->SetUInt("firstHalf", firstHalf);
                ourShader->SetUInt("secondHalf", secondHalf);

                //ourShader->SetUInt("firstHalf", 666666);

                glm::mat4 rotation = glm::mat4_cast(glm::quat(glm::radians(entity.GetComponent<TransformComponent>().GetRotation())));
                glm::mat4 translation = glm::translate(glm::mat4(1.0f), entity.GetComponent<TransformComponent>().GetTranslation());
                glm::mat4 scale = glm::scale(glm::mat4(1.0f), entity.GetComponent<TransformComponent>().GetScale());
                glm::mat4 model = translation * rotation * scale;

                ourShader->SetMat4("model", entity.GetComponent<TransformComponent>().GetTransform());
                ourShader->SetFloat3("color", entity.GetComponent<ColorComponent>().GetColor());
                RenderCommand::Draw(entity.GetComponent<CubeComponent>().cube.GetVertexArray());
                ourShader->Unbind();
            }
        });


        m_ActiveScene->m_Registry.each([&](auto entityID) {
            Entity entity{ entityID , m_ActiveScene.get() };
                uint64_t UUID = entity.GetUUID();
                //INFO("---> {}", pixelData);
                if(UUID == pixelData) {
                    m_SceneHierarchyPanel.SetSelectedEntity(entity);
                    pixelData = 0;
                }
        });

        m_Framebuffer->Unbind();

        ImGuiLayer->begin();

        // Docking
        {
            if (opt_fullscreen) {
                const ImGuiViewport* viewport = ImGui::GetMainViewport();
                ImGui::SetNextWindowPos(viewport->WorkPos);
                ImGui::SetNextWindowSize(viewport->WorkSize);
                ImGui::SetNextWindowViewport(viewport->ID);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
                window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
                window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
            }
            else {
                dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
            }

            if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
                window_flags |= ImGuiWindowFlags_NoBackground;

            if (!opt_padding)
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::Begin("DockSpace Demo", &p_open, window_flags);
            if (!opt_padding)
                ImGui::PopStyleVar();

            if (opt_fullscreen)
                ImGui::PopStyleVar(2);

            // DockSpace
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
                ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
                ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
            }
            else {

            }

            if (ImGui::BeginMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if(ImGui::MenuItem("New Scene")) {

                    }

                    if(ImGui::MenuItem("Save Scene")) {
                        SceneSerializer serializer(m_ActiveScene);
                        serializer.Serialize("assets/scene/Example.scene");
                        INFO("Saving");
                    }

                    if(ImGui::MenuItem("Open Scene")) {
                        m_ActiveScene = CreateRef<Scene>();
                        SceneSerializer serializer(m_ActiveScene);
                        serializer.Deserialize("assets/scene/Example.scene");
                        INFO("Loading");
                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }
        }

        {
            ImGui::Begin("Viewport");
            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
            if (m_ViewportSize != *((glm::vec2*)&viewportPanelSize)) {
                m_Framebuffer->Resize(viewportPanelSize.x, viewportPanelSize.y);
                m_Camera->SetProjection(viewportPanelSize.x, viewportPanelSize.y);
                m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
            }

            if (ImGui::IsWindowHovered())
                m_Camera->Inputs(windowHandler->GetWindow());

            windowSize = ImGui::GetContentRegionAvail();
            //ImGui::Image((void*)textureColorbuffer, ImVec2{ windowSize.x, windowSize.y }, ImVec2(0, 1), ImVec2(1, 0));
            ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ windowSize.x, windowSize.y }, ImVec2(0, 1), ImVec2(1, 0));
            auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
            auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
            auto viewportOffset = ImGui::GetWindowPos();
            m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
            m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

            if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
                if (!ImGuizmo::IsUsing())
                    m_GizmoType = -1;
            }

            if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_W) == GLFW_PRESS) {
                if (!ImGuizmo::IsUsing())
                    m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
            }

            if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_E) == GLFW_PRESS) {
                if (!ImGuizmo::IsUsing())
                    m_GizmoType = ImGuizmo::OPERATION::ROTATE;
            }

            if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_R) == GLFW_PRESS) {
                if (!ImGuizmo::IsUsing())
                    m_GizmoType = ImGuizmo::OPERATION::SCALE;
            }

            Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
            //Entity selectedEntity = m_HoveredEntity;
            if(selectedEntity) {
                    //INFO("BINGO");
            }
            if (selectedEntity && m_GizmoType != -1)
            {
                ImGuizmo::SetOrthographic(false);
                ImGuizmo::SetDrawlist();

                auto& tc = selectedEntity.GetComponent<TransformComponent>();
                glm::mat4 transform = tc.GetTransform();

                float windowWidth = (float)ImGui::GetWindowWidth();
                float winodwHeight = (float)ImGui::GetWindowHeight();
                ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, winodwHeight);
                //glm::mat4 transform = selectedEntity.GetComponent<TransformComponent>().GetTransform();
                ImGuizmo::Manipulate(glm::value_ptr(m_Camera->GetView()), glm::value_ptr(m_Camera->GetProjection()), (ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));
                if (ImGuizmo::IsUsing()) {
                    glm::vec3 translation, rotation, scale;
                    Math::DecomposeTransform(transform, translation, rotation, scale);

                    glm::vec3 deltaRotation = rotation - tc.Rotation;
                    tc.Translation = translation;
                    tc.Rotation += deltaRotation;
                    tc.Scale = scale;
                }
            }
            ImGui::End();

            m_SceneHierarchyPanel.OnImGuiRender();
            m_ContentBrowserPanel.OnImGuiRender();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            auto& colors = ImGui::GetStyle().Colors;
            const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
            const auto& buttonActive = colors[ImGuiCol_ButtonActive];
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

            ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

            float size = ImGui::GetWindowHeight() - 4.0f;
            ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
            ImGui::Button("Play");
            ImGui::PopStyleVar(2);
            ImGui::PopStyleColor(3);
            ImGui::End();
        }

        ImGuiLayer->end(windowHandler->GetWindow());
        windowHandler->Update();
    }

    windowHandler->Close();
    return 0;
}