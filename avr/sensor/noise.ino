#include "arduinoFFT.h"

//#define NOISE_OUT_PIN PIN_PA5
#define NOISE_OUT_PIN PIN_A1

#define NOISE_SAMPLING_FREQ 8192 //Hz, must be less than 10000 due to ADC
#define NOISE_SAMPLES 64 //This value MUST ALWAYS be a power of 2
#define NOISE_SAMPLING_PERIOD (round(1000000*(1.0/NOISE_SAMPLING_FREQ)))

#define NOISE_MAX_FREQ_TO_RETURN  8
#define NOISE_DATA_MIN_VOLUME  100.0

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void noise_init() {
  pinMode(NOISE_OUT_PIN,  INPUT);
  gpio_logger_send_message("Noise sensor OK");
}

noise_data_t * noise_read_level() {  
  double * vReal = malloc(sizeof(double) * NOISE_SAMPLES);
  double * vImag = malloc(sizeof(double) * NOISE_SAMPLES);
  memset(vImag, 0, sizeof(double) * NOISE_SAMPLES);

  unsigned long sampling_period_us = NOISE_SAMPLING_PERIOD;
  unsigned long microseconds = micros();

  for(int i=0; i<NOISE_SAMPLES; i++)
  {
      vReal[i] = analogRead(NOISE_OUT_PIN);
      while(micros() - microseconds < sampling_period_us){
        //empty loop
      }
      microseconds += sampling_period_us;
  }

  arduinoFFT FFT = arduinoFFT(vReal, vImag, NOISE_SAMPLES, NOISE_SAMPLING_FREQ); /* Create FFT object */
  FFT.Windowing(FFT_WIN_TYP_TRIANGLE, FFT_FORWARD);
  FFT.Compute(FFT_FORWARD);
  FFT.ComplexToMagnitude();

  free(vImag);
  vImag = NULL;
  
 // PrintVector(vReal, (NOISE_SAMPLES >> 1), SCL_FREQUENCY);

  uint16_t * freqs   = malloc(sizeof(uint16_t) * NOISE_MAX_FREQ_TO_RETURN);
  uint16_t * volumes = malloc(sizeof(uint16_t) * NOISE_MAX_FREQ_TO_RETURN);

  memset(freqs,   0, sizeof(uint16_t) * NOISE_MAX_FREQ_TO_RETURN);
  memset(volumes, 0, sizeof(uint16_t) * NOISE_MAX_FREQ_TO_RETURN);
  
  // find all peaks..
  for (int i = 1; i<(NOISE_SAMPLES >> 1); i++) {
    if (vReal[i] > 0xFFFF) {
      vReal[i] = 0xFFFF;
    }

    if (vReal[i] > NOISE_DATA_MIN_VOLUME) {
      double freq = (double) ((i * 1.0 * NOISE_SAMPLING_FREQ) / NOISE_SAMPLES);
      if (freq > 0xFFFF) {
        freq = 0xFFFF;
      }

      for (int j = 0; j<NOISE_MAX_FREQ_TO_RETURN; j++) {
        if (vReal[i] > volumes[j]) {
          for (int k = NOISE_MAX_FREQ_TO_RETURN - 1; k >= j; k--){
            if (k > 0) {
              freqs[k]   = freqs[k-1];
              volumes[k] = volumes[k-1];
            }
          }

          freqs[j]   = freq;
          volumes[j] = vReal[i];

          break;
        }
      }
    }
  }

  free(vReal);
  vReal = NULL;

  // check empty
  if (volumes[0] == 0) {
     free(volumes);
     free(freqs);
     return NULL;
  }

  for (int i = 0; i<NOISE_MAX_FREQ_TO_RETURN; i++) {
    gpio_logger_send_message("volume[%d] == %d; freq == %d", i, volumes[i], freqs[i]);
  }

  noise_data_t * result = malloc(sizeof(noise_data_t));
  memset(result, 0, sizeof(noise_data_t));

  // count peaks
  if (volumes[1] == 0) {
    result->count = 1;
  } else {
    result->count = NOISE_MAX_FREQ_TO_RETURN;
    
    for (int i = 1; i<NOISE_MAX_FREQ_TO_RETURN; i++) {
      if (volumes[i] < volumes[0] / 5) {
        result->count = i;
        break;
      }
    }
  }

  result->freq   = malloc(sizeof(uint16_t) * result->count);
  result->volume = malloc(sizeof(uint16_t) * result->count);

  memcpy(result->freq,   freqs,   sizeof(uint16_t) * result->count);
  memcpy(result->volume, volumes, sizeof(uint16_t) * result->count);

  free(freqs);
  free(volumes);
  
  return result;
}


void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
  break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / NOISE_SAMPLING_FREQ);
  break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * NOISE_SAMPLING_FREQ) / NOISE_SAMPLES);
  break;
    }
    Serial.print(abscissa, 6);
    if(scaleType==SCL_FREQUENCY)
      Serial.print("Hz");
    Serial.print(" ");
    Serial.println(vData[i], 4);
  }
  Serial.println();
}
