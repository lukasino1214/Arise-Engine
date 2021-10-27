//
// Created by lukas on 09.10.21.
//

#include "Camera.h"

/*float mouseSpeed = 0.005f;
float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;*/

/*namespace Engine {
    /*Camera3D::Camera3D(float fov, uint32_t width, uint32_t height, float nearClip, float farClip) : m_ViewportWidth(width), m_ViewportHeight(height) {
        UpdateProjection();
    }

    void Camera3D::UpdateProjection()
    {
        m_AspectRatio = m_ViewportWidth / m_ViewportHeight;
        m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
    }
}*


/*namespace Engine {

    Camera3D::Camera3D() {
        RecalculatePerspective();
    }

    void Camera3D::SetPerspective(float verticalFOV, float nearClip, float farClip) {
        m_PerspectiveFOV = verticalFOV;
        m_PerspectiveNear = nearClip;
        m_PerspectiveFar = farClip;
        RecalculatePerspective();
    }

    void Camera3D::SetViewportSize(uint32_t width, uint32_t height)
    {
        //ASSERT(width > 0 && height > 0);
        m_AspectRatio = (float)width / (float)height;
        RecalculatePerspective();
    }

    void Camera3D::RecalculatePerspective() {
        m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
    }

    EditorCamera3D::EditorCamera3D(float fov, float aspectRatio, float nearClip, float farClip)
            : m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip), Camera3D(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip))
    {
        UpdateView();
    }
}*/

namespace Engine {
    /*Camera3D::Camera3D(GLFWwindow* window, const FramebufferSpecification& spec) : m_Specification(spec) {
        //m_View = glm::lookAt(m_Position, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

        //Move(window, 1.0f);
        SetFOV(90.0f);
        SetProjection(spec.Width, spec.Height);

    }

    void Camera3D::Move(GLFWwindow* window, float delta) {
        static double lastTime = glfwGetTime();
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);


        glfwGetCursorPos(window, &xpos, &ypos);

        glfwSetCursorPos(window, 1280 / 2, 720 / 2);

        horizontalAngle += mouseSpeed * float(1280 / 2 - xpos);
        verticalAngle += mouseSpeed * float(720 / 2 - ypos);


        //m_Direction = glm::vec3((cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle)));
        m_Direction = { cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle) };

        glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));

        // Up vector
        glm::vec3 up = glm::normalize(glm::cross(right, m_Direction));



        // Move forward
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            m_Position += m_Direction * delta * m_speed;
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            m_Position -= m_Direction * delta * m_speed;
        }
        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            m_Position += right * delta * m_speed;
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            m_Position -= right * delta * m_speed;
        }

        m_View = glm::lookAt(
                m_Position,           // Camera is here
                m_Position + m_Direction, // and looks here : at the same position, plus "direction"
                up                  // Head is up (set to 0,-1,0 to look upside-down)
        );

    }*/

    Camera::Camera(int width, int height, glm::vec3 position) : m_Position(position), m_Width(width), m_Height(height) {
        m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
        m_Projection = glm::perspective(glm::radians(m_FOV), (float)m_Width / m_Height, nearPlane, farPlane);
    }

    /*void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, const char* uniform)
    {
        // Initializes matrices since otherwise they will be the null matrix
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        // Makes camera look in the right direction from the right position
        view = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
        // Adds perspective to the scene
        projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);
    }*/



    void Camera::Inputs(GLFWwindow* window)
    {
        // Handles key inputs
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            m_Position += speed * m_Orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_Position += speed * -glm::normalize(glm::cross(m_Orientation, m_Up));
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            m_Position += speed * -m_Orientation;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_Position += speed * glm::normalize(glm::cross(m_Orientation, m_Up));
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        {
            m_Position += speed * m_Up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        {
            m_Position += speed * -m_Up;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        {
            speed = 0.4f;
        }
        else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
        {
            speed = 0.1f;
        }


        // Handles mouse inputs
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        {
            // Hides mouse cursor
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

            // Prevents camera from jumping on the first click
            if (firstClick)
            {
                glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
                firstClick = false;
            }

            // Stores the coordinates of the cursor
            double mouseX;
            double mouseY;
            // Fetches the coordinates of the cursor
            glfwGetCursorPos(window, &mouseX, &mouseY);

            // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
            // and then "transforms" them into degrees
            float rotX = sensitivity * (float)(mouseY - (m_Height / 2)) / m_Height;
            float rotY = sensitivity * (float)(mouseX - (m_Width / 2)) / m_Width;

            // Calculates upcoming vertical change in the Orientation
            glm::vec3 newOrientation = glm::rotate(m_Orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_Orientation, m_Up)));

            // Decides whether or not the next vertical Orientation is legal or not
            if (abs(glm::angle(newOrientation, m_Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
            {
                m_Orientation = newOrientation;
            }

            // Rotates the Orientation left and right
            m_Orientation = glm::rotate(m_Orientation, glm::radians(-rotY), m_Up);

            // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
            glfwSetCursorPos(window, (m_Width / 2), (m_Height / 2));
        }
        else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
        {
            // Unhides cursor since camera is not looking around anymore
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            // Makes sure the next time the camera looks around it doesn't jump
            firstClick = true;
        }

        m_View = glm::lookAt(m_Position, m_Position + m_Orientation, m_Up);
    }
}
