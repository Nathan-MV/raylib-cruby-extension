#include <audio_stream_bindings.h>

// AudioStream management functions
// RLAPI AudioStream LoadAudioStream(unsigned int sampleRate, unsigned int sampleSize, unsigned int channels); // Load audio stream (to stream raw audio pcm data)
// static VALUE rb_load_audio_stream(VALUE self, VALUE rb_sample_rate, VALUE rb_sample_size, VALUE rb_channels) {
//   int sample_rate = NUM2INT(rb_sample_rate);
//   int sample_size = NUM2INT(rb_sample_size);
//   int channels = NUM2INT(rb_channels);

//   AudioStream stream = LoadAudioStream(sample_rate, sample_size, channels);

//   return stream;
// }
// RLAPI bool IsAudioStreamValid(AudioStream stream);                    // Checks if an audio stream is ready
// RLAPI void UnloadAudioStream(AudioStream stream);                     // Unload audio stream and free memory
// RLAPI void UpdateAudioStream(AudioStream stream, const void *data, int frameCount); // Update audio stream buffers with data
// RLAPI bool IsAudioStreamProcessed(AudioStream stream);                // Check if any audio stream buffers requires refill
// RLAPI void PlayAudioStream(AudioStream stream);                       // Play audio stream
// RLAPI void PauseAudioStream(AudioStream stream);                      // Pause audio stream
// RLAPI void ResumeAudioStream(AudioStream stream);                     // Resume audio stream
// RLAPI bool IsAudioStreamPlaying(AudioStream stream);                  // Check if audio stream is playing
// RLAPI void StopAudioStream(AudioStream stream);                       // Stop audio stream
// RLAPI void SetAudioStreamVolume(AudioStream stream, float volume);    // Set volume for audio stream (1.0 is max level)
// RLAPI void SetAudioStreamPitch(AudioStream stream, float pitch);      // Set pitch for audio stream (1.0 is base level)
// RLAPI void SetAudioStreamPan(AudioStream stream, float pan);          // Set pan for audio stream (0.5 is centered)
// RLAPI void SetAudioStreamBufferSizeDefault(int size);                 // Default size for new audio streams
// RLAPI void SetAudioStreamCallback(AudioStream stream, AudioCallback callback); // Audio thread callback to request new data

// RLAPI void AttachAudioStreamProcessor(AudioStream stream, AudioCallback processor); // Attach audio stream processor to stream, receives the samples as 'float'
// RLAPI void DetachAudioStreamProcessor(AudioStream stream, AudioCallback processor); // Detach audio stream processor from stream

// RLAPI void AttachAudioMixedProcessor(AudioCallback processor); // Attach audio stream processor to the entire audio pipeline, receives the samples as 'float'
// RLAPI void DetachAudioMixedProcessor(AudioCallback processor); // Detach audio stream processor from the entire audio pipeline
