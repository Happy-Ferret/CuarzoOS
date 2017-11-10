#include "qwayland-server-custom.h"

QT_BEGIN_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wmissing-field-initializers")

namespace QtWaylandServer {
    qt_example_extension::qt_example_extension(struct ::wl_client *client, int id, int version)
        : m_resource_map()
        , m_resource(0)
        , m_global(0)
    {
        init(client, id, version);
    }

    qt_example_extension::qt_example_extension(struct ::wl_display *display, int version)
        : m_resource_map()
        , m_resource(0)
        , m_global(0)
    {
        init(display, version);
    }

    qt_example_extension::qt_example_extension(struct ::wl_resource *resource)
        : m_resource_map()
        , m_resource(0)
        , m_global(0)
    {
        init(resource);
    }

    qt_example_extension::qt_example_extension()
        : m_resource_map()
        , m_resource(0)
        , m_global(0)
    {
    }

    qt_example_extension::~qt_example_extension()
    {
    }

    void qt_example_extension::init(struct ::wl_client *client, int id, int version)
    {
        m_resource = bind(client, id, version);
    }

    void qt_example_extension::init(struct ::wl_resource *resource)
    {
        m_resource = bind(resource);
    }

    qt_example_extension::Resource *qt_example_extension::add(struct ::wl_client *client, int version)
    {
        Resource *resource = bind(client, 0, version);
        m_resource_map.insert(client, resource);
        return resource;
    }

    qt_example_extension::Resource *qt_example_extension::add(struct ::wl_client *client, int id, int version)
    {
        Resource *resource = bind(client, id, version);
        m_resource_map.insert(client, resource);
        return resource;
    }

    void qt_example_extension::init(struct ::wl_display *display, int version)
    {
        m_global = wl_global_create(display, &::qt_example_extension_interface, version, this, bind_func);
        m_globalVersion = version;
    }

    const struct wl_interface *qt_example_extension::interface()
    {
        return &::qt_example_extension_interface;
    }

    qt_example_extension::Resource *qt_example_extension::example_extension_allocate()
    {
        return new Resource;
    }

    void qt_example_extension::example_extension_bind_resource(Resource *)
    {
    }

    void qt_example_extension::example_extension_destroy_resource(Resource *)
    {
    }

