// File: User_Space_Application.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

#define PROC_FILE "/proc/kernel_monitor"
#define REFRESH_RATE 1  // seconds

struct kernel_stats {
    unsigned long total_ram;
    unsigned long free_ram;
    unsigned long proc_count;
    unsigned long cpu_idle;
    unsigned long cpu_user;
    unsigned long cpu_system;
};

void read_kernel_stats(struct kernel_stats *stats)
{
    FILE *fp = fopen(PROC_FILE, "r");
    if (!fp) {
        perror("Failed to open proc file");
        exit(1);
    }
    
    fscanf(fp, "%lu %lu %lu %lu %lu %lu",
           &stats->total_ram,
           &stats->free_ram,
           &stats->proc_count,
           &stats->cpu_idle,
           &stats->cpu_user,
           &stats->cpu_system);
    
    fclose(fp);
}

void display_stats(struct kernel_stats *stats)
{
    clear();
    
    mvprintw(1, 2, "Kernel Internals Monitor");
    mvprintw(3, 2, "Memory Statistics:");
    mvprintw(4, 4, "Total RAM: %lu MB", stats->total_ram / (1024 * 1024));
    mvprintw(5, 4, "Free RAM:  %lu MB", stats->free_ram / (1024 * 1024));
    mvprintw(6, 4, "Used RAM:  %lu MB", (stats->total_ram - stats->free_ram) / (1024 * 1024));
    
    mvprintw(8, 2, "Process Statistics:");
    mvprintw(9, 4, "Total Processes: %lu", stats->proc_count);
    
    unsigned long total_cpu = stats->cpu_idle + stats->cpu_user + stats->cpu_system;
    if (total_cpu > 0) {
        mvprintw(11, 2, "CPU Usage:");
        mvprintw(12, 4, "User:    %.1f%%", (stats->cpu_user * 100.0) / total_cpu);
        mvprintw(13, 4, "System:  %.1f%%", (stats->cpu_system * 100.0) / total_cpu);
        mvprintw(14, 4, "Idle:    %.1f%%", (stats->cpu_idle * 100.0) / total_cpu);
    }
    
    mvprintw(16, 2, "Press 'q' to quit");
    refresh();
}

int main()
{
    struct kernel_stats stats;
    int ch;
    
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    
    while (1) {
        read_kernel_stats(&stats);
        display_stats(&stats);
        
        ch = getch();
        if (ch == 'q' || ch == 'Q')
            break;
        
        sleep(REFRESH_RATE);
    }
    
    // Clean up ncurses
    endwin();
    return 0;
}