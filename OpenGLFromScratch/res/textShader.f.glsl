#version 330

in vec2 texcoord;
uniform sampler2D tex;
uniform vec4 color;

out FragColor;

void main(void) {
  FragColor = vec4(1, 1, 1, texture2D(tex, texcoord).r) * color;
}