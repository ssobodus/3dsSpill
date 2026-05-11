#include "gamemenu/RenderLayer.h"
#include "engine/common.h"
#include "engine/common.h"
extern "C"
{

  #include <c3d/maths.h>
  #include <3ds/os.h>
  #include <c3d/renderqueue.h>
}


namespace renderlayer
{
  float slider = osGet3DSliderState();
  float iod = slider / 3.0f;
  

  void RenderLayer::Render()
  {
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    C3D_FrameDrawOn(this->leftTarget);
    
    if(iod > 0.0f)
    {
      C3D_FrameDrawOn(this->rightTarget);
      
    }
      C3D_FrameEnd(0);
  }

    void RenderLayer::SceneRender(float interOcularDistance)
  {

    Mtx_PerspStereoTilt(projectionMatrix, 40.0f * (std::acos(-1) / 180.0f),  400.0f / 240.0f, 0.01f, 1000.0f, interOcularDistance, 2.0f, false);
    float distZ = 20.0f;
		Mtx_Translate(projectionMatrix, 0.0f, 0.0f, -10.0f + distZ, false);
		C3D_Mtx modelView;
		Mtx_Identity(&modelView);
		Mtx_Translate(&modelView, 0.0, 0.0, -2.0 + sinf(20.0f), true); //AngleX
		Mtx_RotateX(&modelView, 20.0f, true); //Anglex
		Mtx_RotateY(&modelView, 20.0f, true); //AngleY
		
		//if (interOcularDistance >= 0.0f){
			//this->angleX += radian;
			//this->angleY += radian;
		//}
		
		//Update uniforms
		C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, this->uLoc_projection, projectionMatrix);
		C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, this->uLoc_modelView, &modelView);
		
		//Draw the vertex buffer objects.
		C3D_DrawArrays(GPU_TRIANGLES, 0, sizeof(vertexList)); //vertexlistsize
	}
}
