#version 330 core

// Input vertex data, different for all executions of this shader.
attribute vec2 vertex_position_screenspace;
attribute vec2 vertex_uv;

uniform int screen_width;
uniform int screen_height;

// Output data ; will be interpolated for each fragment.
varying vec2 UV;

void main()
{
    // Output position of the vertex, in clip space
    // map [0..800][0..600] to [-1..1][-1..1]

    vec2 vertex_position_homogenousspace = vertex_position_screenspace - vec2(screen_width / 2, screen_height / 2); // [0..800][0..600] -> [-400..400][-300..300]

    vertex_position_homogenousspace /= vec2(screen_width / 2, screen_height / 2);

    gl_Position = vec4(vertex_position_homogenousspace, 0, 1);

    // UV of the vertex. No special space for this one.
    UV = vertex_uv;
}
