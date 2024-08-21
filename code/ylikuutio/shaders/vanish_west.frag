#version 330 core

// Interpolated values from the vertex shaders.
varying vec2 uv;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sampler;

uniform int screen_width;

out vec4 color;

void main()
{
    // Vanish west.
    vec2 UV_east = uv + vec2(1.0f / screen_width, 0.0f);

    float current_red = texture(texture_sampler, uv).r;
    float current_green = texture(texture_sampler, uv).g;
    float current_blue = texture(texture_sampler, uv).b;

    float east_red = texture(texture_sampler, UV_east).r;
    float east_green = texture(texture_sampler, UV_east).g;
    float east_blue = texture(texture_sampler, UV_east).b;

    if (current_red > east_red)
    {
        current_red = east_red;
    }

    if (current_green > east_green)
    {
        current_green = east_green;
    }

    if (current_blue > east_blue)
    {
        current_blue = east_blue;
    }

    color = vec4(current_red, current_green, current_blue, 0.0f);
}
