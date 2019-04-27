#version 120

// Interpolated values from the vertex shaders.
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sampler;

uniform int screen_width;
uniform int screen_height;

void main()
{
    vec2 UV_northwest = UV + vec2(-1.0f / screen_width, 1.0f / screen_height);
    vec3 northwest = texture2D(texture_sampler, UV_northwest).rgb;
    vec2 UV_north = UV + vec2(0.0f, 1.0f / screen_height);
    vec3 north = texture2D(texture_sampler, UV_north).rgb;
    vec2 UV_northeast = UV + vec2(1.0f / screen_width, 1.0f / screen_height);
    vec3 northeast = texture2D(texture_sampler, UV_northeast).rgb;

    vec2 UV_southwest = UV + vec2(-1.0f / screen_width, -1.0f / screen_height);
    vec3 southwest = texture2D(texture_sampler, UV_southwest).rgb;
    vec2 UV_south = UV + vec2(0.0f, -1.0f / screen_height);
    vec3 south = texture2D(texture_sampler, UV_south).rgb;
    vec2 UV_southeast = UV + vec2(1.0f / screen_width, -1.0f / screen_height);
    vec3 southeast = texture2D(texture_sampler, UV_southeast).rgb;

    float red_value = -1.0f * northwest.r - 2.0f * north.r - 1.0f * northwest.r + 1.0f * southeast.r + 2.0f * south.r + 1.0f * southeast.r;
    float green_value = -1.0f * northwest.g - 2.0f * north.g - 1.0f * northwest.g + 1.0f * southeast.g + 2.0f * south.g + 1.0f * southeast.g;
    float blue_value = -1.0f * northwest.b - 2.0f * north.b - 1.0f * northwest.b + 1.0f * southeast.b + 2.0f * south.b + 1.0f * southeast.b;
    float gray_value = (red_value + green_value + blue_value) / 3.0f;
    gl_FragColor = vec4(gray_value, gray_value, gray_value, 0.0f);
}
