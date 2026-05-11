#pragma once

#include "engine/core.h"

namespace GameMenu
{
  class Menu : public Core::AppLayer
  {
    

    public:
    Menu () = default;
    void OnStart() override;   
    void OnExit() override;
    void OnEvent() override;
    void OnUpdate() override; 
    void OnRender() override;
    };

}


