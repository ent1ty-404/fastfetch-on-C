#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/statvfs.h>

#define ARCH_BLUE "\033[38;5;75m"
#define RESET     "\033[0m"

void CPUF() {
    FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
    if (cpuinfo == NULL) {
        printf(ARCH_BLUE "Ошибка: " RESET "не удалось открыть cpuinfo!\n");
        return;
    }
    
    char buffer[256];
    char cpu_model[128];

    while (fgets(buffer, sizeof(buffer), cpuinfo) != NULL) {
        if (strstr(buffer, "model name")) {
            sscanf(buffer, "model name : %127[^\n]", cpu_model);
            printf(ARCH_BLUE "CPU: " RESET "%s\n", cpu_model); 
            break;
        }
    }
    fclose(cpuinfo);
}

void ram() {
    FILE *raminfo = fopen("/proc/meminfo", "r");
    if (raminfo == NULL){
        printf(ARCH_BLUE "Ошибка: " RESET "не удалось открыть raminfo!\n");
        return;
    }
    
    char buffer[256];
    int ram_kb; 
    double ram_gb;

    while (fgets(buffer, sizeof(buffer), raminfo) != NULL) {
        if (strstr(buffer, "MemTotal")) {
            sscanf(buffer, "MemTotal: %d kB", &ram_kb); 
            ram_gb = (double)ram_kb / (1024.0 * 1024.0);
            printf(ARCH_BLUE "RAM: " RESET "%.2f GB\n", ram_gb); 
            break;
        }
    }
    fclose(raminfo);
}

void distro() {
    FILE *distroinfo = fopen("/etc/os-release", "r");
    if (distroinfo == NULL){
        printf(ARCH_BLUE "Ошибка: " RESET "не удалось открыть distroinfo!\n");
        return;
    } 
    
    char buffer[256];
    char distroname[128];
    
    while (fgets(buffer, sizeof(buffer), distroinfo) != NULL){
        if (strncmp(buffer, "NAME=", 5) == 0) {
            sscanf(buffer, "NAME=\"%127[^\"]\"", distroname);
            printf(ARCH_BLUE "Distro: " RESET "%s\n", distroname);
            break;
        }
    }
    fclose(distroinfo); 
}

void uptime() {
    FILE *uptimeinfo = fopen("/proc/uptime", "r");
    if (uptimeinfo == NULL) {
        printf(ARCH_BLUE "Ошибка: " RESET "не удалось открыть uptimeinfo!\n");
        return;
    }

    double uptime_seconds;
  
    if (fscanf(uptimeinfo, "%lf", &uptime_seconds) != 1) {
        printf(ARCH_BLUE "Ошибка: " RESET "чтения uptime\n");
        fclose(uptimeinfo);
        return;
    }
    fclose(uptimeinfo);

    int total_seconds = (int)uptime_seconds;
    int days = total_seconds / 86400;             
    int hours = (total_seconds % 86400) / 3600;   
    int minutes = (total_seconds % 3600) / 60;   

    if (days > 0) {
        printf(ARCH_BLUE "Uptime: " RESET "%d days, %d hours, %d mins\n", days, hours, minutes);
    } else {
        printf(ARCH_BLUE "Uptime: " RESET "%d hours, %d mins\n", hours, minutes);
    }
}

void GPU() {
    FILE *gpuinfo = popen("nvidia-smi --query-gpu=name --format=csv,noheader", "r");
    if (gpuinfo == NULL) {
        printf(ARCH_BLUE "Ошибка: " RESET "не удалось запустить nvidia-smi!\n");
        return;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), gpuinfo) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        printf(ARCH_BLUE "GPU: " RESET "%s\n", buffer);
    }

    pclose(gpuinfo);
}

void user() {
    char *username = getenv("USER");
    if (username != NULL) {
        printf(ARCH_BLUE "User: " RESET "%s\n", username);
    } else {
        printf(ARCH_BLUE "User: " RESET "unknown\n");
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
        printf(ARCH_BLUE "Shell: " RESET "%s\n", shellname);
    } else {
        printf(ARCH_BLUE "Shell: " RESET "unknown\n");
    }
}

