#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * 绋嬪簭鎬濊矾锛�
 * 1. 鍒濆鍖栨鐩橈紝瀹屽叏闅忔満杈撳嚭涓€涓鐩樻暟缁剆olution
 * 2. 灏嗘鐩樼殑x锛寉鍧愭爣鏀逛负瀵硅绾垮潗鏍囩殑褰㈠紡锛屼篃鍗充富瀵硅绾�2n-1鏉★紝鍓瑙掔嚎2n-1鏉°€傚皢鍚屼竴鏉″瑙掔嚎鍐呯殑鎬绘瀛愭暟鍐欏叆isrepeat鏁扮粍涔嬩腑銆傝繖鏍蜂互鏉�
 * 3. evaluate_first鍑芥暟鐢ㄦ潵璁＄畻绗竴娆＄敓鎴愮殑闅忔満妫嬬洏鏁扮粍鐨勫瑙掔嚎涓婄殑妫嬪瓙鏁板拰鍐茬獊鏁般€�
 * 4. 鏋勯€犲啿绐佹暟璁＄畻鍑芥暟evaluate锛岀敤浜庣粰鏇挎崲浜嗛殢鏈轰袱鍒楃殑閭诲眳妫嬬洏璁＄畻鍏跺啿绐佹暟銆�
 * 5. 濡傛灉鎶婇偦灞呴亶鍘嗕簡锛岃繕娌℃湁鎵惧埌value=0鐨勮В锛屽垯閲嶅惎绋嬪簭銆�
*/
long long number_of_queens;
int *solution, *neighbour;
int *isrepeat_temp, *isrepeat;
int *posi_k, *nega_k;
int t;
int value;
void initqueens()
{
	scanf("%lld", &number_of_queens);
	solution = (int *)malloc(sizeof(int) * (number_of_queens) + 1);
	int temp,num;
	for(int i = 0; i < number_of_queens; i++)
	{
		solution[i] = i + 1;
	}
	for(int i = 0; i < number_of_queens; i++)
	{
		temp = solution[i];
		solution[i] = solution[(num = rand()%(number_of_queens))];
		solution[num] = temp;
	}

}


int evaluate_first()
{
	int sub_value = 0;

	posi_k = (int *)malloc(sizeof(int) * (number_of_queens) + 1);
	nega_k = (int *)malloc(sizeof(int) * (number_of_queens) + 1);
	isrepeat_temp = (int *)malloc(sizeof(int) * (4 * number_of_queens - 1));
	
	for(int i = 0; i < 4 * number_of_queens - 2; i++)
	{
		isrepeat_temp[i] = 0;
	}
	isrepeat = isrepeat_temp + 2 * number_of_queens - 1;
	
	for(int i = 0; i < number_of_queens; i++)
	{
		posi_k[i] = i - solution[i];
		nega_k[i] = i + solution[i];

	}
	for(int i = 0; i < number_of_queens; i++)
	{
		isrepeat[posi_k[i] - number_of_queens + 2]++;
		isrepeat[nega_k[i]]++;
	}
	for(int i = 0; i < 4 * number_of_queens - 2; i++)
	{
		if(isrepeat_temp[i] >= 2)
		{
			sub_value += isrepeat_temp[i] * (isrepeat_temp[i] - 1) / 2;
		}
	}
	return sub_value;
}



int evaluate(int row_1, int row_2)
{
	int temp;
	int sub_value = value;

	int solu_row_2 = solution[row_1];
	int solu_row_1 = solution[row_2];
	//change the value
	
	int posik_1 = row_1 - solution[row_1];
	int negak_1 = row_1 + solution[row_1];
	int posik_2 = row_2 - solution[row_2];
	int negak_2 = row_2 + solution[row_2];
	
	int posik_1_changed = row_1 - solu_row_1;
	int posik_2_changed = row_2 - solu_row_2;
	int negak_1_changed = row_1 + solu_row_1;
	int negak_2_changed = row_2 + solu_row_2;
	
	int delta_value_1 = (--isrepeat[posik_1 - number_of_queens + 2]) + (--isrepeat[posik_2 - number_of_queens + 2]) + (--isrepeat[negak_1]) + (--isrepeat[negak_2]) - 4;
	int delta_value_2 = (isrepeat[posik_1_changed - number_of_queens + 2]++) + (isrepeat[posik_2_changed - number_of_queens + 2]++) + (isrepeat[negak_1_changed]++) + (isrepeat[negak_2_changed]++);
	
	int delta_value = delta_value_2 - delta_value_1;

	sub_value += delta_value;

	if(sub_value == 0 || delta_value <= 0)
	{
		temp = solution[row_1];
		solution[row_1] = solution[row_2];
		solution[row_2] = temp;
		value = sub_value;
		return 1;
	}
	else if(delta_value > 0)
	{
		isrepeat[posik_1 - number_of_queens + 2]++;
		isrepeat[posik_2 - number_of_queens + 2]++;
		isrepeat[negak_1]++;
		isrepeat[negak_2]++;
		isrepeat[posik_1_changed - number_of_queens + 2]--;
		isrepeat[posik_2_changed - number_of_queens + 2]--;
		isrepeat[negak_1_changed]--;
		isrepeat[negak_2_changed]--;

		return -1;
	}
}

int exchange_lines()
{
	int row_1 = rand()%number_of_queens;
	int row_2 = rand()%number_of_queens;
	return 0; // evaluate(row_1, row_2);
}

int restart_recalc()
{
	int temp, num;
	for(int i = 0; i < number_of_queens; i++)
	{
		temp = solution[i];
		solution[i] = solution[(num = rand()%(number_of_queens))];
		solution[num] = temp;
	}
	
	value = evaluate_first();

	return value;
}

int main(void)
{	
	long seed = 820;
//	srand(seed);
	clock_t start_t, end_t;
	start_t = clock();
	initqueens();
	end_t = clock();
	double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Used time: \t%lf\n", total_t);

	int flag, times;
	value = evaluate_first();
	times = 0;
	flag = exchange_lines();
	printf("value = %d\n", value);
	while(value != 0)
	{
		times++;
		if(times < number_of_queens + 20)
			flag = exchange_lines();
		else if(times >= number_of_queens + 20)
		{
			value = restart_recalc();
			flag = exchange_lines();
		}
		if(value == 0) break;
	}

	printf("----------------------\n");
	for(int i = 0; i < number_of_queens; i++)
		printf("%d\n", solution[i]);
	
//	for(int i = 0; i < number_of_queens; i++)
//	{
//		printf("%d\n", solution[i]);
//	}
	if(value == 0)
	{
		clock_t end2_t;
		double total2_t;
		end2_t = clock();
		total2_t = (double)(end2_t - start_t) / CLOCKS_PER_SEC;
		printf("Used time: \t%lfs\nvalue = %d", total2_t, evaluate_first());
	}
	
}
