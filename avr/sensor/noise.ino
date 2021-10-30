#include "arduinoFFT.h"

//#define NOISE_OUT_PIN PIN_PA5
#define NOISE_OUT_PIN PIN_A1

#define NOISE_SAMPLES 64 //This value MUST ALWAYS be a power of 2
#define NOISE_SAMPLING_PERIOD(freq) (round(1000000*(1.0/freq)))
#define NOISE_INDEX2FREQ(index, sampling_freq) ((double) ((index * 1.0 * sampling_freq) / NOISE_SAMPLES))

#define NOISE_MAX_FREQ_TO_RETURN  8
#define NOISE_DATA_MIN_VOLUME     100.0
#define NOISE_DATA_SKIP_UNUSED_K  10

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void noise_init() {
  pinMode(NOISE_OUT_PIN,  INPUT);
  Serial.println("Noise sensor OK");
}

uint8_t noise_do_read_level(uint16_t sampling_freq, uint16_t out_from_freq, uint16_t * out_major_freq, uint16_t * out_major_volume, uint8_t major_array_size) {
  double * real_part = malloc(sizeof(double) * NOISE_SAMPLES);
  double * imag_part = malloc(sizeof(double) * NOISE_SAMPLES);
  memset(imag_part, 0, sizeof(double) * NOISE_SAMPLES);

  unsigned long sampling_period_us = NOISE_SAMPLING_PERIOD(sampling_freq);
  unsigned long microseconds = micros();

  // get samples
  for(uint8_t i=0; i<NOISE_SAMPLES; i++)
  {
      real_part[i] = analogRead(NOISE_OUT_PIN);
      while(micros() - microseconds < sampling_period_us){
        //empty loop
      }
      microseconds += sampling_period_us;
  }

  // exec FFT
  arduinoFFT FFT = arduinoFFT(real_part, imag_part, NOISE_SAMPLES, sampling_freq);
  FFT.Windowing(FFT_WIN_TYP_TRIANGLE, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  free(imag_part); 
  imag_part = NULL;

  // find all peaks..
  for (int i = 1; i<(NOISE_SAMPLES >> 1); i++) {
    if (real_part[i] > 0xFFFF) {
      real_part[i] = 0xFFFF;
    }

    if (real_part[i] > NOISE_DATA_MIN_VOLUME) {
      double freq = NOISE_INDEX2FREQ(i, sampling_freq);
      if (freq > 0xFFFF) {
        freq = 0xFFFF;
      }

      if (freq < out_from_freq) {
        continue;
      }

      for (int j = 0; j<major_array_size; j++) {
        if (real_part[i] > out_major_volume[j]) {
          for (int k = major_array_size - 1; k >= j; k--){
            if (k > 0) {
              out_major_freq[k]   = out_major_freq[k-1];
              out_major_volume[k] = out_major_volume[k-1];
            }
          }

          out_major_freq[j]   = freq;
          out_major_volume[j] = real_part[i];

          break;
        }
      }
    }
  }

  free(real_part); 
  real_part = NULL;

  // count peaks
  if (out_major_volume[0] == 0) {
    return 0;
  } else if (out_major_volume[1] == 0) {
    return 1;
  } else {
    for (int i = 1; i<major_array_size; i++) {
      if (out_major_volume[i] < out_major_volume[0] / NOISE_DATA_SKIP_UNUSED_K) {
        return i;
      }
    }

    return major_array_size;
  }
}

noise_data_t * noise_read_level() {  
  uint16_t freqs[16];
  uint16_t volumes[16];

  memset(freqs, 0, sizeof(uint16_t) * 16);
  memset(volumes, 0, sizeof(uint16_t) * 16);

  uint8_t total_count = 0;

  // execute multiple times FFT with different sampling rate on different frequencies
  total_count += noise_do_read_level(512,  200, freqs, volumes, 4);
  total_count += noise_do_read_level(1024, 256,  &freqs[total_count], &volumes[total_count], 4);
  total_count += noise_do_read_level(4096, 512, &freqs[total_count], &volumes[total_count], 4);
  total_count += noise_do_read_level(8192, 2048, &freqs[total_count], &volumes[total_count], 4);

  if (total_count == 0) {
    return NULL;
  }

  noise_data_t * result = malloc(sizeof(noise_data_t));
  result->freq   = malloc(sizeof(uint16_t) * total_count);
  result->volume = malloc(sizeof(uint16_t) * total_count);
  result->count  = total_count;


  // Full result array and sort it by volume DESC
  if (total_count == 1) {
    result->freq[0]   = freqs[0];
    result->volume[0] = volumes[0];
    return result;
  }

  for (uint8_t i = 0; i<total_count; i++) {
    // find max and move it to array
    uint16_t max_value = 0;
    uint8_t max_value_position = 0;
    for (uint8_t j = 0; j<total_count; j++) {
      if (volumes[j] > max_value) {
        max_value = volumes[j];
        max_value_position = j;
      }
    }

    if (i > 0 && max_value < result->volume[i] / NOISE_DATA_SKIP_UNUSED_K) {
      result->count = i;
      break;
    }

    result->volume[i] = max_value;
    result->freq[i] = freqs[max_value_position];
    volumes[max_value_position] = 0;
  }
  
  return result;
}
