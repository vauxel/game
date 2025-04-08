#version 410
#define MAX_LIGHTS 10

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
}

in vec3 fragPosition;
in vec2 fragUV;
in vec3 fragNormal;

out vec4 fragColor;

uniform sampler2D textureSampler;

uniform mat4 camera;
uniform mat4 model;
uniform mat3 modelNormal;
uniform vec3 cameraPosition;

uniform Material material;

uniform int numLights;
uniform struct Light {
	int type;
	vec3 position;
	vec3 intensities;
	float attenuation;
	float ambientCoefficient;
	float coneAngle;
	vec3 coneDirection;
} lights[MAX_LIGHTS];

vec3 calcLight(Light light, vec3 surfaceColor, vec3 normal, vec3 surfacePos, vec3 surfaceToCamera) {
	vec3 surfaceToLight;
	float attenuation = 1.0;

	if (light.type == 0) { // Directional light
		surfaceToLight = normalize(light.position.xyz);
	} else if (light.type == 1 || light.type == 2) { // Point/Spot light
		// Point light
		surfaceToLight = normalize(light.position.xyz - surfacePos);
		float distanceToLight = length(light.position.xyz - surfacePos);
		attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));

		// Spot light
		if (light.type == 2) {
			float lightToSurfaceAngle = degrees(acos(dot(-surfaceToLight, normalize(light.coneDirection))));
			if (lightToSurfaceAngle > light.coneAngle){
				attenuation = 0.0;
			}
		}
	}

	vec3 ambient = surfaceColor.rgb * light.ambientCoefficient;

	float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight));
	vec3 diffuse = diffuseCoefficient * surfaceColor.rgb * light.intensities;

	return ambient + attenuation * diffuse;
}

void main() {
	vec3 normal = modelNormal * fragNormal;
	vec3 surfacePos = vec3(model * vec4(fragPosition, 1));
	vec4 surfaceColor = texture(textureSampler, fragUV);
	vec3 surfaceToCamera = normalize(cameraPosition - surfacePos);
	
	vec3 linearColor = vec3(0.0);
	for(int i = 0; i < numLights; i++) {
		linearColor += calcLight(
			lights[i],
			surfaceColor.rgb,
			normal,
			surfacePos,
			surfaceToCamera
		);
	}

	fragColor = vec4(linearColor, surfaceColor.a);
}