#include "gamemenu/GameMenu.h"
#include "gamemenu/RenderLayer.h"

namespace GameMenu
{
  renderlayer::RenderLayer Renderlay{};

  void Menu::OnStart()
  {
    Renderlay.Initialize();
    Renderlay.InitializeScene();
  }
  void Menu::OnExit()
  {

  }
  void Menu::OnEvent()
  {
    
  }
  void Menu::OnRender()
  {
    Renderlay.Render();
    Renderlay.SceneRender(-3);
  }
  void Menu::OnUpdate()
  {

  }
}
