//
// Created by lukas on 09.10.21.
//

#ifndef ARISE_ENGINE_CAMERA_H
#define ARISE_ENGINE_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>
#include "Framebuffer.h"
#include "../Core/Log.h"

namespace Engine {
    class Camera {
    public:
        // Stores the main vectors of the camera
        /*glm::vec3 Position;
        glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);*/

        // Prevents the camera from jumping around when first clicking left click
        bool firstClick = true;

        // Stores the width and height of the window
        /*int width;
        int height;*/

        // Adjust the speed of the camera and it's sensitivity when looking around
        float speed = 0.1f;
        float sensitivity = 100.0f;

        // Camera constructor to set up initial values
        Camera(int width, int height, glm::vec3 position);

        glm::mat4 GetView() { return m_View; }
        glm::mat4 GetProjection() { return m_Projection; }

        // Updates and exports the camera matrix to the Vertex Shader
        void Matrix(float FOVdeg, float nearPlane, float farPlane, const char* uniform);
        // Handles camera inputs
        void Inputs(GLFWwindow* window);
    private:
        int m_Width;
        int m_Height;
        float m_FOV = { 90.0f };
        float nearPlane = { 0.001f };
        float farPlane = { 1000.0f };

        glm::mat4 m_View = glm::mat4(1.0f);
        glm::mat4 m_Projection = glm::mat4(1.0f);

        glm::vec3 m_Position;
        glm::vec3 m_Orientation = { -1.0f, -1.0f, -1.0f };
        glm::vec3 m_Up = { 0.0f, 1.0f, 0.0f };
    };


    /*class Camera3D {
    public:
        Camera3D(GLFWwindow* window, const FramebufferSpecification& spec);

        void Move(GLFWwindow* window, float delta);

        void SetPosition(glm::vec3 position) { position = m_Position; }
        glm::vec3 GetPosition() { return m_Position; }
        glm::mat4 GetProjection() { return m_Projection; }
        glm::mat4 GetView() { return m_View; }
        void SetView(const glm::mat4& view) { m_View = view; }
        void SetFOV(float FOV) { FOV = m_FOV; }
        float GetFOV() { return m_FOV; }
        void SetProjection(int width, int height) { m_Projection = glm::perspective(glm::radians(GetFOV()), (float)width / (float)height, 0.1f, 1000.0f); }

        void SetTestProjection() {
            m_Projection = glm::perspective(glm::radians(GetFOV()), (float) 800 /(float) 600, 0.1f, 1000.0f);
            //Please work!!!
        }
        void SetMode(bool mode) { mode = m_Mode; }
        bool GetMode() { return m_Mode; }
    private:
        glm::vec3 m_Position = glm::vec3(5.0f, 5.0f, 5.0f);
        glm::mat4 m_View = glm::lookAt(m_Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        //glm::vec3 m_Direction;
        glm::mat4 m_Projection;
        FramebufferSpecification m_Specification;
        float m_FOV = 90.0f;
        float m_speed = 3.0f;
        float m_horizontalAngle = 3.14f;
        float m_verticalAngle = 0.0f;
        glm::vec3 m_Direction = { 0.0f, 0.0f, 0.0f };

        double xpos = 640.0, ypos = 360.0;
    };*/
}

/*namespace Engine {
    class Camera {
    public:
        Camera() = default;
        Camera(const glm::mat4& projection) : m_Projection(projection) {}

        virtual ~Camera() = default;

        const glm::mat4& GetProjection() const { return m_Projection; }
    protected:
        glm::mat4 m_Projection = glm::mat4(1.0f);
    };

    class Camera3D : public Camera {
    public:
        Camera3D();
        Camera3D(const glm::mat4& projection) : m_Projection(projection) {}

        void SetPerspective(float verticalFOV, float nearClip, float farClip);

        void SetViewportSize(uint32_t width, uint32_t height);

        float GetPerspectiveVerticalFOV() const { return m_PerspectiveFOV; }
        void SetPerspectiveVerticalFOV(float verticalFov) { m_PerspectiveFOV = verticalFov; RecalculatePerspective(); }
        float GetPerspectiveNearClip() const { return m_PerspectiveNear; }
        void SetPerspectiveNearClip(float nearClip) { m_PerspectiveNear = nearClip; RecalculatePerspective(); }
        float GetPerspectiveFarClip() const { return m_PerspectiveFar; }
        void SetPerspectiveFarClip(float farClip) { m_PerspectiveFar = farClip; RecalculatePerspective(); }

        glm::mat4 GetViewMatrix() { return m_ViewMatrix; }

        void SetPosition(const glm::vec3& position) { m_Position = position; }
        glm::vec3 GetPosition() { return m_Position; }
    private:
        void RecalculatePerspective();
    private:
        glm::mat4 m_ViewMatrix;
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

        float m_PerspectiveFOV = glm::radians(45.0f);
        float m_PerspectiveNear = 0.01f, m_PerspectiveFar = 1000.0f;

        float m_AspectRatio = 0.0f;

        glm::mat4 m_Projection = glm::mat4(1.0f);
    };

    class EditorCamera3D : public Camera3D {
    public:
        EditorCamera3D() = default;
        EditorCamera3D(float fov, float aspectRatio, float nearClip, float farClip);

        //void OnUpdate(Timestep ts);

        inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        //glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

        glm::vec3 GetUpDirection() const;
        glm::vec3 GetRightDirection() const;
        glm::vec3 GetForwardDirection() const;
        const glm::vec3& GetPosition() const { return m_Position; }
        glm::quat GetOrientation() const;

        float GetPitch() const { return m_Pitch; }
        float GetYaw() const { return m_Yaw; }
    private:
        void UpdateProjection();
        void UpdateView();

        glm::vec3 CalculatePosition() const;

        float RotationSpeed() const;
    private:
        float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

        glm::mat4 m_ViewMatrix;
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };

        glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

        float m_Pitch = 0.0f, m_Yaw = 0.0f;

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;
    };
}*/


#endif //ARISE_ENGINE_CAMERA_H
