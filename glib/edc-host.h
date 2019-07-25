#ifndef __EDC_HOST_H__
#define __EDC_HOST_H__

#include "edc-object.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _EdcHost EdcHost;
struct _EdcHost
{
	EdcObject parent;

	gchar *name;
	gchar *address;
	gint port;
	gchar *user;
	gchar *password;
};

EdcHost *edc_host_new(void);

#ifdef __cplusplus
}
#endif

#endif  /* __EDC_HOST_H__ */
