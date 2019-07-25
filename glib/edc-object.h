#ifndef __EDC_OBJECT_H__
#define __EDC_OBJECT_H__

#include <glib.h>

#ifdef __cplusplus
extern "C" {
#endif 


typedef struct _EdcObject EdcObject;
struct _EdcObject
{
	gint ref_count;
	GDestroyNotify finalize;
};


static inline gpointer edc_object_alloc(GDestroyNotify finalize, gint obj_size)
{
	EdcObject *obj;

	obj = g_malloc(obj_size);
	if ( !obj )
		return NULL;

	obj->ref_count =1;
	obj->finalize = finalize;

	return obj;
}

static inline gpointer edc_object_ref(gpointer obj)
{
	EdcObject *object = obj;

	if ( object )
		g_atomic_int_inc(&gobject->ref_count);

	return object;
}


static inline void edc_object_unref(gpointer obj)
{
	EdcObject *object = obj;

	if ( !obj )
		return;

	if ( g_atomic_int_dec_and_test(&object->ref_count) ) 
	{
		if ( object->finalize )
			object->finalize(object);

		g_free(object);
	}
}


#ifdef __cplusplus 
}
#endif 

#endif /* __EDC_OBJECT_H__ */
