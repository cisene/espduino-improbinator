/*
   NO LICENSES

   DISCLAIMER: By downloading and executing this sketch you might commit a criminal fellony in some country.

   This code is for EDUCATIONAL USE ONLY.

   No warranties, no support, no batteries included.

   Author: Christopher Isene<christopher.isene@gmail.com>
   Revision: 201610272306

*/
#include <ESP8266WiFi.h>

extern "C" {
#include "user_interface.h"
}

#define LED 39

uint8_t phones[] = {
  0x24, 0xDB, 0xAC, // Huawei
  0x28, 0x3C, 0xE4, // Huawei
  0xF8, 0x3D, 0xFF, // Huawei
  0x90, 0x72, 0x40, // Apple
  0x20, 0xC9, 0xD0, // Apple
  0x02, 0x1A, 0x11, // HTC
  0x5C, 0x0E, 0x8B, // Motorola
  0x50, 0x9F, 0x27, // Huawei
  0x98, 0x0C, 0x82, // Samsung
  0x88, 0x1F, 0xA1, // Apple
  0x0C, 0x96, 0xBF, // Huawei
  0x34, 0xCD, 0xBE, // Huawei
  0xBC, 0x25, 0xE0, // Huawei
  0x32, 0xCD, 0xA7, // Samsung
  0x5C, 0x0A, 0x5B, // Samsung
  0x38, 0xAA, 0x3C, // Samsung
  0x88, 0x53, 0xD4, // Huawei
  0x02, 0x15, 0x99, // Samsung
  0x10, 0x9A, 0xDD, // Apple
  0x80, 0xEA, 0x96, // Apple
  0xC8, 0xD1, 0x5E, // Huawei
  0xCC, 0x3A, 0x61, // Samsung
  0x6C, 0x70, 0x9F, // Apple
  0x84, 0x74, 0x2A, // ZTE
  0x28, 0xCF, 0xDA, // Apple
  0x90, 0x84, 0x0D, // Apple
  0x90, 0x18, 0x7C, // Samsung
  0x4C, 0x54, 0x99, // Huawei
  0x5C, 0x7D, 0x5E, // Huawei
  0x88, 0x30, 0x8A, // Samsung
  0xE8, 0x08, 0x8B, // Huawei
  0xAC, 0xE2, 0x15, // Huawei
  0x40, 0xF3, 0x08, // Samsung
  0xB8, 0x8D, 0x12, // Apple
  0x70, 0x73, 0xCB, // Apple
  0x08, 0x63, 0x61, // Huawei
  0x88, 0x32, 0x9B, // Samsung
  0xD0, 0x22, 0xBE, // Samsung
  0x10, 0xC6, 0x1F, // Huawei
  0xD0, 0x2D, 0xB3, // Huawei
  0x5C, 0x96, 0x9D, // Apple
  0x68, 0xA8, 0x6D, // Apple
  0xAC, 0xE8, 0x7B, // Huawei
  0x40, 0x4D, 0x8E, // Huawei
  0x20, 0x64, 0x32, // Samsung
  0x00, 0x37, 0x6D, // Samsung
  0x7C, 0xD1, 0xC3, // Apple
  0x00, 0x1F, 0xF3, // Apple
  0xE8, 0x99, 0xC4, // HTC
  0x00, 0x24, 0x36, // Apple
  0x4C, 0x8B, 0xEF, // Huawei
  0x54, 0x72, 0x4F, // Apple
  0xF0, 0xD1, 0xA9, // Apple
  0xB0, 0x5B, 0x67, // Huawei
  0xB4, 0xC7, 0x99, // Motorola
  0x70, 0x56, 0x81, // Apple
  0xA4, 0xC3, 0x61, // Apple
  0xB8, 0xC7, 0x5D, // Apple
  0xA0, 0x0B, 0xBA, // Samsung
  0x18, 0x87, 0x96, // HTC
  0x34, 0x6B, 0xD3, // Huawei
  0x40, 0xB3, 0x95, // Apple
  0x5C, 0xF8, 0xA1, // Samsung
  0x50, 0xCC, 0xF8, // Samsung
  0x1C, 0xB0, 0x94, // HTC
  0xC8, 0x51, 0x95, // Huawei
  0x20, 0x02, 0xAF, // Samsung
  0x2C, 0x26, 0xC5, // ZTE
  0x9C, 0xA9, 0xE4, // ZTE
  0x40, 0xCB, 0xA8, // Huawei
  0x7C, 0x61, 0x93, // HTC
  0xD4, 0x20, 0x6D, // HTC
  0x6C, 0x8B, 0x2F, // ZTE
  0x04, 0xF7, 0xE4, // Apple
  0x54, 0xE4, 0x3A, // Apple
  0x90, 0xB9, 0x31, // Apple
  0xE4, 0xCE, 0x8F, // Apple
  0x48, 0x28, 0x2F, // ZTE
  0x30, 0xF7, 0xC5, // Apple
  0x3C, 0x47, 0x11, // Huawei
  0xF0, 0xF6, 0x1C, // Apple
  0xF0, 0x25, 0xB7, // Samsung
  0xA8, 0xA6, 0x68, // ZTE
  0x90, 0x21, 0x55, // HTC
  0xF8, 0xDB, 0x7F, // HTC
  0x34, 0xE0, 0xCF, // ZTE
  0xD4, 0x6E, 0x5C, // Huawei
  0x00, 0x1E, 0x52, // Apple
  0x28, 0x37, 0x37, // Apple
  0xAC, 0xCF, 0x5C, // Apple
  0xB8, 0xE8, 0x56, // Apple
  0x58, 0x1F, 0xAA, // Apple
  0xD8, 0x9E, 0x3F, // Apple
  0xE8, 0x50, 0x8B, // Samsung
  0xE0, 0xF8, 0x47, // Apple
  0x60, 0x33, 0x4B, // Apple
  0x78, 0xD6, 0xF0, // Samsung
  0x84, 0x38, 0x38, // Samsung
  0xCC, 0x7B, 0x35, // ZTE
  0x00, 0x26, 0xBB  // Apple
};

