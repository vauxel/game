#include "render.h"

RenderSystem::RenderSystem(GLFWwindow* win, Camera* cam) {
  window = win;
  camera = cam;

  EntityManager::instance()->registerSystem(this);

  glfwSwapInterval(1);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_CULL_FACE);

  ResourceManager::instance()->loadResource(new Shader, "shader", "res/shader");
  shader = ResourceManager::instance()->getResource<Shader>("shader");

  InputHandler::instance()->addKeyBinding(GLFW_KEY_3, std::bind(&RenderSystem::createNewLightAtCamera, this));
  InputHandler::instance()->addKeyBinding(GLFW_KEY_1, std::bind(&RenderSystem::moveLight1ToCamera, this));
  InputHandler::instance()->addKeyBinding(GLFW_KEY_2, std::bind(&RenderSystem::moveLight2ToCamera, this));
}

RenderSystem::~RenderSystem() {
  this->shader->unload();
}

void RenderSystem::setCamera(Camera* cam) {
  camera = cam;
}

void RenderSystem::updateCameraMatrix(Camera* cam) {
  glm::mat4 projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 100.0f);
  glm::mat4 viewMatrix = glm::lookAt(
    cam->getPos(),
    cam->getPos() + cam->getTarget(),
    cam->getUp()
  );

  cameraMatrix = projectionMatrix * viewMatrix;

  glUniformMatrix4fv(shader->getUniformLocation("camera"), 1, GL_FALSE, &cameraMatrix[0][0]);

  glUniform3fv(shader->getUniformLocation("cameraPosition"), 1, &cam->getPos()[0]);
}

void RenderSystem::updateModelMatrix(glm::vec3 pos, glm::quat rot) {
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, pos);
  modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f));
  modelMatrix *= glm::mat4_cast(rot);

  modelNormalMatrix = glm::mat3(glm::transpose(glm::inverse(modelMatrix)));

  glUniformMatrix4fv(shader->getUniformLocation("model"), 1, GL_FALSE, &modelMatrix[0][0]);
  glUniformMatrix3fv(shader->getUniformLocation("modelNormal"), 1, GL_FALSE, &modelNormalMatrix[0][0]);
}

void RenderSystem::updateLightingUniforms() {
  glUniform1i(shader->getUniformLocation("numLights"), (int)lights.size());

  char uniformName[100];
  for(unsigned int i = 0; i < lights.size(); i++) {
    snprintf(uniformName, 99, "lights[%d].type", i);
    glUniform1i(
      shader->getUniformLocation(uniformName),
      lights[i]->get<Light>()->type
    );

    snprintf(uniformName, 99, "lights[%d].position", i);
    glUniform3fv(
      shader->getUniformLocation(uniformName),
      1,
      &lights[i]->get<Spatial>()->position[0]
    );

    snprintf(uniformName, 99, "lights[%d].intensities", i);
    glUniform3fv(
      shader->getUniformLocation(uniformName),
      1,
      &lights[i]->get<Light>()->intensities[0]
    );
    
    snprintf(uniformName, 99, "lights[%d].attenuation", i);
    glUniform1f(
      shader->getUniformLocation(uniformName),
      lights[i]->get<Light>()->attenuation
    );

    snprintf(uniformName, 99, "lights[%d].ambientCoefficient", i);
    glUniform1f(
      shader->getUniformLocation(uniformName),
      lights[i]->get<Light>()->ambientCoefficient
    );

    snprintf(uniformName, 99, "lights[%d].coneAngle", i);
    glUniform1f(
      shader->getUniformLocation(uniformName),
      lights[i]->get<Light>()->coneAngle
    );

    snprintf(uniformName, 99, "lights[%d].coneDirection", i);
    glUniform3fv(
      shader->getUniformLocation(uniformName),
      1,
      &lights[i]->get<Light>()->coneDirection[0]
    );
  }
}

void RenderSystem::renderEntities() {
  for (Entity* entity : entities) {
    updateModelMatrix(
      entity->get<Spatial>()->position,
      entity->get<Spatial>()->rotation
    );

    entity->get<Render>()->render(this->shader);
  }
}

void RenderSystem::loop() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glUseProgram(shader->program);

  updateCameraMatrix(camera);
  updateLightingUniforms();
  renderEntities();

  glfwSwapBuffers(window);
}

void RenderSystem::attachEntity(Entity* entity) {
  if (entity->has<Render>() && entity->has<Spatial>()) {
    LOG_DEBUG("Attached render entity [id=%d]", entity->getId());
    entities.emplace_back(entity);
  }
  
  if (entity->has<Light>()) {
    LOG_DEBUG("Attached light entity [id=%d]", entity->getId());
    lights.emplace_back(entity);
  }
}

void RenderSystem::handleMessage(MessageType type, Message* msg) {}

void RenderSystem::moveLight1ToCamera() {
  glm::vec3 pos = camera->getPos();
  lights[0]->get<Spatial>()->position = pos;
  LOG_DEBUG("Set light 1 pos to [%f %f %f]", pos.x, pos.y, pos.z);
}

void RenderSystem::moveLight2ToCamera() {
  glm::vec3 pos = camera->getPos();
  glm::vec3 target = camera->getTarget();
  lights[1]->get<Spatial>()->position = pos;
  lights[1]->get<Light>()->coneDirection = target;
  LOG_DEBUG("Set light 2 pos to [%f %f %f] [%f %f %f]", pos.x, pos.y, pos.z, target.x, target.y, target.z);
}

void RenderSystem::createNewLightAtCamera() {
  glm::vec3 pos = camera->getPos();
  Entity* newLight = new Entity();
  newLight->assign<Spatial>(pos);
  newLight->assign<Light>(
    Light::Type::POINT,
    glm::vec3(2.0f, 2.0f, 2.0f),
    1.0f,
    0.05f
  );
  EntityManager::instance()->instantiate(newLight);
}
