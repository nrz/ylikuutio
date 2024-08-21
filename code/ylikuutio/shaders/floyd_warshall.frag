#version 330 core

// Interpolated values from the vertex shaders.
varying vec2 uv;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sampler;

uniform int screen_width;
uniform int screen_height;

uniform int iteration_i; // k is an index, needs to be adjusted for distance matrix size in this shader.

out float distance;

void main()
{
    // All texture coordinates are in the range [0, 1].
    // Therefore, the type of all texture coordinates must be `float`.
    // `uv.x` is `i`.
    // `uv.y` is `j`.
    // `iteration_i` divided by
    float i = uv.x;
    float j = uv.y;
    float k = float(iteration_i) / float(screen_width);

    vec2 UV_i_j = vec2(i, j);
    vec2 UV_i_k = vec2(i, k);
    vec2 UV_k_j = vec2(k, j);

    float dist_i_j = texture(texture_sampler, UV_i_j).r;
    float dist_i_k = texture(texture_sampler, UV_i_k).r;
    float dist_k_j = texture(texture_sampler, UV_k_j).r;

    if (dist_i_j > dist_i_k + dist_k_j)
    {
        dist_i_j = dist_i_k + dist_k_j;
    }

    // distance is the distance value computed by this shader.
    distance = dist_i_j;
}
