#define SHADER_NORMAL 0
#define SHADER_BACKGROUND 1
#define SHADER_HBLUR 2
#define SHADER_VBLUR 3
#define SHADER_FINAL 4
#define SHADER_BLUR_RECT 5
#define SHADER_DRAW_BLUR 6


uniform highp vec2 textureSize;
uniform sampler2D Texture;
uniform lowp int Mode;
uniform lowp int viewOpacity;


precision mediump float;
precision mediump int;

varying mediump vec4 finalColor;
varying mediump vec2 texCoordsOut;
varying highp vec2 blurTextureCoords[11];

void main(void){

    if ( Mode == 4 || Mode == 5 )
    {
        gl_FragColor = texture2D(Texture, texCoordsOut);
    }

    if(Mode == 2 || Mode == 3)
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

        sum = sum*1.03f ;
        sum.a = 1.0;


        gl_FragColor = sum;

    }
    else if(Mode == 0 )
    {
        vec4 color = finalColor;
        color.a = color.a * (float(viewOpacity) / 255.0);
        gl_FragColor =  texture2D(Texture,texCoordsOut)*color;
    }
    else if(Mode == 1 )
    {
        gl_FragColor =  texture2D(Texture,texCoordsOut)*finalColor;
    }

    else if(Mode == 6)
    {
        gl_FragColor =  (texture2D(Texture,texCoordsOut)*0.4 + vec4(0.6))*finalColor;
    }

}
