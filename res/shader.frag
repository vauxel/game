#version 460

in vec2 uv;
out vec3 fragColor;

uniform sampler2D textureSampler;

void main() {
    fragColor = texture(textureSampler, uv).rgb;
}