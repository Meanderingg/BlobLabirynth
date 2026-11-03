#version 330

in vec4 ex_Color;
in vec2 tex_Coord;

out vec4 out_Color;

uniform sampler2D myTexture;
uniform int transformation_order;

vec4 red = vec4(1.0,0.0,0.0,1.0);
vec4 green= vec4(0.0,1.0,0.0,1.0);

void main(void)
  {

        out_Color=ex_Color;

        out_Color = mix(texture(myTexture, tex_Coord), ex_Color, 0.0);

  }
