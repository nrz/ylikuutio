#version 120

// Interpolated values from the vertex shaders
varying vec2 UV;
varying vec3 position_worldspace;
varying vec3 normal_cameraspace;
varying vec3 eye_direction_cameraspace;
varying vec3 light_direction_cameraspace;

// Values that stay constant for the whole mesh.
uniform sampler2D my_texture_sampler;
uniform mat4 MV;
uniform vec3 light_position_worldspace;
uniform float water_level;

void main()
{
    // Light emission properties
    // You probably want to put them as uniforms
    vec3 LightColor = vec3(1, 1, 1);
    float LightPower = 20000.0f;

    if (position_worldspace.y < water_level)
    {
        LightColor = vec3(0, 0, 1);
    }

    // Material properties
    vec3 MaterialDiffuseColor = texture2D(my_texture_sampler, UV).rgb;
    vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
    vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

    // Distance to the light
    // float distance = length(light_position_worldspace - position_worldspace);
    float distance = 100.0f;

    // Normal of the computed fragment, in camera space
    vec3 n = normalize(normal_cameraspace);
    // Direction of the light (from the fragment to the light)
    vec3 l = normalize(light_direction_cameraspace);
    // Cosine of the angle between the normal and the light direction,
    // clamped above 0
    //  - light is at the vertical of the triangle -> 1
    //  - light is perpendicular to the triangle -> 0
    //  - light is behind the triangle -> 0
    float cosTheta = clamp(dot(n, l), 0, 1);

    // Eye vector (towards the camera)
    vec3 E = normalize(eye_direction_cameraspace);
    // Direction in which the triangle reflects the light
    vec3 R = reflect(-l, n);
    // Cosine of the angle between the Eye vector and the Reflect vector,
    // clamped to 0
    //  - Looking into the reflection -> 1
    //  - Looking elsewhere -> < 1
    float cosAlpha = clamp(dot(E, R), 0, 1);

    gl_FragColor.rgb =
        // Ambient : simulates indirect lighting
        MaterialAmbientColor +
        // Diffuse : "color" of the object
        MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance) +
        // Specular : reflective highlight, like a mirror
        MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance * distance);
}
