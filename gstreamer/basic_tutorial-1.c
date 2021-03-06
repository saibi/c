#include <gst/gst.h>

int main(int argc, char *argv[])
{
	GstElement *pipeline;
	GstBus *bus;
	GstMessage *msg;


	/* Initialize Gstreamer */
	gst_init(&argc, &argv);

	/* build the pipeline */
	//pipeline = gst_parse_launch("playbin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);
	pipeline = gst_parse_launch("playbin uri=file:///home/saibi/saibi-mini9/hdd/w64/movie/201905/Bad.Police.2019.FRENCH.720p.WEB.H264-EXTREME.mkv", NULL);

	/* start playing */
	gst_element_set_state(pipeline, GST_STATE_PLAYING);

	/* wait ultil error or EOS */
	bus = gst_element_get_bus(pipeline);
	msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE, GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

	/* free resources */
	if ( msg != NULL )
		gst_message_unref(msg);

	gst_object_unref(bus);
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);

	return 0;
}
	
