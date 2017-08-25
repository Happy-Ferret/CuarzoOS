#define SHADER_DRAW_SURFACE 0
#define SHADER_DRAW_BACKGROUND 1
#define SHADER_DRAW_SHADOW 2
#define SHADER_DRAW_BLUR 3

#define BLUR_RECT 0
#define BLUR_HORIZONTAL 1
#define BLUR_VERTICAL 2

// Get GLSL Uniforms Locations

uniform int Mode;
uniform ivec2 Screen;
uniform ivec2 Size;
uniform ivec2 Position;
uniform bvec4 Borders;
uniform float BorderRadius;
uniform int Opacity;
uniform float BlurWhite;
uniform float BlurLevel;
uniform int BlurStage;
uniform int BlurIteration;
uniform int ShadowSize;
uniform float ShadowIntensity;

varying highp vec2 blurTextureCoords[11];

// Shadow
float margin = 256.0;


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
        blurTextureCoords[ i + 5 ] = texCoordsIn + vec2( 0.0 ,pixelSize * float( i ) );
    }

    // Sends vertex position
    gl_Position= pos;
}

void drawBlur()
{
    calcSurfacePosition();

    // Set Texture Vertex Position
   // texCoordsOut.x = ( pos.x + 150.0 ) / (viewSize.x + 300.0) ;
    //texCoordsOut.y = ( pos.y + 150.0 ) / (viewSize.y + 300.0) ;

    texCoordsOut = texCoordsIn;

}

void drawSurface()
{
    calcSurfacePosition();

     // Set Texture Vertex Position
    texCoordsOut = texCoordsIn;
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

void drawBottomShadow()
{
    if( pos.x == 0.0 )
        gl_Position.x = (2.0f/screenSize.x)*(viewOffset.x - margin) - 1.0f;
    else
        gl_Position.x = (2.0f/screenSize.x)*(viewOffset.x + pos.x + margin) - 1.0f;

    if( pos.y == 0.0 )
        gl_Position.y = 1.0f - (2.0f/screenSize.y)*(viewOffset.y + pos.y);
    else
        gl_Position.y = 1.0f - (2.0f/screenSize.y)*(viewOffset.y + pos.y + margin);

    gl_Position.z = pos.z;
    gl_Position.w = 1.0f;

    texCoordsOut = texCoordsIn;
}

void drawTopShadow()
{
    if( pos.x == 0.0 )
        gl_Position.x = (2.0f/screenSize.x)*(viewOffset.x - margin) - 1.0f;
    else
        gl_Position.x = (2.0f/screenSize.x)*(viewOffset.x + pos.x + margin) - 1.0f;

    if( pos.y == 0.0 )
        gl_Position.y = 1.0f - (2.0f/screenSize.y)*(viewOffset.y + pos.y - margin);
    else
        gl_Position.y = 1.0f - (2.0f/screenSize.y)*(viewOffset.y + pos.y);

    gl_Position.z = pos.z;
    gl_Position.w = 1.0f;

    texCoordsOut = texCoordsIn;
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

    // Draws title bar
    if(Mode == 7) drawSurface();

    // Draws bottom shadow
    if(Mode == 8) drawBottomShadow();

    // Draws top shadow
    if(Mode == 9) drawTopShadow();

}


