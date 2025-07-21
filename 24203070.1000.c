#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define ZONES 10
#define HOURS 24

// Function prototypes
void generateTemperatureData(float data[ZONES][HOURS]);
float calculateDailyAverage(float data[ZONES][HOURS], int zone);
float findPeakTemperature(float data[ZONES][HOURS], int* zone, int* hour);
void findZoneWiseAverages(float data[ZONES][HOURS], float averages[ZONES]);
int detectAnomalies(float data[ZONES][HOURS], float threshold);
void displayZoneTrend(float data[ZONES][HOURS], int zone);

int main() {
    float temperatures[ZONES][HOURS];
    float zoneAverages[ZONES];
    int peakZone, peakHour;
    float peakTemp;
    int anomalyCount;
    int userZone;

    // Seed the random number generator
    srand(time(0));

    // 1. Generate temperature data
    generateTemperatureData(temperatures);

    // 2. Calculate and display zone-wise averages
    findZoneWiseAverages(temperatures, zoneAverages);
    printf("\nZone-wise Average Temperatures:\n");
    for (int i = 0; i < ZONES; i++) {
        printf("Zone %d: %.2f°C\n", i, zoneAverages[i]);
    }

    // 3. Find and display peak temperature
    peakTemp = findPeakTemperature(temperatures, &peakZone, &peakHour);
    printf("\nPeak Temperature: %.2f°C\n", peakTemp);
    printf("Occurred in Zone %d at Hour %d\n", peakZone, peakHour);

    // 4. Detect and display anomalies
    anomalyCount = detectAnomalies(temperatures, 40.0f);
    printf("\nNumber of anomalies (above 40.0°C): %d\n", anomalyCount);

    // 5. Additional challenge: User interaction for zone trend
    printf("\nEnter a zone number (0-9) to view its temperature trend: ");
    scanf("%d", &userZone);

    if (userZone >= 0 && userZone < ZONES) {
        displayZoneTrend(temperatures, userZone);
    } else {
        printf("Invalid zone number!\n");
    }

    return 0;
}

// Function to generate random temperature data between 15.0°C and 45.0°C
void generateTemperatureData(float data[ZONES][HOURS]) {
    for (int i = 0; i < ZONES; i++) {
        for (int j = 0; j < HOURS; j++) {
            // Generate random float between 15.0 and 45.0
            data[i][j] = 15.0 + ((float)rand() / RAND_MAX) * 30.0;
        }
    }
}

// Function to calculate daily average for a specific zone
float calculateDailyAverage(float data[ZONES][HOURS], int zone) {
    float sum = 0.0;
    for (int i = 0; i < HOURS; i++) {
        sum += data[zone][i];
    }
    return sum / HOURS;
}

// Function to find the peak temperature and its location
float findPeakTemperature(float data[ZONES][HOURS], int* zone, int* hour) {
    float peak = data[0][0];
    *zone = 0;
    *hour = 0;

    for (int i = 0; i < ZONES; i++) {
        for (int j = 0; j < HOURS; j++) {
            if (data[i][j] > peak) {
                peak = data[i][j];
                *zone = i;
                *hour = j;
            }
        }
    }
    return peak;
}

// Function to calculate averages for all zones
void findZoneWiseAverages(float data[ZONES][HOURS], float averages[ZONES]) {
    for (int i = 0; i < ZONES; i++) {
        averages[i] = calculateDailyAverage(data, i);
    }
}

// Function to detect temperature anomalies above a threshold
int detectAnomalies(float data[ZONES][HOURS], float threshold) {
    int count = 0;
    for (int i = 0; i < ZONES; i++) {
        for (int j = 0; j < HOURS; j++) {
            if (data[i][j] > threshold) {
                count++;
            }
        }
    }
    return count;
}

// Function to display temperature trend for a specific zone
void displayZoneTrend(float data[ZONES][HOURS], int zone) {
    printf("\nTemperature Trend for Zone %d:\n", zone);
    printf("Hour\tTemperature\n");
    printf("----\t-----------\n");

    for (int i = 0; i < HOURS; i++) {
        printf("%2d\t%6.2f°C\n", i, data[zone][i]);
    }
}

