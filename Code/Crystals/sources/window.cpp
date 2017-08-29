#include "window.h"
#include "compositor.h"

Window::Window(Compositor *_compositor)
{
    // Save the compositor reference
    compositor = _compositor;

    // Calculate the full rect vertices
    calcfullRectVertices();

    // Drag event
    connect(compositor, &Compositor::dragStarted, this, &Window::startDrag);

    connect(fpsTimer,SIGNAL(timeout()),this,SLOT(displayFps()));

    fpsTimer->start(1);

    // Set screen
    QWindow::setScreen(QGuiApplication::primaryScreen());

    // Show window
    QWindow::show();

}

void Window::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

    // Select the current shader program
    glUseProgram(program.programId());

    // Get shader attributes locations
    VertexPositionSlot = glGetAttribLocation(program.programId(), "VertexPosition");
    VertexColorSlot = glGetAttribLocation(program.programId(),  "VertexColor");
    TextureCoordsSlot = glGetAttribLocation(program.programId(),  "TextureCoords");

    // Enable shader attributes
    glEnableVertexAttribArray(VertexPositionSlot);
    glEnableVertexAttribArray(VertexColorSlot);
    glEnableVertexAttribArray(TextureCoordsSlot);

    // Get GLSL Uniforms Locations
    ModeUniform = glGetUniformLocation(program.programId(), "Mode");
    ScreenUniform = glGetUniformLocation(program.programId(), "Screen");
    SizeUniform = glGetUniformLocation(program.programId(), "Size");
    InvertedUniform = glGetUniformLocation(program.programId(), "Inverted");
    PositionUniform = glGetUniformLocation(program.programId(), "Position");
    BorderRadiusActiveCornersUniform = glGetUniformLocation(program.programId(), "Borders");
    BorderRadiusSizeUniform = glGetUniformLocation(program.programId(), "BorderRadius");
    OpacityUniform = glGetUniformLocation(program.programId(), "Opacity");
    BlurWhiteIntensityUniform = glGetUniformLocation(program.programId(), "BlurWhite");
    BlurLevelUniform = glGetUniformLocation(program.programId(), "BlurLevel");
    BlurStageUniform = glGetUniformLocation(program.programId(), "BlurStage");
    BlurIterationUniform = glGetUniformLocation(program.programId(), "BlurIteration");
    ShadowSizeUniform = glGetUniformLocation(program.programId(), "ShadowSize");
    ShadowIntensityUniform = glGetUniformLocation(program.programId(), "ShadowIntensity");


}


void Window::initializeGL()
{
    glEnable(GL_TEXTURE_2D);

    /* ---------- OFFSCREEN BUFFER AND TEXTURE  ---------- */

    // Create offscreen texture
    glGenTextures(1,&offscreenTexture);
    glBindTexture(GL_TEXTURE_2D, offscreenTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Create the offscreen buffer
    glGenFramebuffers(1, &offscreenBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, offscreenBuffer);

    // Set offscreen texture as our colour attachement
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,offscreenTexture,0);

    // Set the list of draw buffers.
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

     /* ---------- SURFACE BLUR BUFFER AND TEXTURE ---------- */

    // Create blur texture
    glGenTextures(1,&blurTexture);
    glBindTexture(GL_TEXTURE_2D, blurTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Create the offscreen buffer
    glGenFramebuffers(1, &blurBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, blurBuffer);

    // Set offscreen texture as our colour attachement
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,blurTexture,0);

    // Set the list of draw buffers.
    glDrawBuffers(1, DrawBuffers);

      /* ---------- OPEN-GL SETUP ---------- */

    // Create a vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Create a vertex index buffer
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    // Send the triangles indices list for the background
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(background->Indices), background->Indices, GL_STATIC_DRAW);

    // Set default background image
    setBackground(SYSTEM_PATH + "/System/Wallpapers/Valparaiso 1.jpg");

    // Set default background color
    background->setColor(Qt::white);

    // Create shaders
    initShaders();

    // Set screen clear color
    glClearColor(1, 1, 1, 1); // White

    // Set the data index and size of each vertex
    glVertexAttribPointer(VertexPositionSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(VertexColorSlot, 4, GL_FLOAT, GL_FALSE,sizeof(Vertex), (GLvoid*) (sizeof(float) * 3));
    glVertexAttribPointer(TextureCoordsSlot, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (sizeof(float) * 7));
}

