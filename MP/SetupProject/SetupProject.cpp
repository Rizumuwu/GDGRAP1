
#include "Converge.h"
using namespace Controller;
using namespace PointOfInterest;
using namespace character;

Game::Game() {
    Initialize();

    this->character = new Character();
    this->world = new Worldspace();
    this->Moon = new Directional();
    LightData data;
    data.light_direction = glm::normalize(glm::vec3(140.0f, 90.0f, 0.0f));
    data.light_color = glm::vec3(1.0f, 1.0f, 1.0f);
    data.ambient_color = glm::vec3(1.0f, 1.0f, 1.0f);
    data.ambient_str = 0.5f;
    data.spec_str = 0.2f;
    data.spec_phong = 16.0f;
    data.intensity = 0.5f;
    this->Moon->InitLightData(data);

    InitPOI();
}

void Controller::Game::InitPOI() {
    POI* Poi;
    // Load in Dino
    Poi = new POI();
    Poi->Initialize("3D/POI/Dino_Model.obj", "3D/POI/Dino_Texture.jpg",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(50.0f, 2.0f, -40.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::PITCH, -90.0f);
    Poi->RetrieveTransform()->InitScale(0.5f);
    POIList.push_back(Poi);
    Poi = new POI();
    Poi->Initialize("3D/POI/Dino_Model.obj", "3D/POI/Dino_Texture.jpg",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(100.0f, 2.0f, -40.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::PITCH, -90.0f);
    Poi->RetrieveTransform()->InitScale(0.5f);
    POIList.push_back(Poi);
    Poi = new POI();
    Poi->Initialize("3D/POI/Dino_Model.obj", "3D/POI/Dino_Texture.jpg",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(0.0f, 2.0f, -40.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::PITCH, -90.0f);
    Poi->RetrieveTransform()->InitScale(0.5f);
    POIList.push_back(Poi);
    Poi = new POI();
    Poi->Initialize("3D/POI/Dino_Model.obj", "3D/POI/Dino_Texture.jpg",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(-50.0f, 2.0f, -40.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::PITCH, -90.0f);
    Poi->RetrieveTransform()->InitScale(0.5f);
    POIList.push_back(Poi);

    // Load in Aircraft
    Poi = new POI();
    Poi->Initialize("3D/POI/Aircraft_Model.obj", "3D/POI/Aircraft_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(0.0f, 16.0f, 10.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, -90.0f);
    Poi->RetrieveTransform()->InitScale(20.0f);
    POIList.push_back(Poi);
    Poi = new POI();

    // Load in Droid
    Poi = new POI();
    Poi->Initialize("3D/POI/Droid_Model.obj", "3D/POI/Droid_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(0.0f, 0.0f, 70.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, 180.0f);
    Poi->RetrieveTransform()->InitScale(5.0f);
    POIList.push_back(Poi);
    Poi = new POI();
    Poi->Initialize("3D/POI/Droid_Model.obj", "3D/POI/Droid_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(20.0f, 0.0f, 70.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, 180.0f);
    Poi->RetrieveTransform()->InitScale(5.0f);
    POIList.push_back(Poi);
    Poi = new POI();
    Poi->Initialize("3D/POI/Droid_Model.obj", "3D/POI/Droid_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(-20.0f, 0.0f, 70.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, 180.0f);
    Poi->RetrieveTransform()->InitScale(5.0f);
    POIList.push_back(Poi);
    Poi = new POI();
    Poi->Initialize("3D/POI/Droid_Model.obj", "3D/POI/Droid_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(10.0f, 0.0f, 90.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, 180.0f);
    Poi->RetrieveTransform()->InitScale(5.0f);
    POIList.push_back(Poi);
    Poi = new POI();
    Poi->Initialize("3D/POI/Droid_Model.obj", "3D/POI/Droid_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(-10.0f, 0.0f, 90.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, 180.0f);
    Poi->RetrieveTransform()->InitScale(5.0f);
    POIList.push_back(Poi);

    // Load in Anvil
    Poi = new POI();
    Poi->Initialize("3D/POI/Anvil_Model.obj", "3D/POI/Anvil_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(0.0f, 0.0f, -90.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, 90.0f);
    Poi->RetrieveTransform()->InitScale(20.0f);
    POIList.push_back(Poi);

    // Load in Anti-Air
    Poi = new POI();
    Poi->Initialize("3D/POI/AAT_Model.obj", "3D/POI/AAT_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(0.0f, 0.0f, 0.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, -90.0f);
    Poi->RetrieveTransform()->InitScale(5.0f);
    POIList.push_back(Poi);
    Poi = new POI();
    Poi->Initialize("3D/POI/AAT_Model.obj", "3D/POI/AAT_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(-90.0f, 0.0f, 0.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, -90.0f);
    Poi->RetrieveTransform()->InitScale(5.0f);
    POIList.push_back(Poi);

    // Load in Mandarin
    Poi = new POI();
    Poi->Initialize("3D/POI/Mandarin_Model.obj", "3D/POI/Mandarin_Texture.png",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(60.0f, 10.0f, 90.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::YAW, -90.0f);
    Poi->RetrieveTransform()->InitScale(0.5f);
    POIList.push_back(Poi);

    // Make ground
    Poi = new POI();
    Poi->Initialize("3D/POI/plane.obj", "3D/POI/Dino_Texture.jpg",
        "Shaders/POI.vert", "Shaders/POI.frag");
    Poi->RetrieveTransform()->InitPos(0.0f, -1.5f, 0.0f);
    Poi->RetrieveTransform()->InitRotation(RotationAxis::PITCH, 90.0f);
    Poi->RetrieveTransform()->InitScale(500.0f);
    POIList.push_back(Poi);
}

void Game::Initialize() {
    if (!glfwInit())
        exit(-1);
    this->gameWindow = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Dino War - by Paglinawan, Miguel", NULL, NULL);
    if (!gameWindow) {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(gameWindow);
    gladLoadGL();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::Run() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glfwSetTime(0.0f);
    //Variables to make sure each frame is fixed (avoid glitches caused by lag or speedups)
    double prevUpdate = 0.0f;
    float tpf = 1.f / FRAME_RATE_LIMIT;
    //Initialize cursor at window center;
    glfwSetCursorPos(this->gameWindow, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

    while (!glfwWindowShouldClose(gameWindow)) {
        this->ProcessInput();
        prevUpdate += glfwGetTime();
        glfwSetTime(0.0f);
        while (prevUpdate > tpf) {
            prevUpdate -= tpf;
            this->Update(tpf);
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        this->Render();
        glfwSwapBuffers(gameWindow);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Game::ProcessInput(){
    this->character->CheckInputs(this->gameWindow);
}

void Game::Update(float tDeltaTime) {
    this->character->Update(tDeltaTime);
}

void Game::Render() {
    LightData pointLightData = this->character->RetrievePointData();
    LightData dirLightData = this->Moon->RetrieveLightData();
    CameraData cameraData = this->character->RetrieveCamData();

    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    this->world->Draw(cameraData);

    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);

    this->character->InitDirectionalData(dirLightData);

    // Draw player first
    this->character->Draw();

    // Draw objects next
    for (POI* Poi : POIList) {
        Poi->Draw(cameraData, pointLightData, dirLightData);
    }
}

int main() {

    Game game;
    game.Run();

    return 0;
}

/*
References:
Player Model - https://opengameart.org/content/stridsvagn-103
Dino - https://opengameart.org/content/low-poly-dino
Mandarin Orange - https://opengameart.org/content/mandarin-orange
Aircraft - https://opengameart.org/content/abstract-rts-model-pack
Turret - https://opengameart.org/content/abstract-rts-model-pack
Droid - https://opengameart.org/content/abstract-rts-model-pack
Anvil - https://opengameart.org/content/anvil-1 
*/