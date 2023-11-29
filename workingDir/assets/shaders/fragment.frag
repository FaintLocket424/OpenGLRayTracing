#version 460 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

out vec4 FragColor;

void main()
{
   float specularStrength = 0.5f;

   float ambientStrength = 0.1f;
   vec3 ambient = ambientStrength * lightColor;

   vec4 Mix = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);

   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);

   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = diff * lightColor;

   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, norm);

   float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
   vec3 specular = specularStrength * spec * lightColor;

   vec3 result = ambient + diffuse + specular;

   FragColor = vec4(result, 1.0f) * Mix;
}