/*
 * testJson.cpp
 *
 *  Created on: 13 ago. 2021
 *      Author: joaquin
 */


#include "ch.hpp"
#include "hal.h"

#include "chprintf.h"
#include "ArduinoJson.h"

extern "C" {
uint8_t testJSON(BaseSequentialStream *tty);
}


uint8_t testJSON(BaseSequentialStream *tty)
{
    // Allocate the JSON document
      //
      // Inside the brackets, 200 is the capacity of the memory pool in bytes.
      // Don't forget to change this value to match your JSON document.
      // Use https://arduinojson.org/v6/assistant to compute the capacity.
      StaticJsonDocument<300> doc;

      // StaticJsonDocument<N> allocates memory on the stack, it can be
      // replaced by DynamicJsonDocument which allocates in the heap.
      //
      // DynamicJsonDocument doc(200);

      // JSON input string.
      //
      // Using a char[], as shown here, enables the "zero-copy" mode. This mode uses
      // the minimal amount of memory because the JsonDocument stores pointers to
      // the input buffer.
      // If you use another type of input, ArduinoJson must copy the strings from
      // the input to the JsonDocument, so you need to increase the capacity of the
      // JsonDocument.
      char json[] =
          "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";

      // Deserialize the JSON document
      DeserializationError error = deserializeJson(doc, json);

      // Test if parsing succeeds.
      if (error) {
          chprintf(tty,"deserializeJson() failed: ");
//        std::cerr << "deserializeJson() failed: " << error.c_str() << std::endl;
        return 1;
      }

      // Fetch values.
      //
      // Most of the time, you can rely on the implicit casts.
      // In other case, you can do doc["time"].as<long>();
      const char* sensor = doc["sensor"];
      long time = doc["time"];
      double latitude = doc["data"][0];
      double longitude = doc["data"][1];

      // Print values.
      chprintf(tty,"sensor:%s time:%ld lat:%.5f long:%.5f\n",sensor,time,latitude,longitude);
//      std::cout << sensor << std::endl;
//      std::cout << time << std::endl;
//      std::cout << latitude << std::endl;
//      std::cout << longitude << std::endl;

      return 0;

}

