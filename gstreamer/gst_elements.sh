#!/bin/bash 

# bins
#gst-launch-1.0 uridecodebin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm ! videoconvert ! autovideosink
#gst-launch-1.0 uridecodebin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm ! audioconvert ! autoaudiosink
#gst-launch-1.0 souphttpsrc location=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm ! decodebin ! autovideosink


# file i/o
#gst-launch-1.0 filesrc location=/home/saibi/saibi-mini9/hdd/g500/movie/Close.2019.1080p.NF.WEB-DL.MkvCage.ws.mkv ! decodebin ! autovideosink
#gst-launch-1.0 audiotestsrc ! vorbisenc ! oggmux ! filesink location=/tmp/test.ogg


# network

#gst-launch-1.0 souphttpsrc location=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm ! decodebin ! autoaudiosink


#gst-launch-1.0 videotestsrc ! videoconvert ! autovideosink
#gst-launch-1.0 audiotestsrc ! audioconvert ! autoaudiosink


# video adaptor

#gst-launch-1.0 videotestsrc ! video/x-raw,framerate=30/1 ! videorate ! video/x-raw,framerate=2/1 ! videoconvert ! autovideosink

# gst-launch-1.0 uridecodebin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm ! videoscale ! video/x-raw,width=1920,height=1080 ! videoconvert ! autovideosink


# audio adaptor
#gst-launch-1.0 audiotestsrc ! audioconvert ! autoaudiosink

#gst-launch-1.0 uridecodebin uri=https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm ! audioresample ! audio/x-raw-float,rate=4000 ! audioconvert ! autoaudiosink 






#gst-launch-1.0 audiotestsrc ! tee name=t ! queue ! audioconvert ! autoaudiosink t. ! queue ! wavescope ! videoconvert ! autovideosink



#gst-launch-1.0 videotestsrc ! video/x-raw,format=GRAY8 ! videoconvert ! autovideosink
