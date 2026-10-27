const express = require('express');
const mysql = require('mysql2');

const app = express();
const PORT = 3000;
const API_KEY_SECRETA = process.env.API_KEY; // Debe coincidir con la de tu NodeMCU

// Las credenciales vienen del archivo .env (ver .env.example); no se guardan en el codigo.
if (!process.env.API_KEY || !process.env.DB_USER) {
    console.error('Faltan variables de entorno (API_KEY, DB_USER, DB_PASSWORD). Copia .env.example a .env y llenalo.');
    process.exit(1);
}

// Middleware para procesar datos de formularios (Content-Type: application/x-www-form-urlencoded)
app.use(express.urlencoded({ extended: true }));
app.use(express.json()); // Por si en el futuro decides enviar JSON

// Configuración de la conexión a MySQL
// RECORDAR ejecutar en la terminal el comando: npm run dev
// ... lo anterior es para iniciar la conexión con la base de datos MySQL y que el servidor esté escuchando en el puerto 3000
// ... recuerda que el API corre como un proceso independiente, por lo que si cierras la terminal, el API dejará de funcionar.
const conexion = mysql.createConnection({
    host: process.env.DB_HOST || 'localhost',
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD ?? '',
    database: process.env.DB_NAME || 'iot_data'
});

// Conectar a la base de datos
conexion.connect((err) => {
    if (err) {
        console.error('Error conectando a MySQL:', err.stack);
        return;
    }
    console.log('Conectado exitosamente a la base de datos MySQL.');
});

app.use((err, req, res, next) => {
    if (err instanceof SyntaxError && err.status === 400 && 'body' in err) {
        console.error('Petición rechazada: El formato enviado no es un JSON válido.');
        return res.status(400).send('Error: El formato de los datos enviados es inválido.');
    }
    next();
});

// Ruta POST para recibir los datos del NodeMCU
app.post('/api/sensor', (req, res) => {
    const { api_key, sensor_value } = req.body;

    // 1. Validar que los datos existan
    if (!api_key || !sensor_value) {
        return res.status(400).send("Error: Faltan parámetros en la petición.");
    }

    // 2. Validar la API Key por seguridad
    if (api_key !== API_KEY_SECRETA) {
        return res.status(401).send("Error: API Key no autorizada.");
    }

    // 3. Insertar de forma segura usando consultas preparadas (Previene SQL Injection)
    const query = 'INSERT INTO SensorData (reading) VALUES (?)';
    conexion.query(query, [sensor_value], (error, results) => {
        if (error) {
            console.error('Error al insertar datos:', error);
            return res.status(500).send("Error interno del servidor al guardar en BD.");
        }
        console.log(`Dato guardado con éxito. ID asignado: ${results.insertId}`);
        res.status(200).send("Success");
    });
});

app.get('/api/datetime', (req, res) => {
    // Validación por encabezado por seguridad
    const api_key = req.headers['x-api-key'];
    if (!api_key || api_key !== API_KEY_SECRETA) {
        return res.status(401).json({ error: "No autorizado." });
    }

    // Calcular tiempo actual del servidor
    const ahora = new Date();
    const fecha = ahora.getFullYear() + '-' +
        String(ahora.getMonth() + 1).padStart(2, '0') + '-' +
        String(ahora.getDate()).padStart(2, '0');
        
    const hora = String(ahora.getHours()).padStart(2, '0') + ':' +
        String(ahora.getMinutes()).padStart(2, '0') + ':' +
        String(ahora.getSeconds()).padStart(2, '0');

    // Retorna estrictamente la respuesta de tiempo solicitada
    res.status(200).json({
        date: fecha,
        dayNumber: ahora.getDay(), // Returns 0 for Sunday, 1 for Monday,
        time: hora,
        timestamp: `${fecha} ${hora}`
    });
});
/*
// Ruta GET para extraer todos los datos del sensor
app.get('/api/sensor', (req, res) => {
    // 1. (Opcional) Validar API Key si quieres que tus datos sean privados
    // Para simplificar la URL, la pedimos por los encabezados (Headers) de la petición
    const api_key = req.headers['x-api-key'];

    if (!api_key || api_key !== API_KEY_SECRETA) {
        return res.status(401).send("Error: API Key no provista o no autorizada.");
    }

    // 2. Hacer la consulta SQL para traer los datos (ej. los últimos 50 registros)
    const query = 'SELECT id, reading, reg_date FROM SensorData ORDER BY reg_date DESC LIMIT 50';
    
    conexion.query(query, (error, resultados) => {
        if (error) {
            console.error('Error al extraer datos:', error);
            return res.status(500).send("Error interno al consultar la base de datos.");
        }

        // 3. Responder con los datos en un formato JSON limpio y estructurado
        res.status(200).json({
            status: "Success",
            count: resultados.length,
            data: resultados
        });
    });
});
*/

// Ruta GET con filtros para el NodeMCU
app.get('/api/sensor', (req, res) => {
    // Validación de seguridad por Header
    const api_key = req.headers['x-api-key'];
    if (!api_key || api_key !== API_KEY_SECRETA) {
        return res.status(401).send("Error: API Key no autorizada.");
    }

    // Capturar parámetros de la URL (Ej: /api/sensor?limit=5)
    // Si no envían un límite, por defecto traerá 10 registros
    const cantidad = parseInt(req.query.limit) || 10; 

    // Consulta SQL usando el límite dinámico
    const query = 'SELECT id, reading, reg_date FROM SensorData ORDER BY reg_date DESC LIMIT ?';
    
    conexion.query(query, [cantidad], (error, resultados) => {
        if (error) {
            console.error('Error al extraer datos:', error);
            return res.status(500).send("Error en la base de datos.");
        }

        // Enviamos la respuesta estructurada
        res.status(200).json(resultados);
    });
});

// Iniciar el servidor
app.listen(PORT, () => {
    console.log(`Servidor API corriendo localmente en: http://localhost:${PORT}`);
});
