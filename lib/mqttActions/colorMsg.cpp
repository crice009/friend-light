#include "colorMsg.h"

#include <string>
void onColorMsg(char* color){
    Serial.println("message is in color category.");

    std::string colorStr(color); // Convert color to std::string

    // Remove '#' if it exists at the start of the string
    if (colorStr[0] == '#') {
      colorStr = colorStr.substr(1);
    }

    // Trim any characters beyond the first 6
    if (colorStr.size() > 6) {
      colorStr = colorStr.substr(0, 6);
    }

    // Check if the color is a valid hex color code
    size_t payloadLen = colorStr.length(); // Use length() instead of strlen()
    // Check if the payload is a valid hex color code
    bool isValidHex = true;
  for (size_t i = 0; i < payloadLen; i++) {
    if (!isxdigit(color[i])) {
      isValidHex = false;
      break;
    }
  }

  // Return the color code, if valid or a default color
  const char * hexColor = "000000";
  if (isValidHex) {
    hexColor = color;
  }

  char r[3] = {hexColor[0], hexColor[1], '\0'};
  char g[3] = {hexColor[2], hexColor[3], '\0'};
  char b[3] = {hexColor[4], hexColor[5], '\0'};

  int rgb[3];
  rgb[0] = strtol(r, NULL, 16);
  rgb[1] = strtol(g, NULL, 16);
  rgb[2] = strtol(b, NULL, 16);

  Serial.print("  r: ");
  Serial.println(rgb[0]);
  Serial.print("  g: ");
  Serial.println(rgb[1]);
  Serial.print("  b: ");
  Serial.println(rgb[2]);
  #ifdef RGB_BUILTIN
  neopixelWrite(RGB_BUILTIN,rgb[0],rgb[1],rgb[2]);
  #endif
}