void WM() {
    char *WM = getenv("XDG_CURRENT_DESKTOP");
    if (WM != NULL) {
        char *WMNAME = strrchr(WM, '/');
        if (WMNAME != NULL) {
            WMNAME++; 
        } else {
            WMNAME = WM; 
        }
        printf(ARCH_BLUE "WM/DE: " RESET "%s\n", WMNAME);
    } else {
        printf(ARCH_BLUE "WM/DE: " RESET "unknown\n");
    }
}

void kernel() {
    FILE *kernelversion = fopen("/proc/version", "r");
    if (kernelversion == NULL) {
        printf(ARCH_BLUE "Ошибка: " RESET "не удалось открыть kernelversion!\n");
        return;
    }
    char buffer[256];
    char kernelver[128];

    while (fgets(buffer, sizeof(buffer), kernelversion) != NULL) {
        if (strstr(buffer, "Linux version")) {
            sscanf(buffer, "Linux version %127s", kernelver);
            printf(ARCH_BLUE "Kernel: " RESET "%s\n", kernelver); 
            break;
        }
    }
    fclose(kernelversion);
}

void disk(){
    struct statvfs vfs;
    if (statvfs("/", &vfs) != 0) {
        printf(ARCH_BLUE "Ошибка: " RESET "чтения диска!\n");
        return;
    }
    unsigned long total_bytes = vfs.f_blocks * vfs.f_frsize;
    unsigned long free_bytes = vfs.f_bfree * vfs.f_frsize;
    unsigned long used_bytes = total_bytes - free_bytes;
    double total_gb = (double)total_bytes / (1024.0 * 1024.0 * 1024.0);
    double used_gb = (double)used_bytes / (1024.0 * 1024.0 * 1024.0);
    double percent = ((double)used_bytes / total_bytes) * 100.0;
    
    printf(ARCH_BLUE "Disk(/): " RESET "%.2f GiB / %.2f GiB (%.0f%%)\n", used_gb, total_gb, percent);
}  

void bootdisk(){
    struct statvfs vfs;
    if (statvfs("/boot/efi", &vfs) != 0) {
        printf(ARCH_BLUE "Ошибка: " RESET "чтения диска /boot/efi!\n");
        return;
    }
    unsigned long total_bytes = vfs.f_blocks * vfs.f_frsize;
    unsigned long free_bytes = vfs.f_bfree * vfs.f_frsize;
    unsigned long used_bytes = total_bytes - free_bytes;
    double total_mb = (double)total_bytes / (1024.0 * 1024.0);
    double used_mb = (double)used_bytes / (1024.0 * 1024.0);
    double percent = ((double)used_bytes / total_bytes) * 100.0;
    
    printf(ARCH_BLUE "EFI: " RESET "%.2f MiB / %.2f MiB (%.0f%%)\n", used_mb, total_mb, percent);
}

void monitor(){
    FILE *fp = popen("hyprctl monitors", "r");
    if (fp == NULL) {
        printf(ARCH_BLUE "Ошибка: " RESET "не удалось запустить hyprctl\n");
        return;
    }
    char buffer[512];
    char Monitor[256] = "";
    char mode[128] = "";

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        if (strstr(buffer, "description:")) {
            sscanf(buffer, " description: %255[^\n]", Monitor);
        }
        
        if (strchr(buffer, '@') && strchr(buffer, 'x') && strstr(buffer, " at ")) {
            sscanf(buffer, " %127s", mode); 
        }
    }

    pclose(fp);

    if (Monitor[0] != '\0') {
        printf(ARCH_BLUE "Monitor: " RESET "%s\n", Monitor);
    }
    if (mode[0] != '\0') {
        printf(ARCH_BLUE "Mode: " RESET "%s\n", mode);
    }
}

int main() {
    CPUF();
    ram();
    GPU();
    distro();
    user();
    shell();
    disk();
    bootdisk();
    WM();
    monitor();
    kernel();
    uptime();
    return 0;
}