    void qt_example_extension::bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id)
    {
        qt_example_extension *that = static_cast<qt_example_extension *>(data);
        that->add(client, id, qMin(that->m_globalVersion, version));
    }

    void qt_example_extension::destroy_func(struct ::wl_resource *client_resource)
    {
        Resource *resource = Resource::fromResource(client_resource);
        qt_example_extension *that = resource->example_extension_object;
        that->m_resource_map.remove(resource->client(), resource);
        that->example_extension_destroy_resource(resource);
        delete resource;
#if !WAYLAND_VERSION_CHECK(1, 2, 0)
        free(client_resource);
#endif
    }

    qt_example_extension::Resource *qt_example_extension::bind(struct ::wl_client *client, uint32_t id, int version)
    {
        Q_ASSERT_X(!wl_client_get_object(client, id), "QWaylandObject bind", QStringLiteral("binding to object %1 more than once").arg(id).toLocal8Bit().constData());
        struct ::wl_resource *handle = wl_resource_create(client, &::qt_example_extension_interface, version, id);
        return bind(handle);
    }

    qt_example_extension::Resource *qt_example_extension::bind(struct ::wl_resource *handle)
    {
        Resource *resource = example_extension_allocate();
        resource->example_extension_object = this;

        wl_resource_set_implementation(handle, &m_qt_example_extension_interface, resource, destroy_func);
        resource->handle = handle;
        example_extension_bind_resource(resource);
        return resource;
    }
    qt_example_extension::Resource *qt_example_extension::Resource::fromResource(struct ::wl_resource *resource)
    {
        if (wl_resource_instance_of(resource, &::qt_example_extension_interface, &m_qt_example_extension_interface))
            return static_cast<Resource *>(resource->data);
        return 0;
    }

    const struct ::qt_example_extension_interface qt_example_extension::m_qt_example_extension_interface = {
        qt_example_extension::handle_register_surface,
        qt_example_extension::handle_bounce,
        qt_example_extension::handle_spin,
        qt_example_extension::handle_create_local_object
    };

    void qt_example_extension::example_extension_register_surface(Resource *, struct ::wl_resource *)
    {
    }

    void qt_example_extension::example_extension_bounce(Resource *, struct ::wl_resource *, uint32_t )
    {
    }

    void qt_example_extension::example_extension_spin(Resource *, struct ::wl_resource *, uint32_t )
    {
    }

    void qt_example_extension::example_extension_create_local_object(Resource *, uint32_t, const QString &, const QString &)
    {
    }


    void qt_example_extension::handle_register_surface(
        ::wl_client *client,
        struct wl_resource *resource,
        struct ::wl_resource *surface)
    {
        Q_UNUSED(client);
        Resource *r = Resource::fromResource(resource);
        static_cast<qt_example_extension *>(r->example_extension_object)->example_extension_register_surface(
            r,
            surface);
    }

    void qt_example_extension::handle_bounce(
        ::wl_client *client,
        struct wl_resource *resource,
        struct ::wl_resource *surface,
        uint32_t duration)
    {
        Q_UNUSED(client);
        Resource *r = Resource::fromResource(resource);
        static_cast<qt_example_extension *>(r->example_extension_object)->example_extension_bounce(
            r,
            surface,
            duration);
    }

    void qt_example_extension::handle_spin(
        ::wl_client *client,
        struct wl_resource *resource,
        struct ::wl_resource *surface,
        uint32_t duration)
    {
        Q_UNUSED(client);
        Resource *r = Resource::fromResource(resource);
        static_cast<qt_example_extension *>(r->example_extension_object)->example_extension_spin(
            r,
            surface,
            duration);
    }

    void qt_example_extension::handle_create_local_object(
        ::wl_client *client,
        struct wl_resource *resource,
        uint32_t id,
        const char *color,
        const char *text)
    {
        Q_UNUSED(client);
        Resource *r = Resource::fromResource(resource);
        static_cast<qt_example_extension *>(r->example_extension_object)->example_extension_create_local_object(
            r,
            id,
            QString::fromUtf8(color),
            QString::fromUtf8(text));
    }

    void qt_example_extension::send_close(struct ::wl_resource *surface)
    {
        send_close(
            m_resource->handle,
            surface);
    }

    void qt_example_extension::send_close(struct ::wl_resource *resource, struct ::wl_resource *surface)
    {
        qt_example_extension_send_close(
            resource,
            surface);
    }


    void qt_example_extension::send_set_font_size(struct ::wl_resource *surface, uint32_t pixel_size)
    {
        send_set_font_size(
            m_resource->handle,
            surface,
            pixel_size);
    }

    void qt_example_extension::send_set_font_size(struct ::wl_resource *resource, struct ::wl_resource *surface, uint32_t pixel_size)
    {
        qt_example_extension_send_set_font_size(
            resource,
            surface,
            pixel_size);
    }


    void qt_example_extension::send_set_window_decoration(uint32_t state)
    {
        send_set_window_decoration(
            m_resource->handle,
            state);
    }

    void qt_example_extension::send_set_window_decoration(struct ::wl_resource *resource, uint32_t state)
    {
        qt_example_extension_send_set_window_decoration(
            resource,
            state);
    }


    qt_example_local_object::qt_example_local_object(struct ::wl_client *client, int id, int version)
        : m_resource_map()
        , m_resource(0)
        , m_global(0)
    {
        init(client, id, version);
    }

    qt_example_local_object::qt_example_local_object(struct ::wl_display *display, int version)
        : m_resource_map()
        , m_resource(0)
        , m_global(0)
    {
        init(display, version);
    }

    qt_example_local_object::qt_example_local_object(struct ::wl_resource *resource)
        : m_resource_map()
        , m_resource(0)
        , m_global(0)
    {
        init(resource);
    }

    qt_example_local_object::qt_example_local_object()
        : m_resource_map()
        , m_resource(0)
        , m_global(0)
    {
    }

    qt_example_local_object::~qt_example_local_object()
    {
    }

    void qt_example_local_object::init(struct ::wl_client *client, int id, int version)
    {
        m_resource = bind(client, id, version);
    }

    void qt_example_local_object::init(struct ::wl_resource *resource)
    {
        m_resource = bind(resource);
    }

    qt_example_local_object::Resource *qt_example_local_object::add(struct ::wl_client *client, int version)
    {
        Resource *resource = bind(client, 0, version);
        m_resource_map.insert(client, resource);
        return resource;
    }

    qt_example_local_object::Resource *qt_example_local_object::add(struct ::wl_client *client, int id, int version)
    {
        Resource *resource = bind(client, id, version);
        m_resource_map.insert(client, resource);
        return resource;
    }

    void qt_example_local_object::init(struct ::wl_display *display, int version)
    {
        m_global = wl_global_create(display, &::qt_example_local_object_interface, version, this, bind_func);
        m_globalVersion = version;
    }

    const struct wl_interface *qt_example_local_object::interface()
    {
        return &::qt_example_local_object_interface;
    }

    qt_example_local_object::Resource *qt_example_local_object::example_local_object_allocate()
    {
        return new Resource;
    }

    void qt_example_local_object::example_local_object_bind_resource(Resource *)
    {
    }

    void qt_example_local_object::example_local_object_destroy_resource(Resource *)
    {
    }

    void qt_example_local_object::bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id)
    {
        qt_example_local_object *that = static_cast<qt_example_local_object *>(data);
        that->add(client, id, qMin(that->m_globalVersion, version));
    }

    void qt_example_local_object::destroy_func(struct ::wl_resource *client_resource)
    {
        Resource *resource = Resource::fromResource(client_resource);
        qt_example_local_object *that = resource->example_local_object_object;
        that->m_resource_map.remove(resource->client(), resource);
        that->example_local_object_destroy_resource(resource);
        delete resource;
#if !WAYLAND_VERSION_CHECK(1, 2, 0)
        free(client_resource);
#endif
    }

    qt_example_local_object::Resource *qt_example_local_object::bind(struct ::wl_client *client, uint32_t id, int version)
    {
        Q_ASSERT_X(!wl_client_get_object(client, id), "QWaylandObject bind", QStringLiteral("binding to object %1 more than once").arg(id).toLocal8Bit().constData());
        struct ::wl_resource *handle = wl_resource_create(client, &::qt_example_local_object_interface, version, id);
        return bind(handle);
    }

    qt_example_local_object::Resource *qt_example_local_object::bind(struct ::wl_resource *handle)
    {
        Resource *resource = example_local_object_allocate();
        resource->example_local_object_object = this;

        wl_resource_set_implementation(handle, &m_qt_example_local_object_interface, resource, destroy_func);
        resource->handle = handle;
        example_local_object_bind_resource(resource);
        return resource;
    }
    qt_example_local_object::Resource *qt_example_local_object::Resource::fromResource(struct ::wl_resource *resource)
    {
        if (wl_resource_instance_of(resource, &::qt_example_local_object_interface, &m_qt_example_local_object_interface))
            return static_cast<Resource *>(resource->data);
        return 0;
    }

    const struct ::qt_example_local_object_interface qt_example_local_object::m_qt_example_local_object_interface = {
        qt_example_local_object::handle_set_text
    };

    void qt_example_local_object::example_local_object_set_text(Resource *, const QString &)
    {
    }


    void qt_example_local_object::handle_set_text(
        ::wl_client *client,
        struct wl_resource *resource,
        const char *text)
    {
        Q_UNUSED(client);
        Resource *r = Resource::fromResource(resource);
        static_cast<qt_example_local_object *>(r->example_local_object_object)->example_local_object_set_text(
            r,
            QString::fromUtf8(text));
    }

    void qt_example_local_object::send_clicked()
    {
        send_clicked(
            m_resource->handle);
    }

    void qt_example_local_object::send_clicked(struct ::wl_resource *resource)
    {
        qt_example_local_object_send_clicked(
            resource);
    }

}

QT_WARNING_POP
QT_END_NAMESPACE
