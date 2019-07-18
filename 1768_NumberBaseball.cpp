#define N 4



typedef struct {

	int strike;

	int ball;

} Result;



// API

extern Result query(int guess[]);


int numbers[5100];
int numbers_index = 0;

int arr[10] = { 0,1,2,3,4,5,6,7,8,9 };

bool flag[10000] = { false, };

void SwapArr(int arrs[], int a, int b)
{
	int tmp = arrs[a];
	arrs[a] = arrs[b];
	arrs[b]= tmp;
}

void Perm(int arrSize)
{
	if (arrSize == 4)
	{
		numbers[numbers_index] = arr[0] * 1000;
		numbers[numbers_index] += arr[1] * 100;
		numbers[numbers_index] += arr[2] * 10;
		numbers[numbers_index] += arr[3];

		numbers_index++;
	}

	for (int i = arrSize; i < 10; i++)
	{
		SwapArr(arr, i, arrSize);
		Perm(arrSize + 1);
		SwapArr(arr, i, arrSize);
	}

}

bool isFirst = true;

Result Compare(int lhs, int rhs)
{
	Result result;
	result.strike = 0;
	result.ball = 0;

	int check[10] = { 0, };

	for (int i = 0; i < 4; i++)
	{		
		if (lhs % 10 == rhs % 10)
			result.strike++;
		else
		{
			check[lhs % 10]++;
			check[rhs % 10]++;
		}
	
		if (check[lhs % 10] == 2)
			result.ball++;

		if (check[rhs % 10] == 2)
			result.ball++;

		lhs /= 10;
		rhs /= 10;

	}

	return result;
}

//guess를 수정해서 값을 반환한다.
void doUserImplementation(int guess[]) {

	// Implement a user's implementation function

	//

	// The array of guess[] is a return array that

	// is your guess for what digits[] would be.

	if (isFirst == true)
	{
		isFirst = false;
		Perm(0);		
	}

	for (int i = 0; i < numbers_index; i++)
	{
		flag[numbers[i]] = false;
	}

	int value;
	Result result;
	Result hub;

	while (1)
	{
		//값이 같아질 수 있는 확률이 있는 수를 찾는다.
		for (int i = 0; i < numbers_index; i++)
		{
			if (flag[numbers[i]] == false)
			{
				value = numbers[i];
				guess[3] = numbers[i] % 10;
				guess[2] = (numbers[i] / 10) % 10;
				guess[1] = (numbers[i] / 100) % 10;
				guess[0] = numbers[i] / 1000;
				result = query(guess);
				break;
			}
		}

		if (result.strike == 4)
			break;


		//result를 기반으로 guess와 모든수를 비교하여 답이 될 가능성을 확인한다. 
		for (int i = 0; i < numbers_index; i++)
		{
			if (flag[numbers[i]] == false)
			{
				hub = Compare(value, numbers[i]);
				if (!(hub.ball == result.ball && hub.strike == result.strike))
					flag[numbers[i]] = true;
			}
		}
	}
	
}
