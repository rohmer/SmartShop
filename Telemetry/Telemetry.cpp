#include "Telemetry.h"

sTelemetryReturn Telemetry::GetTelemetryStats(int maxFilesystems, int maxProcesses)
{
	sTelemetryReturn tele;
	tele.timestamp = std::time(NULL);
	
	sigar_t *sigar;
	if (SIGAR_OK != sigar_open(&sigar))
	{
		Logger::GetInstance()->LogC("Could not open sigar library");
		return tele;
	}
	sigar_mem_t mem;
	
	if (sigar_mem_get(sigar, &mem) != SIGAR_OK)
	{
		Logger::GetInstance()->LogC("Failed to get memory statistics");		
	}
	else
	{		
		tele.memory.free = mem.free;
		tele.memory.freePct = mem.free_percent;
		tele.memory.used = mem.used;
		tele.memory.usedPct = mem.used_percent;
	}
	
	sigar_swap_t swap;
	if (sigar_swap_get(sigar, &swap) != SIGAR_OK)
	{
		Logger::GetInstance()->LogC("Failed to get swap statistics");	
	}
	else
	{
		tele.swap.free = swap.free;
		tele.swap.used = swap.used;
		tele.swap.total = swap.total;
		tele.swap.pagein = swap.page_in;
		tele.swap.pageout = swap.page_out;
	}
	
	sigar_cpu_t cpu;
	if (sigar_cpu_get(sigar, &cpu) != SIGAR_OK)
	{
		Logger::GetInstance()->LogC("Failed to get CPU statistics");
	}
	else
	{
		tele.cpu.idle = cpu.idle;
		tele.cpu.irq = cpu.irq;
		tele.cpu.nice = cpu.nice;
		tele.cpu.softIRQ = cpu.soft_irq;
		tele.cpu.stolen = cpu.stolen;
		tele.cpu.sys = cpu.sys;
		tele.cpu.total = cpu.total;
		tele.cpu.wait = cpu.wait;
	}
	tele.cpu.tempC = CPUInfo::GetTempC();
	
	sigar_proc_list_t ps;
	if (sigar_proc_list_get(sigar, &ps) != SIGAR_OK)
	{
		Logger::GetInstance()->LogW("Failed to get process statistics");
	}
	else
	{
		for (int i = 0; i < ps.number; i++)
		{
			sigar_proc_mem_t proc_mem;
			sigar_proc_time_t proc_time;
			sigar_proc_state_t proc_state;
			ProcessTableStats pt;
			
			pt.pid = ps.data[i];
			if (SIGAR_OK ==  sigar_proc_mem_get(sigar, pt.pid, &proc_mem))
			{
				pt.size = proc_mem.size;
			}
			if (SIGAR_OK == sigar_proc_time_get(sigar, pt.pid, &proc_time))
			{
				pt.sysTime = proc_time.sys;
				pt.userTime = proc_time.user;
				pt.totalTime = proc_time.total;
			}
			if (SIGAR_OK == sigar_proc_state_get(sigar, pt.pid, &proc_state))
			{
				pt.state = proc_state.name;
				pt.threads = proc_state.threads;				
			}
			if (maxProcesses != -1 && i < maxProcesses)
				tele.processes.push_back(pt);
		}
	}

	sigar_file_system_list_t fslist;
	if (sigar_file_system_list_get(sigar, &fslist) != SIGAR_OK)
	{
		Logger::GetInstance()->LogW("Failed to get file systemstatistics");
	}
	for (int i = 0; i < fslist.number; i++)
	{
		FileSystemStats entry;
		sigar_file_system_t fs = fslist.data[i];
		sigar_file_system_usage_t fsusage;
		sigar_disk_usage_t diskusage;
		entry.filesystem = fs.dir_name;
		if (SIGAR_OK == sigar_file_system_usage_get(sigar, fs.dir_name, &fsusage))
		{
			entry.avail = fsusage.avail;			
			entry.files = fsusage.files;
			entry.filesystem = fs.dir_name;
			entry.free = fsusage.free;
			entry.freeFiles = fsusage.free_files;
			entry.total = fsusage.total;
			entry.used = fsusage.used;
			entry.usedPct = fsusage.use_percent;
			if(maxFilesystems!=-1 && i<maxFilesystems)
				tele.fileSystems.push_back(entry);
		}
	}
	
	return tele;
}