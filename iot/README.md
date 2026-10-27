# Internet of Things (TC1004B — Group 503, Team 3)

Team project. Two pieces: a NodeMCU node that talks MQTT, and a REST API that stores sensor readings.

| Folder | What it is |
| --- | --- |
| [`mqtt_node/`](mqtt_node) | Arduino sketch for an ESP8266 NodeMCU in a small collaborative network of up to 5 nodes. |
| [`rest-api/`](rest-api) | Node.js (Express 5) + MySQL API with API-key authentication. |

---

## mqtt_node — collaborative temperature network

Each node:

1. Reads a potentiometer on `A0` and maps it to a simulated temperature (0–50 °C).
2. Publishes it every 3 s to `TC1004B.503.Eq3/nodo<N>/temp` on the public HiveMQ broker (`broker.hivemq.com:1883`).
3. Subscribes to `TC1004B.503.Eq3/+/temp` to hear every node.
4. Every 5 s averages the latest value from each node it has heard (including its own) and sets an RGB LED: **blue** below 15 °C, **green** from 15 to 30 °C, **red** above 30 °C.

Wiring (from the sketch): LED red → `D1`, green → `D0`, blue → `D2`; potentiometer → `A0`.

Setup:

1. Install the ESP8266 board package (the sketch header notes version 2.5.2) and the `PubSubClient` library.
2. Copy `secrets.h.example` to `secrets.h` and fill in your Wi-Fi name and password. `secrets.h` is git-ignored.
3. At the top of `mqtt_node.ino`, set `MI_ID` (your node, 1–5) and `ANODO_COMUN` (`true` for a common-anode LED).
4. Open `mqtt_node.ino` in the Arduino IDE and upload.

The broker is public and unauthenticated, so anyone who knows the topic prefix can read or publish to it. Don't send anything sensitive.

---

## rest-api

| Method | Path | Auth | What it does |
| --- | --- | --- | --- |
| `POST` | `/api/sensor` | `api_key` in the body | Stores `sensor_value` in `SensorData`. |
| `GET` | `/api/sensor?limit=N` | `x-api-key` header | Returns the last `N` readings, newest first (default 10). |
| `GET` | `/api/datetime` | `x-api-key` header | Returns the server's date and time as JSON. |

Queries are parameterized. The API runs over plain HTTP and the key is a shared secret, which is fine for a local lab network but not production-grade authentication.

Setup (Node 20.6+ and MySQL/MariaDB, for example from XAMPP):

```bash
# 1. Create the database and table (or import schema.sql in phpMyAdmin)
mysql -u root -p < schema.sql

# 2. Create a user for the API
#    CREATE USER 'iotuser'@'localhost' IDENTIFIED BY '<your password>';
#    GRANT SELECT, INSERT ON iot_data.* TO 'iotuser'@'localhost';

# 3. Configure credentials (.env is git-ignored)
cp .env.example .env      # then edit it

# 4. Run
npm install
npm start                 # http://localhost:3000
```

Try it:

```bash
curl -X POST -d "api_key=YOUR_KEY&sensor_value=23.5" http://localhost:3000/api/sensor
curl -H "x-api-key: YOUR_KEY" "http://localhost:3000/api/sensor?limit=5"
curl -H "x-api-key: YOUR_KEY" http://localhost:3000/api/datetime
```

`schema.sql` is a minimal schema that matches the queries in `index.js` (`id`, `reading`, `reg_date`). The device-side sketch that calls this API is not included in this folder.
