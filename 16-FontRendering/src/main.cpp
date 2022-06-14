#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

// contains new std::shuffle definition
#include <algorithm>
#include <random>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"
#include "Headers/ThirdPersonCamera.h"

// Font rendering
#include "Headers/FontTypeRendering.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

// Include Terrain
#include "Headers/Terrain.h"

#include "Headers/AnimationUtils.h"

// Include Colision headers functions
#include "Headers/Colisiones.h"

// ShadowBox include
#include "Headers/ShadowBox.h"

// OpenAL include
#include <AL/alut.h>

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

GLFWwindow* window;

//Shader para menu
Shader shaderTexture;
Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader para el terreno
Shader shaderTerrain;
//Shader para las particulas de fountain
//Shader shaderParticlesFountain;
//Shader para las particulas de fuego
Shader shaderParticlesFire;
//Shader para visualizar el buffer de profundidad
Shader shaderViewDepth;
//Shader para dibujar el buffer de profunidad
Shader shaderDepth;

std::shared_ptr<Camera> camera(new ThirdPersonCamera());
float distanceFromTarget = 7.0;

Sphere skyboxSphere(20, 20);
Box boxCollider;
Sphere sphereCollider(10, 10);
Box boxViewDepth;
Box boxLightViewBox;
Cylinder cylinder(10, 10, 0.05, 0.05);
Box boxInicio;
ShadowBox* shadowBox;


// Lamps
Model modelLamp1;
Model modelLamp2;
// Hierba
Model modelGrass;
// Ironman
Model ironmanModelAnimate;
//Zombie
Model zombieModelAnimate;
Model zombie1ModelAnimate;
Model zombie2ModelAnimate;
Model zombie3ModelAnimate;
Model zombie4ModelAnimate;
Model zombie5ModelAnimate;
Model zombie6ModelAnimate;
Model zombie7ModelAnimate;
Model zombie8ModelAnimate;
Model zombie9ModelAnimate;
//Entorno
Model rejaModelAnimate;
Model reja2ModelAnimate;

Model limiteModelAnimate;
Model limite2ModelAnimate;
Model limite3ModelAnimate;
Model limite4ModelAnimate;

Model entradaModelAnimate;
Model entrada2ModelAnimate;

Model gasModelAnimate;

Model carroModelAnimate;
Model carro2ModelAnimate;
Model carro3ModelAnimate;
Model carropModelAnimate;

Model apartamentosModelAnimate;

Model arbolModelAnimate;
Model arbol2ModelAnimate;
Model arbol3ModelAnimate;
Model arbol4ModelAnimate;
Model arbol5ModelAnimate;
Model arbol6ModelAnimate;
Model arbol7ModelAnimate;
Model arbol8ModelAnimate;
Model arbol9ModelAnimate;
Model arbol10ModelAnimate;
Model arbol11ModelAnimate;
Model arbol12ModelAnimate;
Model arbol13ModelAnimate;
Model rocaModelAnimate;
Model roca2ModelAnimate;
Model roca3ModelAnimate;
Model roca4ModelAnimate;


// Terrain model instance
Terrain terrain(-1, -1, 200, 32, "../Textures/Prueba.png");


GLuint textureTerrainBackgroundID, textureTerrainRID, textureTerrainGID,
textureTerrainBID, textureTerrainBlendMapID;
GLuint textureParticleFireID, texId;
GLuint skyboxTextureID;
GLuint textureInicioID, textureInicio2ID, textureActivaID;
GLuint textureVidasID, textureVidas2ID, textureVidas3ID, textureVidas4ID;
GLuint textureObjetivosID, textureControlesID, textureCompletadoID, textureGameOverID;

// Modelo para el redener de texto
FontTypeRendering::FontTypeRendering* modelText;
FontTypeRendering::FontTypeRendering* modelText2;
FontTypeRendering::FontTypeRendering* modelText3;

GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/mp_bloodvalley/blood-valley_ft.tga",
		"../Textures/mp_bloodvalley/blood-valley_bk.tga",
		"../Textures/mp_bloodvalley/blood-valley_up.tga",
		"../Textures/mp_bloodvalley/blood-valley_dn.tga",
		"../Textures/mp_bloodvalley/blood-valley_rt.tga",
		"../Textures/mp_bloodvalley/blood-valley_lf.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

// Model matrix definitions
glm::mat4 modelMatrixIronman = glm::mat4(1.0f);

glm::mat4 modelMatrixZombie = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie1 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie2 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie3 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie4 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie5 = glm::mat4(1.0f);

glm::mat4 modelMatrixZombie6 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie7 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie8 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie9 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie10 = glm::mat4(1.0f);
glm::mat4 modelMatrixZombie11 = glm::mat4(1.0f);

//Entorno
glm::mat4 modelMatrixReja = glm::mat4(1.0f);
glm::mat4 modelMatrixReja2 = glm::mat4(1.0f);

glm::mat4 modelMatrixLimite = glm::mat4(1.0f);
glm::mat4 modelMatrixLimite2 = glm::mat4(1.0f);
glm::mat4 modelMatrixLimite3 = glm::mat4(1.0f);
glm::mat4 modelMatrixLimite4 = glm::mat4(1.0f);

glm::mat4 modelMatrixEntrada = glm::mat4(1.0f);
glm::mat4 modelMatrixEntrada2 = glm::mat4(1.0f);

glm::mat4 modelMatrixGas = glm::mat4(1.0f);

glm::mat4 modelMatrixCarro = glm::mat4(1.0f);
glm::mat4 modelMatrixCarro2 = glm::mat4(1.0f);
glm::mat4 modelMatrixCarro3 = glm::mat4(1.0f);
glm::mat4 modelMatrixCarrop = glm::mat4(1.0f);

glm::mat4 modelMatrixApartamentos = glm::mat4(1.0f);

glm::mat4 modelMatrixArbol = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol2 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol3 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol4 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol5 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol6 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol7 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol8 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol9 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol10 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol11 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol12 = glm::mat4(1.0f);
glm::mat4 modelMatrixArbol13 = glm::mat4(1.0f);
glm::mat4 modelMatrixRoca = glm::mat4(1.0f);
glm::mat4 modelMatrixRoca2 = glm::mat4(1.0f);
glm::mat4 modelMatrixRoca3 = glm::mat4(1.0f);
glm::mat4 modelMatrixRoca4 = glm::mat4(1.0f);

int animationIndex;
int animationIndexZombie;
int animationIndexZombie0;
int animationIndexZombie1;
int animationIndexZombie2;
int animationIndexZombie3;
int animationIndexZombie4;


int modelSelected = 2;
bool reinicio = false;
bool win = false;
// Variables to animations keyframes

bool iniciaPartida = false;
bool presionarOpcion = false;
int zombieMuerte = 0;
int zombie1Muerte = 0;
int zombie2Muerte = 0;
int zombie3Muerte = 0;
int zombie4Muerte = 0;
int zombie5Muerte = 0;
int zombie6Muerte = 0;
int zombie7Muerte = 0;
int zombie8Muerte = 0;
int zombie9Muerte = 0;
int state4 = 0;
int state = 0;
int state1 = 0;
int state2 = 0;
int state3 = 0;
double tiempo_final = 0;


// Lamps positions
std::vector<glm::vec3> lamp1Position = { glm::vec3(44, 0, 45), glm::vec3(
		54, 0, 45), glm::vec3(44, 0, 0), glm::vec3(44, 0, 0) };
std::vector<float> lamp1Orientation = { 0, 0, 0, 0 };

std::vector<glm::vec3> lamp2Position = { glm::vec3(80, 0, 52),
		glm::vec3(60, 0, 52), glm::vec3(40, 0, 52), glm::vec3(20, 0, 75), glm::vec3(20, 0, 95),
		glm::vec3(-57, 0, 87.5), glm::vec3(-57, 0, 64), glm::vec3(-57, 0, 33), glm::vec3(-72.5, 0, 21), glm::vec3(-92, 0, 21) };
std::vector<float> lamp2Orientation = { 0, 0, 0, 90, 90, -90, -90, -90, 0, 0 };

// Blending model unsorted
std::map<std::string, glm::vec3> blendingUnsorted = {
	{ "fire", glm::vec3(44, 2.8, 45) },
	{ "fire2", glm::vec3(54, 2.8, 45) },
	{ "fire3", glm::vec3(44, 2.8, 0) },
	{ "fire4", glm::vec3(44, 2.8, 0) },
};

double deltaTime;
double currTime, lastTime;

//Bullet
//bool enableBulletFiring = true;
//bool bulletIsActive = false;
//float bulletMovement = 0.0;
//float bulletMaxMovement = 6.0;
bool renderRoca = true;
bool renderZombie = true;
bool renderZombie1 = true;
bool renderZombie2 = true;
bool renderZombie3 = true;
bool renderZombie4 = true;
bool renderZombie5 = true;
bool renderZombie6 = true;
bool renderZombie7 = true;
bool renderZombie8 = true;
bool renderZombie9 = true;
bool renderRay = false;
bool boolMuerto = false;
int puntaje = 0;
int renderVidas = 3;


// Definition for the particle system
GLuint initVel, startTime;
GLuint VAOParticles;
GLuint nParticles = 8000;
double currTimeParticlesAnimation, lastTimeParticlesAnimation;

// Definition for the particle system fire
GLuint initVelFire, startTimeFire;
GLuint VAOParticlesFire;
GLuint nParticlesFire = 2000;
GLuint posBuf[2], velBuf[2], age[2];
GLuint particleArray[2];
GLuint feedback[2];
GLuint drawBuf = 1;
float particleSize = 0.5, particleLifetime = 3.0;
double currTimeParticlesAnimationFire, lastTimeParticlesAnimationFire;

// Colliders
std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;
std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> > collidersSBB;

// Framesbuffers
GLuint depthMap, depthMapFBO;


double tiempoEvento1 = 0, tiempoEvento2 = 0;

/**********************
 * OpenAL config
 */

 // OpenAL Defines
#define NUM_BUFFERS 3
#define NUM_SOURCES 3
#define NUM_ENVIRONMENTS 1
// Listener
ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
// Source 0
//ALfloat source0Pos[] = { -2.0, 0.0, 0.0 };
//ALfloat source0Vel[] = { 0.0, 0.0, 0.0 };
// Source 1
ALfloat source1Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source1Vel[] = { 0.0, 0.0, 0.0 };
// Source 2
ALfloat source2Pos[] = { 2.0, 0.0, 0.0 };
ALfloat source2Vel[] = { 0.0, 0.0, 0.0 };
// Buffers
ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];
// Configs
ALsizei size, freq;
ALenum format;
ALvoid* data;
int ch;
ALboolean loop;
std::vector<bool> sourcesPlay = { true, true, true };

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode);
void mouseCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void initParticleBuffers();
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);
void prepareScene();
void prepareDepthScene();
void renderScene(bool renderParticles = true);

