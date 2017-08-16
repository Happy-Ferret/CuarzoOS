#define SHADER_NORMAL 0
#define SHADER_BACKGROUND 1
#define SHADER_HBLUR 2
#define SHADER_VBLUR 3
#define SHADER_FINAL 4
#define SHADER_BLUR_RECT 5
#define SHADER_DRAW_BLUR 6


attribute vec4 pos;
attribute vec4 col;
attribute highp vec2 texCoordsIn;

varying vec4 finalColor;
varying highp vec2 texCoordsOut;

uniform vec2 screenSize;
uniform vec2 viewSize;
uniform vec2 viewOffset;
uniform lowp int Mode;
uniform bool inverted;
uniform float blurRadius;

uniform highp vec2 textureSize;

varying highp vec2 blurTextureCoords[11];

void calcBlurRect()
{
    texCoordsOut.x = texCoordsIn.x/screenSize.x;
    texCoordsOut.y =  texCoordsIn.y/screenSize.y;
    gl_Position = pos;
}

void calcSurfacePosition()
{
    gl_Position.x = (2.0f/screenSize.x)*(viewOffset.x + pos.x) - 1.0f;
    gl_Position.y = 1.0f - (2.0f/screenSize.y)*(viewOffset.y + pos.y);
    gl_Position.z = pos.z;
    gl_Position.w = 1.0f;
}

void horizontalBlur()
{
    // Calculates the vertex size
    float pixelSize = blurRadius / viewSize.x;

    // Loop the 11 vertices
    for( int i = -5; i <= 5; i++ )
    {
        // Calculates the x offset
        blurTextureCoords[ i + 5 ] = texCoordsIn + vec2( pixelSize * float( i ) , 0.0 );
    }

    // Sends vertex position
    gl_Position= pos;
}

void verticalBlur()
{
    // Calculates the vertex size
    float pixelSize = blurRadius / viewSize.y;

    // Loop the 11 vertices
    for( int i = -5; i <= 5; i++ )
    {
        // Calculates the y offset
        blurTextureCoords[ i + 5 ] = texCoordsIn + vec2( 0.0, pixelSize * float( i ) ) ;
    }

    // Sends vertex position
    gl_Position= pos;
}

void drawBlur()
{
    calcSurfacePosition();

    // Set Texture Vertex Position
    texCoordsOut.x = ( pos.x + 80.0 ) / (viewSize.x + 240.0) ;
    texCoordsOut.y = ( pos.y + 80.0 ) / (viewSize.y + 240.0) ;
}

void drawSurface()
{
    calcSurfacePosition();

     // Set Texture Vertex Position
     texCoordsOut.x = (pos.x)/viewSize.x;
     texCoordsOut.y = (pos.y)/viewSize.y;
}

void drawBackground()
{
    texCoordsOut = texCoordsIn;
    if(inverted)
    {
        texCoordsOut.y = 1.0f - texCoordsIn.y;
    }

    gl_Position = pos;
}

void drawScreen()
{
    texCoordsOut = texCoordsIn;
    gl_Position = pos;
}

void main(void)
{
    // Set vertex color
    finalColor = col;

    // Draws surface
    if(Mode == 0) drawSurface();

    // Draws background
    if(Mode == 1) drawBackground();

    // Calc horizontal blur
    if(Mode == 2) horizontalBlur();

    // Calc vertical blur
    if(Mode == 3) verticalBlur();

    // Draws finall view to screen
    if(Mode == 4) drawScreen();

    // Calc blurRect
    if(Mode == 5) calcBlurRect();

    // Draws blur
    if(Mode == 6) drawBlur();

}


