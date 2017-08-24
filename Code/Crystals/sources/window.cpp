#include "window.h"
#include "compositor.h"

Window::Window(Compositor *comp)
{
    // Save the compositor reference
    compositor = comp;

    // Resize event
    connect(compositor, &Compositor::startResize, this, &Window::startResize);

    // Drag event
    connect(compositor, &Compositor::dragStarted, this, &Window::startDrag);

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
    posSlot = glGetAttribLocation(program.programId(), "pos");
    colSlot = glGetAttribLocation(program.programId(), "col");
    corSlot = glGetAttribLocation(program.programId(), "texCoordsIn");

    // Enable shader attributes
    glEnableVertexAttribArray(posSlot);
    glEnableVertexAttribArray(colSlot);
    glEnableVertexAttribArray(corSlot);

    // Get shader uniforms locations
    screenSizeUniform   = glGetUniformLocation(program.programId(), "screenSize");
    textureSizeUniform  = glGetUniformLocation(program.programId(), "textureSize");
    textureUniform      = glGetUniformLocation(program.programId(), "Texture");
    invertUniform       = glGetUniformLocation(program.programId(), "inverted");
    shaderModeUniform   = glGetUniformLocation(program.programId(), "Mode");
    offsetUniform       = glGetUniformLocation(program.programId(), "viewOffset");
    viewSizeUniform     = glGetUniformLocation(program.programId(), "viewSize");
    viewOpacityUniform     = glGetUniformLocation(program.programId(), "viewOpacity");
    blurRadiusUniform     = glGetUniformLocation(program.programId(), "blurRadius");

}


void Window::initializeGL()
{
    glEnable(GL_TEXTURE_2D);

    /* ---------- OFFSCREEN BUFFER AND TEXTURE  ---------- */

    // Create offscreen texture
    glGenTextures(1,&offscreenTexture);
    glBindTexture(GL_TEXTURE_2D, offscreenTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

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
    setBackground(SYSTEM_PATH + "/System/Wallpapers/Sea 1.jpg");

    // Set default background color
    background->setColor(Qt::white);

    // Create shaders
    initShaders();

    // Set screen clear color
    glClearColor(1, 1, 1, 1); // White

    // Set the data index and size of each vertex
    glVertexAttribPointer(posSlot, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); // Position
    glVertexAttribPointer(colSlot, 4, GL_FLOAT, GL_FALSE,sizeof(Vertex), (GLvoid*) (sizeof(float) * 3)); // Color
    glVertexAttribPointer(corSlot, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) (sizeof(float) * 7)); // Texture Cords
}

void Window::drawBackground()
{

    // Binds offscren fb
    glBindFramebuffer(GL_FRAMEBUFFER,offscreenBuffer);

    // Selects background texture
    glBindTexture(GL_TEXTURE_2D, background->texture->textureId());

    // Set OpenGL to background mode
    glUniform1i(shaderModeUniform,SHADER_BACKGROUND);

    // Tells OpenGL the background size
    glUniform2f(textureSizeUniform,background->texture->width(),background->texture->height());

    // Send the vertex list
    glBufferData(GL_ARRAY_BUFFER, sizeof(background->vertices), background->vertices, GL_STATIC_DRAW);

    //Draw Background to the offscreen buffer
    glDrawElements(GL_TRIANGLES, sizeof(GLubyte)*6,GL_UNSIGNED_BYTE, 0);

}

