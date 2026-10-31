#include <stdio.h>
#include <string.h>

void CPUF() {
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL) {
        printf("Ошибка: не удалось открыть cpuinfo!\n");
        return;
    }
    
    char buffer[256];
    char cpu_model[128];

    while (fgets(buffer, sizeof(buffer), cpuinfo) != NULL) {
        if (strstr(buffer, "model name")) {
            sscanf(buffer, "model name : %127[^\n]", cpu_model);
            printf("CPU: %s\n", cpu_model); 
            break;
        }
    }
    fclose(cpuinfo);
}

void ram() {
    FILE *raminfo = fopen("/proc/meminfo", "r");
    if (raminfo == NULL){
        printf("Ошибка: не удалось открыть raminfo!\n");
        return;
    }
    
    char buffer[256];
    int ram_kb; 
    double ram_gb;

    while (fgets(buffer, sizeof(buffer), raminfo) != NULL) {
        if (strstr(buffer, "MemTotal")) {
            sscanf(buffer, "MemTotal: %d kB", &ram_kb); 
            ram_gb = (double)ram_kb / (1024.0 * 1024.0);
            printf("RAM: %.2f GB\n", ram_gb); 
            break;
        }
    }
    fclose(raminfo);
}
void distro() {
    FILE *distroinfo = fopen("/etc/os-release", "r");
    if (distroinfo == NULL){
        printf("Ошибка: не удалось открыть distroinfo!\n");
        return;
    } 
    
    char buffer[256];
    char distroname[128];
    
    while (fgets(buffer, sizeof(buffer), distroinfo) != NULL){
        if (strncmp(buffer, "NAME=", 5) == 0) {
            sscanf(buffer, "NAME=\"%127[^\"]\"", distroname);
            printf("Distro: %s\n", distroname);
            break;
        }
    }
    fclose(distroinfo); 
}
int main() {
    CPUF();
    ram();
    distro();
    return 0;
}