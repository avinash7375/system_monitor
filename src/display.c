#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/display.h"

void display_metrics(const SystemMetrics* metrics) {
    system("clear"); // Clear screen for better visibility
    
    printf("\n=== System Hardware Monitor ===\n");
    printf("CPU Usage: %.1f%%\n", metrics->cpu_usage);
    printf("Memory Usage: %.1f%%\n", metrics->mem_usage);
    printf("Swap Usage: %.1f%%\n", metrics->swap_usage);
    printf("Disk Usage: %.1f%%\n", metrics->disk_usage);
    
    if (metrics->cpu_temp != -1) {
        printf("CPU Temperature: %d°C\n", metrics->cpu_temp);
    }
    
    int hours = metrics->uptime / 3600;
    int minutes = (metrics->uptime % 3600) / 60;
    printf("System Uptime: %dh %dm\n", hours, minutes);
    
    time_t now = time(NULL);
    printf("Last Update: %s", ctime(&now));
    printf("============================\n");
}
