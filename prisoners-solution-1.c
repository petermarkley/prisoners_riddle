#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PRISONER_NUM 100

// https://www.tiktok.com/@evan_db_dub/video/7186126660859645226

typedef enum {
	BOOL_TRUE = 1,
	BOOL_FALSE = 0
} boolean;

struct prisoner {
	int count;
	int found_on;
	int found_off;
	int times_flipped;
	int visits;
};

struct prisoner prison[PRISONER_NUM];
boolean lightswitch, start;
int count, day, finish;

void flip() {
	if (lightswitch == BOOL_TRUE) {
		lightswitch = BOOL_FALSE;
	} else {
		lightswitch = BOOL_TRUE;
	}
	//fprintf(stdout,"SWITCH FLIPPED\n");
	return;
}

void assert() {
	if (count == PRISONER_NUM) {
		fprintf(stdout,"WIN after %d days\n",day);
	} else {
		fprintf(stdout,"LOSE after %d days -- count was %d\n",day,count);
	}
	finish = BOOL_TRUE;
}

void interrogate(int cell) {
	boolean found = lightswitch;
	//fprintf(stdout,"day %d: called prisoner %d; light was %s for the %dth time (real count %d)\n",day,cell,(lightswitch == BOOL_TRUE ? "ON" : "OFF"),(lightswitch == BOOL_TRUE ? prison[cell].found_on+1 : prison[cell].found_off+1),count);
	
	/*
	===============================
	       PRISONER STRATEGY
	===============================
	*/
	
	if (cell == 0) {
		//Designated Counter
		//==================
		
		if (lightswitch == BOOL_TRUE) {
			
			if (prison[cell].times_flipped > 0) {
				prison[cell].count++;
			}
			
			flip();
			prison[cell].times_flipped++;
			//fprintf(stdout,"flipped: %d; count: %d\n",prison[cell].times_flipped,prison[cell].count);
			
			if (prison[cell].count == (PRISONER_NUM - 1)) {
				assert();
			}
			
		} else if (prison[cell].visits == 0) {
			
			flip();
			prison[cell].times_flipped++;
			//fprintf(stdout,"flipped: %d; count: %d\n",prison[cell].times_flipped,prison[cell].count);
			
		}
		
		//=================
	} else {
		//General Prisoners
		//=================
		
		if (lightswitch == BOOL_FALSE       // CONDITION ONE
		    &&                              //   AND
		    prison[cell].found_on > 0      // CONDITION TWO
		    &&                              //   AND
		    prison[cell].times_flipped < 1) // CONDITION THREE
		    {
			
			flip();
			prison[cell].times_flipped++;
			
		}
		
		//=================
	}
	
	/*
	===============================
	===============================
	*/
	
	if (prison[cell].visits == 0) {
		count++;
	}
	prison[cell].visits++;
	if (found == BOOL_TRUE) {
		prison[cell].found_on++;
	} else {
		prison[cell].found_off++;
	}
	return;
}

void init() {
	int i = 0;
	srandom(time(0));
	if (1) {//(random()%2) {
		lightswitch = BOOL_TRUE;
	} else {
		lightswitch = BOOL_FALSE;
	}
	start = lightswitch;
	//fprintf(stdout,"light starting %s\n",(lightswitch == BOOL_TRUE ? "ON" : "OFF"));
	count = 0;
	day = 0;
	for (i=0; i < PRISONER_NUM; i++) {
		prison[i].count = 0;
		prison[i].found_on = 0;
		prison[i].found_off = 0;
		prison[i].times_flipped = 0;
		prison[i].visits = 0;
	}
	finish = BOOL_FALSE;
}

int main (int argc, char **argv) {
	int r;
	init();
	while (finish == BOOL_FALSE) {
		if (prison[0].visits < 2) {
			r = 0;
		} else {
			r = random() % PRISONER_NUM;
		}
		interrogate(r);
		day++;
	}
	fprintf(stdout,"light started %s; prisoner 0 has been called %d times\n",(start == BOOL_TRUE ? "ON" : "OFF"),prison[0].visits);
	return 0;
}
