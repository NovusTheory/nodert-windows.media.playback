// Copyright (c) The NodeRT Contributors
// All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the ""License""); you may
// not use this file except in compliance with the License. You may obtain a
// copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// THIS CODE IS PROVIDED ON AN  *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS
// OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY
// IMPLIED WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
// MERCHANTABLITY OR NON-INFRINGEMENT.
//
// See the Apache Version 2.0 License for specific language governing permissions
// and limitations under the License.

// TODO: Verify that this is is still needed..
#define NTDDI_VERSION 0x06010000

#include <v8.h>
#include "nan.h"
#include <string>
#include <ppltasks.h>
#include "CollectionsConverter.h"
#include "CollectionsWrap.h"
#include "node-async.h"
#include "NodeRtUtils.h"
#include "OpaqueWrapper.h"
#include "WrapperBase.h"

#using <Windows.WinMD>

// this undefs fixes the issues of compiling Windows.Data.Json, Windows.Storag.FileProperties, and Windows.Stroage.Search
// Some of the node header files brings windows definitions with the same names as some of the WinRT methods
#undef DocumentProperties
#undef GetObject
#undef CreateEvent
#undef FindText
#undef SendMessage

const char* REGISTRATION_TOKEN_MAP_PROPERTY_NAME = "__registrationTokenMap__";

using v8::Array;
using v8::String;
using v8::Value;
using v8::Boolean;
using v8::Integer;
using v8::FunctionTemplate;
using v8::Object;
using v8::Local;
using v8::Function;
using v8::Date;
using v8::Number;
using v8::PropertyAttribute;
using v8::Primitive;
using Nan::HandleScope;
using Nan::Persistent;
using Nan::Undefined;
using Nan::True;
using Nan::False;
using Nan::Null;
using Nan::MaybeLocal;
using Nan::EscapableHandleScope;
using Nan::HandleScope;
using Nan::TryCatch;
using namespace concurrency;

namespace NodeRT { namespace Windows { namespace Media { namespace Playback { 
  v8::Local<v8::Value> WrapPlaybackMediaMarker(::Windows::Media::Playback::PlaybackMediaMarker^ wintRtInstance);
  ::Windows::Media::Playback::PlaybackMediaMarker^ UnwrapPlaybackMediaMarker(Local<Value> value);
  
