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

    vec2 uv_west = uv + vec2(-1.0f / screen_width, 0.0f);
    vec3 west = texture(texture_sampler, uv_west).rgb;
    vec2 uv_east = uv + vec2(1.0f / screen_width, 0.0f);
    vec3 east = texture(texture_sampler, uv_east).rgb;

    vec2 uv_southwest = uv + vec2(-1.0f / screen_width, -1.0f / screen_height);
    vec3 southwest = texture(texture_sampler, uv_southwest).rgb;
    vec2 uv_south = uv + vec2(0.0f, -1.0f / screen_height);
    vec3 south = texture(texture_sampler, uv_south).rgb;
    vec2 uv_southeast = uv + vec2(1.0f / screen_width, -1.0f / screen_height);
    vec3 southeast = texture(texture_sampler, uv_southeast).rgb;

    float x_red_value = -1.0f * northwest.r - 2.0f * west.r - 1.0f * southwest.r + 1.0f * northeast.r + 2.0f * east.r + 1.0f * southeast.r;
    float x_green_value = -1.0f * northwest.g - 2.0f * west.g - 1.0f * southwest.g + 1.0f * northeast.g + 2.0f * east.g + 1.0f * southeast.g;
    float x_blue_value = -1.0f * northwest.b - 2.0f * west.b - 1.0f * southwest.b + 1.0f * northeast.b + 2.0f * east.b + 1.0f * southeast.b;
    float x_gray_value = (x_red_value + x_green_value + x_blue_value) / 3.0f;

    float y_red_value = -1.0f * northwest.r - 2.0f * north.r - 1.0f * northwest.r + 1.0f * southeast.r + 2.0f * south.r + 1.0f * southeast.r;
    float y_green_value = -1.0f * northwest.g - 2.0f * north.g - 1.0f * northwest.g + 1.0f * southeast.g + 2.0f * south.g + 1.0f * southeast.g;
    float y_blue_value = -1.0f * northwest.b - 2.0f * north.b - 1.0f * northwest.b + 1.0f * southeast.b + 2.0f * south.b + 1.0f * southeast.b;
    float y_gray_value = (y_red_value + y_green_value + y_blue_value) / 3.0f;

    float gradient_magnitude = sqrt(x_gray_value * x_gray_value + y_gray_value * y_gray_value);

    color = vec4(gradient_magnitude, gradient_magnitude, gradient_magnitude, 0.0f);
}
