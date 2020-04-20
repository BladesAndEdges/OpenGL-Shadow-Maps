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

#include<QOpenGLWidget>
#include<QSurfaceformat>
#include<assert.h>
#include<QMessageBox>

#include<QMatrix4x4>

/*Global variables*/
const QVector3D g_worldUpVector(0.0f, 1.0f, 0.0f);
const QVector4D g_toLightSourceDirectionVector(1.0f, 1.0f, 1.0f, 0.0f); // Direction the sun is located in, from the scene

class RenderWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{

private:

	TextureObject* texture;

	GLuint m_uniformBuffer;
	GLuint m_shadowMapFramebuffer;

	GLuint m_shadowMapTexture;

	QSurfaceFormat* m_surfaceFormat;

	Shader m_shadowMappingShader; // Shader where the actual Shadow Mapping is done
	Shader m_debuggingShader; // Shader which we use to output the depth map to a quad

	CameraView* m_mainViewCamera;
	CameraView* m_shadowViewCamera; // As seen from the light source

	Mesh* m_debuggingQuadMesh;
	Mesh* m_floorMesh;
	Mesh* m_wallMesh;
	Mesh* m_cubeMesh;

	void catchErrorMessage(GLenum errorCode);
	void getOpenGLInformation();
	void renderSceneObjects(const CameraView& mainViewCamera, const CameraView& shadowViewCamera);

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

