#ifndef METRICS_H
#define METRICS_H

// Structure to hold system metrics
typedef struct {
    double cpu_usage;
    double mem_usage;
    double disk_usage;
    double swap_usage;
    long uptime;
    int cpu_temp;
} SystemMetrics;

// Function declarations
double get_cpu_usage(void);
void get_memory_usage(double* mem_usage, double* swap_usage);
double get_disk_usage(const char* path);
int get_cpu_temp(void);
void collect_metrics(SystemMetrics* metrics);

#endif // METRICS_H