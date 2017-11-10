/* Generated by wayland-scanner 1.12.0 */

#ifndef CUSTOM_SERVER_PROTOCOL_H
#define CUSTOM_SERVER_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-server.h"

#ifdef  __cplusplus
extern "C" {
#endif

struct wl_client;
struct wl_resource;

/**
 * @page page_custom The custom protocol
 * @section page_ifaces_custom Interfaces
 * - @subpage page_iface_qt_example_extension - Example Wayland extension
 * - @subpage page_iface_qt_example_local_object - An object created on the client side
 * @section page_copyright_custom Copyright
 * <pre>
 *
 * Copyright (C) 2015 The Qt Company Ltd.
 * Contact: http://www.qt.io/licensing/
 *
 * This file is part of the examples of the Qt Wayland module
 *
 * $QT_BEGIN_LICENSE:BSD$
 * You may use this file under the terms of the BSD license as follows:
 *
 * "Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the
 * distribution.
 * * Neither the name of The Qt Company Ltd nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
 *
 * $QT_END_LICENSE$
 * </pre>
 */
struct qt_example_extension;
struct qt_example_local_object;
struct wl_surface;

/**
 * @page page_iface_qt_example_extension qt_example_extension
 * @section page_iface_qt_example_extension_desc Description
 *
 * This example shows how to add extra functionality to Wayland
 * through an extension. This is the global object of the extension.
 * @section page_iface_qt_example_extension_api API
 * See @ref iface_qt_example_extension.
 */
/**
 * @defgroup iface_qt_example_extension The qt_example_extension interface
 *
 * This example shows how to add extra functionality to Wayland
 * through an extension. This is the global object of the extension.
 */
extern const struct wl_interface qt_example_extension_interface;
/**
 * @page page_iface_qt_example_local_object qt_example_local_object
 * @section page_iface_qt_example_local_object_desc Description
 *
 * This object should have a visual representation in the compositor.
 * @section page_iface_qt_example_local_object_api API
 * See @ref iface_qt_example_local_object.
 */
/**
 * @defgroup iface_qt_example_local_object The qt_example_local_object interface
 *
 * This object should have a visual representation in the compositor.
 */
extern const struct wl_interface qt_example_local_object_interface;

#ifndef QT_EXAMPLE_EXTENSION_DECORATION_STATE_ENUM
#define QT_EXAMPLE_EXTENSION_DECORATION_STATE_ENUM
/**
 * @ingroup iface_qt_example_extension
 * window decoration state
 *
 * Describes whether window decorations should be shown.
 */
enum qt_example_extension_decoration_state {
	/**
	 * Decorations are not shown
	 */
	QT_EXAMPLE_EXTENSION_DECORATION_STATE_HIDDEN = 0,
	/**
	 * Decorations are shown
	 */
	QT_EXAMPLE_EXTENSION_DECORATION_STATE_SHOWN = 1,
};
#endif /* QT_EXAMPLE_EXTENSION_DECORATION_STATE_ENUM */

/**
 * @ingroup iface_qt_example_extension
 * @struct qt_example_extension_interface
 */
struct qt_example_extension_interface {
	/**
	 * Register a surface with the example extension
	 *
	 * Inform the compositor that the client has a new surface that
	 * is covered by the extension.
	 */
	void (*register_surface)(struct wl_client *client,
				 struct wl_resource *resource,
				 struct wl_resource *surface);
	/**
	 * Move the surface around for a little while
	 *
	 * The compositor should perform a move animation on the surface.
	 * @param duration duration in ms
	 */
	void (*bounce)(struct wl_client *client,
		       struct wl_resource *resource,
		       struct wl_resource *surface,
		       uint32_t duration);
	/**
	 * Rotate the surface for a little while
	 *
	 * The compositor should perform a rotating animation on the
	 * surface.
	 * @param duration duration in ms
	 */
	void (*spin)(struct wl_client *client,
		     struct wl_resource *resource,
		     struct wl_resource *surface,
		     uint32_t duration);
	/**
	 * Create a sily object
	 *
	 * Create a new object that should be visualized by the
	 * compositor
	 */
	void (*create_local_object)(struct wl_client *client,
				    struct wl_resource *resource,
				    uint32_t id,
				    const char *color,
				    const char *text);
};

#define QT_EXAMPLE_EXTENSION_CLOSE 0
#define QT_EXAMPLE_EXTENSION_SET_FONT_SIZE 1
#define QT_EXAMPLE_EXTENSION_SET_WINDOW_DECORATION 2

/**
 * @ingroup iface_qt_example_extension
 */
#define QT_EXAMPLE_EXTENSION_CLOSE_SINCE_VERSION 1
/**
 * @ingroup iface_qt_example_extension
 */
#define QT_EXAMPLE_EXTENSION_SET_FONT_SIZE_SINCE_VERSION 1
/**
 * @ingroup iface_qt_example_extension
 */
#define QT_EXAMPLE_EXTENSION_SET_WINDOW_DECORATION_SINCE_VERSION 1

/**
 * @ingroup iface_qt_example_extension
 */
#define QT_EXAMPLE_EXTENSION_REGISTER_SURFACE_SINCE_VERSION 1
/**
 * @ingroup iface_qt_example_extension
 */
#define QT_EXAMPLE_EXTENSION_BOUNCE_SINCE_VERSION 1
/**
 * @ingroup iface_qt_example_extension
 */
#define QT_EXAMPLE_EXTENSION_SPIN_SINCE_VERSION 1
/**
 * @ingroup iface_qt_example_extension
 */
#define QT_EXAMPLE_EXTENSION_CREATE_LOCAL_OBJECT_SINCE_VERSION 1

/**
 * @ingroup iface_qt_example_extension
 * Sends an close event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
qt_example_extension_send_close(struct wl_resource *resource_, struct wl_resource *surface)
{
	wl_resource_post_event(resource_, QT_EXAMPLE_EXTENSION_CLOSE, surface);
}

/**
 * @ingroup iface_qt_example_extension
 * Sends an set_font_size event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
qt_example_extension_send_set_font_size(struct wl_resource *resource_, struct wl_resource *surface, uint32_t pixel_size)
{
	wl_resource_post_event(resource_, QT_EXAMPLE_EXTENSION_SET_FONT_SIZE, surface, pixel_size);
}

/**
 * @ingroup iface_qt_example_extension
 * Sends an set_window_decoration event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
qt_example_extension_send_set_window_decoration(struct wl_resource *resource_, uint32_t state)
{
	wl_resource_post_event(resource_, QT_EXAMPLE_EXTENSION_SET_WINDOW_DECORATION, state);
}

/**
 * @ingroup iface_qt_example_local_object
 * @struct qt_example_local_object_interface
 */
struct qt_example_local_object_interface {
	/**
	 * Change the text
	 *
	 * Tell the compositor that the object's text is changed
	 */
	void (*set_text)(struct wl_client *client,
			 struct wl_resource *resource,
			 const char *text);
};

#define QT_EXAMPLE_LOCAL_OBJECT_CLICKED 0

/**
 * @ingroup iface_qt_example_local_object
 */
#define QT_EXAMPLE_LOCAL_OBJECT_CLICKED_SINCE_VERSION 1

/**
 * @ingroup iface_qt_example_local_object
 */
#define QT_EXAMPLE_LOCAL_OBJECT_SET_TEXT_SINCE_VERSION 1

/**
 * @ingroup iface_qt_example_local_object
 * Sends an clicked event to the client owning the resource.
 * @param resource_ The client's resource
 */
static inline void
qt_example_local_object_send_clicked(struct wl_resource *resource_)
{
	wl_resource_post_event(resource_, QT_EXAMPLE_LOCAL_OBJECT_CLICKED);
}

#ifdef  __cplusplus
}
#endif

#endif