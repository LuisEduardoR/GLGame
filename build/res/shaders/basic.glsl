#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
out vec4 v_color;

void main()
{
   gl_Position = position;
   v_color = vec4( 0.5 + position.x,  0.5 - position.x, 0.0, 1.0);
}

#shader fragment
#version 410 core

in vec4 v_color;
layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
   color = v_color + u_Color;
}