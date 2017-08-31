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
    QPointer<View> mouseView;

    // Topbar grab
    void mouseGrabBegin();


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
    GLuint InvertedUniform;
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
    GLuint OnlyColorUniform;
    GLuint ColorUniform;

    // OpenGL Slots
    GLuint VertexPositionSlot;
    GLuint VertexColorSlot;
    GLuint TextureCoordsSlot;

    // Important Elements
    Background *background = new Background(this);
    Compositor *compositor = nullptr;

    QOpenGLTexture *closeButtonTexture;
    QOpenGLTexture *minimizeButtonTexture;
    QOpenGLTexture *expandButtonTexture;

    // Draw Functions
    void drawWindow(View *view);
    void drawBackground();
    void drawParadiso();

    void drawSurface(QRectF rect, uint opacity,GLuint textureId, bool TL, bool TR, bool BR, bool BL, float borderRadius, bool inverted, bool solidColor = false, QColor color = Qt::white);
    void drawBlur(const QRectF &rect, float whiteIntensity, float blurLevel, float quality, uint opacity, bool TL, bool TR, bool BR, bool BL, float borderRadius);
    void drawShadow(const QRectF &rect, float intensity, uint opacity, float size, bool TL, bool TR, bool BR, bool BL, float borderRadius);

    // Event Variables
    enum GrabState { NoGrab, MoveGrab, DragGrab , LeftResize, TopResize, RightResize, BottomResize};
    QPointF mouseOffset, initialMousePos, initialViewPosition;
    QSize initialSize, blurSize, initialViewSize;
    GrabState grabState = NoGrab;
    bool mousePressing = false;

    View *viewAt(const QPointF &point);
    bool mouseGrab() const { return grabState != NoGrab ;}
    void sendMouseEvent(QMouseEvent *e, View *target);


};


#endif
