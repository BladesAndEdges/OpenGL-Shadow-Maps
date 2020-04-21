#include "RenderWidget.h"
#include <qdebug.h>
#include <iostream>
#include <qsurfaceformat.h>
#include <qopenglcontext.h>
#include <assert.h>
#include <qmessagebox.h>

//Math stuff
#include <qmatrix4x4.h>
const QVector3D worldUpVector(0.0f, 1.0f, 0.0f);
const QVector4D lightDirection(1.0f, 1.0f, 1.0f, 0.0f);

/*Opengl function which will record error's returned by the API and output an error*/
void RenderWidget::catchOpenGLError(GLenum error)
{
	switch (error)
	{
	case GL_INVALID_ENUM:
		OutputDebugStringA("GL_INVALID_ENUM\n");
	case GL_INVALID_VALUE:
		OutputDebugStringA("GL_INVALID_VALUE\n");
	case GL_INVALID_OPERATION:
		OutputDebugStringA("GL_INVALID_OPERATION\n");
	case GL_STACK_OVERFLOW:
		OutputDebugStringA("GL_STACK_OVERFLOW\n");
	case GL_STACK_UNDERFLOW:
		OutputDebugStringA("GL_STACK_UNDERFLOW\n");
	case GL_OUT_OF_MEMORY:
		OutputDebugStringA("GL_OUT_OF_MEMORY\n");
	case GL_INVALID_FRAMEBUFFER_OPERATION:
		OutputDebugStringA("GL_INVALID_FRAMEBUFFER_OPERATION\n");
	default:
		break;
	}

}

/*Used to ensure we're using the correct OpenGL API specification*/
void RenderWidget::getOpenGLInformation()
{
	int major;
	int minor;

	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);

	qDebug() << "The OpenGL version in use is: " << major << "\n";
	qDebug() << "The OpenGL version in use is: " << minor << "\n";

}

void RenderWidget::renderSceneObjects(const CameraView& cameraView, const CameraView& shadowMapView)
{
	const QVector3D worldUp(0.0f, 1.0f, 0.0f);

	QMatrix4x4 model;
	QMatrix4x4 view;
	QMatrix4x4 projection;

	QMatrix4x4 lightView;
	QMatrix4x4 lightProjection;

	ubo uniformBuffer;

	/*************************************************THIS NEEDS EITHER REWORKING OR BOTH****************************************************/

	/*YOU CHANGED THE SIGNS ON THE ROTATIONS< DUMBASS*/

	/*Obtain the Light Space matrix for our Shadow map ??????*/
	lightView = constructViewMatrix(shadowMapView);
	lightProjection = constructProjectionMatrix(shadowMapView);

	QMatrix4x4 lightSpaceMatrix = lightProjection * lightView;

	copyMatrixIntoFloatArray(lightSpaceMatrix, uniformBuffer.lightSpaceMatrix);

	/****************************************************************************************************************************************/

	/*Reset the matrices*/
	model.setToIdentity();
	view.setToIdentity();
	projection.setToIdentity();

	/*Reconstruct a new view matrix for the camera*/
	view = constructViewMatrix(cameraView);
	projection = constructProjectionMatrix(cameraView);

	QMatrix4x4 viewProjection = projection * view;

	/*Copy over the data into a valid buffer*/
	copyMatrixIntoFloatArray(model, uniformBuffer.model);
	copyMatrixIntoFloatArray(viewProjection, uniformBuffer.viewProjection);
	copyVector4IntoFloatArray(lightDirection, uniformBuffer.toLightDirection);

	m_shadowMappingShader.useShader();

	/*Floor*/
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo), &uniformBuffer, GL_STATIC_DRAW);

	glBindVertexArray(m_floorMesh->m_meshVAO);
	glDrawArrays(GL_TRIANGLES, 0, m_floorMesh->m_meshVertexCount);
	glBindVertexArray(0);

	/*Wall*/
	model.setToIdentity();
	model.translate(QVector3D(0.0f, 0.0f, -20.0f));
	copyMatrixIntoFloatArray(model, uniformBuffer.model);

	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo), &uniformBuffer, GL_STATIC_DRAW);

	glBindVertexArray(m_wallMesh->m_meshVAO);
	glDrawArrays(GL_TRIANGLES, 0, m_wallMesh->m_meshVertexCount);
	glBindVertexArray(0);


	/*Cubes*/

	const std::vector<QVector3D> cubeTranslationVectors =
	{
		QVector3D(5.0f, 8.0f, -8.0f),
		QVector3D(18.0f, 3.0f, -10.0f),
		QVector3D(4.0f, 2.0f, -3.0f),
		QVector3D(2.0f, 15.0f, -17.0f),
		QVector3D(13.0f, 20.0f, -2.0f),
		QVector3D(5.0f, 0.0f, -14.0f),
		QVector3D(7.0f, 12.0f, -6.0f),
		QVector3D(1.0f, 6.0f, -0.0f),
		QVector3D(17.0f, 9.0f, -2.0f),
		QVector3D(16.0f, 1.0f, -14.0f),
	};

	glBindVertexArray(m_cubeMesh->m_meshVAO);
	for (uint32_t cube = 0; cube < cubeTranslationVectors.size(); cube++)
	{
		model.setToIdentity();
		model.scale(0.5f, 0.5f, 0.5f);
		model.translate(cubeTranslationVectors[cube]);
		copyMatrixIntoFloatArray(model, uniformBuffer.model);

		glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo), &uniformBuffer, GL_STATIC_DRAW);

		glDrawArrays(GL_TRIANGLES, 0, m_cubeMesh->m_meshVertexCount);
	}
	glBindVertexArray(0);
}

