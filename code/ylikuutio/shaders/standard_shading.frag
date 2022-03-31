#version 330 core

// Interpolated values from the vertex shaders.
varying vec2 UV;
varying vec3 position_worldspace;
varying vec3 normal_cameraspace;
varying vec3 eye_direction_cameraspace;
varying vec3 light_direction_cameraspace;

// Values that stay constant for each `Scene`.
layout (std140) uniform scene_uniform_block
{
    vec4 light_position_worldspace;
    float water_level;
};

uniform sampler2D texture_sampler;

out vec3 color;

void main()
{
    // Light emission properties
    // You probably want to put them as uniforms
    vec3 light_color = vec3(1, 1, 1);
    float light_power = 40000000000.0f;

    if (position_worldspace.y < water_level)
    {
        light_color = vec3(0, 0, 1);
    }

    // Material properties
    vec3 material_diffuse_color = texture(texture_sampler, UV).rgb;
    vec3 material_ambient_color = vec3(0.1, 0.1, 0.1) * material_diffuse_color;
    vec3 material_specular_color = vec3(0.3, 0.3, 0.3);

    // Distance to the light
    float distance = length(light_position_worldspace.xyz - position_worldspace);

    // Normal of the computed fragment, in camera space
    vec3 n = normalize(normal_cameraspace);
    // Direction of the light (from the fragment to the light)
    vec3 l = normalize(light_direction_cameraspace);
    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    //  - light is behind the triangle -> 0
    float cos_theta = clamp(dot(n, l), 0, 1);

    // Eye vector (towards the camera)
    vec3 E = normalize(eye_direction_cameraspace);
    // Direction in which the triangle reflects the light
    vec3 R = reflect(-l, n);
    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float cos_alpha = clamp(dot(E, R), 0, 1);

    color =
        // Ambient: simulates indirect lighting.
        material_ambient_color +
        // Diffuse: "color" of the object.
        material_diffuse_color * light_color * light_power * cos_theta / (distance * distance) +
        // Specular: reflective highlight, like a mirror.
        material_specular_color * light_color * light_power * pow(cos_alpha, 5) / (distance * distance);
}
