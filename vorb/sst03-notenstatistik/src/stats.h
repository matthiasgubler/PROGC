//
// Created by cod on 15.09.18.
//

#ifndef SST03_NOTENSTATISTIK_STATS_H
#define SST03_NOTENSTATISTIK_STATS_H
struct MarkCounter {
    unsigned int sechser;
    unsigned int fuenfer;
    unsigned int vierer;
    unsigned int dreier;
    unsigned int zweier;
    unsigned int einer;
};

int findWorstMark(const struct MarkCounter* counter);
int findBestMark(const struct MarkCounter* counter);
int countStudents(const struct MarkCounter* counter);
double calcAverage(const struct MarkCounter* counter);
int readPoints(int *punkte);
int calcMoreThan4(const struct MarkCounter* counter);
int readMinimum(int *minimum);
int calcNote(int punkte, int punkteFuer6);
int calculateStatistics(const int *punkte, int *noten, int minimum6, struct MarkCounter *counter);
#endif //SST03_NOTENSTATISTIK_STATS_H
