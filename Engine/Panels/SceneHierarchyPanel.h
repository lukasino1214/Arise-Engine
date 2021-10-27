//
// Created by lukas on 21.09.21.
//

#ifndef ARISE_ENGINE_SCENEHIERARCHYPANEL_H
#define ARISE_ENGINE_SCENEHIERARCHYPANEL_H


#include "../../Arise/Core/Base.h"
#include "../../Arise/Data/Scene.h"
#include "../../Arise/Data/Entity.h"

namespace Engine {

    class SceneHierarchyPanel {
    public:
        SceneHierarchyPanel() = default;
        SceneHierarchyPanel(const Ref<Scene>& scene);

        void SetContext(const Ref<Scene>& scene);

        void OnImGuiRender();

        Entity GetSelectedEntity() const { return m_SelectionContext; }
        void SetSelectedEntity(Entity entity);
    private:
        void DrawEntityNode(Entity entity);
        static void DrawComponents(Entity entity);
    private:
        Ref<Scene> m_Context;
        Entity m_SelectionContext;
    };

}


#endif //ARISE_ENGINE_SCENEHIERARCHYPANEL_H
