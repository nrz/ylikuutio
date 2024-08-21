#version 330 core

// Interpolated values from the vertex shaders.
varying vec2 uv;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sampler;

uniform int screen_width;

out vec4 color;

void main()
{
    // Go west.
    vec2 uv_east = uv + vec2(1.0f / screen_width, 0.0f);
    color = texture(texture_sampler, uv_east);
}
