#version 450 core
#define MAX_DIRECTIONAL_LIGHTS 5
#define MAX_POINT_LIGHTS 5
#define MAX_SPOT_LIGHTS 5


out vec4 FragColor;


in vec2 uv;
in vec3 norm;
in vec3 fragPos;

uniform vec3 viewPos;





struct dirLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


struct pointLight
{
	vec3 position;

	float constant;
	float linear; 
	float quadratic;


	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};

struct spotLight
{
	vec3 position;
	vec3 direction;

	float innerAngle;
	float outerAngle;

	float constant;
	float linear; 
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;


};

struct material 
{
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
	sampler2D emission;

	float shininess;
};

uniform material objMaterial;

uniform int directionalAmount, pointAmount, spotAmount; 

uniform pointLight pointLights[MAX_POINT_LIGHTS];
uniform dirLight   dirLights[MAX_DIRECTIONAL_LIGHTS];
uniform spotLight  spotLights[MAX_SPOT_LIGHTS];




vec3 calculateDirectionalLight(dirLight dirL, material objMat, vec3 n, vec3 viewPos);
vec3 calculatePointLight(pointLight p, material objMat, vec3 n, vec3 viewPos);
vec3 calculateSpotLight(spotLight sLight, material objMat, vec3 n, vec3 viewP);

vec3 calculateDiffuse(vec3 lightDirection, vec3 lightDiffuse, vec3 n);
vec3 calculateSpecular(vec3 lightDirection, vec3 lightSpecular, vec3 n, vec3 viewPosition, float shine);
void main()
{
	vec3 finalCol = vec3(0.0);
	vec3 dirCol = vec3(0.0), pCol = vec3(0.0), spotCol = vec3(0.0);
	for(int dirIndex = 0; dirIndex < directionalAmount; dirIndex++)
	{

		dirCol += calculateDirectionalLight(dirLights[dirIndex], objMaterial, norm, viewPos);
	}


	
	for(int pointIndex = 0; pointIndex < pointAmount; pointIndex++)
	{
		pCol += calculatePointLight(pointLights[pointIndex], objMaterial, norm, viewPos);
	}

	for(int spotIndex = 0; spotIndex < spotAmount; spotIndex++)
	{

		spotCol += calculateSpotLight(spotLights[spotIndex], objMaterial, norm, viewPos);
	}

	float far = 1000.0, near = 0.001;


	finalCol = dirCol + pCol + spotCol;

	
	FragColor = vec4(finalCol, 1.0);
}





vec3 calculateDirectionalLight(dirLight dirL, material objMat, vec3 n, vec3 viewPos)
{
	vec3 normal = normalize(n);
	vec3 lightDir = normalize(-dirL.direction);



	vec3 ambientCol, diffuseCol, specularCol;


	//calculate the diffuse color based on the light direction and the normal of the fragment;
	diffuseCol = calculateDiffuse(lightDir, dirL.diffuse, normal);

	specularCol = calculateSpecular(lightDir, dirL.specular, normal, viewPos, objMat.shininess);

	
	ambientCol = dirL.ambient * texture2D(objMat.texture_diffuse0, uv).rgb; 
	diffuseCol *= texture2D(objMat.texture_diffuse0, uv).rgb;
	specularCol *= texture2D(objMat.texture_specular0, uv).rgb;


	

	vec3 finalCol = vec3(ambientCol + diffuseCol + specularCol);

	return finalCol;
}



vec3 calculatePointLight(pointLight p, material objMat, vec3 n, vec3 viewPos)
{

	vec3 normal = normalize(n);
	vec3 lightDir = normalize(p.position - fragPos );

	float dist = length(p.position - fragPos);
	float attenuation = 1.0;
	attenuation /= ( p.constant + (p.linear * dist) + (p.quadratic * (dist*dist)));

	//attenuation = clamp(attenuation, 0.0, 1.0);



	vec3 ambientCol, diffuseCol, specularCol;

	ambientCol = p.ambient * texture2D(objMat.texture_diffuse0, uv).rgb; 


	//calculate the diffuse color based on the light direction and the normal of the fragment;
	diffuseCol = calculateDiffuse(lightDir, p.diffuse, normal);

	specularCol = calculateSpecular(lightDir, p.specular, normal, viewPos, objMat.shininess);

	diffuseCol *= texture2D(objMat.texture_diffuse0, uv).rgb;
	specularCol *= texture2D(objMat.texture_specular0, uv).rgb;


		
	ambientCol  *= attenuation;
	diffuseCol  *= attenuation;
	specularCol *= attenuation;


	return ambientCol + diffuseCol + specularCol;




}



vec3 calculateSpotLight(spotLight sLight, material objMat, vec3 n, vec3 viewP)
{

	float epsilon =  sLight.innerAngle - sLight.outerAngle;
	
	vec3 normal = normalize(n);
	vec3 lightDir = normalize(sLight.position - fragPos);

	float dist = length(sLight.position - fragPos);
	float attenuation = 1.0 / ( sLight.constant + sLight.linear * dist + sLight.quadratic * (dist*dist));
	//attenuation = clamp(attenuation, 0, 1);

	float theta = dot(lightDir, normalize(-sLight.direction));
	float intensity = (theta - sLight.outerAngle) / epsilon;

	intensity = clamp(intensity, 0.0, 1.0);

	vec3 ambientCol, diffuseCol , specularCol;

	

		
	diffuseCol = calculateDiffuse(lightDir, sLight.diffuse, normal);

	specularCol = calculateSpecular(lightDir, sLight.specular, normal, viewPos, objMat.shininess);

	ambientCol = sLight.ambient * texture2D(objMat.texture_diffuse0, uv).rgb; 
	diffuseCol *= texture2D(objMat.texture_diffuse0, uv).rgb;
	specularCol *= texture2D(objMat.texture_specular0, uv).rgb;

	ambientCol  *= intensity * attenuation;
	diffuseCol  *= intensity * attenuation;
	specularCol *= intensity * attenuation;




	return ambientCol + diffuseCol + specularCol;

}



vec3 calculateDiffuse(vec3 lightDirection, vec3 lightDiffuse,vec3 n)
{
	vec3 retCol = vec3(0.0);

	float d = dot(lightDirection, n);
	d = max(d, 0.0);

	retCol = d * lightDiffuse ;


	return retCol;
}
vec3 calculateSpecular(vec3 lightDirection, vec3 lightSpecular, vec3 n, vec3 viewPosition, float shine)
{
	vec3 retCol = vec3(0.0);
	vec3 reflected = normalize(reflect(-lightDirection, n));
	vec3 viewDirection = normalize(viewPosition - fragPos);

	float d = dot(reflected, viewDirection);
	d = max(d, 0.0);
	d = pow(d, shine);

	retCol = d * lightSpecular;

	return retCol;
}
