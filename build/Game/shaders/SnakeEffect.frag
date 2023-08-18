uniform float u_time;
uniform vec2 rectSize;
uniform vec2 rectPosition;

float mapRange(float x, float minIn, float maxIn, float minOut, float maxOut)
{
    float normalizedValue = (x - minIn) / (maxIn - minIn);
    return minOut + normalizedValue * (maxOut - minOut);
}

void getLightPosition(float proportion, float currentTime, out vec2 firstLightPosition, out vec2 secondLightPosition)
{   
    float pixelX = gl_FragCoord.x;
    float pixelY = gl_FragCoord.y;
    float rectX = rectPosition.x;
    float rectY = rectPosition.y;
    float width = rectSize.x;
    float height = rectSize.y;

    vec2 leftUpperPoint = vec2(rectX, rectY);
    vec2 rightUpperPoint = vec2(rectX + width, rectY);
    vec2 leftLowerPoint = vec2(rectX, rectY - height);
    vec2 rightLowerPoint = vec2(rectX + width, rectY - height);

    float firstLightValue = abs(sin(currentTime)); 
    vec2 lightPosition;
    vec2 lightPosition2;

    float firstLightAverageValue = 1.0 - (1.0 / (proportion + 1.0));
    if (firstLightValue < firstLightAverageValue)
    {
        // Need to move point from leftUpper to rightUpper
        float newValue = mapRange(firstLightValue, 0.0, firstLightAverageValue, leftUpperPoint.x, rightUpperPoint.x);
        firstLightPosition = vec2(newValue, leftUpperPoint.y);
    }
    else if (firstLightValue < 1.0)
    {   
        // Need to move point from rightUpper to rightLower
        float newValue = mapRange(firstLightValue, firstLightAverageValue, 1.0, rightUpperPoint.y, rightLowerPoint.y);
        firstLightPosition = vec2(rightLowerPoint.x, newValue);
    }

    float secondLightValue = -(abs(sin(currentTime)));
    float secondLightAverageValue = -1.0 + (1.0 / (proportion + 1.0));
    if (secondLightValue > secondLightAverageValue)
    {
        // Need to move point from rightLower to leftLower
        float newValue = mapRange(secondLightValue, secondLightAverageValue , 0.0, leftLowerPoint.x, rightLowerPoint.x);
        secondLightPosition = vec2(newValue, leftLowerPoint.y);
    }
    else if (secondLightValue > -1.0 )
    {
        // Need to move point from leftLower to leftUpper
        float newValue = mapRange(secondLightValue, -1.0, secondLightAverageValue, leftUpperPoint.y, leftLowerPoint.y);
        secondLightPosition = vec2(leftLowerPoint.x, newValue);
    }
}

float getProportion(float width, float height)
{
    float proportion;
    if (width > height)
        proportion = width / height;
    else 
        proportion = height / width;
    return proportion;
}

void main()
{
    float u_speed = 0.65;
    float currentTime = u_time * u_speed;

    float pixelX = gl_FragCoord.x;
    float pixelY = gl_FragCoord.y;

    float rectX = rectPosition.x;
    float rectY = rectPosition.y;

    float width = rectSize.x;
    float height = rectSize.y;

    vec2 firstLightPosition;
    vec2 secondLightPosition;

    float proportion = getProportion(width, height);

    getLightPosition(proportion, currentTime, firstLightPosition, secondLightPosition);

    vec2 pixelPoint = vec2(pixelX, pixelY);  

    float toFirstLightPoint = distance(firstLightPosition, pixelPoint);
    float toSecondLightPoint = distance(secondLightPosition, pixelPoint);

    float maxDistance = sqrt(pow(width, 2.0) + pow(height, 2.0));

    float radius = 50.0;
    float normalizedDistanceToFirstLightPoint = clamp(1.0 - (toFirstLightPoint / radius), 0.0, 1.0);
    float normalizedDistanceToSecondLightPoint = clamp(1.0 - (toSecondLightPoint / radius), 0.0, 1.0);

    vec3 firstLightColor = vec3(1.0, 1.0, 0.0);
    vec3 secondLightColor = vec3(0.0, 1.0, 0.0);
    vec3 cellColor = vec3(0.098, 0.098, 0.098);
    // vec3 cellColor = vec3(0.0, 0.0, 0.0);
    float transperent;
    vec3 color;
    float border = 2.0;
    if (pixelY < (rectY - border) && pixelY > (rectY - height + border) && pixelX > (rectX + border) && pixelX < (rectX + width - border))
    {
        color = cellColor;
        transperent = 0.3;
    }
    else 
    {
        color = (firstLightColor * normalizedDistanceToFirstLightPoint) + (secondLightColor * normalizedDistanceToSecondLightPoint);
        transperent = 1.0;
    }
    gl_FragColor = vec4(color.x, color.y, color.z, transperent);
}