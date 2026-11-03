#version 330

layout (location = 0) in vec4 in_Position;
layout (location = 1) in vec4 in_Color;
layout (location = 2) in vec2 texCoord;

out vec4 ex_Color;
out vec2 tex_Coord;

uniform mat4 myMatrix;
uniform mat4 myMatrix1;
uniform int transformation_order;

void main(void)
  {
    if (transformation_order == 0)
        gl_Position = myMatrix*in_Position;
    else
    {
        gl_Position = myMatrix1*in_Position;
    }

    ex_Color = in_Color;
    tex_Coord = vec2(texCoord.x, 1-texCoord.y);

   }
