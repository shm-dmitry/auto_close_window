#include <SoftwareSerial.h>

#define DATA_TRANSFER_RX  A5
#define DATA_TRANSFER_TX  A6

#define DATA_TRANSFER_SEND_BYTE(b) { \
  data_transfer_port.write((uint8_t) b); \
  crc += b; \
}
#define DATA_TRANSFER_SEND_WORD(w) { \
  DATA_TRANSFER_SEND_BYTE((w / 0xFF)); \
  DATA_TRANSFER_SEND_BYTE((w % 0xFF)); \
}

SoftwareSerial data_transfer_port(DATA_TRANSFER_RX, DATA_TRANSFER_TX); 

void data_transfer_init() {
  data_transfer_port.begin(38400);
}

void data_transfer_send(int8_t temperature, uint16_t tvoc, const noise_data_t * noise) {
  uint8_t crc = 0;

  // Preambula
  DATA_TRANSFER_SEND_BYTE(0xA0);
  DATA_TRANSFER_SEND_BYTE(0xA1);
  DATA_TRANSFER_SEND_BYTE(0xA2);

  // Data
  DATA_TRANSFER_SEND_BYTE(temperature);
  DATA_TRANSFER_SEND_WORD(tvoc);
  if (noise == NULL || noise->count == 0) {
    DATA_TRANSFER_SEND_BYTE(0);
  } else {
    DATA_TRANSFER_SEND_BYTE(noise->count);
    for (int8_t i = 0; i<noise->count; i++) {
      DATA_TRANSFER_SEND_WORD(noise->freq[i]);
      DATA_TRANSFER_SEND_WORD(noise->volume[i]);
    }
  }

  // CRC
  DATA_TRANSFER_SEND_BYTE(crc);
}
