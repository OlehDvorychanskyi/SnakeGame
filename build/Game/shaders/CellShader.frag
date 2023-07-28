uniform vec2 snakeLightPosition;
uniform vec3 snakeLightColor;

uniform vec2 fruitLightPosition;
uniform vec3 fruitLightColor;

float GetBrightnessFactor(vec2 lightPosition, float lightRadius)
{
    float distanceToLight = distance(lightPosition, gl_FragCoord.xy);
    float brightnessFactor = clamp(1.0 - (distanceToLight / lightRadius), 0.0, 1.0);
    return brightnessFactor;
}

void main()
{
    float snakeBrightnessFactor = GetBrightnessFactor(snakeLightPosition, 175.f);
    float fruitBrightnessFactor = GetBrightnessFactor(fruitLightPosition, 150.f);   

    snakeLightColor *= 0.001;
    fruitLightColor *= 0.001;

    vec3 cellColor = vec3(0.098, 0.098, 0.098);

    vec3 snakeFinalColor = snakeLightColor * snakeBrightnessFactor;
    vec3 fruitFinalColor = fruitLightColor * fruitBrightnessFactor;

    vec3 finalColor = cellColor + snakeFinalColor + fruitFinalColor;

    gl_FragColor = vec4(finalColor.xyz , 1.0);
}