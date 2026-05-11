#pragma once
#include <3ds.h>
#include <memory>
#include <vector>

extern "C"
{
  #include "3ds.h"
}

namespace Render 
{
  struct Renderable
  {
    
  };

  class Renderer
  {
    private:
    std::vector<std::unique_ptr<Renderable>> RenderObjects{};

    public:
    virtual void Initialize();
    virtual void InitializeScene();
    Renderer()
    {
  
    }
  };
}
