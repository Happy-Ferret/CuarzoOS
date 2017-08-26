#define SHADER_DRAW_SURFACE 0
#define SHADER_DRAW_SHADOW 1
#define SHADER_DRAW_BLUR 2

#define BLUR_RECT 0
#define BLUR_HORIZONTAL 1
#define BLUR_VERTICAL 2

precision mediump float;
precision mediump int;

uniform int Mode;
uniform vec2 Screen;
uniform vec2 Size;
uniform vec2 Position;
uniform bvec4 Borders;
uniform float BorderRadius;
uniform int Opacity;
uniform float BlurWhite;
uniform float BlurLevel;
uniform int BlurStage;
uniform int BlurIteration;
uniform float ShadowSize;
uniform float ShadowIntensity;

varying highp vec2 blurTextureCoords[11];
varying vec2 TextureCoordsOut;

uniform sampler2D Texture;



/*
float borderRadiusOpacity(bool topLeft, bool topRight, bool bottomRight, bool bottomLeft)
{
    /*
    highp float  xPix = viewSize.x * texCoordsOut.x;
    highp float  yPix = texCoordsOut.y * viewSize.y;

    // Top Left
    if( xPix <= radius && yPix  <= radius )
    {
        if(topLeft)
            return 1.0 - pow(sqrt(pow(radius -xPix,2.0) + pow(radius - yPix, 2.0))/radius,radius);
    }
    // Top Right
    else if( xPix >= viewSize.x - radius && yPix <= radius )
    {
        if(topRight)
            return 1.0 - pow(sqrt(pow(radius -viewSize.x + xPix,2.0) + pow(radius - yPix, 2.0))/radius,radius);
    }
    // Bottom Right
    else if( xPix >= viewSize.x - radius && yPix  >= viewSize.y - radius )
    {
        if(bottomRight)
            return 1.0 - pow(sqrt(pow(radius - viewSize.x + xPix,2.0) + pow(radius - viewSize.y + yPix, 2.0))/radius,radius);
    }
    // Bottom Left
    else if( xPix <= radius && yPix  >= viewSize.y - radius )
    {
        if(bottomLeft)
            return 1.0 - pow(sqrt(pow(radius -xPix,2.0) + pow(radius - viewSize.y + yPix, 2.0))/radius,radius);
    }

    if( xPix <= radius)
        return 1.0 - pow((radius - xPix)/radius,radius);
    else if( yPix <= radius && (topLeft || topRight))
        return 1.0 - pow((radius - yPix)/radius,radius);
    else if( xPix >= viewSize.x - radius)
        return 1.0 - pow((radius - viewSize.x + xPix)/radius,radius);
    else if( yPix >= viewSize.y - radius && (bottomLeft || bottomRight))
        return 1.0 - pow((radius - viewSize.y + yPix)/radius,radius);
    else
        return 1.0;

}

void blur()
{

    vec4 sum = vec4(0.0);
    sum += texture2D(Texture, blurTextureCoords[0]) * 0.0093f;
    sum += texture2D(Texture, blurTextureCoords[1]) * 0.028002f;
    sum += texture2D(Texture, blurTextureCoords[2]) * 0.065984f;
    sum += texture2D(Texture, blurTextureCoords[3]) * 0.121703f;
    sum += texture2D(Texture, blurTextureCoords[4]) * 0.175713f;
    sum += texture2D(Texture, blurTextureCoords[5]) * 0.198596f;
    sum += texture2D(Texture, blurTextureCoords[6]) * 0.175713f;
    sum += texture2D(Texture, blurTextureCoords[7]) * 0.121703f;
    sum += texture2D(Texture, blurTextureCoords[8]) * 0.065984f;
    sum += texture2D(Texture, blurTextureCoords[9]) * 0.028002f;
    sum += texture2D(Texture, blurTextureCoords[10]) * 0.0093f;

    gl_FragColor = sum;

}

void clientView()
{
    vec4 color = finalColor;
    color.a = color.a * (float(viewOpacity) / 255.0);
    if(color.a > 1.0) color.a = 1.0;
    if(color.a < 0.0) color.a = 0.0;
    gl_FragColor =  texture2D(Texture,texCoordsOut)*color*vec4(1.0,1.0,1.0,borderRadiusOpacity(false,false,true,true));
}

void finalView()
{
    gl_FragColor = texture2D(Texture, texCoordsOut);
}

void blurRect()
{
    gl_FragColor = texture2D(Texture, texCoordsOut);
}

void finalBlur()
{
    vec4 px = texture2D(Texture,texCoordsOut);
    px = px*0.7 + vec4(0.35);
    px.a = 1.0;
    vec4 color = finalColor;
    color.a = color.a * (float(viewOpacity) / 255.0);
    gl_FragColor =  (px)*color*vec4(1.0,1.0,1.0,borderRadiusOpacity(false,false,true,true));
}

void background()
{
    gl_FragColor =  texture2D(Texture,texCoordsOut)*finalColor;
}

void titleBar()
{
    gl_FragColor =  texture2D(Texture,texCoordsOut)*vec4(1.0,1.0,1.0,borderRadiusOpacity(true,true,false,false));
}

void bottomShadow()
{

    float xPix =texCoordsOut.x*(viewSize.x + margin*2.0);
    float yPix =texCoordsOut.y*(viewSize.y + margin);

    // Left
    if(xPix <= margin && yPix < viewSize.y - radius)
        gl_FragColor = vec4(0.0,0.0,0.0,streight - sqrt( (margin - xPix)/(margin/streight)));

    // Right
    else if(xPix >= viewSize.x + margin && yPix < viewSize.y -radius )
        gl_FragColor = vec4(0.0,0.0,0.0, streight - sqrt((xPix - viewSize.x - margin)/(margin/streight)));

    // Bottom
    else if(yPix >= viewSize.y && xPix > margin + radius && xPix < viewSize.x + margin - radius)
        gl_FragColor = vec4(0.0,0.0,0.0, streight - sqrt((yPix- viewSize.y )/(margin/streight)));

    // Bottom Left
    else if(yPix >= viewSize.y - radius && xPix < margin + radius)
    {
        float distance = sqrt( pow((margin + radius) -  xPix, 2.0) + pow( (viewSize.y - radius) - yPix, 2.0) );
        if( distance <= radius)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else
            gl_FragColor = vec4(0.0,0.0,0.0, streight - sqrt((distance - radius)/(margin/streight)));
    }

    // Bottom Right
    else if(yPix >= viewSize.y - radius && xPix > viewSize.x + margin - radius)
    {
        float distance = sqrt( pow((viewSize.x + margin - radius) -  xPix, 2.0) + pow( (viewSize.y - radius) - yPix, 2.0) );
        if( distance <= radius)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else
            gl_FragColor = vec4(0.0,0.0,0.0, streight - sqrt((distance - radius)/(margin/streight)));
    }
    else
        gl_FragColor = vec4(0);

}

void topShadow()
{

    float xPix =texCoordsOut.x*(viewSize.x + margin*2.0);
    float yPix =texCoordsOut.y*(viewSize.y + margin);

    // Left
    if(xPix <= margin && yPix > margin + radius)
        gl_FragColor = vec4(0.0,0.0,0.0,streight - sqrt((margin - xPix)/(margin/streight)));

    // Right
    else if(xPix >= viewSize.x + margin && yPix > margin + radius )
        gl_FragColor = vec4(0.0,0.0,0.0, streight - sqrt((xPix - viewSize.x -margin)/(margin/streight)));

    // Top
    else if(yPix <= margin && xPix > margin + radius && xPix < viewSize.x + margin - radius)
        gl_FragColor = vec4(0.0,0.0,0.0, streight - sqrt((margin  - yPix)/(margin/streight)));

    // Top Left
    else if(yPix <= margin + radius && xPix < margin + radius)
    {
        float distance = sqrt( pow((margin + radius) -  xPix, 2.0) + pow( (margin + radius) - yPix, 2.0) );
        if( distance <= radius)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else
            gl_FragColor = vec4(0.0,0.0,0.0, streight - sqrt((distance - radius)/(margin/streight)));
    }

    // Top Right
    else if(yPix <= margin + radius && xPix > viewSize.x + margin - radius)
    {
        float distance = sqrt( pow((viewSize.x + margin - radius) -  xPix, 2.0) + pow( (margin + radius) - yPix, 2.0) );
        if( distance <= radius)
            gl_FragColor = vec4(0.0,0.0,0.0,0.0);
        else
            gl_FragColor = vec4(0.0,0.0,0.0, streight - sqrt((distance - radius)/(margin/streight)));
    }
    else
        gl_FragColor = vec4(0);

}
*/

