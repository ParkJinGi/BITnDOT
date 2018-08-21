#include "decoder.h"

#ifndef FOR_TEST
#include "control_module.h"
#endif

Queue queue;

int main() {

#ifndef FOR_TEST
	InitModule();
#endif

	InitQueue(&queue);
	/*while (1) {
		clear(0);
		delay(1000);
		digitalWrite(latch_pin[0], LOW);
		shiftOut(data_pin[0], clock_pin[0], MSBFIRST, 0x00);
		digitalWrite(latch_pin[0], HIGH);
		delay(1000);
	}*/

	int t[7]={0x0041,0x0062,0x1105,0x1161,0x1175,0x1103,0x1161};

	for(int i=0;i<4;i++)
		decoder(&queue, t[i]);
	
	print_queue(&queue);
}
