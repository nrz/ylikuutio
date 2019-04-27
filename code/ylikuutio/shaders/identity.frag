#version 120

// Interpolated values from the vertex shaders.
varying vec2 UV;

// Values that stay constant for the whole mesh.
uniform sampler2D texture_sampler;

void main()
{
    // Texel color as is.
    gl_FragColor = texture2D(texture_sampler, UV);
}