void Window::drawBackground()
{

    // Binds the offscreen framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER,offscreenBuffer);

    drawSurface(QRectF(0,0,width(),height()), 1.0, background->texture->textureId(), false, false, false, false, 0.0, false);

}

void Window::drawWindow(View *view)
{


    QRectF viewRect = QRectF(view->position().x(),view->position().y(),view->size().width(),view->size().height());

    // Draws  blur
    if( view->blur ) drawBlur( viewRect, 0.5, 1.6, 0.4, view->opacity, true, true, false, false, 8.0);

    // Draws  shadow
    drawShadow( QRectF( viewRect.x(), viewRect.y() -  view->titleBar->size().height(), viewRect.width(), viewRect.height() +  view->titleBar->size().height()), 0.15, view->opacity, 200.0, true, true, true, true, 8.0);

    // Selects blur framebuffer
    glBindFramebuffer( GL_FRAMEBUFFER, offscreenBuffer );

    // Draws surface
    drawSurface( viewRect, view->opacity, view->getTexture()->textureId(), false, false , true, true, 8.0, false);

    // Draws title bar
   drawSurface( QRectF(
                    view->position().x(),
                    view->position().y() - view->titleBar->size().height(),
                    view->size().width(),
                    view->titleBar->size().height()), 255, view->titleBar->getTexture()->textureId(), true, true , false, false, 8.0, false);

    view->previusPosition = view->position();
}

void Window::drawParadiso()
{
    QRect rect = QRect( 0, 0, width(), paradisoView->size().height());
    drawBlur(rect, 0.7, 0.6, 0.3, 1.0, false, false, false, false, 0.0);
    drawSurface( rect, 1.0, paradisoView->getTexture()->textureId(), false, false, false, false, 0.0, false );
    drawShadow( rect, 0.1, 0.5, 50, false, false, false, false, 0.0);
}

void Window::drawSurface(QRectF rect, uint opacity, GLuint textureId, bool TL, bool TR, bool BR, bool BL, float borderRadius, bool inverted)
{

    // Send the vertex data
    glBufferData( GL_ARRAY_BUFFER, sizeof( fullRectVertices ), fullRectVertices, GL_STATIC_DRAW );

    // Tells OpenGL the view position
    glUniform2f(PositionUniform, rect.x(), rect.y() );

    // Tells OpenGL the view size
    glUniform2f(SizeUniform, rect.width(), rect.height());

    // Set OpenGL to blur mode
    glUniform2f(ScreenUniform, width(), height());

    // Tells OpenGL the view opacity
    glUniform1f(OpacityUniform, opacity);

    // Inverts Y axis
    glUniform1ui(InvertedUniform, inverted);

    // Tells OpenGL the active borders
    glUniform4ui(BorderRadiusActiveCornersUniform, TL, TR, BR, BL);

    // Tells OpenGL the active borders
    glUniform1f(BorderRadiusSizeUniform, borderRadius);

    // Sets render size
    glViewport( 0, 0, width(), height());

    // Select current view texture
    glBindTexture(GL_TEXTURE_2D, textureId);

    // Set OpenGL Mode
    glUniform1i(ModeUniform,SHADER_DRAW_SURFACE);

    // Draw Surface
    glDrawArrays(GL_TRIANGLE_FAN,0,4);
}

