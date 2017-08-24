#ifndef COMPOSITORWINDOW_H
#define COMPOSITORWINDOW_H

#include "headers.h"
#include "background.h"

QT_BEGIN_NAMESPACE

class Compositor;
class View;
class QOpenGLTexture;

class Window : public QOpenGLWindow
{
    Q_OBJECT
public:
    Window(Compositor *comp);
    void setBackground(QString path);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int, int) override;

    void mousePressEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *e) override;

    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;

    // Draws the offscreen buffer
    void drawFinalView();

    void initShaders();

private slots:
    void startMove();
    void startResize(int edge, bool anchored);
    void startDrag(View *dragIcon);

private:
    QOpenGLShaderProgram program;
    GLuint vertexBuffer, indexBuffer;

    // Offscreen buffer
    GLuint offscreenBuffer = 0;
    GLuint offscreenTexture;

    // Blur buffer
    GLuint blurBuffer = 0;
    GLuint blurTexture;

    // The screen rect vertices
    Vertex screenRectVertices[4];

    // OpenGL Uniforms
    GLuint screenSizeUniform; // Screen Size ( pixels )
    GLuint textureSizeUniform; // Texture Size ( pixels )
    GLuint textureUniform; // Texture Id
    GLuint shaderModeUniform; // Drawing Mode
    GLuint invertUniform; // Texture Invert
    GLuint offsetUniform; // View Position
    GLuint viewSizeUniform; // View Size ( pixels )
    GLuint viewOpacityUniform; // View Opacity ( 0 - 255 )
    GLuint blurRadiusUniform; // Blur radius ( pixels )

    // OpenGL Slots
    GLuint posSlot; // Vertex  pos
    GLuint colSlot; // Vertex  col
    GLuint corSlot; // Texture pos

    Background *background = new Background(this);

    enum GrabState { NoGrab, MoveGrab, ResizeGrab, DragGrab , LeftResize, TopResize, RightResize, BottomResize};

    View *viewAt(const QPointF &point);
    bool mouseGrab() const { return grabState != NoGrab ;}
    void drawBackground();
    void drawView(View *view);
    void sendMouseEvent(QMouseEvent *e, View *target);

    Compositor *compositor;
    QPointer<View> mouseView;
    GrabState grabState = NoGrab;
    QSize initialSize, blurSize, initialViewSize;
    int resizeEdge;
    bool resizeAnchored;
    QPointF resizeAnchorPosition, mouseOffset, initialMousePos, initialViewPosition;
    View *dragIconView;
};

QT_END_NAMESPACE

#endif // COMPOSITORWINDOW_H
