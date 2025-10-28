#version 450 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 uColor;
uniform float uOpacity;
uniform vec3 uLightPos;
uniform vec3 uViewPos;
uniform vec3 uHiddenDimTint;

void main()
{
    // Ambient lighting
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * vec3(1.0);
    
    // Diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(uLightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0);
    
    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(uViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0);
    
    // Combine lighting with color and hidden dimension tint
    vec3 result = (ambient + diffuse + specular) * uColor * uHiddenDimTint;
    
    FragColor = vec4(result, uOpacity);
}