/*Reconstructs a new View Matrix from scratch*/
QMatrix4x4 RenderWidget::constructViewMatrix(const CameraView & view)
{
	QMatrix4x4 result;

	/*Set matrix to identity, start from new*/
	result.setToIdentity();

	/*First apply rotation*/
	result.rotate(view.getCameraOrientation().getPitchAngle(), QVector3D(1.0f, 0.0f, 0.0f)); // Ask George about this part
	result.rotate(-view.getCameraOrientation().getYawAngle(), QVector3D(0.0f, 1.0f, 0.0f));
	result.rotate(-view.getCameraOrientation().getRollAngle(), QVector3D(0.0f, 0.0f, 1.0f));

	/*Then translation...*/
	result.translate(-view.getCameraWorldPosition());

	return result;
}

QMatrix4x4 RenderWidget::constructProjectionMatrix(const CameraView & view)
{
	QMatrix4x4 result;
	result.setToIdentity();

	if (view.getCameraProjectionType() == ProjectionType::Orthographic)
	{
		const float left = -(view.getCameraWidth() / 2.0f);
		const float right = view.getCameraWidth() / 2.0f;
		const float bottom = -(view.getCameraHeight() / 2.0f);
		const float top = view.getCameraHeight() / 2.0f;

		result.ortho(left, right, bottom, top, view.getCameraNearPlane(), view.getCameraFarPlane());
	}
	if (view.getCameraProjectionType() == ProjectionType::Perspective)
	{
		result.perspective(45.0f, view.getCameraWidth() / view.getCameraHeight(), view.getCameraNearPlane(), view.getCameraFarPlane());
	}

	return result;
}

