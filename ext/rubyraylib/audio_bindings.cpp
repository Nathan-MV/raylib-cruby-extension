#include <audio_bindings.h>

//------------------------------------------------------------------------------------
// Audio Loading and Playing Functions (Module: audio)
//------------------------------------------------------------------------------------
// typedef void (*AudioCallback)(void *bufferData, unsigned int frames);

// Audio device management functions
// RLAPI void InitAudioDevice(void);                                     // Initialize audio device and context
RB_METHOD(rb_init_audio_device, InitAudioDevice)
// RLAPI void CloseAudioDevice(void);                                    // Close the audio device and context
RB_METHOD(rb_close_audio_device, CloseAudioDevice)
// RLAPI bool IsAudioDeviceReady(void);                                  // Check if audio device has been initialized successfully
RB_METHOD_BOOL(rb_is_audio_device_ready, IsAudioDeviceReady)
// RLAPI void SetMasterVolume(float volume);                             // Set master volume (listener)
RB_METHOD_ARG_FLOAT(rb_set_master_volume, SetMasterVolume, Qnil)
// RLAPI float GetMasterVolume(void);                                    // Get master volume (listener)
RB_METHOD_FLOAT(rb_get_master_volume, GetMasterVolume)

extern "C" void Init_Audio() {
  VALUE rb_mAudio = rb_define_module_under(rb_mRL, "Audio");

  rb_define_module_function(rb_mAudio, "init_device", rb_init_audio_device, 0);
  rb_define_module_function(rb_mAudio, "close_device", rb_close_audio_device, 0);
  rb_define_module_function(rb_mAudio, "device_ready?", rb_is_audio_device_ready, 0);
  rb_define_module_function(rb_mAudio, "master_volume=", rb_set_master_volume, 1);
  rb_define_module_function(rb_mAudio, "master_volume", rb_get_master_volume, 0);
}
