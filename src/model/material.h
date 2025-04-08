#pragma once

#include <string>

struct MaterialData {
  std::string mtlName = "";

  float colorAmbientR = 0.2;
  float colorAmbientG = 0.2;
  float colorAmbientB = 0.2;

  float colorDiffuseR = 0.8;
  float colorDiffuseG = 0.8;
  float colorDiffuseB = 0.8;

  std::string colorDiffuseMapName = "";

  float colorSpecularR = 1.0;
  float colorSpecularG = 1.0;
  float colorSpecularB = 1.0;

  float dissolve = 1.0;

  float opticalDensity = 1.0;

  // 0  = Color on and Ambient off
  // 1  = Color on and Ambient on
  // 2  = Highlight on
  // 3  = Reflection on and Ray trace on
  // 4  = Transparency: Glass on, Reflection: Ray trace on
  // 5  = Reflection: Fresnel on and Ray trace on
  // 6  = Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
  // 7  = Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
  // 8  = Reflection on and Ray trace off
  // 9  = Transparency: Glass on, Reflection: Ray trace off
  // 10 = Casts shadows onto invisible surfaces
  int illumination = 0;

  float shininess = 0.0;

  float transmissionFilterR = 1.0;
  float transmissionFilterG = 1.0;
  float transmissionFilterB = 1.0;
};
