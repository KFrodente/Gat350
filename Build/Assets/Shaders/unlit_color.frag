#version 430

in layout(location = 0) vec3 color;

out layout(location = 0) vec4 ocolor;

uniform float time;

void main()
{
	//vec3 xo = color * ((sin(time * 5 ) + 1) * 0.5) * 3;

	//ocolor = vec4(xo, 1);
	ocolor = vec4(color, 1);
}
