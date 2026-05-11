#pragma once

#include <cstring>
#include <memory>
#include <string.h>
#include <vector>


namespace Core
{
  class AppLayer
  {
  public:
      virtual ~AppLayer() = default;
      
      virtual void OnStart();
      virtual void OnExit();

      virtual void OnEvent(){}
      virtual void OnUpdate(){}
      virtual void OnRender(){}
  };

  class Core
  {
  private:

  std::vector<std::unique_ptr<AppLayer>> Applayers; 

  size_t targetlayer_{};
  
  void Run();
  protected:
  
  public:
  
    ~Core()
    {
    }
    Core() 
    {
    };
    
    void push(std::unique_ptr<AppLayer> layer);
    void remove(size_t index);
    void Exec();
 

  };


}