void RenderWidget::initializeGL()
{
	/*Initalizes openGL functions in QT ( Most likely simply loads up all the function pointers)*/
	initializeOpenGLFunctions();

	std::string path = "Textures/Eagle.png";
	m_eagleTexture = new TextureObject(path, GL_NEAREST);

	/*This functions was created to see information about Versions used*/
	//getOpenGLInformation();

	glEnable(GL_DEPTH_TEST);

	/*The shader for the debugging quad, which we texture using the shadow map*/
	const std::string debugVertexShader = "Shaders/debuggingQuadShader.vert";
	const std::string debugFragmentShader = "Shaders/debuggingQuadShader.frag";

	/*The main shader used for rendering the scene*/
	const std::string simpleVertexShader = "Shaders/shadowMappingShader.vert";
	const std::string simpleFragmentShader = "Shaders/shadowMappingShader.frag";

	/*Does the shader set up. In other words, reading the file source code and creating a program object*/
	m_debuggingShader.setUpShader(debugVertexShader, debugFragmentShader);
	m_shadowMappingShader.setUpShader(simpleVertexShader, simpleFragmentShader);

	m_debugQuadMesh = Mesh::createDebugQuadMesh();
	m_floorMesh = Mesh::createFloorMesh();
	m_wallMesh = Mesh::createWallMesh();
	m_cubeMesh = Mesh::createCubeMesh();

	/*UBO*/

	/*Creating the buffer*/
	glGenBuffers(1, &m_uniformBuffer);

	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(ubo), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uniformBuffer);

	/*FBO*/
	glGenFramebuffers(1, &m_shadowMapFramebuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		OutputDebugStringA("Should work");
	}
}

void RenderWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}

void RenderWidget::paintGL()
{
	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///*The shadow map*/

	glGenTextures(1, &m_shadowMapTexture);
	glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 512, 512, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMapFramebuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowMapTexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glViewport(0, 0, 512, 512);
	glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMapFramebuffer);
	glClear(GL_DEPTH_BUFFER_BIT);
	renderSceneObjects(*m_shadowCameraView, *m_shadowCameraView);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, this->defaultFramebufferObject());

	glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glViewport(0, 0, m_mainCameraView->getCameraWidth(), m_mainCameraView->getCameraHeight());
	glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
	renderSceneObjects(*m_mainCameraView, *m_shadowCameraView);

	m_debuggingShader.useShader();
	glBindTexture(GL_TEXTURE_2D, m_shadowMapTexture);
	glBindVertexArray(m_debugQuadMesh->m_meshVAO);
	glDrawArrays(GL_TRIANGLES, 0, m_debugQuadMesh->m_meshVertexCount);
	glBindVertexArray(0);

	/*Initially we set the flag to indicate no error is present*/
	GLenum error = GL_NO_ERROR;

	do
	{
		/*Query the queue if an error has been set*/
		error = glGetError();

		/*While the queue contains a flag that has not been set to GL_NO_ERROR*/
		if (error != GL_NO_ERROR)
		{
			/*Process the error message*/
			catchOpenGLError(error);
		}

		/*Do this while an error is present*/
	} while (error != GL_NO_ERROR);
}

RenderWidget::RenderWidget()
{

	m_mainCameraView = new CameraView(QVector3D(0.0f, 0.f, 0.0f), Orientation(0.0f, 0.0f, 0.0f), ProjectionType::Perspective, 1200, 800, 0.1f, 1000.0f);



	const Orientation shadowViewOrientation = calculateShadowMapViewOrientation(lightDirection);
	const float shadowMapViewWidth = 40.0f;
	const float shadowMapViewHeight = 40.0f;
	const float shadowMapViewNearPlane = 0.1f;
	const float shadowMapViewFarPlane = 50.0f;

	m_shadowCameraView = new CameraView(QVector3D(17.0f, 25.0f, -5.0f), shadowViewOrientation, ProjectionType::Orthographic, shadowMapViewWidth,
		shadowMapViewHeight, shadowMapViewNearPlane, shadowMapViewFarPlane); // Black magic

	m_surfaceFormat = new QSurfaceFormat();

	/*OpenGL format information*/
	m_surfaceFormat->setVersion(4, 5);
	m_surfaceFormat->setProfile(QSurfaceFormat::CoreProfile);
	m_surfaceFormat->setRenderableType(QSurfaceFormat::OpenGL);
	m_surfaceFormat->setOption(QSurfaceFormat::DebugContext);

	setFormat(*m_surfaceFormat);

	setFocusPolicy(Qt::StrongFocus);
}

RenderWidget::~RenderWidget()
{
	glDeleteVertexArrays(1, &m_floorMesh->m_meshVAO);
	glDeleteBuffers(1, &m_floorMesh->m_meshVBO);
}

CameraView * RenderWidget::getCameraViewObject() const
{
	return m_mainCameraView;
}
