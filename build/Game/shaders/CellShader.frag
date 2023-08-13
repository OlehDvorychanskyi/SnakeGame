uniform vec2 snakeLightPosition;
uniform vec3 snakeLightColor;

uniform vec2 fruitLightPositions[5];
uniform vec3 fruitLightColors[5];

uniform vec2 cellSize;

float GetBrightnessFactor(vec2 lightPosition, float lightRadius)
{
    float distanceToLight = distance(lightPosition, gl_FragCoord.xy);
    float brightnessFactor = clamp(1.0 - (distanceToLight / lightRadius), 0.0, 1.0);
    return brightnessFactor;
}

void main()
{
    float lightRadius = cellSize.x * 2.0;

    float snakeBrightnessFactor = GetBrightnessFactor(snakeLightPosition, lightRadius * 1.3);
    vec3 currentSnakeLightColor = snakeLightColor * 0.001;
    vec3 snakeFinalColor = currentSnakeLightColor * snakeBrightnessFactor;

    vec3 cellColor = vec3(0.060, 0.060, 0.060);
    vec3 finalColor = cellColor + snakeFinalColor;

    float fruitBrightnessFactors[5];
    vec3 fruitFinalColors[5];

    vec3 fruitFinalColor;
    for (int i = 0; i < 5; i++)
    {
        fruitBrightnessFactors[i] = GetBrightnessFactor(fruitLightPositions[i], lightRadius);
        fruitFinalColors[i] = fruitLightColors[i] * 0.001 * fruitBrightnessFactors[i];
        fruitFinalColor += fruitFinalColors[i];
    }
    finalColor += fruitFinalColor;

    gl_FragColor = vec4(finalColor.xyz , 1.0);
}