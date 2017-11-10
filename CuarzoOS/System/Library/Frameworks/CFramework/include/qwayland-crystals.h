#ifndef QT_WAYLAND_CRYSTALS
#define QT_WAYLAND_CRYSTALS

#include "wayland-crystals-client-protocol.h"
#include <QByteArray>
#include <QString>

QT_BEGIN_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wmissing-field-initializers")

namespace QtWayland {
    class  crystals
    {
    public:
        crystals(struct ::wl_registry *registry, int id, int version);
        crystals(struct ::crystals *object);
        crystals();

        virtual ~crystals();

        void init(struct ::wl_registry *registry, int id, int version);
        void init(struct ::crystals *object);

        struct ::crystals *object() { return m_crystals; }
        const struct ::crystals *object() const { return m_crystals; }

        bool isInitialized() const;

        static const struct ::wl_interface *interface();

        void register_surface(struct ::wl_surface *surface);
        void role(struct ::wl_surface *surface, uint32_t role);
        void position(struct ::wl_surface *surface, int32_t x, int32_t y);
        void opacity(struct ::wl_surface *surface, uint32_t opacity);
        void minimize(struct ::wl_surface *surface, uint32_t minimize);
        void maximize(struct ::wl_surface *surface, uint32_t maximize, uint32_t workspace);
        void enable_blur(struct ::wl_surface *surface, struct ::wl_surface *blur_surface, uint32_t enabled);
        void register_blur(struct ::wl_surface *surface, struct ::wl_surface *blur_surface);
        void configure_blur(struct ::wl_surface *surface, struct ::wl_surface *blur_surface, uint32_t tint, int32_t x, int32_t y, uint32_t w, uint32_t h);

    protected:
        virtual void crystals_moved(struct ::wl_surface *surface, int32_t x, int32_t y);
        virtual void crystals_resized(struct ::wl_surface *surface, uint32_t w, uint32_t h);

    private:
        void init_listener();
        static const struct crystals_listener m_crystals_listener;
        static void handle_moved(
            void *data,
            struct ::crystals *object,
            struct ::wl_surface *surface,
            int32_t x,
            int32_t y);
        static void handle_resized(
            void *data,
            struct ::crystals *object,
            struct ::wl_surface *surface,
            uint32_t w,
            uint32_t h);
        struct ::crystals *m_crystals;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