float borderRadius()
{
    float x = TextureCoordsOut.x * Size.x;
    float y = TextureCoordsOut.y * Size.y;
    float solid = 50.0;

    if ( Borders[0] )
        if ( x <= BorderRadius && y  <= BorderRadius )
                return 1.0 - pow( sqrt( pow( BorderRadius -x, 2.0 ) + pow( BorderRadius - y, 2.0 ) ) / BorderRadius, solid );

    if ( Borders[1] )
        if ( x >= Size.x - BorderRadius && y <= BorderRadius )
             return 1.0 - pow( sqrt( pow( BorderRadius - Size.x + x, 2.0 ) + pow( BorderRadius - y, 2.0 ) ) / BorderRadius, solid);

    if ( Borders[2] )
        if ( x >= Size.x - BorderRadius && y  >= Size.y - BorderRadius )
            return 1.0 - pow( sqrt( pow( BorderRadius - Size.x + x, 2.0 ) + pow( BorderRadius - Size.y + y, 2.0 ) ) / BorderRadius , solid);

    if ( Borders[3] )
        if ( x <= BorderRadius && y  >= Size.y - BorderRadius )
            return 1.0 - pow( sqrt( pow( BorderRadius -x , 2.0 ) + pow( BorderRadius - Size.y + y, 2.0 ) ) / BorderRadius, solid);

    return 1.0;
}

void drawSurface()
{
    gl_FragColor =  texture2D(Texture,TextureCoordsOut) * borderRadius();
}

