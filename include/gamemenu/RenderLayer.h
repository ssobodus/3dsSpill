#pragma once
#include "engine/Render.h"
#include <cstring>

extern "C" {

    #include <3ds/gpu/shaderProgram.h>
    #include "engine/common.h"
    #include "c2d/base.h"
    #include <c3d/base.h>
    #include <c3d/renderqueue.h>
    #include <c3d/light.h>
    
    #include <3ds/os.h>
    #include <c3d/types.h>
    #include <c3d/lightlut.h>
    #include <3ds/gpu/enums.h>
    #include <c3d/texenv.h>

}


namespace renderlayer
{

  class RenderLayer : public Render::Renderer
  {
  private:
    C3D_RenderTarget* leftTarget{nullptr};
    C3D_RenderTarget* rightTarget{nullptr};
  
    shaderProgram_s program {nullptr};
    DVLB_s* vertexShader_dvlb {nullptr};

    s8 uLoc_projection{};
    s8 uLoc_modelView{};

    C3D_LightEnv*  lightEnvironment {nullptr};
    C3D_LightLut lut_Phong {};
    void* vbo_data{nullptr};

    C3D_Mtx* projectionMatrix{nullptr};

  public:
    
    void Render();
    void SceneRender(float InterOcularDistance);

    void Initialize() override
    {
      gfxInitDefault();
      gfxSet3D(true);
      C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
      this->leftTarget = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
      this->rightTarget = C3D_RenderTargetCreate(240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
      C3D_RenderTargetClear(this->leftTarget, C3D_CLEAR_ALL, C3D_CLEAR_COLOR, 0);
      C3D_RenderTargetClear(this->rightTarget, C3D_CLEAR_ALL, C3D_CLEAR_COLOR, 0);
    }

    void InitializeScene() override
    {
      this->vertexShader_dvlb = DVLB_ParseFile((u32*) vshader_shbin, vshader_shbin_size);
      shaderProgramInit(&this->program);
      shaderProgramSetVsh(&this->program, &this->vertexShader_dvlb->DVLE[0]);
      C3D_BindProgram(&this->program);	
      this->uLoc_projection = shaderInstanceGetUniformLocation(this->program.vertexShader, "projection");
      this->uLoc_modelView = shaderInstanceGetUniformLocation(this->program.vertexShader, "modelView");
	    C3D_AttrInfo* attributeInfo = C3D_GetAttrInfo();
	    AttrInfo_Init(attributeInfo);
	    AttrInfo_AddLoader(attributeInfo, 0, GPU_FLOAT, 3);
	    AttrInfo_AddLoader(attributeInfo, 1, GPU_FLOAT, 2);
	    AttrInfo_AddLoader(attributeInfo, 2, GPU_FLOAT, 3); 

      vbo_data = linearAlloc(sizeof(vertexList));    
      std::memcpy(vbo_data, vertexList, sizeof(vertexList));
	    C3D_BufInfo* bufferInfo = C3D_GetBufInfo();
	    BufInfo_Init(bufferInfo);
	    BufInfo_Add(bufferInfo, this->vbo_data, sizeof(Vertex), 3, 0x210);
	    C3D_TexEnv* environment = C3D_GetTexEnv(0);
	    C3D_TexEnvSrc(environment, C3D_Both, GPU_FRAGMENT_PRIMARY_COLOR, GPU_FRAGMENT_SECONDARY_COLOR);
      C3D_TexEnvOpRgb(environment, GPU_TEVOP_RGB_SRC_COLOR, GPU_TEVOP_RGB_SRC_COLOR, GPU_TEVOP_RGB_SRC_COLOR);
  	  C3D_TexEnvFunc(environment, C3D_Both, GPU_ADD);
	    C3D_LightEnvInit(lightEnvironment);
	    C3D_LightEnvBind(lightEnvironment);
	    C3D_LightEnvMaterial(lightEnvironment, &material);
	    LightLut_Phong(&this->lut_Phong, 30);
	    C3D_LightEnvLut(lightEnvironment, GPU_LUT_D0, GPU_LUTINPUT_LN, false, &this->lut_Phong);

    }


  };
}
