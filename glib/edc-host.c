#include "edc-host.h"

EdcHost *edc_host_new(void)
{
	EdcHost *host;

	host = g_new0(EdcHost, 1);

	if (!host)
		return NULL;

	host->ref_count = 1;

	return host;
}

static void edc_host_destroy(EdcHost *host)
{
	g_return_if_fail( host != NULL );

	g_free(host->name);
	g_free(host->address);
	g_free(host->user);
	g_free(host->password);
	g_free(host);
}

EdcHost * edc_host_ref(EdcHost *host)
{
	g_return_val_if_fail( host != NULL );
	
	g_atomic_int_inc(&host->ref_count);

	return host;
}

void edc_host_unref(EdcHost * host)
{
	g_return_if_fail(host != NULL);

	if ( g_atomic_int_dec_and_test(&host->ref_count))
		edc_host_destroy(host);

}