void Window::drawView(View *view)
{
    // Skip view if is not configured
    if(!view->configured || view->role == TITLEBAR_MODE) return;

    // Surface position
    float x = view->position().x();
    float y = view->position().y();

    // Surface size
    float w = view->size().width();
    float h = view->size().height();

    // Calculates view vertices if size has changed
    if(view->previusSize != view->size())
    {
        // Saves the current view size
        view->previusSize = view->size();

        // Calculates the view vertices
        view->calcVertexPos();

        // Calculates the topbar vertices
        view->calcTopBarRect();
    }

    // Tells OpenGL the view position
    glUniform2f(offsetUniform, x, y);

    // Tells OpenGL the view size
    glUniform2f(viewSizeUniform, w, h);

    // Tells OpenGL the view opacity
    glUniform1i(viewOpacityUniform, view->opacity);

    // Draws Background blur
    if( view->blur ){

        /* ------- Render blur rect ------*/

        // Selects blur framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, blurBuffer);

        // Set blur texture
        glBindTexture(GL_TEXTURE_2D, blurTexture);

        float b = 0.3f;
        int extra = 0;


        // Sets blur texture size
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, (w+extra)*b, (h+extra)*b, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

        // Set OpenGL to blur mode
        glUniform1i(shaderModeUniform,SHADER_BLUR_RECT);

        // Set offscreen texture
        glBindTexture(GL_TEXTURE_2D, offscreenTexture);

        // Calculates the surface rect vertices
        view->calcBlurRect();

        // Sets render size
        glViewport( 0, 0,( w+extra)*b, (h + extra)*b);

        // Send the vertex data
        glBufferData(GL_ARRAY_BUFFER, sizeof(view->blurRectVertices), view->blurRectVertices, GL_STATIC_DRAW);

        // Draw texture
        glDrawArrays(GL_TRIANGLE_FAN,0,4);

         /* ------- Render blur ------*/

        // Set horizontal texture
        glBindTexture(GL_TEXTURE_2D, blurTexture);


        // Send the vertex data
        glBufferData(GL_ARRAY_BUFFER, sizeof(screenRectVertices), screenRectVertices, GL_STATIC_DRAW);

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,   GL_CLAMP_TO_EDGE);


        for( int i = 1;  i <= 13; i+=6 )
        {
            // Set OpenGL to blur mode
            glUniform1f(blurRadiusUniform,i);

            // Set OpenGL to blur mode
            glUniform1i(shaderModeUniform,SHADER_HBLUR);

            // Draw texture
            glDrawArrays(GL_TRIANGLE_FAN,0,4);

            // Set OpenGL to blur mode
            glUniform1i(shaderModeUniform,SHADER_VBLUR);

            // Draw texture
            glDrawArrays(GL_TRIANGLE_FAN,0,4);

        }

        /* ------- Draw  blur ------*/

        // Sets render size
        glViewport( 0, 0, width(), height() );

        // Selects main framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, offscreenBuffer);

        // Select rendered texture
        glBindTexture(GL_TEXTURE_2D, blurTexture);

        // Set OpenGL to normal mode
        glUniform1i(shaderModeUniform,SHADER_DRAW_BLUR);

        // Sends the vertices list
        glBufferData(GL_ARRAY_BUFFER, sizeof(view->vertices), view->vertices, GL_STATIC_DRAW);

        // Draw Surface
        glDrawArrays(GL_TRIANGLE_FAN,0, 4);

    }


    // Select current view texture
    glBindTexture(GL_TEXTURE_2D, view->getTexture()->textureId());

    // Sends the vertices list
    glBufferData(GL_ARRAY_BUFFER, sizeof(view->vertices), view->vertices, GL_STATIC_DRAW);

    // Set blend mode
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

    // Set OpenGL to bottom shadow mode
    glUniform1i(shaderModeUniform,SHADER_BOTTOM_SHADOW);

    // Draw Shadow
    glDrawArrays(GL_TRIANGLE_FAN,0,4);

    // Set blend mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set OpenGL to vblur mode
    glUniform1i(shaderModeUniform,SHADER_NORMAL);

    // Draw Surface
    glDrawArrays(GL_TRIANGLE_FAN,0,4);

    // Draws the titlebar
    if(view->role == WINDOW_MODE)
    {

        // Tells OpenGL the Title Bar size
        glUniform2f(viewSizeUniform, w, 40);

        // Tells OpenGL the view position
        glUniform2f(offsetUniform, x, y - view->topBarHeight);

        // Select current titlebar texture
        glBindTexture(GL_TEXTURE_2D, view->titleBar->getTexture()->textureId());

        // Sends the vertices list
        glBufferData(GL_ARRAY_BUFFER, sizeof(view->topBarVertices), view->topBarVertices, GL_STATIC_DRAW);



        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

        // Set OpenGL to bottom shadow mode
        glUniform1i(shaderModeUniform,SHADER_TOP_SHADOW);

        // Draw Shadow
        glDrawArrays(GL_TRIANGLE_FAN,0,4);

        // Set blend mode
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        // Set OpenGL to blur mode
        glUniform1i(shaderModeUniform,SHADER_TITLEBAR);

        // Draw Surface
        glDrawArrays(GL_TRIANGLE_FAN,0,4);

    }

    view->previusPosition = view->position();
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

    // Begin rendering scene
    compositor->startRender();

    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable alpha blending
    glEnable(GL_BLEND);

    // Set blend mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Asign the screen size uniform
    glUniform2f(screenSizeUniform,width(),height());

    // Draw Background Image
    drawBackground();

    // Draw all views
    Q_FOREACH (View *view, compositor->views) {

        // Skip cursor
        if (view->isCursor())
            continue;

        // Skip if no texture
        auto texture = view->getTexture();
        if (!texture)
            continue;

        // Select current surface
        QWaylandSurface *surface = view->surface();

        // Check if surface is avaliable
        if ((surface && surface->hasContent()) || view->isBufferLocked()) {

            // Get surface size
            QSize s = view->size();

            // Skip if size is 0
            if (!s.isEmpty()) {

                // Draw view
                drawView(view);

            }
        }
    }

    // Draw offscreen framebuffer
    drawFinalView();

    // Finishes rendering
    compositor->endRender();
}

