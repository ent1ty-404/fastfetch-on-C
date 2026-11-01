#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

void uptime() {
    FILE *uptimeinfo = fopen("/proc/uptime", "r");
    if (uptimeinfo == NULL) {
        printf("Ошибка: не удалось открыть uptimeinfo!\n");
        return;
    }

    double uptime_seconds;
  
    if (fscanf(uptimeinfo, "%lf", &uptime_seconds) != 1) {
        printf("Ошибка чтения uptime\n");
        fclose(uptimeinfo);
        return;
    }
    fclose(uptimeinfo);


    int total_seconds = (int)uptime_seconds;
    int days = total_seconds / 86400;             
    int hours = (total_seconds % 86400) / 3600;   
    int minutes = (total_seconds % 3600) / 60;   

    if (days > 0) {
        printf("Uptime: %d days, %d hours, %d mins\n", days, hours, minutes);
    } else {
        printf("Uptime: %d hours, %d mins\n", hours, minutes);
    }

}


void GPU() {
    FILE *gpuinfo = popen("nvidia-smi --query-gpu=name --format=csv,noheader", "r");
    
    if (gpuinfo == NULL) {
        printf("Ошибка: не удалось запустить nvidia-smi!\n");
        return;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), gpuinfo) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        printf("GPU: %s\n", buffer);
    }

    pclose(gpuinfo);
}
void user() {
    char *username = getenv("USER");
    if (username != NULL) {
        printf("User: %s\n", username);
    } else {
        printf("User: unknown\n");
    }
}

void shell() {
    char *shell = getenv("SHELL");
    if (shell != NULL) {
        char *shellname = strrchr(shell, '/');
        if (shellname != NULL) {
            shellname++; 
        } else {
            shellname = shell; 
        }
        printf("Shell: %s\n", shellname);
    } else {
        printf("Shell: unknown\n");
    }
}

int main() {
    CPUF();
    ram();
    GPU();
    distro();
    user();
    shell();
    uptime();
    return 0;
}
