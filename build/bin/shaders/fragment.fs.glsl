#version 330 core

// Interpolated values from the vertex shaders
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vUV;


// Values that stay constant for the whole mesh.
uniform sampler2D uTextureSampler;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensityP;
uniform vec3 uLightIntensityD;

vec3 blinnPhongP(vec3 position_vs, vec3 normal_vs){
    float d = distance(uLightPos_vs, position_vs);
	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = (normalize(uLightPos_vs - position_vs));
	vec3 halfVector = (w_zero + w_i) / 2;

	return (uLightIntensityP / (d * d)) * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}


vec3 blinnPhongD(vec3 position_vs, vec3 normal_vs){

	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = normalize(-uLightDir_vs);
	vec3 halfVector = (w_zero + w_i) / 2;

	return uLightIntensityD * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}



// Ouput data
out vec3 fFragColor;

void main(){

    // Output color = color of the texture at the specified UV
    vec4 color = texture(uTextureSampler, vUV);
	//fFragColor = ( blinnPhongD(vPosition_vs, normalize(vNormal_vs)) * blinnPhongP(vPosition_vs, normalize(vNormal_vs)) );
	//fFragColor = vec4(result, 1.0);

	

    //fFragColor += color.rgb * (blinnPhongP(vPosition_vs, normalize(vNormal_vs)));
	fFragColor = color.rgb * (blinnPhongP(vPosition_vs, normalize(vNormal_vs)) + blinnPhongD(vPosition_vs, normalize(vNormal_vs)));
    //fFragColor += color.rgb * blinnPhongD(vPosition_vs, normalize(vNormal_vs));
}

