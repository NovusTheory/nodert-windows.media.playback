  
Size = (function () {
  var cls = function Size() {
    };
  return cls;
}) ();
exports.Size = Size;


  
Rect = (function () {
  var cls = function Rect() {
    };
  return cls;
}) ();
exports.Rect = Rect;


  
MediaTimeRange = (function () {
  var cls = function MediaTimeRange() {
      this.start = new Number();
      this.end = new Number();
    };
  return cls;
}) ();
exports.MediaTimeRange = MediaTimeRange;


  
Quaternion = (function () {
  var cls = function Quaternion() {
      this.x = new Number();
      this.y = new Number();
      this.z = new Number();
      this.w = new Number();
    };
  return cls;
}) ();
exports.Quaternion = Quaternion;


_MediaPlayerState = function () {
  this.closed = 0;
  this.opening = 1;
  this.buffering = 2;
  this.playing = 3;
  this.paused = 4;
  this.stopped = 5;
}
exports.MediaPlayerState = new _MediaPlayerState();

_MediaPlaybackState = function () {
  this.none = 0;
  this.opening = 1;
  this.buffering = 2;
  this.playing = 3;
  this.paused = 4;
}
exports.MediaPlaybackState = new _MediaPlaybackState();

_MediaPlayerError = function () {
  this.unknown = 0;
  this.aborted = 1;
  this.networkError = 2;
  this.decodingError = 3;
  this.sourceNotSupported = 4;
}
exports.MediaPlayerError = new _MediaPlayerError();

_MediaPlayerAudioCategory = function () {
  this.other = 0;
  this.communications = 1;
  this.alerts = 2;
  this.soundEffects = 3;
  this.gameEffects = 4;
  this.gameMedia = 5;
  this.gameChat = 6;
  this.speech = 7;
  this.movie = 8;
  this.media = 9;
}
exports.MediaPlayerAudioCategory = new _MediaPlayerAudioCategory();

_MediaPlayerAudioDeviceType = function () {
  this.console = 0;
  this.multimedia = 1;
  this.communications = 2;
}
exports.MediaPlayerAudioDeviceType = new _MediaPlayerAudioDeviceType();

_StereoscopicVideoRenderMode = function () {
  this.mono = 0;
  this.stereo = 1;
}
exports.StereoscopicVideoRenderMode = new _StereoscopicVideoRenderMode();

_MediaCommandEnablingRule = function () {
  this.auto = 0;
  this.always = 1;
  this.never = 2;
}
exports.MediaCommandEnablingRule = new _MediaCommandEnablingRule();

_MediaPlaybackSessionVideoConstrictionReason = function () {
  this.none = 0;
  this.virtualMachine = 1;
  this.unsupportedDisplayAdapter = 2;
  this.unsignedDriver = 3;
  this.frameServerEnabled = 4;
  this.outputProtectionFailed = 5;
  this.unknown = 6;
}
exports.MediaPlaybackSessionVideoConstrictionReason = new _MediaPlaybackSessionVideoConstrictionReason();

_SphericalVideoProjectionMode = function () {
  this.spherical = 0;
  this.flat = 1;
}
exports.SphericalVideoProjectionMode = new _SphericalVideoProjectionMode();

_MediaPlaybackItemErrorCode = function () {
  this.none = 0;
  this.aborted = 1;
  this.networkError = 2;
  this.decodeError = 3;
  this.sourceNotSupportedError = 4;
  this.encryptionError = 5;
}
exports.MediaPlaybackItemErrorCode = new _MediaPlaybackItemErrorCode();

_FailedMediaStreamKind = function () {
  this.unknown = 0;
  this.audio = 1;
  this.video = 2;
}
exports.FailedMediaStreamKind = new _FailedMediaStreamKind();

_TimedMetadataTrackPresentationMode = function () {
  this.disabled = 0;
  this.hidden = 1;
  this.applicationPresented = 2;
  this.platformPresented = 3;
}
exports.TimedMetadataTrackPresentationMode = new _TimedMetadataTrackPresentationMode();

_MediaBreakInsertionMethod = function () {
  this.interrupt = 0;
  this.replace = 1;
}
exports.MediaBreakInsertionMethod = new _MediaBreakInsertionMethod();

_MediaPlaybackItemChangedReason = function () {
  this.initialItem = 0;
  this.endOfStream = 1;
  this.error = 2;
  this.appRequested = 3;
}
exports.MediaPlaybackItemChangedReason = new _MediaPlaybackItemChangedReason();

