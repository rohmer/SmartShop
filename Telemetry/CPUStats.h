#pragma once

struct CPUStats
{
public:
	int sys, nice, idle, wait, irq, softIRQ, stolen, total;
	float tempC;
};

