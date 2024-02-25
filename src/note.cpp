//   Serial.println("Publish received.");
//   Serial.print("  topic: ");
//   Serial.println(topic);
//   Serial.print("  payload: ");
//   Serial.println(payload);

//   // Check if the topic is the color topic
//   #include <cstring>

//   if (topic != "test/lol/color") {
//     return;
//   }

//   // Check if the payload is a valid hex color code
//   size_t payloadLen = strlen(payload);
//   // Check if the payload is a valid hex color code
//   bool isValidHex = true;
//   for (size_t i = 0; i < payloadLen; i++) {
//     if (!isxdigit(payload[i])) {
//       isValidHex = false;
//       break;
//     }
//   }

//   // Return the color code, if valid or a default color
//   const char * hexColor = "000000";
//   if (isValidHex) {
//     hexColor = payload;
//   }

//   char r[3] = {hexColor[0], hexColor[1], '\0'};
//   char g[3] = {hexColor[2], hexColor[3], '\0'};
//   char b[3] = {hexColor[4], hexColor[5], '\0'};

//   int rgb[3];
//   rgb[0] = strtol(r, NULL, 16);
//   rgb[1] = strtol(g, NULL, 16);
//   rgb[2] = strtol(b, NULL, 16);

//   Serial.print("  r: ");
//   Serial.println(rgb[0]);
//   Serial.print("  g: ");
//   Serial.println(rgb[1]);
//   Serial.print("  b: ");
//   Serial.println(rgb[2]);
//   #ifdef RGB_BUILTIN
//   neopixelWrite(RGB_BUILTIN,rgb[0],rgb[1],rgb[2]);
//   #endif