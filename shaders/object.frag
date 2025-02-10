#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 u_lightPos; 
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform vec3 u_viewPos;

uniform float u_ambientStrength;
uniform float u_specularStrength;


void main()
{
    // ambient
 
    vec3 ambient = u_ambientStrength * u_lightColor;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;
  	// specular

    vec3 viewDir = normalize(u_viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = u_specularStrength * spec * u_lightColor;  
   
            
    vec3 result = (ambient + diffuse +specular) * u_objectColor;
    FragColor = vec4(result, 1.0);
} 