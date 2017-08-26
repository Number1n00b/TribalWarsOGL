#version 330

//Both GPU and CPU has access to a 'uniform' variable, so it can change at runtime.
uniform sampler2D diffuse;

//Shared with the vertex shader
in vec2 texCoord0;
in vec3 normal0;

in vec4 relativePos;

out vec4 FragColor;

void main(){
    //@Hardcoded: Should import this with a uniform.
    vec3 lightDirection = vec3(0, 0, 1);

    float d = 0.8;
    float d2 = 1;

    //FragColor = vec4(relativePos.x * d2, (relativePos.y-1.7) * d2, relativePos.z * d2, 1.0);
    FragColor = vec4((relativePos.x) * d, (relativePos.y - 1.6) * d, (relativePos.z) * d, 1.0);

    //FragColor = texture2D(diffuse, texCoord0)
    //    * clamp(dot(-lightDirection, normal0), 0.0, 1.0);
}
