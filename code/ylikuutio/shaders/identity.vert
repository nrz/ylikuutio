#version 120

// Input vertex data. These are different for all executions of this shader.
attribute vec3 vertex_position_modelspace;
attribute vec2 vertexUV;

// Output data. These will be interpolated for each fragment.
varying vec2 UV;

void main()
{
    // Output position of the vertex.
    gl_Position.xyz = vertex_position_modelspace;
    gl_Position.w = 1.0;

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}
