#ifndef MAIN_RENDERER_PIPELINE_H
#define MAIN_RENDERER_PIPELINE_H

#include "raylib.h"

class Renderer {

    
public:
    void Initialize();
    void RenderScene(Camera3D camera);
    void Shutdown();
};




#endif 