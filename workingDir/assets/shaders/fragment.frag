#version 460 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 lightColor;
uniform vec3 lightPos;

out vec4 FragColor;

void main()
{
   float ambientStrength = 0.1f;
   vec3 ambient = ambientStrength * lightColor;

   vec4 Mix = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2f);

   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);

   float diff = max(dot(norm, lightDir), 0.0f);
   vec3 diffuse = diff * lightColor;

   vec3 result = ambient + diffuse;

   FragColor = vec4(result, 1.0f) * Mix;
}