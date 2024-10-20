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
    vec2 uv_northwest = uv + vec2(-1.0f / screen_width, 1.0f / screen_height);
    vec3 northwest = texture(texture_sampler, uv_northwest).rgb;
    vec2 uv_north = uv + vec2(0.0f, 1.0f / screen_height);
    vec3 north = texture(texture_sampler, uv_north).rgb;
    vec2 uv_northeast = uv + vec2(1.0f / screen_width, 1.0f / screen_height);
    vec3 northeast = texture(texture_sampler, uv_northeast).rgb;

    vec2 uv_southwest = uv + vec2(-1.0f / screen_width, -1.0f / screen_height);
    vec3 southwest = texture(texture_sampler, uv_southwest).rgb;
    vec2 uv_south = uv + vec2(0.0f, -1.0f / screen_height);
    vec3 south = texture(texture_sampler, uv_south).rgb;
    vec2 uv_southeast = uv + vec2(1.0f / screen_width, -1.0f / screen_height);
    vec3 southeast = texture(texture_sampler, uv_southeast).rgb;

    float red_value = -1.0f * northwest.r - 2.0f * north.r - 1.0f * northwest.r + 1.0f * southeast.r + 2.0f * south.r + 1.0f * southeast.r;
    float green_value = -1.0f * northwest.g - 2.0f * north.g - 1.0f * northwest.g + 1.0f * southeast.g + 2.0f * south.g + 1.0f * southeast.g;
    float blue_value = -1.0f * northwest.b - 2.0f * north.b - 1.0f * northwest.b + 1.0f * southeast.b + 2.0f * south.b + 1.0f * southeast.b;
    float gray_value = (red_value + green_value + blue_value) / 3.0f;
    color = vec4(gray_value, gray_value, gray_value, 0.0f);
}
