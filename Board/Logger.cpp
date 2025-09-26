#include "Logger.h"
#include "AppContext.h"

// Implementación de Logger en .cpp — definiciones no-inline para que el
// enlazador encuentre los símbolos de forma estándar.

bool Logger::begin()
{
	if (!SD.begin(SD_CS_PIN))
	{
		Serial.println("Fallo al inicializar SD");
		Logger::status = SD_ERROR;
		return false;
	}

	if (!SD.exists(logFile))
	{
		File header = SD.open(logFile, FILE_WRITE);
		if (header)
		{
			header.println("timestamp,flow,flow_target,temperature,humidity,pressure,pm1,pm25,pm10,battery_pct");
			header.close();
		}
	}

	Serial.println("SD inicializada");
	Logger::status = SD_OK;
	return true;
}

void Logger::capture(AppContext &context)
{
	if (Logger::status == SD_ERROR)
	{
		Serial.println("Logger: SD en error, intentando re-inicializar...");
		if (!begin()) return;
	}

	File dataFile = SD.open(logFile, FILE_APPEND);
	if (!dataFile)
	{
		Serial.println("Error abriendo archivo en SD para append");
		Logger::status = SD_ERROR;
		return;
	}

	Logger::status = SD_WRITING;

	unsigned long ts = context.nowSeconds();
	dataFile.print(ts);
	dataFile.print(',');

	dataFile.print(context.flowSensor.flow);
	dataFile.print(',');

	dataFile.print(context.flujoObjetivo);
	dataFile.print(',');

	dataFile.print(context.bme.temperature);
	dataFile.print(',');
	dataFile.print(context.bme.humidity);
	dataFile.print(',');
	dataFile.print(context.bme.pressure);
	dataFile.print(',');

	dataFile.print(context.plantower.pm1);
	dataFile.print(',');
	dataFile.print(context.plantower.pm25);
	dataFile.print(',');
	dataFile.print(context.plantower.pm10);
	dataFile.print(',');

	dataFile.print(context.getBatteryPercentage());

	dataFile.println();
	dataFile.close();

	Serial.println("Datos guardados en SD");
	Logger::status = SD_OK;
}
