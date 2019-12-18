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
uniform vec3 uLightIntensity;


vec3 blinnPhong(vec3 position_vs, vec3 normal_vs){
    float d = distance(uLightPos_vs, vPosition_vs);
	vec3 w_zero = normalize(-position_vs);
	vec3 w_i = (normalize(uLightPos_vs - vPosition_vs));
	vec3 halfVector = (w_zero + w_i) / 2;

	//return uLightIntensity * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
	return (uLightIntensity / (d * d)) * ( uKd * ( dot(w_i, normal_vs ) ) + uKs * ( pow( dot(halfVector, normal_vs), uShininess ) ) );
}




// Ouput data
out vec3 fFragColor;

void main(){

    // Output color = color of the texture at the specified UV
    vec4 color = texture(uTextureSampler, vUV);

    fFragColor = color.rgb * blinnPhong(vPosition_vs, normalize(vNormal_vs));
}

