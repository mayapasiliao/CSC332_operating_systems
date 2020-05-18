/*
    Explanation: The agent distributing items is represented by the random number function. When the number is generated, this is
    analogous to the agent placing two of the items that smoker(number generated) doesn't have. The agent's mutex then gets locked
    and the chosen smoker executes. When the smoker finishes, the agent mutex is unlocked and chooses another smoker. I have chosen
    20 iteration to illustrate what the program does.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t agent_lock, smoker0_lock, smoker1_lock, smoker2_lock;

void* smoker0_smokes(void* arg);
void* smoker1_smokes(void* arg);
void* smoker2_smokes(void* arg);

int main(int argc, char* arvg[]) {
	pthread_mutex_init(&agent_lock, 0);

	pthread_t smoker0_thread, smoker1_thread, smoker2_thread;

    // Create smoker threads
    pthread_create(&smoker0_thread, NULL, smoker0_smokes, NULL);
    pthread_create(&smoker1_thread, NULL, smoker1_smokes, NULL);
    pthread_create(&smoker2_thread, NULL, smoker2_smokes, NULL);

	// Create mutex locks
    pthread_mutex_init(&smoker0_lock, 0);
    pthread_mutex_init(&smoker1_lock, 0);
    pthread_mutex_init(&smoker2_lock, 0);

	// agent distributes items using random numbers
	for(int i = 0; i < 20; i++) {
        int smoker_to_unlock = rand() % 3;
        pthread_mutex_lock(&agent_lock);

        if(smoker_to_unlock == 0) {
            pthread_mutex_unlock(&smoker0_lock);
        }
        else if(smoker_to_unlock == 1) {
            pthread_mutex_unlock(&smoker1_lock);
        }
        else {
            pthread_mutex_unlock(&smoker2_lock);
        }
	}

	for (int i = 0; i < 3; ++i) {
		pthread_join(smoker0_thread, NULL);
        pthread_join(smoker1_thread, NULL);
        pthread_join(smoker2_thread, NULL);
	}

    return 0;
}

// smoker0 always has paper
void* smoker0_smokes(void* arg) {
	while(1) {
		pthread_mutex_lock(&smoker0_lock);
		printf("smoker0 gets matches and tobacco, makes cigarette\n");
		pthread_mutex_unlock(&agent_lock);
	}

	return NULL;
}

// smoker1 always has matches
void* smoker1_smokes(void* arg) {
	while(1) {
		pthread_mutex_lock(&smoker1_lock);
		printf("smoker1 gets paper and tobacco, makes cigarette.\n");
		pthread_mutex_unlock(&agent_lock);
	}

	return NULL;
}


// smoker2 always has tobacco
void* smoker2_smokes(void* arg) {
	while(1) {
		pthread_mutex_lock(&smoker2_lock);
		printf("smoker2 gets matches and paper, makes cigarette.\n");
		pthread_mutex_unlock(&agent_lock);
	}

	return NULL;
}