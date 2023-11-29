#version 460 core

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct Light {
   vec3 position;
   vec3 color;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
//uniform vec3 lightColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

out vec4 FragColor;

void main()
{
//   float specularStrength = 0.5f;

   vec3 ambient = light.ambient * material.ambient;

   vec4 Mix = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);

   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(light.position - FragPos);

   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = light.diffuse * (diff * material.diffuse);

   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);

   float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
   vec3 specular = light.specular * spec * material.specular;

   vec3 result = light.color * (ambient + diffuse + specular);

   FragColor = vec4(result, 1.0f) * Mix;
}