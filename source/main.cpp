#include "engine/core.h"
#include "gamemenu/GameMenu.h"
#include <memory>
#include <stdlib.h>
#include <3ds.h>

int main(int argc, char* argv[])
{
  
  Core::Core core{};

  core.push(std::make_unique<GameMenu::Menu>());
  
  core.Exec();
  return 0;
}
