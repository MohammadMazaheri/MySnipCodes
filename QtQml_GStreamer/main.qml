import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtMultimedia 5.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Qml with gst-pipeline")

    Item {
        anchors.fill: parent
        Rectangle
        {
            id:rect1
            anchors.fill: parent
            color: "blue"

            /** @note It's necessary Camera be commented when MediaPlayer wants to work and vice versa. */
            //Camera {
            //    id: camera
            //}

            MediaPlayer {
                id: player
                /** @note Playing video test source of GStreamer: */
                //source: "gst-pipeline: videotestsrc pattern=ball ! video/x-raw, format=I420, framerate=50/2, width=640, height=480 ! qtvideosink"
                /** @note Playing video source such as laptop camera like the Qml Camera: */
                //source: "gst-pipeline: v4l2src device=/dev/video0 ! videoconvert ! qtvideosink"
                /** @note Getting and playing camera stream from network as multicast: */
                source: "gst-pipeline: udpsrc multicast-group=224.0.0.0 port=5000 auto-multicast=true multicast-iface=lo ! application/x-rtp ! rtph264depay ! h264parse ! openh264dec ! qtvideosink sync=false"
                autoPlay: true
            }

            VideoOutput {
                id: videoout
                anchors.fill: parent
                //source: camera
                source: player
            }
        }
    }
}
