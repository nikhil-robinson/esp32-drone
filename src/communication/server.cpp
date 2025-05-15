#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <aerial_robot/flight_control/underactuated_flight_control.hpp>

const char* ssid     = "Your_SSID";
const char* password = "Your_PASSWORD";

AsyncWebServer server(80);

void setup_server() {

    const char* ssid     = "PID_Config_AP";
    const char* password = "12345678";
    WiFi.softAP(ssid, password);
    USBSerial.print("AP IP address: ");
    USBSerial.println(WiFi.softAPIP());

    if (!SPIFFS.begin(true)) {
        USBSerial.println("SPIFFS Mount Failed");
        return;
    }

    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");

    server.on("/update", HTTP_POST, [](AsyncWebServerRequest* request) {
        for (int i = 0; i < request->params(); i++) {
            String name = request->getParam(i)->name();
            float value = request->getParam(i)->value().toFloat();

            using namespace CONTROL;

            if (name == "XY_P_GAIN")
                XY_P_GAIN = value;
            else if (name == "XY_I_GAIN")
                XY_I_GAIN = value;
            else if (name == "XY_D_GAIN")
                XY_D_GAIN = value;
            else if (name == "XY_OUTPUT_LIMIT")
                XY_OUTPUT_LIMIT = value;
            else if (name == "XY_I_LIMIT")
                XY_I_LIMIT = value;
            else if (name == "XY_ROLL_GAIN")
                XY_ROLL_GAIN = value;
            else if (name == "XY_PITCH_GAIN")
                XY_PITCH_GAIN = value;

            else if (name == "Z_P_GAIN")
                Z_P_GAIN = value;
            else if (name == "Z_I_GAIN")
                Z_I_GAIN = value;
            else if (name == "Z_D_GAIN")
                Z_D_GAIN = value;
            else if (name == "Z_OUTPUT_LIMIT")
                Z_OUTPUT_LIMIT = value;
            else if (name == "Z_I_LIMIT")
                Z_I_LIMIT = value;
            else if (name == "Z_OFFSET")
                Z_OFFSET = value;

            else if (name == "ROLL_P_GAIN")
                ROLL_P_GAIN = value;
            else if (name == "ROLL_I_GAIN")
                ROLL_I_GAIN = value;
            else if (name == "ROLL_D_GAIN")
                ROLL_D_GAIN = value;
            else if (name == "ROLL_OUTPUT_LIMIT")
                ROLL_OUTPUT_LIMIT = value;
            else if (name == "ROLL_I_LIMIT")
                ROLL_I_LIMIT = value;

            else if (name == "PITCH_P_GAIN")
                PITCH_P_GAIN = value;
            else if (name == "PITCH_I_GAIN")
                PITCH_I_GAIN = value;
            else if (name == "PITCH_D_GAIN")
                PITCH_D_GAIN = value;
            else if (name == "PITCH_OUTPUT_LIMIT")
                PITCH_OUTPUT_LIMIT = value;
            else if (name == "PITCH_I_LIMIT")
                PITCH_I_LIMIT = value;

            else if (name == "YAW_P_GAIN")
                YAW_P_GAIN = value;
            else if (name == "YAW_I_GAIN")
                YAW_I_GAIN = value;
            else if (name == "YAW_D_GAIN")
                YAW_D_GAIN = value;
            else if (name == "YAW_OUTPUT_LIMIT")
                YAW_OUTPUT_LIMIT = value;
            else if (name == "YAW_I_LIMIT")
                YAW_I_LIMIT = value;
        }

        request->send(200, "text/plain", "Updated");
    });

    server.on("/reset", HTTP_POST, [](AsyncWebServerRequest* request) { ESP.restart(); });

    server.on("/fly", HTTP_POST, [](AsyncWebServerRequest* request) {
        USBSerial.println("FLY INITIATED");
        request->send(200, "text/plain", "Flying...");
    });

    server.begin();
}