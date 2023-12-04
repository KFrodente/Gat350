#version 430

in layout(location = 0) vec3 vposition;
in layout(location = 2) vec3 vnormal;

out layout(location = 0) vec3 otexcoord;

uniform float ior = 1.501;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	// TRANSFORM VERTEC POSITION/NORMAL TO WORLD SPACE
	vec3 position = vec3(model * vec4(vposition, 1));
	vec3 normal = normalize(mat3(model) * vnormal);

	// INVERSE OF VIEW SPACE => WORLD SPACE
	// LAST COLUMN OF MAT4 IS POSITION
	vec3 viewPosition = inverse(view)[3].xyz;
	vec3 viewDir = normalize(position - viewPosition);


	// REFRACT VIEW DIRECTION ABOUT VERTEX NORMAL USING INDEX OF REFRACTION
	otexcoord = refract(viewDir, normal, 1 / ior);

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