uint8_t accesspoints[] = {
  0xDC, 0x53, 0x7C, // Compal Broadband Networks, Inc.
  0x00, 0x03, 0x52, // Colubris Networks
  0x58, 0x98, 0x35, // Technicolor USA Inc.
  0x00, 0x3A, 0x99, // Cisco
  0x00, 0x01, 0x38, // XAVi Technologies Corp.
  0x84, 0x1B, 0x5E, // Netgear
  0x30, 0x91, 0x8F, // Technicolor USA Inc.
  0x00, 0x16, 0xA6, // Dovado
  0xA4, 0x2B, 0x8C, // Netgear
  0xC0, 0x7B, 0xBC, // Cisco
  0xB8, 0x62, 0x1F, // Cisco
  0xA0, 0x21, 0xB7, // Netgear
  0x6C, 0xB0, 0xCE, // Netgear
  0x08, 0x76, 0xFF, // Thomson
  0x2C, 0xB0, 0x5D, // Netgear
  0xA4, 0xB1, 0xE9, // Technicolor USA Inc.
  0x28, 0xC6, 0x8E, // Netgear
  0x10, 0x0D, 0x7F, // Netgear
  0x44, 0x94, 0xFC, // Netgear
  0xC4, 0x01, 0x7C, // Ruckus Wireless
  0x30, 0x46, 0x9A, // Netgear
  0x9C, 0x97, 0x26, // Technicolor USA Inc.
  0x00, 0x24, 0x6C, // Aruba Networks
  0x2C, 0xE6, 0xCC, // Ruckus Wireless
  0x04, 0xA1, 0x51, // Netgear
  0x00, 0x8E, 0xF2, // Netgear
  0x00, 0x1B, 0x2F, // Netgear
  0x58, 0xF3, 0x9C, // Cisco
  0x00, 0x1C, 0xF0, // D-Link
  0x1C, 0xAA, 0x07, // Cisco
  0x20, 0x4E, 0x7F, // Netgear
  0xC4, 0x04, 0x15, // Netgear
  0xC8, 0x6C, 0x87, // Zyxel
  0xC4, 0xEA, 0x1D, // Technicolor USA Inc.
  0x74, 0x44, 0x01, // Netgear
  0x00, 0x25, 0x45, // Cisco
  0x00, 0x1E, 0x2A, // Netgear
  0x00, 0x1F, 0x9F, // Thomson
  0xC0, 0x3F, 0x0E, // Netgear
  0xD8, 0xC7, 0xC8, // Aruba Networks
  0x40, 0x4A, 0x03, // Zyxel
  0x00, 0x26, 0x44, // Thomson
  0xE0, 0x69, 0x95, // Pegatron
  0x00, 0x1D, 0xA1, // Cisco
  0xC6, 0xEA, 0x1D, // Technicolor USA Inc.
  0x0C, 0xD9, 0x96, // Cisco
  0x00, 0x22, 0x07, // Inteno
  0x5C, 0x35, 0x3B, // Compal Broadband Networks, Inc.
  0x34, 0xA8, 0x4E, // Cisco
  0xD0, 0x57, 0x4C, // Cisco
  0x2C, 0x5D, 0x93, // Ruckus Wireless
  0x84, 0x78, 0xAC, // Cisco
  0x4C, 0x60, 0xDE, // Netgear
  0xA4, 0x0C, 0xC3, // Cisco
  0x6C, 0xF3, 0x7F, // Aruba Networks
  0x9C, 0xD3, 0x6D, // Netgear
  0xC4, 0x3D, 0xC7, // Netgear
  0x1C, 0x6A, 0x7A, // Cisco
  0xF4, 0xCF, 0xE2, // Cisco
  0xE0, 0x91, 0xF5, // Netgear
  0x78, 0xBA, 0xF9, // Cisco
  0x08, 0x60, 0x6E, // ASUSTek Computer Inc.
  0x00, 0x24, 0x01, // D-Link
  0xA4, 0x56, 0x30, // Cisco
  0xC8, 0xD3, 0xA3, // D-Link
  0xA0, 0x63, 0x91, // Netgear
  0x70, 0x71, 0xBC, // Pegatron
  0x80, 0x37, 0x73, // Netgear
  0xC8, 0xBE, 0x19, // D-Link
  0x54, 0x67, 0x51, // Compal Broadband Networks, Inc.
  0x64, 0xA0, 0xE7, // Cisco
  0x20, 0x0C, 0xC8, // Netgear
  0xF4, 0x4E, 0x05, // Cisco
  0xB0, 0xB2, 0xDC, // Zyxel
  0x0C, 0x85, 0x25, // Cisco
  0x5C, 0x50, 0x15, // Cisco
  0xD8, 0x50, 0xE6, // ASUSTek Computer Inc.
  0x00, 0x3A, 0x98, // Cisco
  0x24, 0x01, 0xC7, // Cisco
  0xC0, 0x25, 0x5C, // Cisco
  0x0A, 0x18, 0xD6, // Ubiquiti Networks
  0x00, 0x18, 0x4D, // Netgear
  0x00, 0x26, 0x5A, // D-Link
  0x00, 0x1A, 0x1E, // Aruba Networks
  0x00, 0x1F, 0x33, // Netgear
  0x00, 0x19, 0x5B, // D-Link
  0x00, 0x22, 0x3F, // Netgear
  0x00, 0x24, 0x8C, // ASUSTek Computer Inc.
  0x00, 0x22, 0x56, // Cisco
  0x00, 0x13, 0x46, // D-Link
  0xE0, 0x3F, 0x49, // ASUSTek Computer Inc.
  0x24, 0xDE, 0xC6, // Aruba Networks
  0x00, 0x11, 0x95, // D-Link
  0x70, 0x10, 0x5C, // Cisco
  0xBC, 0xEE, 0x7B, // ASUSTek Computer Inc.
  0xA4, 0x18, 0x75, // Cisco
  0x20, 0xE5, 0x2A, // Netgear
  0x1C, 0xE6, 0xC7, // Cisco
  0x06, 0x27, 0x22, // Ubiquiti Networks
  0x00, 0x19, 0xCB, // Zyxel
};