void initParticleBuffers() {
	// Generate the buffers
	glGenBuffers(1, &initVel);   // Initial velocity buffer
	glGenBuffers(1, &startTime); // Start time buffer

	// Allocate space for all buffers
	int size = nParticles * 3 * sizeof(float);
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glBufferData(GL_ARRAY_BUFFER, nParticles * sizeof(float), NULL,
		GL_STATIC_DRAW);

	// Fill the first velocity buffer with random velocities
	glm::vec3 v(0.0f);
	float velocity, theta, phi;
	GLfloat* data = new GLfloat[nParticles * 3];
	for (unsigned int i = 0; i < nParticles; i++) {

		theta = glm::mix(0.0f, glm::pi<float>() / 6.0f,
			((float)rand() / RAND_MAX));
		phi = glm::mix(0.0f, glm::two_pi<float>(), ((float)rand() / RAND_MAX));

		v.x = sinf(theta) * cosf(phi);
		v.y = cosf(theta);
		v.z = sinf(theta) * sinf(phi);

		velocity = glm::mix(0.6f, 0.8f, ((float)rand() / RAND_MAX));
		v = glm::normalize(v) * velocity;

		data[3 * i] = v.x;
		data[3 * i + 1] = v.y;
		data[3 * i + 2] = v.z;
	}
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);

	// Fill the start time buffer
	delete[] data;
	data = new GLfloat[nParticles];
	float time = 0.0f;
	float rate = 0.00075f;
	for (unsigned int i = 0; i < nParticles; i++) {
		data[i] = time;
		time += rate;
	}
	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nParticles * sizeof(float), data);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	delete[] data;

	glGenVertexArrays(1, &VAOParticles);
	glBindVertexArray(VAOParticles);
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void initParticleBuffersFire() {
	// Generate the buffers
	glGenBuffers(2, posBuf);    // position buffers
	glGenBuffers(2, velBuf);    // velocity buffers
	glGenBuffers(2, age);       // age buffers

	// Allocate space for all buffers
	int size = nParticlesFire * sizeof(GLfloat);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, velBuf[0]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, velBuf[1]);
	glBufferData(GL_ARRAY_BUFFER, 3 * size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_COPY);
	glBindBuffer(GL_ARRAY_BUFFER, age[1]);
	glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_COPY);

	// Fill the first age buffer
	std::vector<GLfloat> initialAge(nParticlesFire);
	float rate = particleLifetime / nParticlesFire;
	for (unsigned int i = 0; i < nParticlesFire; i++) {
		int index = i - nParticlesFire;
		float result = rate * index;
		initialAge[i] = result;
	}
	// Shuffle them for better looking results
	//Random::shuffle(initialAge);
	auto rng = std::default_random_engine{ };
	std::shuffle(initialAge.begin(), initialAge.end(), rng);
	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, initialAge.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Create vertex arrays for each set of buffers
	glGenVertexArrays(2, particleArray);

	// Set up particle array 0
	glBindVertexArray(particleArray[0]);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, velBuf[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, age[0]);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	// Set up particle array 1
	glBindVertexArray(particleArray[1]);
	glBindBuffer(GL_ARRAY_BUFFER, posBuf[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, velBuf[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, age[1]);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	// Setup the feedback objects
	glGenTransformFeedbacks(2, feedback);

	// Transform feedback 0
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velBuf[0]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, age[0]);

	// Transform feedback 1
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, posBuf[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, velBuf[1]);
	glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 2, age[1]);

	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
}

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
			glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
			nullptr);

	if (window == nullptr) {
		std::cerr
			<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
			<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Inicialización de los shaders
	shaderTexture.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado.fs");
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox_fog.fs");
	shaderMulLighting.initialize(
		"../Shaders/iluminacion_textura_animation_shadow.vs",
		"../Shaders/multipleLights_shadow.fs");
	shaderTerrain.initialize("../Shaders/terrain_shadow.vs",
		"../Shaders/terrain_shadow.fs");
	//shaderParticlesFountain.initialize("../Shaders/particlesFountain.vs",
	//		"../Shaders/particlesFountain.fs");
	shaderParticlesFire.initialize("../Shaders/particlesFire.vs",
		"../Shaders/particlesFire.fs", { "Position", "Velocity", "Age" });
	shaderViewDepth.initialize("../Shaders/texturizado.vs",
		"../Shaders/texturizado_depth_view.fs");
	shaderDepth.initialize("../Shaders/shadow_mapping_depth.vs",
		"../Shaders/shadow_mapping_depth.fs");

	// Inicializacion de los objetos.
	boxInicio.init();
	boxInicio.setShader(&shaderTexture);
	boxInicio.setScale(glm::vec3(2.0, 2.0, 1.0));

	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(100.0f, 100.0f, 100.0f));

	boxCollider.init();
	boxCollider.setShader(&shader);
	boxCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	sphereCollider.init();
	sphereCollider.setShader(&shader);
	sphereCollider.setColor(glm::vec4(1.0, 1.0, 1.0, 1.0));

	cylinder.init();
	cylinder.setShader(&shader);
	cylinder.setColor(glm::vec4(0.0, 1.0, 1.0, 1.0));

	boxViewDepth.init();
	boxViewDepth.setShader(&shaderViewDepth);

	boxLightViewBox.init();
	boxLightViewBox.setShader(&shaderViewDepth);

	terrain.init();
	terrain.setShader(&shaderTerrain);
	terrain.setPosition(glm::vec3(100, 0, 100));


	//Lamp models
	modelLamp1.loadModel("../models/barril/barril.obj");
	modelLamp1.setShader(&shaderMulLighting);
	modelLamp2.loadModel("../models/lampara/lampara.obj");
	modelLamp2.setShader(&shaderMulLighting);

	//Grass
	modelGrass.loadModel("../models/grass/grassModel.obj");
	modelGrass.setShader(&shaderMulLighting);

	//Fountain
	//modelFountain.loadModel("../models/fountain/fountain.obj");
	//modelFountain.setShader(&shaderMulLighting);

	//Ironman
	ironmanModelAnimate.loadModel("../models/ironman/ultimate7.fbx");
	ironmanModelAnimate.setShader(&shaderMulLighting);

	//Zombie
	zombieModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombieModelAnimate.setShader(&shaderMulLighting);
	zombie1ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie1ModelAnimate.setShader(&shaderMulLighting);
	zombie2ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie2ModelAnimate.setShader(&shaderMulLighting);
	zombie3ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie3ModelAnimate.setShader(&shaderMulLighting);
	zombie4ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie4ModelAnimate.setShader(&shaderMulLighting);
	zombie5ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie5ModelAnimate.setShader(&shaderMulLighting);

	zombie6ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie6ModelAnimate.setShader(&shaderMulLighting);
	zombie7ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie7ModelAnimate.setShader(&shaderMulLighting);
	zombie8ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie8ModelAnimate.setShader(&shaderMulLighting);
	zombie9ModelAnimate.loadModel("../models/Zombie/zombieFullE.fbx");
	zombie9ModelAnimate.setShader(&shaderMulLighting);
	//Entorno
	rejaModelAnimate.loadModel("../models/reja/reja.obj");
	rejaModelAnimate.setShader(&shaderMulLighting);
	reja2ModelAnimate.loadModel("../models/reja/reja2.obj");
	reja2ModelAnimate.setShader(&shaderMulLighting);

	limiteModelAnimate.loadModel("../models/letrero/letrero.obj");
	limiteModelAnimate.setShader(&shaderMulLighting);
	limite2ModelAnimate.loadModel("../models/letrero/letrero.obj");
	limite2ModelAnimate.setShader(&shaderMulLighting);
	limite3ModelAnimate.loadModel("../models/letrero/letrero.obj");
	limite3ModelAnimate.setShader(&shaderMulLighting);
	limite4ModelAnimate.loadModel("../models/letrero/letrero.obj");
	limite4ModelAnimate.setShader(&shaderMulLighting);

	entradaModelAnimate.loadModel("../models/entrada/entrada.obj");
	entradaModelAnimate.setShader(&shaderMulLighting);
	entrada2ModelAnimate.loadModel("../models/entrada/entrada2.obj");
	entrada2ModelAnimate.setShader(&shaderMulLighting);

	gasModelAnimate.loadModel("../models/estacion gas/estacion.obj");
	gasModelAnimate.setShader(&shaderMulLighting);

	carroModelAnimate.loadModel("../models/coches/carro1.obj");
	carroModelAnimate.setShader(&shaderMulLighting);
	carro2ModelAnimate.loadModel("../models/coches/carro2.obj");
	carro2ModelAnimate.setShader(&shaderMulLighting);
	carro3ModelAnimate.loadModel("../models/coches/carro3.obj");
	carro3ModelAnimate.setShader(&shaderMulLighting);
	carropModelAnimate.loadModel("../models/coches/carrop.obj");
	carropModelAnimate.setShader(&shaderMulLighting);

	apartamentosModelAnimate.loadModel("../models/apartamentos/apartamentos.obj");
	apartamentosModelAnimate.setShader(&shaderMulLighting);

	arbolModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbolModelAnimate.setShader(&shaderMulLighting);
	arbol2ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol2ModelAnimate.setShader(&shaderMulLighting);
	arbol3ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol3ModelAnimate.setShader(&shaderMulLighting);
	arbol4ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol4ModelAnimate.setShader(&shaderMulLighting);
	arbol5ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol5ModelAnimate.setShader(&shaderMulLighting);
	arbol6ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol6ModelAnimate.setShader(&shaderMulLighting);
	arbol7ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol7ModelAnimate.setShader(&shaderMulLighting);
	arbol8ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol8ModelAnimate.setShader(&shaderMulLighting);
	arbol9ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol9ModelAnimate.setShader(&shaderMulLighting);
	arbol10ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol10ModelAnimate.setShader(&shaderMulLighting);
	arbol11ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol11ModelAnimate.setShader(&shaderMulLighting);
	arbol12ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol12ModelAnimate.setShader(&shaderMulLighting);
	arbol13ModelAnimate.loadModel("../models/arbol/arbol.obj");
	arbol13ModelAnimate.setShader(&shaderMulLighting);
	rocaModelAnimate.loadModel("../models/rocas/roca1.obj");
	rocaModelAnimate.setShader(&shaderMulLighting);
	roca2ModelAnimate.loadModel("../models/rocas/roca2.obj");
	roca2ModelAnimate.setShader(&shaderMulLighting);
	roca3ModelAnimate.loadModel("../models/rocas/roca3.obj");
	roca3ModelAnimate.setShader(&shaderMulLighting);
	roca4ModelAnimate.loadModel("../models/rocas/roca4.obj");
	roca4ModelAnimate.setShader(&shaderMulLighting);

	camera->setPosition(glm::vec3(0.0, 0.0, 10.0));
	camera->setDistanceFromTarget(distanceFromTarget);
	camera->setSensitivity(1.0);

	// Definimos el tamanio de la imagen
	int imageWidth, imageHeight;
	FIBITMAP* bitmap;
	unsigned char* data;

	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		FIBITMAP* bitmap = skyboxTexture.loadImage(true);
		unsigned char* data = skyboxTexture.convertToData(bitmap, imageWidth,
			imageHeight);
		if (data) {
			glTexImage2D(types[i], 0, GL_RGBA, imageWidth, imageHeight, 0,
				GL_BGRA, GL_UNSIGNED_BYTE, data);
		}
		else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage(bitmap);
	}

	

	// Definiendo la textura a utilizar
	Texture textureInicio1("../Textures/Inicio1.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureInicio1.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureInicio1.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureInicioID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureInicioID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureInicio1.freeImage(bitmap);


	// Definiendo la textura a utilizar
	Texture textureVidas("../Textures/tresVidas.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureVidas.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureVidas.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureVidasID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureVidasID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureVidas.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureVidas2("../Textures/dosVidas.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureVidas2.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureVidas2.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureVidas2ID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureVidas2ID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureVidas2.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureVidas3("../Textures/unaVidas.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureVidas3.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureVidas3.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureVidas3ID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureVidas3ID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureVidas3.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureVidas4("../Textures/ceroVidas.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureVidas4.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureVidas4.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureVidas4ID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureVidas4ID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureVidas4.freeImage(bitmap);

	// Definiendo la textura a utilizar
		Texture textureInicio2("../Textures/Inicio2.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureInicio2.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureInicio2.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureInicio2ID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureInicio2ID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureInicio2.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureGameOver("../Textures/Completado.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureGameOver.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureGameOver.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureCompletadoID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureCompletadoID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureGameOver.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureCompletado("../Textures/Derrota.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureCompletado.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureCompletado.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureGameOverID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureGameOverID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureCompletado.freeImage(bitmap);


	// Definiendo la textura a utilizar
	Texture textureObjetivos("../Textures/Objetivos.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureObjetivos.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureObjetivos.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureObjetivosID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureObjetivosID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureObjetivos.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureControles("../Textures/Controles.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureControles.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureControles.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureControlesID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureControlesID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureControles.freeImage(bitmap);



	;

	// Definiendo la textura a utilizar
	Texture textureTerrainBackground("../Textures/Grass_Proyecto.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainBackground.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainBackground.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBackgroundID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBackground.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainR("../Textures/Sand_Proyecto.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainR.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainR.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainRID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainR.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainG("../Textures/Snow_Proyecto.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainG.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainG.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainGID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainG.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainB("../Textures/Pavimento_Proyecto.jpg");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainB.loadImage();
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainB.convertToData(bitmap, imageWidth, imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainB.freeImage(bitmap);

	// Definiendo la textura a utilizar
	Texture textureTerrainBlendMap("../Textures/Prueba2.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	bitmap = textureTerrainBlendMap.loadImage(true);
	// Convertimos el mapa de bits en un arreglo unidimensional de tipo unsigned char
	data = textureTerrainBlendMap.convertToData(bitmap, imageWidth,
		imageHeight);
	// Creando la textura con id 1
	glGenTextures(1, &textureTerrainBlendMapID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (data) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureTerrainBlendMap.freeImage(bitmap);

	//Texture textureParticlesFountain("../Textures/bluewater.png");
	//bitmap = textureParticlesFountain.loadImage();
	//data = textureParticlesFountain.convertToData(bitmap, imageWidth,
	//		imageHeight);
	//glGenTextures(1, &textureParticleFountainID);
	//glBindTexture(GL_TEXTURE_2D, textureParticleFountainID);
	//// set the texture wrapping parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//if (data) {
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
	//	GL_BGRA, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//} else
	//	std::cout << "Failed to load texture" << std::endl;
	//textureParticlesFountain.freeImage(bitmap);

	Texture textureParticleFire("../Textures/fire.png");
	bitmap = textureParticleFire.loadImage();
	data = textureParticleFire.convertToData(bitmap, imageWidth, imageHeight);
	glGenTextures(1, &textureParticleFireID);
	glBindTexture(GL_TEXTURE_2D, textureParticleFireID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0,
			GL_BGRA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load texture" << std::endl;
	textureParticleFire.freeImage(bitmap);

	std::uniform_real_distribution<float> distr01 =
		std::uniform_real_distribution<float>(0.0f, 1.0f);
	std::mt19937 generator;
	std::random_device rd;
	generator.seed(rd());
	int size = nParticlesFire * 2;
	std::vector<GLfloat> randData(size);
	for (int i = 0; i < randData.size(); i++) {
		randData[i] = distr01(generator);
	}

	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_1D, texId);
	glTexStorage1D(GL_TEXTURE_1D, 1, GL_R32F, size);
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, size, GL_RED, GL_FLOAT,
		randData.data());
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	shaderParticlesFire.setInt("Pass", 1);
	shaderParticlesFire.setInt("ParticleTex", 0);
	shaderParticlesFire.setInt("RandomTex", 1);
	shaderParticlesFire.setFloat("ParticleLifetime", particleLifetime);
	shaderParticlesFire.setFloat("ParticleSize", particleSize);
	shaderParticlesFire.setVectorFloat3("Accel", glm::value_ptr(glm::vec3(0.0f, 0.1f, 0.0f)));
	shaderParticlesFire.setVectorFloat3("Emitter", glm::value_ptr(glm::vec3(0.0f)));

	glm::mat3 basis;
	glm::vec3 u, v, n;
	v = glm::vec3(0, 1, 0);
	n = glm::cross(glm::vec3(1, 0, 0), v);
	if (glm::length(n) < 0.00001f) {
		n = glm::cross(glm::vec3(0, 1, 0), v);
	}
	u = glm::cross(v, n);
	basis[0] = glm::normalize(u);
	basis[1] = glm::normalize(v);
	basis[2] = glm::normalize(n);
	shaderParticlesFire.setMatrix3("EmitterBasis", 1, false, glm::value_ptr(basis));

	/*******************************************
	 * Inicializacion de los buffers de la fuente
	 *******************************************/
	initParticleBuffers();

	/*******************************************
	 * Inicializacion de los buffers del fuego
	 *******************************************/
	initParticleBuffersFire();

	/*******************************************
	 * Inicializacion del framebuffer para
	 * almacenar el buffer de profunidadad
	 *******************************************/
	glGenFramebuffers(1, &depthMapFBO);
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH,
		SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
		depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	/*******************************************
	 * OpenAL init
	 *******************************************/
	alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);
	alGetError(); // clear any error messages
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}
	// Config source 0
	// Generate buffers, or else no sound will happen!
	alGenBuffers(NUM_BUFFERS, buffer);
	buffer[1] = alutCreateBufferFromFile("../sounds/fire.wav");
	buffer[2] = alutCreateBufferFromFile("../sounds/zombie.wav");
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR) {
		printf("- Error open files with alut %d !!\n", errorAlut);
		exit(2);
	}

	alGetError(); /* clear error */
	alGenSources(NUM_SOURCES, source);

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}

	alSourcef(source[1], AL_PITCH, 1.0f);
	alSourcef(source[1], AL_GAIN, 3.0f);
	alSourcefv(source[1], AL_POSITION, source1Pos);
	alSourcefv(source[1], AL_VELOCITY, source1Vel);
	alSourcei(source[1], AL_BUFFER, buffer[1]);
	alSourcei(source[1], AL_LOOPING, AL_TRUE);
	alSourcef(source[1], AL_MAX_DISTANCE, 2000);

	alSourcef(source[2], AL_PITCH, 1.0f);
	alSourcef(source[2], AL_GAIN, 0.1f);
	alSourcefv(source[2], AL_POSITION, source2Pos);
	alSourcefv(source[2], AL_VELOCITY, source2Vel);
	alSourcei(source[2], AL_BUFFER, buffer[2]);
	alSourcei(source[2], AL_LOOPING, AL_TRUE);
	alSourcef(source[2], AL_MAX_DISTANCE, 1);

	// Se inicializa el modelo de texeles.
	modelText = new FontTypeRendering::FontTypeRendering(screenWidth,
		screenHeight);
	modelText->Initialize("../Fonts/BauhausBold.ttf");

	modelText2 = new FontTypeRendering::FontTypeRendering(screenWidth,
		screenHeight);
	modelText2->Initialize("../Fonts/BauhausBold.ttf");

	modelText3 = new FontTypeRendering::FontTypeRendering(screenWidth,
		screenHeight);
	modelText3->Initialize("../Fonts/BauhausBold.ttf");
}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Shaders Delete
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();
	//shaderParticlesFountain.destroy();
	shaderParticlesFire.destroy();

	// Basic objects Delete
	skyboxSphere.destroy();
	boxCollider.destroy();
	sphereCollider.destroy();
	cylinder.destroy();
	boxViewDepth.destroy();
	boxLightViewBox.destroy();

	// Terrains objects Delete
	terrain.destroy();
	
	modelLamp1.destroy();
	modelLamp2.destroy();
	modelGrass.destroy();

	// Custom objects animate
	ironmanModelAnimate.destroy();

	zombieModelAnimate.destroy();
	zombie1ModelAnimate.destroy();
	zombie2ModelAnimate.destroy();
	zombie3ModelAnimate.destroy();
	zombie4ModelAnimate.destroy();
	zombie5ModelAnimate.destroy();
	zombie6ModelAnimate.destroy();
	zombie7ModelAnimate.destroy();
	zombie8ModelAnimate.destroy();
	zombie9ModelAnimate.destroy();

	//Entorno
	rejaModelAnimate.destroy();
	reja2ModelAnimate.destroy();
	limiteModelAnimate.destroy();
	limite2ModelAnimate.destroy();
	limite3ModelAnimate.destroy();
	limite4ModelAnimate.destroy();
	entradaModelAnimate.destroy();
	entrada2ModelAnimate.destroy();
	gasModelAnimate.destroy();
	carroModelAnimate.destroy();
	carro2ModelAnimate.destroy();
	carro3ModelAnimate.destroy();
	carropModelAnimate.destroy();
	apartamentosModelAnimate.destroy();
	arbolModelAnimate.destroy();
	arbol2ModelAnimate.destroy();
	arbol3ModelAnimate.destroy();
	arbol4ModelAnimate.destroy();
	arbol5ModelAnimate.destroy();
	arbol6ModelAnimate.destroy();
	arbol7ModelAnimate.destroy();
	arbol8ModelAnimate.destroy();
	arbol9ModelAnimate.destroy();
	arbol10ModelAnimate.destroy();
	arbol11ModelAnimate.destroy();
	arbol12ModelAnimate.destroy();
	arbol13ModelAnimate.destroy();
	rocaModelAnimate.destroy();
	roca2ModelAnimate.destroy();
	roca3ModelAnimate.destroy();
	roca4ModelAnimate.destroy();

	// Textures Delete
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &textureTerrainBackgroundID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainBlendMapID);
	glDeleteTextures(1, &textureParticleFireID);

	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);

	// Remove the buffer of the fountain particles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &initVel);
	glDeleteBuffers(1, &startTime);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAOParticles);

	// Remove the buffer of the fire particles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(2, posBuf);
	glDeleteBuffers(2, velBuf);
	glDeleteBuffers(2, age);
	glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, 0);
	glDeleteTransformFeedbacks(2, feedback);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAOParticlesFire);
}

void reshapeCallback(GLFWwindow* Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
	int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void delay(float secs)
{
	float end = clock() / CLOCKS_PER_SEC + secs;
	while ((clock() / CLOCKS_PER_SEC) < end);
}


void mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	distanceFromTarget -= yoffset;
	camera->setDistanceFromTarget(distanceFromTarget);
}

void mouseButtonCallback(GLFWwindow* window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}


	/*bool presionarEnter2 = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
	if (!iniciaPartida) {	
		bool presionarEnter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;		

		if (textureActivaID == textureInicioID && presionarEnter)
			iniciaPartida = true;
		tiempoEvento1 = TimeManager::Instance().GetTime();

		if (textureActivaID == textureInicio2ID && presionarEnter)
			exitApp = true;

		if (!presionarOpcion && glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
			presionarOpcion = true;
			if (textureActivaID == textureInicioID)
				textureActivaID = textureInicio2ID;
			else if (textureActivaID == textureInicio2ID)
				textureActivaID = textureInicioID;
		}
		else if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_RELEASE)
			presionarOpcion = false;
	}

	if (boolMuerto && presionarEnter2){
			exitApp = true;
	}

	if (win && presionarEnter2) {
		exitApp = true;
	}*/

	if (glfwJoystickPresent(GLFW_JOYSTICK_1) == GL_TRUE) {
		//std::cout << "Esta presente el joystick" << std::endl;
		int axesCount, buttonCount;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
		//std::cout << "Número de ejes disponibles :=>" << axesCount << std::endl;
		//std::cout << "Left Stick X axis: " << axes[0] << std::endl;
		//std::cout << "Left Stick Y axis: " << axes[1] << std::endl;
		//std::cout << "Right Stick X axis: " << axes[2] << std::endl;
		//std::cout << "Right Stick Y axis: " << axes[3] << std::endl;
		//std::cout << "Left Trigger/L2: " << axes[4] << std::endl;
		//std::cout << "Right Trigger/R2: " << axes[5] << std::endl;

		if (fabs(axes[1]) > 0.2) {//Avanzar y retroceder
			modelMatrixIronman = glm::translate(modelMatrixIronman,
				glm::vec3(0, 0, axes[1] * 0.25));
				animationIndex = 0;
		}
		if (fabs(axes[0]) > 0.2) {//Left stick
			modelMatrixIronman = glm::rotate(modelMatrixIronman,
				glm::radians(-axes[0] * 1.2f), glm::vec3(0, 1, 0));
				animationIndex = 0;
		}

		if (fabs(axes[2]) > 0.2) {
			camera->mouseMoveCamera(axes[2], 0.0, deltaTime);
		}

		if (fabs(axes[3]) > 0.2) {
			camera->mouseMoveCamera(0.0, axes[3], deltaTime);
		}

		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

			/*buttons[0] equis
			buttons[1] circulo
			buttons[2] cuadrado
			buttons[3] traingulo
			buttons[4] L1
			buttons[5] R1
			buttons[6] SELECT
			buttons[7] OPTIONS
			buttons[8] L3
			buttons[9] R3
			buttons[10] ARRIBA
			buttons[11] DERECHA
			buttons[12] ABAJO
			buttons[13] IZQUIERDA
			*/

		if (buttons[5] == GLFW_PRESS && win != true){
			renderRay = true;
			std::cout << "Se presiona R1" << std::endl;
		}
		else
		{
			renderRay = false;
		}



		bool presionarEnter2 = buttons[0] == GLFW_PRESS;
		if (!iniciaPartida) {
			bool presionarEnter = buttons[0] == GLFW_PRESS;

			if (textureActivaID == textureInicioID && presionarEnter)
				iniciaPartida = true;
			tiempoEvento1 = TimeManager::Instance().GetTime();

			if (textureActivaID == textureInicio2ID && presionarEnter)
				exitApp = true;

			if (!presionarOpcion && buttons[12]) {
				presionarOpcion = true;
				if (textureActivaID == textureInicioID)
					textureActivaID = textureInicio2ID;
				else if (textureActivaID == textureInicio2ID)
					textureActivaID = textureInicioID;
			}
			else if (buttons[12] == GLFW_RELEASE)
				presionarOpcion = false;
		}

		if (boolMuerto && presionarEnter2) {
			exitApp = true;
		}

		if (win && presionarEnter2) {
			exitApp = true;
		}





	}

	/*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		camera->mouseMoveCamera(offsetX, 0.0, deltaTime);
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		camera->mouseMoveCamera(0.0, offsetY, deltaTime);*/
	offsetX = 0;
	offsetY = 0;


	/*if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && win != true)
		renderRay = true;*/
	/*if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE)
		renderRay = false;*/

	
	//if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && win != true) {
	//	modelMatrixIronman = glm::rotate(modelMatrixIronman, glm::radians(2.5f),
	//		glm::vec3(0, 1, 0));
	//	animationIndex = 0;
	//}
	//else if (modelSelected
	//	== 2 && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && win != true) {
	//	modelMatrixIronman = glm::rotate(modelMatrixIronman, glm::radians(-2.5f),
	//		glm::vec3(0, 1, 0));
	//	animationIndex = 0;
	//}
	//if (modelSelected == 2 && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && win != true) {
	//	modelMatrixIronman = glm::translate(modelMatrixIronman,
	//		glm::vec3(0, 0, 0.20));
	//	animationIndex = 0;
	//}
	//else if (modelSelected
	//	== 2 && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && win != true) {
	//	modelMatrixIronman = glm::translate(modelMatrixIronman,
	//		glm::vec3(0, 0, -0.20));
	//	animationIndex = 0;
	//}

	glfwPollEvents();
	return continueApplication;
}

