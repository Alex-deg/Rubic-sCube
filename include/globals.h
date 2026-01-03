#pragma once
#include <glm/glm.hpp>

#define PI 3.14159265358979323846f
extern int WinWidth;
extern int WinHeight;
extern int state = 1;
extern const int COUNT_STATES = 12;
extern const glm::mat4 WorldMatrix;
extern const glm::mat4 WorldMatrix_cj;
extern bool rotationmode;
extern float cameraRadius;
extern float cameraAngle;
extern float cameraHeight;
extern bool operationCheck;
extern bool needToUpdateAfterRotateCube;
extern int key_value;
extern glm::vec3 figurePosition;
extern glm::vec3 cameraPosition;
