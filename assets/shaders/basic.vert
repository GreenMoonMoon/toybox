#version 460
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;

uniform mat4 view;
uniform mat4 modelView;
uniform mat4 normalMatrix;
uniform mat4 Projection;
uniform mat4 mvp;

uniform vec4 lightSource;
uniform vec3 lightIntensity;
uniform vec3 diffuseReflectivity;

out vec3 light;
out vec3 color;

void main() {
    color = aNormal;

    vec3 tNormal = (normalMatrix * vec4(aNormal, 0.0)).xyz;

    vec4 csPosition = modelView * vec4(aPosition, 1.0); // Camera space position
    vec3 lightDirection = (view * vec4(lightSource.xyz - aPosition, 0.0)).xyz; // Calculate the ligth direction in the same space.

    light = lightIntensity * diffuseReflectivity * (max(dot(lightDirection, tNormal), 0.0));

//    gl_Position = mvp * vec4(aPosition, 1.0);
    gl_Position = Projection * csPosition;
}