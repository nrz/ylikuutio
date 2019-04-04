#version 120

// Interpolated values from the vertex shaders
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D my_texture_sampler;

void main()
{
    gl_FragColor = texture2D(my_texture_sampler, UV);
}
