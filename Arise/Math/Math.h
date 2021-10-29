//
// Created by lukas on 29.10.21.
//

#ifndef ARISE_ENGINE_MATH_H
#define ARISE_ENGINE_MATH_H


#include <glm/glm.hpp>

namespace Engine::Math {

    bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);

}


#endif //ARISE_ENGINE_MATH_H
