#define SHADER_DRAW_SURFACE 0
#define SHADER_DRAW_SHADOW 1
#define SHADER_DRAW_BLUR 2

#define BLUR_RECT 0
#define BLUR_HORIZONTAL 1
#define BLUR_VERTICAL 2

precision mediump float;
precision mediump int;

uniform int Mode;
uniform bool Inverted;
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

attribute vec4 VertexPosition;
attribute vec4 VertexColor;
attribute vec2 TextureCoords;

varying highp vec2 blurTextureCoords[11];
varying vec2 TextureCoordsOut;


vec4 calculateVertexPosition( float borderSize )
{
   vec4 finalPosition;

    if ( VertexPosition.x < 0.0 )
        finalPosition.x = ( 2.0 / Screen.x ) * ( Position.x - borderSize ) - 1.0;
    else
        finalPosition.x = ( 2.0 / Screen.x ) * ( Position.x + Size.x + borderSize ) - 1.0;

    if ( VertexPosition.y < 0.0 )
        finalPosition.y = 1.0 - ( 2.0 / Screen.y ) * ( Position.y - borderSize );
    else
        finalPosition.y = 1.0- ( 2.0 / Screen.y ) * ( Position.y + Size.y + borderSize );

    finalPosition.w = 1.0;
    finalPosition.z = -1.0;

    return finalPosition;
}

void drawSurface()
{
    gl_Position = calculateVertexPosition( 0.0 );
    TextureCoordsOut = TextureCoords;

    if(Inverted)
        if (VertexPosition.y > 0.0)
            TextureCoordsOut.y = 0.0;
        else
            TextureCoordsOut.y = 1.0;
}

void drawShadow()
{
    gl_Position = calculateVertexPosition( ShadowSize );
    TextureCoordsOut = TextureCoords;
}

void drawBlur()
{
    if ( BlurStage == 0)
    {
        if(TextureCoords.x == 0.0)
            TextureCoordsOut.x = Position.x / Screen.x;
        else
            TextureCoordsOut.x = ( Position.x + Size.x ) / Screen.x;

        if(TextureCoords.y == 1.0)
            TextureCoordsOut.y = 1.0 - Position.y / Screen.y;
        else
            TextureCoordsOut.y = 1.0 -( Position.y + Size.y ) / Screen.y;

    }
    if( BlurStage == 1)
    {
        // Calculates the vertex size
        float pixelSize = BlurLevel * float(BlurIteration) / Size.x;

        // Loop the 11 vertices
        for( int i = -5; i <= 5; i++ )
            blurTextureCoords[ i + 5 ] = TextureCoords+ vec2( pixelSize * float( i ) , 0.0 );
    }

    if( BlurStage == 2)
    {
        // Calculates the vertex size
        float pixelSize =  BlurLevel * float(BlurIteration) / Size.y;

        // Loop the 11 vertices
        for( int i = -5; i <= 5; i++ )
            blurTextureCoords[ i + 5 ] = TextureCoords + vec2( 0.0 ,pixelSize * float( i ) );

    }

    gl_Position= VertexPosition;

}

void main(void)
{
    if(Mode == 0) drawSurface();
    if(Mode == 1) drawShadow();
    if(Mode == 2) drawBlur();
}