void Window::drawBlur(const QRectF &rect, float whiteIntensity, float blurLevel, float quality, uint opacity, bool TL, bool TR, bool BR, bool BL, float borderRadius)
{
    // Selects blur framebuffer
    glBindFramebuffer( GL_FRAMEBUFFER, blurBuffer );

    // Set blur texture
    glBindTexture( GL_TEXTURE_2D, blurTexture );

    // Sets blur texture size
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, rect.width() * quality, rect.height() * quality, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );

    // Set OpenGL to blur mode
    glUniform1i( ModeUniform, SHADER_DRAW_BLUR );

    // Set OpenGL to blur mode
    glUniform1f( BlurLevelUniform, blurLevel );

    // Tells OpenGL the view position
    glUniform2f(PositionUniform, rect.x(), rect.y() );

    // Tells OpenGL the view size
    glUniform2f(SizeUniform, rect.width(), rect.height());

    // Set OpenGL to blur mode
    glUniform2f(ScreenUniform, width(), height());

    // White tint
    glUniform1f(BlurWhiteIntensityUniform, whiteIntensity);

    // Set blur stage
    glUniform1i( BlurStageUniform, BLUR_RECT);

    // Set offscreen texture
    glBindTexture( GL_TEXTURE_2D, offscreenTexture );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,   GL_MIRRORED_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,   GL_MIRRORED_REPEAT);

    // Sets render size
    glViewport( 0, 0, rect.width() * quality, rect.height() * quality);

    // Send the vertex data
    glBufferData( GL_ARRAY_BUFFER, sizeof( fullRectVertices ), fullRectVertices, GL_STATIC_DRAW );


    // Draw texture
    glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );


     /* ------- Apply blur to the previus texture ------*/

    // Set horizontal texture
    glBindTexture( GL_TEXTURE_2D, blurTexture );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,   GL_MIRRORED_REPEAT);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,   GL_MIRRORED_REPEAT);

    // Apply the vertical and horizontal blur
    for( int i = 1;  i <= 13; i+=6 )
    {
        // Set OpenGL to blur mode
        glUniform1i( BlurIterationUniform, i );



        // Set OpenGL to blur mode
        glUniform1i( BlurStageUniform, BLUR_VERTICAL );

        // Draw texture
        glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );

        // Set OpenGL to blur mode
        glUniform1i( BlurStageUniform, BLUR_HORIZONTAL );

        // Draw texture
        glDrawArrays( GL_TRIANGLE_FAN, 0, 4 );

    }

    /* ------- Draws the final  blur ------*/

    // Sets render size
    glViewport( 0, 0, width(), height());

    // Selects main framebuffer
    glBindFramebuffer( GL_FRAMEBUFFER, offscreenBuffer );

    // Draws final blur
   drawSurface( rect, opacity, blurTexture, TL, TR, BR, BL, borderRadius, true);
}

