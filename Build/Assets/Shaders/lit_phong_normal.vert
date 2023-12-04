 #version 430

in layout(location = 0) vec3 vposition;
in layout(location = 1) vec2 vtexcoord;
in layout(location = 2) vec3 vnormal;
in layout(location = 3) vec3 vtangent;

out layout(location = 0) vec3 oposition;
out layout(location = 1) vec2 otexcoord;
out layout(location = 2) mat3 otbn;
out layout(location = 5) vec4 oshadowcoord;
//OSHADOWCOORD ADDED


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 shadowVP;
//SHADOWVP ADDED

uniform struct Material
{
	uint params;

	vec3 albedo;
	vec3 specular;
	vec3 emissive;
	float shininess;

	vec2 offset;
	vec2 tiling;


} material;



//uniform vec3 ambientLight = vec3(0.5, 0.5, 0.5);

void main()
{
	otexcoord = (vtexcoord * material.tiling) + material.offset;
	mat4 modelView = view * model;

	//CONVERT POSITION AND NORMAL TO WORLD-VIEW SPACE
	oposition = vec3(modelView * vec4(vposition, 1));

	//CALCULATE TBN MATRIX
	vec3 normal = normalize(mat3(modelView) * vnormal);
	vec3 tangent = normalize(mat3(modelView) * vtangent);
	vec3 bitangent = cross(normal, tangent);

	otbn = mat3(tangent, bitangent, normal);

	//SETS SHADOW COORDS
	oshadowcoord = shadowVP * model * vec4(vposition, 1);

	mat4 mvp = projection * view * model;
	gl_Position = mvp * vec4(vposition, 1.0);
}
