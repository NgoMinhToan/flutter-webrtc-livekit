#if TARGET_OS_IPHONE
#import <Flutter/Flutter.h>
#elif TARGET_OS_OSX
#import <FlutterMacOS/FlutterMacOS.h>
#endif

#import <Foundation/Foundation.h>
#import <LiveKitWebRTC/LiveKitWebRTC.h>

@class FlutterRTCVideoRenderer;
@class FlutterRTCFrameCapturer;

void postEvent(FlutterEventSink _Nonnull sink, id _Nullable event);

typedef void (^CompletionHandler)(void);

typedef void (^CapturerStopHandler)(CompletionHandler _Nonnull handler);

@interface FlutterWebRTCPlugin : NSObject <FlutterPlugin,
                                           LKRTCPeerConnectionDelegate,
                                           FlutterStreamHandler
#if TARGET_OS_OSX
                                           ,
                                           RTCDesktopMediaListDelegate,
                                           RTCDesktopCapturerDelegate
#endif
                                           >

@property(nonatomic, strong) LKRTCPeerConnectionFactory* _Nullable peerConnectionFactory;
@property(nonatomic, strong) NSMutableDictionary<NSString*, LKRTCPeerConnection*>* _Nullable peerConnections;
@property(nonatomic, strong) NSMutableDictionary<NSString*, LKRTCMediaStream*>* _Nullable localStreams;
@property(nonatomic, strong) NSMutableDictionary<NSString*, LKRTCMediaStreamTrack*>* _Nullable localTracks;
@property(nonatomic, strong) NSMutableDictionary<NSNumber*, FlutterRTCVideoRenderer*>* _Nullable renders;
@property(nonatomic, strong)
    NSMutableDictionary<NSString*, CapturerStopHandler>* _Nullable videoCapturerStopHandlers;

@property(nonatomic, strong) NSMutableDictionary<NSString*, LKRTCFrameCryptor*>* _Nullable frameCryptors;
@property(nonatomic, strong) NSMutableDictionary<NSString*, LKRTCFrameCryptorKeyProvider*>* _Nullable keyProviders;

#if TARGET_OS_IPHONE
@property(nonatomic, retain) UIViewController* _Nullable viewController; /*for broadcast or ReplayKit */
#endif

@property(nonatomic, strong) FlutterEventSink _Nullable eventSink;
@property(nonatomic, strong) NSObject<FlutterBinaryMessenger>* _Nonnull messenger;
@property(nonatomic, strong) LKRTCCameraVideoCapturer* _Nullable videoCapturer;
@property(nonatomic, strong) FlutterRTCFrameCapturer* _Nullable frameCapturer;
@property(nonatomic, strong) AVAudioSessionPort _Nullable preferredInput;

@property(nonatomic) BOOL _usingFrontCamera;
@property(nonatomic) NSInteger _lastTargetWidth;
@property(nonatomic) NSInteger _lastTargetHeight;
@property(nonatomic) NSInteger _lastTargetFps;

- (LKRTCMediaStream* _Nullable)streamForId:(NSString* _Nonnull)streamId peerConnectionId:(NSString* _Nonnull)peerConnectionId;
- (LKRTCRtpTransceiver* _Nullable)getRtpTransceiverById:(LKRTCPeerConnection* _Nonnull)peerConnection Id:(NSString* _Nonnull)Id;
- (NSDictionary* _Nullable)mediaStreamToMap:(LKRTCMediaStream* _Nonnull)stream ownerTag:(NSString* _Nonnull)ownerTag;
- (NSDictionary* _Nullable)mediaTrackToMap:(LKRTCMediaStreamTrack* _Nonnull)track;
- (NSDictionary* _Nullable)receiverToMap:(LKRTCRtpReceiver* _Nonnull)receiver;
- (NSDictionary* _Nullable)transceiverToMap:(LKRTCRtpTransceiver* _Nonnull)transceiver;

- (BOOL)hasLocalAudioTrack;
- (void)ensureAudioSession;
- (void)deactiveRtcAudioSession;

- (LKRTCRtpReceiver* _Nullable)getRtpReceiverById:(LKRTCPeerConnection* _Nonnull)peerConnection Id:(NSString* _Nonnull)Id;
- (LKRTCRtpSender* _Nullable)getRtpSenderById:(LKRTCPeerConnection* _Nonnull)peerConnection Id:(NSString* _Nonnull)Id;

@end