  v8::Local<v8::Value> WrapPlaybackMediaMarkerSequence(::Windows::Media::Playback::PlaybackMediaMarkerSequence^ wintRtInstance);
  ::Windows::Media::Playback::PlaybackMediaMarkerSequence^ UnwrapPlaybackMediaMarkerSequence(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlayerFailedEventArgs(::Windows::Media::Playback::MediaPlayerFailedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlayerFailedEventArgs^ UnwrapMediaPlayerFailedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlayerRateChangedEventArgs(::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ UnwrapMediaPlayerRateChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapPlaybackMediaMarkerReachedEventArgs(::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ UnwrapPlaybackMediaMarkerReachedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlayerDataReceivedEventArgs(::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ UnwrapMediaPlayerDataReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlayer(::Windows::Media::Playback::MediaPlayer^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlayer^ UnwrapMediaPlayer(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaBreakManager(::Windows::Media::Playback::MediaBreakManager^ wintRtInstance);
  ::Windows::Media::Playback::MediaBreakManager^ UnwrapMediaBreakManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManager(::Windows::Media::Playback::MediaPlaybackCommandManager^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManager^ UnwrapMediaPlaybackCommandManager(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackSession(::Windows::Media::Playback::MediaPlaybackSession^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackSession^ UnwrapMediaPlaybackSession(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlayerSurface(::Windows::Media::Playback::MediaPlayerSurface^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlayerSurface^ UnwrapMediaPlayerSurface(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackSphericalVideoProjection(::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ UnwrapMediaPlaybackSphericalVideoProjection(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackSessionOutputDegradationPolicyState(::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ UnwrapMediaPlaybackSessionOutputDegradationPolicyState(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackSessionBufferingStartedEventArgs(::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ UnwrapMediaPlaybackSessionBufferingStartedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaBreakSeekedOverEventArgs(::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ UnwrapMediaBreakSeekedOverEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaBreakStartedEventArgs(::Windows::Media::Playback::MediaBreakStartedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaBreakStartedEventArgs^ UnwrapMediaBreakStartedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaBreakEndedEventArgs(::Windows::Media::Playback::MediaBreakEndedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaBreakEndedEventArgs^ UnwrapMediaBreakEndedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaBreakSkippedEventArgs(::Windows::Media::Playback::MediaBreakSkippedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaBreakSkippedEventArgs^ UnwrapMediaBreakSkippedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapBackgroundMediaPlayer(::Windows::Media::Playback::BackgroundMediaPlayer^ wintRtInstance);
  ::Windows::Media::Playback::BackgroundMediaPlayer^ UnwrapBackgroundMediaPlayer(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPlayReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPlayReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPauseReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPauseReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerNextReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerNextReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPreviousReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPreviousReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerFastForwardReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerFastForwardReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerRewindReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerRewindReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerShuffleReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerShuffleReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPositionReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPositionReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerRateReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerRateReceivedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerCommandBehavior(::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ UnwrapMediaPlaybackCommandManagerCommandBehavior(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackItem(::Windows::Media::Playback::MediaPlaybackItem^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackItem^ UnwrapMediaPlaybackItem(Local<Value> value);
  
  v8::Local<v8::Value> WrapIMediaPlaybackSource(::Windows::Media::Playback::IMediaPlaybackSource^ wintRtInstance);
  ::Windows::Media::Playback::IMediaPlaybackSource^ UnwrapIMediaPlaybackSource(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackAudioTrackList(::Windows::Media::Playback::MediaPlaybackAudioTrackList^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackAudioTrackList^ UnwrapMediaPlaybackAudioTrackList(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackVideoTrackList(::Windows::Media::Playback::MediaPlaybackVideoTrackList^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackVideoTrackList^ UnwrapMediaPlaybackVideoTrackList(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackTimedMetadataTrackList(::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ UnwrapMediaPlaybackTimedMetadataTrackList(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaBreakSchedule(::Windows::Media::Playback::MediaBreakSchedule^ wintRtInstance);
  ::Windows::Media::Playback::MediaBreakSchedule^ UnwrapMediaBreakSchedule(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaItemDisplayProperties(::Windows::Media::Playback::MediaItemDisplayProperties^ wintRtInstance);
  ::Windows::Media::Playback::MediaItemDisplayProperties^ UnwrapMediaItemDisplayProperties(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaBreak(::Windows::Media::Playback::MediaBreak^ wintRtInstance);
  ::Windows::Media::Playback::MediaBreak^ UnwrapMediaBreak(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackList(::Windows::Media::Playback::MediaPlaybackList^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackList^ UnwrapMediaPlaybackList(Local<Value> value);
  
  v8::Local<v8::Value> WrapIMediaEnginePlaybackSource(::Windows::Media::Playback::IMediaEnginePlaybackSource^ wintRtInstance);
  ::Windows::Media::Playback::IMediaEnginePlaybackSource^ UnwrapIMediaEnginePlaybackSource(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackItemError(::Windows::Media::Playback::MediaPlaybackItemError^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackItemError^ UnwrapMediaPlaybackItemError(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackItemFailedEventArgs(::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ UnwrapMediaPlaybackItemFailedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapCurrentMediaPlaybackItemChangedEventArgs(::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ UnwrapCurrentMediaPlaybackItemChangedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapMediaPlaybackItemOpenedEventArgs(::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ UnwrapMediaPlaybackItemOpenedEventArgs(Local<Value> value);
  
  v8::Local<v8::Value> WrapTimedMetadataPresentationModeChangedEventArgs(::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ wintRtInstance);
  ::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ UnwrapTimedMetadataPresentationModeChangedEventArgs(Local<Value> value);
  



  static void InitMediaPlayerStateEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlayerState").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("closed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerState::Closed)));
    Nan::Set(enumObject, Nan::New<String>("opening").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerState::Opening)));
    Nan::Set(enumObject, Nan::New<String>("buffering").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerState::Buffering)));
    Nan::Set(enumObject, Nan::New<String>("playing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerState::Playing)));
    Nan::Set(enumObject, Nan::New<String>("paused").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerState::Paused)));
    Nan::Set(enumObject, Nan::New<String>("stopped").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerState::Stopped)));
  }

  static void InitMediaPlaybackStateEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlaybackState").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackState::None)));
    Nan::Set(enumObject, Nan::New<String>("opening").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackState::Opening)));
    Nan::Set(enumObject, Nan::New<String>("buffering").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackState::Buffering)));
    Nan::Set(enumObject, Nan::New<String>("playing").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackState::Playing)));
    Nan::Set(enumObject, Nan::New<String>("paused").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackState::Paused)));
  }

  static void InitMediaPlayerErrorEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlayerError").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerError::Unknown)));
    Nan::Set(enumObject, Nan::New<String>("aborted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerError::Aborted)));
    Nan::Set(enumObject, Nan::New<String>("networkError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerError::NetworkError)));
    Nan::Set(enumObject, Nan::New<String>("decodingError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerError::DecodingError)));
    Nan::Set(enumObject, Nan::New<String>("sourceNotSupported").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerError::SourceNotSupported)));
  }

  static void InitMediaPlayerAudioCategoryEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlayerAudioCategory").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("other").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::Other)));
    Nan::Set(enumObject, Nan::New<String>("communications").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::Communications)));
    Nan::Set(enumObject, Nan::New<String>("alerts").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::Alerts)));
    Nan::Set(enumObject, Nan::New<String>("soundEffects").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::SoundEffects)));
    Nan::Set(enumObject, Nan::New<String>("gameEffects").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::GameEffects)));
    Nan::Set(enumObject, Nan::New<String>("gameMedia").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::GameMedia)));
    Nan::Set(enumObject, Nan::New<String>("gameChat").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::GameChat)));
    Nan::Set(enumObject, Nan::New<String>("speech").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::Speech)));
    Nan::Set(enumObject, Nan::New<String>("movie").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::Movie)));
    Nan::Set(enumObject, Nan::New<String>("media").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioCategory::Media)));
  }

  static void InitMediaPlayerAudioDeviceTypeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlayerAudioDeviceType").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("console").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioDeviceType::Console)));
    Nan::Set(enumObject, Nan::New<String>("multimedia").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioDeviceType::Multimedia)));
    Nan::Set(enumObject, Nan::New<String>("communications").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlayerAudioDeviceType::Communications)));
  }

  static void InitStereoscopicVideoRenderModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("StereoscopicVideoRenderMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("mono").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::StereoscopicVideoRenderMode::Mono)));
    Nan::Set(enumObject, Nan::New<String>("stereo").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::StereoscopicVideoRenderMode::Stereo)));
  }

  static void InitMediaCommandEnablingRuleEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaCommandEnablingRule").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("auto").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaCommandEnablingRule::Auto)));
    Nan::Set(enumObject, Nan::New<String>("always").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaCommandEnablingRule::Always)));
    Nan::Set(enumObject, Nan::New<String>("never").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaCommandEnablingRule::Never)));
  }

  static void InitMediaPlaybackSessionVideoConstrictionReasonEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlaybackSessionVideoConstrictionReason").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackSessionVideoConstrictionReason::None)));
    Nan::Set(enumObject, Nan::New<String>("virtualMachine").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackSessionVideoConstrictionReason::VirtualMachine)));
    Nan::Set(enumObject, Nan::New<String>("unsupportedDisplayAdapter").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackSessionVideoConstrictionReason::UnsupportedDisplayAdapter)));
    Nan::Set(enumObject, Nan::New<String>("unsignedDriver").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackSessionVideoConstrictionReason::UnsignedDriver)));
    Nan::Set(enumObject, Nan::New<String>("frameServerEnabled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackSessionVideoConstrictionReason::FrameServerEnabled)));
    Nan::Set(enumObject, Nan::New<String>("outputProtectionFailed").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackSessionVideoConstrictionReason::OutputProtectionFailed)));
    Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackSessionVideoConstrictionReason::Unknown)));
  }

  static void InitSphericalVideoProjectionModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("SphericalVideoProjectionMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("spherical").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::SphericalVideoProjectionMode::Spherical)));
    Nan::Set(enumObject, Nan::New<String>("flat").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::SphericalVideoProjectionMode::Flat)));
  }

  static void InitMediaPlaybackItemErrorCodeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlaybackItemErrorCode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemErrorCode::None)));
    Nan::Set(enumObject, Nan::New<String>("aborted").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemErrorCode::Aborted)));
    Nan::Set(enumObject, Nan::New<String>("networkError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemErrorCode::NetworkError)));
    Nan::Set(enumObject, Nan::New<String>("decodeError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemErrorCode::DecodeError)));
    Nan::Set(enumObject, Nan::New<String>("sourceNotSupportedError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemErrorCode::SourceNotSupportedError)));
    Nan::Set(enumObject, Nan::New<String>("encryptionError").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemErrorCode::EncryptionError)));
  }

  static void InitFailedMediaStreamKindEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("FailedMediaStreamKind").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("unknown").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::FailedMediaStreamKind::Unknown)));
    Nan::Set(enumObject, Nan::New<String>("audio").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::FailedMediaStreamKind::Audio)));
    Nan::Set(enumObject, Nan::New<String>("video").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::FailedMediaStreamKind::Video)));
  }

  static void InitTimedMetadataTrackPresentationModeEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("TimedMetadataTrackPresentationMode").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("disabled").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::TimedMetadataTrackPresentationMode::Disabled)));
    Nan::Set(enumObject, Nan::New<String>("hidden").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::TimedMetadataTrackPresentationMode::Hidden)));
    Nan::Set(enumObject, Nan::New<String>("applicationPresented").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::TimedMetadataTrackPresentationMode::ApplicationPresented)));
    Nan::Set(enumObject, Nan::New<String>("platformPresented").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::TimedMetadataTrackPresentationMode::PlatformPresented)));
  }

  static void InitMediaBreakInsertionMethodEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaBreakInsertionMethod").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("interrupt").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaBreakInsertionMethod::Interrupt)));
    Nan::Set(enumObject, Nan::New<String>("replace").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaBreakInsertionMethod::Replace)));
  }

  static void InitMediaPlaybackItemChangedReasonEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("MediaPlaybackItemChangedReason").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("initialItem").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemChangedReason::InitialItem)));
    Nan::Set(enumObject, Nan::New<String>("endOfStream").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemChangedReason::EndOfStream)));
    Nan::Set(enumObject, Nan::New<String>("error").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemChangedReason::Error)));
    Nan::Set(enumObject, Nan::New<String>("appRequested").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::MediaPlaybackItemChangedReason::AppRequested)));
  }

  static void InitAutoLoadedDisplayPropertyKindEnum(const Local<Object> exports) {
    HandleScope scope;

    Local<Object> enumObject = Nan::New<Object>();

    Nan::Set(exports, Nan::New<String>("AutoLoadedDisplayPropertyKind").ToLocalChecked(), enumObject);
    Nan::Set(enumObject, Nan::New<String>("none").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::AutoLoadedDisplayPropertyKind::None)));
    Nan::Set(enumObject, Nan::New<String>("musicOrVideo").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::AutoLoadedDisplayPropertyKind::MusicOrVideo)));
    Nan::Set(enumObject, Nan::New<String>("music").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::AutoLoadedDisplayPropertyKind::Music)));
    Nan::Set(enumObject, Nan::New<String>("video").ToLocalChecked(), Nan::New<Integer>(static_cast<int>(::Windows::Media::Playback::AutoLoadedDisplayPropertyKind::Video)));
  }


  static bool IsSizeJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::Size SizeFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Foundation::Size returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> SizeToJsObject(::Windows::Foundation::Size value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();


    return scope.Escape(obj);
  }
  static bool IsRectJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    return true;
  }

  ::Windows::Foundation::Rect RectFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Foundation::Rect returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    return returnValue;
  }

  Local<Value> RectToJsObject(::Windows::Foundation::Rect value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();


    return scope.Escape(obj);
  }
  static bool IsMediaTimeRangeJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("start").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("end").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    return true;
  }

  ::Windows::Media::MediaTimeRange MediaTimeRangeFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Media::MediaTimeRange returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("start").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.Start = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    symbol = Nan::New<String>("end").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.End = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0));
    }
    
    return returnValue;
  }

  Local<Value> MediaTimeRangeToJsObject(::Windows::Media::MediaTimeRange value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("start").ToLocalChecked(), Nan::New<Number>(value.Start.Duration/10000.0));
    Nan::Set(obj, Nan::New<String>("end").ToLocalChecked(), Nan::New<Number>(value.End.Duration/10000.0));

    return scope.Escape(obj);
  }
  static bool IsQuaternionJsObject(Local<Value> value) {
    if (!value->IsObject()) {
      return false;
    }

    Local<String> symbol;
    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();

    symbol = Nan::New<String>("x").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("y").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("z").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    symbol = Nan::New<String>("w").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      if (!Nan::Get(obj,symbol).ToLocalChecked()->IsNumber()) {
        return false;
      }
    }
    
    return true;
  }

  ::Windows::Foundation::Numerics::quaternion QuaternionFromJsObject(Local<Value> value) {
    HandleScope scope;
    ::Windows::Foundation::Numerics::quaternion returnValue;

    if (!value->IsObject()) {
      Nan::ThrowError(Nan::TypeError(NodeRT::Utils::NewString(L"Unexpected type, expected an object")));
      return returnValue;
    }

    Local<Object> obj = Nan::To<Object>(value).ToLocalChecked();
    Local<String> symbol;

    symbol = Nan::New<String>("x").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.x = static_cast<float>(Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0));
    }
    
    symbol = Nan::New<String>("y").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.y = static_cast<float>(Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0));
    }
    
    symbol = Nan::New<String>("z").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.z = static_cast<float>(Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0));
    }
    
    symbol = Nan::New<String>("w").ToLocalChecked();
    if (Nan::Has(obj, symbol).FromMaybe(false)) {
      returnValue.w = static_cast<float>(Nan::To<double>(Nan::Get(obj,symbol).ToLocalChecked()).FromMaybe(0.0));
    }
    
    return returnValue;
  }

  Local<Value> QuaternionToJsObject(::Windows::Foundation::Numerics::quaternion value) {
    EscapableHandleScope scope;

    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New<String>("x").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.x)));
    Nan::Set(obj, Nan::New<String>("y").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.y)));
    Nan::Set(obj, Nan::New<String>("z").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.z)));
    Nan::Set(obj, Nan::New<String>("w").ToLocalChecked(), Nan::New<Number>(static_cast<double>(value.w)));

    return scope.Escape(obj);
  }

  class PlaybackMediaMarker : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("PlaybackMediaMarker").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mediaMarkerType").ToLocalChecked(), MediaMarkerTypeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("text").ToLocalChecked(), TextGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("time").ToLocalChecked(), TimeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("PlaybackMediaMarker").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      PlaybackMediaMarker(::Windows::Media::Playback::PlaybackMediaMarker^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::PlaybackMediaMarker^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarker^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::PlaybackMediaMarker^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsNumber())
      {
        try {
          ::Windows::Foundation::TimeSpan arg0 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[0]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Media::Playback::PlaybackMediaMarker(arg0);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && info[0]->IsNumber()
        && info[1]->IsString()
        && info[2]->IsString())
      {
        try {
          ::Windows::Foundation::TimeSpan arg0 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[0]).FromMaybe(0));
          Platform::String^ arg1 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[1])));
          Platform::String^ arg2 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[2])));
          
          winRtInstance = ref new ::Windows::Media::Playback::PlaybackMediaMarker(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PlaybackMediaMarker *wrapperInstance = new PlaybackMediaMarker(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarker^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::PlaybackMediaMarker^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::PlaybackMediaMarker^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapPlaybackMediaMarker(winRtInstance));
    }





    static void MediaMarkerTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarker^>(info.This())) {
        return;
      }

      PlaybackMediaMarker *wrapper = PlaybackMediaMarker::Unwrap<PlaybackMediaMarker>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->MediaMarkerType;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TextGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarker^>(info.This())) {
        return;
      }

      PlaybackMediaMarker *wrapper = PlaybackMediaMarker::Unwrap<PlaybackMediaMarker>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->Text;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarker^>(info.This())) {
        return;
      }

      PlaybackMediaMarker *wrapper = PlaybackMediaMarker::Unwrap<PlaybackMediaMarker>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->Time;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::PlaybackMediaMarker^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapPlaybackMediaMarker(::Windows::Media::Playback::PlaybackMediaMarker^ wintRtInstance);
      friend ::Windows::Media::Playback::PlaybackMediaMarker^ UnwrapPlaybackMediaMarker(Local<Value> value);
  };

  Persistent<FunctionTemplate> PlaybackMediaMarker::s_constructorTemplate;

  v8::Local<v8::Value> WrapPlaybackMediaMarker(::Windows::Media::Playback::PlaybackMediaMarker^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PlaybackMediaMarker::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::PlaybackMediaMarker^ UnwrapPlaybackMediaMarker(Local<Value> value) {
     return PlaybackMediaMarker::Unwrap<PlaybackMediaMarker>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPlaybackMediaMarker(Local<Object> exports) {
    PlaybackMediaMarker::Init(exports);
  }

  class PlaybackMediaMarkerSequence : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("PlaybackMediaMarkerSequence").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "insert", Insert);
            Nan::SetPrototypeMethod(localRef, "clear", Clear);
            Nan::SetPrototypeMethod(localRef, "first", First);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("size").ToLocalChecked(), SizeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("PlaybackMediaMarkerSequence").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      PlaybackMediaMarkerSequence(::Windows::Media::Playback::PlaybackMediaMarkerSequence^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::PlaybackMediaMarkerSequence^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerSequence^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::PlaybackMediaMarkerSequence^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PlaybackMediaMarkerSequence *wrapperInstance = new PlaybackMediaMarkerSequence(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerSequence^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::PlaybackMediaMarkerSequence^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::PlaybackMediaMarkerSequence^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapPlaybackMediaMarkerSequence(winRtInstance));
    }


    static void Insert(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerSequence^>(info.This())) {
        return;
      }

      PlaybackMediaMarkerSequence *wrapper = PlaybackMediaMarkerSequence::Unwrap<PlaybackMediaMarkerSequence>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarker^>(info[0]))
      {
        try
        {
          ::Windows::Media::Playback::PlaybackMediaMarker^ arg0 = UnwrapPlaybackMediaMarker(info[0]);
          
          wrapper->_instance->Insert(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Clear(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerSequence^>(info.This())) {
        return;
      }

      PlaybackMediaMarkerSequence *wrapper = PlaybackMediaMarkerSequence::Unwrap<PlaybackMediaMarkerSequence>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Clear();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerSequence^>(info.This())) {
        return;
      }

      PlaybackMediaMarkerSequence *wrapper = PlaybackMediaMarkerSequence::Unwrap<PlaybackMediaMarkerSequence>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Media::Playback::PlaybackMediaMarker^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Media::Playback::PlaybackMediaMarker^>::CreateIteratorWrapper(result, 
            [](::Windows::Media::Playback::PlaybackMediaMarker^ val) -> Local<Value> {
              return WrapPlaybackMediaMarker(val);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void SizeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerSequence^>(info.This())) {
        return;
      }

      PlaybackMediaMarkerSequence *wrapper = PlaybackMediaMarkerSequence::Unwrap<PlaybackMediaMarkerSequence>(info.This());

      try  {
        unsigned int result = wrapper->_instance->Size;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::PlaybackMediaMarkerSequence^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapPlaybackMediaMarkerSequence(::Windows::Media::Playback::PlaybackMediaMarkerSequence^ wintRtInstance);
      friend ::Windows::Media::Playback::PlaybackMediaMarkerSequence^ UnwrapPlaybackMediaMarkerSequence(Local<Value> value);
  };

  Persistent<FunctionTemplate> PlaybackMediaMarkerSequence::s_constructorTemplate;

  v8::Local<v8::Value> WrapPlaybackMediaMarkerSequence(::Windows::Media::Playback::PlaybackMediaMarkerSequence^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PlaybackMediaMarkerSequence::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::PlaybackMediaMarkerSequence^ UnwrapPlaybackMediaMarkerSequence(Local<Value> value) {
     return PlaybackMediaMarkerSequence::Unwrap<PlaybackMediaMarkerSequence>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPlaybackMediaMarkerSequence(Local<Object> exports) {
    PlaybackMediaMarkerSequence::Init(exports);
  }

  class MediaPlayerFailedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlayerFailedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorMessage").ToLocalChecked(), ErrorMessageGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedErrorCode").ToLocalChecked(), ExtendedErrorCodeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlayerFailedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlayerFailedEventArgs(::Windows::Media::Playback::MediaPlayerFailedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlayerFailedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerFailedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlayerFailedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlayerFailedEventArgs *wrapperInstance = new MediaPlayerFailedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerFailedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlayerFailedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlayerFailedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlayerFailedEventArgs(winRtInstance));
    }





    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerFailedEventArgs^>(info.This())) {
        return;
      }

      MediaPlayerFailedEventArgs *wrapper = MediaPlayerFailedEventArgs::Unwrap<MediaPlayerFailedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlayerError result = wrapper->_instance->Error;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ErrorMessageGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerFailedEventArgs^>(info.This())) {
        return;
      }

      MediaPlayerFailedEventArgs *wrapper = MediaPlayerFailedEventArgs::Unwrap<MediaPlayerFailedEventArgs>(info.This());

      try  {
        Platform::String^ result = wrapper->_instance->ErrorMessage;
        info.GetReturnValue().Set(NodeRT::Utils::NewString(result->Data()));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerFailedEventArgs^>(info.This())) {
        return;
      }

      MediaPlayerFailedEventArgs *wrapper = MediaPlayerFailedEventArgs::Unwrap<MediaPlayerFailedEventArgs>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlayerFailedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlayerFailedEventArgs(::Windows::Media::Playback::MediaPlayerFailedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlayerFailedEventArgs^ UnwrapMediaPlayerFailedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlayerFailedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlayerFailedEventArgs(::Windows::Media::Playback::MediaPlayerFailedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlayerFailedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlayerFailedEventArgs^ UnwrapMediaPlayerFailedEventArgs(Local<Value> value) {
     return MediaPlayerFailedEventArgs::Unwrap<MediaPlayerFailedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlayerFailedEventArgs(Local<Object> exports) {
    MediaPlayerFailedEventArgs::Init(exports);
  }

  class MediaPlayerRateChangedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlayerRateChangedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("newRate").ToLocalChecked(), NewRateGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlayerRateChangedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlayerRateChangedEventArgs(::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlayerRateChangedEventArgs *wrapperInstance = new MediaPlayerRateChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlayerRateChangedEventArgs(winRtInstance));
    }





    static void NewRateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^>(info.This())) {
        return;
      }

      MediaPlayerRateChangedEventArgs *wrapper = MediaPlayerRateChangedEventArgs::Unwrap<MediaPlayerRateChangedEventArgs>(info.This());

      try  {
        double result = wrapper->_instance->NewRate;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlayerRateChangedEventArgs(::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ UnwrapMediaPlayerRateChangedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlayerRateChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlayerRateChangedEventArgs(::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlayerRateChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ UnwrapMediaPlayerRateChangedEventArgs(Local<Value> value) {
     return MediaPlayerRateChangedEventArgs::Unwrap<MediaPlayerRateChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlayerRateChangedEventArgs(Local<Object> exports) {
    MediaPlayerRateChangedEventArgs::Init(exports);
  }

  class PlaybackMediaMarkerReachedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("PlaybackMediaMarkerReachedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackMediaMarker").ToLocalChecked(), PlaybackMediaMarkerGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("PlaybackMediaMarkerReachedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      PlaybackMediaMarkerReachedEventArgs(::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      PlaybackMediaMarkerReachedEventArgs *wrapperInstance = new PlaybackMediaMarkerReachedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapPlaybackMediaMarkerReachedEventArgs(winRtInstance));
    }





    static void PlaybackMediaMarkerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^>(info.This())) {
        return;
      }

      PlaybackMediaMarkerReachedEventArgs *wrapper = PlaybackMediaMarkerReachedEventArgs::Unwrap<PlaybackMediaMarkerReachedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::PlaybackMediaMarker^ result = wrapper->_instance->PlaybackMediaMarker;
        info.GetReturnValue().Set(WrapPlaybackMediaMarker(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapPlaybackMediaMarkerReachedEventArgs(::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ UnwrapPlaybackMediaMarkerReachedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> PlaybackMediaMarkerReachedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapPlaybackMediaMarkerReachedEventArgs(::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(PlaybackMediaMarkerReachedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ UnwrapPlaybackMediaMarkerReachedEventArgs(Local<Value> value) {
     return PlaybackMediaMarkerReachedEventArgs::Unwrap<PlaybackMediaMarkerReachedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitPlaybackMediaMarkerReachedEventArgs(Local<Object> exports) {
    PlaybackMediaMarkerReachedEventArgs::Init(exports);
  }

  class MediaPlayerDataReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlayerDataReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("data").ToLocalChecked(), DataGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlayerDataReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlayerDataReceivedEventArgs(::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlayerDataReceivedEventArgs *wrapperInstance = new MediaPlayerDataReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlayerDataReceivedEventArgs(winRtInstance));
    }





    static void DataGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlayerDataReceivedEventArgs *wrapper = MediaPlayerDataReceivedEventArgs::Unwrap<MediaPlayerDataReceivedEventArgs>(info.This());

      try  {
        ::Windows::Foundation::Collections::ValueSet^ result = wrapper->_instance->Data;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "ValueSet", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlayerDataReceivedEventArgs(::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ UnwrapMediaPlayerDataReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlayerDataReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlayerDataReceivedEventArgs(::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlayerDataReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ UnwrapMediaPlayerDataReceivedEventArgs(Local<Value> value) {
     return MediaPlayerDataReceivedEventArgs::Unwrap<MediaPlayerDataReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlayerDataReceivedEventArgs(Local<Object> exports) {
    MediaPlayerDataReceivedEventArgs::Init(exports);
  }

  class MediaPlayer : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlayer").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "addAudioEffect", AddAudioEffect);
            Nan::SetPrototypeMethod(localRef, "removeAllEffects", RemoveAllEffects);
            Nan::SetPrototypeMethod(localRef, "close", Close);
            Nan::SetPrototypeMethod(localRef, "stepForwardOneFrame", StepForwardOneFrame);
            Nan::SetPrototypeMethod(localRef, "stepBackwardOneFrame", StepBackwardOneFrame);
            Nan::SetPrototypeMethod(localRef, "getAsCastingSource", GetAsCastingSource);
            Nan::SetPrototypeMethod(localRef, "setSurfaceSize", SetSurfaceSize);
            Nan::SetPrototypeMethod(localRef, "getSurface", GetSurface);
            Nan::SetPrototypeMethod(localRef, "addVideoEffect", AddVideoEffect);
            Nan::SetPrototypeMethod(localRef, "copyFrameToVideoSurface", CopyFrameToVideoSurface);
            Nan::SetPrototypeMethod(localRef, "copyFrameToStereoscopicVideoSurfaces", CopyFrameToStereoscopicVideoSurfaces);
            Nan::SetPrototypeMethod(localRef, "renderSubtitlesToSurface", RenderSubtitlesToSurface);
            Nan::SetPrototypeMethod(localRef, "play", Play);
            Nan::SetPrototypeMethod(localRef, "pause", Pause);
            Nan::SetPrototypeMethod(localRef, "setUriSource", SetUriSource);
            Nan::SetPrototypeMethod(localRef, "setFileSource", SetFileSource);
            Nan::SetPrototypeMethod(localRef, "setStreamSource", SetStreamSource);
            Nan::SetPrototypeMethod(localRef, "setMediaSource", SetMediaSource);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("volume").ToLocalChecked(), VolumeGetter, VolumeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter, PositionSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackRate").ToLocalChecked(), PlaybackRateGetter, PlaybackRateSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isLoopingEnabled").ToLocalChecked(), IsLoopingEnabledGetter, IsLoopingEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isMuted").ToLocalChecked(), IsMutedGetter, IsMutedSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("autoPlay").ToLocalChecked(), AutoPlayGetter, AutoPlaySetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currentState").ToLocalChecked(), CurrentStateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("naturalDuration").ToLocalChecked(), NaturalDurationGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackMediaMarkers").ToLocalChecked(), PlaybackMediaMarkersGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isProtected").ToLocalChecked(), IsProtectedGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bufferingProgress").ToLocalChecked(), BufferingProgressGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canPause").ToLocalChecked(), CanPauseGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canSeek").ToLocalChecked(), CanSeekGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("audioDeviceType").ToLocalChecked(), AudioDeviceTypeGetter, AudioDeviceTypeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("audioCategory").ToLocalChecked(), AudioCategoryGetter, AudioCategorySetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("systemMediaTransportControls").ToLocalChecked(), SystemMediaTransportControlsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("timelineControllerPositionOffset").ToLocalChecked(), TimelineControllerPositionOffsetGetter, TimelineControllerPositionOffsetSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("timelineController").ToLocalChecked(), TimelineControllerGetter, TimelineControllerSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("stereoscopicVideoRenderMode").ToLocalChecked(), StereoscopicVideoRenderModeGetter, StereoscopicVideoRenderModeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("realTimePlayback").ToLocalChecked(), RealTimePlaybackGetter, RealTimePlaybackSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("audioDevice").ToLocalChecked(), AudioDeviceGetter, AudioDeviceSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("audioBalance").ToLocalChecked(), AudioBalanceGetter, AudioBalanceSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("commandManager").ToLocalChecked(), CommandManagerGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("breakManager").ToLocalChecked(), BreakManagerGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackSession").ToLocalChecked(), PlaybackSessionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isVideoFrameServerEnabled").ToLocalChecked(), IsVideoFrameServerEnabledGetter, IsVideoFrameServerEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("audioStateMonitor").ToLocalChecked(), AudioStateMonitorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("protectionManager").ToLocalChecked(), ProtectionManagerGetter, ProtectionManagerSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("source").ToLocalChecked(), SourceGetter, SourceSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlayer").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlayer(::Windows::Media::Playback::MediaPlayer^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlayer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlayer^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Media::Playback::MediaPlayer();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlayer *wrapperInstance = new MediaPlayer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlayer^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlayer^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlayer(winRtInstance));
    }


    static void AddAudioEffect(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsBoolean()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          bool arg1 = Nan::To<bool>(info[1]).FromMaybe(false);
          ::Windows::Foundation::Collections::IPropertySet^ arg2 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[2]));
          
          wrapper->_instance->AddAudioEffect(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveAllEffects(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->RemoveAllEffects();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StepForwardOneFrame(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->StepForwardOneFrame();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void StepBackwardOneFrame(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->StepBackwardOneFrame();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetAsCastingSource(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Media::Casting::CastingSource^ result;
          result = wrapper->_instance->GetAsCastingSource();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Casting", "CastingSource", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetSurfaceSize(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsSize(info[0]))
      {
        try
        {
          ::Windows::Foundation::Size arg0 = NodeRT::Utils::SizeFromJs(info[0]);
          
          wrapper->_instance->SetSurfaceSize(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetSurface(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::UI::Composition::Compositor^>(info[0]))
      {
        try
        {
          ::Windows::UI::Composition::Compositor^ arg0 = dynamic_cast<::Windows::UI::Composition::Compositor^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Media::Playback::MediaPlayerSurface^ result;
          result = wrapper->_instance->GetSurface(arg0);
          info.GetReturnValue().Set(WrapMediaPlayerSurface(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void AddVideoEffect(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 3
        && info[0]->IsString()
        && info[1]->IsBoolean()
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IPropertySet^>(info[2]))
      {
        try
        {
          Platform::String^ arg0 = ref new Platform::String(NodeRT::Utils::StringToWchar(v8::String::Value(v8::Isolate::GetCurrent(), info[0])));
          bool arg1 = Nan::To<bool>(info[1]).FromMaybe(false);
          ::Windows::Foundation::Collections::IPropertySet^ arg2 = dynamic_cast<::Windows::Foundation::Collections::IPropertySet^>(NodeRT::Utils::GetObjectInstance(info[2]));
          
          wrapper->_instance->AddVideoEffect(arg0, arg1, arg2);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CopyFrameToVideoSurface(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg0 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->CopyFrameToVideoSurface(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[0])
        && NodeRT::Utils::IsRect(info[1]))
      {
        try
        {
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg0 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::Rect arg1 = NodeRT::Utils::RectFromJs(info[1]);
          
          wrapper->_instance->CopyFrameToVideoSurface(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void CopyFrameToStereoscopicVideoSurfaces(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[0])
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[1]))
      {
        try
        {
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg0 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg1 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[1]));
          
          wrapper->_instance->CopyFrameToStereoscopicVideoSurfaces(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RenderSubtitlesToSurface(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[0]))
      {
        try
        {
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg0 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          bool result;
          result = wrapper->_instance->RenderSubtitlesToSurface(arg0);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(info[0])
        && NodeRT::Utils::IsRect(info[1]))
      {
        try
        {
          ::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^ arg0 = dynamic_cast<::Windows::Graphics::DirectX::Direct3D11::IDirect3DSurface^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::Rect arg1 = NodeRT::Utils::RectFromJs(info[1]);
          
          bool result;
          result = wrapper->_instance->RenderSubtitlesToSurface(arg0, arg1);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Play(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Play();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void Pause(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->Pause();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetUriSource(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Uri^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Uri^ arg0 = dynamic_cast<::Windows::Foundation::Uri^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->SetUriSource(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetFileSource(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::IStorageFile^>(info[0]))
      {
        try
        {
          ::Windows::Storage::IStorageFile^ arg0 = dynamic_cast<::Windows::Storage::IStorageFile^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->SetFileSource(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetStreamSource(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::IRandomAccessStream^>(info[0]))
      {
        try
        {
          ::Windows::Storage::Streams::IRandomAccessStream^ arg0 = dynamic_cast<::Windows::Storage::Streams::IRandomAccessStream^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->SetStreamSource(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetMediaSource(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Core::IMediaSource^>(info[0]))
      {
        try
        {
          ::Windows::Media::Core::IMediaSource^ arg0 = dynamic_cast<::Windows::Media::Core::IMediaSource^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          wrapper->_instance->SetMediaSource(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void VolumeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        double result = wrapper->_instance->Volume;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VolumeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->Volume = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PositionSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Position = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PlaybackRateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        double result = wrapper->_instance->PlaybackRate;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackRateSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->PlaybackRate = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsLoopingEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        bool result = wrapper->_instance->IsLoopingEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsLoopingEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsLoopingEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsMutedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        bool result = wrapper->_instance->IsMuted;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsMutedSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsMuted = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AutoPlayGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        bool result = wrapper->_instance->AutoPlay;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AutoPlaySetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->AutoPlay = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void CurrentStateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlayerState result = wrapper->_instance->CurrentState;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NaturalDurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->NaturalDuration;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackMediaMarkersGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::PlaybackMediaMarkerSequence^ result = wrapper->_instance->PlaybackMediaMarkers;
        info.GetReturnValue().Set(WrapPlaybackMediaMarkerSequence(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsProtectedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        bool result = wrapper->_instance->IsProtected;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BufferingProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        double result = wrapper->_instance->BufferingProgress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanPauseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        bool result = wrapper->_instance->CanPause;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanSeekGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        bool result = wrapper->_instance->CanSeek;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AudioDeviceTypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlayerAudioDeviceType result = wrapper->_instance->AudioDeviceType;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AudioDeviceTypeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Media::Playback::MediaPlayerAudioDeviceType winRtValue = static_cast<::Windows::Media::Playback::MediaPlayerAudioDeviceType>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->AudioDeviceType = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AudioCategoryGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlayerAudioCategory result = wrapper->_instance->AudioCategory;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AudioCategorySetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Media::Playback::MediaPlayerAudioCategory winRtValue = static_cast<::Windows::Media::Playback::MediaPlayerAudioCategory>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->AudioCategory = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void SystemMediaTransportControlsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::SystemMediaTransportControls^ result = wrapper->_instance->SystemMediaTransportControls;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media", "SystemMediaTransportControls", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TimelineControllerPositionOffsetGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->TimelineControllerPositionOffset;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TimelineControllerPositionOffsetSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->TimelineControllerPositionOffset = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void TimelineControllerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::MediaTimelineController^ result = wrapper->_instance->TimelineController;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media", "MediaTimelineController", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TimelineControllerSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::MediaTimelineController^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Media::MediaTimelineController^ winRtValue = dynamic_cast<::Windows::Media::MediaTimelineController^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->TimelineController = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void StereoscopicVideoRenderModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::StereoscopicVideoRenderMode result = wrapper->_instance->StereoscopicVideoRenderMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StereoscopicVideoRenderModeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Media::Playback::StereoscopicVideoRenderMode winRtValue = static_cast<::Windows::Media::Playback::StereoscopicVideoRenderMode>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->StereoscopicVideoRenderMode = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void RealTimePlaybackGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        bool result = wrapper->_instance->RealTimePlayback;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RealTimePlaybackSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->RealTimePlayback = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AudioDeviceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Devices::Enumeration::DeviceInformation^ result = wrapper->_instance->AudioDevice;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Devices.Enumeration", "DeviceInformation", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AudioDeviceSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Devices::Enumeration::DeviceInformation^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Devices::Enumeration::DeviceInformation^ winRtValue = dynamic_cast<::Windows::Devices::Enumeration::DeviceInformation^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->AudioDevice = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AudioBalanceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        double result = wrapper->_instance->AudioBalance;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AudioBalanceSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->AudioBalance = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void CommandManagerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManager^ result = wrapper->_instance->CommandManager;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManager(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void BreakManagerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreakManager^ result = wrapper->_instance->BreakManager;
        info.GetReturnValue().Set(WrapMediaBreakManager(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackSessionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackSession^ result = wrapper->_instance->PlaybackSession;
        info.GetReturnValue().Set(WrapMediaPlaybackSession(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsVideoFrameServerEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        bool result = wrapper->_instance->IsVideoFrameServerEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsVideoFrameServerEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsVideoFrameServerEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AudioStateMonitorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Audio::AudioStateMonitor^ result = wrapper->_instance->AudioStateMonitor;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Audio", "AudioStateMonitor", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProtectionManagerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Protection::MediaProtectionManager^ result = wrapper->_instance->ProtectionManager;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Protection", "MediaProtectionManager", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProtectionManagerSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Protection::MediaProtectionManager^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Media::Protection::MediaProtectionManager^ winRtValue = dynamic_cast<::Windows::Media::Protection::MediaProtectionManager^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->ProtectionManager = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void SourceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try  {
        ::Windows::Media::Playback::IMediaPlaybackSource^ result = wrapper->_instance->Source;
        info.GetReturnValue().Set(WrapIMediaPlaybackSource(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SourceSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::IMediaPlaybackSource^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This())) {
        return;
      }

      MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());

      try {

        ::Windows::Media::Playback::IMediaPlaybackSource^ winRtValue = dynamic_cast<::Windows::Media::Playback::IMediaPlaybackSource^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Source = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingEnded", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BufferingEnded::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingStarted", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BufferingStarted::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"currentStateChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->CurrentStateChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"mediaEnded", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->MediaEnded::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"mediaFailed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->MediaFailed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Windows::Media::Playback::MediaPlayerFailedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Windows::Media::Playback::MediaPlayerFailedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = WrapMediaPlayerFailedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"mediaOpened", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->MediaOpened::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"mediaPlayerRateChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->MediaPlayerRateChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Windows::Media::Playback::MediaPlayerRateChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = WrapMediaPlayerRateChangedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackMediaMarkerReached", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PlaybackMediaMarkerReached::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Windows::Media::Playback::PlaybackMediaMarkerReachedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = WrapPlaybackMediaMarkerReachedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"seekCompleted", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->SeekCompleted::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"volumeChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->VolumeChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"isMutedChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->IsMutedChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"sourceChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->SourceChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"videoFrameAvailable", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->VideoFrameAvailable::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"subtitleFrameChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->SubtitleFrameChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlayer^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlayer^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlayer(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"bufferingEnded", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"bufferingStarted", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"currentStateChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"mediaEnded", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"mediaFailed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"mediaOpened", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"mediaPlayerRateChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playbackMediaMarkerReached", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"seekCompleted", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"volumeChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"isMutedChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"sourceChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"videoFrameAvailable", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"subtitleFrameChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingEnded", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->BufferingEnded::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingStarted", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->BufferingStarted::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"currentStateChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->CurrentStateChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"mediaEnded", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->MediaEnded::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"mediaFailed", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->MediaFailed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"mediaOpened", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->MediaOpened::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"mediaPlayerRateChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->MediaPlayerRateChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackMediaMarkerReached", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->PlaybackMediaMarkerReached::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"seekCompleted", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->SeekCompleted::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"volumeChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->VolumeChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"isMutedChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->IsMutedChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"sourceChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->SourceChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"videoFrameAvailable", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->VideoFrameAvailable::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"subtitleFrameChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayer^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlayer *wrapper = MediaPlayer::Unwrap<MediaPlayer>(info.This());
          wrapper->_instance->SubtitleFrameChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlayer^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlayer(::Windows::Media::Playback::MediaPlayer^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlayer^ UnwrapMediaPlayer(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlayer::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlayer(::Windows::Media::Playback::MediaPlayer^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlayer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlayer^ UnwrapMediaPlayer(Local<Value> value) {
     return MediaPlayer::Unwrap<MediaPlayer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlayer(Local<Object> exports) {
    MediaPlayer::Init(exports);
  }

  class MediaBreakManager : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaBreakManager").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "playBreak", PlayBreak);
            Nan::SetPrototypeMethod(localRef, "skipCurrentBreak", SkipCurrentBreak);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currentBreak").ToLocalChecked(), CurrentBreakGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackSession").ToLocalChecked(), PlaybackSessionGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaBreakManager").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaBreakManager(::Windows::Media::Playback::MediaBreakManager^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaBreakManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaBreakManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaBreakManager *wrapperInstance = new MediaBreakManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaBreakManager^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaBreakManager^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaBreakManager(winRtInstance));
    }


    static void PlayBreak(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This())) {
        return;
      }

      MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info[0]))
      {
        try
        {
          ::Windows::Media::Playback::MediaBreak^ arg0 = UnwrapMediaBreak(info[0]);
          
          wrapper->_instance->PlayBreak(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SkipCurrentBreak(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This())) {
        return;
      }

      MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->SkipCurrentBreak();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void CurrentBreakGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This())) {
        return;
      }

      MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreak^ result = wrapper->_instance->CurrentBreak;
        info.GetReturnValue().Set(WrapMediaBreak(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackSessionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This())) {
        return;
      }

      MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackSession^ result = wrapper->_instance->PlaybackSession;
        info.GetReturnValue().Set(WrapMediaPlaybackSession(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"breakEnded", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BreakEnded::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaBreakManager^, ::Windows::Media::Playback::MediaBreakEndedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaBreakManager^ arg0, ::Windows::Media::Playback::MediaBreakEndedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaBreakManager(arg0);
                  wrappedArg1 = WrapMediaBreakEndedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"breakSkipped", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BreakSkipped::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaBreakManager^, ::Windows::Media::Playback::MediaBreakSkippedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaBreakManager^ arg0, ::Windows::Media::Playback::MediaBreakSkippedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaBreakManager(arg0);
                  wrappedArg1 = WrapMediaBreakSkippedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"breakStarted", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BreakStarted::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaBreakManager^, ::Windows::Media::Playback::MediaBreakStartedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaBreakManager^ arg0, ::Windows::Media::Playback::MediaBreakStartedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaBreakManager(arg0);
                  wrappedArg1 = WrapMediaBreakStartedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"breaksSeekedOver", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BreaksSeekedOver::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaBreakManager^, ::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaBreakManager^ arg0, ::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaBreakManager(arg0);
                  wrappedArg1 = WrapMediaBreakSeekedOverEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"breakEnded", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"breakSkipped", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"breakStarted", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"breaksSeekedOver", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"breakEnded", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());
          wrapper->_instance->BreakEnded::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"breakSkipped", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());
          wrapper->_instance->BreakSkipped::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"breakStarted", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());
          wrapper->_instance->BreakStarted::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"breaksSeekedOver", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaBreakManager *wrapper = MediaBreakManager::Unwrap<MediaBreakManager>(info.This());
          wrapper->_instance->BreaksSeekedOver::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaBreakManager^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaBreakManager(::Windows::Media::Playback::MediaBreakManager^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaBreakManager^ UnwrapMediaBreakManager(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaBreakManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaBreakManager(::Windows::Media::Playback::MediaBreakManager^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaBreakManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaBreakManager^ UnwrapMediaBreakManager(Local<Value> value) {
     return MediaBreakManager::Unwrap<MediaBreakManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaBreakManager(Local<Object> exports) {
    MediaBreakManager::Init(exports);
  }

  class MediaPlaybackCommandManager : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManager").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);




          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isEnabled").ToLocalChecked(), IsEnabledGetter, IsEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("autoRepeatModeBehavior").ToLocalChecked(), AutoRepeatModeBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("fastForwardBehavior").ToLocalChecked(), FastForwardBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mediaPlayer").ToLocalChecked(), MediaPlayerGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("nextBehavior").ToLocalChecked(), NextBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("pauseBehavior").ToLocalChecked(), PauseBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playBehavior").ToLocalChecked(), PlayBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("positionBehavior").ToLocalChecked(), PositionBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("previousBehavior").ToLocalChecked(), PreviousBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rateBehavior").ToLocalChecked(), RateBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("rewindBehavior").ToLocalChecked(), RewindBehaviorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("shuffleBehavior").ToLocalChecked(), ShuffleBehaviorGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManager").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManager(::Windows::Media::Playback::MediaPlaybackCommandManager^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManager^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManager^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManager *wrapperInstance = new MediaPlaybackCommandManager(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManager^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManager^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManager(winRtInstance));
    }





    static void IsEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        bool result = wrapper->_instance->IsEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AutoRepeatModeBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->AutoRepeatModeBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FastForwardBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->FastForwardBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MediaPlayerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlayer^ result = wrapper->_instance->MediaPlayer;
        info.GetReturnValue().Set(WrapMediaPlayer(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NextBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->NextBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PauseBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->PauseBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlayBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->PlayBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PositionBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->PositionBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PreviousBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->PreviousBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RateBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->RateBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void RewindBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->RewindBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ShuffleBehaviorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ result = wrapper->_instance->ShuffleBehavior;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"autoRepeatModeReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->AutoRepeatModeReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"fastForwardReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->FastForwardReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerFastForwardReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"nextReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->NextReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerNextReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"pauseReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PauseReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerPauseReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PlayReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerPlayReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"positionReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PositionReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerPositionReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"previousReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PreviousReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerPreviousReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"rateReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->RateReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerRateReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"rewindReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->RewindReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerRewindReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"shuffleReceived", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->ShuffleReceived::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManager^, ::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManager^ arg0, ::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManager(arg0);
                  wrappedArg1 = WrapMediaPlaybackCommandManagerShuffleReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"autoRepeatModeReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"fastForwardReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"nextReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"pauseReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"positionReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"previousReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"rateReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"rewindReceived", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"shuffleReceived", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"autoRepeatModeReceived", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->AutoRepeatModeReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"fastForwardReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->FastForwardReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"nextReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->NextReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"pauseReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->PauseReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->PlayReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"positionReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->PositionReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"previousReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->PreviousReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"rateReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->RateReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"rewindReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->RewindReceived::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"shuffleReceived", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManager^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManager *wrapper = MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(info.This());
          wrapper->_instance->ShuffleReceived::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManager^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManager(::Windows::Media::Playback::MediaPlaybackCommandManager^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManager^ UnwrapMediaPlaybackCommandManager(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManager::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManager(::Windows::Media::Playback::MediaPlaybackCommandManager^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManager::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManager^ UnwrapMediaPlaybackCommandManager(Local<Value> value) {
     return MediaPlaybackCommandManager::Unwrap<MediaPlaybackCommandManager>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManager(Local<Object> exports) {
    MediaPlaybackCommandManager::Init(exports);
  }

  class MediaPlaybackSession : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackSession").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getSeekableRanges", GetSeekableRanges);
            Nan::SetPrototypeMethod(localRef, "isSupportedPlaybackRateRange", IsSupportedPlaybackRateRange);
            Nan::SetPrototypeMethod(localRef, "getOutputDegradationPolicyState", GetOutputDegradationPolicyState);
            Nan::SetPrototypeMethod(localRef, "getBufferedRanges", GetBufferedRanges);
            Nan::SetPrototypeMethod(localRef, "getPlayedRanges", GetPlayedRanges);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("stereoscopicVideoPackingMode").ToLocalChecked(), StereoscopicVideoPackingModeGetter, StereoscopicVideoPackingModeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter, PositionSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackRate").ToLocalChecked(), PlaybackRateGetter, PlaybackRateSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("normalizedSourceRect").ToLocalChecked(), NormalizedSourceRectGetter, NormalizedSourceRectSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("bufferingProgress").ToLocalChecked(), BufferingProgressGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canPause").ToLocalChecked(), CanPauseGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canSeek").ToLocalChecked(), CanSeekGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("downloadProgress").ToLocalChecked(), DownloadProgressGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isProtected").ToLocalChecked(), IsProtectedGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mediaPlayer").ToLocalChecked(), MediaPlayerGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("naturalDuration").ToLocalChecked(), NaturalDurationGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("naturalVideoHeight").ToLocalChecked(), NaturalVideoHeightGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("naturalVideoWidth").ToLocalChecked(), NaturalVideoWidthGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackState").ToLocalChecked(), PlaybackStateGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isMirroring").ToLocalChecked(), IsMirroringGetter, IsMirroringSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("sphericalVideoProjection").ToLocalChecked(), SphericalVideoProjectionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackRotation").ToLocalChecked(), PlaybackRotationGetter, PlaybackRotationSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackSession").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackSession(::Windows::Media::Playback::MediaPlaybackSession^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackSession^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackSession^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackSession *wrapperInstance = new MediaPlaybackSession(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackSession^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackSession^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackSession(winRtInstance));
    }


    static void GetSeekableRanges(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Media::MediaTimeRange>^ result;
          result = wrapper->_instance->GetSeekableRanges();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::MediaTimeRange>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::MediaTimeRange val) -> Local<Value> {
              return MediaTimeRangeToJsObject(val);
            },
            [](Local<Value> value) -> bool {
              return IsMediaTimeRangeJsObject(value);
            },
            [](Local<Value> value) -> ::Windows::Media::MediaTimeRange {
              return MediaTimeRangeFromJsObject(value);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IsSupportedPlaybackRateRange(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      if (info.Length() == 2
        && info[0]->IsNumber()
        && info[1]->IsNumber())
      {
        try
        {
          double arg0 = Nan::To<double>(info[0]).FromMaybe(0.0);
          double arg1 = Nan::To<double>(info[1]).FromMaybe(0.0);
          
          bool result;
          result = wrapper->_instance->IsSupportedPlaybackRateRange(arg0, arg1);
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetOutputDegradationPolicyState(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ result;
          result = wrapper->_instance->GetOutputDegradationPolicyState();
          info.GetReturnValue().Set(WrapMediaPlaybackSessionOutputDegradationPolicyState(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetBufferedRanges(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Media::MediaTimeRange>^ result;
          result = wrapper->_instance->GetBufferedRanges();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::MediaTimeRange>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::MediaTimeRange val) -> Local<Value> {
              return MediaTimeRangeToJsObject(val);
            },
            [](Local<Value> value) -> bool {
              return IsMediaTimeRangeJsObject(value);
            },
            [](Local<Value> value) -> ::Windows::Media::MediaTimeRange {
              return MediaTimeRangeFromJsObject(value);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetPlayedRanges(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IVectorView<::Windows::Media::MediaTimeRange>^ result;
          result = wrapper->_instance->GetPlayedRanges();
          info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::MediaTimeRange>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::MediaTimeRange val) -> Local<Value> {
              return MediaTimeRangeToJsObject(val);
            },
            [](Local<Value> value) -> bool {
              return IsMediaTimeRangeJsObject(value);
            },
            [](Local<Value> value) -> ::Windows::Media::MediaTimeRange {
              return MediaTimeRangeFromJsObject(value);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void StereoscopicVideoPackingModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        ::Windows::Media::MediaProperties::StereoscopicVideoPackingMode result = wrapper->_instance->StereoscopicVideoPackingMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StereoscopicVideoPackingModeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try {

        ::Windows::Media::MediaProperties::StereoscopicVideoPackingMode winRtValue = static_cast<::Windows::Media::MediaProperties::StereoscopicVideoPackingMode>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->StereoscopicVideoPackingMode = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PositionSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try {

        ::Windows::Foundation::TimeSpan winRtValue = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0));

        wrapper->_instance->Position = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PlaybackRateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        double result = wrapper->_instance->PlaybackRate;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackRateSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->PlaybackRate = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void NormalizedSourceRectGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        ::Windows::Foundation::Rect result = wrapper->_instance->NormalizedSourceRect;
        info.GetReturnValue().Set(NodeRT::Utils::RectToJs(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NormalizedSourceRectSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsRect(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try {

        ::Windows::Foundation::Rect winRtValue = NodeRT::Utils::RectFromJs(value);

        wrapper->_instance->NormalizedSourceRect = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void BufferingProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        double result = wrapper->_instance->BufferingProgress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanPauseGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        bool result = wrapper->_instance->CanPause;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanSeekGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        bool result = wrapper->_instance->CanSeek;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DownloadProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        double result = wrapper->_instance->DownloadProgress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsProtectedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        bool result = wrapper->_instance->IsProtected;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MediaPlayerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlayer^ result = wrapper->_instance->MediaPlayer;
        info.GetReturnValue().Set(WrapMediaPlayer(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NaturalDurationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->NaturalDuration;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NaturalVideoHeightGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        unsigned int result = wrapper->_instance->NaturalVideoHeight;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void NaturalVideoWidthGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        unsigned int result = wrapper->_instance->NaturalVideoWidth;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackStateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackState result = wrapper->_instance->PlaybackState;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsMirroringGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        bool result = wrapper->_instance->IsMirroring;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsMirroringSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsMirroring = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void SphericalVideoProjectionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ result = wrapper->_instance->SphericalVideoProjection;
        info.GetReturnValue().Set(WrapMediaPlaybackSphericalVideoProjection(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackRotationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try  {
        ::Windows::Media::MediaProperties::MediaRotation result = wrapper->_instance->PlaybackRotation;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackRotationSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This())) {
        return;
      }

      MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());

      try {

        ::Windows::Media::MediaProperties::MediaRotation winRtValue = static_cast<::Windows::Media::MediaProperties::MediaRotation>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->PlaybackRotation = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingEnded", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BufferingEnded::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingProgressChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BufferingProgressChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingStarted", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BufferingStarted::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"downloadProgressChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->DownloadProgressChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"naturalDurationChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->NaturalDurationChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"naturalVideoSizeChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->NaturalVideoSizeChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackRateChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PlaybackRateChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackStateChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PlaybackStateChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PositionChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"seekCompleted", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->SeekCompleted::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferedRangesChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->BufferedRangesChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"playedRangesChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PlayedRangesChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"seekableRangesChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->SeekableRangesChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"supportedPlaybackRatesChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->SupportedPlaybackRatesChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackSession^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackSession^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackSession(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"bufferingEnded", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"bufferingProgressChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"bufferingStarted", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"downloadProgressChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"naturalDurationChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"naturalVideoSizeChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playbackRateChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playbackStateChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"seekCompleted", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"bufferedRangesChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"playedRangesChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"seekableRangesChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"supportedPlaybackRatesChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingEnded", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->BufferingEnded::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingProgressChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->BufferingProgressChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferingStarted", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->BufferingStarted::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"downloadProgressChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->DownloadProgressChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"naturalDurationChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->NaturalDurationChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"naturalVideoSizeChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->NaturalVideoSizeChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackRateChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->PlaybackRateChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playbackStateChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->PlaybackStateChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"positionChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->PositionChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"seekCompleted", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->SeekCompleted::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"bufferedRangesChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->BufferedRangesChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"playedRangesChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->PlayedRangesChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"seekableRangesChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->SeekableRangesChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"supportedPlaybackRatesChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSession^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackSession *wrapper = MediaPlaybackSession::Unwrap<MediaPlaybackSession>(info.This());
          wrapper->_instance->SupportedPlaybackRatesChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlaybackSession^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackSession(::Windows::Media::Playback::MediaPlaybackSession^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackSession^ UnwrapMediaPlaybackSession(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackSession::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackSession(::Windows::Media::Playback::MediaPlaybackSession^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackSession::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackSession^ UnwrapMediaPlaybackSession(Local<Value> value) {
     return MediaPlaybackSession::Unwrap<MediaPlaybackSession>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackSession(Local<Object> exports) {
    MediaPlaybackSession::Init(exports);
  }

  class MediaPlayerSurface : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlayerSurface").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "close", Close);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("compositionSurface").ToLocalChecked(), CompositionSurfaceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("compositor").ToLocalChecked(), CompositorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mediaPlayer").ToLocalChecked(), MediaPlayerGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlayerSurface").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlayerSurface(::Windows::Media::Playback::MediaPlayerSurface^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlayerSurface^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerSurface^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlayerSurface^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlayerSurface *wrapperInstance = new MediaPlayerSurface(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerSurface^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlayerSurface^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlayerSurface^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlayerSurface(winRtInstance));
    }



    static void Close(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerSurface^>(info.This())) {
        return;
      }

      MediaPlayerSurface *wrapper = MediaPlayerSurface::Unwrap<MediaPlayerSurface>(info.This());

      if (info.Length() == 0) {
        try {
          delete wrapper->_instance;
          wrapper->_instance = nullptr;
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      } else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void CompositionSurfaceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerSurface^>(info.This())) {
        return;
      }

      MediaPlayerSurface *wrapper = MediaPlayerSurface::Unwrap<MediaPlayerSurface>(info.This());

      try  {
        ::Windows::UI::Composition::ICompositionSurface^ result = wrapper->_instance->CompositionSurface;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.UI.Composition", "ICompositionSurface", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CompositorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerSurface^>(info.This())) {
        return;
      }

      MediaPlayerSurface *wrapper = MediaPlayerSurface::Unwrap<MediaPlayerSurface>(info.This());

      try  {
        ::Windows::UI::Composition::Compositor^ result = wrapper->_instance->Compositor;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.UI.Composition", "Compositor", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MediaPlayerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlayerSurface^>(info.This())) {
        return;
      }

      MediaPlayerSurface *wrapper = MediaPlayerSurface::Unwrap<MediaPlayerSurface>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlayer^ result = wrapper->_instance->MediaPlayer;
        info.GetReturnValue().Set(WrapMediaPlayer(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlayerSurface^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlayerSurface(::Windows::Media::Playback::MediaPlayerSurface^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlayerSurface^ UnwrapMediaPlayerSurface(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlayerSurface::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlayerSurface(::Windows::Media::Playback::MediaPlayerSurface^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlayerSurface::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlayerSurface^ UnwrapMediaPlayerSurface(Local<Value> value) {
     return MediaPlayerSurface::Unwrap<MediaPlayerSurface>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlayerSurface(Local<Object> exports) {
    MediaPlayerSurface::Init(exports);
  }

  class MediaPlaybackSphericalVideoProjection : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackSphericalVideoProjection").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("viewOrientation").ToLocalChecked(), ViewOrientationGetter, ViewOrientationSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("projectionMode").ToLocalChecked(), ProjectionModeGetter, ProjectionModeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isEnabled").ToLocalChecked(), IsEnabledGetter, IsEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("horizontalFieldOfViewInDegrees").ToLocalChecked(), HorizontalFieldOfViewInDegreesGetter, HorizontalFieldOfViewInDegreesSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("frameFormat").ToLocalChecked(), FrameFormatGetter, FrameFormatSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackSphericalVideoProjection").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackSphericalVideoProjection(::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackSphericalVideoProjection *wrapperInstance = new MediaPlaybackSphericalVideoProjection(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackSphericalVideoProjection(winRtInstance));
    }





    static void ViewOrientationGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try  {
        ::Windows::Foundation::Numerics::quaternion result = wrapper->_instance->ViewOrientation;
        info.GetReturnValue().Set(QuaternionToJsObject(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ViewOrientationSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!IsQuaternionJsObject(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try {

        ::Windows::Foundation::Numerics::quaternion winRtValue = QuaternionFromJsObject(value);

        wrapper->_instance->ViewOrientation = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ProjectionModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try  {
        ::Windows::Media::Playback::SphericalVideoProjectionMode result = wrapper->_instance->ProjectionMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ProjectionModeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try {

        ::Windows::Media::Playback::SphericalVideoProjectionMode winRtValue = static_cast<::Windows::Media::Playback::SphericalVideoProjectionMode>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->ProjectionMode = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try  {
        bool result = wrapper->_instance->IsEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void HorizontalFieldOfViewInDegreesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try  {
        double result = wrapper->_instance->HorizontalFieldOfViewInDegrees;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HorizontalFieldOfViewInDegreesSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try {

        double winRtValue = Nan::To<double>(value).FromMaybe(0.0);

        wrapper->_instance->HorizontalFieldOfViewInDegrees = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void FrameFormatGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try  {
        ::Windows::Media::MediaProperties::SphericalVideoFrameFormat result = wrapper->_instance->FrameFormat;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void FrameFormatSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^>(info.This())) {
        return;
      }

      MediaPlaybackSphericalVideoProjection *wrapper = MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(info.This());

      try {

        ::Windows::Media::MediaProperties::SphericalVideoFrameFormat winRtValue = static_cast<::Windows::Media::MediaProperties::SphericalVideoFrameFormat>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->FrameFormat = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackSphericalVideoProjection(::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ UnwrapMediaPlaybackSphericalVideoProjection(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackSphericalVideoProjection::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackSphericalVideoProjection(::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackSphericalVideoProjection::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackSphericalVideoProjection^ UnwrapMediaPlaybackSphericalVideoProjection(Local<Value> value) {
     return MediaPlaybackSphericalVideoProjection::Unwrap<MediaPlaybackSphericalVideoProjection>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackSphericalVideoProjection(Local<Object> exports) {
    MediaPlaybackSphericalVideoProjection::Init(exports);
  }

  class MediaPlaybackSessionOutputDegradationPolicyState : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackSessionOutputDegradationPolicyState").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("videoConstrictionReason").ToLocalChecked(), VideoConstrictionReasonGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackSessionOutputDegradationPolicyState").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackSessionOutputDegradationPolicyState(::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackSessionOutputDegradationPolicyState *wrapperInstance = new MediaPlaybackSessionOutputDegradationPolicyState(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackSessionOutputDegradationPolicyState(winRtInstance));
    }





    static void VideoConstrictionReasonGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^>(info.This())) {
        return;
      }

      MediaPlaybackSessionOutputDegradationPolicyState *wrapper = MediaPlaybackSessionOutputDegradationPolicyState::Unwrap<MediaPlaybackSessionOutputDegradationPolicyState>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackSessionVideoConstrictionReason result = wrapper->_instance->VideoConstrictionReason;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackSessionOutputDegradationPolicyState(::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ UnwrapMediaPlaybackSessionOutputDegradationPolicyState(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackSessionOutputDegradationPolicyState::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackSessionOutputDegradationPolicyState(::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackSessionOutputDegradationPolicyState::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackSessionOutputDegradationPolicyState^ UnwrapMediaPlaybackSessionOutputDegradationPolicyState(Local<Value> value) {
     return MediaPlaybackSessionOutputDegradationPolicyState::Unwrap<MediaPlaybackSessionOutputDegradationPolicyState>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackSessionOutputDegradationPolicyState(Local<Object> exports) {
    MediaPlaybackSessionOutputDegradationPolicyState::Init(exports);
  }

  class MediaPlaybackSessionBufferingStartedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackSessionBufferingStartedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isPlaybackInterruption").ToLocalChecked(), IsPlaybackInterruptionGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackSessionBufferingStartedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackSessionBufferingStartedEventArgs(::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackSessionBufferingStartedEventArgs *wrapperInstance = new MediaPlaybackSessionBufferingStartedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackSessionBufferingStartedEventArgs(winRtInstance));
    }





    static void IsPlaybackInterruptionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackSessionBufferingStartedEventArgs *wrapper = MediaPlaybackSessionBufferingStartedEventArgs::Unwrap<MediaPlaybackSessionBufferingStartedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->IsPlaybackInterruption;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackSessionBufferingStartedEventArgs(::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ UnwrapMediaPlaybackSessionBufferingStartedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackSessionBufferingStartedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackSessionBufferingStartedEventArgs(::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackSessionBufferingStartedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackSessionBufferingStartedEventArgs^ UnwrapMediaPlaybackSessionBufferingStartedEventArgs(Local<Value> value) {
     return MediaPlaybackSessionBufferingStartedEventArgs::Unwrap<MediaPlaybackSessionBufferingStartedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackSessionBufferingStartedEventArgs(Local<Object> exports) {
    MediaPlaybackSessionBufferingStartedEventArgs::Init(exports);
  }

  class MediaBreakSeekedOverEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaBreakSeekedOverEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("newPosition").ToLocalChecked(), NewPositionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("oldPosition").ToLocalChecked(), OldPositionGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("seekedOverBreaks").ToLocalChecked(), SeekedOverBreaksGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaBreakSeekedOverEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaBreakSeekedOverEventArgs(::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaBreakSeekedOverEventArgs *wrapperInstance = new MediaBreakSeekedOverEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaBreakSeekedOverEventArgs(winRtInstance));
    }





    static void NewPositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^>(info.This())) {
        return;
      }

      MediaBreakSeekedOverEventArgs *wrapper = MediaBreakSeekedOverEventArgs::Unwrap<MediaBreakSeekedOverEventArgs>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->NewPosition;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OldPositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^>(info.This())) {
        return;
      }

      MediaBreakSeekedOverEventArgs *wrapper = MediaBreakSeekedOverEventArgs::Unwrap<MediaBreakSeekedOverEventArgs>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->OldPosition;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SeekedOverBreaksGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^>(info.This())) {
        return;
      }

      MediaBreakSeekedOverEventArgs *wrapper = MediaBreakSeekedOverEventArgs::Unwrap<MediaBreakSeekedOverEventArgs>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Media::Playback::MediaBreak^>^ result = wrapper->_instance->SeekedOverBreaks;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::Playback::MediaBreak^>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::Playback::MediaBreak^ val) -> Local<Value> {
              return WrapMediaBreak(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(value);
            },
            [](Local<Value> value) -> ::Windows::Media::Playback::MediaBreak^ {
              return UnwrapMediaBreak(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaBreakSeekedOverEventArgs(::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ UnwrapMediaBreakSeekedOverEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaBreakSeekedOverEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaBreakSeekedOverEventArgs(::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaBreakSeekedOverEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaBreakSeekedOverEventArgs^ UnwrapMediaBreakSeekedOverEventArgs(Local<Value> value) {
     return MediaBreakSeekedOverEventArgs::Unwrap<MediaBreakSeekedOverEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaBreakSeekedOverEventArgs(Local<Object> exports) {
    MediaBreakSeekedOverEventArgs::Init(exports);
  }

  class MediaBreakStartedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaBreakStartedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mediaBreak").ToLocalChecked(), MediaBreakGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaBreakStartedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaBreakStartedEventArgs(::Windows::Media::Playback::MediaBreakStartedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaBreakStartedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakStartedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaBreakStartedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaBreakStartedEventArgs *wrapperInstance = new MediaBreakStartedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakStartedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaBreakStartedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaBreakStartedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaBreakStartedEventArgs(winRtInstance));
    }





    static void MediaBreakGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakStartedEventArgs^>(info.This())) {
        return;
      }

      MediaBreakStartedEventArgs *wrapper = MediaBreakStartedEventArgs::Unwrap<MediaBreakStartedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreak^ result = wrapper->_instance->MediaBreak;
        info.GetReturnValue().Set(WrapMediaBreak(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaBreakStartedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaBreakStartedEventArgs(::Windows::Media::Playback::MediaBreakStartedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaBreakStartedEventArgs^ UnwrapMediaBreakStartedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaBreakStartedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaBreakStartedEventArgs(::Windows::Media::Playback::MediaBreakStartedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaBreakStartedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaBreakStartedEventArgs^ UnwrapMediaBreakStartedEventArgs(Local<Value> value) {
     return MediaBreakStartedEventArgs::Unwrap<MediaBreakStartedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaBreakStartedEventArgs(Local<Object> exports) {
    MediaBreakStartedEventArgs::Init(exports);
  }

  class MediaBreakEndedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaBreakEndedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mediaBreak").ToLocalChecked(), MediaBreakGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaBreakEndedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaBreakEndedEventArgs(::Windows::Media::Playback::MediaBreakEndedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaBreakEndedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakEndedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaBreakEndedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaBreakEndedEventArgs *wrapperInstance = new MediaBreakEndedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakEndedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaBreakEndedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaBreakEndedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaBreakEndedEventArgs(winRtInstance));
    }





    static void MediaBreakGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakEndedEventArgs^>(info.This())) {
        return;
      }

      MediaBreakEndedEventArgs *wrapper = MediaBreakEndedEventArgs::Unwrap<MediaBreakEndedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreak^ result = wrapper->_instance->MediaBreak;
        info.GetReturnValue().Set(WrapMediaBreak(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaBreakEndedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaBreakEndedEventArgs(::Windows::Media::Playback::MediaBreakEndedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaBreakEndedEventArgs^ UnwrapMediaBreakEndedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaBreakEndedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaBreakEndedEventArgs(::Windows::Media::Playback::MediaBreakEndedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaBreakEndedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaBreakEndedEventArgs^ UnwrapMediaBreakEndedEventArgs(Local<Value> value) {
     return MediaBreakEndedEventArgs::Unwrap<MediaBreakEndedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaBreakEndedEventArgs(Local<Object> exports) {
    MediaBreakEndedEventArgs::Init(exports);
  }

  class MediaBreakSkippedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaBreakSkippedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("mediaBreak").ToLocalChecked(), MediaBreakGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaBreakSkippedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaBreakSkippedEventArgs(::Windows::Media::Playback::MediaBreakSkippedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaBreakSkippedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSkippedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaBreakSkippedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaBreakSkippedEventArgs *wrapperInstance = new MediaBreakSkippedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSkippedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaBreakSkippedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaBreakSkippedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaBreakSkippedEventArgs(winRtInstance));
    }





    static void MediaBreakGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSkippedEventArgs^>(info.This())) {
        return;
      }

      MediaBreakSkippedEventArgs *wrapper = MediaBreakSkippedEventArgs::Unwrap<MediaBreakSkippedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreak^ result = wrapper->_instance->MediaBreak;
        info.GetReturnValue().Set(WrapMediaBreak(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaBreakSkippedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaBreakSkippedEventArgs(::Windows::Media::Playback::MediaBreakSkippedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaBreakSkippedEventArgs^ UnwrapMediaBreakSkippedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaBreakSkippedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaBreakSkippedEventArgs(::Windows::Media::Playback::MediaBreakSkippedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaBreakSkippedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaBreakSkippedEventArgs^ UnwrapMediaBreakSkippedEventArgs(Local<Value> value) {
     return MediaBreakSkippedEventArgs::Unwrap<MediaBreakSkippedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaBreakSkippedEventArgs(Local<Object> exports) {
    MediaBreakSkippedEventArgs::Init(exports);
  }

  class BackgroundMediaPlayer : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("BackgroundMediaPlayer").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "sendMessageToBackground", SendMessageToBackground);
        Nan::SetMethod(constructor, "sendMessageToForeground", SendMessageToForeground);
        Nan::SetMethod(constructor, "isMediaPlaying", IsMediaPlaying);
        Nan::SetMethod(constructor, "shutdown", Shutdown);
        Nan::SetAccessor(constructor, Nan::New<String>("current").ToLocalChecked(), CurrentGetter);
        
              Local<Function> addListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(AddListener)).ToLocalChecked();
              Nan::Set(constructor, Nan::New<String>("addListener").ToLocalChecked(), addListenerFunc);
              Nan::Set(constructor, Nan::New<String>("on").ToLocalChecked(), addListenerFunc);
              Local<Function> removeListenerFunc = Nan::GetFunction(Nan::New<FunctionTemplate>(RemoveListener)).ToLocalChecked();
              Nan::Set(constructor, Nan::New<String>("removeListener").ToLocalChecked(), removeListenerFunc);
              Nan::Set(constructor, Nan::New<String>("off").ToLocalChecked(), removeListenerFunc);


        Nan::Set(exports, Nan::New<String>("BackgroundMediaPlayer").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      BackgroundMediaPlayer(::Windows::Media::Playback::BackgroundMediaPlayer^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::BackgroundMediaPlayer^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::BackgroundMediaPlayer^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::BackgroundMediaPlayer^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      BackgroundMediaPlayer *wrapperInstance = new BackgroundMediaPlayer(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::BackgroundMediaPlayer^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::BackgroundMediaPlayer^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::BackgroundMediaPlayer^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapBackgroundMediaPlayer(winRtInstance));
    }





    static void SendMessageToBackground(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::ValueSet^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Collections::ValueSet^ arg0 = dynamic_cast<::Windows::Foundation::Collections::ValueSet^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Media::Playback::BackgroundMediaPlayer::SendMessageToBackground(arg0);
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void SendMessageToForeground(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::ValueSet^>(info[0]))
      {
        try
        {
          ::Windows::Foundation::Collections::ValueSet^ arg0 = dynamic_cast<::Windows::Foundation::Collections::ValueSet^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Media::Playback::BackgroundMediaPlayer::SendMessageToForeground(arg0);
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void IsMediaPlaying(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          bool result;
          result = ::Windows::Media::Playback::BackgroundMediaPlayer::IsMediaPlaying();
          info.GetReturnValue().Set(Nan::New<Boolean>(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void Shutdown(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Media::Playback::BackgroundMediaPlayer::Shutdown();
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void CurrentGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      try
      {
        ::Windows::Media::Playback::MediaPlayer^ result = ::Windows::Media::Playback::BackgroundMediaPlayer::Current;
        info.GetReturnValue().Set(WrapMediaPlayer(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      

    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"messageReceivedFromBackground", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::Playback::BackgroundMediaPlayer::MessageReceivedFromBackground::add(
            ref new ::Windows::Foundation::EventHandler<::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = WrapMediaPlayerDataReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"messageReceivedFromForeground", str))
      {
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = ::Windows::Media::Playback::BackgroundMediaPlayer::MessageReceivedFromForeground::add(
            ref new ::Windows::Foundation::EventHandler<::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^>(
            [callbackObjPtr](::Platform::Object^ arg0, ::Windows::Media::Playback::MediaPlayerDataReceivedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = CreateOpaqueWrapper(arg0);
                  wrappedArg1 = WrapMediaPlayerDataReceivedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"messageReceivedFromBackground", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"messageReceivedFromForeground", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"messageReceivedFromBackground", str)) {
          ::Windows::Media::Playback::BackgroundMediaPlayer::MessageReceivedFromBackground::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"messageReceivedFromForeground", str))
        {
          ::Windows::Media::Playback::BackgroundMediaPlayer::MessageReceivedFromForeground::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::BackgroundMediaPlayer^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapBackgroundMediaPlayer(::Windows::Media::Playback::BackgroundMediaPlayer^ wintRtInstance);
      friend ::Windows::Media::Playback::BackgroundMediaPlayer^ UnwrapBackgroundMediaPlayer(Local<Value> value);
  };

  Persistent<FunctionTemplate> BackgroundMediaPlayer::s_constructorTemplate;

  v8::Local<v8::Value> WrapBackgroundMediaPlayer(::Windows::Media::Playback::BackgroundMediaPlayer^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(BackgroundMediaPlayer::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::BackgroundMediaPlayer^ UnwrapBackgroundMediaPlayer(Local<Value> value) {
     return BackgroundMediaPlayer::Unwrap<BackgroundMediaPlayer>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitBackgroundMediaPlayer(Local<Object> exports) {
    BackgroundMediaPlayer::Init(exports);
  }

  class MediaPlaybackCommandManagerPlayReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerPlayReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerPlayReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerPlayReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerPlayReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerPlayReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerPlayReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPlayReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPlayReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPlayReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPlayReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPlayReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPlayReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPlayReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPlayReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPlayReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPlayReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPlayReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerPlayReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPlayReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerPlayReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerPlayReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPlayReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerPlayReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPlayReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerPlayReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerPlayReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerPauseReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerPauseReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerPauseReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerPauseReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerPauseReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerPauseReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerPauseReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPauseReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPauseReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPauseReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPauseReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPauseReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPauseReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPauseReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPauseReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPauseReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPauseReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPauseReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerPauseReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPauseReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerPauseReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerPauseReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPauseReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerPauseReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPauseReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerPauseReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerPauseReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerNextReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerNextReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerNextReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerNextReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerNextReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerNextReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerNextReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerNextReceivedEventArgs *wrapper = MediaPlaybackCommandManagerNextReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerNextReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerNextReceivedEventArgs *wrapper = MediaPlaybackCommandManagerNextReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerNextReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerNextReceivedEventArgs *wrapper = MediaPlaybackCommandManagerNextReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerNextReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerNextReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerNextReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerNextReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerNextReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerNextReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerNextReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerNextReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerNextReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerNextReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerNextReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerNextReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerPreviousReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerPreviousReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerPreviousReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerPreviousReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerPreviousReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerPreviousReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerPreviousReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPreviousReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPreviousReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPreviousReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPreviousReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPreviousReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPreviousReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPreviousReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPreviousReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPreviousReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPreviousReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPreviousReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerPreviousReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPreviousReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerPreviousReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerPreviousReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPreviousReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerPreviousReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPreviousReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerPreviousReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerPreviousReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerFastForwardReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerFastForwardReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerFastForwardReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerFastForwardReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerFastForwardReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerFastForwardReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerFastForwardReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerFastForwardReceivedEventArgs *wrapper = MediaPlaybackCommandManagerFastForwardReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerFastForwardReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerFastForwardReceivedEventArgs *wrapper = MediaPlaybackCommandManagerFastForwardReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerFastForwardReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerFastForwardReceivedEventArgs *wrapper = MediaPlaybackCommandManagerFastForwardReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerFastForwardReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerFastForwardReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerFastForwardReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerFastForwardReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerFastForwardReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerFastForwardReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerFastForwardReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerFastForwardReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerFastForwardReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerFastForwardReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerFastForwardReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerFastForwardReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerRewindReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerRewindReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerRewindReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerRewindReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerRewindReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerRewindReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerRewindReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerRewindReceivedEventArgs *wrapper = MediaPlaybackCommandManagerRewindReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRewindReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerRewindReceivedEventArgs *wrapper = MediaPlaybackCommandManagerRewindReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRewindReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerRewindReceivedEventArgs *wrapper = MediaPlaybackCommandManagerRewindReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRewindReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerRewindReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerRewindReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerRewindReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerRewindReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerRewindReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerRewindReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerRewindReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerRewindReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRewindReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerRewindReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerRewindReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerShuffleReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerShuffleReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isShuffleRequested").ToLocalChecked(), IsShuffleRequestedGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerShuffleReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerShuffleReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerShuffleReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerShuffleReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerShuffleReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerShuffleReceivedEventArgs *wrapper = MediaPlaybackCommandManagerShuffleReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerShuffleReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerShuffleReceivedEventArgs *wrapper = MediaPlaybackCommandManagerShuffleReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerShuffleReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerShuffleReceivedEventArgs *wrapper = MediaPlaybackCommandManagerShuffleReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerShuffleReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void IsShuffleRequestedGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerShuffleReceivedEventArgs *wrapper = MediaPlaybackCommandManagerShuffleReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerShuffleReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->IsShuffleRequested;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerShuffleReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerShuffleReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerShuffleReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerShuffleReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerShuffleReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerShuffleReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerShuffleReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerShuffleReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerShuffleReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerShuffleReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerShuffleReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("autoRepeatMode").ToLocalChecked(), AutoRepeatModeGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs *wrapper = MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs *wrapper = MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs *wrapper = MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AutoRepeatModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs *wrapper = MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs>(info.This());

      try  {
        ::Windows::Media::MediaPlaybackAutoRepeatMode result = wrapper->_instance->AutoRepeatMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerPositionReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerPositionReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("position").ToLocalChecked(), PositionGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerPositionReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerPositionReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerPositionReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerPositionReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerPositionReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPositionReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPositionReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPositionReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPositionReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPositionReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPositionReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPositionReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPositionReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPositionReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerPositionReceivedEventArgs *wrapper = MediaPlaybackCommandManagerPositionReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPositionReceivedEventArgs>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->Position;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPositionReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPositionReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerPositionReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerPositionReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerPositionReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerPositionReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerPositionReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerPositionReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerPositionReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerPositionReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerPositionReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerRateReceivedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerRateReceivedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDeferral", GetDeferral);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("handled").ToLocalChecked(), HandledGetter, HandledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackRate").ToLocalChecked(), PlaybackRateGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerRateReceivedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerRateReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerRateReceivedEventArgs *wrapperInstance = new MediaPlaybackCommandManagerRateReceivedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerRateReceivedEventArgs(winRtInstance));
    }


    static void GetDeferral(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerRateReceivedEventArgs *wrapper = MediaPlaybackCommandManagerRateReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRateReceivedEventArgs>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Deferral^ result;
          result = wrapper->_instance->GetDeferral();
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation", "Deferral", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void HandledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerRateReceivedEventArgs *wrapper = MediaPlaybackCommandManagerRateReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRateReceivedEventArgs>(info.This());

      try  {
        bool result = wrapper->_instance->Handled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void HandledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerRateReceivedEventArgs *wrapper = MediaPlaybackCommandManagerRateReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRateReceivedEventArgs>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->Handled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PlaybackRateGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerRateReceivedEventArgs *wrapper = MediaPlaybackCommandManagerRateReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRateReceivedEventArgs>(info.This());

      try  {
        double result = wrapper->_instance->PlaybackRate;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerRateReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerRateReceivedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerRateReceivedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerRateReceivedEventArgs(::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerRateReceivedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerRateReceivedEventArgs^ UnwrapMediaPlaybackCommandManagerRateReceivedEventArgs(Local<Value> value) {
     return MediaPlaybackCommandManagerRateReceivedEventArgs::Unwrap<MediaPlaybackCommandManagerRateReceivedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerRateReceivedEventArgs(Local<Object> exports) {
    MediaPlaybackCommandManagerRateReceivedEventArgs::Init(exports);
  }

  class MediaPlaybackCommandManagerCommandBehavior : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackCommandManagerCommandBehavior").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);




          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("enablingRule").ToLocalChecked(), EnablingRuleGetter, EnablingRuleSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("commandManager").ToLocalChecked(), CommandManagerGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isEnabled").ToLocalChecked(), IsEnabledGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackCommandManagerCommandBehavior").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackCommandManagerCommandBehavior(::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackCommandManagerCommandBehavior *wrapperInstance = new MediaPlaybackCommandManagerCommandBehavior(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackCommandManagerCommandBehavior(winRtInstance));
    }





    static void EnablingRuleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerCommandBehavior *wrapper = MediaPlaybackCommandManagerCommandBehavior::Unwrap<MediaPlaybackCommandManagerCommandBehavior>(info.This());

      try  {
        ::Windows::Media::Playback::MediaCommandEnablingRule result = wrapper->_instance->EnablingRule;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void EnablingRuleSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerCommandBehavior *wrapper = MediaPlaybackCommandManagerCommandBehavior::Unwrap<MediaPlaybackCommandManagerCommandBehavior>(info.This());

      try {

        ::Windows::Media::Playback::MediaCommandEnablingRule winRtValue = static_cast<::Windows::Media::Playback::MediaCommandEnablingRule>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->EnablingRule = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void CommandManagerGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerCommandBehavior *wrapper = MediaPlaybackCommandManagerCommandBehavior::Unwrap<MediaPlaybackCommandManagerCommandBehavior>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackCommandManager^ result = wrapper->_instance->CommandManager;
        info.GetReturnValue().Set(WrapMediaPlaybackCommandManager(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^>(info.This())) {
        return;
      }

      MediaPlaybackCommandManagerCommandBehavior *wrapper = MediaPlaybackCommandManagerCommandBehavior::Unwrap<MediaPlaybackCommandManagerCommandBehavior>(info.This());

      try  {
        bool result = wrapper->_instance->IsEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"isEnabledChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackCommandManagerCommandBehavior *wrapper = MediaPlaybackCommandManagerCommandBehavior::Unwrap<MediaPlaybackCommandManagerCommandBehavior>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->IsEnabledChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackCommandManagerCommandBehavior(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"isEnabledChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"isEnabledChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackCommandManagerCommandBehavior *wrapper = MediaPlaybackCommandManagerCommandBehavior::Unwrap<MediaPlaybackCommandManagerCommandBehavior>(info.This());
          wrapper->_instance->IsEnabledChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackCommandManagerCommandBehavior(::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ UnwrapMediaPlaybackCommandManagerCommandBehavior(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackCommandManagerCommandBehavior::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackCommandManagerCommandBehavior(::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackCommandManagerCommandBehavior::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackCommandManagerCommandBehavior^ UnwrapMediaPlaybackCommandManagerCommandBehavior(Local<Value> value) {
     return MediaPlaybackCommandManagerCommandBehavior::Unwrap<MediaPlaybackCommandManagerCommandBehavior>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackCommandManagerCommandBehavior(Local<Object> exports) {
    MediaPlaybackCommandManagerCommandBehavior::Init(exports);
  }

  class MediaPlaybackItem : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackItem").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getDisplayProperties", GetDisplayProperties);
            Nan::SetPrototypeMethod(localRef, "applyDisplayProperties", ApplyDisplayProperties);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("audioTracks").ToLocalChecked(), AudioTracksGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("source").ToLocalChecked(), SourceGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("timedMetadataTracks").ToLocalChecked(), TimedMetadataTracksGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("videoTracks").ToLocalChecked(), VideoTracksGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canSkip").ToLocalChecked(), CanSkipGetter, CanSkipSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("breakSchedule").ToLocalChecked(), BreakScheduleGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("durationLimit").ToLocalChecked(), DurationLimitGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("startTime").ToLocalChecked(), StartTimeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("isDisabledInPlaybackList").ToLocalChecked(), IsDisabledInPlaybackListGetter, IsDisabledInPlaybackListSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("autoLoadedDisplayProperties").ToLocalChecked(), AutoLoadedDisplayPropertiesGetter, AutoLoadedDisplayPropertiesSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("totalDownloadProgress").ToLocalChecked(), TotalDownloadProgressGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);

        Nan::SetMethod(constructor, "findFromMediaSource", FindFromMediaSource);


        Nan::Set(exports, Nan::New<String>("MediaPlaybackItem").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackItem(::Windows::Media::Playback::MediaPlaybackItem^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackItem^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackItem^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Core::MediaSource^>(info[0])
        && info[1]->IsNumber())
      {
        try {
          ::Windows::Media::Core::MediaSource^ arg0 = dynamic_cast<::Windows::Media::Core::MediaSource^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::TimeSpan arg1 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[1]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Media::Playback::MediaPlaybackItem(arg0,arg1);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 3
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Core::MediaSource^>(info[0])
        && info[1]->IsNumber()
        && info[2]->IsNumber())
      {
        try {
          ::Windows::Media::Core::MediaSource^ arg0 = dynamic_cast<::Windows::Media::Core::MediaSource^>(NodeRT::Utils::GetObjectInstance(info[0]));
          ::Windows::Foundation::TimeSpan arg1 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[1]).FromMaybe(0));
          ::Windows::Foundation::TimeSpan arg2 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[2]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Media::Playback::MediaPlaybackItem(arg0,arg1,arg2);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Core::MediaSource^>(info[0]))
      {
        try {
          ::Windows::Media::Core::MediaSource^ arg0 = dynamic_cast<::Windows::Media::Core::MediaSource^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          winRtInstance = ref new ::Windows::Media::Playback::MediaPlaybackItem(arg0);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackItem *wrapperInstance = new MediaPlaybackItem(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackItem^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackItem^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackItem(winRtInstance));
    }


    static void GetDisplayProperties(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Media::Playback::MediaItemDisplayProperties^ result;
          result = wrapper->_instance->GetDisplayProperties();
          info.GetReturnValue().Set(WrapMediaItemDisplayProperties(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void ApplyDisplayProperties(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info[0]))
      {
        try
        {
          ::Windows::Media::Playback::MediaItemDisplayProperties^ arg0 = UnwrapMediaItemDisplayProperties(info[0]);
          
          wrapper->_instance->ApplyDisplayProperties(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void FindFromMediaSource(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Core::MediaSource^>(info[0]))
      {
        try
        {
          ::Windows::Media::Core::MediaSource^ arg0 = dynamic_cast<::Windows::Media::Core::MediaSource^>(NodeRT::Utils::GetObjectInstance(info[0]));
          
          ::Windows::Media::Playback::MediaPlaybackItem^ result;
          result = ::Windows::Media::Playback::MediaPlaybackItem::FindFromMediaSource(arg0);
          info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
          return;
        }
        catch (Platform::Exception ^exception)
        {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else  {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }

    static void AudioTracksGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackAudioTrackList^ result = wrapper->_instance->AudioTracks;
        info.GetReturnValue().Set(WrapMediaPlaybackAudioTrackList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SourceGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        ::Windows::Media::Core::MediaSource^ result = wrapper->_instance->Source;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "MediaSource", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TimedMetadataTracksGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ result = wrapper->_instance->TimedMetadataTracks;
        info.GetReturnValue().Set(WrapMediaPlaybackTimedMetadataTrackList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VideoTracksGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackVideoTrackList^ result = wrapper->_instance->VideoTracks;
        info.GetReturnValue().Set(WrapMediaPlaybackVideoTrackList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanSkipGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        bool result = wrapper->_instance->CanSkip;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanSkipSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->CanSkip = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void BreakScheduleGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreakSchedule^ result = wrapper->_instance->BreakSchedule;
        info.GetReturnValue().Set(WrapMediaBreakSchedule(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void DurationLimitGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->DurationLimit;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StartTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        ::Windows::Foundation::TimeSpan result = wrapper->_instance->StartTime;
        info.GetReturnValue().Set(Nan::New<Number>(result.Duration/10000.0));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsDisabledInPlaybackListGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        bool result = wrapper->_instance->IsDisabledInPlaybackList;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void IsDisabledInPlaybackListSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->IsDisabledInPlaybackList = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AutoLoadedDisplayPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        ::Windows::Media::Playback::AutoLoadedDisplayPropertyKind result = wrapper->_instance->AutoLoadedDisplayProperties;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AutoLoadedDisplayPropertiesSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try {

        ::Windows::Media::Playback::AutoLoadedDisplayPropertyKind winRtValue = static_cast<::Windows::Media::Playback::AutoLoadedDisplayPropertyKind>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->AutoLoadedDisplayProperties = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void TotalDownloadProgressGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This())) {
        return;
      }

      MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());

      try  {
        double result = wrapper->_instance->TotalDownloadProgress;
        info.GetReturnValue().Set(Nan::New<Number>(static_cast<double>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"audioTracksChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->AudioTracksChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackItem^, ::Windows::Foundation::Collections::IVectorChangedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackItem^ arg0, ::Windows::Foundation::Collections::IVectorChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackItem(arg0);
                  wrappedArg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IVectorChangedEventArgs", arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"timedMetadataTracksChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->TimedMetadataTracksChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackItem^, ::Windows::Foundation::Collections::IVectorChangedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackItem^ arg0, ::Windows::Foundation::Collections::IVectorChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackItem(arg0);
                  wrappedArg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IVectorChangedEventArgs", arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"videoTracksChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->VideoTracksChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackItem^, ::Windows::Foundation::Collections::IVectorChangedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackItem^ arg0, ::Windows::Foundation::Collections::IVectorChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackItem(arg0);
                  wrappedArg1 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IVectorChangedEventArgs", arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"audioTracksChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"timedMetadataTracksChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"videoTracksChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"audioTracksChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());
          wrapper->_instance->AudioTracksChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"timedMetadataTracksChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());
          wrapper->_instance->TimedMetadataTracksChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"videoTracksChanged", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackItem *wrapper = MediaPlaybackItem::Unwrap<MediaPlaybackItem>(info.This());
          wrapper->_instance->VideoTracksChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlaybackItem^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackItem(::Windows::Media::Playback::MediaPlaybackItem^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackItem^ UnwrapMediaPlaybackItem(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackItem::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackItem(::Windows::Media::Playback::MediaPlaybackItem^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackItem::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackItem^ UnwrapMediaPlaybackItem(Local<Value> value) {
     return MediaPlaybackItem::Unwrap<MediaPlaybackItem>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackItem(Local<Object> exports) {
    MediaPlaybackItem::Init(exports);
  }

  class IMediaPlaybackSource : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IMediaPlaybackSource").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);






        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IMediaPlaybackSource").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IMediaPlaybackSource(::Windows::Media::Playback::IMediaPlaybackSource^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::IMediaPlaybackSource^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::IMediaPlaybackSource^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::IMediaPlaybackSource^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IMediaPlaybackSource *wrapperInstance = new IMediaPlaybackSource(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::IMediaPlaybackSource^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::IMediaPlaybackSource^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::IMediaPlaybackSource^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIMediaPlaybackSource(winRtInstance));
    }







    private:
      ::Windows::Media::Playback::IMediaPlaybackSource^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIMediaPlaybackSource(::Windows::Media::Playback::IMediaPlaybackSource^ wintRtInstance);
      friend ::Windows::Media::Playback::IMediaPlaybackSource^ UnwrapIMediaPlaybackSource(Local<Value> value);
  };

  Persistent<FunctionTemplate> IMediaPlaybackSource::s_constructorTemplate;

  v8::Local<v8::Value> WrapIMediaPlaybackSource(::Windows::Media::Playback::IMediaPlaybackSource^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IMediaPlaybackSource::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::IMediaPlaybackSource^ UnwrapIMediaPlaybackSource(Local<Value> value) {
     return IMediaPlaybackSource::Unwrap<IMediaPlaybackSource>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIMediaPlaybackSource(Local<Object> exports) {
    IMediaPlaybackSource::Init(exports);
  }

  class MediaPlaybackAudioTrackList : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackAudioTrackList").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getAt", GetAt);
            Nan::SetPrototypeMethod(localRef, "indexOf", IndexOf);
            Nan::SetPrototypeMethod(localRef, "getMany", GetMany);
            Nan::SetPrototypeMethod(localRef, "first", First);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("selectedIndex").ToLocalChecked(), SelectedIndexGetter, SelectedIndexSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackAudioTrackList").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackAudioTrackList(::Windows::Media::Playback::MediaPlaybackAudioTrackList^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackAudioTrackList^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackAudioTrackList^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackAudioTrackList *wrapperInstance = new MediaPlaybackAudioTrackList(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackAudioTrackList^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackAudioTrackList^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackAudioTrackList(winRtInstance));
    }


    static void GetAt(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackAudioTrackList *wrapper = MediaPlaybackAudioTrackList::Unwrap<MediaPlaybackAudioTrackList>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Media::Core::AudioTrack^ result;
          result = wrapper->_instance->GetAt(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "AudioTrack", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IndexOf(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackAudioTrackList *wrapper = MediaPlaybackAudioTrackList::Unwrap<MediaPlaybackAudioTrackList>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Core::AudioTrack^>(info[0]))
      {
        try
        {
          ::Windows::Media::Core::AudioTrack^ arg0 = dynamic_cast<::Windows::Media::Core::AudioTrack^>(NodeRT::Utils::GetObjectInstance(info[0]));
          unsigned int arg1;
          
          bool result;
          result = wrapper->_instance->IndexOf(arg0, &arg1);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("boolean").ToLocalChecked(), Nan::New<Boolean>(result));
          Nan::Set(resObj, Nan::New<String>("index").ToLocalChecked(), Nan::New<Integer>(arg1));
          info.GetReturnValue().Set(resObj);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetMany(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Not implemented")));
    }
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackAudioTrackList *wrapper = MediaPlaybackAudioTrackList::Unwrap<MediaPlaybackAudioTrackList>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Media::Core::AudioTrack^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Media::Core::AudioTrack^>::CreateIteratorWrapper(result, 
            [](::Windows::Media::Core::AudioTrack^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "AudioTrack", val);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void SelectedIndexGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackAudioTrackList *wrapper = MediaPlaybackAudioTrackList::Unwrap<MediaPlaybackAudioTrackList>(info.This());

      try  {
        int result = wrapper->_instance->SelectedIndex;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SelectedIndexSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackAudioTrackList *wrapper = MediaPlaybackAudioTrackList::Unwrap<MediaPlaybackAudioTrackList>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->SelectedIndex = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"selectedIndexChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackAudioTrackList *wrapper = MediaPlaybackAudioTrackList::Unwrap<MediaPlaybackAudioTrackList>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->SelectedIndexChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Core::ISingleSelectMediaTrackList^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Core::ISingleSelectMediaTrackList^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "ISingleSelectMediaTrackList", arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"selectedIndexChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"selectedIndexChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackAudioTrackList^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackAudioTrackList *wrapper = MediaPlaybackAudioTrackList::Unwrap<MediaPlaybackAudioTrackList>(info.This());
          wrapper->_instance->SelectedIndexChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlaybackAudioTrackList^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackAudioTrackList(::Windows::Media::Playback::MediaPlaybackAudioTrackList^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackAudioTrackList^ UnwrapMediaPlaybackAudioTrackList(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackAudioTrackList::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackAudioTrackList(::Windows::Media::Playback::MediaPlaybackAudioTrackList^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackAudioTrackList::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackAudioTrackList^ UnwrapMediaPlaybackAudioTrackList(Local<Value> value) {
     return MediaPlaybackAudioTrackList::Unwrap<MediaPlaybackAudioTrackList>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackAudioTrackList(Local<Object> exports) {
    MediaPlaybackAudioTrackList::Init(exports);
  }

  class MediaPlaybackVideoTrackList : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackVideoTrackList").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getAt", GetAt);
            Nan::SetPrototypeMethod(localRef, "indexOf", IndexOf);
            Nan::SetPrototypeMethod(localRef, "getMany", GetMany);
            Nan::SetPrototypeMethod(localRef, "first", First);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("selectedIndex").ToLocalChecked(), SelectedIndexGetter, SelectedIndexSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackVideoTrackList").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackVideoTrackList(::Windows::Media::Playback::MediaPlaybackVideoTrackList^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackVideoTrackList^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackVideoTrackList^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackVideoTrackList *wrapperInstance = new MediaPlaybackVideoTrackList(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackVideoTrackList^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackVideoTrackList^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackVideoTrackList(winRtInstance));
    }


    static void GetAt(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackVideoTrackList *wrapper = MediaPlaybackVideoTrackList::Unwrap<MediaPlaybackVideoTrackList>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Media::Core::VideoTrack^ result;
          result = wrapper->_instance->GetAt(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "VideoTrack", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IndexOf(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackVideoTrackList *wrapper = MediaPlaybackVideoTrackList::Unwrap<MediaPlaybackVideoTrackList>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Core::VideoTrack^>(info[0]))
      {
        try
        {
          ::Windows::Media::Core::VideoTrack^ arg0 = dynamic_cast<::Windows::Media::Core::VideoTrack^>(NodeRT::Utils::GetObjectInstance(info[0]));
          unsigned int arg1;
          
          bool result;
          result = wrapper->_instance->IndexOf(arg0, &arg1);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("boolean").ToLocalChecked(), Nan::New<Boolean>(result));
          Nan::Set(resObj, Nan::New<String>("index").ToLocalChecked(), Nan::New<Integer>(arg1));
          info.GetReturnValue().Set(resObj);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetMany(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Not implemented")));
    }
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackVideoTrackList *wrapper = MediaPlaybackVideoTrackList::Unwrap<MediaPlaybackVideoTrackList>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Media::Core::VideoTrack^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Media::Core::VideoTrack^>::CreateIteratorWrapper(result, 
            [](::Windows::Media::Core::VideoTrack^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "VideoTrack", val);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void SelectedIndexGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackVideoTrackList *wrapper = MediaPlaybackVideoTrackList::Unwrap<MediaPlaybackVideoTrackList>(info.This());

      try  {
        int result = wrapper->_instance->SelectedIndex;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void SelectedIndexSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackVideoTrackList *wrapper = MediaPlaybackVideoTrackList::Unwrap<MediaPlaybackVideoTrackList>(info.This());

      try {

        int winRtValue = static_cast<int>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->SelectedIndex = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"selectedIndexChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackVideoTrackList *wrapper = MediaPlaybackVideoTrackList::Unwrap<MediaPlaybackVideoTrackList>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->SelectedIndexChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Core::ISingleSelectMediaTrackList^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Core::ISingleSelectMediaTrackList^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "ISingleSelectMediaTrackList", arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"selectedIndexChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"selectedIndexChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackVideoTrackList^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackVideoTrackList *wrapper = MediaPlaybackVideoTrackList::Unwrap<MediaPlaybackVideoTrackList>(info.This());
          wrapper->_instance->SelectedIndexChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlaybackVideoTrackList^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackVideoTrackList(::Windows::Media::Playback::MediaPlaybackVideoTrackList^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackVideoTrackList^ UnwrapMediaPlaybackVideoTrackList(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackVideoTrackList::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackVideoTrackList(::Windows::Media::Playback::MediaPlaybackVideoTrackList^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackVideoTrackList::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackVideoTrackList^ UnwrapMediaPlaybackVideoTrackList(Local<Value> value) {
     return MediaPlaybackVideoTrackList::Unwrap<MediaPlaybackVideoTrackList>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackVideoTrackList(Local<Object> exports) {
    MediaPlaybackVideoTrackList::Init(exports);
  }

  class MediaPlaybackTimedMetadataTrackList : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackTimedMetadataTrackList").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "getAt", GetAt);
            Nan::SetPrototypeMethod(localRef, "indexOf", IndexOf);
            Nan::SetPrototypeMethod(localRef, "getMany", GetMany);
            Nan::SetPrototypeMethod(localRef, "first", First);
            Nan::SetPrototypeMethod(localRef, "getPresentationMode", GetPresentationMode);
            Nan::SetPrototypeMethod(localRef, "setPresentationMode", SetPresentationMode);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);


        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackTimedMetadataTrackList").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackTimedMetadataTrackList(::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackTimedMetadataTrackList *wrapperInstance = new MediaPlaybackTimedMetadataTrackList(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackTimedMetadataTrackList(winRtInstance));
    }


    static void GetAt(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackTimedMetadataTrackList *wrapper = MediaPlaybackTimedMetadataTrackList::Unwrap<MediaPlaybackTimedMetadataTrackList>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Media::Core::TimedMetadataTrack^ result;
          result = wrapper->_instance->GetAt(arg0);
          info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "TimedMetadataTrack", result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void IndexOf(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackTimedMetadataTrackList *wrapper = MediaPlaybackTimedMetadataTrackList::Unwrap<MediaPlaybackTimedMetadataTrackList>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Core::TimedMetadataTrack^>(info[0]))
      {
        try
        {
          ::Windows::Media::Core::TimedMetadataTrack^ arg0 = dynamic_cast<::Windows::Media::Core::TimedMetadataTrack^>(NodeRT::Utils::GetObjectInstance(info[0]));
          unsigned int arg1;
          
          bool result;
          result = wrapper->_instance->IndexOf(arg0, &arg1);
          Local<Object> resObj = Nan::New<Object>();
          Nan::Set(resObj, Nan::New<String>("boolean").ToLocalChecked(), Nan::New<Boolean>(result));
          Nan::Set(resObj, Nan::New<String>("index").ToLocalChecked(), Nan::New<Integer>(arg1));
          info.GetReturnValue().Set(resObj);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetMany(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Not implemented")));
    }
    static void First(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackTimedMetadataTrackList *wrapper = MediaPlaybackTimedMetadataTrackList::Unwrap<MediaPlaybackTimedMetadataTrackList>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Foundation::Collections::IIterator<::Windows::Media::Core::TimedMetadataTrack^>^ result;
          result = wrapper->_instance->First();
          info.GetReturnValue().Set(NodeRT::Collections::IteratorWrapper<::Windows::Media::Core::TimedMetadataTrack^>::CreateIteratorWrapper(result, 
            [](::Windows::Media::Core::TimedMetadataTrack^ val) -> Local<Value> {
              return NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "TimedMetadataTrack", val);
            }
          ));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void GetPresentationMode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackTimedMetadataTrackList *wrapper = MediaPlaybackTimedMetadataTrackList::Unwrap<MediaPlaybackTimedMetadataTrackList>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Media::Playback::TimedMetadataTrackPresentationMode result;
          result = wrapper->_instance->GetPresentationMode(arg0);
          info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetPresentationMode(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info.This())) {
        return;
      }

      MediaPlaybackTimedMetadataTrackList *wrapper = MediaPlaybackTimedMetadataTrackList::Unwrap<MediaPlaybackTimedMetadataTrackList>(info.This());

      if (info.Length() == 2
        && info[0]->IsUint32()
        && info[1]->IsInt32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          ::Windows::Media::Playback::TimedMetadataTrackPresentationMode arg1 = static_cast<::Windows::Media::Playback::TimedMetadataTrackPresentationMode>(Nan::To<int32_t>(info[1]).FromMaybe(0));
          
          wrapper->_instance->SetPresentationMode(arg0, arg1);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }





    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"presentationModeChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackTimedMetadataTrackList *wrapper = MediaPlaybackTimedMetadataTrackList::Unwrap<MediaPlaybackTimedMetadataTrackList>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->PresentationModeChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^, ::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ arg0, ::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackTimedMetadataTrackList(arg0);
                  wrappedArg1 = WrapTimedMetadataPresentationModeChangedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"presentationModeChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"presentationModeChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackTimedMetadataTrackList *wrapper = MediaPlaybackTimedMetadataTrackList::Unwrap<MediaPlaybackTimedMetadataTrackList>(info.This());
          wrapper->_instance->PresentationModeChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackTimedMetadataTrackList(::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ UnwrapMediaPlaybackTimedMetadataTrackList(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackTimedMetadataTrackList::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackTimedMetadataTrackList(::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackTimedMetadataTrackList::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackTimedMetadataTrackList^ UnwrapMediaPlaybackTimedMetadataTrackList(Local<Value> value) {
     return MediaPlaybackTimedMetadataTrackList::Unwrap<MediaPlaybackTimedMetadataTrackList>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackTimedMetadataTrackList(Local<Object> exports) {
    MediaPlaybackTimedMetadataTrackList::Init(exports);
  }

  class MediaBreakSchedule : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaBreakSchedule").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "insertMidrollBreak", InsertMidrollBreak);
            Nan::SetPrototypeMethod(localRef, "removeMidrollBreak", RemoveMidrollBreak);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("prerollBreak").ToLocalChecked(), PrerollBreakGetter, PrerollBreakSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("postrollBreak").ToLocalChecked(), PostrollBreakGetter, PostrollBreakSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("midrollBreaks").ToLocalChecked(), MidrollBreaksGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackItem").ToLocalChecked(), PlaybackItemGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaBreakSchedule").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaBreakSchedule(::Windows::Media::Playback::MediaBreakSchedule^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaBreakSchedule^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaBreakSchedule^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaBreakSchedule *wrapperInstance = new MediaBreakSchedule(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaBreakSchedule^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaBreakSchedule^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaBreakSchedule(winRtInstance));
    }


    static void InsertMidrollBreak(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This())) {
        return;
      }

      MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info[0]))
      {
        try
        {
          ::Windows::Media::Playback::MediaBreak^ arg0 = UnwrapMediaBreak(info[0]);
          
          wrapper->_instance->InsertMidrollBreak(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void RemoveMidrollBreak(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This())) {
        return;
      }

      MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info[0]))
      {
        try
        {
          ::Windows::Media::Playback::MediaBreak^ arg0 = UnwrapMediaBreak(info[0]);
          
          wrapper->_instance->RemoveMidrollBreak(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void PrerollBreakGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This())) {
        return;
      }

      MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreak^ result = wrapper->_instance->PrerollBreak;
        info.GetReturnValue().Set(WrapMediaBreak(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PrerollBreakSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This())) {
        return;
      }

      MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());

      try {

        ::Windows::Media::Playback::MediaBreak^ winRtValue = dynamic_cast<::Windows::Media::Playback::MediaBreak^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->PrerollBreak = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void PostrollBreakGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This())) {
        return;
      }

      MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreak^ result = wrapper->_instance->PostrollBreak;
        info.GetReturnValue().Set(WrapMediaBreak(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PostrollBreakSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This())) {
        return;
      }

      MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());

      try {

        ::Windows::Media::Playback::MediaBreak^ winRtValue = dynamic_cast<::Windows::Media::Playback::MediaBreak^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->PostrollBreak = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void MidrollBreaksGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This())) {
        return;
      }

      MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Media::Playback::MediaBreak^>^ result = wrapper->_instance->MidrollBreaks;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::Playback::MediaBreak^>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::Playback::MediaBreak^ val) -> Local<Value> {
              return WrapMediaBreak(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(value);
            },
            [](Local<Value> value) -> ::Windows::Media::Playback::MediaBreak^ {
              return UnwrapMediaBreak(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This())) {
        return;
      }

      MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItem^ result = wrapper->_instance->PlaybackItem;
        info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"scheduleChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->ScheduleChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaBreakSchedule^, ::Platform::Object^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaBreakSchedule^ arg0, ::Platform::Object^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaBreakSchedule(arg0);
                  wrappedArg1 = CreateOpaqueWrapper(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"scheduleChanged", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"scheduleChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreakSchedule^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaBreakSchedule *wrapper = MediaBreakSchedule::Unwrap<MediaBreakSchedule>(info.This());
          wrapper->_instance->ScheduleChanged::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaBreakSchedule^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaBreakSchedule(::Windows::Media::Playback::MediaBreakSchedule^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaBreakSchedule^ UnwrapMediaBreakSchedule(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaBreakSchedule::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaBreakSchedule(::Windows::Media::Playback::MediaBreakSchedule^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaBreakSchedule::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaBreakSchedule^ UnwrapMediaBreakSchedule(Local<Value> value) {
     return MediaBreakSchedule::Unwrap<MediaBreakSchedule>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaBreakSchedule(Local<Object> exports) {
    MediaBreakSchedule::Init(exports);
  }

  class MediaItemDisplayProperties : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaItemDisplayProperties").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "clearAll", ClearAll);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("type").ToLocalChecked(), TypeGetter, TypeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("thumbnail").ToLocalChecked(), ThumbnailGetter, ThumbnailSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("musicProperties").ToLocalChecked(), MusicPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("videoProperties").ToLocalChecked(), VideoPropertiesGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaItemDisplayProperties").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaItemDisplayProperties(::Windows::Media::Playback::MediaItemDisplayProperties^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaItemDisplayProperties^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaItemDisplayProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaItemDisplayProperties *wrapperInstance = new MediaItemDisplayProperties(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaItemDisplayProperties^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaItemDisplayProperties^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaItemDisplayProperties(winRtInstance));
    }


    static void ClearAll(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info.This())) {
        return;
      }

      MediaItemDisplayProperties *wrapper = MediaItemDisplayProperties::Unwrap<MediaItemDisplayProperties>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          wrapper->_instance->ClearAll();
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void TypeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info.This())) {
        return;
      }

      MediaItemDisplayProperties *wrapper = MediaItemDisplayProperties::Unwrap<MediaItemDisplayProperties>(info.This());

      try  {
        ::Windows::Media::MediaPlaybackType result = wrapper->_instance->Type;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TypeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsInt32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info.This())) {
        return;
      }

      MediaItemDisplayProperties *wrapper = MediaItemDisplayProperties::Unwrap<MediaItemDisplayProperties>(info.This());

      try {

        ::Windows::Media::MediaPlaybackType winRtValue = static_cast<::Windows::Media::MediaPlaybackType>(Nan::To<int32_t>(value).FromMaybe(0));

        wrapper->_instance->Type = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ThumbnailGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info.This())) {
        return;
      }

      MediaItemDisplayProperties *wrapper = MediaItemDisplayProperties::Unwrap<MediaItemDisplayProperties>(info.This());

      try  {
        ::Windows::Storage::Streams::RandomAccessStreamReference^ result = wrapper->_instance->Thumbnail;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Storage.Streams", "RandomAccessStreamReference", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ThumbnailSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Storage::Streams::RandomAccessStreamReference^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info.This())) {
        return;
      }

      MediaItemDisplayProperties *wrapper = MediaItemDisplayProperties::Unwrap<MediaItemDisplayProperties>(info.This());

      try {

        ::Windows::Storage::Streams::RandomAccessStreamReference^ winRtValue = dynamic_cast<::Windows::Storage::Streams::RandomAccessStreamReference^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->Thumbnail = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void MusicPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info.This())) {
        return;
      }

      MediaItemDisplayProperties *wrapper = MediaItemDisplayProperties::Unwrap<MediaItemDisplayProperties>(info.This());

      try  {
        ::Windows::Media::MusicDisplayProperties^ result = wrapper->_instance->MusicProperties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media", "MusicDisplayProperties", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void VideoPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaItemDisplayProperties^>(info.This())) {
        return;
      }

      MediaItemDisplayProperties *wrapper = MediaItemDisplayProperties::Unwrap<MediaItemDisplayProperties>(info.This());

      try  {
        ::Windows::Media::VideoDisplayProperties^ result = wrapper->_instance->VideoProperties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media", "VideoDisplayProperties", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaItemDisplayProperties^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaItemDisplayProperties(::Windows::Media::Playback::MediaItemDisplayProperties^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaItemDisplayProperties^ UnwrapMediaItemDisplayProperties(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaItemDisplayProperties::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaItemDisplayProperties(::Windows::Media::Playback::MediaItemDisplayProperties^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaItemDisplayProperties::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaItemDisplayProperties^ UnwrapMediaItemDisplayProperties(Local<Value> value) {
     return MediaItemDisplayProperties::Unwrap<MediaItemDisplayProperties>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaItemDisplayProperties(Local<Object> exports) {
    MediaItemDisplayProperties::Init(exports);
  }

  class MediaBreak : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaBreak").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("canStart").ToLocalChecked(), CanStartGetter, CanStartSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("customProperties").ToLocalChecked(), CustomPropertiesGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("insertionMethod").ToLocalChecked(), InsertionMethodGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("playbackList").ToLocalChecked(), PlaybackListGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("presentationPosition").ToLocalChecked(), PresentationPositionGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaBreak").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaBreak(::Windows::Media::Playback::MediaBreak^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaBreak^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaBreak^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 1
        && info[0]->IsInt32())
      {
        try {
          ::Windows::Media::Playback::MediaBreakInsertionMethod arg0 = static_cast<::Windows::Media::Playback::MediaBreakInsertionMethod>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Media::Playback::MediaBreak(arg0);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 2
        && info[0]->IsInt32()
        && info[1]->IsNumber())
      {
        try {
          ::Windows::Media::Playback::MediaBreakInsertionMethod arg0 = static_cast<::Windows::Media::Playback::MediaBreakInsertionMethod>(Nan::To<int32_t>(info[0]).FromMaybe(0));
          ::Windows::Foundation::TimeSpan arg1 = NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(info[1]).FromMaybe(0));
          
          winRtInstance = ref new ::Windows::Media::Playback::MediaBreak(arg0,arg1);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaBreak *wrapperInstance = new MediaBreak(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaBreak^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaBreak^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaBreak(winRtInstance));
    }





    static void CanStartGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info.This())) {
        return;
      }

      MediaBreak *wrapper = MediaBreak::Unwrap<MediaBreak>(info.This());

      try  {
        bool result = wrapper->_instance->CanStart;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CanStartSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info.This())) {
        return;
      }

      MediaBreak *wrapper = MediaBreak::Unwrap<MediaBreak>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->CanStart = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void CustomPropertiesGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info.This())) {
        return;
      }

      MediaBreak *wrapper = MediaBreak::Unwrap<MediaBreak>(info.This());

      try  {
        ::Windows::Foundation::Collections::ValueSet^ result = wrapper->_instance->CustomProperties;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "ValueSet", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void InsertionMethodGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info.This())) {
        return;
      }

      MediaBreak *wrapper = MediaBreak::Unwrap<MediaBreak>(info.This());

      try  {
        ::Windows::Media::Playback::MediaBreakInsertionMethod result = wrapper->_instance->InsertionMethod;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PlaybackListGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info.This())) {
        return;
      }

      MediaBreak *wrapper = MediaBreak::Unwrap<MediaBreak>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackList^ result = wrapper->_instance->PlaybackList;
        info.GetReturnValue().Set(WrapMediaPlaybackList(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void PresentationPositionGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaBreak^>(info.This())) {
        return;
      }

      MediaBreak *wrapper = MediaBreak::Unwrap<MediaBreak>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->PresentationPosition;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaBreak^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaBreak(::Windows::Media::Playback::MediaBreak^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaBreak^ UnwrapMediaBreak(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaBreak::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaBreak(::Windows::Media::Playback::MediaBreak^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaBreak::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaBreak^ UnwrapMediaBreak(Local<Value> value) {
     return MediaBreak::Unwrap<MediaBreak>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaBreak(Local<Object> exports) {
    MediaBreak::Init(exports);
  }

  class MediaPlaybackList : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackList").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "moveNext", MoveNext);
            Nan::SetPrototypeMethod(localRef, "movePrevious", MovePrevious);
            Nan::SetPrototypeMethod(localRef, "moveTo", MoveTo);
            Nan::SetPrototypeMethod(localRef, "setShuffledItems", SetShuffledItems);
          


          
          Nan::SetPrototypeMethod(localRef,"addListener", AddListener);
          Nan::SetPrototypeMethod(localRef,"on", AddListener);
          Nan::SetPrototypeMethod(localRef,"removeListener", RemoveListener);
          Nan::SetPrototypeMethod(localRef, "off", RemoveListener);

          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("shuffleEnabled").ToLocalChecked(), ShuffleEnabledGetter, ShuffleEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("autoRepeatEnabled").ToLocalChecked(), AutoRepeatEnabledGetter, AutoRepeatEnabledSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currentItem").ToLocalChecked(), CurrentItemGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currentItemIndex").ToLocalChecked(), CurrentItemIndexGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("items").ToLocalChecked(), ItemsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("startingItem").ToLocalChecked(), StartingItemGetter, StartingItemSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxPrefetchTime").ToLocalChecked(), MaxPrefetchTimeGetter, MaxPrefetchTimeSetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("shuffledItems").ToLocalChecked(), ShuffledItemsGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("maxPlayedItemsToKeepOpen").ToLocalChecked(), MaxPlayedItemsToKeepOpenGetter, MaxPlayedItemsToKeepOpenSetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackList").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackList(::Windows::Media::Playback::MediaPlaybackList^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackList^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackList^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
      else if (info.Length() == 0)
      {
        try {
          winRtInstance = ref new ::Windows::Media::Playback::MediaPlaybackList();
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackList *wrapperInstance = new MediaPlaybackList(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackList^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackList^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackList(winRtInstance));
    }


    static void MoveNext(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Media::Playback::MediaPlaybackItem^ result;
          result = wrapper->_instance->MoveNext();
          info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MovePrevious(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      if (info.Length() == 0)
      {
        try
        {
          ::Windows::Media::Playback::MediaPlaybackItem^ result;
          result = wrapper->_instance->MovePrevious();
          info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void MoveTo(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      if (info.Length() == 1
        && info[0]->IsUint32())
      {
        try
        {
          unsigned int arg0 = static_cast<unsigned int>(Nan::To<uint32_t>(info[0]).FromMaybe(0));
          
          ::Windows::Media::Playback::MediaPlaybackItem^ result;
          result = wrapper->_instance->MoveTo(arg0);
          info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }
    static void SetShuffledItems(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      if (info.Length() == 1
        && (NodeRT::Utils::IsWinRtWrapperOf<::Windows::Foundation::Collections::IIterable<::Windows::Media::Playback::MediaPlaybackItem^>^>(info[0]) || info[0]->IsArray()))
      {
        try
        {
          ::Windows::Foundation::Collections::IIterable<::Windows::Media::Playback::MediaPlaybackItem^>^ arg0 = 
            [] (v8::Local<v8::Value> value) -> ::Windows::Foundation::Collections::IIterable<::Windows::Media::Playback::MediaPlaybackItem^>^
            {
              if (value->IsArray())
              {
                return NodeRT::Collections::JsArrayToWinrtVector<::Windows::Media::Playback::MediaPlaybackItem^>(value.As<Array>(), 
                 [](Local<Value> value) -> bool {
                   return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(value);
                 },
                 [](Local<Value> value) -> ::Windows::Media::Playback::MediaPlaybackItem^ {
                   return UnwrapMediaPlaybackItem(value);
                 }
                );
              }
              else
              {
                return dynamic_cast<::Windows::Foundation::Collections::IIterable<::Windows::Media::Playback::MediaPlaybackItem^>^>(NodeRT::Utils::GetObjectInstance(value));
              }
            } (info[0]);
          
          wrapper->_instance->SetShuffledItems(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void ShuffleEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        bool result = wrapper->_instance->ShuffleEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ShuffleEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->ShuffleEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void AutoRepeatEnabledGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        bool result = wrapper->_instance->AutoRepeatEnabled;
        info.GetReturnValue().Set(Nan::New<Boolean>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void AutoRepeatEnabledSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsBoolean()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try {

        bool winRtValue = Nan::To<bool>(value).FromMaybe(false);

        wrapper->_instance->AutoRepeatEnabled = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void CurrentItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItem^ result = wrapper->_instance->CurrentItem;
        info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void CurrentItemIndexGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        unsigned int result = wrapper->_instance->CurrentItemIndex;
        info.GetReturnValue().Set(Nan::New<Integer>(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ItemsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        ::Windows::Foundation::Collections::IObservableVector<::Windows::Media::Playback::MediaPlaybackItem^>^ result = wrapper->_instance->Items;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Foundation.Collections", "IObservableVector`1", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StartingItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItem^ result = wrapper->_instance->StartingItem;
        info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void StartingItemSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(value)) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try {

        ::Windows::Media::Playback::MediaPlaybackItem^ winRtValue = dynamic_cast<::Windows::Media::Playback::MediaPlaybackItem^>(NodeRT::Utils::GetObjectInstance(value));

        wrapper->_instance->StartingItem = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void MaxPrefetchTimeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ result = wrapper->_instance->MaxPrefetchTime;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Number>(result->Value.Duration/10000.0)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MaxPrefetchTimeSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsNumber()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try {

        ::Platform::IBox<::Windows::Foundation::TimeSpan>^ winRtValue = ref new ::Platform::Box<::Windows::Foundation::TimeSpan>(NodeRT::Utils::TimeSpanFromMilli(Nan::To<int64_t>(value).FromMaybe(0)));

        wrapper->_instance->MaxPrefetchTime = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      
    static void ShuffledItemsGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        ::Windows::Foundation::Collections::IVectorView<::Windows::Media::Playback::MediaPlaybackItem^>^ result = wrapper->_instance->ShuffledItems;
        info.GetReturnValue().Set(NodeRT::Collections::VectorViewWrapper<::Windows::Media::Playback::MediaPlaybackItem^>::CreateVectorViewWrapper(result, 
            [](::Windows::Media::Playback::MediaPlaybackItem^ val) -> Local<Value> {
              return WrapMediaPlaybackItem(val);
            },
            [](Local<Value> value) -> bool {
              return NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItem^>(value);
            },
            [](Local<Value> value) -> ::Windows::Media::Playback::MediaPlaybackItem^ {
              return UnwrapMediaPlaybackItem(value);
            }
          ));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MaxPlayedItemsToKeepOpenGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try  {
        ::Platform::IBox<unsigned int>^ result = wrapper->_instance->MaxPlayedItemsToKeepOpen;
        info.GetReturnValue().Set(result ? static_cast<Local<Value>>(Nan::New<Integer>(result->Value)) : Undefined());
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void MaxPlayedItemsToKeepOpenSetter(Local<String> property, Local<Value> value, const Nan::PropertyCallbackInfo<void> &info) {
      HandleScope scope;

      if (!value->IsUint32()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Value to set is of unexpected type")));
        return;
      }

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This())) {
        return;
      }

      MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());

      try {

        ::Platform::IBox<unsigned int>^ winRtValue = ref new ::Platform::Box<unsigned int>(static_cast<unsigned int>(Nan::To<uint32_t>(value).FromMaybe(0)));

        wrapper->_instance->MaxPlayedItemsToKeepOpen = winRtValue;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }
    }
      


    static void AddListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected arguments are eventName(string),callback(function)")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      Local<Function> callback = info[1].As<Function>();

      ::Windows::Foundation::EventRegistrationToken registrationToken;
      if (NodeRT::Utils::CaseInsenstiveEquals(L"currentItemChanged", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->CurrentItemChanged::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackList^, ::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackList^ arg0, ::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackList(arg0);
                  wrappedArg1 = WrapCurrentMediaPlaybackItemChangedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"itemFailed", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->ItemFailed::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackList^, ::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackList^ arg0, ::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackList(arg0);
                  wrappedArg1 = WrapMediaPlaybackItemFailedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
      else if (NodeRT::Utils::CaseInsenstiveEquals(L"itemOpened", str))
      {
        if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This()))
        {
          Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
      return;
        }
        MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());
      
        try {
          Persistent<Object>* perstPtr = new Persistent<Object>();
          perstPtr->Reset(NodeRT::Utils::CreateCallbackObjectInDomain(callback));
          std::shared_ptr<Persistent<Object>> callbackObjPtr(perstPtr,
            [] (Persistent<Object> *ptr ) {
              NodeUtils::Async::RunOnMain([ptr]() {
                ptr->Reset();
                delete ptr;
            });
          });

          registrationToken = wrapper->_instance->ItemOpened::add(
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::Media::Playback::MediaPlaybackList^, ::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^>(
            [callbackObjPtr](::Windows::Media::Playback::MediaPlaybackList^ arg0, ::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ arg1) {
              NodeUtils::Async::RunOnMain([callbackObjPtr , arg0, arg1]() {
                HandleScope scope;


                Local<Value> wrappedArg0;
                Local<Value> wrappedArg1;

                {
                  TryCatch tryCatch;


                  wrappedArg0 = WrapMediaPlaybackList(arg0);
                  wrappedArg1 = WrapMediaPlaybackItemOpenedEventArgs(arg1);


                  if (wrappedArg0.IsEmpty()) wrappedArg0 = Undefined();
                  if (wrappedArg1.IsEmpty()) wrappedArg1 = Undefined();
                }

                Local<Value> args[] = { wrappedArg0, wrappedArg1 };
                Local<Object> callbackObjLocalRef = Nan::New<Object>(*callbackObjPtr);
                NodeRT::Utils::CallCallbackInDomain(callbackObjLocalRef, _countof(args), args);
              });
            })
          );
        }
        catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }

      }
 else  {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Value> tokenMapVal = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());
      Local<Object> tokenMap;

      if (tokenMapVal.IsEmpty() || Nan::Equals(tokenMapVal, Undefined()).FromMaybe(false)) {
        tokenMap = Nan::New<Object>();
        NodeRT::Utils::SetHiddenValueWithObject(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked(), tokenMap);
      } else {
        tokenMap = Nan::To<Object>(tokenMapVal).ToLocalChecked();
      }

      Nan::Set(tokenMap, info[0], CreateOpaqueWrapper(::Windows::Foundation::PropertyValue::CreateInt64(registrationToken.Value)));
    }

    static void RemoveListener(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (info.Length() < 2 || !info[0]->IsString() || !info[1]->IsFunction()) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"wrong arguments, expected a string and a callback")));
        return;
      }

      String::Value eventName(v8::Isolate::GetCurrent(), info[0]);
      auto str = *eventName;

      if ((!NodeRT::Utils::CaseInsenstiveEquals(L"currentItemChanged", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"itemFailed", str)) &&(!NodeRT::Utils::CaseInsenstiveEquals(L"itemOpened", str))) {
        Nan::ThrowError(Nan::Error(String::Concat(v8::Isolate::GetCurrent(), NodeRT::Utils::NewString(L"given event name isn't supported: "), info[0].As<String>())));
        return;
      }

      Local<Function> callback = info[1].As<Function>();
      Local<Value> tokenMap = NodeRT::Utils::GetHiddenValue(callback, Nan::New<String>(REGISTRATION_TOKEN_MAP_PROPERTY_NAME).ToLocalChecked());

      if (tokenMap.IsEmpty() || Nan::Equals(tokenMap, Undefined()).FromMaybe(false)) {
        return;
      }

      Local<Value> opaqueWrapperObj =  Nan::Get(Nan::To<Object>(tokenMap).ToLocalChecked(), info[0]).ToLocalChecked();

      if (opaqueWrapperObj.IsEmpty() || Nan::Equals(opaqueWrapperObj,Undefined()).FromMaybe(false)) {
        return;
      }

      OpaqueWrapper *opaqueWrapper = OpaqueWrapper::Unwrap<OpaqueWrapper>(opaqueWrapperObj.As<Object>());

      long long tokenValue = (long long) opaqueWrapper->GetObjectInstance();
      ::Windows::Foundation::EventRegistrationToken registrationToken;
      registrationToken.Value = tokenValue;

      try  {
        if (NodeRT::Utils::CaseInsenstiveEquals(L"currentItemChanged", str)) {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());
          wrapper->_instance->CurrentItemChanged::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"itemFailed", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());
          wrapper->_instance->ItemFailed::remove(registrationToken);
        }
        else if (NodeRT::Utils::CaseInsenstiveEquals(L"itemOpened", str))
        {
          if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackList^>(info.This()))
          {
            Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"The caller of this method isn't of the expected type or internal WinRt object was disposed")));
            return;
          }
          MediaPlaybackList *wrapper = MediaPlaybackList::Unwrap<MediaPlaybackList>(info.This());
          wrapper->_instance->ItemOpened::remove(registrationToken);
        }
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
      }

      Nan::Delete(Nan::To<Object>(tokenMap).ToLocalChecked(), Nan::To<String>(info[0]).ToLocalChecked());
    }
    private:
      ::Windows::Media::Playback::MediaPlaybackList^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackList(::Windows::Media::Playback::MediaPlaybackList^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackList^ UnwrapMediaPlaybackList(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackList::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackList(::Windows::Media::Playback::MediaPlaybackList^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackList::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackList^ UnwrapMediaPlaybackList(Local<Value> value) {
     return MediaPlaybackList::Unwrap<MediaPlaybackList>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackList(Local<Object> exports) {
    MediaPlaybackList::Init(exports);
  }

  class IMediaEnginePlaybackSource : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("IMediaEnginePlaybackSource").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);


          
            Nan::SetPrototypeMethod(localRef, "setPlaybackSource", SetPlaybackSource);
          



          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("currentItem").ToLocalChecked(), CurrentItemGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("IMediaEnginePlaybackSource").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      IMediaEnginePlaybackSource(::Windows::Media::Playback::IMediaEnginePlaybackSource^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::IMediaEnginePlaybackSource^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::IMediaEnginePlaybackSource^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::IMediaEnginePlaybackSource^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      IMediaEnginePlaybackSource *wrapperInstance = new IMediaEnginePlaybackSource(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::IMediaEnginePlaybackSource^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::IMediaEnginePlaybackSource^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::IMediaEnginePlaybackSource^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapIMediaEnginePlaybackSource(winRtInstance));
    }


    static void SetPlaybackSource(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::IMediaEnginePlaybackSource^>(info.This())) {
        return;
      }

      IMediaEnginePlaybackSource *wrapper = IMediaEnginePlaybackSource::Unwrap<IMediaEnginePlaybackSource>(info.This());

      if (info.Length() == 1
        && NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::IMediaPlaybackSource^>(info[0]))
      {
        try
        {
          ::Windows::Media::Playback::IMediaPlaybackSource^ arg0 = UnwrapIMediaPlaybackSource(info[0]);
          
          wrapper->_instance->SetPlaybackSource(arg0);
          return;
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Bad arguments: no suitable overload found")));
        return;
      }
    }



    static void CurrentItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::IMediaEnginePlaybackSource^>(info.This())) {
        return;
      }

      IMediaEnginePlaybackSource *wrapper = IMediaEnginePlaybackSource::Unwrap<IMediaEnginePlaybackSource>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItem^ result = wrapper->_instance->CurrentItem;
        info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::IMediaEnginePlaybackSource^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapIMediaEnginePlaybackSource(::Windows::Media::Playback::IMediaEnginePlaybackSource^ wintRtInstance);
      friend ::Windows::Media::Playback::IMediaEnginePlaybackSource^ UnwrapIMediaEnginePlaybackSource(Local<Value> value);
  };

  Persistent<FunctionTemplate> IMediaEnginePlaybackSource::s_constructorTemplate;

  v8::Local<v8::Value> WrapIMediaEnginePlaybackSource(::Windows::Media::Playback::IMediaEnginePlaybackSource^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(IMediaEnginePlaybackSource::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::IMediaEnginePlaybackSource^ UnwrapIMediaEnginePlaybackSource(Local<Value> value) {
     return IMediaEnginePlaybackSource::Unwrap<IMediaEnginePlaybackSource>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitIMediaEnginePlaybackSource(Local<Object> exports) {
    IMediaEnginePlaybackSource::Init(exports);
  }

  class MediaPlaybackItemError : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackItemError").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("errorCode").ToLocalChecked(), ErrorCodeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("extendedError").ToLocalChecked(), ExtendedErrorGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackItemError").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackItemError(::Windows::Media::Playback::MediaPlaybackItemError^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackItemError^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemError^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackItemError^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackItemError *wrapperInstance = new MediaPlaybackItemError(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemError^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackItemError^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackItemError^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackItemError(winRtInstance));
    }





    static void ErrorCodeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemError^>(info.This())) {
        return;
      }

      MediaPlaybackItemError *wrapper = MediaPlaybackItemError::Unwrap<MediaPlaybackItemError>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItemErrorCode result = wrapper->_instance->ErrorCode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ExtendedErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemError^>(info.This())) {
        return;
      }

      MediaPlaybackItemError *wrapper = MediaPlaybackItemError::Unwrap<MediaPlaybackItemError>(info.This());

      try  {
        ::Windows::Foundation::HResult result = wrapper->_instance->ExtendedError;
        info.GetReturnValue().Set(Nan::New<Integer>(result.Value));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackItemError^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackItemError(::Windows::Media::Playback::MediaPlaybackItemError^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackItemError^ UnwrapMediaPlaybackItemError(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackItemError::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackItemError(::Windows::Media::Playback::MediaPlaybackItemError^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackItemError::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackItemError^ UnwrapMediaPlaybackItemError(Local<Value> value) {
     return MediaPlaybackItemError::Unwrap<MediaPlaybackItemError>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackItemError(Local<Object> exports) {
    MediaPlaybackItemError::Init(exports);
  }

  class MediaPlaybackItemFailedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackItemFailedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("error").ToLocalChecked(), ErrorGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("item").ToLocalChecked(), ItemGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackItemFailedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackItemFailedEventArgs(::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackItemFailedEventArgs *wrapperInstance = new MediaPlaybackItemFailedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackItemFailedEventArgs(winRtInstance));
    }





    static void ErrorGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackItemFailedEventArgs *wrapper = MediaPlaybackItemFailedEventArgs::Unwrap<MediaPlaybackItemFailedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItemError^ result = wrapper->_instance->Error;
        info.GetReturnValue().Set(WrapMediaPlaybackItemError(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackItemFailedEventArgs *wrapper = MediaPlaybackItemFailedEventArgs::Unwrap<MediaPlaybackItemFailedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItem^ result = wrapper->_instance->Item;
        info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackItemFailedEventArgs(::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ UnwrapMediaPlaybackItemFailedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackItemFailedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackItemFailedEventArgs(::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackItemFailedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackItemFailedEventArgs^ UnwrapMediaPlaybackItemFailedEventArgs(Local<Value> value) {
     return MediaPlaybackItemFailedEventArgs::Unwrap<MediaPlaybackItemFailedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackItemFailedEventArgs(Local<Object> exports) {
    MediaPlaybackItemFailedEventArgs::Init(exports);
  }

  class CurrentMediaPlaybackItemChangedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("CurrentMediaPlaybackItemChangedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("newItem").ToLocalChecked(), NewItemGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("oldItem").ToLocalChecked(), OldItemGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("reason").ToLocalChecked(), ReasonGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("CurrentMediaPlaybackItemChangedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      CurrentMediaPlaybackItemChangedEventArgs(::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      CurrentMediaPlaybackItemChangedEventArgs *wrapperInstance = new CurrentMediaPlaybackItemChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapCurrentMediaPlaybackItemChangedEventArgs(winRtInstance));
    }





    static void NewItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^>(info.This())) {
        return;
      }

      CurrentMediaPlaybackItemChangedEventArgs *wrapper = CurrentMediaPlaybackItemChangedEventArgs::Unwrap<CurrentMediaPlaybackItemChangedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItem^ result = wrapper->_instance->NewItem;
        info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OldItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^>(info.This())) {
        return;
      }

      CurrentMediaPlaybackItemChangedEventArgs *wrapper = CurrentMediaPlaybackItemChangedEventArgs::Unwrap<CurrentMediaPlaybackItemChangedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItem^ result = wrapper->_instance->OldItem;
        info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void ReasonGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^>(info.This())) {
        return;
      }

      CurrentMediaPlaybackItemChangedEventArgs *wrapper = CurrentMediaPlaybackItemChangedEventArgs::Unwrap<CurrentMediaPlaybackItemChangedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItemChangedReason result = wrapper->_instance->Reason;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapCurrentMediaPlaybackItemChangedEventArgs(::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ UnwrapCurrentMediaPlaybackItemChangedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> CurrentMediaPlaybackItemChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapCurrentMediaPlaybackItemChangedEventArgs(::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(CurrentMediaPlaybackItemChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::CurrentMediaPlaybackItemChangedEventArgs^ UnwrapCurrentMediaPlaybackItemChangedEventArgs(Local<Value> value) {
     return CurrentMediaPlaybackItemChangedEventArgs::Unwrap<CurrentMediaPlaybackItemChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitCurrentMediaPlaybackItemChangedEventArgs(Local<Object> exports) {
    CurrentMediaPlaybackItemChangedEventArgs::Init(exports);
  }

  class MediaPlaybackItemOpenedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("MediaPlaybackItemOpenedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("item").ToLocalChecked(), ItemGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("MediaPlaybackItemOpenedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      MediaPlaybackItemOpenedEventArgs(::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      MediaPlaybackItemOpenedEventArgs *wrapperInstance = new MediaPlaybackItemOpenedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapMediaPlaybackItemOpenedEventArgs(winRtInstance));
    }





    static void ItemGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^>(info.This())) {
        return;
      }

      MediaPlaybackItemOpenedEventArgs *wrapper = MediaPlaybackItemOpenedEventArgs::Unwrap<MediaPlaybackItemOpenedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::MediaPlaybackItem^ result = wrapper->_instance->Item;
        info.GetReturnValue().Set(WrapMediaPlaybackItem(result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapMediaPlaybackItemOpenedEventArgs(::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ UnwrapMediaPlaybackItemOpenedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> MediaPlaybackItemOpenedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapMediaPlaybackItemOpenedEventArgs(::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(MediaPlaybackItemOpenedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::MediaPlaybackItemOpenedEventArgs^ UnwrapMediaPlaybackItemOpenedEventArgs(Local<Value> value) {
     return MediaPlaybackItemOpenedEventArgs::Unwrap<MediaPlaybackItemOpenedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitMediaPlaybackItemOpenedEventArgs(Local<Object> exports) {
    MediaPlaybackItemOpenedEventArgs::Init(exports);
  }

  class TimedMetadataPresentationModeChangedEventArgs : public WrapperBase {
    public:
      
      static void Init(const Local<Object> exports) {
        HandleScope scope;

        Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(New);
        s_constructorTemplate.Reset(localRef);
        localRef->SetClassName(Nan::New<String>("TimedMetadataPresentationModeChangedEventArgs").ToLocalChecked());
        localRef->InstanceTemplate()->SetInternalFieldCount(1);





          
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("newPresentationMode").ToLocalChecked(), NewPresentationModeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("oldPresentationMode").ToLocalChecked(), OldPresentationModeGetter);
            Nan::SetAccessor(localRef->PrototypeTemplate(), Nan::New<String>("track").ToLocalChecked(), TrackGetter);

        Local<Object> constructor = Nan::To<Object>(Nan::GetFunction(localRef).ToLocalChecked()).ToLocalChecked();
        Nan::SetMethod(constructor, "castFrom", CastFrom);



        Nan::Set(exports, Nan::New<String>("TimedMetadataPresentationModeChangedEventArgs").ToLocalChecked(), constructor);
      }

      virtual ::Platform::Object^ GetObjectInstance() const override {
        return _instance;
      }

    private:

      TimedMetadataPresentationModeChangedEventArgs(::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ instance) {
        _instance = instance;
      }

      
    static void New(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;

      Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(s_constructorTemplate);

      // in case the constructor was called without the new operator
      if (!localRef->HasInstance(info.This())) {
        if (info.Length() > 0) {
          std::unique_ptr<Local<Value> []> constructorArgs(new Local<Value>[info.Length()]);

          Local<Value> *argsPtr = constructorArgs.get();
          for (int i = 0; i < info.Length(); i++) {
            argsPtr[i] = info[i];
          }

          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), constructorArgs.get());
          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        } else {
          MaybeLocal<Object> res = Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(), info.Length(), nullptr);

          if (res.IsEmpty()) {
            return;
          }

          info.GetReturnValue().Set(res.ToLocalChecked());
          return;
        }
      }

      ::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ winRtInstance;


      if (info.Length() == 1 && OpaqueWrapper::IsOpaqueWrapper(info[0]) &&
        NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^>(info[0])) {
        try {
          winRtInstance = (::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
        } catch (Platform::Exception ^exception) {
          NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
          return;
        }
      }
 else {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no suitable constructor found")));
        return;
      }

      NodeRT::Utils::SetHiddenValue(info.This(), Nan::New<String>("__winRtInstance__").ToLocalChecked(), True());

      TimedMetadataPresentationModeChangedEventArgs *wrapperInstance = new TimedMetadataPresentationModeChangedEventArgs(winRtInstance);
      wrapperInstance->Wrap(info.This());

      info.GetReturnValue().Set(info.This());
    }


      
    static void CastFrom(Nan::NAN_METHOD_ARGS_TYPE info) {
      HandleScope scope;
      if (info.Length() < 1 || !NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^>(info[0])) {
        Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"Invalid arguments, no object provided, or given object could not be casted to requested type")));
        return;
      }

      ::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ winRtInstance;
      try {
        winRtInstance = (::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^) NodeRT::Utils::GetObjectInstance(info[0]);
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }

      info.GetReturnValue().Set(WrapTimedMetadataPresentationModeChangedEventArgs(winRtInstance));
    }





    static void NewPresentationModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^>(info.This())) {
        return;
      }

      TimedMetadataPresentationModeChangedEventArgs *wrapper = TimedMetadataPresentationModeChangedEventArgs::Unwrap<TimedMetadataPresentationModeChangedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::TimedMetadataTrackPresentationMode result = wrapper->_instance->NewPresentationMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void OldPresentationModeGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^>(info.This())) {
        return;
      }

      TimedMetadataPresentationModeChangedEventArgs *wrapper = TimedMetadataPresentationModeChangedEventArgs::Unwrap<TimedMetadataPresentationModeChangedEventArgs>(info.This());

      try  {
        ::Windows::Media::Playback::TimedMetadataTrackPresentationMode result = wrapper->_instance->OldPresentationMode;
        info.GetReturnValue().Set(Nan::New<Integer>(static_cast<int>(result)));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      
    static void TrackGetter(Local<String> property, const Nan::PropertyCallbackInfo<v8::Value> &info) {
      HandleScope scope;

      if (!NodeRT::Utils::IsWinRtWrapperOf<::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^>(info.This())) {
        return;
      }

      TimedMetadataPresentationModeChangedEventArgs *wrapper = TimedMetadataPresentationModeChangedEventArgs::Unwrap<TimedMetadataPresentationModeChangedEventArgs>(info.This());

      try  {
        ::Windows::Media::Core::TimedMetadataTrack^ result = wrapper->_instance->Track;
        info.GetReturnValue().Set(NodeRT::Utils::CreateExternalWinRTObject("Windows.Media.Core", "TimedMetadataTrack", result));
        return;
      } catch (Platform::Exception ^exception) {
        NodeRT::Utils::ThrowWinRtExceptionInJs(exception);
        return;
      }
    }
      


    private:
      ::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ _instance;
      static Persistent<FunctionTemplate> s_constructorTemplate;

      friend v8::Local<v8::Value> WrapTimedMetadataPresentationModeChangedEventArgs(::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ wintRtInstance);
      friend ::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ UnwrapTimedMetadataPresentationModeChangedEventArgs(Local<Value> value);
  };

  Persistent<FunctionTemplate> TimedMetadataPresentationModeChangedEventArgs::s_constructorTemplate;

  v8::Local<v8::Value> WrapTimedMetadataPresentationModeChangedEventArgs(::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ winRtInstance) {
    EscapableHandleScope scope;

    if (winRtInstance == nullptr) {
      return scope.Escape(Undefined());
    }

    Local<Value> opaqueWrapper = CreateOpaqueWrapper(winRtInstance);
    Local<Value> args[] = {opaqueWrapper};
    Local<FunctionTemplate> localRef = Nan::New<FunctionTemplate>(TimedMetadataPresentationModeChangedEventArgs::s_constructorTemplate);
    return scope.Escape(Nan::NewInstance(Nan::GetFunction(localRef).ToLocalChecked(),_countof(args), args).ToLocalChecked());
  }

  ::Windows::Media::Playback::TimedMetadataPresentationModeChangedEventArgs^ UnwrapTimedMetadataPresentationModeChangedEventArgs(Local<Value> value) {
     return TimedMetadataPresentationModeChangedEventArgs::Unwrap<TimedMetadataPresentationModeChangedEventArgs>(Nan::To<Object>(value).ToLocalChecked())->_instance;
  }

  void InitTimedMetadataPresentationModeChangedEventArgs(Local<Object> exports) {
    TimedMetadataPresentationModeChangedEventArgs::Init(exports);
  }


} } } } 

NAN_MODULE_INIT(init) {
  // We ignore failures for now since it probably means that
  // the initialization already happened for STA, and that's cool

  CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  /*
  if (FAILED(CoInitializeEx(nullptr, COINIT_MULTITHREADED))) {
    Nan::ThrowError(Nan::Error(NodeRT::Utils::NewString(L"error in CoInitializeEx()")));
    return;
  }
  */

      NodeRT::Windows::Media::Playback::InitMediaPlayerStateEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackStateEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaPlayerErrorEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaPlayerAudioCategoryEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaPlayerAudioDeviceTypeEnum(target);
      NodeRT::Windows::Media::Playback::InitStereoscopicVideoRenderModeEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaCommandEnablingRuleEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackSessionVideoConstrictionReasonEnum(target);
      NodeRT::Windows::Media::Playback::InitSphericalVideoProjectionModeEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackItemErrorCodeEnum(target);
      NodeRT::Windows::Media::Playback::InitFailedMediaStreamKindEnum(target);
      NodeRT::Windows::Media::Playback::InitTimedMetadataTrackPresentationModeEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaBreakInsertionMethodEnum(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackItemChangedReasonEnum(target);
      NodeRT::Windows::Media::Playback::InitAutoLoadedDisplayPropertyKindEnum(target);
      NodeRT::Windows::Media::Playback::InitPlaybackMediaMarker(target);
      NodeRT::Windows::Media::Playback::InitPlaybackMediaMarkerSequence(target);
      NodeRT::Windows::Media::Playback::InitMediaPlayerFailedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlayerRateChangedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitPlaybackMediaMarkerReachedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlayerDataReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlayer(target);
      NodeRT::Windows::Media::Playback::InitMediaBreakManager(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManager(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackSession(target);
      NodeRT::Windows::Media::Playback::InitMediaPlayerSurface(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackSphericalVideoProjection(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackSessionOutputDegradationPolicyState(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackSessionBufferingStartedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaBreakSeekedOverEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaBreakStartedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaBreakEndedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaBreakSkippedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitBackgroundMediaPlayer(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerPlayReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerPauseReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerNextReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerPreviousReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerFastForwardReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerRewindReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerShuffleReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerAutoRepeatModeReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerPositionReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerRateReceivedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackCommandManagerCommandBehavior(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackItem(target);
      NodeRT::Windows::Media::Playback::InitIMediaPlaybackSource(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackAudioTrackList(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackVideoTrackList(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackTimedMetadataTrackList(target);
      NodeRT::Windows::Media::Playback::InitMediaBreakSchedule(target);
      NodeRT::Windows::Media::Playback::InitMediaItemDisplayProperties(target);
      NodeRT::Windows::Media::Playback::InitMediaBreak(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackList(target);
      NodeRT::Windows::Media::Playback::InitIMediaEnginePlaybackSource(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackItemError(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackItemFailedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitCurrentMediaPlaybackItemChangedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitMediaPlaybackItemOpenedEventArgs(target);
      NodeRT::Windows::Media::Playback::InitTimedMetadataPresentationModeChangedEventArgs(target);


  NodeRT::Utils::RegisterNameSpace("Windows.Media.Playback", target);
}



NODE_MODULE(binding, init)
