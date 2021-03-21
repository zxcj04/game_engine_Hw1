#version 460 compatibility
out vec3 N; //normal vector
out vec3 L0; //light direction vector
// out vec3 L1; //light direction vector
// out vec3 L2; //light direction vector
out vec3 E; //V vector for specular.

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    vec4 eyePosition = gl_ModelViewMatrix*gl_Vertex;
    vec4 eyeLightPos0 = gl_ModelViewMatrix*gl_LightSource[0].position;
    N =  normalize(gl_NormalMatrix*gl_Normal);
    L0 = eyeLightPos0.xyz - eyePosition.xyz ;
    E = -eyePosition.xyz;
}