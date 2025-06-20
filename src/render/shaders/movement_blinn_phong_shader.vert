#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec2 texCoord;
out vec4 FragPosLightSpace;

uniform mat4 uModel;
uniform mat4 uViewProjection;
uniform mat4 lightSpaceMatrix;
uniform float uTime; // Added for animation

void main()
{
    vec4 worldPos = uModel * vec4(aPos, 1.0);
    
    // Animate Y position with a wave based on X/Z and time
    float amplitude = 0.5;
    float phase = worldPos.x * 0.5 + worldPos.z * 0.5;
    worldPos.y += amplitude * sin(uTime + phase);
    FragPos = vec3(worldPos);
    Normal = mat3(transpose(inverse(uModel))) * aNormal;
    gl_Position = uViewProjection * worldPos;
    FragPosLightSpace = lightSpaceMatrix * worldPos;
    texCoord = aTexCoord;
}