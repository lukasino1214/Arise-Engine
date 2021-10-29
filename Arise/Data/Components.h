//
// Created by lukas on 20.09.21.
//

#ifndef ARISE_ENGINE_COMPONENTS_H
#define ARISE_ENGINE_COMPONENTS_H

#include "../Core/UUID.h"
#include "../Core/Base.h"
#include "SimpleShapes.h"

//#include "../Renderer/Model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <string>

namespace Engine {

    struct IDComponent {
        UUID ID;

        IDComponent() = default;
        IDComponent(const UUID& uuid) : ID(uuid) {}
        IDComponent(const IDComponent&) = default;
    };

    struct TagComponent {
        std::string Tag;

        TagComponent() = default;
        TagComponent(const TagComponent&) = default;
        TagComponent(const std::string& tag) : Tag(tag) {}
    };

    struct TransformComponent {
        glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const glm::vec3& translation) : Translation(translation) {}

        glm::mat4 GetTransform() const
        {
            glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

            return glm::translate(glm::mat4(1.0f), Translation)
                   * rotation
                   * glm::scale(glm::mat4(1.0f), Scale);
        }

        glm::vec3 GetTranslation() { return Translation; }
        glm::vec3 GetRotation() { return Rotation; }
        glm::vec3 GetScale() { return Scale; }
    };


    struct CubeComponent {
        Cube cube;

        CubeComponent() = default;
        CubeComponent(const CubeComponent&) = default;
    };

    struct ColorComponent {
      glm::vec3 color = { 1.0f, 1.0f, 1.0f };

      glm::vec3 GetColor() { return color; }
      void SetColor(const glm::vec3& Color) { color = Color; }
    };

}

#endif //ARISE_ENGINE_COMPONENTS_H
