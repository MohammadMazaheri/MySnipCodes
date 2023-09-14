#ifndef VIDEOSERVER_H
#define VIDEOSERVER_H

#include <gst/gst.h>
#include <gst/video/video.h>
#include <gst/gstpad.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class VideoServer
{
public:
    VideoServer();
    ~VideoServer();

private:
    GstElement *m_pipeline;
    GstElement *m_sink;
    GstPad     *m_padSink;

};

#endif // VIDEOSERVER_H
