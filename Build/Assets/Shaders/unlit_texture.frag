#version 430

//in layout(location = 0) vec3 color;
in layout(location = 1) vec2 texcoord;

out layout(location = 0) vec4 ocolor;

layout(binding = 0) uniform sampler2D tex;

uniform vec4 color;
uniform vec2 offset;
uniform vec2 tiling;

//uniform float time;

void main()
{
	//vec3 xo = color * ((sin(time * 5 ) + 1) * 0.5) * 3;

	//ocolor = vec4(xo, 1);

	vec4 texcolor = texture(tex, (texcoord * tiling) + offset);
	//if (texcolor.a < 0.8) discard;
	ocolor = texcolor * color;
}
