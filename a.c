#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 6

/*Function Prototypes*/
int * enterTheLotteryNumber(int *array);
int * enterYourSelection(int *array);
void checkRepeatForSelection(int *array,bool isSelectionRepeat);
void checkOutOfRangeForSelection(int *array,bool isSelectionOutOfRange);
void checkRepeatForResult(int *array,bool isResultRepeat);
void checkOutOfRangeForResult(int *array,bool isResultOutOfRange);
void swap(int *a, int *b);
int * selection_sort(int * list);
char * getStatus(char *status);

/*Run the program.*/
int main (void){
	int selection[SIZE];
	int lottery[SIZE+1];
	int count = 0;
	int point = 0;
	int money = 0;
	int chosen[100][SIZE];
	char str[SIZE] = {0};
	char *status = str;

	/*判斷是否輸入錯誤*/
	bool isSelectionRepeat = false;
	bool isSelectionOutOfRange  = false;
	bool isResultRepeat = false;
	bool isResultOutOfRange  = false;

	/*輸入下注號碼*/
	printf("請按y輸入您的號碼,按f結束輸入或按e結束本程式.:");
	do{	
		char *check = getStatus(status);
		if(strcmp(check, "y")==0){
			int *selected = enterYourSelection(selection);
			checkRepeatForSelection(selected,isSelectionRepeat);
			checkOutOfRangeForSelection(selected,isSelectionOutOfRange);
			if (isSelectionRepeat==false && isSelectionOutOfRange==false)
			{
				printf("輸入成功.請按y輸入下一注,按f結束輸入或按e結束本程式.\n");
				int *sortsel = selection_sort(selected);
			//	printf("count:%d\n",count);
				for (int j = 0; j < SIZE; j++)
				{
					chosen[count][j] = sortsel[j];

				}
				count = count + 1;
			}
		}else if(strcmp(check, "f")==0){
			printf("輸入完畢,您本期一共下注了%d注,開始進行對獎.\n",count);
			break;
		}else if (strcmp(check, "e")==0) {
			exit(1);
		}
	}while(isSelectionRepeat==false && isSelectionOutOfRange==false);

	/*輸入頭獎號碼*/
	int *result = enterTheLotteryNumber(lottery);
	checkRepeatForResult(result, isResultRepeat);
	checkOutOfRangeForResult(result, isResultOutOfRange);
	if (isResultOutOfRange == false && isResultOutOfRange == false){
		printf("本期樂透頭獎中獎號碼輸入成功.\n");
		printf("本期樂透頭獎中獎號碼為: ");
		int *sorted = selection_sort(result);
		for (int t = 0; t < SIZE; t++)
		{
			printf("%d ",sorted[t]);
		}
		printf("特別號為:%d\n",result[6]);
	}
	printf("-------------準備就緒,開始兌獎---------------\n");
	
	if (count == 0)
	{
		printf("您未成功輸入號碼,無法為您對獎,程式結束.\n");
	}
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			
			for (int k = 0; k < SIZE; k++)
			{
				if (chosen[i][j] == result[k])
				{
					point++;
				}
			}
			if (chosen[i][j] == result[6]){
				point+=10;
			}			
		}
		if (point==3){
			printf("第%d注中了普獎400元\n",i+1);
			money += 400;
		}else if (point==12){
			printf("第%d注中了柒獎400元\n",i+1);
			money += 400;
		}else if (point==13){
			printf("第%d注中了陸獎1000元\n",i+1);
			money += 1000;
		}else if (point==4){
			printf("第%d注中了伍獎2000元\n",i+1);
			money += 2000;
		}else if (point==14){
			printf("第%d注中了肆獎20000元\n",i+1);
			money += 20000;
		}else if (point==5){
			printf("第%d注中了參獎150000元\n",i+1);
			money += 150000;
		}else if (point==15){
			printf("第%d注中了貳獎5000000元\n",i+1);
			money += 5000000;
		}else if (point==6){
			printf("第%d注中了頭獎100000000元\n",i+1);
			money += 100000000;
		}else {
			printf("第%d注未中獎.\n",i+1);
			money += 0;
		}
		point = 0;
	}
	printf("總中獎金額為:%d元\n",money);
	printf("-------------程式結束.-----------------------\n");						

}

int * enterTheLotteryNumber(int *array){
	printf("請輸入本期樂透頭獎中獎號碼,共6+1碼：\n");
	for(int i=0;i < SIZE+1;i++){
		scanf("%d,", &array[i]);
	}
	return array;
}
int * enterYourSelection(int *array){
	printf("請輸入本期下注的號碼：\n");
	for(int i = 0; i < SIZE;i++){
		scanf("%d,", &array[i]);
	}
	return array;
}
char * getStatus(char *status){
	fgets(status,2,stdin);
	return status;
}
	
void checkRepeatForSelection(int *array,bool isSelectionRepeat) {
	isSelectionRepeat = false;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i==j)
			{
				isSelectionRepeat = false;
				continue;
			}
			else if (array[i]==array[j])
			{
				isSelectionRepeat = true;
				if (isSelectionRepeat == true) {
					printf("下注號碼輸入重複,請重新輸入.\n");
					enterYourSelection(array);
					break;
				}
				
			}
		}
	}
}
void checkOutOfRangeForSelection(int *array,bool isSelectionOutOfRange){
		isSelectionOutOfRange = false;
		for(int i = 0;i < SIZE;i++){
			switch(array[i]){
				case 1 ...49:
					isSelectionOutOfRange = false;
					break;
				default:
					isSelectionOutOfRange = true;
					break;
			}
			if (isSelectionOutOfRange == true){
				printf("下注號碼輸入超過範圍,請重新輸入.\n");
				enterYourSelection(array);
			}else {
				continue;
			}	
		}
}

void checkRepeatForResult(int *array,bool isResultRepeat) {
	isResultRepeat = false;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (i==j)
			{
				continue;
			}
			else if (array[i]==array[j])
			{
				isResultRepeat = true;
			//	printf("ERROR\n");
				if (isResultRepeat == true) {
					printf("頭獎輸入號碼重複,請重新輸入.\n");
					enterTheLotteryNumber(array);
					break;
				}
				
			}
		}
	}
}
void checkOutOfRangeForResult(int *array,bool isResultOutOfRange){
	isResultOutOfRange = false;
		for(int i = 0;i < SIZE;i++){
			switch(array[i]){
				case 1 ...49:
					isResultOutOfRange = false;
					break;
				default:
					isResultOutOfRange = true;
					break;
			}
			if (isResultOutOfRange == true){
				printf("頭獎輸入號碼超過範圍,請重新輸入.\n");
				enterTheLotteryNumber(array);
			}else {
				continue;
			}	
		}
}

void swap(int *a, int *b){
  int temp;
  temp = *a;
  *a = *b;
  *b= temp;
}
int * selection_sort(int *list){
  int i, j, min_id;
  for(i = 0; i < SIZE-1; i++){
    min_id = i;
    for(j=i+1; j < SIZE; j++){
      if (list[j] < list[min_id])
        min_id = j;
    }
    swap(&list[i], &list[min_id]); //送地址過去swap function
  }
  return list;
}