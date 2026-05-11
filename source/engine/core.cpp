#include "engine/core.h"
#include <memory>
#include <utility>

extern "C"
{
    #include "citro2d.h"
    #include "citro3d.h"
}

namespace Core
{
  void Core::Exec()
  {
    Applayers.at(0)->OnStart();
     while(aptMainLoop())
    {
		  gspWaitForVBlank();
		  gfxSwapBuffers();
		  hidScanInput();

	    Core::Run();

      u32 kDown = hidKeysDown();
		  if (kDown & KEY_START)
			  break;
	  } 
  }
  void Core::Run()
  {
    Applayers.at(0)->OnEvent();
    Applayers.at(0)->OnUpdate();
    Applayers.at(0)->OnRender();
  }  
  void Core::push(std::unique_ptr<AppLayer> layer)
  {
    if(layer != nullptr)
    {
      Applayers.push_back(std::move(layer));
    }
  }

  void Core::remove(std::size_t index)
  {
  }

}
