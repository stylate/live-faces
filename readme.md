Proof-of-concept project on live streams, tinkering with AWS and deep learning.

** Consider reading the following [issue](https://github.com/awslabs/amazon-kinesis-video-streams-producer-sdk-cpp/issues/92) in regards to correctly installing the GStreamer plugin for AWS (kvssink). At this time (6/21/18), the GStreamer plugin in the producer SDK (C++) had segmentation faults when running gst-launch-1.0 and I had to integrate my own installation of GStreamer with kvssink.

## Dependencies:
    * AWS Kinesis
    * AWS Rekognition
    * Gstreamer
    * AWS Producer SDK (for C++)
    * Node.js
    * pm2

Run the following after setting up all appropriate dependencies:

`gst-launch-1.0 -v souphttpsrc location="<HLS m3u8 link>" ! hlsdemux ! tsdemux ! h264parse ! video/x-h264,alignment=au,stream-format=avc ! kvssink stream-name="<insert name>" storage-size=512 access-key="<insert access key>" secret-key="<insert secret key>"`

Afterwards, the target stream will be broadcasted onto AWS Kinesis.

## Goals:
    * Introduce scalability through pm2 and Node.js.
    * Develop a series of collections for AWS Rekognition.

## Directions:
    1. Pipe the target .m3u8 stream to KVS through gstreamer.
    2. Set the appropriate environment variables `KDS_NAME`, `COLLECTION`, `KVSARN`, `KDSARN`, and `KINESIS_ROLE`.
        - `KDS_NAME` represents the name for the Kinesis data stream.
        - `COLLECTION` represents the collection that will be in use for AWS Rekognition.
        - `KVSARN` represents the ARN for the select Kinesis Video Stream.
        - `KDSARN` represents the ARN for the select Kinesis Data Stream.
        - `KINESIS_ROLE` represents the IAM role that has full access to S3, Kinesis, and Rekognition.
    3. Run `stream.py`, which will then do image recognition on the stream based on its collection from S3.
    4. Retrieve the data from Kinesis data streams and log onto Splunk.


