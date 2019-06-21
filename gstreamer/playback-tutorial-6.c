// gst-launch-1.0 playbin uri=file:///home/saibi/saibi-mini9/hdd/ss25/music/Billboard\ Hot\ 100\ Singles\ Chart\ \(01.06.2019\)\ Mp3\ 320kbps\ Songs\ \[PMEDIA\]/83.\ Brett\ Eldredge\ -\ Love\ Someone.mp3 flags=11 vis-plugin=goom


#include <gst/gst.h>

/* playbin flags */
typedef enum {
	GST_PLAY_FLAG_VIS = ( 1 << 3 ) /* enable rendering of visualizations when there is no video stream */
} GstPlayFlags;


/* return true if this is a visualization element */
static gboolean filter_vis_features(GstPluginFeature *feature, gpointer data)
{
	GstElementFactory *factory;

	if ( !GST_IS_ELEMENT_FACTORY(feature) )
		return FALSE;

	factory = GST_ELEMENT_FACTORY(feature);
	if ( ! g_strrstr(gst_element_factory_get_klass(factory), "Visualization"))
		return FALSE;


	return TRUE;
}



int main(int argc, char *argv[])
{
	GstElement *pipeline, *vis_plugin;
	GstBus *bus;
	GstMessage *msg;
	GList *list, *walk;
	GstElementFactory *selected_factory = NULL;
	guint flags;


	gst_init(&argc, &argv);


	/* get a list of all visualization plugins */
	list = gst_registry_feature_filter(gst_registry_get(), filter_vis_features, FALSE, NULL);

	/* print their names */
	g_print("Available visualization plugins:\n");
	for  ( walk = list ; walk != NULL; walk = g_list_next(walk) )
	{
		const gchar *name;
		GstElementFactory *factory;

		factory = GST_ELEMENT_FACTORY(walk->data);
		name = gst_element_factory_get_longname(factory);
		g_print("  %s\n", name);


		if ( selected_factory == NULL || g_str_has_prefix(name, "GOOM") )
		{
			selected_factory = factory;
		}
	}


	/* Don't use the factory if it's still empty */
	/* e.g. no visualization plugins found */

	if ( !selected_factory )
	{
		g_print("No visualization plugins found!\n");
		return -1;
	}


	/* we have now selected a factory for the visualization element */
	g_print("Selected '%s'\n", gst_element_factory_get_longname(selected_factory));
	vis_plugin = gst_element_factory_create(selected_factory, NULL);
	if (!vis_plugin)
		return -1;

	/* build the pipeline */
	pipeline = gst_parse_launch("playbin uri=http://radio.hbr1.com:19800/ambient.ogg", NULL);

	/* set the visualization flag */
	g_object_get(pipeline, "flags", &flags, NULL);
	flags |= GST_PLAY_FLAG_VIS;
	g_object_set(pipeline, "flags", flags, NULL);

	/* set vis pluging for playbin */
	g_object_set(pipeline, "vis-plugin", vis_plugin, NULL);

	/* start playing */
	gst_element_set_state(pipeline, GST_STATE_PLAYING);

	/* wait untill error of EOS */
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	/* free resources */
	if ( msg != NULL )
		gst_message_unref(msg);

	gst_plugin_feature_list_free(list);
	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);

	return 0;

}
