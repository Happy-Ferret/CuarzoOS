#ifndef COMPOSITORWINDOW_H
#define COMPOSITORWINDOW_H

#include "headers.h"
#include "background.h"

class Compositor;
class View;
class QOpenGLTexture;

class Window : public QOpenGLWindow
{
    Q_OBJECT
public:

    // Setup
    Window(Compositor *_compositor);

    // Set background image
    void setBackground(QString path);

    // Special views
    View *paradisoView = nullptr;
    View *dragIconView = nullptr;

protected:

    // OpenGL functions
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int, int) override;

    // Mouse Events
    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

    // Key Events
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    // Draws the offscreen buffer
    void drawFinalView();
    void initShaders();

private slots:
    void startMove();
    void startDrag(View *dragIcon);

private:
    // OpenGL Programs
    QOpenGLShaderProgram program;

    // OpenGL Buffers
    GLuint vertexBuffer, indexBuffer, offscreenBuffer, blurBuffer;

    // OpenGL Textures
    GLuint offscreenTexture, blurTexture;

    // The full rect vertices
    Vertex fullRectVertices[4];
    void calcfullRectVertices();

    // OpenGL Uniforms
    GLuint ModeUniform;
    GLuint ScreenUniform;
    GLuint SizeUniform;
    GLuint PositionUniform;
    GLuint BorderRadiusActiveCornersUniform;
    GLuint BorderRadiusSizeUniform;
    GLuint OpacityUniform;
    GLuint BlurWhiteIntensityUniform;
    GLuint BlurLevelUniform;
    GLuint BlurStageUniform;
    GLuint BlurIterationUniform;
    GLuint ShadowSizeUniform;
    GLuint ShadowIntensityUniform;

    // OpenGL Slots
    GLuint VertexPositionSlot;
    GLuint VertexColorSlot;
    GLuint TextureCoordsSlot;

    // Important Elements
    Background *background = new Background(this);
    Compositor *compositor = nullptr;

    // Draw Functions
    void drawWindow(View *view);
    void drawBackground();
    void drawParadiso();

    void drawSurface(const QRectF &rect, uint opacity,GLuint textureId, bool TL, bool TR, bool BR, bool BL, float borderRadius);
    void drawBlur(const QRectF &rect, float whiteIntensity, float blurLevel, float quality, uint opacity, GLuint textureId, bool TL, bool TR, bool BR, bool BL, float borderRadius);
    void drawShadow(const QRectF &rect, float intensity, uint opacity, float size, bool TL, bool TR, bool BR, bool BL, float borderRadius);

    // Event Variables
    enum GrabState { NoGrab, MoveGrab, ResizeGrab, DragGrab , LeftResize, TopResize, RightResize, BottomResize};
    QPointF mouseOffset, initialMousePos, initialViewPosition;
    QSize initialSize, blurSize, initialViewSize;
    GrabState grabState = NoGrab;

    View *viewAt(const QPointF &point);
    bool mouseGrab() const { return grabState != NoGrab ;}
    void sendMouseEvent(QMouseEvent *e, View *target);

    QPointer<View> mouseView;

};


#endif