char* ssids[] = {
  "ASUS",
  "All Station Guests",
  "BUTIKEXTVIDEO",
  "DOVADO",
  "GIGABYTE",
  "Glocalnet Wireless",
  "Guest",
  "Guestnet",
  "H&M Free WiFi",
  "ICA - Gratis Wifi",
  "IKEA WiFi",
  "Linksys",
  "Mobile",
  "NETGEAR",
  "Net99",
  "Pressbyran",
  "QuickNetFree",
  "Radisson_Guest",
  "RoverRabbit",
  "SEB Corporate",
  "SEB Guest",
  "SEB Internet",
  "SJ",
  "SJ-Guest",
  "Swedbank Guest",
  "TP-LINK",
  "Telia wifi",
  "Telia wifi1x",
  "Telia-testsignal-bg",
  "VOICE",
  "Vasteras Stad Guest Net",
  "WLAN Zone - The Cloud",
  "WirelessICC",
  "WirelessMobile",
  "arosnet",
  "belkin54g",
  "d-link",
  "default",
  "dlink",
  "edu_internet",
  "eduroam",
  "espressohouse",
  "guest_net",
  "homerun",
  "homerun1x",
  "mobile net",
  "mycloud",
  "scandic_easy",
  "service",
  "skynet",
  "wireless",
  "zyxel"
};

