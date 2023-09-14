#include "videoserver.h"

static GstPadProbeReturn onFrameData (GstPad *pad, GstPadProbeInfo *info, gpointer data)
{
    GstMapInfo map;
    guint8 *ptr = nullptr;
    GstBuffer *buffer = nullptr;

    /* Making a writable buffer - It cannot be copied and is used more than once) */
    buffer = GST_PAD_PROBE_INFO_BUFFER (info);
    buffer = gst_buffer_make_writable (buffer);
    if (buffer != NULL)
        if (gst_buffer_map (buffer, &map, GST_MAP_WRITE /*GST_MAP_READWRITE*/)) {
            ptr = (guint8 *) map.data;

            /*CAPS*/
            GstCaps *caps = gst_pad_query_caps(pad, NULL);
            string strCaps = gst_caps_to_string(caps);

            /*Type your code here ...*/

            gst_buffer_unmap (buffer, &map);
            //gst_buffer_unref (buffer);
        }
    return GST_PAD_PROBE_OK;
}

VideoServer::VideoServer()
{
    gst_init(nullptr, nullptr);

    /** @note Making 2 virtual sources from a phisical source: */
    //string pipe = "v4l2src device=/dev/video0 ! tee name=t t. ! queue ! v4l2sink device=/dev/video1 t. ! queue ! v4l2sink device=/dev/video2 &";
    /** @note Playing video source such as laptop camera: */
    //string pipe = "v4l2src device=/dev/video0 ! videoconvert ! xvimagesink name=sink &";
    /** @note Pumping camera stream to network as multicast: */
    string pipe = "v4l2src device=/dev/video0 ! videoconvert ! openh264enc bitrate=1000000 ! rtph264pay ! udpsink name=sink host=224.0.0.0 port=5000 auto-multicast=true multicast-iface=lo force-ipv4=true sync=false";
    cout<<endl<<pipe<<endl;

    m_pipeline = gst_parse_launch (pipe.data(), nullptr);
    if (m_pipeline == nullptr)
    {
        g_print ("There is an error on pipeline! \n");
        return;
    }

    m_sink = gst_bin_get_by_name (GST_BIN (m_pipeline), "sink");
    m_padSink = gst_element_get_static_pad (m_sink, "sink");
    gst_pad_add_probe(m_padSink, GST_PAD_PROBE_TYPE_BUFFER,static_cast<GstPadProbeCallback>(onFrameData), NULL, NULL);

    gst_element_set_state (m_pipeline, GST_STATE_PLAYING);
    g_print ("The video server has been started. \n");
}

VideoServer::~VideoServer()
{
    gst_element_set_state (m_pipeline, GST_STATE_NULL);
    gst_object_unref (m_pipeline);
}
