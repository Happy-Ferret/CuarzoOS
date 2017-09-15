#define SHADER_DRAW_SURFACE 0
#define SHADER_DRAW_SHADOW 1
#define SHADER_DRAW_BLUR 2

#define BLUR_RECT 0
#define BLUR_HORIZONTAL 1
#define BLUR_VERTICAL 2

precision mediump float;
precision mediump int;

uniform int Mode;
uniform vec4 Color;
uniform bool OnlyColor;
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


float borderRadius()
{
    float x = TextureCoordsOut.x * Size.x;
    float y = TextureCoordsOut.y * Size.y;
    float solid = 32.0;

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
    if( OnlyColor )
        gl_FragColor =  Color * borderRadius();
    else
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
