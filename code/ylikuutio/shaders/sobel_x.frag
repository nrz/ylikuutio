#version 330 core

// Interpolated values from the vertex shaders.
varying vec2 uv;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sampler;

uniform int screen_width;
uniform int screen_height;

out vec4 color;

void main()
{
    vec2 UV_northwest = uv + vec2(-1.0f / screen_width, 1.0f / screen_height);
    vec3 northwest = texture(texture_sampler, UV_northwest).rgb;
    vec2 UV_west = uv + vec2(-1.0f / screen_width, 0.0f);
    vec3 west = texture(texture_sampler, UV_west).rgb;
    vec2 UV_southwest = uv + vec2(-1.0f / screen_width, -1.0f / screen_height);
    vec3 southwest = texture(texture_sampler, UV_southwest).rgb;

    vec2 UV_northeast = uv + vec2(1.0f / screen_width, 1.0f / screen_height);
    vec3 northeast = texture(texture_sampler, UV_northeast).rgb;
    vec2 UV_east = uv + vec2(1.0f / screen_width, 0.0f);
    vec3 east = texture(texture_sampler, UV_east).rgb;
    vec2 UV_southeast = uv + vec2(1.0f / screen_width, -1.0f / screen_height);
    vec3 southeast = texture(texture_sampler, UV_southeast).rgb;

    float red_value = -1.0f * northwest.r - 2.0f * west.r - 1.0f * southwest.r + 1.0f * northeast.r + 2.0f * east.r + 1.0f * southeast.r;
    float green_value = -1.0f * northwest.g - 2.0f * west.g - 1.0f * southwest.g + 1.0f * northeast.g + 2.0f * east.g + 1.0f * southeast.g;
    float blue_value = -1.0f * northwest.b - 2.0f * west.b - 1.0f * southwest.b + 1.0f * northeast.b + 2.0f * east.b + 1.0f * southeast.b;
    float gray_value = (red_value + green_value + blue_value) / 3.0f;
    color = vec4(gray_value, gray_value, gray_value, 0.0f);
}
