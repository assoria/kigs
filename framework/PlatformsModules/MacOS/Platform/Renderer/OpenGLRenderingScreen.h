#ifndef _MACOSOPENGLRENDERINGSCREEN_H
#define _MACOSOPENGLRENDERINGSCREEN_H


class OpenGLTexture;

#include "UIVerticesInfo.h"

#include "Platform\Renderer\OpenGLInclude.h"

class OpenGLPlatformRenderingScreen : public RenderingScreen
{
public:
    DECLARE_ABSTRACT_CLASS_INFO(OpenGLPlatformRenderingScreen,RenderingScreen,Renderer)

	OpenGLPlatformRenderingScreen(const kstl::string& name,DECLARE_CLASS_NAME_TREE_ARG);
    
	void	SetWindowByHandle(void *PtrToHandle);

	void*	GetContextHandle()
	{
		//return &myhDC;
		// TODO
 		return nullptr; 
	}

protected:
    
	 void Update(const Timer&  timer, void* /*addParam*/)override;


	 virtual void InitializeGL(GLsizei width, GLsizei height)=0;

	 void	InitModifiable()override;
	 void	UninitModifiable()override;

	 void	setCurrentContext() override;

	virtual ~OpenGLPlatformRenderingScreen();
   
	bool SetupPixelFormat(/*HDC hdc*/ int todo);
/*
	HDC   myhDC; 
	HGLRC myhRC; 

	HWND  myhWnd;*/


		
};    


#endif //_MACOSOPENGLRENDERINGSCREEN_H