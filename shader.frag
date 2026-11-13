#version 330

in vec4 ex_Color;
in vec2 tex_Coord;

out vec4 out_Color;

uniform sampler2D myTexture;
uniform vec4 tint;

void main(void)
{
      out_Color = texture(myTexture, tex_Coord) * tint;
}
