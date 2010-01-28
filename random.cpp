#include <cstdlib>

int randomInt(int min, int max){
	return int(((float(rand())/float(RAND_MAX)) * (max-min+1)) + min);
}

float randomFloat(float min, float max){
	return float(((float(rand())/float(RAND_MAX)) * (max-min+1)) + min);
}

