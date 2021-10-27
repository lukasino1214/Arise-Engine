//
// Created by lukas on 26.09.21.
//

#ifndef ARISE_GRAPHICSCONTEXT_H
#define ARISE_GRAPHICSCONTEXT_H


namespace Engine {
    class GraphicsContext {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}

#endif //ARISE_GRAPHICSCONTEXT_H
