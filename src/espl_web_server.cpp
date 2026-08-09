#ifndef ESPL_WEB_SERVER_CPP
#define ESPL_WEB_SERVER_CPP
#include "espl_web_server.h"

EsplWebServer::EsplWebServer(EsplConfig &config, EsplNetwork &network, SystemService &systemService) : config(config), network(network), systemService(&systemService)
{
    server = new AsyncWebServer(config.getPort());
    webSocket = new AsyncWebSocket("/ws");
}

EsplWebServer::~EsplWebServer()
{
    this->server->end();
    this->webSocket->closeAll();
    delete server;
    delete webSocket;
}

void EsplWebServer::begin()
{
    setupRoutes();
    setupWebSocket();
    server->begin();
    Serial.println("Web server started on port " + String(config.getPort()));
}

void EsplWebServer::setupRoutes()
{
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
               { request->send(200, "text/html", R"rawliteral(
            <!DOCTYPE html>
            <html lang="en">

            <head>
                <meta charset="UTF-8">
                <meta name="viewport" content="width=device-width, initial-scale=1.0">
                <title>ESPL Smart Home Dashboard</title>
                <style>
                    :root {
                        color-scheme: dark;
                    }

                    body {
                        margin: 0;
                        min-height: 100vh;
                        font-family: "Segoe UI", sans-serif;
                        background: radial-gradient(circle at top, #1f3a83 0%, #0d182e 55%, #07101f 100%);
                        color: #e8eef7;
                    }

                    .mb-24 {
                        margin-bottom: 24px;
                    }

                    .page {
                        max-width: 960px;
                        margin: 0 auto;
                        padding: 24px;
                    }

                    header {
                        display: flex;
                        flex-wrap: wrap;
                        align-items: center;
                        justify-content: space-between;
                        gap: 16px;
                        margin-bottom: 28px;
                    }

                    header h1 {
                        margin: 0;
                        font-size: clamp(1.8rem, 2.4vw, 2.8rem);
                        letter-spacing: 0.02em;
                    }

                    .status {
                        padding: 12px 16px;
                        border-radius: 16px;
                        background: rgba(255, 255, 255, 0.08);
                        border: 1px solid rgba(255, 255, 255, 0.12);
                        font-weight: 600;
                        color: #d5e6ff;
                    }
                    .select-control {
                        padding: 12px 16px;
                        border-radius: 12px;
                        background: rgba(255, 255, 255, 0.08);
                        border: 1px solid rgba(255, 255, 255, 0.12);
                        color: #d5e6ff;
                        font-size: 0.9rem;
                    }
                    .select-control option {
                        background: #0d182e;
                        color: #d5e6ff;
                    }

                    .grid {
                        display: grid;
                        gap: 18px;
                        grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
                    }

                    .card {
                        background: rgba(11, 18, 40, 0.88);
                        border: 1px solid rgba(255, 255, 255, 0.08);
                        border-radius: 24px;
                        padding: 22px;
                        box-shadow: 0 20px 60px rgba(0, 0, 0, 0.18);
                        transition: transform 180ms ease, border-color 180ms ease;
                    }

                    .card:hover {
                        transform: translateY(-2px);
                        border-color: rgba(85, 144, 255, 0.2);
                    }

                    .card-title {
                        margin: 0 0 10px;
                        font-size: 0.95rem;
                        text-transform: uppercase;
                        letter-spacing: 0.16em;
                        color: #92a7d3;
                    }
                    .card-subtitle {
                        text-align: center;
                        margin-top: 6px;
                        font-size: 0.85rem;
                        color: #7a8db0;
                    }

                    .card-value {
                        font-size: clamp(2.2rem, 4vw, 3.4rem);
                        font-weight: 700;
                        line-height: 1;
                    }

                    .relay-switch {
                        position: relative;
                        display: inline-block;
                        width: 60px;
                        height: 34px;
                    }
                    .relay-switch .slider {
                        position: absolute;
                        cursor: pointer;
                        top: 0;
                        left: 0;
                        right: 0;
                        bottom: 0;
                        background-color: #ccc;
                        transition: .4s;
                        border-radius: 34px;
                    }
                    .relay-switch .slider:before {
                        position: absolute;
                        content: "";
                        height: 26px;
                        width: 26px;
                        left: 4px;
                        bottom: 4px;
                        background-color: white;
                        transition: .4s;
                        border-radius: 50%;
                    }
                    .relay-switch input {
                        opacity: 0;
                        width: 0;
                        height: 0;
                    }
                    .relay-switch input:checked + .slider {
                        background-color: #2196F3;
                    }

                    .relay-switch input:checked + .slider:before {
                        transform: translateX(26px);
                    }
                    .relay-switch input:focus + .slider {
                        box-shadow: 0 0 1px #2196F3;
                    }

                    .footer {
                        margin-top: 28px;
                        padding: 16px 20px;
                        border-radius: 18px;
                        background: rgba(255, 255, 255, 0.05);
                        border: 1px solid rgba(255, 255, 255, 0.08);
                        color: #b8c6de;
                    }

                    .footer strong {
                        color: #fff;
                    }

                    @media (max-width: 520px) {
                        .page {
                            padding: 18px;
                        }
                    }
                </style>
            </head>

            <body>
                <div class="page">
                    <header>
                        <div>
                            <h1>ESPL Smart Home Dashboard</h1>
                            <p style="margin: 8px 0 0; color: #b8c6de; max-width: 600px;">Data collected from a network of sensors in your smart home.</p>
                        </div>
                        <div class="status" id="status">Connecting to device...</div>
                        <select id="updateInterval" class="select-control" onchange="changeUpdateInterval(this.value)">
                            <option value="5">Update every 5s</option>
                            <option value="15">Update every 15s</option>
                            <option value="30">Update every 30s</option>
                            <option value="60" selected>Update every 1m</option>
                            <option value="3600">Update every 1h</option>
                        </select>
                    </header>
                    <div class="grid mb-24">
                        <div class="card">
                            <div class="card-title">Time</div>
                            <div class="card-value">
                                <div id="time">--:--:--</div>
                            </div>
                        </div>
                        <div class="card">
                            <div class="card-title">Date</div>
                            <div class="card-value">
                                <div id="date">-- -- ----</div> 
                            </div>
                        </div>
                    </div>
                    <div class="grid mb-24">
                        <div class="card">
                            <div class="card-title">Temperature</div>
                            <div class="card-value" id="temperature">-- °C</div>
                        </div>
                        <div class="card">
                            <div class="card-title">Humidity</div>
                            <div class="card-value" id="humidity">-- %</div>
                        </div>
                        <div class="card">
                            <div class="card-title">Heat index</div>
                            <div class="card-value" id="heatIndex">-- °C</div>
                        </div>
                    </div>
                    <div class="grid">
                        <div class="card">
                            <div class="card-title">Relay 1</div>
                            <label class="relay-switch" for="relay1Checkbox">
                                <input type="checkbox" id="relay1Checkbox">
                                <span class="slider"></span>
                            </label>
                        </div>
                        <div class="card">
                            <div class="card-title">Relay 2</div>
                            <label class="relay-switch" for="relay2Checkbox">
                                <input type="checkbox" id="relay2Checkbox">
                                <span class="slider"></span>
                            </label>
                        </div>
                    </div>
                    <div class="footer" id="footer">Waiting for sensor data...</div>
                </div>
                <script>
                    const statusEl = document.getElementById('status');
                    const footerEl = document.getElementById('footer');
                    const timeEl = document.getElementById('time');
                    const dateEl = document.getElementById('date');
                    const temperatureEl = document.getElementById('temperature');
                    const humidityEl = document.getElementById('humidity');
                    const heatIndexEl = document.getElementById('heatIndex');
                    const relay1Checkbox = document.getElementById('relay1Checkbox');
                    const relay2Checkbox = document.getElementById('relay2Checkbox');

                    let updateTimeInterval = 60; // seconds
                    let updateIntervalId = null;

                    const wsProtocol = location.protocol === 'https:' ? 'wss://' : 'ws://';
                    const socket = new WebSocket(wsProtocol + "192.168.20.108" + '/ws');
                    socket.binaryType = 'arraybuffer';

                    function changeUpdateInterval(value) {
                        updateTimeInterval = parseInt(value);
                        if (socket.readyState === WebSocket.OPEN) {
                            clearInterval(updateIntervalId);
                            updateIntervalId = setInterval(requestSensorData, updateTimeInterval * 1000);
                        }
                    }

                    function sendRelayStatus(relayNumber, status) {
                        if (socket.readyState === WebSocket.OPEN) {
                            const relayStatusArray = new Uint8Array([0x03, relayNumber, status ? 1 : 0]);
                            socket.send(relayStatusArray);
                        }
                    }

                    socket.addEventListener('open', () => {
                        statusEl.textContent = 'Connected - fetching sensor data';
                        statusEl.style.background = 'rgba(17, 91, 198, 0.18)';
                        requestSensorData();
                        updateIntervalId = setInterval(requestSensorData, updateTimeInterval * 1000);
                    });

                    socket.addEventListener('close', () => {
                        statusEl.textContent = 'Disconnected - retrying...';
                        statusEl.style.background = 'rgba(196, 33, 33, 0.14)';
                        footerEl.textContent = 'WebSocket disconnected. Reload the page if connection does not recover.';
                        clearInterval(updateIntervalId);
                    });

                    socket.addEventListener('error', () => {
                        statusEl.textContent = 'WebSocket error';
                        statusEl.style.background = 'rgba(221, 57, 57, 0.16)';
                    });

                    const SensorDataType = {
                        RequestData : 0x01,
                        SensorResData : 0x02,
                        SetRelayStatusResponse : 0x04,
                    };

                    class SensorData {
                        static PAYLOAD_SIZE = 32; // 4 bytes for temperature, 4 for humidity, 4 for heat index, 11 for date, 9 for time
                        constructor(temperature, humidity, heatIndex, date, time, relay1Status, relay2Status) {
                            this.temperature = temperature;
                            this.humidity = humidity;
                            this.heatIndex = heatIndex;
                            this.date = date;
                            this.time = time;
                            this.relay1Status = relay1Status;
                            this.relay2Status = relay2Status;
                        }

                        static fromArrayBuffer(arrayBufferView) {
                            let offset = 5;
                            const temperature = arrayBufferView.getFloat32(offset, true); offset += 4;
                            const humidity = arrayBufferView.getFloat32(offset, true); offset += 4;
                            const heatIndex = arrayBufferView.getFloat32(offset, true); offset += 4;
                            const dateChars = [];
                            for (let i = 0; i < 11; i++) {
                                const charCode = arrayBufferView.getUint8(offset++);
                                if (charCode === 0) continue;
                                dateChars.push(String.fromCharCode(charCode));
                            }
                            const timeChars = [];
                            for (let i = 0; i < 9; i++) {
                                const charCode = arrayBufferView.getUint8(offset++);
                                if (charCode === 0) continue;
                                timeChars.push(String.fromCharCode(charCode));
                            }
                            const timeString = timeChars.join('');
                            const dateString = dateChars.join('');
                            const relay1Status = arrayBufferView.getUint8(offset++);
                            const relay2Status = arrayBufferView.getUint8(offset++);
                            return new SensorData(temperature, humidity, heatIndex, dateString, timeString, relay1Status, relay2Status);
                        }
                        
                    }

                    handleReceivedSensorData = (arrayBufferView) => {
                        const payloadLength = arrayBufferView.getUint32(1, true);
                        if (payloadLength < SensorData.PAYLOAD_SIZE) {
                            console.error('Invalid payload length:', payloadLength);
                            return;
                        }
                        const sensorData = SensorData.fromArrayBuffer(arrayBufferView);
                        updateDashboard(sensorData);
                    };
                    handleReceivedSetRelayStatusResponse = (arrayBufferView) => {
                        const payloadLength = arrayBufferView.getUint32(1, true);
                        if (payloadLength < 2) {
                            console.error('Invalid payload length for relay status response:', payloadLength);
                            return;
                        }
                        const relay1Status = arrayBufferView.getUint8(5);
                        const relay2Status = arrayBufferView.getUint8(6);
                        relay1Checkbox.checked = !!relay1Status;
                        relay2Checkbox.checked = !!relay2Status;
                    };

                    socket.addEventListener('message', event => {
                        if (!(event.data instanceof ArrayBuffer)) {
                            return;
                        }
                        const arrayBufferView = new DataView(event.data);
                        const type = arrayBufferView.getUint8(0);

                        switch (type) {
                            case SensorDataType.SensorResData:
                                handleReceivedSensorData(arrayBufferView);
                                break;
                            case SensorDataType.SetRelayStatusResponse:
                                handleReceivedSetRelayStatusResponse(arrayBufferView);
                                break;
                            default:
                                console.error('Unknown data type received:', type);
                                return;
                        }
                    });

                    function requestSensorData() {
                        if (socket.readyState === WebSocket.OPEN) {
                            socket.send(new Uint8Array([0x01]));
                        }
                    }

                    function formatLocalDate(dateTimeString) {
                        const dateTime = new Date(dateTimeString);
                        return `${dateTime.getFullYear()}-${String(dateTime.getMonth() + 1).padStart(2, '0')}-${String(dateTime.getDate()).padStart(2, '0')} ${String(dateTime.getHours()).padStart(2, '0')}:${String(dateTime.getMinutes()).padStart(2, '0')}:${String(dateTime.getSeconds()).padStart(2, '0')}`;
                    }

                    function updateDashboard(sensorData) {
                        timeEl.textContent = `${sensorData.time}`;
                        dateEl.textContent = `${sensorData.date}`;
                        temperatureEl.textContent = `${sensorData.temperature.toFixed(1)} °C`;
                        humidityEl.textContent = `${sensorData.humidity.toFixed(1)} %`;
                        heatIndexEl.textContent = `${sensorData.heatIndex.toFixed(1)} °C`;
                        relay1Checkbox.checked = !!sensorData.relay1Status;
                        relay2Checkbox.checked = !!sensorData.relay2Status;
                        footerEl.innerHTML = `Last updated: <strong>${new Date().toLocaleTimeString()}</strong>`;
                        statusEl.textContent = 'Connected';
                        statusEl.style.background = 'rgba(17, 91, 198, 0.18)';
                    }

                    function handleRelayChange(event) {
                        const relayNumber = event.target.id === 'relay1Checkbox' ? 1 : 2;
                        const status = event.target.checked;
                        sendRelayStatus(relayNumber, status);
                    }

                    relay1Checkbox.addEventListener('change', handleRelayChange);
                    relay2Checkbox.addEventListener('change', handleRelayChange);
                </script>
            </body>

            </html>
        )rawliteral"); });
}

void EsplWebServer::setupWebSocket()
{
    webSocket->onEvent([this](AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
                       {

        if (type == WS_EVT_CONNECT) {
            Serial.printf("WebSocket client connected: %u\n", client->id());
        } else if (type == WS_EVT_DISCONNECT) {
            Serial.printf("WebSocket client disconnected: %u\n", client->id());
        } else if (type == WS_EVT_DATA) {
            AwsFrameInfo *info = (AwsFrameInfo *)arg;
            if(info->final && info->index == 0 && info->len == len && info->opcode == WS_BINARY){
                uint8_t buffer[256] = {0};
                // extract message type
                uint8_t messageType = data[0];
                // reading next 4 bytes to get the payload length
                // uint32_t payloadLength = (data[1] << 24) | (data[2] << 16) | (data[3] << 8) | data[4];
                switch (messageType) {
                    case MessageType::GET_SENSOR_DATA:{
                        Serial.printf("Received GET_SENSOR_DATA message from client %u\n", client->id());
                        // get current sensor data and date time
                        THData thData = this->systemService->getCurrentTHData();
                        DateTimeData dateTimeData = this->systemService->getCurrentDateTime();

                        WSTHData wsTHData = thData.toWsTHData();
                        WSDateTimeData wsDateTimeData = dateTimeData.toWsDateTimeData();
                        RelayStatusData relayStatusData = this->systemService->getCurrentRelayStatus();
                        WSRelayData wsRelayData = createWSRelayData(relayStatusData.getRelay1Status(), relayStatusData.getRelay2Status());

                        struct WSSensorData sensorData = createWSSensorData(wsTHData, wsDateTimeData, wsRelayData);
                        struct WSMessage responseMessage = createWSMessage(MessageType::SENSOR_DATA_RESPONSE, (uint8_t*)&sensorData, sizeof(WSSensorData));
                       
                        convertWSMessageToBuffer(responseMessage, buffer, sizeof(buffer));
                        client->binary(buffer, calculateWSMessageSize(responseMessage));
                        break;
                    }
                    case MessageType::SET_RELAY_STATUS:{
                        Serial.printf("Received SET_RELAY_STATUS message from client %u\n", client->id());
                        // read relay status from payload
                        uint8_t relayNumber = data[1];
                        bool relayStatus = (bool)data[2];

                        Serial.printf("Setting relay status: Relay%d=%d\n", relayNumber, relayStatus);
                        // set relay status & update system state
                        this->systemService->setRelayStatus(relayNumber, relayStatus);
                        // send response back to client
                        RelayStatusData relayStatusData = this->systemService->getCurrentRelayStatus();
                        WSRelayData wsRelayData = createWSRelayData(relayStatusData.getRelay1Status(), relayStatusData.getRelay2Status());
                        struct WSMessage responseMessage = createWSMessage(MessageType::SET_RELAY_STATUS_RESPONSE, (uint8_t*)&wsRelayData, sizeof(WSRelayData));
                        convertWSMessageToBuffer(responseMessage, buffer, sizeof(buffer));
                        client->binary(buffer, calculateWSMessageSize(responseMessage));
                        break;
                    }
                }

            }
            
        } });
    server->addHandler(webSocket);
}

#endif // ESPL_WEB_SERVER_CPP