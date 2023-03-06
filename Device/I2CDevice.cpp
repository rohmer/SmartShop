#include "I2CDevice.h"

I2CDevice::I2CDevice(std::string Name, std::string Description, eDeviceType DeviceType, unsigned short I2CAddress, eI2CBus I2CBus, int PollingInterval) 
	: DeviceBase(Name, Description, DeviceType, eDeviceBus::I2C, PollingInterval)
	, i2cAddr(I2CAddress)
	, i2cBus(I2CBus)
{
	openBus(i2cBus, i2cAddr);
}

I2CDevice::I2CDevice(std::string Name, std::string Description, eDeviceType DeviceType, DeviceConfig config, unsigned short I2CAddress, eI2CBus I2CBus, int PollingInterval) 
	: DeviceBase(Name, Description, config, DeviceType, eDeviceBus::I2C, PollingInterval)
	, i2cAddr(I2CAddress)
	, i2cBus(I2CBus)
{	
	openBus(i2cBus, i2cAddr);
}

I2CDevice::~I2CDevice()
{
	if (i2cHandle >= 0 && busOpen)
		i2cClose(i2cHandle);
}

void I2CDevice::openBus(eI2CBus bus, unsigned short address)
{
	int v = i2cOpen(i2cBus, i2cAddr, 0);
	if (v >= 0)
	{
		busOpen = true;
		i2cHandle = v;
		return;
	}
	std::string errMsg;
	if (v == PI_BAD_I2C_BUS)
	{
		errMsg = "BAD I2C BUS";
	}
	if (v == PI_BAD_I2C_ADDR)
	{
		errMsg = "BAD I2C ADDR";
	}
	if (v == PI_BAD_FLAGS)
	{
		errMsg = "BAD I2C FLAGS";
	}
	if (v == PI_NO_HANDLE)
	{
		errMsg = "NO HANDLE";
	}
	if (v == PI_I2C_OPEN_FAILED)
	{
		errMsg = "I2C OPEN FAILED";
	}
	
	std::stringstream ss;
	ss << "Error opening I2C Bus: " << i2cBus << ", Address: " << i2cAddr << ".  Error==" << errMsg;
	log->LogC(ss.str());
	busOpen = false;
}

void I2CDevice::logError(int errNo, std::string error)
{
	std::stringstream ss;
	ss << error << " ";
	switch (errNo)
	{
	case PI_BAD_HANDLE:
		ss << "Bad file handle for I2C";
		break;
	case PI_BAD_PARAM:
		ss << "Invalid parameter";
		break;
		case PI_I2C_WRITE_FAILED:
		ss << "I2C Write failed";
		break;
	case PI_I2C_READ_FAILED:
		ss << "I2C Read failed";
		break;
		
		
	default:
		ss << "Unknown I2C error";
		break;
	}
	log->LogC(ss.str());
}

bool I2CDevice::WriteByte(unsigned value)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return false;
		}
	}
	
	int v = i2cWriteByte(i2cHandle, value);
	if (v >= 0)
		return true;
	logError(v, "Error writing byte");
}

int I2CDevice::ReadByte()
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return false;
		}
	}
	
	int v = i2cReadByte(i2cHandle);
	if (v < 0)
		logError(v,"Error reading byte");
	
	return v;
}

bool I2CDevice::WriteByteData(unsigned i2cReg, unsigned value)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return false;
		}
	}
	int v = i2cWriteByteData(i2cHandle, i2cReg, value);
	if (v < 0)
	{
		logError(v, "Error writing byte to register");
		return false;
	}
	return true;
}

int I2CDevice::ReadByteData(unsigned i2cReg)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return false;
		}
	}
	int v = i2cReadByteData(i2cHandle, i2cReg);
	if (v >= 0)
		return v;
	logError(v, "Error reading byte from register");
	return false;
}

bool I2CDevice::WriteWordData(unsigned i2cReg, unsigned value)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return false;
		}
	}
	int v = i2cWriteWordData(i2cHandle, i2cReg, value);
	if (v < 0)
	{
		logError(v, "Error writing word to register");
		return false;
	}
	return true;
}

int I2CDevice::ReadWordData(unsigned i2cReg)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return false;
		}
	}
	int v = i2cReadWordData(i2cHandle, i2cReg);
	if (v >= 0)
		return v;
	logError(v, "Error reading byte from register");
	return false;
}

bool I2CDevice::WriteBlockData(unsigned i2cReg, std::string value)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return false;
		}
	}
	int v = i2cWriteBlockData(i2cHandle, i2cReg, (char *)value.c_str(), sizeof(value.c_str()));
	if (v < 0)
	{
		logError(v, "Error writing block to register");
		return false;
	}
	return true;
}

std::string I2CDevice::ReadBlockData(unsigned i2cReg)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return "";
		}
	}
	
	std::stringstream ss;
	char *buf = new char(32);
	
	int v = i2cReadBlockData(i2cHandle, i2cReg, buf);
	ss << buf;
	delete(buf);
	
	if (v < 0)
	{
		logError(v,"Error reading block data");
		return "";
	}
	return ss.str();
}

std::string I2CDevice::ReadDevice(unsigned count)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return "";
		}
	}
	char* buf = new char(count);
	int v = i2cReadDevice(i2cHandle, buf, count);
	std::stringstream ss;
	ss << buf;
	delete(buf);
	if (v < 0)
	{
		log->LogC("Failed ReadDevice call");
	}
	return ss.str();
}

int I2CDevice::WriteDevice(std::string data)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return -1;
		}
	}
	int v = i2cWriteDevice(i2cHandle, (char*)data.c_str(), sizeof(data.c_str()));
	if (v < 0)
	{
		log->LogC("Failed to WriteDevice");
	}
	return v;
}

std::string I2CDevice::ReadI2CBlockData(unsigned i2cReg, unsigned short count)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return "";
		}
	}

	char* buf = new char(count);
	int v = i2cReadI2CBlockData(i2cHandle, i2cReg, buf, count);
	if (v < 0)
	{
		delete(buf);
		log->LogC("Failed i2cReadI2CBlockData");
		return "";
	}
	std::stringstream ss;
	ss << buf;
	delete (buf);
	return ss.str();
}

bool I2CDevice::WriteI2CBlockData(unsigned i2cReg, std::string data)
{
	if (!busOpen)
	{
		openBus(i2cBus, i2cAddr);
		if (!busOpen)
		{
			log->LogC("Cannot open bus");
			return "";
		}
	}

	int v = i2cWriteI2CBlockData(i2cHandle, i2cReg, (char*)data.c_str(), sizeof(data.c_str()));
	if (v < 0)
	{
		log->LogC("Failed WriteI2CBlockData");
		return false;
	}
	return true;
}

std::vector<uint8_t> I2CDevice::ReadBytes(uint8_t size)
{
	std::vector<uint8_t> ret;
	
	for (int i = 0; i < size; i ++)
	{
		int v = ReadByte();
		if (v < 0)
			return ret;
		ret.push_back(v);
	}
	
	return ret;
}