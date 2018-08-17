import boto3, json
import os

'''
Notes:
    1. Create a Rekognition client. Create a stream processor through the client.
    2. Start a stream processor based on a specific stream from Kinesis.
    3. Pipeline a stream to Kinesis video.
    3. Begin face detection from processor.
    4. Read in Kinesis data stream.
Read in Kinesis data stream.
start_label_detection only works for videos in S3
PutMedia API only works for videos that are already in container format (.mkv)
'''

def get_data(stream_name):
    '''
    Receives record(s) from a Kinesis data stream. Passes in a parameter STREAM_NAME,
    which denotes the Kinesis data stream name.
    '''
    kinesis = boto3.client('kinesis')
    data_stream = kinesis.describe_stream(StreamName=stream_name)
    shards = data_stream['StreamDescription']['Shards']
    shard_ids = [shard['ShardId'] for shard in shards]
    iter_response = kinesis.get_shard_iterator(StreamName=stream_name, 
                            ShardId=shard_ids[0], ShardIteratorType='TRIM_HORIZON')
    shard_iterator = iter_response['ShardIterator']
    records = kinesis.get_records(ShardIterator=shard_iterator)
    return records

def video_stream():
    kinesis_video = boto3.client('kinesisvideo')

def stream_processor():
    data_stream = "streamer"
    video_stream = "hellopeppy"
    client = boto3.client('rekognition')
    response = client.create_stream_processor(
        Input={
            'KinesisVideoStream': {
                'Arn': os.environ['KVSARN']
            }
        },
        Output={
            'KinesisDataStream': {
                'Arn': os.environ['KDSARN']
            }
        },
        Name=video_stream,
        Settings={
            'FaceSearch': {
                'CollectionId': os.environ['FOX'],
                'FaceMatchThreshold': 85
            }
        },
        RoleArn=os.environ['KINESIS_ROLE']
    )
    response = client.start_stream_processor(Name=video_stream)

    
if __name__ == '__main__':
    stream_processor()
    # PutMedia API
    records = get_data(os.environ['KDS_NAME'])
    print(records)

