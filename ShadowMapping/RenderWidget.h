#pragma once

#include <QOpenGLWidget> // The OpenGL widget. Used for setting up an OpenGL context etc. Stuff we need for rendering.

/*This one is interesting, and confusing at first. Here goes. Basically, the Qt header, contains a class for OpenGL functions with the same signiture.
In other words, we don't really call the OpenGL function, we use a wrapper with the ****SAME NAME**** as the OpenGL functions. Hence why this class is needed,
it not only gives us inherited methods, that we use as OpenGL functions, but it also most likely deals with loading the functions pointers behind the scenes*/
#include <qopenglfunctions_4_5_core.h> 

/*File reading*/
#include <fstream>
#include <string.h>
#include <sstream>

/*For errors that need immediate attention*/
#include <QMessageBox>


#include "Shader.h" // Creates a program object that we can then use
#include "UniformBuffer.h" // Uniform buffer struct, containing uniform data for the shaders.
#include "CameraView.h" // Camera/View Matrix implementation

#include "Mesh.h"
#include "TextureObject.h"


/*The main rendering class. This class creates an OpenGL context and then we use Qt wrappers to load in and use the neccessary OpenGL functions*/

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{

private:

	GLuint m_uniformBuffer;
	GLuint m_shadowMapFramebuffer;
	GLuint m_shadowMapTexture;

	QSurfaceFormat* m_surfaceFormat;

	Shader m_shadowMappingShader;
	Shader m_debuggingShader;

	CameraView* m_mainCameraView;
	CameraView* m_shadowCameraView;

	Mesh* m_debugQuadMesh;
	Mesh* m_floorMesh;
	Mesh* m_wallMesh;
	Mesh* m_cubeMesh;

	void catchOpenGLError(GLenum errorCode);
	void getOpenGLInformation();
	void renderSceneObjects(const CameraView& cameraView, const CameraView& shadowViewMap);

	QMatrix4x4 constructViewMatrix(const CameraView& view);
	QMatrix4x4 constructProjectionMatrix(const CameraView& view);

protected:

	void initializeGL() override;
	void resizeGL(int w, int h) override;
	void paintGL() override;

public:

	RenderWidget();
	~RenderWidget();

	CameraView* getCameraViewObject() const;

};

