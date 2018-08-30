#include "header.h"

int prev = -1;
int prevv = -1;

int B_DD = 0; // 큰따옴표 용
int S_DD = 0; // 작은따옴표 용

int en = 0; // ㅇ 이 있었는지 확인

/*make date using unicode and fill the queue*/
void decoder(Queue_char *queue, Queue_char_arr *queue_arr, int unicode);

/*check prev unicode is figure*/
int prev_is_figure();

/*check prev unicode is Latin*/
int prev_is_Latin();

/*print to console*/
void print_queue(Queue_char *queue);

/*print to console like module*/
void print_module(unsigned char *data, char data_char[][10]);

int prev_is_figure() {
	if (prev >= 0x0030 && prev <= 0x0039)
		return 1;
	else
		return 0;
}

int prev_is_Latin() {
	if ((prev >= 0x0041 && prev <= 0x005A) || (prev >= 0x0061 && prev <= 0x007A))
		return 1;
	else
		return 0;
}

void print_queue(Queue_char *queue) {
	unsigned char data[MODULE_CNT];
	int bit = 2;
	Queue_char* copy = queue_copy_char(queue);
	printf("========================================\n");
	while (!IsEmpty_char(copy)) {
		memset(data, 0x00, sizeof(unsigned char) * MODULE_CNT);
		for (int i = 0;i < MODULE_CNT;i++) {
			if (IsEmpty_char(copy))
				break;
			data[i] = Dequeue_char(copy);
		}
		for (int i = 0;i < 3;i++) {
			for (int j = 0;j < MODULE_CNT;j++) {
				for (int k = 0;k < 2;k++) {
					if (data[j] & (bit << ((i * 2) + k)))
						printf("● ");
					else
						printf("○ ");
				}
				printf("  ");
			}
			printf("\n");
		}
	}
	printf("========================================\n");
}

void print_module(unsigned char *data, char data_char[][10]) {
	int bit = 2;
	char tmp[10] = {0};
	int len;
	int f,b;
	printf("=====================================================\n");
	for (int j = 0;j < MODULE_CNT;j++) {
		strncpy(tmp, data_char[j], 10);
		tmp[10] = '\0';
		len = 9-strlen(tmp);
		if(len%2){ // len is 홀수
			f = len/2 - 1;
			b = (len+1)/2;
		}else{
			f = (len-1)/2;
			b = len/2 + 1;
		}
		for (int i = 0;i < f;i++)
			printf(" ");
		printf("%s", tmp);
		for (int i = 0;i < b;i++)
			printf(" ");
	}
	printf("\n");
	for (int i = 0;i < 3;i++) {
		for (int j = 0;j < MODULE_CNT;j++) {
			for (int k = 0;k < 2;k++) {
				if (data[j] & (bit << ((i * 2) + k)))
					printf(" ● ");
				else
					printf(" ○ ");
			}
			printf("  ");
		}
		printf("\n");
	}
	printf("=====================================================\n");
}

