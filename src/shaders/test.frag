#version 460 compatibility
in vec3 N;
in vec3 L0;
// in vec3 L1;
// in vec3 L2;
in vec3 E;

uniform bvec3 light_enable;

void main()
{
    vec3 Normal = normalize(N);
    vec3 Light0 = normalize(L0);
    // vec3 Light1 = normalize(L1);
    // vec3 Light2 = normalize(L2);
    vec3 Eye = normalize(E);
    vec3 Half0 = normalize(Eye+Light0);
    // vec3 Half1 = normalize(Eye+Light1);
    // vec3 Half2 = normalize(Eye+Light2);

    float Kd0 = max(dot(Normal, Light0), 0.0);
    float Ks0 = pow(max(dot(Half0, Normal), 0.0), gl_FrontMaterial.shininess);
    if(Kd0==0.0) Ks0 = 0.0;
    if(!light_enable[0]) Kd0 = Ks0 = 0.0;

    // float Kd1 = max(dot(Normal, Light1), 0.0);
    // float Ks1 = pow(max(dot(Half1, Normal), 0.0), gl_FrontMaterial.shininess);
    // if(Kd1==0.0) Ks1 = 0.0;
    // if(!light_enable[1]) Kd1 = Ks1 = 0;

    // float Kd2 = max(dot(Normal, Light2), 0.0);
    // float Ks2 = pow(max(dot(Half2, Normal), 0.0), gl_FrontMaterial.shininess);
    // if(Kd2==0.0) Ks2 = 0.0;
    // if(!light_enable[2]) Kd2 = Ks2 = 0;

    // vec4 diffuse = (Kd0*gl_LightSource[0].diffuse + Kd1*gl_LightSource[1].diffuse + Kd2*gl_LightSource[2].diffuse)*gl_FrontMaterial.diffuse;
    // vec4 specular = (Ks0*gl_LightSource[0].specular + Ks1*gl_LightSource[1].specular + Ks2*gl_LightSource[2].specular)*gl_FrontMaterial.specular;
    // vec4 ambient = (gl_LightSource[0].ambient + gl_LightSource[1].ambient + gl_LightSource[2].ambient)*gl_FrontMaterial.ambient;

    vec4 diffuse = (Kd0*gl_LightSource[0].diffuse)*gl_FrontMaterial.diffuse;
    vec4 specular = (Ks0*gl_LightSource[0].specular)*gl_FrontMaterial.specular;
    vec4 ambient = (gl_LightSource[0].ambient)*gl_FrontMaterial.ambient;

    gl_FragColor = ambient + diffuse + specular ;
}
