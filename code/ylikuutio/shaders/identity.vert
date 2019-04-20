#version 120

// Input vertex data. These are different for all executions of this shader.
attribute vec3 vertex_position_modelspace;
attribute vec2 vertexUV;

// Output data. These will be interpolated for each fragment.
varying vec2 UV;

void main()
{
    // Output position of the vertex.
    gl_Position = vec4(vertex_position_modelspace.xy, 0, 1);

    // UV of the vertex. No special space for this one.
    UV = vertexUV;
}
