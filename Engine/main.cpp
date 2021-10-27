#include <iostream>

#include "../Arise/Engine.h"
#include "Panels/SceneHierarchyPanel.h"
#include "Panels/ContentBrowserPanel.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <glm/gtx/string_cast.hpp>

using namespace Engine;



/*int main() {

    float cube[] = {
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    Ref<Window> windowHandler = CreateRef<Window>();

    Ref<ImGuiRenderer> ImGuiLayer = CreateRef<ImGuiRenderer>(windowHandler->GetWindow());

    Ref<Timestep> timestep;
    float m_LastFrameTime = 0.0f;

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

    float vertices[3*7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    uint32_t indices[3] = { 0, 1, 2 };

    Ref<VertexArray> m_VertexArray = VertexArray::Create();

    Ref<VertexBuffer> m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

    BufferLayout layout = {{ ShaderDataType::Float3, "aPos" }, { ShaderDataType::Float4, "aCol" }};
    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);


    Ref<IndexBuffer> m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);


    //Todo: CUBE
    Ref<VertexArray> m_CubeVertexArray = VertexArray::Create();

    Ref<VertexBuffer> m_CubeVertexBuffer = VertexBuffer::Create(cube, sizeof(cube));

    BufferLayout m_CubeLayout = {{ ShaderDataType::Float3, "aPos" }};
    m_VertexBuffer->SetLayout(m_CubeLayout);
    m_VertexArray->AddVertexBuffer(m_CubeVertexBuffer);


    std::string cubeVert = R"(#version 330 core
                            layout (location = 0) in vec3 aPos;

                            uniform mat4 model;
                            uniform mat4 view;
                            uniform mat4 projection;

                            void main() {
	                            gl_Position = projection * view * model * vec4(aPos, 1.0f);
                            })";

    std::string cubeFrag = R"(#version 330 core
                              out vec4 FragColor;

                              void main() {
	                                    FragColor = Vec4(1.0f);
                              })";

    Ref<Shader> m_CubeShader = Shader::Create(cubeVert, cubeFrag);


    std::string vertexShaderSource = R"(#version 330 core
                                        layout (location = 0) in vec3 aPos;
                                        layout (location = 1) in vec4 aCol;
                                        out vec3 vPos;
                                        out vec4 vCol;

                                        void main() {
                                            vPos = aPos;
                                            vCol = aCol;
                                            gl_Position = vec4(aPos, 1.0);
                                        })";

    std::string fragmentShaderSource = R"(#version 330 core
                                          out vec4 FragColor;
                                          in vec3 vPos;
                                          in vec4 vCol;

                                          void main() {
                                              FragColor = vec4(vPos * 0.5 + 0.5, 1.0);
                                              FragColor = vCol;
                                          })";

    Ref<Shader> m_Shader = Shader::Create(vertexShaderSource, fragmentShaderSource);

    //Ref<EditorCamera3D> = CreateRef<Window>();

    float square[3*4] = {
            -0.75f, -0.75f, 0.0f,
             0.75f, -0.75f, 0.0f,
             0.75f,  0.75f, 0.0f,
            -0.75f,  0.75f, 0.0f,
    };

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    Ref<VertexArray> m_SquareVA = VertexArray::Create();
    BufferLayout squareVBlayout = {{ ShaderDataType::Float3, "aPos" }};
    Ref<VertexBuffer> squareVB = VertexBuffer::Create(square, sizeof(square));
    squareVB->SetLayout(squareVBlayout);
    m_SquareVA->AddVertexBuffer(squareVB);

    Ref<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string vertexShaderSource2 = R"(#version 330 core
                                         layout (location = 0) in vec3 aPos;
                                         out vec3 vPos;

                                         void main() {
                                            vPos = aPos;
                                            gl_Position = vec4(aPos, 1.0);
                                         })";

    std::string fragmentShaderSource2 = R"(#version 330 core
                                           layout (location = 0) out vec4 color;
                                           in vec3 vPos;

                                           void main() {
                                               color = vec4(0.2, 0.3, 0.8, 1.0);
                                           })";

    Ref<Shader> m_BlueShader = Shader::Create(vertexShaderSource2, fragmentShaderSource2);

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3( 2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3( 1.3f, -2.0f, -2.5f),
            glm::vec3( 1.5f,  2.0f, -2.5f),
            glm::vec3( 1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    ImVec2 windowSize = { 925, 450 };
    FramebufferSpecification fbSpec;
    fbSpec.Height = windowSize.x;
    fbSpec.Width = windowSize.y;
    fbSpec.Attachments = { FramebufferTextureFormat::RGBA8};
    Ref<Framebuffer> m_Framebuffer;
    m_Framebuffer = Framebuffer::Create(fbSpec);

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)1280 / (float)720, 0.1f, 100.0f);
    //m_CubeShader->Bind();
    //m_CubeShader->SetMat4("projection", projection);
    //m_CubeShader>Unbind();

    while (!glfwWindowShouldClose(windowHandler->GetWindow())) {

        auto time = (float)glfwGetTime();
        timestep = CreateRef<Timestep>(time - m_LastFrameTime);
        m_LastFrameTime = time;
        //INFO("Time: {0} ms", timestep->GetMilliseconds());

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glfwPollEvents();

        //glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        //m_Framebuffer->Bind();
        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        RenderCommand::Clear();

        m_CubeShader->Bind();
        m_CubeVertexArray->Bind();
        m_CubeShader->SetMat4("projection", projection);
        m_CubeShader->SetMat4("view", view);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, {0.0f, 0.0f, 0.0f});
        m_CubeShader->SetMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //RenderCommand::Draw(m_CubeVertexArray);
        m_CubeShader->Unbind();
        m_CubeVertexArray->Unbind();

        float cameraSpeed = 2.5 * deltaTime;
        if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;

        if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            cameraPos -= cameraSpeed * cameraFront;
            std::cout << "Bruh" << std::endl;
        }
        if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;


        m_CubeShader->Bind();
        // camera/view transformation
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        m_CubeShader->SetMat4("projection", projection);
        m_CubeShader->SetMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            m_CubeShader->SetMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        m_CubeShader->Unbind();

        std::cout << deltaTime << std::endl;



        m_BlueShader->Bind();
        //m_SquareVA->Bind();
        RenderCommand::DrawIndexed(m_SquareVA);
        //RenderCommand::Draw(); <-- Draws vertexArray without IndexBuffer
        m_BlueShader->Unbind();
        //m_SquareVA->Unbind();

        m_Shader->Bind();
        //m_VertexArray->Bind();
        RenderCommand::DrawIndexed(m_VertexArray);
        m_Shader->Unbind();
        m_Framebuffer->Unbind();

        if (glfwGetKey(windowHandler->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(windowHandler->GetWindow(), true);

        /*ImGuiLayer->begin();

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
                    if(ImGui::MenuItem("New Project")) {

                    }

                    if(ImGui::MenuItem("Save Project")) {

                    }

                    if(ImGui::MenuItem("Open Project")) {

                    }

                    if(ImGui::MenuItem("New Scene")) {

                    }

                    if(ImGui::MenuItem("Save Scene")) {
                        SceneSerializer serializer(m_ActiveScene);
                        serializer.Serialize("assets/Scene/Example.scene");
                    }

                    if(ImGui::MenuItem("Open Scene")) {
                        m_ActiveScene = CreateRef<Scene>();
                        SceneSerializer serializer(m_ActiveScene);
                        serializer.Deserialize("assets/scene/Example.scene");
                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Data")) {
                    if(ImGui::MenuItem("New Data")) {

                    }

                    if(ImGui::MenuItem("Save Data")) {

                    }

                    if(ImGui::MenuItem("Open Data")) {

                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("View")) {
                    if(ImGui::MenuItem("Viewport", "Alt+V")) {

                    }

                    if(ImGui::MenuItem("Content Browser", "Alt+F")) {

                    }

                    if(ImGui::MenuItem("scene Hierarchy", "Alt+S")) {

                    }

                    if(ImGui::MenuItem("Log", "Alt+L")) {

                    }

                    if(ImGui::MenuItem("Console"), "Alt+C") {

                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Settings")) {
                    if(ImGui::MenuItem("Editor Settings", "Alt+E")) {

                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }
        }

        {
            ImGui::Begin("Viewport");
            windowSize = ImGui::GetContentRegionAvail();
            ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ windowSize.x, windowSize.y }, ImVec2(0, 1), ImVec2(1, 0));
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
}*/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main() {
    /*glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

    Ref<Window> windowHandler = CreateRef<Window>(SCR_WIDTH, SCR_HEIGHT);
    GLFWwindow* window = windowHandler->GetWindow();
    Ref<ImGuiRenderer> ImGuiLayer = CreateRef<ImGuiRenderer>(windowHandler->GetWindow());

    glEnable(GL_DEPTH_TEST);

    Ref<Shader> ourShader = Shader::Create("assets/shaders/cube.shader");

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f),
            glm::vec3( 3.0f,  0.0f,  0.0f),
            glm::vec3( 0.0f,  3.0f,  0.0f),
            glm::vec3( 0.0f,  0.0f,  3.0f)

            /*glm::vec3( 0.0f,  0.0f,  3.0f)*/
    };

    Ref<VertexArray> m_VertexArray = VertexArray::Create();

    Ref<VertexBuffer> m_VertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

    BufferLayout layout = {{ ShaderDataType::Float3, "aPos" }, { ShaderDataType::Float2, "aTex" }};
    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);

    /*ourShader->Bind();

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader->SetMat4("projection", projection);*/

    bool p_open = true;
    static bool opt_fullscreen = true;
    static bool opt_padding = false;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

    Ref<Scene> m_ActiveScene = CreateRef<Scene>();

    SceneSerializer serializer(m_ActiveScene);
    serializer.Deserialize("assets/scene/Example.scene");

    SceneHierarchyPanel m_SceneHierarchyPanel;
    m_SceneHierarchyPanel.SetContext(m_ActiveScene);

    ContentBrowserPanel m_ContentBrowserPanel;

    ImVec2 windowSize = { 925, 450 };
    FramebufferSpecification fbSpec;
    fbSpec.Height = windowSize.x;
    fbSpec.Width = windowSize.y;
    fbSpec.Attachments = { FramebufferTextureFormat::RGBA8};
    Ref<Framebuffer> m_Framebuffer;
    m_Framebuffer = Framebuffer::Create(fbSpec);

    Ref<Camera> m_Camera = CreateRef<Camera>(640, 360, glm::vec3( 5.0f, 5.0f, 5.0f ));

    Ref<Shader> modelShader = Shader::Create("assets/shaders/model.shader");
    Ref<Model> m_Backpack = CreateRef<Model>("assets/models/backpack/backpack.obj");

    while (!glfwWindowShouldClose(windowHandler->GetWindow())) {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        /*auto time = (float)glfwGetTime();
        timestep = CreateRef<Timestep>(time - m_LastFrameTime);
        m_LastFrameTime = time;*/
        m_Camera->Inputs(windowHandler->GetWindow());
        processInput(windowHandler->GetWindow());

        m_Framebuffer->Bind();
        RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        RenderCommand::Clear();

        ourShader->Bind();

        ourShader->SetMat4("view", m_Camera->GetView());
        ourShader->SetMat4("projection", m_Camera->GetProjection());

        for (unsigned int i = 0; i < 4; i++) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            //float angle = 20.0f * i;
            //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            ourShader->SetMat4("model", model);

            RenderCommand::Draw(m_VertexArray);
        }
        ourShader->Unbind();

        modelShader->Bind();
        modelShader->SetMat4("view", m_Camera->GetView());
        modelShader->SetMat4("projection", m_Camera->GetProjection());
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(3.0f, 3.0f, 3.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        modelShader->SetMat4("model", model);
        m_Backpack->Draw(ourShader);
        modelShader->Unbind();

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
                    if(ImGui::MenuItem("New Project")) {

                    }

                    if(ImGui::MenuItem("Save Project")) {

                    }

                    if(ImGui::MenuItem("Open Project")) {

                    }

                    if(ImGui::MenuItem("New Scene")) {

                    }

                    if(ImGui::MenuItem("Save Scene")) {
                        SceneSerializer serializer(m_ActiveScene);
                        serializer.Serialize("assets/Scene/Example.scene");
                    }

                    if(ImGui::MenuItem("Open Scene")) {
                        m_ActiveScene = CreateRef<Scene>();
                        SceneSerializer serializer(m_ActiveScene);
                        serializer.Deserialize("assets/scene/Example.scene");
                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Data")) {
                    if(ImGui::MenuItem("New Data")) {

                    }

                    if(ImGui::MenuItem("Save Data")) {

                    }

                    if(ImGui::MenuItem("Open Data")) {

                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("View")) {
                    if(ImGui::MenuItem("Viewport", "Alt+V")) {

                    }

                    if(ImGui::MenuItem("Content Browser", "Alt+F")) {

                    }

                    if(ImGui::MenuItem("scene Hierarchy", "Alt+S")) {

                    }

                    if(ImGui::MenuItem("Log", "Alt+L")) {

                    }

                    if(ImGui::MenuItem("Console"), "Alt+C") {

                    }

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Settings")) {
                    if(ImGui::MenuItem("Editor Settings", "Alt+E")) {

                    }

                    ImGui::EndMenu();
                }

                ImGui::EndMenuBar();
            }
        }

        {
            ImGui::Begin("Viewport");
            windowSize = ImGui::GetContentRegionAvail();
            ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), ImVec2{ windowSize.x, windowSize.y }, ImVec2(0, 1), ImVec2(1, 0));
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

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