void Window::drawShadow(const QRectF &rect, float intensity, uint opacity, float size, bool TL, bool TR, bool BR, bool BL, float borderRadius)
{

    // Tells OpenGL the view position
    glUniform2f(PositionUniform, rect.x(), rect.y());

    // Tells OpenGL the view size
    glUniform2f(SizeUniform, rect.width(), rect.height());

    // Tells OpenGL the view opacity
    glUniform1f(OpacityUniform, opacity);

    // Tells OpenGL the active borders
    glUniform4ui(BorderRadiusActiveCornersUniform, TL, TR, BR, BL);

    // Tells OpenGL the active borders
    glUniform1f(ShadowSizeUniform, size);

    // Tells OpenGL the active borders
    glUniform1f(ShadowIntensityUniform, intensity);

    // Tells OpenGL the active borders
    glUniform1f(BorderRadiusSizeUniform, borderRadius);

    // Set blend mode
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // Set OpenGL to bottom shadow mode
    glUniform1i(ModeUniform,SHADER_DRAW_SHADOW);

    // Draw Shadow
    glDrawArrays(GL_TRIANGLE_FAN,0,4);

    // Set blend mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::drawFinalView()
{

    // Disable blending
    glDisable(GL_BLEND);

   // Selects screen buffer
   glBindFramebuffer(GL_FRAMEBUFFER, 0);

   // Draw Final View
   drawSurface(QRectF(0,0,width(),height()), 1.0, offscreenTexture, false, false, false, false , 0.0, true);


}


void Window::setBackground(QString path)
{

    QOpenGLTexture *backgroundTexture = new QOpenGLTexture( QImage(path), QOpenGLTexture::DontGenerateMipMaps);
    backgroundTexture->setMinificationFilter(QOpenGLTexture::Linear);
    backgroundTexture->setMagnificationFilter(QOpenGLTexture::Linear);

    background->setImage(backgroundTexture);
    background->setMode(Image);
    background->setImageMode(KeepRatioToFill);

}



void Window::paintGL()
{

    fps++;

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set blend mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Asign the screen size uniform
    glUniform2f( ScreenUniform, width(), height() );

    // Draw Background Image
    drawBackground();

    // Enable alpha blending
    glEnable(GL_BLEND);

    // Draw all views
    Q_FOREACH (View *view, compositor->views) {

        // Skip Special views
        if (view->isCursor() || !view->configured || view->role == TITLEBAR_MODE || view->role == PARADISO_MODE || view->role == FRAMELESS_MODE)
            continue;

        // Skip if no texture
        QOpenGLTexture *texture = view->getTexture();

        // Select current surface
        QWaylandSurface *surface = view->surface();

        // Check if surface is avaliable
        if ((surface && surface->hasContent()) || view->isBufferLocked()) {

            // Get surface size
            QSize s = view->size();

            // Skip if size is 0
            if (!s.isEmpty()) {

                if(view == mouseView && grabState == LeftResize)
                {
                    mouseView->setPosition(QPointF(initialViewPosition.x() - s.width() + initialViewSize.width(), initialViewPosition.y()));
                }
                // Draw view
                drawWindow(view);

            }
        }
    }

    // Draw paradiso
    if( paradisoView != nullptr ) drawParadiso();

    // Draw offscreen framebuffer
    drawFinalView();

}

void Window::resizeGL(int, int)
{
    // Adjust background
    if(background->viewMode == Image)
        background->setImageMode(background->imageMode);

    // Selects offscreen texture
    glBindTexture(GL_TEXTURE_2D, offscreenTexture);

    // Sets texture size
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width(), height(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, 0);

}

View *Window::viewAt(const QPointF &point)
{
    // Store the view
    View *ret = 0;

    // Loop all views
    Q_FOREACH (View *view, compositor->views)
    {
        // Skip if is the drag icon
        if (view == dragIconView)
            continue;

        // Check if point is in view rect
        QRectF geom(view->position() - QPointF(5,5), view->size() + QSizeF(10,10));
        if (geom.contains(point))
            ret = view;
    }
    return ret;
}

void Window::startMove()
{
    grabState = MoveGrab;
}



void Window::startDrag(View *dragIcon)
{
    grabState = DragGrab;
    dragIconView = dragIcon;
    compositor->raise(dragIcon);
}

void Window::displayFps()
{
    this->setTitle(QString::number(fps));
    fps = 0;
    fpsTimer->start(1000);
}

// This method is called just once
void Window::calcfullRectVertices()
{
    // Top left
    fullRectVertices[0].position[0] =-1.0;
    fullRectVertices[0].position[1] = 1.0;
    fullRectVertices[0].position[2] = 0.0;

    fullRectVertices[0].texture[0] = 0.0f;
    fullRectVertices[0].texture[1] = 1.0f;

    // Bottom left
    fullRectVertices[1].position[0] = -1.0;
    fullRectVertices[1].position[1] = -1.0;
    fullRectVertices[1].position[2] = 0.0;

    fullRectVertices[1].texture[0] = 0.0f;
    fullRectVertices[1].texture[1] = 0.0f;

    // Bottom right
    fullRectVertices[2].position[0] =  1.0;
    fullRectVertices[2].position[1] = -1.0;
    fullRectVertices[2].position[2] =  0.0;

    fullRectVertices[2].texture[0] = 1.0f;
    fullRectVertices[2].texture[1] = 0.0f;

    // Top right
    fullRectVertices[3].position[0] = 1.0;
    fullRectVertices[3].position[1] = 1.0;
    fullRectVertices[3].position[2] = 0.0;

    fullRectVertices[3].texture[0] = 1.0f;
    fullRectVertices[3].texture[1] = 1.0f;

}



void Window::mousePressEvent(QMouseEvent *e)
{

    // If there is a view
    if (mouseView)
    {
        QPointF pos = mouseView->position();
        QSize siz = mouseView->size();
        int margin = 5;

        // TopLeft corner
        if ( e->pos().x() <= pos.x() + margin && e->pos().y() <= pos.y() + margin && mouseView->role == TITLEBAR_MODE)
        {
            setCursor(Qt::SizeFDiagCursor);
            return;
        }
        // TopRight corner
        else if ( e->pos().x() >= pos.x() + siz.width() - margin && e->pos().y() <= pos.y() + margin && mouseView->role == TITLEBAR_MODE)
        {
            setCursor(Qt::SizeBDiagCursor);
            return;
        }
        // BottomRight corner
        else if ( e->pos().x() >= pos.x() + siz.width() - margin && e->pos().y() >= pos.y() + siz.height()- margin && mouseView->role == WINDOW_MODE)
        {
            setCursor(Qt::SizeFDiagCursor);
            return;
        }
        // BottomLeft corner
        else if ( e->pos().x() <= pos.x() + margin && e->pos().y() >= pos.y() + siz.height()- margin && mouseView->role == WINDOW_MODE)
        {
            setCursor(Qt::SizeBDiagCursor);
            return;
        }
        // Left border
        else if ( e->pos().x() - margin <= pos.x())
        {
            initialViewSize = mouseView->size();
            initialViewPosition = mouseView->position();
            initialMousePos = e->pos();
            grabState = LeftResize;
            return;
        }
        // Right border
        else if ( e->pos().x() + margin >= pos.x() + siz.width())
        {
            initialViewSize = mouseView->size();
            initialMousePos = e->pos();
            grabState = RightResize;
            return;
        }
        // Top border
        else if ( e->pos().y() - margin <= pos.y() && mouseView->role == TITLEBAR_MODE)
        {
            setCursor(Qt::SizeVerCursor);
        }
        // Bottom border
        else if ( e->pos().y() + margin >= pos.y() + siz.height() && mouseView->role == WINDOW_MODE)
        {
            initialViewSize = mouseView->size();
            initialMousePos = e->pos();
            grabState = BottomResize;
            return;
        }
        else
        {
            // Raise views
            if(mouseView->role == TITLEBAR_MODE)
            {
                compositor->raise(mouseView->titleBarParent);

                // Save mouse press position
                initialViewPosition = mouseView->titleBarParent->position();
                initialMousePos = e->pos();
                mouseOffset = e->localPos() - mouseView->position();
                grabState = MoveGrab;
            }
            if(mouseView->role == WINDOW_MODE)
            {
                compositor->raise(mouseView->titleBar);

                // Save mouse press position
                initialMousePos = e->pos();
                mouseOffset = e->localPos() - mouseView->position();
            }
        }
        compositor->defaultSeat()->setKeyboardFocus(mouseView->surface());
        compositor->defaultSeat()->setMouseFocus(mouseView);
        compositor->raise(mouseView);
        compositor->triggerRender();
    }
    // Send mouse press event
    sendMouseEvent(e, mouseView);
}

void Window::mouseReleaseEvent(QMouseEvent *e)
{
    grabState = NoGrab;
    sendMouseEvent(e, mouseView);
}

void Window::mouseMoveEvent(QMouseEvent *e)
{
    switch (grabState)
    {
    case NoGrab: {

        mouseView = viewAt(e->localPos());

        if (!mouseView)
        {
            setCursor(Qt::ArrowCursor);
            return;
        }
        QPointF pos = mouseView->position();
        QSize siz = mouseView->size();
        int margin = 5;

        // TopLeft corner
        if ( e->pos().x() <= pos.x() + margin && e->pos().y() <= pos.y() + margin && mouseView->role == TITLEBAR_MODE)
        {
            setCursor(Qt::SizeFDiagCursor);
            return;
        }
        // TopRight corner
        else if ( e->pos().x() >= pos.x() + siz.width() - margin && e->pos().y() <= pos.y() + margin && mouseView->role == TITLEBAR_MODE)
        {
            setCursor(Qt::SizeBDiagCursor);
            return;
        }
        // BottomRight corner
        else if ( e->pos().x() >= pos.x() + siz.width() - margin && e->pos().y() >= pos.y() + siz.height()- margin && mouseView->role == WINDOW_MODE)
        {
            setCursor(Qt::SizeFDiagCursor);
            return;
        }
        // BottomLeft corner
        else if ( e->pos().x() <= pos.x() + margin && e->pos().y() >= pos.y() + siz.height()- margin && mouseView->role == WINDOW_MODE)
        {
            setCursor(Qt::SizeBDiagCursor);
            return;
        }
        // Left border
        else if ( e->pos().x() - margin <= pos.x())
        {
            setCursor(Qt::SizeHorCursor);
        }
        // Right border
        else if ( e->pos().x() + margin >= pos.x() + siz.width())
        {
            setCursor(Qt::SizeHorCursor);
        }
        // Top border
        else if ( e->pos().y() - margin <= pos.y() && mouseView->role == TITLEBAR_MODE)
        {
            setCursor(Qt::SizeVerCursor);
        }
        // Bottom border
        else if ( e->pos().y() + margin >= pos.y() + siz.height() && mouseView->role == WINDOW_MODE)
        {
            setCursor(Qt::SizeVerCursor);
        }
        else
        {
            setCursor(Qt::ArrowCursor);
            sendMouseEvent(e, mouseView);
        }
    }
        break;
    case MoveGrab: {
        mouseView->titleBarParent->setPosition(initialViewPosition + e->localPos() - initialMousePos);
        update();
    }
        break;
    case LeftResize:
    {
        mouseView->setSize(QSize(initialViewSize.width() - e->localPos().x() + initialMousePos.x(), initialViewSize.height()));
    }
        break;
    case BottomResize:
    {
        mouseView->setSize(QSize(initialViewSize.width(), initialViewSize.height() + e->localPos().y() - initialMousePos.y()));
    }
        break;
    case RightResize:
    {
        mouseView->setSize(QSize(initialViewSize.width()+ e->localPos().x() - initialMousePos.x(), initialViewSize.height()));
    }
        break;
    case DragGrab: {
        View *view = viewAt(e->localPos());
        compositor->handleDrag(view, e);
        if (dragIconView) {
            dragIconView->setPosition(e->localPos() + dragIconView->position());
            update();
        }
    }
        break;
    }
}

void Window::wheelEvent(QWheelEvent *e)
{
    compositor->defaultSeat()->sendMouseWheelEvent(e->orientation(),e->delta()/10);
}

// Send mouse event to the compositor
void Window::sendMouseEvent(QMouseEvent *e, View *target)
{
    // Get the mouse coords
    QPointF mappedPos = e->localPos();

    // Check if view was found
    if (target) mappedPos -= target->position();

    // Create the mouse event
    QMouseEvent viewEvent(e->type(), mappedPos, e->localPos(), e->button(), e->buttons(), e->modifiers());

    // Send event to the compositor
    compositor->handleMouseEvent(target, &viewEvent);
}

// Send key press event to the compositor
void Window::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_0)
        compositor->man.launchZpp(SYSTEM_PATH + "/Applications/DemoApp.zpp");

    compositor->defaultSeat()->sendKeyPressEvent(e->nativeScanCode());
}

// Send key release event to the compositor
void Window::keyReleaseEvent(QKeyEvent *e)
{
    compositor->defaultSeat()->sendKeyReleaseEvent(e->nativeScanCode());
}




