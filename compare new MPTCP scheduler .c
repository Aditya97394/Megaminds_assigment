#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

void runTest(const char *scheduler, const char *serverIP, const char *outputFile) {
    char command[MAX_COMMAND_LENGTH];

    // Load the MPTCP kernel module with the specified scheduler
    snprintf(command, MAX_COMMAND_LENGTH, "modprobe mptcp %s", scheduler);
    system(command);

    // Run your test command (e.g., iperf for measuring network throughput)
    snprintf(command, MAX_COMMAND_LENGTH, "iperf -c %s >> %s", serverIP, outputFile);
    system(command);

    // Unload the MPTCP kernel module
    snprintf(command, MAX_COMMAND_LENGTH, "modprobe -r mptcp");
    system(command);
}

int main() {
    const char *serverIP = "your_server_ip";
    
    // Run tests for different MPTCP schedulers
    runTest("mptcp_rr", serverIP, "results_mptcp_rr.txt");
    runTest("mptcp_wrr", serverIP, "results_mptcp_wrr.txt");
    runTest("your_mptcp_scheduler", serverIP, "results_your_mptcp_scheduler.txt");

    return 0;
}
