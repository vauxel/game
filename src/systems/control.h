#pragma once

#include "system.h"
#include "input.h"
#include "camera.h"
#include "entity.h"

class ControlSystem : public System {
  private:
    Camera* camera;
  public:
    bool cameraControl = true;
    
    ControlSystem(Camera* cam);
    ~ControlSystem();

    virtual void attachEntity(Entity* entity);
    virtual void loop();
    virtual void handleMessage(MessageType type, Message* msg);
};