void decoder(Queue_char *queue, Queue_char_arr *queue_arr, int unicode) {
	unsigned char data;
	switch (unicode) {
		/**********************초성************************/
		case 0x1100: // ㄱ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			data = SOL_NUM[1];
			Enqueue_char_arr(queue_arr, "ㄱ");
			Enqueue_char(queue, data);
			break;
		case 0x1102: // ㄴ
			if (prev_is_figure()) {
				Enqueue_char(queue, 0);
				Enqueue_char_arr(queue_arr, "");
			}
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			data = SOL_NUM[0] + SOL_NUM[1];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄴ");
			break;
		case 0x1103: // ㄷ	
			if (prev_is_figure()) {
				Enqueue_char(queue, 0);
				Enqueue_char_arr(queue_arr, "");
			}
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1] + SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄷ");
			break;
		case 0x1105: //ㄹ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄹ");
			break;
		case 0x1106: //ㅁ
			if (prev_is_figure()) {
				Enqueue_char(queue, 0);
				Enqueue_char_arr(queue_arr, "");
			}
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅁ");
			break;
		case 0x1107: // ㅂ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅂ");
			break;
		case 0x1109: //ㅅ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅅ");
			break;
		case 0x110B: // ㅇ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			if ((prev == 0x1161) && (prevv == 0x1102 || prevv == 0x1103 || prevv == 0x1106 || prevv == 0x1107 || prevv == 0x110C || prevv == 0x110F || prevv == 0x1110 || prevv == 0x1111 || prevv == 0x1112)) {
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "ㅏ");
			}
			en = 1;
			break;
		case 0x110C: // ㅈ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅈ");
			break;
		case 0x110E: // ㅊ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅊ");
			break;
		case 0x110F: // ㅋ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			if (prev_is_figure()) {
				Enqueue_char(queue, 0);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅋ");
			break;
		case 0x1110: // ㅌ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅌ");
			break;
		case 0x1111: // ㅍ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			if (prev_is_figure()) {
				Enqueue_char(queue, 0);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅍ");
			break;
		case 0x1112: // ㅎ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			if (prev_is_figure()) {
				Enqueue_char(queue, 0);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅎ");
			break;
		case 0x1101: // ㄲ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "ㄲ");
			Enqueue_char(queue, data);
			data = SOL_NUM[1];
			Enqueue_char(queue, data);
			break;
		case 0x1104: // ㄸ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "ㄸ");
			Enqueue_char(queue, data);
			data = SOL_NUM[1] + SOL_NUM[2];
			Enqueue_char(queue, data);
			break;
		case 0x1108: // ㅃ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "ㅃ");
			data = SOL_NUM[1] + SOL_NUM[3];
			Enqueue_char(queue, data);
			break;
		case 0x110A: // ㅆ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "ㅆ");
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			break;
		case 0x110D: // ㅉ
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "ㅉ");
			data = SOL_NUM[1] + SOL_NUM[5];
			Enqueue_char(queue, data);
			break;
			/***************종성*******************/
		case 0x11A8: // ㄱ
			if (prev == 0x1165) { // 억
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "억");
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[5];
			}
			else if (prev == 0x1169) { // 옥
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "옥");
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[4] + SOL_NUM[5];
			}
			else {
				data = SOL_NUM[0];
				Enqueue_char_arr(queue_arr, "ㄱ");
			}
			Enqueue_char(queue, data);
			break;
		case 0x11AB: // ㄴ
			if (prev == 0x1165) { // 언
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "언");
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			}
			else if (prev == 0x1167) { // 연
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "연");
				data = SOL_NUM[0] + SOL_NUM[5];
			}
			else if (prev == 0x116E) { // 운
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "운");
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3];
			}
			else if (prev == 0x1169) { // 온
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "온");
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			}
			else if (prev == 0x1173) { // 은
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "은");
				data = SOL_NUM[0] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			}
			else if (prev == 0x1175) { // 인
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "인");
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			}
			else {
				data = SOL_NUM[2] + SOL_NUM[3];
				Enqueue_char_arr(queue_arr, "ㄴ");
			}
			Enqueue_char(queue, data);
			break;
		case 0x11AE: // ㄷ
			data = SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄷ");
			break;
		case 0x11AF: //ㄹ
			if (prev == 0x1165) { // 얼
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "얼");
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			}
			else if (prev == 0x1167) { // 열
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "열");
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			}
			else if (prev == 0x116E) { // 울
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "울");
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			}
			else if (prev == 0x1173) { // 을
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "을");
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			}
			else {
				Enqueue_char_arr(queue_arr, "ㄹ");
				data = SOL_NUM[2];
			}
			Enqueue_char(queue, data);
			break;
		case 0x11B7: //ㅁ
			data = SOL_NUM[2] + SOL_NUM[5];
			Enqueue_char_arr(queue_arr, "ㅁ");
			Enqueue_char(queue, data);
			break;
		case 0x11B8: // ㅂ
			data = SOL_NUM[0] + SOL_NUM[2];
			Enqueue_char_arr(queue_arr, "ㅂ");
			Enqueue_char(queue, data);
			break;
		case 0x11BA: //ㅅ
			if (prev == 0x1165) { // 엇
				if (prevv == 0x1101) { // 껏
					Dequeue_Back_char(queue);
					Dequeue_Back_char(queue);
					Dequeue_Back_char(queue);
					Dequeue_Back_char_arr(queue_arr);
					Dequeue_Back_char_arr(queue_arr);
					Dequeue_Back_char_arr(queue_arr);
					data = SOL_NUM[5];
					Enqueue_char(queue, data);
					Enqueue_char_arr(queue_arr, "껏");
					data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[5];
					Enqueue_char(queue, data);
					Enqueue_char_arr(queue_arr, "");
					Enqueue_char_arr(queue_arr, "");
					data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
				}
				else {
					Dequeue_Back_char(queue);
					Dequeue_Back_char_arr(queue_arr);
					data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[5];
					Enqueue_char(queue, data);
					Enqueue_char_arr(queue_arr, "엇");
					data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
					Enqueue_char_arr(queue_arr, "");
				}
			}
			else {
				data = SOL_NUM[4];
				Enqueue_char_arr(queue_arr, "ㅅ");
			}
			Enqueue_char(queue, data);
			break;
		case 0x11BC: // ㅇ
			if ((prev == 0x1165) && (prevv == 0x1109 || prevv == 0x110C || prevv == 0x110A || prevv == 0x110D)) {
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "엉");
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			}
			else if (prev == 0x1167) { // 영
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "영");
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			}
			else if (prev == 0x1169) { // 옹
				Dequeue_Back_char(queue);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "옹");
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			}
			else {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "ㅇ");
			}
			Enqueue_char(queue, data);
			break;
		case 0x11BD: // ㅈ
			data = SOL_NUM[0] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅈ");
			break;
		case 0x11BE: // ㅊ
			data = SOL_NUM[2] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅊ");
			break;
		case 0x11BF: // ㅋ
			data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅋ");
			break;
		case 0x11C0: // ㅌ
			data = SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅌ");
			break;
		case 0x11C1: // ㅍ
			data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅍ");
			break;
		case 0x11C2: // ㅎ
			data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅎ");
			break;
			/***************쌍받침*********************/
		case 0x11A9: // ㄲ
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄲ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11BB: // ㅆ
			if (prev == 0x1161 && prevv == 0x1111) {
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "ㅏ");
			}
			data = SOL_NUM[1] + SOL_NUM[4];
			Enqueue_char_arr(queue_arr, "ㅆ");
			Enqueue_char(queue, data);
			break;
			/****************겹받침*******************/
		case 0x11AA: // 윿
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄳ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11AC: // 읁
			data = SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄵ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11AD: // 읂
			data = SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄶ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11B1: // 읆
			data = SOL_NUM[2];
			Enqueue_char(queue, data);
			data = SOL_NUM[2] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄻ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11B0: // 읅
			data = SOL_NUM[2];
			Enqueue_char(queue, data);
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄺ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11B2: // 읇
			data = SOL_NUM[2];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄼ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11B3: // 읈
			data = SOL_NUM[2];
			Enqueue_char(queue, data);
			data = SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄽ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11B4: // 읉
			data = SOL_NUM[2];
			Enqueue_char(queue, data);
			data = SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄾ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11B5: // 읊
			data = SOL_NUM[2];
			Enqueue_char(queue, data);
			data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㄿ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11B6: // 읋
			data = SOL_NUM[2];
			Enqueue_char(queue, data);
			data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅀ");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x11B9: // 읎
			data = SOL_NUM[0] + SOL_NUM[2];
			Enqueue_char(queue, data);
			data = SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "ㅄ");
			Enqueue_char_arr(queue_arr, "");
			break;
			/*********************모음********************/
		case 0x1161: // ㅏ
			if (prev == 0x1100) { // 가
				Dequeue_Back_char(queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[5];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "가");
			}
			else if (prev == 0x1101) { // 까
				Dequeue_Back_char(queue);
				Dequeue_Back_char(queue);
				data = SOL_NUM[5];
				Enqueue_char(queue, data);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[5];
				Dequeue_Back_char_arr(queue_arr);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "까");
				Enqueue_char_arr(queue_arr, "");
			}
			else if (prev == 0x1102) { // 나
				Dequeue_Back_char(queue);
				data = SOL_NUM[0] + SOL_NUM[1];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "나");
			}
			else if (prev == 0x1103) { // 다
				Dequeue_Back_char(queue);
				data = SOL_NUM[1] + SOL_NUM[2];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "다");
			}
			else if (prev == 0x1106) { // 마
				Dequeue_Back_char(queue);
				data = SOL_NUM[0] + SOL_NUM[3];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "마");
			}
			else if (prev == 0x1107) { // 바
				Dequeue_Back_char(queue);
				data = SOL_NUM[1] + SOL_NUM[3];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "바");
			}
			else if (prev == 0x1109) { // 사
				Dequeue_Back_char(queue);
				data = SOL_NUM[0] + SOL_NUM[1];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "사");
			}
			else if (prev == 0x110A) { // 싸
				Dequeue_Back_char(queue);
				Dequeue_Back_char(queue);
				data = SOL_NUM[5];
				Enqueue_char(queue, data);
				data = SOL_NUM[0] + SOL_NUM[1];
				Dequeue_Back_char_arr(queue_arr);
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "싸");
				Enqueue_char_arr(queue_arr, "");
			}
			else if (prev == 0x110C) { // 자
				Dequeue_Back_char(queue);
				data = SOL_NUM[1] + SOL_NUM[5];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "자");
			}
			else if (prev == 0x110F) { // 카
				Dequeue_Back_char(queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "카");
			}
			else if (prev == 0x1110) { // 타
				Dequeue_Back_char(queue);
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "타");
			}
			else if (prev == 0x1111) { // 파
				Dequeue_Back_char(queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "파");
			}
			else if (prev == 0x1112) { // 하
				Dequeue_Back_char(queue);
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3];
				Dequeue_Back_char_arr(queue_arr);
				Enqueue_char_arr(queue_arr, "하");
			}
			else if (en) { // 아
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "아");
				en = 0;
			}
			else {
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "ㅏ");
			}
			Enqueue_char(queue, data);
			break;
		case 0x1163: // ㅑ
			data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "야");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅑ");
			break;
		case 0x1165: // ㅓ
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "어");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅓ");
			break;
		case 0x1167: // ㅕ
			data = SOL_NUM[0] + SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "여");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅕ");
			break;
		case 0x1169: // ㅗ
			data = SOL_NUM[0] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "오");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅗ");
			break;
		case 0x116D: // ㅛ
			data = SOL_NUM[1] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "요");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅛ");
			break;
		case 0x116E: // ㅜ
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "우");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅜ");
			break;
		case 0x1172: // ㅠ
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "유");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅠ");
			break;
		case 0x1173: // ㅡ
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "으");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅡ");
			break;
		case 0x1175: // ㅣ
			data = SOL_NUM[0] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "이");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅣ");
			break;
		case 0x1162: // ㅐ
			if ((prev == 0x110B) && (prevv == 0x1163 || prevv == 0x116E || prevv == 0x116A || prevv == 0x116F)) {
				data = SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "애");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅐ");
			break;
		case 0x1164: // ㅒ
			data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "얘");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅒ");
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x1166: // ㅔ
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "에");
				en = 0;
			}
			else
			Enqueue_char_arr(queue_arr, "ㅔ");
			break;
		case 0x1168: // ㅖ
			if (!(prevv >= 0x11A8 && prevv <= 0x11C2) && prev == 0x110B) {
				data = SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "예");
				en = 0;
			}
				else
			Enqueue_char_arr(queue_arr, "ㅖ");
			break;
		case 0x116A: // ㅘ
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "와");
				en = 0;
			}
			else
				Enqueue_char_arr(queue_arr, "ㅘ");
			break;
		case 0x116B: // ㅙ
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "왜");
				en = 0;
			}
				Enqueue_char_arr(queue_arr, "ㅙ");
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x116C: // ㅚ
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "외");
				en = 0;
			}
				Enqueue_char_arr(queue_arr, "ㅚ");
			break;
		case 0x116F: // ㅝ
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "워");
				en = 0;
			}
				Enqueue_char_arr(queue_arr, "ㅝ");
			break;
		case 0x1170: // ㅞ
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "웨");
				en = 0;
			}
				Enqueue_char_arr(queue_arr, "ㅞ");
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x1171: // ㅟ
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[4];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "위");
				en = 0;
			}
				Enqueue_char_arr(queue_arr, "ㅟ");
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x1174: // ㅢ
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			if (en) {
				Enqueue_char_arr(queue_arr, "의");
				en = 0;
			}
			Enqueue_char_arr(queue_arr, "ㅢ");
			break;
			/**********************figure**************************/
		case 0x0030: // 0
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "0");
			break;
		case 0x0031: // 1
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "1");
			break;
		case 0x0032: // 2
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "2");
			break;
		case 0x0033: // 3
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[1];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "3");
			break;
		case 0x0034: // 4
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "4");
			break;
		case 0x0035: // 5	
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "5");
			break;
		case 0x0036: // 6	
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "6");
			break;
		case 0x0037: // 7
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "7");
			break;
		case 0x0038: // 8	
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "8");
			break;
		case 0x0039: // 9
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char_arr(queue_arr, "");
				Enqueue_char(queue, data);
			}
			if (!prev_is_figure()) {
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1] + SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "9");
			break;

			/**********************Latin**************************/
		case 0x0041: // A
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "A");
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			break;

		case 0x0042: // B
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "B");
			data = SOL_NUM[0] + SOL_NUM[2];
			Enqueue_char(queue, data);
			break;

		case 0x0043: // C
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "C");
			data = SOL_NUM[0] + SOL_NUM[1];
			Enqueue_char(queue, data);
			break;

		case 0x0044: // D
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "D");
			break;

		case 0x0045: // E
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "E");
			break;

		case 0x0046: // F
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "F");
			break;

		case 0x0047: // G
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "G");
			break;

		case 0x0048: // H
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "H");
			break;

		case 0x0049: // I
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[1] + SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "I");
			break;

		case 0x004A: // J
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "J");
			break;

		case 0x004B: // K
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "K");
			break;

		case 0x004C: // L
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "L");
			break;

		case 0x004D: // M
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "M");
			break;

		case 0x004E: // N
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "N");
			break;

		case 0x004F: // O
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "O");
			break;

		case 0x0050: // P
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "P");
			break;

		case 0x0051: // Q
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "Q");
			break;

		case 0x0052: // R
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "R");
			break;

		case 0x0053: // S
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "S");
			break;

		case 0x0054: // T
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "T");
			break;

		case 0x0055: // U
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "U");
			break;

		case 0x0056: // V
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "V");
			break;

		case 0x0057: // W
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "W");
			break;
		case 0x0058: // X
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "X");
			break;
		case 0x0059: // Y
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "Y");
			break;
		case 0x005A: // Z
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "Z");
			break;
		case 0x0061: // a
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "a");
			break;
		case 0x0062: // b
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "b");
			break;
		case 0x0063: // c
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "c");
			break;
		case 0x0064: // d
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "d");
			break;
		case 0x0065: // e
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "e");
			break;
		case 0x0066: // f
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "f");
			break;
		case 0x0067: // g
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[2]+ SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "g");
			break;
		case 0x0068: // h
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[2]+ SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "h");
			break;
		case 0x0069: // i
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1]+ SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "i");
			break;
		case 0x006A: // j
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1]+ SOL_NUM[2]+ SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "j");
			break;
		case 0x006B: // k
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "k");
			break;
		case 0x006C: // l
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[2]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "l");
			break;
		case 0x006D: // m
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "m");
			break;
		case 0x006E: // n
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[3]+ SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "n");
			break;
		case 0x006F: // o
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[3]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "o");
			break;
		case 0x0070: // p
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[2]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "p");
			break;
		case 0x0071: // q
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[2]+ SOL_NUM[3]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "q");
			break;
		case 0x0072: // r
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[2]+ SOL_NUM[3]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "r");
			break;
		case 0x0073: // s
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1]+ SOL_NUM[2]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "s");
			break;
		case 0x0074: // t
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1]+ SOL_NUM[2]+ SOL_NUM[3]+ SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "t");
			break;
		case 0x0075: // u
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[4]+ SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "u");
			break;
		case 0x0076: // v
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[2]+ SOL_NUM[4]+ SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "v");
			break;
		case 0x0077: // w
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[1]+ SOL_NUM[2]+ SOL_NUM[3]+ SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "w");
			break;
		case 0x0078: // x
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[4]+ SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "x");
			break;
		case 0x0079: // y
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[1]+ SOL_NUM[3]+ SOL_NUM[4]+ SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "y");
			break;
		case 0x007A: // z
			if (!prev_is_Latin()) {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0]+ SOL_NUM[3]+ SOL_NUM[4]+ SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "z");
			break;
		/***********************특수문자********************************/
		case 0x002E: // .
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, ".");
			break;
		case 0x003F: // ?
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "?");
			break;
		case 0x0021: // !
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "!");
			break;
		case 0x002C: // ,
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, ",");
			break;
		case 0x0020: // 공백
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = 0;
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x0028: // (
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char_arr(queue_arr, "(");
			Enqueue_char(queue, data);
			break;
		case 0x0029: // )
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char_arr(queue_arr, ")");
			Enqueue_char(queue, data);
			break;
		case 0x003A: // :
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[3];
			Enqueue_char(queue, data);
			data = SOL_NUM[2];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, ":");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x0022: // "
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			if (B_DD == 0) {
				data = SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
				B_DD = 1;
			}
			else {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				B_DD = 0;
			}
			Enqueue_char_arr(queue_arr, "\"");
			Enqueue_char(queue, data);
			break;
		case 0x0027: // '
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			if (S_DD == 0) {
				data = SOL_NUM[5];
				Enqueue_char(queue, data);
				data = SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
				S_DD = 1;
			}
			else {
				data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
				Enqueue_char(queue, data);
				data = SOL_NUM[4];
				S_DD = 0;
			}
			Enqueue_char_arr(queue_arr, "\'");
			Enqueue_char(queue, data);
			break;
		case 0x007B: // {
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[2] + SOL_NUM[4];	
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "{");
			break;
		case 0x007D: // }
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "}");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x005B: // [
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "[");
			break;
		case 0x005D: // ]
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "");
			Enqueue_char_arr(queue_arr, "]");
			break;
		case 0x002D: // -
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "-");
			break;
		case 0x007E: // ~
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			data = SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "~");
			Enqueue_char_arr(queue_arr, "");
			break;
		/**************************** 약어 ********************************/
		case 0x4001: // 그래서
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "그래서");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x4002: // 그러나
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "그러나");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x4003: // 그러면
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[2] + SOL_NUM[3];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "그러면");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x4004: // 그러므로
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[2] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "그러므로");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x4005: // 그런데
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[4];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "그러므로");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x4006: // 그리고
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[4] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "그리고");
			Enqueue_char_arr(queue_arr, "");
			break;
		case 0x4007: // 그리하여
			if (prev_is_Latin()) {
				data = SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue_char(queue, data);
				Enqueue_char_arr(queue_arr, "");
			}
			data = SOL_NUM[0];
			Enqueue_char(queue, data);
			data = SOL_NUM[0] + SOL_NUM[3] + SOL_NUM[5];
			Enqueue_char(queue, data);
			Enqueue_char_arr(queue_arr, "그리하여");
			Enqueue_char_arr(queue_arr, "");
			break;

	}
	prevv = prev;
	prev = unicode;
}
