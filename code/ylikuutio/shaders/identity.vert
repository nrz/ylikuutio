#version 330 core

// Input vertex data. These are different for all executions of this shader.
attribute vec3 vertex_position_modelspace;
attribute vec2 vertex_uv;

// Output data. These will be interpolated for each fragment.
varying vec2 uv;

void main()
{
    // Output position of the vertex.
    gl_Position = vec4(vertex_position_modelspace.xy, 0, 1);

    // UV of the vertex. No special space for this one.
    uv = vertex_uv;
}
