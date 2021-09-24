#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#define ZERO L"솔브"
#define ONE L"바보"

void encode(wchar_t *);
void decode(wchar_t *);

int main (int argc, char *argv[]) {
  setlocale(LC_ALL, "");

  wchar_t **wargv = malloc(argc * sizeof(wchar_t *));
  for (int i = 0; i < argc; i++) {
    wargv[i] = malloc(strlen(argv[i]) * sizeof(wchar_t));
    mbstowcs(wargv[i], argv[i], strlen(argv[i]));
  }

  if (argc < 2)  {
    printf("Usage: <encode/decode> <string>\n");
    return 1;
  }

  if (strcmp(argv[1], "encode") == 0) {
    encode(wargv[2]);
  }

  if (strcmp(argv[1], "decode") == 0) {
    decode(wargv[2]);
  }
}

void encode(wchar_t *message) {
  short octets[30003];
  int length = wcslen(message);
  int l = 0;
  int i = 0;

  while (i < length) {
    uint32_t codePoint = message[i];

    int c = 0;
    int bits = 0;

    if (codePoint <= 0x0000007F) {
      c = 0;
      bits = 0x00;
    } else if (codePoint <= 0x000007FF) {
      c = 6;
      bits = 0xC0;
    } else if (codePoint <= 0x0000FFFF) {
      c = 12;
      bits = 0xE0;
    } else if (codePoint <= 0x001FFFFF) {
      c = 18;
      bits = 0xF0;
    }

    octets[l] = bits | (codePoint >> c);
    l++;

    c -= 6;
    while (c >= 0) {
      octets[l] = 0x80 | ((codePoint >> c) & 0x3F);
      l++;
      c -= 6;
    }
    i += codePoint >= 0x10000 ? 2 : 1;
  }

  char bits[30003 * 8];
  int bitlength = 0;

  for (int ic = 0; ic < l; ic++) {
    for (int ib = 7; ib >= 0; ib--) {
      bits[bitlength] = (octets[ic] >> ib) & 1;
      bitlength++;
    }
  }

  for (int ib = 0; ib < bitlength; ib++) {
    if (bits[ib] == 0) wprintf(ZERO);
    else wprintf(ONE);
  }
}

void decode(wchar_t *message) {
  char bits[30003 * 8];
  int bitlength = 0;

  for (int i = 0; i < wcslen(message); i+=2) {
    wchar_t word[3];
    wcpncpy(word, message + i, 2);

    if (wcscmp(word, ZERO) == 0) {
      bits[bitlength] = 0;
    } else if (wcscmp(word, ONE) == 0) {
      bits[bitlength] = 1;
    } else {
      printf("Invalid character: %lc\n", word[0]);
      return;
    }

    bitlength++;
  }

  short octets[30003] = {0,};
  int l = 0;
  
  for (int ib = 0; ib < bitlength; ib+=8) {
    for (int ic = 0; ic < 8; ic++) {
      octets[l] = octets[l] | (bits[ib + ic] << (7 - ic));
    }
    l++;
  }

  int i = 0;
   while (i < l) {
    short octet = octets[i];
    int bytesNeeded = 0;
    int codePoint = 0;

    if (octet <= 0x7F) {
      bytesNeeded = 0;
      codePoint = octet & 0xFF;
    } else if (octet <= 0xDF) {
      bytesNeeded = 1;
      codePoint = octet & 0x1F;
    } else if (octet <= 0xEF) {
      bytesNeeded = 2;
      codePoint = octet & 0x0F;
    } else if (octet <= 0xF4) {
      bytesNeeded = 3;
      codePoint = octet & 0x07;
    }

    if (l - i - bytesNeeded > 0) {
      int k = 0;
      while (k < bytesNeeded) {
        octet = octets[i + k + 1];
        codePoint = (codePoint << 6) | (octet & 0x3F);
        k += 1;
      }
    } else {
      codePoint = 0xFFFD;
      bytesNeeded = l - i;
    }

    printf("%lc", codePoint);
    i += bytesNeeded + 1;
  }
}