void drawShadow()
{
    float x = TextureCoordsOut.x * (Size.x + 2.0 * ShadowSize);
    float y = TextureCoordsOut.y * (Size.y + 2.0 * ShadowSize);
    float smoother = 0.5;
    gl_FragColor =  vec4( 0.0 );

    // Left
    if( x < ShadowSize && y > ShadowSize + BorderRadius && y < Size.y + ShadowSize - BorderRadius)
        gl_FragColor.a = ShadowIntensity - smoother * sqrt( ( ShadowSize - x ) / ( ShadowSize / ShadowIntensity ) );

    // Right
    if( x > Size.x + ShadowSize && y > ShadowSize + BorderRadius && y < Size.y + ShadowSize - BorderRadius)
        gl_FragColor.a = ShadowIntensity - smoother * sqrt( (ShadowSize - Size.x - ShadowSize*2.0 + x ) / ( ShadowSize / ShadowIntensity ) );

    // Top
    if( x > BorderRadius + ShadowSize && x < Size.x - BorderRadius + ShadowSize && y < ShadowSize)
        gl_FragColor.a = ShadowIntensity - smoother * sqrt( ( ShadowSize - y ) / ( ShadowSize / ShadowIntensity ) );

    // Bottom
    if( x > BorderRadius + ShadowSize && x < Size.x - BorderRadius + ShadowSize && y > Size.y + ShadowSize)
        gl_FragColor.a = ShadowIntensity - smoother * sqrt( ( ShadowSize - Size.y - ShadowSize * 2.0 + y ) / ( ShadowSize / ShadowIntensity ) );

    // Top Left
    if( x < ShadowSize + BorderRadius && y < ShadowSize + BorderRadius)
    {
        float distance = sqrt( pow( ( ShadowSize + BorderRadius) -  x, 2.0) + pow( ( ShadowSize + BorderRadius ) - y, 2.0) );
        if( distance > BorderRadius)
            gl_FragColor.a = ShadowIntensity - smoother * sqrt( ( distance - BorderRadius ) / ( ShadowSize / ShadowIntensity ) );
    }
    // Top Right
    if( x > Size.x + ShadowSize - BorderRadius && y < ShadowSize + BorderRadius)
    {
        float distance = sqrt( pow( x - ( Size.x + ShadowSize - BorderRadius ) , 2.0) + pow( ( ShadowSize + BorderRadius ) - y, 2.0) );
        if( distance > BorderRadius)
            gl_FragColor.a = ShadowIntensity - smoother * sqrt( ( distance - BorderRadius ) / ( ShadowSize / ShadowIntensity ) );
    }
    // Bottom Left
    if( x < ShadowSize + BorderRadius && y > Size.y + ShadowSize - BorderRadius)
    {
        float distance = sqrt( pow( ( ShadowSize + BorderRadius) -  x, 2.0) + pow( y - ( Size.y + ShadowSize - BorderRadius ) , 2.0) );
        if( distance > BorderRadius)
            gl_FragColor.a = ShadowIntensity - smoother * sqrt( ( distance - BorderRadius ) / ( ShadowSize / ShadowIntensity ) );
    }
    // Bottom Right
    if( x > Size.x + ShadowSize - BorderRadius && y > Size.y + ShadowSize - BorderRadius)
    {
        float distance = sqrt( pow( x - ( Size.x + ShadowSize - BorderRadius ) , 2.0) + pow( y - ( Size.y + ShadowSize - BorderRadius ) , 2.0) );
        if( distance > BorderRadius)
            gl_FragColor.a = ShadowIntensity - smoother * sqrt( ( distance - BorderRadius ) / ( ShadowSize / ShadowIntensity ) );
    }

}

void drawBlur()
{
    if( BlurStage == 0 )
    {
        gl_FragColor = texture2D( Texture, TextureCoordsOut) * ( 1.0 - BlurWhite) + vec4(BlurWhite);
    }
    if( BlurStage == 1 || BlurStage == 2)
    {
        vec4 sum = vec4(0.0);
        sum += texture2D(Texture, blurTextureCoords[0]) * 0.0093f;
        sum += texture2D(Texture, blurTextureCoords[1]) * 0.028002f;
        sum += texture2D(Texture, blurTextureCoords[2]) * 0.065984f;
        sum += texture2D(Texture, blurTextureCoords[3]) * 0.121703f;
        sum += texture2D(Texture, blurTextureCoords[4]) * 0.175713f;
        sum += texture2D(Texture, blurTextureCoords[5]) * 0.198596f;
        sum += texture2D(Texture, blurTextureCoords[6]) * 0.175713f;
        sum += texture2D(Texture, blurTextureCoords[7]) * 0.121703f;
        sum += texture2D(Texture, blurTextureCoords[8]) * 0.065984f;
        sum += texture2D(Texture, blurTextureCoords[9]) * 0.028002f;
        sum += texture2D(Texture, blurTextureCoords[10]) * 0.0093f;

        gl_FragColor = sum;
    }
}


void main(void)
{
    if(Mode == 0) drawSurface();
    if(Mode == 1) drawShadow();
    if(Mode == 2) drawBlur();
}