String alfa = "1234567890qwertyuiopasdfghjkklzxcvbnm QWERTYUIOPASDFGHJKLZXCVBNM_";
byte channel;

// Probe Request packet buffer
uint8_t probereq[128] = {
  /* 00 */  0x40,                               /* Management Frame - Probe Request */
  /* 01 */  0x00,                               /* Frame Control Field #2 - always ZERO */
  /* 02 */  0x00, 0x00,                         /* Duration - always ZERO */
  /* 04 */  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* Destination address */
  /* 0a */  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* Source address */
  /* 10 */  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* Broadcast */
  /* 16 */  0x90, 0x00,                         /* Sequence control - no fragment */
  /* 18 */  0x00, 0x0f,
  /* 1a */  0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41, 0x41,
  /* 28 */  0x01, 0x04,
  /* 2a */  0x82,                               /* Basic rate - 1.0Mbit/s */
  /* 2c */  0x84,                               /* Basic rate - 2.0Mbit/s */
  /* 2d */  0x8b,                               /* Basic rate - 5.5Mbit/s */
  /* 2e */  0x96                                /* Basic rate - 11Mbit/s  */
};

/* ======================================================================== */
uint8_t clientBuffer[] = {

  /*
     0x00 - First byte of packet is TTL - Time to live in seconds
     0x01 - 0x2f is Probe Request frame payload
  */

  /* 00 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  /* 01 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  /* 02 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  /* 03 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  /* 04 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  /* 05 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  /* 06 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

  /* 07 */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00


};

uint8_t clientBufferIndex[] = {
  /*
     As many elements as buffer slots

     0x00 - Empty/free slot
     0x01 - Occupied slot

  */
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/* ======================================================================== */




/* ======================================================================== */
void setup() {
  delay(500);
  pinMode(LED, OUTPUT);


  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
}



void loop() {
  // debugPort.println("Loop start");

  digitalWrite(LED, HIGH);   // Turn on the LED

  int i;
  int slotIndex;
  int prf;
  int oui_idx;
  int p;


  /* Find active buffer entries */
  for (i = 0; i <= sizeof(clientBufferIndex) - 1; i = i + 1) {
    if (clientBufferIndex[i] != 0) {
      slotIndex = (i * 0x30);
      if (clientBuffer[slotIndex] <= 1) {
        clientBufferIndex[i] = 0;
      } else {
        clientBuffer[slotIndex] -= 1;
      }
    }
  }

  /* Prepare new faked client into buffer */
  for (i = 0; i <= sizeof(clientBufferIndex) - 1; i = i + 1) {
    if (clientBufferIndex[i] != 0) {
      clientBufferIndex[i] = 0x01;
      slotIndex = (i * 0x30);

      /* Set a random TTL */
      clientBuffer[slotIndex] = random(10, 240);

      /* Copy template into buffer */
      for (prf = 0; prf <= 0x2f; prf = prf + 1) {
        clientBuffer[(slotIndex + 1) + prf] = probereq[prf];
      }

      /* Copy randomized OUI for source address */
      oui_idx = (random(0, sizeof(phones)) * 0x03);
      for (p = 0; p <= 0x03; p = p + 1) {
        clientBuffer[(slotIndex + 0x0b) + p] = phones[oui_idx + p];
      }

      /* Assign three random bytes to complete source address */
      for (p = 0; p <= 0x03; p = p + 1) {
        clientBuffer[(slotIndex + 0x0e) + p] = random(0, 255);
      }

      /* Copy randomized SSID to buffer */

      /* Adjust buffer for SSID length */

      /* Fiddle with speed capabilities */

    }
  }

  /* Randomize channel */
  channel = random(1, 14);
  wifi_set_channel(channel);


  /* TODO: Stitch up frames properly */

  // wifi_send_pkt_freedom(packet, 57, 0);
  // wifi_send_pkt_freedom(packet, 57, 0);
  // wifi_send_pkt_freedom(packet, 57, 0);

  digitalWrite(LED, LOW);

  // debugPort.println("Loop End");
  delay(1);
}
