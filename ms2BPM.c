#include <stdio.h>
int main() {
	float bpm;
	float ms;
	while (1) {
		printf("Input ms\n(Enter '0' to exit program)\n");
		
		scanf_s("%f", &ms);
		if (ms == 0.0f)
			break;
		else {
			bpm = 60000.0f / ms;
			printf("BPM:%.2f\n", bpm);
		}
}
	return 0;
}
