#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../include/metrics.h"

// Function to read CPU usage from /proc/stat
double get_cpu_usage() {
    static long prev_idle = 0, prev_total = 0;
    long idle, total;
    double cpu_usage;
    
    FILE* file = fopen("/proc/stat", "r");
    if (file == NULL) {
        perror("Error opening /proc/stat");
        return -1;
    }
    
    char buffer[1024];
    fgets(buffer, sizeof(buffer), file);
    fclose(file);
    
    long user, nice, system, idle_time, iowait, irq, softirq, steal;
    sscanf(buffer, "cpu %ld %ld %ld %ld %ld %ld %ld %ld",
           &user, &nice, &system, &idle_time, &iowait, &irq, &softirq, &steal);
    
    idle = idle_time + iowait;
    total = user + nice + system + idle + irq + softirq + steal;
    
    if (prev_total != 0) {
        long diff_idle = idle - prev_idle;
        long diff_total = total - prev_total;
        cpu_usage = (1.0 - (diff_idle / (double)diff_total)) * 100.0;
    } else {
        cpu_usage = 0;
    }
    
    prev_idle = idle;
    prev_total = total;
    return cpu_usage;
}

// Function to get memory usage
void get_memory_usage(double* mem_usage, double* swap_usage) {
    struct sysinfo si;
    if (sysinfo(&si) == -1) {
        perror("Error getting system info");
        return;
    }
    
    *mem_usage = ((si.totalram - si.freeram) / (double)si.totalram) * 100.0;
    *swap_usage = (si.totalswap > 0) ? 
                  ((si.totalswap - si.freeswap) / (double)si.totalswap) * 100.0 : 0;
}

// Function to get disk usage
double get_disk_usage(const char* path) {
    struct statvfs buf;
    if (statvfs(path, &buf) == -1) {
        perror("Error getting disk info");
        return -1;
    }
    
    double total = buf.f_blocks * buf.f_frsize;
    double available = buf.f_bfree * buf.f_frsize;
    return ((total - available) / total) * 100.0;
}

// Function to get CPU temperature
int get_cpu_temp() {
    FILE* file = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (file == NULL) {
        return -1;
    }
    
    int temp;
    fscanf(file, "%d", &temp);
    fclose(file);
    return temp / 1000; // Convert from millidegrees to degrees
}

// Function to collect all metrics
void collect_metrics(SystemMetrics* metrics) {
    metrics->cpu_usage = get_cpu_usage();
    get_memory_usage(&metrics->mem_usage, &metrics->swap_usage);
    metrics->disk_usage = get_disk_usage("/");
    metrics->cpu_temp = get_cpu_temp();
    
    struct sysinfo si;
    if (sysinfo(&si) != -1) {
        metrics->uptime = si.uptime;
    }
}