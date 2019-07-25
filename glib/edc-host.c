#include "edc-host.h"

static void edc_host_finalize(gpointer obj)
{
	EdcHost *host = obj;

	g_free(host->name);
	g_free(host->address);
	g_free(host->user);
	g_free(host->password);
}

EdcHost *edc_host_new(void)
{
	EdcHost *host;

	host = edc_object_alloc(edc_host_finalize, sizeof(EdcHost));

	if (!host)
		return NULL;

	host->name = NULL;
	host->address = NULL;
	host->user = NULL;
	host->password = NULL;

	return host;
}

