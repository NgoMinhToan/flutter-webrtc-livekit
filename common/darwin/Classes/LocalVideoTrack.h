#import <WebRTC/WebRTC.h>
#import "LocalTrack.h"
#import "VideoProcessingAdapter.h"

@interface LocalVideoTrack : NSObject<LocalTrack>

-(instancetype)initWithTrack:(RTCVideoTrack *)track;

-(instancetype)initWithTrack:(RTCVideoTrack *)track
             videoProcessing:(VideoProcessingAdapter *)processing;

@property (nonatomic, strong) RTCVideoTrack *videoTrack;
@property (nonatomic, strong) VideoProcessingAdapter *processing;

@end
