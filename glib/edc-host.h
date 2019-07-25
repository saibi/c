#ifndef __EDC_HOST_H__
#define __EDC_HOST_H__

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _EdcHost EdcHost;
struct _EdcHost
{
	gchar *name;
	gchar *address;
	gint port;
	gchar *user;
	gchar *password;

	gint ref_count;
};

EdcHost *edc_host_new(void);
EdcHost *edc_host_ref(EdcHost *host);
void edc_host_unref(EdcHost *host);

#ifdef __cplusplus
}
#endif

#endif 