_AutoLoadedDisplayPropertyKind = function () {
  this.none = 0;
  this.musicOrVideo = 1;
  this.music = 2;
  this.video = 3;
}
exports.AutoLoadedDisplayPropertyKind = new _AutoLoadedDisplayPropertyKind();

PlaybackMediaMarker = (function () {
  var cls = function PlaybackMediaMarker() {
    this.mediaMarkerType = new String();
    this.text = new String();
    this.time = new Number();
  };
  
var cls = function PlaybackMediaMarker(value) {
      this.mediaMarkerType = new String();
      this.text = new String();
      this.time = new Number();
};

var cls = function PlaybackMediaMarker(value, mediaMarketType, text) {
      this.mediaMarkerType = new String();
      this.text = new String();
      this.time = new Number();
};


  return cls;
}) ();
exports.PlaybackMediaMarker = PlaybackMediaMarker;

PlaybackMediaMarkerSequence = (function () {
  var cls = function PlaybackMediaMarkerSequence() {
    this.size = new Number();
  };
  

  cls.prototype.insert = function insert(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="PlaybackMediaMarker">A param.</param>
    /// </signature>
  }


  cls.prototype.clear = function clear() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.PlaybackMediaMarkerSequence = PlaybackMediaMarkerSequence;

MediaPlayerFailedEventArgs = (function () {
  var cls = function MediaPlayerFailedEventArgs() {
    this.error = new MediaPlayerError();
    this.errorMessage = new String();
    this.extendedErrorCode = new Number();
  };
  

  return cls;
}) ();
exports.MediaPlayerFailedEventArgs = MediaPlayerFailedEventArgs;

MediaPlayerRateChangedEventArgs = (function () {
  var cls = function MediaPlayerRateChangedEventArgs() {
    this.newRate = new Number();
  };
  

  return cls;
}) ();
exports.MediaPlayerRateChangedEventArgs = MediaPlayerRateChangedEventArgs;

PlaybackMediaMarkerReachedEventArgs = (function () {
  var cls = function PlaybackMediaMarkerReachedEventArgs() {
    this.playbackMediaMarker = new PlaybackMediaMarker();
  };
  

  return cls;
}) ();
exports.PlaybackMediaMarkerReachedEventArgs = PlaybackMediaMarkerReachedEventArgs;

MediaPlayerDataReceivedEventArgs = (function () {
  var cls = function MediaPlayerDataReceivedEventArgs() {
    this.data = new Object();
  };
  

  return cls;
}) ();
exports.MediaPlayerDataReceivedEventArgs = MediaPlayerDataReceivedEventArgs;

MediaPlayer = (function () {
  var cls = function MediaPlayer() {
    this.volume = new Number();
    this.position = new Number();
    this.playbackRate = new Number();
    this.isLoopingEnabled = new Boolean();
    this.isMuted = new Boolean();
    this.autoPlay = new Boolean();
    this.currentState = new MediaPlayerState();
    this.naturalDuration = new Number();
    this.playbackMediaMarkers = new PlaybackMediaMarkerSequence();
    this.isProtected = new Boolean();
    this.bufferingProgress = new Number();
    this.canPause = new Boolean();
    this.canSeek = new Boolean();
    this.audioDeviceType = new MediaPlayerAudioDeviceType();
    this.audioCategory = new MediaPlayerAudioCategory();
    this.systemMediaTransportControls = new Object();
    this.timelineControllerPositionOffset = new Number();
    this.timelineController = new Object();
    this.stereoscopicVideoRenderMode = new StereoscopicVideoRenderMode();
    this.realTimePlayback = new Boolean();
    this.audioDevice = new Object();
    this.audioBalance = new Number();
    this.commandManager = new MediaPlaybackCommandManager();
    this.breakManager = new MediaBreakManager();
    this.playbackSession = new MediaPlaybackSession();
    this.isVideoFrameServerEnabled = new Boolean();
    this.audioStateMonitor = new Object();
    this.protectionManager = new Object();
    this.source = new IMediaPlaybackSource();
  };
  

  cls.prototype.addAudioEffect = function addAudioEffect(activatableClassId, effectOptional, configuration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="effectOptional" type="Boolean">A param.</param>
    /// <param name="configuration" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.removeAllEffects = function removeAllEffects() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.close = function close() {
}


  cls.prototype.stepForwardOneFrame = function stepForwardOneFrame() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.stepBackwardOneFrame = function stepBackwardOneFrame() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.getAsCastingSource = function getAsCastingSource() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.setSurfaceSize = function setSurfaceSize(size) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="size" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.getSurface = function getSurface(compositor) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="compositor" type="Object">A param.</param>
    /// <returns type="MediaPlayerSurface" />
    /// </signature>
    return new MediaPlayerSurface();
  }


  cls.prototype.addVideoEffect = function addVideoEffect(activatableClassId, effectOptional, effectConfiguration) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="activatableClassId" type="String">A param.</param>
    /// <param name="effectOptional" type="Boolean">A param.</param>
    /// <param name="effectConfiguration" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.copyFrameToVideoSurface = function copyFrameToVideoSurface(destination) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destination" type="Object">A param.</param>
    /// </signature>
  }

cls.prototype.copyFrameToVideoSurface = function copyFrameToVideoSurface(destination, targetRectangle) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destination" type="Object">A param.</param>
    /// <param name="targetRectangle" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.copyFrameToStereoscopicVideoSurfaces = function copyFrameToStereoscopicVideoSurfaces(destinationLeftEye, destinationRightEye) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destinationLeftEye" type="Object">A param.</param>
    /// <param name="destinationRightEye" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.renderSubtitlesToSurface = function renderSubtitlesToSurface(destination) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destination" type="Object">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }

cls.prototype.renderSubtitlesToSurface = function renderSubtitlesToSurface(destination, targetRectangle) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="destination" type="Object">A param.</param>
    /// <param name="targetRectangle" type="Object">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.play = function play() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.pause = function pause() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.prototype.setUriSource = function setUriSource(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.setFileSource = function setFileSource(file) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="file" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.setStreamSource = function setStreamSource(stream) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="stream" type="Object">A param.</param>
    /// </signature>
  }


  cls.prototype.setMediaSource = function setMediaSource(source) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="Object">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlayer = MediaPlayer;

MediaBreakManager = (function () {
  var cls = function MediaBreakManager() {
    this.currentBreak = new MediaBreak();
    this.playbackSession = new MediaPlaybackSession();
  };
  

  cls.prototype.playBreak = function playBreak(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="MediaBreak">A param.</param>
    /// </signature>
  }


  cls.prototype.skipCurrentBreak = function skipCurrentBreak() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaBreakManager = MediaBreakManager;

MediaPlaybackCommandManager = (function () {
  var cls = function MediaPlaybackCommandManager() {
    this.isEnabled = new Boolean();
    this.autoRepeatModeBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.fastForwardBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.mediaPlayer = new MediaPlayer();
    this.nextBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.pauseBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.playBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.positionBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.previousBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.rateBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.rewindBehavior = new MediaPlaybackCommandManagerCommandBehavior();
    this.shuffleBehavior = new MediaPlaybackCommandManagerCommandBehavior();
  };
  

    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlaybackCommandManager = MediaPlaybackCommandManager;

MediaPlaybackSession = (function () {
  var cls = function MediaPlaybackSession() {
    this.stereoscopicVideoPackingMode = new Number();
    this.position = new Number();
    this.playbackRate = new Number();
    this.normalizedSourceRect = new Object();
    this.bufferingProgress = new Number();
    this.canPause = new Boolean();
    this.canSeek = new Boolean();
    this.downloadProgress = new Number();
    this.isProtected = new Boolean();
    this.mediaPlayer = new MediaPlayer();
    this.naturalDuration = new Number();
    this.naturalVideoHeight = new Number();
    this.naturalVideoWidth = new Number();
    this.playbackState = new MediaPlaybackState();
    this.isMirroring = new Boolean();
    this.sphericalVideoProjection = new MediaPlaybackSphericalVideoProjection();
    this.playbackRotation = new Number();
  };
  

  cls.prototype.getSeekableRanges = function getSeekableRanges() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.isSupportedPlaybackRateRange = function isSupportedPlaybackRateRange(rate1, rate2) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="rate1" type="Number">A param.</param>
    /// <param name="rate2" type="Number">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getOutputDegradationPolicyState = function getOutputDegradationPolicyState() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="MediaPlaybackSessionOutputDegradationPolicyState" />
    /// </signature>
    return new MediaPlaybackSessionOutputDegradationPolicyState();
  }


  cls.prototype.getBufferedRanges = function getBufferedRanges() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getPlayedRanges = function getPlayedRanges() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlaybackSession = MediaPlaybackSession;

MediaPlayerSurface = (function () {
  var cls = function MediaPlayerSurface() {
    this.compositionSurface = new Object();
    this.compositor = new Object();
    this.mediaPlayer = new MediaPlayer();
  };
  

  cls.prototype.close = function close() {
}


  return cls;
}) ();
exports.MediaPlayerSurface = MediaPlayerSurface;

MediaPlaybackSphericalVideoProjection = (function () {
  var cls = function MediaPlaybackSphericalVideoProjection() {
    this.viewOrientation = new Quaternion();
    this.projectionMode = new SphericalVideoProjectionMode();
    this.isEnabled = new Boolean();
    this.horizontalFieldOfViewInDegrees = new Number();
    this.frameFormat = new Number();
  };
  

  return cls;
}) ();
exports.MediaPlaybackSphericalVideoProjection = MediaPlaybackSphericalVideoProjection;

MediaPlaybackSessionOutputDegradationPolicyState = (function () {
  var cls = function MediaPlaybackSessionOutputDegradationPolicyState() {
    this.videoConstrictionReason = new MediaPlaybackSessionVideoConstrictionReason();
  };
  

  return cls;
}) ();
exports.MediaPlaybackSessionOutputDegradationPolicyState = MediaPlaybackSessionOutputDegradationPolicyState;

MediaPlaybackSessionBufferingStartedEventArgs = (function () {
  var cls = function MediaPlaybackSessionBufferingStartedEventArgs() {
    this.isPlaybackInterruption = new Boolean();
  };
  

  return cls;
}) ();
exports.MediaPlaybackSessionBufferingStartedEventArgs = MediaPlaybackSessionBufferingStartedEventArgs;

MediaBreakSeekedOverEventArgs = (function () {
  var cls = function MediaBreakSeekedOverEventArgs() {
    this.newPosition = new Number();
    this.oldPosition = new Number();
    this.seekedOverBreaks = new Object();
  };
  

  return cls;
}) ();
exports.MediaBreakSeekedOverEventArgs = MediaBreakSeekedOverEventArgs;

MediaBreakStartedEventArgs = (function () {
  var cls = function MediaBreakStartedEventArgs() {
    this.mediaBreak = new MediaBreak();
  };
  

  return cls;
}) ();
exports.MediaBreakStartedEventArgs = MediaBreakStartedEventArgs;

MediaBreakEndedEventArgs = (function () {
  var cls = function MediaBreakEndedEventArgs() {
    this.mediaBreak = new MediaBreak();
  };
  

  return cls;
}) ();
exports.MediaBreakEndedEventArgs = MediaBreakEndedEventArgs;

MediaBreakSkippedEventArgs = (function () {
  var cls = function MediaBreakSkippedEventArgs() {
    this.mediaBreak = new MediaBreak();
  };
  

  return cls;
}) ();
exports.MediaBreakSkippedEventArgs = MediaBreakSkippedEventArgs;

BackgroundMediaPlayer = (function () {
  var cls = function BackgroundMediaPlayer() {
  };
  

  cls.sendMessageToBackground = function sendMessageToBackground(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }


  cls.sendMessageToForeground = function sendMessageToForeground(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }


  cls.isMediaPlaying = function isMediaPlaying() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.shutdown = function shutdown() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  cls.current = new MediaPlayer();
    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.BackgroundMediaPlayer = BackgroundMediaPlayer;

MediaPlaybackCommandManagerPlayReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerPlayReceivedEventArgs() {
    this.handled = new Boolean();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerPlayReceivedEventArgs = MediaPlaybackCommandManagerPlayReceivedEventArgs;

MediaPlaybackCommandManagerPauseReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerPauseReceivedEventArgs() {
    this.handled = new Boolean();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerPauseReceivedEventArgs = MediaPlaybackCommandManagerPauseReceivedEventArgs;

MediaPlaybackCommandManagerNextReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerNextReceivedEventArgs() {
    this.handled = new Boolean();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerNextReceivedEventArgs = MediaPlaybackCommandManagerNextReceivedEventArgs;

MediaPlaybackCommandManagerPreviousReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerPreviousReceivedEventArgs() {
    this.handled = new Boolean();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerPreviousReceivedEventArgs = MediaPlaybackCommandManagerPreviousReceivedEventArgs;

MediaPlaybackCommandManagerFastForwardReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerFastForwardReceivedEventArgs() {
    this.handled = new Boolean();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerFastForwardReceivedEventArgs = MediaPlaybackCommandManagerFastForwardReceivedEventArgs;

MediaPlaybackCommandManagerRewindReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerRewindReceivedEventArgs() {
    this.handled = new Boolean();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerRewindReceivedEventArgs = MediaPlaybackCommandManagerRewindReceivedEventArgs;

MediaPlaybackCommandManagerShuffleReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerShuffleReceivedEventArgs() {
    this.handled = new Boolean();
    this.isShuffleRequested = new Boolean();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerShuffleReceivedEventArgs = MediaPlaybackCommandManagerShuffleReceivedEventArgs;

MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs() {
    this.handled = new Boolean();
    this.autoRepeatMode = new Number();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs = MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs;

MediaPlaybackCommandManagerPositionReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerPositionReceivedEventArgs() {
    this.handled = new Boolean();
    this.position = new Number();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerPositionReceivedEventArgs = MediaPlaybackCommandManagerPositionReceivedEventArgs;

MediaPlaybackCommandManagerRateReceivedEventArgs = (function () {
  var cls = function MediaPlaybackCommandManagerRateReceivedEventArgs() {
    this.handled = new Boolean();
    this.playbackRate = new Number();
  };
  

  cls.prototype.getDeferral = function getDeferral() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  return cls;
}) ();
exports.MediaPlaybackCommandManagerRateReceivedEventArgs = MediaPlaybackCommandManagerRateReceivedEventArgs;

MediaPlaybackCommandManagerCommandBehavior = (function () {
  var cls = function MediaPlaybackCommandManagerCommandBehavior() {
    this.enablingRule = new MediaCommandEnablingRule();
    this.commandManager = new MediaPlaybackCommandManager();
    this.isEnabled = new Boolean();
  };
  

    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlaybackCommandManagerCommandBehavior = MediaPlaybackCommandManagerCommandBehavior;

MediaPlaybackItem = (function () {
  var cls = function MediaPlaybackItem() {
    this.audioTracks = new MediaPlaybackAudioTrackList();
    this.source = new Object();
    this.timedMetadataTracks = new MediaPlaybackTimedMetadataTrackList();
    this.videoTracks = new MediaPlaybackVideoTrackList();
    this.canSkip = new Boolean();
    this.breakSchedule = new MediaBreakSchedule();
    this.durationLimit = new Number();
    this.startTime = new Number();
    this.isDisabledInPlaybackList = new Boolean();
    this.autoLoadedDisplayProperties = new AutoLoadedDisplayPropertyKind();
    this.totalDownloadProgress = new Number();
  };
  
var cls = function MediaPlaybackItem(source, startTime) {
      this.audioTracks = new MediaPlaybackAudioTrackList();
      this.source = new Object();
      this.timedMetadataTracks = new MediaPlaybackTimedMetadataTrackList();
      this.videoTracks = new MediaPlaybackVideoTrackList();
      this.canSkip = new Boolean();
      this.breakSchedule = new MediaBreakSchedule();
      this.durationLimit = new Number();
      this.startTime = new Number();
      this.isDisabledInPlaybackList = new Boolean();
      this.autoLoadedDisplayProperties = new AutoLoadedDisplayPropertyKind();
      this.totalDownloadProgress = new Number();
};

var cls = function MediaPlaybackItem(source, startTime, durationLimit) {
      this.audioTracks = new MediaPlaybackAudioTrackList();
      this.source = new Object();
      this.timedMetadataTracks = new MediaPlaybackTimedMetadataTrackList();
      this.videoTracks = new MediaPlaybackVideoTrackList();
      this.canSkip = new Boolean();
      this.breakSchedule = new MediaBreakSchedule();
      this.durationLimit = new Number();
      this.startTime = new Number();
      this.isDisabledInPlaybackList = new Boolean();
      this.autoLoadedDisplayProperties = new AutoLoadedDisplayPropertyKind();
      this.totalDownloadProgress = new Number();
};

var cls = function MediaPlaybackItem(source) {
      this.audioTracks = new MediaPlaybackAudioTrackList();
      this.source = new Object();
      this.timedMetadataTracks = new MediaPlaybackTimedMetadataTrackList();
      this.videoTracks = new MediaPlaybackVideoTrackList();
      this.canSkip = new Boolean();
      this.breakSchedule = new MediaBreakSchedule();
      this.durationLimit = new Number();
      this.startTime = new Number();
      this.isDisabledInPlaybackList = new Boolean();
      this.autoLoadedDisplayProperties = new AutoLoadedDisplayPropertyKind();
      this.totalDownloadProgress = new Number();
};


  cls.prototype.getDisplayProperties = function getDisplayProperties() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="MediaItemDisplayProperties" />
    /// </signature>
    return new MediaItemDisplayProperties();
  }


  cls.prototype.applyDisplayProperties = function applyDisplayProperties(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="MediaItemDisplayProperties">A param.</param>
    /// </signature>
  }


  cls.findFromMediaSource = function findFromMediaSource(source) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="Object">A param.</param>
    /// <returns type="MediaPlaybackItem" />
    /// </signature>
    return new MediaPlaybackItem();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlaybackItem = MediaPlaybackItem;

IMediaPlaybackSource = (function () {
  var cls = function IMediaPlaybackSource() {
  };
  

  return cls;
}) ();
exports.IMediaPlaybackSource = IMediaPlaybackSource;

MediaPlaybackAudioTrackList = (function () {
  var cls = function MediaPlaybackAudioTrackList() {
    this.selectedIndex = new Number();
  };
  

  cls.prototype.getAt = function getAt(index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.indexOf = function indexOf(value, index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getMany = function () {
}

  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlaybackAudioTrackList = MediaPlaybackAudioTrackList;

MediaPlaybackVideoTrackList = (function () {
  var cls = function MediaPlaybackVideoTrackList() {
    this.selectedIndex = new Number();
  };
  

  cls.prototype.getAt = function getAt(index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.indexOf = function indexOf(value, index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getMany = function () {
}

  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlaybackVideoTrackList = MediaPlaybackVideoTrackList;

MediaPlaybackTimedMetadataTrackList = (function () {
  var cls = function MediaPlaybackTimedMetadataTrackList() {
  };
  

  cls.prototype.getAt = function getAt(index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.indexOf = function indexOf(value, index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="Boolean" />
    /// </signature>
    return new Boolean();
  }


  cls.prototype.getMany = function () {
}

  cls.prototype.first = function first() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="Object" />
    /// </signature>
    return new Object();
  }


  cls.prototype.getPresentationMode = function getPresentationMode(index) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="index" type="Number">A param.</param>
    /// <returns type="TimedMetadataTrackPresentationMode" />
    /// </signature>
    return new TimedMetadataTrackPresentationMode();
  }


  cls.prototype.setPresentationMode = function setPresentationMode(index, value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="index" type="Number">A param.</param>
    /// <param name="value" type="TimedMetadataTrackPresentationMode">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlaybackTimedMetadataTrackList = MediaPlaybackTimedMetadataTrackList;

MediaBreakSchedule = (function () {
  var cls = function MediaBreakSchedule() {
    this.prerollBreak = new MediaBreak();
    this.postrollBreak = new MediaBreak();
    this.midrollBreaks = new Object();
    this.playbackItem = new MediaPlaybackItem();
  };
  

  cls.prototype.insertMidrollBreak = function insertMidrollBreak(mediaBreak) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mediaBreak" type="MediaBreak">A param.</param>
    /// </signature>
  }


  cls.prototype.removeMidrollBreak = function removeMidrollBreak(mediaBreak) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="mediaBreak" type="MediaBreak">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaBreakSchedule = MediaBreakSchedule;

MediaItemDisplayProperties = (function () {
  var cls = function MediaItemDisplayProperties() {
    this.type = new Number();
    this.thumbnail = new Object();
    this.musicProperties = new Object();
    this.videoProperties = new Object();
  };
  

  cls.prototype.clearAll = function clearAll() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// </signature>
  }


  return cls;
}) ();
exports.MediaItemDisplayProperties = MediaItemDisplayProperties;

MediaBreak = (function () {
  var cls = function MediaBreak() {
    this.canStart = new Boolean();
    this.customProperties = new Object();
    this.insertionMethod = new MediaBreakInsertionMethod();
    this.playbackList = new MediaPlaybackList();
    this.presentationPosition = new Number();
  };
  
var cls = function MediaBreak(insertionMethod) {
      this.canStart = new Boolean();
      this.customProperties = new Object();
      this.insertionMethod = new MediaBreakInsertionMethod();
      this.playbackList = new MediaPlaybackList();
      this.presentationPosition = new Number();
};

var cls = function MediaBreak(insertionMethod, presentationPosition) {
      this.canStart = new Boolean();
      this.customProperties = new Object();
      this.insertionMethod = new MediaBreakInsertionMethod();
      this.playbackList = new MediaPlaybackList();
      this.presentationPosition = new Number();
};


  return cls;
}) ();
exports.MediaBreak = MediaBreak;

MediaPlaybackList = (function () {
  var cls = function MediaPlaybackList() {
    this.shuffleEnabled = new Boolean();
    this.autoRepeatEnabled = new Boolean();
    this.currentItem = new MediaPlaybackItem();
    this.currentItemIndex = new Number();
    this.items = new Object();
    this.startingItem = new MediaPlaybackItem();
    this.maxPrefetchTime = new Number();
    this.shuffledItems = new Object();
    this.maxPlayedItemsToKeepOpen = new Number();
  };
  

  cls.prototype.moveNext = function moveNext() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="MediaPlaybackItem" />
    /// </signature>
    return new MediaPlaybackItem();
  }


  cls.prototype.movePrevious = function movePrevious() {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <returns type="MediaPlaybackItem" />
    /// </signature>
    return new MediaPlaybackItem();
  }


  cls.prototype.moveTo = function moveTo(itemIndex) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="itemIndex" type="Number">A param.</param>
    /// <returns type="MediaPlaybackItem" />
    /// </signature>
    return new MediaPlaybackItem();
  }


  cls.prototype.setShuffledItems = function setShuffledItems(value) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="value" type="Object">A param.</param>
    /// </signature>
  }


    cls.prototype.addListener = function addListener(eventName, callback){}
    cls.prototype.removeListener = function removeListener(eventName, callback){}
    cls.prototype.on = function on(eventName, callback){}
    cls.prototype.off = function off(eventName, callback){}
  return cls;
}) ();
exports.MediaPlaybackList = MediaPlaybackList;

IMediaEnginePlaybackSource = (function () {
  var cls = function IMediaEnginePlaybackSource() {
    this.currentItem = new MediaPlaybackItem();
  };
  

  cls.prototype.setPlaybackSource = function setPlaybackSource(source) {
    /// <signature>
    /// <summary>Function summary.</summary>
    /// <param name="source" type="IMediaPlaybackSource">A param.</param>
    /// </signature>
  }


  return cls;
}) ();
exports.IMediaEnginePlaybackSource = IMediaEnginePlaybackSource;

MediaPlaybackItemError = (function () {
  var cls = function MediaPlaybackItemError() {
    this.errorCode = new MediaPlaybackItemErrorCode();
    this.extendedError = new Number();
  };
  

  return cls;
}) ();
exports.MediaPlaybackItemError = MediaPlaybackItemError;

MediaPlaybackItemFailedEventArgs = (function () {
  var cls = function MediaPlaybackItemFailedEventArgs() {
    this.error = new MediaPlaybackItemError();
    this.item = new MediaPlaybackItem();
  };
  

  return cls;
}) ();
exports.MediaPlaybackItemFailedEventArgs = MediaPlaybackItemFailedEventArgs;

CurrentMediaPlaybackItemChangedEventArgs = (function () {
  var cls = function CurrentMediaPlaybackItemChangedEventArgs() {
    this.newItem = new MediaPlaybackItem();
    this.oldItem = new MediaPlaybackItem();
    this.reason = new MediaPlaybackItemChangedReason();
  };
  

  return cls;
}) ();
exports.CurrentMediaPlaybackItemChangedEventArgs = CurrentMediaPlaybackItemChangedEventArgs;

MediaPlaybackItemOpenedEventArgs = (function () {
  var cls = function MediaPlaybackItemOpenedEventArgs() {
    this.item = new MediaPlaybackItem();
  };
  

  return cls;
}) ();
exports.MediaPlaybackItemOpenedEventArgs = MediaPlaybackItemOpenedEventArgs;

TimedMetadataPresentationModeChangedEventArgs = (function () {
  var cls = function TimedMetadataPresentationModeChangedEventArgs() {
    this.newPresentationMode = new TimedMetadataTrackPresentationMode();
    this.oldPresentationMode = new TimedMetadataTrackPresentationMode();
    this.track = new Object();
  };
  

  return cls;
}) ();
exports.TimedMetadataPresentationModeChangedEventArgs = TimedMetadataPresentationModeChangedEventArgs;