void applicationLoop() {
	bool psi = true;

	glm::mat4 view;
	glm::vec3 axis;
	glm::vec3 target;
	float angleTarget;
	int numberAdvanceZombies = 0;
	float rotCount = 0.0;
	float avanceCount = 0.0;
	float maxAdvanceZombie = 0.0;
	int numberAdvanceZombies2 = 0;
	float rotCount2 = 0.0;
	float avanceCount2 = 0.0;
	float maxAdvanceZombie2 = 0.0;

	int numberAdvanceZombies3 = 0;
	float rotCount3 = 0.0;
	float avanceCount3 = 0.0;
	float maxAdvanceZombie3 = 0.0;

	int numberAdvanceZombies4 = 0;
	float rotCount4 = 0.0;
	float avanceCount4 = 0.0;
	float maxAdvanceZombie4 = 0.0;
	int numberAdvanceZombies1 = 0;
	float rotCount1 = 0.0;
	float avanceCount1 = 0.0;
	float maxAdvanceZombie1 = 0.0;

	modelMatrixIronman = glm::translate(modelMatrixIronman, glm::vec3(48.0f, 0.0f, 64.0f));
	modelMatrixIronman = glm::rotate(modelMatrixIronman, glm::radians(-180.0f), glm::vec3(0, 1, 0));

	modelMatrixZombie = glm::translate(modelMatrixZombie, glm::vec3(25.0f, 0.0f, 0.0f));
	modelMatrixZombie1 = glm::translate(modelMatrixZombie1,glm::vec3(40.0f, 0.0f, 25.0f));
	modelMatrixZombie2 = glm::translate(modelMatrixZombie2,glm::vec3(20.0f, 0.0f, -10.0f));
	modelMatrixZombie3 = glm::translate(modelMatrixZombie3,glm::vec3(40.0f, 0.0f, -30.0f));
	modelMatrixZombie4 = glm::translate(modelMatrixZombie4,glm::vec3(30.0f, 0.0f, 0.0f));
	modelMatrixZombie5 = glm::translate(modelMatrixZombie5,glm::vec3(60.0f, 0.0f, -5.0f));
	modelMatrixZombie6 = glm::translate(modelMatrixZombie6, glm::vec3(80.0f, 0.0f, -10.0f));
	modelMatrixZombie7 = glm::translate(modelMatrixZombie7, glm::vec3(65.0f, 0.0f, 10.0f));
	modelMatrixZombie8 = glm::translate(modelMatrixZombie8, glm::vec3(80.0f, 0.0f, 20.0f));
	modelMatrixZombie9 = glm::translate(modelMatrixZombie9, glm::vec3(80.0f, 0.0f, 0.0f));

	//Entorno
	modelMatrixReja = glm::translate(modelMatrixReja, glm::vec3(16.28f, 0.0f, 74.78f));
	modelMatrixReja = glm::rotate(modelMatrixReja, glm::radians(-90.0f), glm::vec3(0, 1, 0));

	modelMatrixReja2 = glm::translate(modelMatrixReja2, glm::vec3(16.28f, 0.0f, 74.78f));
	modelMatrixReja2 = glm::rotate(modelMatrixReja2, glm::radians(-90.0f), glm::vec3(0, 1, 0));

	modelMatrixLimite = glm::translate(modelMatrixLimite, glm::vec3(95.31f, 0.0f, -2.34f));
	modelMatrixLimite = glm::rotate(modelMatrixLimite, glm::radians(-90.0f), glm::vec3(0, 1, 0));

	modelMatrixLimite2 = glm::translate(modelMatrixLimite2, glm::vec3(-95.31f, 0.0f, -2.34f));
	modelMatrixLimite2 = glm::rotate(modelMatrixLimite2, glm::radians(90.0f), glm::vec3(0, 1, 0));

	modelMatrixLimite3 = glm::translate(modelMatrixLimite3, glm::vec3(25.0f, 0.0f, 95.31f));
	modelMatrixLimite3 = glm::rotate(modelMatrixLimite3, glm::radians(180.0f), glm::vec3(0, 1, 0));

	modelMatrixLimite4 = glm::translate(modelMatrixLimite4, glm::vec3(-2.34f, 0.0f, -95.31f));

	modelMatrixEntrada = glm::translate(modelMatrixEntrada, glm::vec3(60.0f, 0.0f, 48.43f));

	modelMatrixEntrada2 = glm::translate(modelMatrixEntrada2, glm::vec3(60.0f, 0.0f, 48.43f));

	modelMatrixGas = glm::translate(modelMatrixGas, glm::vec3(50.0f, 0.0f, 80.0f));
	modelMatrixGas = glm::rotate(modelMatrixGas, glm::radians(180.0f), glm::vec3(0, 1, 0));

	modelMatrixCarro = glm::translate(modelMatrixCarro, glm::vec3(40.0f, 0.0f, 65.0f));
	modelMatrixCarro = glm::rotate(modelMatrixCarro, glm::radians(-45.0f), glm::vec3(0, 1, 0));

	modelMatrixCarro2 = glm::translate(modelMatrixCarro2, glm::vec3(30.0f, 0.0f, 70.0f));

	modelMatrixCarro3 = glm::translate(modelMatrixCarro3, glm::vec3(-80.0f, 0.0f, 30.0f));
	modelMatrixCarro3 = glm::rotate(modelMatrixCarro3, glm::radians(90.0f), glm::vec3(0, 1, 0));

	modelMatrixCarrop = glm::translate(modelMatrixCarrop, glm::vec3(-67.0f, 0.0f, 70.0f));

	modelMatrixApartamentos = glm::translate(modelMatrixApartamentos, glm::vec3(-80.0f, 0.0f, 85.0f));
	modelMatrixApartamentos = glm::rotate(modelMatrixApartamentos, glm::radians(-90.0f), glm::vec3(0, 1, 0));

	modelMatrixArbol = glm::translate(modelMatrixArbol, glm::vec3(30.0f, 0.0f, -40.0f));

	modelMatrixArbol2 = glm::translate(modelMatrixArbol2, glm::vec3(40.0f, 0.0f, -50.0f));

	modelMatrixArbol3 = glm::translate(modelMatrixArbol3, glm::vec3(35.0f, 0.0f, -65.0f));

	modelMatrixArbol4 = glm::translate(modelMatrixArbol4, glm::vec3(50.0f, 0.0f, -45.0f));

	modelMatrixArbol5 = glm::translate(modelMatrixArbol5, glm::vec3(60.0f, 0.0f, -60.0f));

	modelMatrixArbol6 = glm::translate(modelMatrixArbol6, glm::vec3(85.0f, 0.0f, -50.0f));

	modelMatrixArbol7 = glm::translate(modelMatrixArbol7, glm::vec3(70.0f, 0.0f, -75.0f));

	modelMatrixArbol8 = glm::translate(modelMatrixArbol8, glm::vec3(20.0f, 0.0f, -60.0f));

	modelMatrixArbol9 = glm::translate(modelMatrixArbol9, glm::vec3(5.0f, 0.0f, -70.0f));

	modelMatrixArbol10 = glm::translate(modelMatrixArbol10, glm::vec3(5.0f, 0.0f, -90.0f));

	modelMatrixArbol11 = glm::translate(modelMatrixArbol11, glm::vec3(-10.0f, 0.0f, -85.0f));

	modelMatrixArbol12 = glm::translate(modelMatrixArbol12, glm::vec3(-35.0f, 0.0f, -80.0f));

	modelMatrixArbol13 = glm::translate(modelMatrixArbol13, glm::vec3(-40.0f, 0.0f, -65.0f));

	modelMatrixRoca = glm::translate(modelMatrixRoca, glm::vec3(85.0f, 0.0f, -15.0f));
	modelMatrixRoca2 = glm::translate(modelMatrixRoca2, glm::vec3(83.0f, 0.0f, -25.0f));

	modelMatrixRoca3 = glm::translate(modelMatrixRoca3, glm::vec3(30.0f, 0.0f, 20.0f));

	modelMatrixRoca4 = glm::translate(modelMatrixRoca4, glm::vec3(30.0f, 0.0f, 28.0f));
	modelMatrixRoca4 = glm::rotate(modelMatrixRoca4, glm::radians(-45.0f), glm::vec3(0, 1, 0));

	//modelMatrixFountain = glm::translate(modelMatrixFountain, glm::vec3(5.0, 0.0, -40.0));


	//modelMatrixFountain[3][1] = terrain.getHeightTerrain(
	//		modelMatrixFountain[3][0], modelMatrixFountain[3][2]) + 0.2;
	//modelMatrixFountain = glm::scale(modelMatrixFountain,
	//		glm::vec3(10.0f, 10.0f, 10.0f));

	lastTime = TimeManager::Instance().GetTime();

	// Time for the particles animation
	currTimeParticlesAnimation = lastTime;
	lastTimeParticlesAnimation = lastTime;

	currTimeParticlesAnimationFire = lastTime;
	lastTimeParticlesAnimationFire = lastTime;

	glm::vec3 lightPos = glm::vec3(10.0, 10.0, 0.0);

	shadowBox = new ShadowBox(-lightPos, camera.get(), 15.0f, 0.1f, 45.0f);

	textureActivaID = textureInicioID;

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if (currTime - lastTime < 0.016666667) {
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(true);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		std::map<std::string, bool> collisionDetection;

		// Variables donde se guardan las matrices de cada articulacion por 1 frame
		std::vector<float> matrixDartJoints;
		std::vector<glm::mat4> matrixDart;

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
			(float)screenWidth / (float)screenHeight, 0.1f, 100.0f);

		if (modelSelected == 2) {
			axis = glm::axis(glm::quat_cast(modelMatrixIronman));
			angleTarget = glm::angle(glm::quat_cast(modelMatrixIronman));
			target = modelMatrixIronman[3];
		}

		if (std::isnan(angleTarget))
			angleTarget = 0.0;
		if (axis.y < 0)
			angleTarget = -angleTarget;
		if (modelSelected == 1)
			angleTarget -= glm::radians(90.0f);


		camera->setCameraTarget(target);
		camera->setAngleTarget(angleTarget);
		camera->updateCamera();
		view = camera->getViewMatrix();

		shadowBox->update(screenWidth, screenHeight);
		glm::vec3 centerBox = shadowBox->getCenter();

		// Projection light shadow mapping
		glm::mat4 lightProjection = glm::mat4(1.0f), lightView = glm::mat4(
			1.0f);
		glm::mat4 lightSpaceMatrix;

		lightProjection[0][0] = 2.0f / shadowBox->getWidth();
		lightProjection[1][1] = 2.0f / shadowBox->getHeight();
		lightProjection[2][2] = -2.0f / shadowBox->getLength();
		lightProjection[3][3] = 1.0f;

		lightView = glm::lookAt(centerBox,
			centerBox + glm::normalize(-lightPos),
			glm::vec3(0.0, 1.0, 0.0));

		lightSpaceMatrix = lightProjection * lightView;
		shaderDepth.setMatrix4("lightSpaceMatrix", 1, false,
			glm::value_ptr(lightSpaceMatrix));

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
			glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false, glm::value_ptr(view));
		shaderMulLighting.setMatrix4("lightSpaceMatrix", 1, false,
			glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderTerrain.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false, glm::value_ptr(view));
		shaderTerrain.setMatrix4("lightSpaceMatrix", 1, false,
			glm::value_ptr(lightSpaceMatrix));
		// Settea la matriz de vista y projection al shader para el fountain
		
		// Settea la matriz de vista y projection al shader para el fuego
		shaderParticlesFire.setInt("Pass", 2);
		shaderParticlesFire.setMatrix4("projection", 1, false,
			glm::value_ptr(projection));
		shaderParticlesFire.setMatrix4("view", 1, false, glm::value_ptr(view));

		/*******************************************
		 * Propiedades de neblina
		 *******************************************/
		shaderMulLighting.setFloat("density", 0.04);
		shaderMulLighting.setVectorFloat3("fogColor",
			//glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
			glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderTerrain.setFloat("density", 0.04);
		shaderTerrain.setVectorFloat3("fogColor",
			//glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
			glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		shaderSkybox.setVectorFloat3("fogColor",
			//glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
			glm::value_ptr(glm::vec3(0.5, 0.5, 0.5)));
		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos",
			glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient",
			glm::value_ptr(glm::vec3(0.05, 0.05, 0.05)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse",
			glm::value_ptr(glm::vec3(0.05, 0.05, 0.05)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular",
			glm::value_ptr(glm::vec3(0.1, 0.1, 0.05)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction",
			glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));


		/*******************************************
		 * Propiedades Luz direccional Terrain
		 *******************************************/
		shaderTerrain.setVectorFloat3("viewPos",
			glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient",
			glm::value_ptr(glm::vec3(0.05, 0.05, 0.05)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse",
			glm::value_ptr(glm::vec3(0.05, 0.05, 0.05)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular",
			glm::value_ptr(glm::vec3(0.1, 0.1, 0.05)));
		shaderTerrain.setVectorFloat3("directionalLight.direction",
			glm::value_ptr(glm::vec3(-0.707106781, -0.707106781, 0.0)));

		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/

		 /*******************************************
		  * Propiedades PointLights
		  *******************************************/
		shaderMulLighting.setInt("pointLightCount", lamp1Position.size() + lamp2Orientation.size());
		shaderTerrain.setInt("pointLightCount", lamp1Position.size() + lamp2Orientation.size());
		for (int i = 0; i < lamp1Position.size(); i++) {
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0f);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp1Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(0.5, 0.5, 0.5));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0, 10.3585, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.01);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(i) + "].quadratic", 0.02);
		}
		for (int i = 0; i < lamp2Position.size(); i++) {
			glm::mat4 matrixAdjustLamp = glm::mat4(1.0f);
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, lamp2Position[i]);
			matrixAdjustLamp = glm::rotate(matrixAdjustLamp, glm::radians(lamp2Orientation[i]), glm::vec3(0, 1, 0));
			matrixAdjustLamp = glm::scale(matrixAdjustLamp, glm::vec3(1.0, 1.0, 1.0));
			matrixAdjustLamp = glm::translate(matrixAdjustLamp, glm::vec3(0.759521, 5.00174, 0));
			glm::vec3 lampPosition = glm::vec3(matrixAdjustLamp[3]);
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderMulLighting.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderMulLighting.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.01);
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.ambient", glm::value_ptr(glm::vec3(0.2, 0.16, 0.01)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.diffuse", glm::value_ptr(glm::vec3(0.4, 0.32, 0.02)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].light.specular", glm::value_ptr(glm::vec3(0.6, 0.58, 0.03)));
			shaderTerrain.setVectorFloat3("pointLights[" + std::to_string(lamp1Position.size() + i) + "].position", glm::value_ptr(lampPosition));
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].constant", 1.0);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].linear", 0.09);
			shaderTerrain.setFloat("pointLights[" + std::to_string(lamp1Position.size() + i) + "].quadratic", 0.02);
		}


		if (!iniciaPartida) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glViewport(0, 0, screenWidth, screenHeight);
			shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
			shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureActivaID);
			shaderTexture.setInt("outTexture", 0);
			boxInicio.render();
			glfwSwapBuffers(window);
			continue;
		}

		/*******************************************
		 * 1.- We render the depth buffer
		 *******************************************/
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// render scene from light's point of view
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		//glCullFace(GL_FRONT);
		prepareDepthScene();
		renderScene(false);
		//glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		/*******************************************
		 * Debug to view the texture view map
		 *******************************************/

		  /*******************************************
		   * 2.- We render the normal objects
		   *******************************************/
		glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		prepareScene();
		glActiveTexture(GL_TEXTURE10);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		shaderMulLighting.setInt("shadowMap", 10);
		shaderTerrain.setInt("shadowMap", 10);


		//Rayo de ironman

		glm::mat4 modelMatrixRayI = glm::mat4(modelMatrixIronman);
		modelMatrixRayI = glm::translate(modelMatrixRayI, glm::vec3(0.0, 1.6, -0.3));
		glm::vec3 rayDirection = glm::normalize(glm::vec3(modelMatrixRayI[2]));
		glm::vec3 ori = glm::vec3(modelMatrixRayI[3]);
		glm::vec3 tar = ori + 5.0f * rayDirection;
		glm::vec3 dmd = ori + 2.5f * rayDirection;
		if (renderRay) {
			modelMatrixRayI[3] = glm::vec4(dmd, 1.0f);
			modelMatrixRayI = glm::rotate(modelMatrixRayI, glm::radians(90.0f), glm::vec3(1.0, 0, 0));
			modelMatrixRayI = glm::scale(modelMatrixRayI, glm::vec3(1.0, 5.0, 1.0));
			cylinder.render(modelMatrixRayI);
		}
		/*******************************************
		 * Skybox
		 *******************************************/
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);
		renderScene();


		shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
		glActiveTexture(GL_TEXTURE0);
		

				//Collider de arbol 2
		AbstractModel::OBB arbol2Collider;
		glm::mat4 modelmatrixColliderArbol2 = glm::mat4(modelMatrixArbol2);
		// Set the orientation of collider before doing the scale
		arbol2Collider.u = glm::quat_cast(modelmatrixColliderArbol2);
		modelmatrixColliderArbol2 = glm::scale(modelmatrixColliderArbol2,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol2 = glm::translate(modelmatrixColliderArbol2,
			glm::vec3(arbol2ModelAnimate.getObb().c.x,
				arbol2ModelAnimate.getObb().c.y,
				arbol2ModelAnimate.getObb().c.z));
		arbol2Collider.e = arbol2ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol2Collider.c = glm::vec3(modelmatrixColliderArbol2[3]);
		addOrUpdateColliders(collidersOBB, "arbol2", arbol2Collider,
			modelMatrixArbol2);

		//Collider de arbol 3
		AbstractModel::OBB arbol3Collider;
		glm::mat4 modelmatrixColliderArbol3 = glm::mat4(modelMatrixArbol3);
		// Set the orientation of collider before doing the scale
		arbol3Collider.u = glm::quat_cast(modelmatrixColliderArbol3);
		modelmatrixColliderArbol3 = glm::scale(modelmatrixColliderArbol3,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol3 = glm::translate(modelmatrixColliderArbol3,
			glm::vec3(arbol3ModelAnimate.getObb().c.x,
				arbol3ModelAnimate.getObb().c.y,
				arbol3ModelAnimate.getObb().c.z));
		arbol3Collider.e = arbol3ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol3Collider.c = glm::vec3(modelmatrixColliderArbol3[3]);
		addOrUpdateColliders(collidersOBB, "arbol3", arbol3Collider,
			modelMatrixArbol3);

		//Collider de arbol 4
		AbstractModel::OBB arbol4Collider;
		glm::mat4 modelmatrixColliderArbol4 = glm::mat4(modelMatrixArbol4);
		// Set the orientation of collider before doing the scale
		arbol4Collider.u = glm::quat_cast(modelmatrixColliderArbol4);
		modelmatrixColliderArbol4 = glm::scale(modelmatrixColliderArbol4,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol4 = glm::translate(modelmatrixColliderArbol4,
			glm::vec3(arbol4ModelAnimate.getObb().c.x,
				arbol4ModelAnimate.getObb().c.y,
				arbol4ModelAnimate.getObb().c.z));
		arbol4Collider.e = arbol4ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol4Collider.c = glm::vec3(modelmatrixColliderArbol4[3]);
		addOrUpdateColliders(collidersOBB, "arbol4", arbol4Collider,
			modelMatrixArbol4);

		//Collider de arbol 5 
		AbstractModel::OBB arbol5Collider;
		glm::mat4 modelmatrixColliderArbol5 = glm::mat4(modelMatrixArbol5);
		// Set the orientation of collider before doing the scale
		arbol5Collider.u = glm::quat_cast(modelmatrixColliderArbol5);
		modelmatrixColliderArbol5 = glm::scale(modelmatrixColliderArbol5,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol5 = glm::translate(modelmatrixColliderArbol5,
			glm::vec3(arbol5ModelAnimate.getObb().c.x,
				arbol5ModelAnimate.getObb().c.y,
				arbol5ModelAnimate.getObb().c.z));
		arbol5Collider.e = arbol5ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol5Collider.c = glm::vec3(modelmatrixColliderArbol5[3]);
		addOrUpdateColliders(collidersOBB, "arbol5", arbol5Collider,
			modelMatrixArbol5);

		//Collider de arbol 6
		AbstractModel::OBB arbol6Collider;
		glm::mat4 modelmatrixColliderArbol6 = glm::mat4(modelMatrixArbol6);
		// Set the orientation of collider before doing the scale
		arbol6Collider.u = glm::quat_cast(modelmatrixColliderArbol6);
		modelmatrixColliderArbol6 = glm::scale(modelmatrixColliderArbol6,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol6 = glm::translate(modelmatrixColliderArbol6,
			glm::vec3(arbol6ModelAnimate.getObb().c.x,
				arbol6ModelAnimate.getObb().c.y,
				arbol6ModelAnimate.getObb().c.z));
		arbol6Collider.e = arbol6ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol6Collider.c = glm::vec3(modelmatrixColliderArbol6[3]);
		addOrUpdateColliders(collidersOBB, "arbol6", arbol6Collider,
			modelMatrixArbol6);

		//Collider de arbol 7
		AbstractModel::OBB arbol7Collider;
		glm::mat4 modelmatrixColliderArbol7 = glm::mat4(modelMatrixArbol7);
		// Set the orientation of collider before doing the scale
		arbol7Collider.u = glm::quat_cast(modelmatrixColliderArbol7);
		modelmatrixColliderArbol7 = glm::scale(modelmatrixColliderArbol7,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol7 = glm::translate(modelmatrixColliderArbol7,
			glm::vec3(arbol7ModelAnimate.getObb().c.x,
				arbol7ModelAnimate.getObb().c.y,
				arbol7ModelAnimate.getObb().c.z));
		arbol7Collider.e = arbol7ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol7Collider.c = glm::vec3(modelmatrixColliderArbol7[3]);
		addOrUpdateColliders(collidersOBB, "arbol7", arbol7Collider,
			modelMatrixArbol7);

		//Collider de arbol 8
		AbstractModel::OBB arbol8Collider;
		glm::mat4 modelmatrixColliderArbol8 = glm::mat4(modelMatrixArbol8);
		// Set the orientation of collider before doing the scale
		arbol8Collider.u = glm::quat_cast(modelmatrixColliderArbol8);
		modelmatrixColliderArbol8 = glm::scale(modelmatrixColliderArbol8,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol8 = glm::translate(modelmatrixColliderArbol8,
			glm::vec3(arbol8ModelAnimate.getObb().c.x,
				arbol8ModelAnimate.getObb().c.y,
				arbol8ModelAnimate.getObb().c.z));
		arbol8Collider.e = arbol8ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol8Collider.c = glm::vec3(modelmatrixColliderArbol8[3]);
		addOrUpdateColliders(collidersOBB, "arbol8", arbol8Collider,
			modelMatrixArbol8);

		//Collider de arbol 9
		AbstractModel::OBB arbol9Collider;
		glm::mat4 modelmatrixColliderArbol9 = glm::mat4(modelMatrixArbol9);
		// Set the orientation of collider before doing the scale
		arbol9Collider.u = glm::quat_cast(modelmatrixColliderArbol9);
		modelmatrixColliderArbol9 = glm::scale(modelmatrixColliderArbol9,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol9 = glm::translate(modelmatrixColliderArbol9,
			glm::vec3(arbol9ModelAnimate.getObb().c.x,
				arbol9ModelAnimate.getObb().c.y,
				arbol9ModelAnimate.getObb().c.z));
		arbol9Collider.e = arbol9ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol9Collider.c = glm::vec3(modelmatrixColliderArbol9[3]);
		addOrUpdateColliders(collidersOBB, "arbol9", arbol9Collider,
			modelMatrixArbol9);

		//Collider de arbol 10
		AbstractModel::OBB arbol10Collider;
		glm::mat4 modelmatrixColliderArbol10 = glm::mat4(modelMatrixArbol10);
		// Set the orientation of collider before doing the scale
		arbol10Collider.u = glm::quat_cast(modelmatrixColliderArbol10);
		modelmatrixColliderArbol10 = glm::scale(modelmatrixColliderArbol10,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol10 = glm::translate(modelmatrixColliderArbol10,
			glm::vec3(arbol10ModelAnimate.getObb().c.x,
				arbol10ModelAnimate.getObb().c.y,
				arbol10ModelAnimate.getObb().c.z));
		arbol10Collider.e = arbol10ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol10Collider.c = glm::vec3(modelmatrixColliderArbol10[3]);
		addOrUpdateColliders(collidersOBB, "arbol10", arbol10Collider,
			modelMatrixArbol10);

		//Collider de arbol 11
		AbstractModel::OBB arbol11Collider;
		glm::mat4 modelmatrixColliderArbol11 = glm::mat4(modelMatrixArbol11);
		// Set the orientation of collider before doing the scale
		arbol11Collider.u = glm::quat_cast(modelmatrixColliderArbol11);
		modelmatrixColliderArbol11 = glm::scale(modelmatrixColliderArbol11,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol11 = glm::translate(modelmatrixColliderArbol11,
			glm::vec3(arbol11ModelAnimate.getObb().c.x,
				arbol11ModelAnimate.getObb().c.y,
				arbol11ModelAnimate.getObb().c.z));
		arbol11Collider.e = arbol11ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol11Collider.c = glm::vec3(modelmatrixColliderArbol11[3]);
		addOrUpdateColliders(collidersOBB, "arbol11", arbol11Collider,
			modelMatrixArbol11);

		//Collider de arbol 12
		AbstractModel::OBB arbol12Collider;
		glm::mat4 modelmatrixColliderArbol12 = glm::mat4(modelMatrixArbol12);
		// Set the orientation of collider before doing the scale
		arbol12Collider.u = glm::quat_cast(modelmatrixColliderArbol12);
		modelmatrixColliderArbol12 = glm::scale(modelmatrixColliderArbol12,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol12 = glm::translate(modelmatrixColliderArbol12,
			glm::vec3(arbol12ModelAnimate.getObb().c.x,
				arbol12ModelAnimate.getObb().c.y,
				arbol12ModelAnimate.getObb().c.z));
		arbol12Collider.e = arbol12ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol12Collider.c = glm::vec3(modelmatrixColliderArbol12[3]);
		addOrUpdateColliders(collidersOBB, "arbol12", arbol12Collider,
			modelMatrixArbol12);

		//Collider de arbol 13
		AbstractModel::OBB arbol13Collider;
		glm::mat4 modelmatrixColliderArbol13 = glm::mat4(modelMatrixArbol13);
		// Set the orientation of collider before doing the scale
		arbol13Collider.u = glm::quat_cast(modelmatrixColliderArbol13);
		modelmatrixColliderArbol13 = glm::scale(modelmatrixColliderArbol13,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol13 = glm::translate(modelmatrixColliderArbol13,
			glm::vec3(arbol13ModelAnimate.getObb().c.x,
				arbol13ModelAnimate.getObb().c.y,
				arbol13ModelAnimate.getObb().c.z));
		arbol13Collider.e = arbol13ModelAnimate.getObb().e
			* glm::vec3(0.25, 1.0, 0.25);
		arbol13Collider.c = glm::vec3(modelmatrixColliderArbol13[3]);
		addOrUpdateColliders(collidersOBB, "arbol13", arbol13Collider,
			modelMatrixArbol13);


		// Lamps1 colliders
		for (int i = 0; i < lamp1Position.size(); i++) {
			AbstractModel::OBB lampCollider;
			glm::mat4 modelMatrixColliderLamp = glm::mat4(1.0);
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp,
				lamp1Position[i]);
			modelMatrixColliderLamp = glm::rotate(modelMatrixColliderLamp,
				glm::radians(lamp1Orientation[i]), glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "lamp1-" + std::to_string(i),
				lampCollider, modelMatrixColliderLamp);
			// Set the orientation of collider before doing the scale
			lampCollider.u = glm::quat_cast(modelMatrixColliderLamp);
			modelMatrixColliderLamp = glm::scale(modelMatrixColliderLamp,
				glm::vec3(100.0, 100.0, 100.0));
			modelMatrixColliderLamp = glm::translate(modelMatrixColliderLamp,
				modelLamp1.getObb().c);
			lampCollider.c = glm::vec3(modelMatrixColliderLamp[3]);
			lampCollider.e = modelLamp1.getObb().e * glm::vec3(100.0, 100.0, 100.0);
			std::get<0>(collidersOBB.find("lamp1-" + std::to_string(i))->second) =
				lampCollider;
		}


		// Lamps2 colliders
		for (int i = 0; i < lamp2Position.size(); i++) {
			AbstractModel::OBB lamp2Collider;
			glm::mat4 modelMatrixColliderLamp2 = glm::mat4(1.0);
			modelMatrixColliderLamp2 = glm::translate(modelMatrixColliderLamp2,
				lamp2Position[i]);
			modelMatrixColliderLamp2 = glm::rotate(modelMatrixColliderLamp2,
				glm::radians(lamp2Orientation[i]), glm::vec3(0, 1, 0));
			addOrUpdateColliders(collidersOBB, "lamp2-" + std::to_string(i),
				lamp2Collider, modelMatrixColliderLamp2);
			// Set the orientation of collider before doing the scale
			lamp2Collider.u = glm::quat_cast(modelMatrixColliderLamp2);
			modelMatrixColliderLamp2 = glm::scale(modelMatrixColliderLamp2,
				glm::vec3(1.0, 1.0, 1.0));
			modelMatrixColliderLamp2 = glm::translate(modelMatrixColliderLamp2,
				modelLamp2.getObb().c);
			lamp2Collider.c = glm::vec3(modelMatrixColliderLamp2[3]);
			lamp2Collider.e = modelLamp2.getObb().e * glm::vec3(1.0, 1.0, 1.0);
			std::get<0>(collidersOBB.find("lamp2-" + std::to_string(i))->second) =
				lamp2Collider;
		}

		// Collider de ironman
		AbstractModel::OBB ironmanCollider;
		glm::mat4 modelmatrixColliderIronman = glm::mat4(modelMatrixIronman);
		//		modelmatrixColliderIronman = glm::rotate(modelmatrixColliderIronman,
		//				glm::radians(-90.0f), glm::vec3(1, 0, 0));
				// Set the orientation of collider before doing the scale
		ironmanCollider.u = glm::quat_cast(modelmatrixColliderIronman);
				modelmatrixColliderIronman = glm::translate(modelmatrixColliderIronman,
						glm::vec3(0.0, 0.0, -0.5));
		modelmatrixColliderIronman = glm::translate(modelmatrixColliderIronman,
			glm::vec3(ironmanModelAnimate.getObb().c.x,
				ironmanModelAnimate.getObb().c.y,
				ironmanModelAnimate.getObb().c.z));
		ironmanCollider.e = ironmanModelAnimate.getObb().e * glm::vec3(0.5, 0.75, 1.5);
		ironmanCollider.c = glm::vec3(modelmatrixColliderIronman[3]);
		addOrUpdateColliders(collidersOBB, "ironman", ironmanCollider, modelMatrixIronman);



		// Collider de zombie
		AbstractModel::OBB zombieCollider;
		glm::mat4 modelmatrixColliderZombie = glm::mat4(modelMatrixZombie);
		// Set the orientation of collider before doing the scale
		if (renderZombie) {
			modelmatrixColliderZombie = glm::mat4(modelMatrixZombie);
			// Set the orientation of collider before doing the scale
			zombieCollider.u = glm::quat_cast(modelmatrixColliderZombie);
			modelmatrixColliderZombie = glm::translate(modelmatrixColliderZombie, glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie = glm::translate(modelmatrixColliderZombie, glm::vec3(zombieModelAnimate.getObb().c.x, zombieModelAnimate.getObb().c.y, zombieModelAnimate.getObb().c.z));
			zombieCollider.e = zombieModelAnimate.getObb().e * glm::vec3(1.0, 0.6, 1.0);
			zombieCollider.c = glm::vec3(modelmatrixColliderZombie[3]);
			addOrUpdateColliders(collidersOBB, "zombie", zombieCollider, modelMatrixZombie);
		}
		else {
			collidersOBB.erase("zombie");
		}

		// Collider de zombie 1
		AbstractModel::OBB zombie1Collider;
		glm::mat4 modelmatrixColliderZombie1 = glm::mat4(modelMatrixZombie1);
		// Set the orientation of collider before doing the scale
		if (renderZombie1) {
			modelmatrixColliderZombie1 = glm::mat4(modelMatrixZombie1);
			// Set the orientation of collider before doing the scale
			zombie1Collider.u = glm::quat_cast(modelmatrixColliderZombie1);
			modelmatrixColliderZombie1 = glm::translate(modelmatrixColliderZombie1,
				glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie1 = glm::translate(modelmatrixColliderZombie1,
				glm::vec3(zombie1ModelAnimate.getObb().c.x,
					zombie1ModelAnimate.getObb().c.y,
					zombie1ModelAnimate.getObb().c.z));
			zombie1Collider.e = zombie1ModelAnimate.getObb().e
				* glm::vec3(1.0, 0.6, 1.0);
			zombie1Collider.c = glm::vec3(modelmatrixColliderZombie1[3]);
			addOrUpdateColliders(collidersOBB, "zombie1", zombie1Collider,
				modelMatrixZombie1);
		}
		else {
			collidersOBB.erase("zombie1");
		}

		// Collider de zombie 2
		AbstractModel::OBB zombie2Collider;
		glm::mat4 modelmatrixColliderZombie2 = glm::mat4(modelMatrixZombie2);
		// Set the orientation of collider before doing the scale
		if (renderZombie2) {
			modelmatrixColliderZombie2 = glm::mat4(modelMatrixZombie2);
			// Set the orientation of collider before doing the scale
			zombie2Collider.u = glm::quat_cast(modelmatrixColliderZombie2);
			modelmatrixColliderZombie2 = glm::translate(modelmatrixColliderZombie2,
				glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie2 = glm::translate(modelmatrixColliderZombie2,
				glm::vec3(zombie2ModelAnimate.getObb().c.x,
					zombie2ModelAnimate.getObb().c.y,
					zombie2ModelAnimate.getObb().c.z));
			zombie2Collider.e = zombie2ModelAnimate.getObb().e
				* glm::vec3(1.0, 0.6, 1.0);
			zombie2Collider.c = glm::vec3(modelmatrixColliderZombie2[3]);
			addOrUpdateColliders(collidersOBB, "zombie2", zombie2Collider,
				modelMatrixZombie2);
		}
		else {
			collidersOBB.erase("zombie2");
		}

		// Collider de zombie 3
		AbstractModel::OBB zombie3Collider;
		glm::mat4 modelmatrixColliderZombie3 = glm::mat4(modelMatrixZombie3);
		// Set the orientation of collider before doing the scale
		if (renderZombie3) {
			modelmatrixColliderZombie3 = glm::mat4(modelMatrixZombie3);
			// Set the orientation of collider before doing the scale
			zombie3Collider.u = glm::quat_cast(modelmatrixColliderZombie3);
			modelmatrixColliderZombie3 = glm::translate(modelmatrixColliderZombie3, glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie3 = glm::translate(modelmatrixColliderZombie3, glm::vec3(zombie3ModelAnimate.getObb().c.x, zombie3ModelAnimate.getObb().c.y, zombie3ModelAnimate.getObb().c.z));
			zombie3Collider.e = zombie3ModelAnimate.getObb().e * glm::vec3(1.0, 0.6, 1.0);
			zombie3Collider.c = glm::vec3(modelmatrixColliderZombie3[3]);
			addOrUpdateColliders(collidersOBB, "zombie3", zombie3Collider, modelMatrixZombie3);
		}
		else {
			collidersOBB.erase("zombie3");
		}
		// Collider de zombie 4
		AbstractModel::OBB zombie4Collider;
		glm::mat4 modelmatrixColliderZombie4 = glm::mat4(modelMatrixZombie4);
		// Set the orientation of collider before doing the scale
		if (renderZombie4) {
			modelmatrixColliderZombie4 = glm::mat4(modelMatrixZombie4);
			// Set the orientation of collider before doing the scale
			zombie4Collider.u = glm::quat_cast(modelmatrixColliderZombie4);
			modelmatrixColliderZombie4 = glm::translate(modelmatrixColliderZombie4, glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie4 = glm::translate(modelmatrixColliderZombie4, glm::vec3(zombie4ModelAnimate.getObb().c.x, zombie4ModelAnimate.getObb().c.y, zombie4ModelAnimate.getObb().c.z));
			zombie4Collider.e = zombie4ModelAnimate.getObb().e * glm::vec3(1.0, 0.6, 1.0);
			zombie4Collider.c = glm::vec3(modelmatrixColliderZombie4[3]);
			addOrUpdateColliders(collidersOBB, "zombie4", zombie4Collider, modelMatrixZombie4);
		}
		else {
			collidersOBB.erase("zombie4");
		}

		// Collider de zombie 5
		AbstractModel::OBB zombie5Collider;
		glm::mat4 modelmatrixColliderZombie5 = glm::mat4(modelMatrixZombie5);
		// Set the orientation of collider before doing the scale
		if (renderZombie5) {
			modelmatrixColliderZombie5 = glm::mat4(modelMatrixZombie5);
			// Set the orientation of collider before doing the scale
			zombie5Collider.u = glm::quat_cast(modelmatrixColliderZombie5);
			modelmatrixColliderZombie5 = glm::translate(modelmatrixColliderZombie5, glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie5 = glm::translate(modelmatrixColliderZombie5, glm::vec3(zombie5ModelAnimate.getObb().c.x, zombie5ModelAnimate.getObb().c.y, zombie5ModelAnimate.getObb().c.z));
			zombie5Collider.e = zombie5ModelAnimate.getObb().e * glm::vec3(1.0, 0.6, 1.0);
			zombie5Collider.c = glm::vec3(modelmatrixColliderZombie5[3]);
			addOrUpdateColliders(collidersOBB, "zombie5", zombie5Collider, modelMatrixZombie5);
		}
		else {
			collidersOBB.erase("zombie5");
		}

		// Collider de zombie 6
		AbstractModel::OBB zombie6Collider;
		glm::mat4 modelmatrixColliderZombie6 = glm::mat4(modelMatrixZombie6);
		// Set the orientation of collider before doing the scale
		if (renderZombie6) {
			modelmatrixColliderZombie6 = glm::mat4(modelMatrixZombie6);
			// Set the orientation of collider before doing the scale
			zombie6Collider.u = glm::quat_cast(modelmatrixColliderZombie6);
			modelmatrixColliderZombie6 = glm::translate(modelmatrixColliderZombie6, glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie6 = glm::translate(modelmatrixColliderZombie6, glm::vec3(zombie6ModelAnimate.getObb().c.x, zombie6ModelAnimate.getObb().c.y, zombie6ModelAnimate.getObb().c.z));
			zombie6Collider.e = zombie6ModelAnimate.getObb().e * glm::vec3(1.0, 0.6, 1.0);
			zombie6Collider.c = glm::vec3(modelmatrixColliderZombie6[3]);
			addOrUpdateColliders(collidersOBB, "zombie6", zombie6Collider, modelMatrixZombie6);
		}
		else {
			collidersOBB.erase("zombie6");
		}


		// Collider de zombie 7
		AbstractModel::OBB zombie7Collider;
		glm::mat4 modelmatrixColliderZombie7 = glm::mat4(modelMatrixZombie7);
		// Set the orientation of collider before doing the scale
		if (renderZombie7) {
			modelmatrixColliderZombie7 = glm::mat4(modelMatrixZombie7);
			// Set the orientation of collider before doing the scale
			zombie7Collider.u = glm::quat_cast(modelmatrixColliderZombie7);
			modelmatrixColliderZombie7 = glm::translate(modelmatrixColliderZombie7, glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie7 = glm::translate(modelmatrixColliderZombie7, glm::vec3(zombie7ModelAnimate.getObb().c.x, zombie7ModelAnimate.getObb().c.y, zombie7ModelAnimate.getObb().c.z));
			zombie7Collider.e = zombie7ModelAnimate.getObb().e * glm::vec3(1.0, 0.6, 1.0);
			zombie7Collider.c = glm::vec3(modelmatrixColliderZombie7[3]);
			addOrUpdateColliders(collidersOBB, "zombie7", zombie7Collider, modelMatrixZombie7);
		}
		else {
			collidersOBB.erase("zombie7");
		}

		// Collider de zombie 8
		AbstractModel::OBB zombie8Collider;
		glm::mat4 modelmatrixColliderZombie8 = glm::mat4(modelMatrixZombie8);
		// Set the orientation of collider before doing the scale
		if (renderZombie8) {
			modelmatrixColliderZombie8 = glm::mat4(modelMatrixZombie8);
			// Set the orientation of collider before doing the scale
			zombie8Collider.u = glm::quat_cast(modelmatrixColliderZombie8);
			modelmatrixColliderZombie8 = glm::translate(modelmatrixColliderZombie8, glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie8 = glm::translate(modelmatrixColliderZombie8, glm::vec3(zombie8ModelAnimate.getObb().c.x, zombie8ModelAnimate.getObb().c.y, zombie8ModelAnimate.getObb().c.z));
			zombie8Collider.e = zombie8ModelAnimate.getObb().e * glm::vec3(1.0, 0.6, 1.0);
			zombie8Collider.c = glm::vec3(modelmatrixColliderZombie8[3]);
			addOrUpdateColliders(collidersOBB, "zombie8", zombie8Collider, modelMatrixZombie8);
		}
		else {
			collidersOBB.erase("zombie8");
		}


		// Collider de zombie 9
		AbstractModel::OBB zombie9Collider;
		glm::mat4 modelmatrixColliderZombie9 = glm::mat4(modelMatrixZombie9);
		// Set the orientation of collider before doing the scale
		if (renderZombie9) {
			modelmatrixColliderZombie9 = glm::mat4(modelMatrixZombie9);
			// Set the orientation of collider before doing the scale
			zombie9Collider.u = glm::quat_cast(modelmatrixColliderZombie9);
			modelmatrixColliderZombie9 = glm::translate(modelmatrixColliderZombie9, glm::vec3(0.0, 0.0, 0.25));
			modelmatrixColliderZombie9 = glm::translate(modelmatrixColliderZombie9, glm::vec3(zombie9ModelAnimate.getObb().c.x, zombie9ModelAnimate.getObb().c.y, zombie9ModelAnimate.getObb().c.z));
			zombie9Collider.e = zombie9ModelAnimate.getObb().e * glm::vec3(1.0, 0.6, 1.0);
			zombie9Collider.c = glm::vec3(modelmatrixColliderZombie9[3]);
			addOrUpdateColliders(collidersOBB, "zombie9", zombie9Collider, modelMatrixZombie9);
		}
		else {
			collidersOBB.erase("zombie9");
		}


		//Collider de reja
		AbstractModel::OBB rejaCollider;
		glm::mat4 modelmatrixColliderReja = glm::mat4(modelMatrixReja);
		// Set the orientation of collider before doing the scale
		rejaCollider.u = glm::quat_cast(modelmatrixColliderReja);
		modelmatrixColliderReja = glm::scale(modelmatrixColliderReja,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderReja = glm::translate(modelmatrixColliderReja,
			glm::vec3(rejaModelAnimate.getObb().c.x,
				rejaModelAnimate.getObb().c.y,
				rejaModelAnimate.getObb().c.z));
		rejaCollider.e = rejaModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 1.0);
		rejaCollider.c = glm::vec3(modelmatrixColliderReja[3]);
		addOrUpdateColliders(collidersOBB, "reja", rejaCollider,
			modelMatrixReja);

		//Collider de reja 2
		AbstractModel::OBB reja2Collider;
		glm::mat4 modelmatrixColliderReja2 = glm::mat4(modelMatrixReja2);
		// Set the orientation of collider before doing the scale
		reja2Collider.u = glm::quat_cast(modelmatrixColliderReja2);
		modelmatrixColliderReja2 = glm::scale(modelmatrixColliderReja2,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderReja2 = glm::translate(modelmatrixColliderReja2,
			glm::vec3(reja2ModelAnimate.getObb().c.x,
				reja2ModelAnimate.getObb().c.y,
				reja2ModelAnimate.getObb().c.z));
		reja2Collider.e = reja2ModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 1.0);
		reja2Collider.c = glm::vec3(modelmatrixColliderReja2[3]);
		addOrUpdateColliders(collidersOBB, "reja2", reja2Collider,
			modelMatrixReja2);


		//Collider de limite
		AbstractModel::OBB limiteCollider;
		glm::mat4 modelmatrixColliderLimite = glm::mat4(modelMatrixLimite);
		// Set the orientation of collider before doing the scale
		limiteCollider.u = glm::quat_cast(modelmatrixColliderLimite);
		modelmatrixColliderLimite = glm::scale(modelmatrixColliderLimite,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderLimite = glm::translate(modelmatrixColliderLimite,
			glm::vec3(limiteModelAnimate.getObb().c.x,
				limiteModelAnimate.getObb().c.y,
				limiteModelAnimate.getObb().c.z));
		limiteCollider.e = limiteModelAnimate.getObb().e
			* glm::vec3(250.0, 2.0, 10.0);
		limiteCollider.c = glm::vec3(modelmatrixColliderLimite[3]);
		addOrUpdateColliders(collidersOBB, "limite", limiteCollider,
			modelMatrixLimite);

		//Collider de limite 2
		AbstractModel::OBB limite2Collider;
		glm::mat4 modelmatrixColliderLimite2 = glm::mat4(modelMatrixLimite2);
		// Set the orientation of collider before doing the scale
		limite2Collider.u = glm::quat_cast(modelmatrixColliderLimite2);
		modelmatrixColliderLimite2 = glm::scale(modelmatrixColliderLimite2,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderLimite2 = glm::translate(modelmatrixColliderLimite2,
			glm::vec3(limite2ModelAnimate.getObb().c.x,
				limite2ModelAnimate.getObb().c.y,
				limite2ModelAnimate.getObb().c.z));
		limite2Collider.e = limite2ModelAnimate.getObb().e
			* glm::vec3(250.0, 2.0, 10.0);
		limite2Collider.c = glm::vec3(modelmatrixColliderLimite2[3]);
		addOrUpdateColliders(collidersOBB, "limite2", limite2Collider,
			modelMatrixLimite2);

		//Collider de limite 3
		AbstractModel::OBB limite3Collider;
		glm::mat4 modelmatrixColliderLimite3 = glm::mat4(modelMatrixLimite3);
		// Set the orientation of collider before doing the scale
		limite3Collider.u = glm::quat_cast(modelmatrixColliderLimite3);
		modelmatrixColliderLimite3 = glm::scale(modelmatrixColliderLimite3,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderLimite3 = glm::translate(modelmatrixColliderLimite3,
			glm::vec3(limite3ModelAnimate.getObb().c.x,
				limite3ModelAnimate.getObb().c.y,
				limite3ModelAnimate.getObb().c.z));
		limite3Collider.e = limite3ModelAnimate.getObb().e
			* glm::vec3(250.0, 2.0, 10.0);
		limite3Collider.c = glm::vec3(modelmatrixColliderLimite3[3]);
		addOrUpdateColliders(collidersOBB, "limite3", limite3Collider,
			modelMatrixLimite3);

		//Collider de limite 4
		AbstractModel::OBB limite4Collider;
		glm::mat4 modelmatrixColliderLimite4 = glm::mat4(modelMatrixLimite4);
		// Set the orientation of collider before doing the scale
		limite4Collider.u = glm::quat_cast(modelmatrixColliderLimite4);
		modelmatrixColliderLimite4 = glm::scale(modelmatrixColliderLimite4,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderLimite4 = glm::translate(modelmatrixColliderLimite4,
			glm::vec3(limite4ModelAnimate.getObb().c.x,
				limite4ModelAnimate.getObb().c.y,
				limite4ModelAnimate.getObb().c.z));
		limite4Collider.e = limite4ModelAnimate.getObb().e
			* glm::vec3(250.0, 2.0, 10.0);
		limite4Collider.c = glm::vec3(modelmatrixColliderLimite4[3]);
		addOrUpdateColliders(collidersOBB, "limite4", limite4Collider,
			modelMatrixLimite4);

		//Collider de entrada
		AbstractModel::OBB entradaCollider;
		glm::mat4 modelmatrixColliderEntrada = glm::mat4(modelMatrixEntrada);
		// Set the orientation of collider before doing the scale
		entradaCollider.u = glm::quat_cast(modelmatrixColliderEntrada);
		modelmatrixColliderEntrada = glm::scale(modelmatrixColliderEntrada,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderEntrada = glm::translate(modelmatrixColliderEntrada,
			glm::vec3(entradaModelAnimate.getObb().c.x,
				entradaModelAnimate.getObb().c.y,
				entradaModelAnimate.getObb().c.z));
		entradaCollider.e = entradaModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 5.0);
		entradaCollider.c = glm::vec3(modelmatrixColliderEntrada[3]);
		addOrUpdateColliders(collidersOBB, "entrada", entradaCollider,
			modelMatrixEntrada);


		//Collider de entrada 2
		AbstractModel::OBB entrada2Collider;
		glm::mat4 modelmatrixColliderEntrada2 = glm::mat4(modelMatrixEntrada2);
		// Set the orientation of collider before doing the scale
		entrada2Collider.u = glm::quat_cast(modelmatrixColliderEntrada2);
		modelmatrixColliderEntrada2 = glm::scale(modelmatrixColliderEntrada2,
			glm::vec3(1.0, 1.0, 10.0));
		modelmatrixColliderEntrada2 = glm::translate(modelmatrixColliderEntrada2,
			glm::vec3(entrada2ModelAnimate.getObb().c.x,
				entrada2ModelAnimate.getObb().c.y,
				entrada2ModelAnimate.getObb().c.z));
		entrada2Collider.e = entrada2ModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 5.0);
		entrada2Collider.c = glm::vec3(modelmatrixColliderEntrada2[3]);
		addOrUpdateColliders(collidersOBB, "entrada2", entrada2Collider,
			modelMatrixEntrada2);

		//Collider de apartamentos
		AbstractModel::OBB apartamentosCollider;
		glm::mat4 modelmatrixColliderApartamentos = glm::mat4(modelMatrixApartamentos);
		// Set the orientation of collider before doing the scale
		apartamentosCollider.u = glm::quat_cast(modelmatrixColliderApartamentos);
		modelmatrixColliderApartamentos = glm::scale(modelmatrixColliderApartamentos,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderApartamentos = glm::translate(modelmatrixColliderApartamentos,
			glm::vec3(apartamentosModelAnimate.getObb().c.x,
				apartamentosModelAnimate.getObb().c.y,
				apartamentosModelAnimate.getObb().c.z));
		apartamentosCollider.e = apartamentosModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 1.0);
		apartamentosCollider.c = glm::vec3(modelmatrixColliderApartamentos[3]);
		addOrUpdateColliders(collidersOBB, "apartamentos", apartamentosCollider,
			modelMatrixApartamentos);

		//Collider de gas
		AbstractModel::OBB gasCollider;
		glm::mat4 modelmatrixColliderGas = glm::mat4(modelMatrixGas);
		// Set the orientation of collider before doing the scale
		gasCollider.u = glm::quat_cast(modelmatrixColliderGas);
		modelmatrixColliderGas = glm::scale(modelmatrixColliderGas,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderGas = glm::translate(modelmatrixColliderGas,
			glm::vec3(gasModelAnimate.getObb().c.x,
				gasModelAnimate.getObb().c.y,
				gasModelAnimate.getObb().c.z));
		gasCollider.e = gasModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 1.0);
		gasCollider.c = glm::vec3(modelmatrixColliderGas[3]);
		addOrUpdateColliders(collidersOBB, "gas", gasCollider,
			modelMatrixGas);

		//Collider de arbol
		AbstractModel::OBB arbolCollider;
		glm::mat4 modelmatrixColliderArbol = glm::mat4(modelMatrixArbol);
		// Set the orientation of collider before doing the scale
		arbolCollider.u = glm::quat_cast(modelmatrixColliderArbol);
		modelmatrixColliderArbol = glm::scale(modelmatrixColliderArbol,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderArbol = glm::translate(modelmatrixColliderArbol,
			glm::vec3(arbolModelAnimate.getObb().c.x,
				arbolModelAnimate.getObb().c.y,
				arbolModelAnimate.getObb().c.z));
		arbolCollider.e = arbolModelAnimate.getObb().e
			* glm::vec3(0.2, 1.0, 0.2);
		arbolCollider.c = glm::vec3(modelmatrixColliderArbol[3]);
		addOrUpdateColliders(collidersOBB, "arbol", arbolCollider,
			modelMatrixArbol);

		//Collider de coche
		AbstractModel::OBB cocheCollider;
		glm::mat4 modelmatrixColliderCoche = glm::mat4(modelMatrixCarro);
		// Set the orientation of collider before doing the scale
		cocheCollider.u = glm::quat_cast(modelmatrixColliderCoche);
		modelmatrixColliderCoche = glm::scale(modelmatrixColliderCoche,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderCoche = glm::translate(modelmatrixColliderCoche,
			glm::vec3(carroModelAnimate.getObb().c.x,
				carroModelAnimate.getObb().c.y,
				carroModelAnimate.getObb().c.z));
		cocheCollider.e = carroModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 1.0);
		cocheCollider.c = glm::vec3(modelmatrixColliderCoche[3]);
		addOrUpdateColliders(collidersOBB, "carro", cocheCollider,
			modelMatrixCarro);

		//Collider de coche 2
		AbstractModel::OBB coche2Collider;
		glm::mat4 modelmatrixColliderCoche2 = glm::mat4(modelMatrixCarro2);
		// Set the orientation of collider before doing the scale
		coche2Collider.u = glm::quat_cast(modelmatrixColliderCoche2);
		modelmatrixColliderCoche2 = glm::scale(modelmatrixColliderCoche2,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderCoche2 = glm::translate(modelmatrixColliderCoche2,
			glm::vec3(carro2ModelAnimate.getObb().c.x,
				carro2ModelAnimate.getObb().c.y,
				carro2ModelAnimate.getObb().c.z));
		coche2Collider.e = carro2ModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 1.0);
		coche2Collider.c = glm::vec3(modelmatrixColliderCoche2[3]);
		addOrUpdateColliders(collidersOBB, "carro2", coche2Collider,
			modelMatrixCarro2);

		//Collider de coche 3
		AbstractModel::OBB coche3Collider;
		glm::mat4 modelmatrixColliderCoche3 = glm::mat4(modelMatrixCarro3);
		// Set the orientation of collider before doing the scale
		coche3Collider.u = glm::quat_cast(modelmatrixColliderCoche3);
		modelmatrixColliderCoche3 = glm::scale(modelmatrixColliderCoche3,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderCoche3 = glm::translate(modelmatrixColliderCoche3,
			glm::vec3(carro3ModelAnimate.getObb().c.x,
				carro3ModelAnimate.getObb().c.y,
				carro3ModelAnimate.getObb().c.z));
		coche3Collider.e = carro3ModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 1.0);
		coche3Collider.c = glm::vec3(modelmatrixColliderCoche3[3]);
		addOrUpdateColliders(collidersOBB, "carro3", coche3Collider,
			modelMatrixCarro3);

		//Collider de coche policia
		AbstractModel::OBB cochepCollider;
		glm::mat4 modelmatrixColliderCochep = glm::mat4(modelMatrixCarrop);
		// Set the orientation of collider before doing the scale
		cochepCollider.u = glm::quat_cast(modelmatrixColliderCochep);
		modelmatrixColliderCochep = glm::scale(modelmatrixColliderCochep,
			glm::vec3(1.0, 1.0, 1.0));
		modelmatrixColliderCochep = glm::translate(modelmatrixColliderCochep,
			glm::vec3(carropModelAnimate.getObb().c.x,
				carropModelAnimate.getObb().c.y,
				carropModelAnimate.getObb().c.z));
		cochepCollider.e = carropModelAnimate.getObb().e
			* glm::vec3(1.0, 1.0, 1.0);
		cochepCollider.c = glm::vec3(modelmatrixColliderCochep[3]);
		addOrUpdateColliders(collidersOBB, "cochep", cochepCollider,
			modelMatrixCarrop);

		//Collider del la roca 1
		AbstractModel::SBB roca1Collider;
		glm::mat4 modelMatrixColliderRoca1 = glm::mat4(modelMatrixRoca);
		modelMatrixColliderRoca1 = glm::scale(modelMatrixColliderRoca1,
			glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderRoca1 = glm::translate(modelMatrixColliderRoca1,
			rocaModelAnimate.getSbb().c);
		roca1Collider.c = glm::vec3(modelMatrixColliderRoca1[3]);
		roca1Collider.ratio = rocaModelAnimate.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "roca1", roca1Collider,
			modelMatrixRoca);

		//Collider del la roca 2
		AbstractModel::SBB roca2Collider;
		glm::mat4 modelMatrixColliderRoca2 = glm::mat4(modelMatrixRoca2);
		modelMatrixColliderRoca2 = glm::scale(modelMatrixColliderRoca2,
			glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderRoca2 = glm::translate(modelMatrixColliderRoca2,
			roca2ModelAnimate.getSbb().c);
		roca2Collider.c = glm::vec3(modelMatrixColliderRoca2[3]);
		roca2Collider.ratio = roca2ModelAnimate.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "roca2", roca2Collider,
			modelMatrixRoca2);


		//Collider del la roca 3
		AbstractModel::SBB roca3Collider;
		glm::mat4 modelMatrixColliderRoca3 = glm::mat4(modelMatrixRoca3);
		modelMatrixColliderRoca3 = glm::scale(modelMatrixColliderRoca3,
			glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderRoca3 = glm::translate(modelMatrixColliderRoca3,
			roca3ModelAnimate.getSbb().c);
		roca3Collider.c = glm::vec3(modelMatrixColliderRoca3[3]);
		roca3Collider.ratio = roca3ModelAnimate.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "roca3", roca3Collider,
			modelMatrixRoca3);


		//Collider del la roca 4
		AbstractModel::SBB roca4Collider;
		glm::mat4 modelMatrixColliderRoca4 = glm::mat4(modelMatrixRoca4);
		modelMatrixColliderRoca4 = glm::scale(modelMatrixColliderRoca4,
			glm::vec3(1.0, 1.0, 1.0));
		modelMatrixColliderRoca4 = glm::translate(modelMatrixColliderRoca4,
			roca4ModelAnimate.getSbb().c);
		roca4Collider.c = glm::vec3(modelMatrixColliderRoca4[3]);
		roca4Collider.ratio = roca4ModelAnimate.getSbb().ratio * 1.0;
		addOrUpdateColliders(collidersSBB, "roca4", roca4Collider,
			modelMatrixRoca4);


		/*******************************************
		 * Render de colliders
		 *******************************************/

		 /*******************************************
		  * Test Colisions
		  *******************************************/
		for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it = collidersOBB.begin(); it != collidersOBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt = collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
				if (it != jt && testOBBOBB(std::get<0>(it->second), std::get<0>(jt->second))) {
					isCollision = true;
					//std::cout << "Colision " << it->first << " with " << jt->first << std::endl;
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie") == 0) {
						renderVidas--;
						renderZombie = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie1") == 0) {
						renderVidas--;
						renderZombie1 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie2") == 0) {
						renderVidas--;
						renderZombie2 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie3") == 0) {
						renderVidas--;
						renderZombie3 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie4") == 0) {
						renderVidas--;
						renderZombie4 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie5") == 0) {
						renderVidas--;
						renderZombie5 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie6") == 0) {
						renderVidas--;
						renderZombie6 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie7") == 0) {
						renderVidas--;
						renderZombie7 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie8") == 0) {
						renderVidas--;
						renderZombie8 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("zombie9") == 0) {
						renderVidas--;
						renderZombie9 = false;
					}
					if (it->first.compare("ironman") == 0 && jt->first.compare("cochep") == 0) {
						win = true;
						std::cout << "Has ganado con " << tiempo_final << " y " << puntaje << std::endl;
					}
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it = collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator jt = collidersSBB.begin(); jt != collidersSBB.end(); jt++) {
				if (it != jt && testSphereSphereIntersection(std::get<0>(it->second), std::get<0>(jt->second))) {
					//std::cout << "Colision " << it->first << " with " << jt->first << std::endl;
					isCollision = true;
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it = collidersSBB.begin(); it != collidersSBB.end(); it++) {
			bool isCollision = false;
			std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt = collidersOBB.begin();
			for (; jt != collidersOBB.end(); jt++) {
				if (testSphereOBox(std::get<0>(it->second), std::get<0>(jt->second))) {
					//std::cout << "Colision " << it->first << " with " << jt->first << std::endl;
					isCollision = true;
					addOrUpdateCollisionDetection(collisionDetection, jt->first, isCollision);
				}
			}
			addOrUpdateCollisionDetection(collisionDetection, it->first, isCollision);
		}

		std::map<std::string, bool>::iterator colIt;
		for (colIt = collisionDetection.begin(); colIt != collisionDetection.end(); colIt++) {
			std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4> >::iterator it = collidersSBB.find(colIt->first);
			std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator jt = collidersOBB.find(colIt->first);
			if (it != collidersSBB.end()) {
				if (!colIt->second)
					addOrUpdateColliders(collidersSBB, it->first);
			}
			if (jt != collidersOBB.end()) {
				if (!colIt->second)
					addOrUpdateColliders(collidersOBB, jt->first);
				else {
					if (jt->first.compare("ironman") == 0)
						modelMatrixIronman = std::get<1>(jt->second);
					//if (jt->first.compare("dart") == 0)
					//	modelMatrixDart = std::get<1>(jt->second);
					if (jt->first.compare("zombie") == 0)
						modelMatrixZombie = std::get<1>(jt->second);
					if (jt->first.compare("zombie1") == 0)
						modelMatrixZombie1 = std::get<1>(jt->second);
					if (jt->first.compare("zombie2") == 0)
						modelMatrixZombie2 = std::get<1>(jt->second);
					if (jt->first.compare("zombie3") == 0)
						modelMatrixZombie3 = std::get<1>(jt->second);
					if (jt->first.compare("zombie4") == 0)
						modelMatrixZombie4 = std::get<1>(jt->second);
					if (jt->first.compare("zombie5") == 0)
						modelMatrixZombie5 = std::get<1>(jt->second);
					if (jt->first.compare("zombie6") == 0)
						modelMatrixZombie6 = std::get<1>(jt->second);
					if (jt->first.compare("zombie7") == 0)
						modelMatrixZombie7 = std::get<1>(jt->second);
					if (jt->first.compare("zombie8") == 0)
						modelMatrixZombie8 = std::get<1>(jt->second);
					if (jt->first.compare("zombie9") == 0)
						modelMatrixZombie9 = std::get<1>(jt->second);
					if (jt->first.compare("zombie10") == 0)
						modelMatrixZombie10 = std::get<1>(jt->second);
					if (jt->first.compare("zombie11") == 0)
						modelMatrixZombie11 = std::get<1>(jt->second);
				}
			}
		}

		//Ray vs Sphere
		if (renderRay) {
			for (std::map<std::string, std::tuple<AbstractModel::SBB, glm::mat4, glm::mat4>>::iterator it = collidersSBB.begin(); it != collidersSBB.end(); it++) {
				float tray;
				if (raySphereIntersect(ori, tar, rayDirection, std::get<0>(it->second), tray)) {
					std::cout << "Colision " << it->first << " con el rayo de Ironman" << std::endl;
				}
			}
		}

		//Ray vs Box
		if (renderRay) {
			for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator it = collidersOBB.begin(); it != collidersOBB.end(); it++) {
				if (intersectRayOBB(ori, tar, rayDirection, std::get<0>(it->second))) {
					std::cout << "Colision " << it->first << " con el rayo de Ironman" << std::endl;
					if (it->first.compare("zombie") == 0) {
						zombieMuerte++;
						if (zombieMuerte == 1) {
							modelMatrixZombie = glm::translate(modelMatrixZombie, glm::vec3(62.5f, 0.0f, -92.0f)); //87.5f, 0.0f, -92.0f
							puntaje++;
						}
						else if (zombieMuerte == 2) {
							modelMatrixZombie = glm::translate(modelMatrixZombie, glm::vec3(-139.5f, 0.0f, 48.0f)); //-52.0f, 0.0f, -44.0f
							puntaje++;
							animationIndexZombie1 = 1;
							state1 = 1;
						}
						else if (zombieMuerte == 3) {
							renderZombie = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie1") == 0) {
						zombie1Muerte++;
						if (zombie1Muerte == 1) {
							modelMatrixZombie1 = glm::translate(modelMatrixZombie1, glm::vec3(-11.0f, 0.0f, -117.0)); //29.0f, 0.0, -92.0f
							puntaje++;
						}
						else if (zombie1Muerte == 2) {
							modelMatrixZombie1 = glm::translate(modelMatrixZombie1, glm::vec3(-120.5f, 0.0f, 70.0f)); //-91.5f, 0.0f, -22.0f
							animationIndexZombie2 = 1;
							state2 = 1;
							puntaje++;
						}
						else if (zombie1Muerte == 3) {
							renderZombie1 = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie2") == 0) {
						zombie2Muerte++;
						if (zombie2Muerte == 1) {
							modelMatrixZombie2 = glm::translate(modelMatrixZombie2, glm::vec3(-69.0f, 0.0f, -80.0f)); // -49.0f, 0.0f, -90.0f
							puntaje++;
						}
						else if (zombie2Muerte == 2) {
							modelMatrixZombie2 = glm::translate(modelMatrixZombie2, glm::vec3(-19.75f, 0.0f, 82.0f)); //-68.75f, 0.0f, -8.0f
							puntaje++;
						}
						else if (zombie2Muerte == 3) {
							renderZombie2 = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie3") == 0) {
						zombie3Muerte++;
						if (zombie3Muerte == 1) {
							modelMatrixZombie3 = glm::translate(modelMatrixZombie3, glm::vec3(24.0f, 0.0f, -46.5f)); //64.0f, 0.0f, -76.5f
							puntaje++;
						}
						else if (zombie3Muerte == 2) {
							modelMatrixZombie3 = glm::translate(modelMatrixZombie3, glm::vec3(-101.5f, 0.0f, 70.25f)); //-37.5f, 0.0f, -6.25f
							animationIndexZombie0 = 1;
							state = 1;
							puntaje++;
						}
						else if (zombie3Muerte == 3) {
							renderZombie3 = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie4") == 0) {
						zombie4Muerte++;
						if (zombie4Muerte == 1) {
							modelMatrixZombie4 = glm::translate(modelMatrixZombie4, glm::vec3(57.5f, 0.0f, -50.0f)); //87.5f, 0.0f, -50.0f
							puntaje++;
						}
						else if (zombie4Muerte == 2) {
							modelMatrixZombie4 = glm::translate(modelMatrixZombie4, glm::vec3(-160.0f, 0.0f, 70.0f)); //-72.5f, 0.0f, 20.0f
							animationIndexZombie3 = 1;
							state3 = 1;
							puntaje++;
						}
						else if (zombie4Muerte == 3) {
							renderZombie4 = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie5") == 0) {
						zombie5Muerte++;
						if (zombie5Muerte == 1) {
							modelMatrixZombie5 = glm::translate(modelMatrixZombie5, glm::vec3(-28.0f, 0.0f, -72.0f)); //32.0f, 0.0f, -77.0f
							puntaje++;
						}
						else if (zombie5Muerte == 2) {
							modelMatrixZombie5 = glm::translate(modelMatrixZombie5, glm::vec3(-100.0f, 0.0f, 127.0f)); //-68.0f, 0.0f, 50.0f
							puntaje++;
						}
						else if (zombie5Muerte == 3) {
							renderZombie5 = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie6") == 0) {
						zombie6Muerte++;
						if (zombie6Muerte == 1) {
							modelMatrixZombie6 = glm::translate(modelMatrixZombie6, glm::vec3(-91.0f, 0.0f, -50.0f)); //-11.0f, 0.0f, -54.5f
							puntaje++;
						}
						else if (zombie6Muerte == 2) {
							modelMatrixZombie6 = glm::translate(modelMatrixZombie6, glm::vec3(-26.5f, 0.0f, 92.5f)); //-37.5f, 0.0f, 38.0f
							animationIndexZombie4 = 1;
							state4 = 1;
							puntaje++;
						}
						else if (zombie6Muerte == 3) {
							renderZombie6 = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie7") == 0) {
						zombie7Muerte++;
						if (zombie7Muerte == 1) {
							modelMatrixZombie7 = glm::translate(modelMatrixZombie7, glm::vec3(-9.0f, 0.0f, -53.0f)); //56.0f, 0.0f, -43.0f
							puntaje++;
						}
						else if (zombie7Muerte == 2) {
							modelMatrixZombie7 = glm::translate(modelMatrixZombie7, glm::vec3(-101.0f, 0.0f, 99.25f)); //-45.0f, 0.0f, 56.25f
							puntaje++;
						}
						else if (zombie7Muerte == 3) {
							renderZombie7 = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie8") == 0) {
						zombie8Muerte++;
						if (zombie8Muerte == 1) {
							modelMatrixZombie8 = glm::translate(modelMatrixZombie8, glm::vec3(-78.5f, 0.0f, -92.0f)); //1.5f, 0.0f, -72.0f
							puntaje++;
						}
						else if (zombie8Muerte == 2) {
							modelMatrixZombie8 = glm::translate(modelMatrixZombie8, glm::vec3(-42.5f, 0.0f, 159.5f)); //-41.0f, 0.0f, 87.5f
							puntaje++;
						}
						else if (zombie8Muerte == 3) {
							renderZombie8 = false;
							puntaje++;
						}
					}
					if (it->first.compare("zombie9") == 0) {
						zombie9Muerte++;
						if (zombie9Muerte == 1) {
							modelMatrixZombie9 = glm::translate(modelMatrixZombie9, glm::vec3(-51.0f, 0.0f, -60.0f)); //29.0f, 0.0f, -60.0f
							puntaje++;
						}
						else if (zombie9Muerte == 2) {
							modelMatrixZombie9 = glm::translate(modelMatrixZombie9, glm::vec3(-97.0f, 0.0f, 145.0f)); //-68.0f, 0.0f, 95.0f
							puntaje++;
						}
						else if (zombie9Muerte == 3) {
							renderZombie9 = false;
							puntaje++;
						}
					}
				}
			}
		}


		///*******************************************
		// * Interpolation key frames with disconect objects
		// *******************************************/
		
		if (boolMuerto)
			animationIndex = 1;
		else
			animationIndex = 2;

		if (state4 == 1 || state4 == 2) {
			animationIndexZombie4 = 1;
		}
		else {
			animationIndexZombie4 = 0;
		}
		
		if (state == 1 || state == 2) {
			animationIndexZombie0 = 1;
		}
		else {
			animationIndexZombie0 = 0;
		}

		if (state1 == 1 || state1 == 2) {
			animationIndexZombie1 = 1;
		}
		else {
			animationIndexZombie1 = 0;
		}

		if (state2 == 1 || state2 == 2) {
			animationIndexZombie2 = 1;
		}
		else {
			animationIndexZombie2 = 0;
		}

		if (state3 == 1 || state3 == 2) {
			animationIndexZombie3 = 1;
		}
		else {
			animationIndexZombie3 = 0;
		}
	
		 /*******************************************
		  * Ruta Zombies
		  *******************************************/
		switch (state) {
		case 0:
			break;
		case 1:
			maxAdvanceZombie = 2.0;
			modelMatrixZombie3 = glm::translate(modelMatrixZombie3, glm::vec3(0.0f, 0.0f, 0.1f));
			avanceCount += 0.01;
			if (avanceCount > maxAdvanceZombie) {
				avanceCount = 0;
				state = 2;
			}
			break;

		case 2:
			rotCount += 1.0;
			modelMatrixZombie3 = glm::rotate(modelMatrixZombie3, glm::radians(1.0f), glm::vec3(0, -1, 0));
			if (rotCount >= 180.0) {
				rotCount = 0.0;
				state = 1;
			}
			break;
		default:
			break;
		}

		switch (state1) {
		case 0:
			break;
		case 1:
			maxAdvanceZombie1 = 2.0;
			modelMatrixZombie = glm::translate(modelMatrixZombie, glm::vec3(0.0f, 0.0f, 0.1f));
			avanceCount1 += 0.01;
			if (avanceCount1 > maxAdvanceZombie1) {
				avanceCount1 = 0;
				state1 = 2;
			}
			break;

		case 2:
			rotCount1 += 1.0;
			modelMatrixZombie = glm::rotate(modelMatrixZombie, glm::radians(1.0f), glm::vec3(0, -1, 0));
			if (rotCount1 >= 180.0) {
				rotCount1 = 0.0;
				state1 = 1;
			}
			break;
		default:
			break;
		}

		switch (state2) {
		case 0:
			break;
		case 1:
			maxAdvanceZombie2 = 2.0;
			modelMatrixZombie1 = glm::translate(modelMatrixZombie1, glm::vec3(0.0f, 0.0f, 0.1f));
			avanceCount2 += 0.01;
			if (avanceCount2 > maxAdvanceZombie2) {
				avanceCount2 = 0;
				state2 = 2;
			}
			break;

		case 2:
			rotCount2 += 1.0;
			modelMatrixZombie1 = glm::rotate(modelMatrixZombie1, glm::radians(1.0f), glm::vec3(0, -1, 0));
			if (rotCount2 >= 180.0) {
				rotCount2 = 0.0;
				state2 = 1;
			}
			break;
		default:
			break;
		}

		switch (state3) {
		case 0:
			break;
		case 1:
			maxAdvanceZombie3 = 2.0;
			modelMatrixZombie4 = glm::translate(modelMatrixZombie4, glm::vec3(0.0f, 0.0f, 0.1f));
			avanceCount3 += 0.01;
			if (avanceCount3 > maxAdvanceZombie3) {
				avanceCount3 = 0;
				state3 = 2;
			}
			break;

		case 2:
			rotCount3 += 1.0;
			modelMatrixZombie4 = glm::rotate(modelMatrixZombie4, glm::radians(1.0f), glm::vec3(0, -1, 0));
			if (rotCount3 >= 180.0) {
				rotCount3 = 0.0;
				state3 = 1;
			}
			break;
		default:
			break;
		}

		switch (state4) {
		case 0:
			break;
		case 1:
			maxAdvanceZombie4 = 2.0;
			modelMatrixZombie6 = glm::translate(modelMatrixZombie6, glm::vec3(0.0f, 0.0f, 0.1f));
			avanceCount4 += 0.01;
			if (avanceCount4 > maxAdvanceZombie4) {
				avanceCount4 = 0;
				state4 = 2;
			}
			break;

		case 2:
			rotCount4 += 1.0;
			modelMatrixZombie6 = glm::rotate(modelMatrixZombie6, glm::radians(1.0f), glm::vec3(0, -1, 0));
			if (rotCount4 >= 180.0) {
				rotCount4 = 0.0;
				state4 = 1;
			}
			break;
		default:
			break;
		}



		if (renderVidas == 3 && win == false)
		{
			//glfwSetTime(0);
			tiempoEvento2 = TimeManager::Instance().GetTime();
			tiempo_final = tiempoEvento2 - tiempoEvento1;
			modelText2->render(std::to_string(tiempo_final), -1, -0.5, 0.0, 1.0, 1.0, 24);
			modelText3->render(std::to_string(puntaje), -0.80, 0.88, 0.0, 1.0, 1.0, 30);
			glBindTexture(GL_TEXTURE_2D, textureVidasID);
			shaderTexture.setInt("outTexture", 0);
			boxInicio.render();
			glfwSwapBuffers(window);
			
		}
		else if (renderVidas == 2 && win == false)
		{
			//modelText->render("Vidas: <3 <3", -1, 0, 1.0, 1.0, 1.0, 24);
			tiempoEvento2 = TimeManager::Instance().GetTime();
			tiempo_final = tiempoEvento2 - tiempoEvento1;
			modelText2->render(std::to_string(tiempo_final), -1, -0.5, 0.0, 1.0, 1.0, 24);
			modelText3->render(std::to_string(puntaje), -0.80, 0.88, 0.0, 1.0, 1.0, 30);
			glBindTexture(GL_TEXTURE_2D, textureVidas2ID);
			shaderTexture.setInt("outTexture", 0);
			boxInicio.render();

			glfwSwapBuffers(window);
		}
		else if (renderVidas == 1 && win == false) {
			//modelText->render("Vidas: <3", -1, 0, 1.0, 1.0, 1.0, 24);
			tiempoEvento2 = TimeManager::Instance().GetTime();
			tiempo_final = tiempoEvento2 - tiempoEvento1;
			modelText2->render(std::to_string(tiempo_final), -1, -0.5, 0.0, 1.0, 1.0, 24);
			modelText3->render(std::to_string(puntaje), -0.80, 0.88, 0.0, 1.0, 1.0, 30);
			glBindTexture(GL_TEXTURE_2D, textureVidas3ID);
			shaderTexture.setInt("outTexture", 0);
			boxInicio.render();

			glfwSwapBuffers(window);
		}
		else if (renderVidas == 0 && win == false)
		{
			tiempoEvento2 = TimeManager::Instance().GetTime();
			tiempo_final = tiempoEvento2 - tiempoEvento1;
			modelText2->render(std::to_string(tiempo_final), -1, -0.5, 0.0, 1.0, 1.0, 24);
			modelText3->render(std::to_string(puntaje), -0.80, 0.88, 0.0, 1.0, 1.0, 30);
			glBindTexture(GL_TEXTURE_2D, textureVidas4ID);
			shaderTexture.setInt("outTexture", 0);
			boxInicio.render();

			glfwSwapBuffers(window);
		}
		
		else if (renderVidas >= 0 && win == true)//Aqui es si ganamos
		{
			modelText2->render(std::to_string(tiempo_final), 0.39, 0.0, 1.0, 1.0, 1.0, 30);
			modelText3->render(std::to_string(puntaje), 0.39, -0.15, 1.0, 1.0, 1.0, 30);
			glBindTexture(GL_TEXTURE_2D, textureCompletadoID);
			shaderTexture.setInt("outTexture", 0);
			boxInicio.render();
			glfwSwapBuffers(window);

		}
		else//Si perdemos
		{
			modelText2->render(std::to_string(tiempo_final), 0.39, 0.0, 1.0, 1.0, 1.0, 30);
			modelText3->render(std::to_string(puntaje), 0.39, -0.15, 1.0, 1.0, 1.0, 30);
			glBindTexture(GL_TEXTURE_2D, textureGameOverID);
			shaderTexture.setInt("outTexture", 0);
			boolMuerto = true;
			boxInicio.render();

			glfwSwapBuffers(window);
		}
		/****************************+
		 * Open AL sound data
		 */
		 

		source2Pos[0] = modelMatrixZombie[3].x;
		source2Pos[1] = modelMatrixZombie[3].y;
		source2Pos[2] = modelMatrixZombie[3].z;
		alSourcefv(source[2], AL_POSITION, source2Pos);

		// Listener for the Thris person camera
		listenerPos[0] = modelMatrixIronman[3].x;
		listenerPos[1] = modelMatrixIronman[3].y;
		listenerPos[2] = modelMatrixIronman[3].z;
		alListenerfv(AL_POSITION, listenerPos);

		glm::vec3 upModel = glm::normalize(modelMatrixIronman[1]);
		glm::vec3 frontModel = glm::normalize(modelMatrixIronman[2]);

		listenerOri[0] = frontModel.x;
		listenerOri[1] = frontModel.y;
		listenerOri[2] = frontModel.z;
		listenerOri[3] = upModel.x;
		listenerOri[4] = upModel.y;
		listenerOri[5] = upModel.z;

		// Listener for the First person camera
		
		alListenerfv(AL_ORIENTATION, listenerOri);

		for (unsigned int i = 0; i < sourcesPlay.size(); i++) {
			if (sourcesPlay[i]) {
				sourcesPlay[i] = false;
				alSourcePlay(source[i]);
			}
		}
	}
}

void prepareScene() {

	skyboxSphere.setShader(&shaderSkybox);


	terrain.setShader(&shaderTerrain);



	//Lamp models
	modelLamp1.setShader(&shaderMulLighting);
	modelLamp2.setShader(&shaderMulLighting);

	//Grass
	modelGrass.setShader(&shaderMulLighting);

	//Ironman
	ironmanModelAnimate.setShader(&shaderMulLighting);

	//Zombie
	zombieModelAnimate.setShader(&shaderMulLighting);
	zombie1ModelAnimate.setShader(&shaderMulLighting);
	zombie2ModelAnimate.setShader(&shaderMulLighting);
	zombie3ModelAnimate.setShader(&shaderMulLighting);
	zombie4ModelAnimate.setShader(&shaderMulLighting);
	zombie5ModelAnimate.setShader(&shaderMulLighting);
	zombie6ModelAnimate.setShader(&shaderMulLighting);
	zombie7ModelAnimate.setShader(&shaderMulLighting);
	zombie8ModelAnimate.setShader(&shaderMulLighting);
	zombie9ModelAnimate.setShader(&shaderMulLighting);

	//Entorno
	rejaModelAnimate.setShader(&shaderMulLighting);
	reja2ModelAnimate.setShader(&shaderMulLighting);
	limiteModelAnimate.setShader(&shaderMulLighting);
	limite2ModelAnimate.setShader(&shaderMulLighting);
	limite3ModelAnimate.setShader(&shaderMulLighting);
	limite4ModelAnimate.setShader(&shaderMulLighting);
	entradaModelAnimate.setShader(&shaderMulLighting);
	entrada2ModelAnimate.setShader(&shaderMulLighting);
	gasModelAnimate.setShader(&shaderMulLighting);
	carroModelAnimate.setShader(&shaderMulLighting);
	carro2ModelAnimate.setShader(&shaderMulLighting);
	carro3ModelAnimate.setShader(&shaderMulLighting);
	carropModelAnimate.setShader(&shaderMulLighting);
	apartamentosModelAnimate.setShader(&shaderMulLighting);
	arbolModelAnimate.setShader(&shaderMulLighting);
	arbol2ModelAnimate.setShader(&shaderMulLighting);
	arbol3ModelAnimate.setShader(&shaderMulLighting);
	arbol4ModelAnimate.setShader(&shaderMulLighting);
	arbol5ModelAnimate.setShader(&shaderMulLighting);
	arbol6ModelAnimate.setShader(&shaderMulLighting);
	arbol7ModelAnimate.setShader(&shaderMulLighting);
	arbol8ModelAnimate.setShader(&shaderMulLighting);
	arbol9ModelAnimate.setShader(&shaderMulLighting);
	arbol10ModelAnimate.setShader(&shaderMulLighting);
	arbol11ModelAnimate.setShader(&shaderMulLighting);
	arbol12ModelAnimate.setShader(&shaderMulLighting);
	arbol13ModelAnimate.setShader(&shaderMulLighting);
	rocaModelAnimate.setShader(&shaderMulLighting);
	roca2ModelAnimate.setShader(&shaderMulLighting);
	roca3ModelAnimate.setShader(&shaderMulLighting);
	roca4ModelAnimate.setShader(&shaderMulLighting);

}

void prepareDepthScene() {

	skyboxSphere.setShader(&shaderDepth);

	terrain.setShader(&shaderDepth);

	

	//Lamp models
	modelLamp1.setShader(&shaderDepth);
	modelLamp2.setShader(&shaderDepth);

	//Grass
	modelGrass.setShader(&shaderDepth);

	//Ironman
	ironmanModelAnimate.setShader(&shaderDepth);

	//Zombie
	zombieModelAnimate.setShader(&shaderDepth);
	zombie1ModelAnimate.setShader(&shaderDepth);
	zombie2ModelAnimate.setShader(&shaderDepth);
	zombie3ModelAnimate.setShader(&shaderDepth);
	zombie4ModelAnimate.setShader(&shaderDepth);
	zombie5ModelAnimate.setShader(&shaderDepth);
	zombie6ModelAnimate.setShader(&shaderDepth);
	zombie7ModelAnimate.setShader(&shaderDepth);
	zombie8ModelAnimate.setShader(&shaderDepth);
	zombie9ModelAnimate.setShader(&shaderDepth);

	//Entorno
	rejaModelAnimate.setShader(&shaderDepth);
	reja2ModelAnimate.setShader(&shaderDepth);
	limiteModelAnimate.setShader(&shaderDepth);
	limite2ModelAnimate.setShader(&shaderDepth);
	limite3ModelAnimate.setShader(&shaderDepth);
	limite4ModelAnimate.setShader(&shaderDepth);
	entradaModelAnimate.setShader(&shaderDepth);
	entrada2ModelAnimate.setShader(&shaderDepth);
	gasModelAnimate.setShader(&shaderDepth);
	carroModelAnimate.setShader(&shaderDepth);
	carro2ModelAnimate.setShader(&shaderDepth);
	carro3ModelAnimate.setShader(&shaderDepth);
	carropModelAnimate.setShader(&shaderDepth);
	apartamentosModelAnimate.setShader(&shaderDepth);
	arbolModelAnimate.setShader(&shaderDepth);
	arbol2ModelAnimate.setShader(&shaderDepth);
	arbol3ModelAnimate.setShader(&shaderDepth);
	arbol4ModelAnimate.setShader(&shaderDepth);
	arbol5ModelAnimate.setShader(&shaderDepth);
	arbol6ModelAnimate.setShader(&shaderDepth);
	arbol7ModelAnimate.setShader(&shaderDepth);
	arbol8ModelAnimate.setShader(&shaderDepth);
	arbol9ModelAnimate.setShader(&shaderDepth);
	arbol10ModelAnimate.setShader(&shaderDepth);
	arbol11ModelAnimate.setShader(&shaderDepth);
	arbol12ModelAnimate.setShader(&shaderDepth);
	arbol13ModelAnimate.setShader(&shaderDepth);
	rocaModelAnimate.setShader(&shaderDepth);
	roca2ModelAnimate.setShader(&shaderDepth);
	roca3ModelAnimate.setShader(&shaderDepth);
	roca4ModelAnimate.setShader(&shaderDepth);
}

void renderScene(bool renderParticles) {
	/*******************************************
	 * Terrain Cesped
	 *******************************************/
	glm::mat4 modelCesped = glm::mat4(1.0);
	modelCesped = glm::translate(modelCesped, glm::vec3(0.0, 0.0, 0.0));
	modelCesped = glm::scale(modelCesped, glm::vec3(200.0, 0.001, 200.0));
	// Se activa la textura del background
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBackgroundID);
	shaderTerrain.setInt("backgroundTexture", 0);
	// Se activa la textura de tierra
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
	shaderTerrain.setInt("rTexture", 1);
	// Se activa la textura de hierba
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
	shaderTerrain.setInt("gTexture", 2);
	// Se activa la textura del camino
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
	shaderTerrain.setInt("bTexture", 3);
	// Se activa la textura del blend map
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
	shaderTerrain.setInt("blendMapTexture", 4);
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(40, 40)));
	terrain.setPosition(glm::vec3(100, 0, 100));
	terrain.render();
	shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
	glBindTexture(GL_TEXTURE_2D, 0);

	/*******************************************
	 * Custom objects obj
	 *******************************************/
	
	// Forze to enable the unit texture to 0 always ----------------- IMPORTANT
	glActiveTexture(GL_TEXTURE0);

	// Render the lamps
	for (int i = 0; i < lamp1Position.size(); i++) {
		lamp1Position[i].y = terrain.getHeightTerrain(lamp1Position[i].x,
			lamp1Position[i].z);
		modelLamp1.setPosition(lamp1Position[i]);
		modelLamp1.setScale(glm::vec3(100.0, 100.0, 100.0));
		modelLamp1.setOrientation(glm::vec3(0, lamp1Orientation[i], 0));
		modelLamp1.render();
	}

	for (int i = 0; i < lamp2Position.size(); i++) {
		lamp2Position[i].y = terrain.getHeightTerrain(lamp2Position[i].x,
			lamp2Position[i].z);
		modelLamp2.setPosition(lamp2Position[i]);
		modelLamp2.setScale(glm::vec3(1.0, 1.0, 1.0));
		modelLamp2.setOrientation(glm::vec3(0, lamp2Orientation[i], 0));
		modelLamp2.render();
	}

	// Grass
	glDisable(GL_CULL_FACE);
	glm::vec3 grassPosition = glm::vec3(0.0, 0.0, 0.0);
	grassPosition.y = terrain.getHeightTerrain(grassPosition.x,
		grassPosition.z);
	modelGrass.setPosition(grassPosition);
	modelGrass.render();
	glEnable(GL_CULL_FACE);

	

	/*******************************************
	 * Custom Anim objects obj
	 *******************************************/

	//Ironman
	modelMatrixIronman[3][1] = terrain.getHeightTerrain(modelMatrixIronman[3][0], modelMatrixIronman[3][2]);
	glm::mat4 modelMatrixIronmanBody = glm::mat4(modelMatrixIronman);
	//	modelMatrixIronmanBody = glm::scale(modelMatrixIronmanBody,
	//			glm::vec3(0.021, 0.021, 0.021));
	ironmanModelAnimate.setAnimationIndex(animationIndex);
	ironmanModelAnimate.render(modelMatrixIronmanBody);

	//Zombie render
	if (renderZombie) {
		modelMatrixZombie[3][1] = terrain.getHeightTerrain(modelMatrixZombie[3][0], modelMatrixZombie[3][2]);
		zombieModelAnimate.setAnimationIndex(animationIndexZombie1);
		zombieModelAnimate.render(modelMatrixZombie);
	}

	if (renderZombie1) {	
	modelMatrixZombie1[3][1] = terrain.getHeightTerrain(modelMatrixZombie1[3][0], modelMatrixZombie1[3][2]);	
	zombie1ModelAnimate.setAnimationIndex(animationIndexZombie2);	
	zombie1ModelAnimate.render(modelMatrixZombie1);	
	}	

	if (renderZombie2) {	
		modelMatrixZombie2[3][1] = terrain.getHeightTerrain(modelMatrixZombie2[3][0], modelMatrixZombie2[3][2]);	
		zombie2ModelAnimate.setAnimationIndex(animationIndexZombie);	
		zombie2ModelAnimate.render(modelMatrixZombie2);	
	}

	if (renderZombie3) {
		modelMatrixZombie3[3][1] = terrain.getHeightTerrain(modelMatrixZombie3[3][0], modelMatrixZombie3[3][2]);
		zombie3ModelAnimate.setAnimationIndex(animationIndexZombie0);
		zombie3ModelAnimate.render(modelMatrixZombie3);
	}

	if (renderZombie4) {
		modelMatrixZombie4[3][1] = terrain.getHeightTerrain(modelMatrixZombie4[3][0], modelMatrixZombie4[3][2]);
		zombie4ModelAnimate.setAnimationIndex(animationIndexZombie3);
		zombie4ModelAnimate.render(modelMatrixZombie4);
	}

	if (renderZombie5) {
		modelMatrixZombie5[3][1] = terrain.getHeightTerrain(modelMatrixZombie5[3][0], modelMatrixZombie5[3][2]);
		zombie5ModelAnimate.setAnimationIndex(animationIndexZombie);
		zombie5ModelAnimate.render(modelMatrixZombie5);
	}
	if (renderZombie6) {
		modelMatrixZombie6[3][1] = terrain.getHeightTerrain(modelMatrixZombie6[3][0], modelMatrixZombie6[3][2]);
		zombie6ModelAnimate.setAnimationIndex(animationIndexZombie4);
		zombie6ModelAnimate.render(modelMatrixZombie6);
	}

	if (renderZombie7) {
		modelMatrixZombie7[3][1] = terrain.getHeightTerrain(modelMatrixZombie7[3][0], modelMatrixZombie7[3][2]);
		zombie7ModelAnimate.setAnimationIndex(animationIndexZombie);
		zombie7ModelAnimate.render(modelMatrixZombie7);
	}

	if (renderZombie8) {
		modelMatrixZombie8[3][1] = terrain.getHeightTerrain(modelMatrixZombie8[3][0], modelMatrixZombie8[3][2]);
		zombie8ModelAnimate.setAnimationIndex(animationIndexZombie);
		zombie8ModelAnimate.render(modelMatrixZombie8);
	}

	if (renderZombie9) {
		modelMatrixZombie9[3][1] = terrain.getHeightTerrain(modelMatrixZombie9[3][0], modelMatrixZombie9[3][2]);
		zombie9ModelAnimate.setAnimationIndex(animationIndexZombie);
		zombie9ModelAnimate.render(modelMatrixZombie9);
	}

	//Entorno
	modelMatrixReja[3][1] = terrain.getHeightTerrain(modelMatrixReja[3][0], modelMatrixReja[3][2]);
	rejaModelAnimate.render(modelMatrixReja);

	modelMatrixReja2[3][1] = terrain.getHeightTerrain(modelMatrixReja2[3][0], modelMatrixReja2[3][2]);
	reja2ModelAnimate.render(modelMatrixReja2);

	modelMatrixLimite[3][1] = terrain.getHeightTerrain(modelMatrixLimite[3][0], modelMatrixLimite[3][2]);
	limiteModelAnimate.render(modelMatrixLimite);

	modelMatrixLimite2[3][1] = terrain.getHeightTerrain(modelMatrixLimite2[3][0], modelMatrixLimite2[3][2]);
	limite2ModelAnimate.render(modelMatrixLimite2);

	modelMatrixLimite3[3][1] = terrain.getHeightTerrain(modelMatrixLimite3[3][0], modelMatrixLimite3[3][2]);
	limite3ModelAnimate.render(modelMatrixLimite3);

	modelMatrixLimite4[3][1] = terrain.getHeightTerrain(modelMatrixLimite4[3][0], modelMatrixLimite4[3][2]);
	limite4ModelAnimate.render(modelMatrixLimite4);

	modelMatrixEntrada[3][1] = terrain.getHeightTerrain(modelMatrixEntrada[3][0], modelMatrixEntrada[3][2]);
	entradaModelAnimate.render(modelMatrixEntrada);

	modelMatrixEntrada2[3][1] = terrain.getHeightTerrain(modelMatrixEntrada2[3][0], modelMatrixEntrada2[3][2]);
	entrada2ModelAnimate.render(modelMatrixEntrada2);

	modelMatrixGas[3][1] = terrain.getHeightTerrain(modelMatrixGas[3][0], modelMatrixGas[3][2]);
	gasModelAnimate.render(modelMatrixGas);

	modelMatrixCarro[3][1] = terrain.getHeightTerrain(modelMatrixCarro[3][0], modelMatrixCarro[3][2]);
	carroModelAnimate.render(modelMatrixCarro);

	modelMatrixCarro2[3][1] = terrain.getHeightTerrain(modelMatrixCarro2[3][0], modelMatrixCarro2[3][2]);
	carro2ModelAnimate.render(modelMatrixCarro2);

	modelMatrixCarro3[3][1] = terrain.getHeightTerrain(modelMatrixCarro3[3][0], modelMatrixCarro3[3][2]);
	carro3ModelAnimate.render(modelMatrixCarro3);

	modelMatrixCarrop[3][1] = terrain.getHeightTerrain(modelMatrixCarrop[3][0], modelMatrixCarrop[3][2]);
	carropModelAnimate.render(modelMatrixCarrop);

	modelMatrixApartamentos[3][1] = terrain.getHeightTerrain(modelMatrixApartamentos[3][0], modelMatrixApartamentos[3][2]);
	apartamentosModelAnimate.render(modelMatrixApartamentos);

	modelMatrixArbol[3][1] = terrain.getHeightTerrain(modelMatrixArbol[3][0], modelMatrixArbol[3][2]);
	arbolModelAnimate.render(modelMatrixArbol);

	modelMatrixArbol2[3][1] = terrain.getHeightTerrain(modelMatrixArbol2[3][0], modelMatrixArbol2[3][2]);
	arbol2ModelAnimate.render(modelMatrixArbol2);

	modelMatrixArbol3[3][1] = terrain.getHeightTerrain(modelMatrixArbol3[3][0], modelMatrixArbol3[3][2]);
	arbol3ModelAnimate.render(modelMatrixArbol3);

	modelMatrixArbol4[3][1] = terrain.getHeightTerrain(modelMatrixArbol4[3][0], modelMatrixArbol4[3][2]);
	arbol4ModelAnimate.render(modelMatrixArbol4);

	modelMatrixArbol5[3][1] = terrain.getHeightTerrain(modelMatrixArbol5[3][0], modelMatrixArbol5[3][2]);
	arbol5ModelAnimate.render(modelMatrixArbol5);

	modelMatrixArbol6[3][1] = terrain.getHeightTerrain(modelMatrixArbol6[3][0], modelMatrixArbol6[3][2]);
	arbol6ModelAnimate.render(modelMatrixArbol6);

	modelMatrixArbol7[3][1] = terrain.getHeightTerrain(modelMatrixArbol7[3][0], modelMatrixArbol7[3][2]);
	arbol7ModelAnimate.render(modelMatrixArbol7);

	modelMatrixArbol8[3][1] = terrain.getHeightTerrain(modelMatrixArbol8[3][0], modelMatrixArbol8[3][2]);
	arbol8ModelAnimate.render(modelMatrixArbol8);

	modelMatrixArbol9[3][1] = terrain.getHeightTerrain(modelMatrixArbol9[3][0], modelMatrixArbol9[3][2]);
	arbol9ModelAnimate.render(modelMatrixArbol9);

	modelMatrixArbol10[3][1] = terrain.getHeightTerrain(modelMatrixArbol10[3][0], modelMatrixArbol10[3][2]);
	arbol10ModelAnimate.render(modelMatrixArbol10);

	modelMatrixArbol11[3][1] = terrain.getHeightTerrain(modelMatrixArbol11[3][0], modelMatrixArbol11[3][2]);
	arbol11ModelAnimate.render(modelMatrixArbol11);

	modelMatrixArbol12[3][1] = terrain.getHeightTerrain(modelMatrixArbol12[3][0], modelMatrixArbol12[3][2]);
	arbol12ModelAnimate.render(modelMatrixArbol12);

	modelMatrixArbol13[3][1] = terrain.getHeightTerrain(modelMatrixArbol13[3][0], modelMatrixArbol13[3][2]);
	arbol13ModelAnimate.render(modelMatrixArbol13);

	modelMatrixRoca[3][1] = terrain.getHeightTerrain(modelMatrixRoca[3][0], modelMatrixRoca[3][2]);
	rocaModelAnimate.render(modelMatrixRoca);

	modelMatrixRoca2[3][1] = terrain.getHeightTerrain(modelMatrixRoca2[3][0], modelMatrixRoca2[3][2]);
	roca2ModelAnimate.render(modelMatrixRoca2);

	modelMatrixRoca3[3][1] = terrain.getHeightTerrain(modelMatrixRoca3[3][0], modelMatrixRoca3[3][2]);
	roca3ModelAnimate.render(modelMatrixRoca3);

	modelMatrixRoca4[3][1] = terrain.getHeightTerrain(modelMatrixRoca4[3][0], modelMatrixRoca4[3][2]);
	roca4ModelAnimate.render(modelMatrixRoca4);



	/**********
	 * Update the position with alpha objects
	 */
	 // Update the aircraft
	 

	 /**********
	  * Sorter with alpha objects
	  */
	std::map<float, std::pair<std::string, glm::vec3>> blendingSorted;
	std::map<std::string, glm::vec3>::iterator itblend;
	for (itblend = blendingUnsorted.begin(); itblend != blendingUnsorted.end();
		itblend++) {
		float distanceFromView = glm::length(
			camera->getPosition() - itblend->second);
		blendingSorted[distanceFromView] = std::make_pair(itblend->first,
			itblend->second);
	}

	/**********
	 * Render de las transparencias
	 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	for (std::map<float, std::pair<std::string, glm::vec3> >::reverse_iterator it = blendingSorted.rbegin(); it != blendingSorted.rend(); it++) {
		


		if (renderParticles && it->second.first.compare("fire") == 0) {
			/**********
			 * Init Render particles systems
			 */
			lastTimeParticlesAnimationFire = currTimeParticlesAnimationFire;
			currTimeParticlesAnimationFire = TimeManager::Instance().GetTime();

			shaderParticlesFire.setInt("Pass", 1);
			shaderParticlesFire.setFloat("Time",
				currTimeParticlesAnimationFire);
			shaderParticlesFire.setFloat("DeltaT",
				currTimeParticlesAnimationFire
				- lastTimeParticlesAnimationFire);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_1D, texId);
			glEnable(GL_RASTERIZER_DISCARD);
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[drawBuf]);
			glBeginTransformFeedback(GL_POINTS);
			glBindVertexArray(particleArray[1 - drawBuf]);
			glVertexAttribDivisor(0, 0);
			glVertexAttribDivisor(1, 0);
			glVertexAttribDivisor(2, 0);
			glDrawArrays(GL_POINTS, 0, nParticlesFire);
			glEndTransformFeedback();
			glDisable(GL_RASTERIZER_DISCARD);

			shaderParticlesFire.setInt("Pass", 2);
			glm::mat4 modelFireParticles = glm::mat4(1.0);
			modelFireParticles = glm::translate(modelFireParticles, it->second.second);
			//modelFireParticles[3][1] = terrain.getHeightTerrain(modelFireParticles[3][0], modelFireParticles[3][2]);
			shaderParticlesFire.setMatrix4("model", 1, false, glm::value_ptr(modelFireParticles));

			shaderParticlesFire.turnOn();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureParticleFireID);
			glDepthMask(GL_FALSE);
			glBindVertexArray(particleArray[drawBuf]);
			glVertexAttribDivisor(0, 1);
			glVertexAttribDivisor(1, 1);
			glVertexAttribDivisor(2, 1);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, nParticlesFire);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);
			drawBuf = 1 - drawBuf;
			shaderParticlesFire.turnOff();

			/****************************+
			 * Open AL sound data
			 */
			source1Pos[0] = modelFireParticles[3].x;
			source1Pos[1] = modelFireParticles[3].y;
			source1Pos[2] = modelFireParticles[3].z;
			alSourcefv(source[1], AL_POSITION, source1Pos);

			/**********
			 * End Render particles systems
			 */
		}

		else if (renderParticles && it->second.first.compare("fire2") == 0) {
			/**********
			 * Init Render particles systems
			 */
			lastTimeParticlesAnimationFire = currTimeParticlesAnimationFire;
			currTimeParticlesAnimationFire = TimeManager::Instance().GetTime();

			shaderParticlesFire.setInt("Pass", 1);
			shaderParticlesFire.setFloat("Time",
				currTimeParticlesAnimationFire);
			shaderParticlesFire.setFloat("DeltaT",
				currTimeParticlesAnimationFire
				- lastTimeParticlesAnimationFire);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_1D, texId);
			glEnable(GL_RASTERIZER_DISCARD);
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[drawBuf]);
			glBeginTransformFeedback(GL_POINTS);
			glBindVertexArray(particleArray[1 - drawBuf]);
			glVertexAttribDivisor(0, 0);
			glVertexAttribDivisor(1, 0);
			glVertexAttribDivisor(2, 0);
			glDrawArrays(GL_POINTS, 0, nParticlesFire);
			glEndTransformFeedback();
			glDisable(GL_RASTERIZER_DISCARD);

			shaderParticlesFire.setInt("Pass", 2);
			glm::mat4 modelFireParticles = glm::mat4(1.0);
			modelFireParticles = glm::translate(modelFireParticles,
				it->second.second);
			//modelFireParticles[3][1] = terrain.getHeightTerrain(
				//modelFireParticles[3][0], modelFireParticles[3][2]);
			shaderParticlesFire.setMatrix4("model", 1, false,
				glm::value_ptr(modelFireParticles));

			shaderParticlesFire.turnOn();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureParticleFireID);
			glDepthMask(GL_FALSE);
			glBindVertexArray(particleArray[drawBuf]);
			glVertexAttribDivisor(0, 1);
			glVertexAttribDivisor(1, 1);
			glVertexAttribDivisor(2, 1);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, nParticlesFire);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);
			drawBuf = 1 - drawBuf;
			shaderParticlesFire.turnOff();

			/****************************+
			 * Open AL sound data
			 */
			source1Pos[0] = modelFireParticles[3].x;
			source1Pos[1] = modelFireParticles[3].y;
			source1Pos[2] = modelFireParticles[3].z;
			alSourcefv(source[1], AL_POSITION, source1Pos);

			/**********
			 * End Render particles systems
			 */
		}
		/*} else*/ if (renderParticles && it->second.first.compare("fire3") == 0) {
			/**********
			 * Init Render particles systems
			 */
			lastTimeParticlesAnimationFire = currTimeParticlesAnimationFire;
			currTimeParticlesAnimationFire = TimeManager::Instance().GetTime();

			shaderParticlesFire.setInt("Pass", 1);
			shaderParticlesFire.setFloat("Time",
				currTimeParticlesAnimationFire);
			shaderParticlesFire.setFloat("DeltaT",
				currTimeParticlesAnimationFire
				- lastTimeParticlesAnimationFire);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_1D, texId);
			glEnable(GL_RASTERIZER_DISCARD);
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[drawBuf]);
			glBeginTransformFeedback(GL_POINTS);
			glBindVertexArray(particleArray[1 - drawBuf]);
			glVertexAttribDivisor(0, 0);
			glVertexAttribDivisor(1, 0);
			glVertexAttribDivisor(2, 0);
			glDrawArrays(GL_POINTS, 0, nParticlesFire);
			glEndTransformFeedback();
			glDisable(GL_RASTERIZER_DISCARD);

			shaderParticlesFire.setInt("Pass", 2);
			glm::mat4 modelFireParticles = glm::mat4(1.0);
			modelFireParticles = glm::translate(modelFireParticles,
				it->second.second);
			/*modelFireParticles[3][1] = terrain.getHeightTerrain(
				modelFireParticles[3][0], modelFireParticles[3][2]);*/
			shaderParticlesFire.setMatrix4("model", 1, false,
				glm::value_ptr(modelFireParticles));

			shaderParticlesFire.turnOn();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureParticleFireID);
			glDepthMask(GL_FALSE);
			glBindVertexArray(particleArray[drawBuf]);
			glVertexAttribDivisor(0, 1);
			glVertexAttribDivisor(1, 1);
			glVertexAttribDivisor(2, 1);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, nParticlesFire);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);
			drawBuf = 1 - drawBuf;
			shaderParticlesFire.turnOff();

			/****************************+
			 * Open AL sound data
			 */
			source1Pos[0] = modelFireParticles[3].x;
			source1Pos[1] = modelFireParticles[3].y;
			source1Pos[2] = modelFireParticles[3].z;
			alSourcefv(source[1], AL_POSITION, source1Pos);

			/**********
			 * End Render particles systems
			 */
		}
		/*} else*/ if (renderParticles && it->second.first.compare("fire4") == 0) {
			/**********
			 * Init Render particles systems
			 */
			lastTimeParticlesAnimationFire = currTimeParticlesAnimationFire;
			currTimeParticlesAnimationFire = TimeManager::Instance().GetTime();

			shaderParticlesFire.setInt("Pass", 1);
			shaderParticlesFire.setFloat("Time",
				currTimeParticlesAnimationFire);
			shaderParticlesFire.setFloat("DeltaT",
				currTimeParticlesAnimationFire
				- lastTimeParticlesAnimationFire);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_1D, texId);
			glEnable(GL_RASTERIZER_DISCARD);
			glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, feedback[drawBuf]);
			glBeginTransformFeedback(GL_POINTS);
			glBindVertexArray(particleArray[1 - drawBuf]);
			glVertexAttribDivisor(0, 0);
			glVertexAttribDivisor(1, 0);
			glVertexAttribDivisor(2, 0);
			glDrawArrays(GL_POINTS, 0, nParticlesFire);
			glEndTransformFeedback();
			glDisable(GL_RASTERIZER_DISCARD);

			shaderParticlesFire.setInt("Pass", 2);
			glm::mat4 modelFireParticles = glm::mat4(1.0);
			modelFireParticles = glm::translate(modelFireParticles,
				it->second.second);
			/*modelFireParticles[3][1] = terrain.getHeightTerrain(
				modelFireParticles[3][0], modelFireParticles[3][2]);*/
			shaderParticlesFire.setMatrix4("model", 1, false,
				glm::value_ptr(modelFireParticles));

			shaderParticlesFire.turnOn();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureParticleFireID);
			glDepthMask(GL_FALSE);
			glBindVertexArray(particleArray[drawBuf]);
			glVertexAttribDivisor(0, 1);
			glVertexAttribDivisor(1, 1);
			glVertexAttribDivisor(2, 1);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, nParticlesFire);
			glBindVertexArray(0);
			glDepthMask(GL_TRUE);
			drawBuf = 1 - drawBuf;
			shaderParticlesFire.turnOff();

			/****************************+
			 * Open AL sound data
			 */
			source1Pos[0] = modelFireParticles[3].x;
			source1Pos[1] = modelFireParticles[3].y;
			source1Pos[2] = modelFireParticles[3].z;
			alSourcefv(source[1], AL_POSITION, source1Pos);

			/**********
			 * End Render particles systems
			 */
		}
	}
	glEnable(GL_CULL_FACE);
}

int main(int argc, char** argv) {

	init(800, 700, "Ironman", false);
	applicationLoop();
	destroy();

	return 1;
}