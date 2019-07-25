#ifndef __EDC_HOST_H__
#define __EDC_HOST_H__

#include <glib-object.h>

G_BEGIN_DECLS

#define EDC_TYPE_HOST (edc_host_get_type())
#define EDC_HOST(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), EDC_TYPE_HOST, EdcHost)) 
#define EDC_HOST_CLASS(obj) (G_TYPE_CHECK_CLASS_CAST ((obj), EDC_TYPE_HOST, EdcHostClass))
#define EDC_IS_HOST(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), EDC_TYPE_HOST))
#define EDC_IS_HOST_CLASS(obj) (G_TYPE_CHECK_CLASS_TYPE((obj), EDC_TYPE_HOST))
#define EDC_GET_HOST_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), EDC_TYPE_HOST, EdcHostClass))

typedef struct _EdcHostClass EdcHostClass;
typedef struct _EdcHost EdcHost;
struct _EdcHost
{
	GObject parent;

	gchar *name;
	gchar *address;
	gint port;
	gchar *user;
	gchar *password;
};

struct _EdcHostClass
{
	GObjectClass parent_class;
};


GType edc_host_get_type(void) G_GNUC_CONST;
EdcHost *edc_host_new (void);

G_END_DECLS

#endif  /* __EDC_HOST_H__ */
