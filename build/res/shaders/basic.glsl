#shader vertex
#version 410 core

layout(location = 0) in vec4 position;
out vec4 colorV;

void main()
{
   gl_Position = position;
   colorV = vec4( 0.5 + position.x,  0.5 - position.x, 0.5 + position.y, 1.0);
}

#shader fragment
#version 410 core

in vec4 colorV;
out vec4 color;

void main()
{
   color = colorV;
}