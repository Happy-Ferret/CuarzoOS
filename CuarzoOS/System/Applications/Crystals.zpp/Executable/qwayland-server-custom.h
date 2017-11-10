#ifndef QT_WAYLAND_SERVER_CUSTOM
#define QT_WAYLAND_SERVER_CUSTOM

#include "wayland-server.h"
#include "wayland-custom-server-protocol.h"
#include <QByteArray>
#include <QMultiMap>
#include <QString>

#ifndef WAYLAND_VERSION_CHECK
#define WAYLAND_VERSION_CHECK(major, minor, micro) \
    ((WAYLAND_VERSION_MAJOR > (major)) || \
    (WAYLAND_VERSION_MAJOR == (major) && WAYLAND_VERSION_MINOR > (minor)) || \
    (WAYLAND_VERSION_MAJOR == (major) && WAYLAND_VERSION_MINOR == (minor) && WAYLAND_VERSION_MICRO >= (micro)))
#endif

QT_BEGIN_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wmissing-field-initializers")

namespace QtWaylandServer {
    class  qt_example_extension
    {
    public:
        qt_example_extension(struct ::wl_client *client, int id, int version);
        qt_example_extension(struct ::wl_display *display, int version);
        qt_example_extension(struct ::wl_resource *resource);
        qt_example_extension();

        virtual ~qt_example_extension();

        class Resource
        {
        public:
            Resource() : example_extension_object(0), handle(0) {}
            virtual ~Resource() {}

            qt_example_extension *example_extension_object;
            struct ::wl_resource *handle;

            struct ::wl_client *client() const { return handle->client; }
            int version() const { return wl_resource_get_version(handle); }

            static Resource *fromResource(struct ::wl_resource *resource);
        };

        void init(struct ::wl_client *client, int id, int version);
        void init(struct ::wl_display *display, int version);
        void init(struct ::wl_resource *resource);

        Resource *add(struct ::wl_client *client, int version);
        Resource *add(struct ::wl_client *client, int id, int version);
        Resource *add(struct wl_list *resource_list, struct ::wl_client *client, int id, int version);

        Resource *resource() { return m_resource; }
        const Resource *resource() const { return m_resource; }

        QMultiMap<struct ::wl_client*, Resource*> resourceMap() { return m_resource_map; }
        const QMultiMap<struct ::wl_client*, Resource*> resourceMap() const { return m_resource_map; }

        bool isGlobal() const { return m_global != 0; }
        bool isResource() const { return m_resource != 0; }

        static const struct ::wl_interface *interface();
        static QByteArray interfaceName() { return interface()->name; }
        static int interfaceVersion() { return interface()->version; }


        enum decoration_state {
            decoration_state_hidden = 0, // Decorations are not shown
            decoration_state_shown = 1 // Decorations are shown
        };

        void send_close(struct ::wl_resource *surface);
        void send_close(struct ::wl_resource *resource, struct ::wl_resource *surface);
        void send_set_font_size(struct ::wl_resource *surface, uint32_t pixel_size);
        void send_set_font_size(struct ::wl_resource *resource, struct ::wl_resource *surface, uint32_t pixel_size);
        void send_set_window_decoration(uint32_t state);
        void send_set_window_decoration(struct ::wl_resource *resource, uint32_t state);

    protected:
        virtual Resource *example_extension_allocate();

        virtual void example_extension_bind_resource(Resource *resource);
        virtual void example_extension_destroy_resource(Resource *resource);

        virtual void example_extension_register_surface(Resource *resource, struct ::wl_resource *surface);
        virtual void example_extension_bounce(Resource *resource, struct ::wl_resource *surface, uint32_t duration);
        virtual void example_extension_spin(Resource *resource, struct ::wl_resource *surface, uint32_t duration);
        virtual void example_extension_create_local_object(Resource *resource, uint32_t id, const QString &color, const QString &text);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::qt_example_extension_interface m_qt_example_extension_interface;

        static void handle_register_surface(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *surface);
        static void handle_bounce(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *surface,
            uint32_t duration);
        static void handle_spin(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *surface,
            uint32_t duration);
        static void handle_create_local_object(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            const char *color,
            const char *text);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };

    class  qt_example_local_object
    {
    public:
        qt_example_local_object(struct ::wl_client *client, int id, int version);
        qt_example_local_object(struct ::wl_display *display, int version);
        qt_example_local_object(struct ::wl_resource *resource);
        qt_example_local_object();

        virtual ~qt_example_local_object();

        class Resource
        {
        public:
            Resource() : example_local_object_object(0), handle(0) {}
            virtual ~Resource() {}

            qt_example_local_object *example_local_object_object;
            struct ::wl_resource *handle;

            struct ::wl_client *client() const { return handle->client; }
            int version() const { return wl_resource_get_version(handle); }

            static Resource *fromResource(struct ::wl_resource *resource);
        };

        void init(struct ::wl_client *client, int id, int version);
        void init(struct ::wl_display *display, int version);
        void init(struct ::wl_resource *resource);

        Resource *add(struct ::wl_client *client, int version);
        Resource *add(struct ::wl_client *client, int id, int version);
        Resource *add(struct wl_list *resource_list, struct ::wl_client *client, int id, int version);

        Resource *resource() { return m_resource; }
        const Resource *resource() const { return m_resource; }

        QMultiMap<struct ::wl_client*, Resource*> resourceMap() { return m_resource_map; }
        const QMultiMap<struct ::wl_client*, Resource*> resourceMap() const { return m_resource_map; }

        bool isGlobal() const { return m_global != 0; }
        bool isResource() const { return m_resource != 0; }

        static const struct ::wl_interface *interface();
        static QByteArray interfaceName() { return interface()->name; }
        static int interfaceVersion() { return interface()->version; }


        void send_clicked();
        void send_clicked(struct ::wl_resource *resource);

    protected:
        virtual Resource *example_local_object_allocate();

        virtual void example_local_object_bind_resource(Resource *resource);
        virtual void example_local_object_destroy_resource(Resource *resource);

        virtual void example_local_object_set_text(Resource *resource, const QString &text);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::qt_example_local_object_interface m_qt_example_local_object_interface;

        static void handle_set_text(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *text);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
