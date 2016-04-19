#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float     shininess;
};  

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
out vec4 color;
  
uniform int tex;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	if (tex == 1) {
		// Ambient
		vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	
		// Diffuse 
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(light.position - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
    
		// Specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 reflectDir = reflect(-lightDir, norm);  
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
		vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
        
		color = vec4(ambient + diffuse + specular, 1.0f); 
	}
	else {
			vec3 lightPos = vec3(1.2f, 1.0f, 2.0f); 
			vec3 viewPos = vec3(0.0f, 0.0f, 3.0f); 
			vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
			vec3 objectColor = vec3(0.5f, 0.5f, 0.5f);

		    float ambientStrength = 0.1f;
			vec3 ambient = ambientStrength * lightColor;
  	
			// Diffuse 
			vec3 norm = normalize(Normal);
			vec3 lightDir = normalize(lightPos - FragPos);
			float diff = max(dot(norm, lightDir), 0.0);
			vec3 diffuse = diff * lightColor;
    
			// Specular
			float specularStrength = 0.5f;
			vec3 viewDir = normalize(viewPos - FragPos);
			vec3 reflectDir = reflect(-lightDir, norm);  
			float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
			vec3 specular = specularStrength * spec * lightColor;  
        
			vec3 result = (ambient + diffuse + specular) * objectColor;
			color = vec4(result, 1.0f);
	}
} 