void Window::drawFinalView()
{
    // Sets render size
    glViewport( 0, 0, width() , height());

    // Selects screen buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Top left
    screenRectVertices[0].position[0] = -1.0f;
    screenRectVertices[0].position[1] =  1.0f;
    screenRectVertices[0].position[2] = 0.0f;

    screenRectVertices[0].texture[0] = 0.0f;
    screenRectVertices[0].texture[1] = 1.0f;

    // Bottom left
    screenRectVertices[1].position[0] = -1.0f;
    screenRectVertices[1].position[1] = -1.0f;
    screenRectVertices[1].position[2] = 0.0f;

    screenRectVertices[1].texture[0] = 0.0f;
    screenRectVertices[1].texture[1] = 0.0f;

    // Bottom right
    screenRectVertices[2].position[0] =  1.0f;
    screenRectVertices[2].position[1] = -1.0f;
    screenRectVertices[2].position[2] = 0.0f;

    screenRectVertices[2].texture[0] = 1.0f;
    screenRectVertices[2].texture[1] = 0.0f;

    // Top right
    screenRectVertices[3].position[0] = 1.0f;
    screenRectVertices[3].position[1] = 1.0f ;
    screenRectVertices[3].position[2] = 0.0f;

    screenRectVertices[3].texture[0] = 1.0f;
    screenRectVertices[3].texture[1] = 1.0f;

    // Set OpenGL to final mode
    glUniform1i(shaderModeUniform,SHADER_FINAL);

    // Select current view texture
    glBindTexture(GL_TEXTURE_2D, offscreenTexture);

    // Sends the vertices list
    glBufferData(GL_ARRAY_BUFFER, sizeof(screenRectVertices), screenRectVertices, GL_STATIC_DRAW);

    // Draw Surface
    glDrawArrays(GL_TRIANGLE_FAN,0, 4);

}
void Window::resizeGL(int, int)
{
    // Adjust background
    if(background->viewMode == Image)
        background->setImageMode(background->imageMode);

    // Selects offscreen texture
    glBindTexture(GL_TEXTURE_2D, offscreenTexture);

    // Sets texture size
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width(), height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

    glViewport(0,0,width(),height());
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

void Window::startResize(int edge, bool anchored)
{
    initialSize = mouseView->size();
    grabState = ResizeGrab;
    resizeEdge = edge;
    resizeAnchored = anchored;
}

void Window::startDrag(View *dragIcon)
{
    grabState = DragGrab;
    dragIconView = dragIcon;
    compositor->raise(dragIcon);
}

void Window::mousePressEvent(QMouseEvent *e)
{
    // Find view at mouse position
    mouseView = viewAt(e->localPos());

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
            setCursor(Qt::SizeHorCursor);
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
    compositor->defaultSeat()->sendKeyPressEvent(e->nativeScanCode());
}

// Send key release event to the compositor
void Window::keyReleaseEvent(QKeyEvent *e)
{
    compositor->defaultSeat()->sendKeyReleaseEvent(e->nativeScanCode());
}




