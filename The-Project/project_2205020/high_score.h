#include<string.h>

int point_collected, hit_got;
double diff_fact = 1.0, score_per_point = 50, loss_per_hit = -40, health_per_hit = -0.1, invincible = 0;

typedef struct player{
    char name[20];
    char score[6];
} player;

void sort_player(player players[], int size = 5){//does selection sort according to scores, biggest first
    for(int i=0; i<size-1; i++){
        int index = i;
        for(int j=i+1; j<size; j++){
            if(strlen(players[index].score) < strlen(players[j].score)) index = j;
            else if(strlen(players[index].score) == strlen(players[j].score) && strcmp(players[j].score, players[index].score) >= 0) index = j;
        }
        player temp;
        temp = players[i], players[i] = players[index], players[index] = temp;
    }
}