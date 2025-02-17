#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/metrics.h"
#include "../include/display.h"

int main() {
    SystemMetrics metrics;
    const int UPDATE_INTERVAL = 2; // Update every 2 seconds
    
    printf("Starting System Monitor...\n");
    printf("Press Ctrl+C to exit\n");
    sleep(1);
    
    while (1) {
        collect_metrics(&metrics);
        display_metrics(&metrics);
        sleep(UPDATE_INTERVAL);
    }
    
    return 0;
}
