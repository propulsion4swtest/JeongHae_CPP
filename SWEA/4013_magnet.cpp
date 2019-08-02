#include<iostream>
#include<vector>

#define N 0
#define S 1

#define LEFT 6
#define RIGHT 2

#define CLOCK 1
#define REVCLOCK -1

using namespace std;


class Gear
{
public:
	vector<int> tooth;
	Gear *left;
	Gear *right;

	Gear(vector<int> &vi)
	{
		tooth = vi;
	}


	void Cycle(int dir)
	{
		if (dir == CLOCK)
		{
			int tmp = tooth[7];
			for (int i = 7; i >= 1; i--)
			{
				tooth[i] = tooth[i - 1];
			}
			tooth[0] = tmp;
		}
		else if (dir == REVCLOCK)
		{
			int tmp = tooth[0];
			for (int i = 0; i <= 6; i++)
			{
				tooth[i] = tooth[i + 1];
			}
			tooth[7] = tmp;
		}
	}


	void TurnLeft(int dir)
	{
		if (left != nullptr)
		{
			if (left->tooth[RIGHT] != tooth[LEFT])
			{
				left->TurnLeft(-1 * dir);
			}
		}
		Cycle(dir);
	}


	void TurnRight(int dir)
	{
		if (right != nullptr)
		{
			if (right->tooth[LEFT] != tooth[RIGHT])
			{
				right->TurnRight(-1 * dir);
			}
		}
		Cycle(dir);
	}


	void Turn(int dir)
	{
		if (left != nullptr)
		{
			if (left->tooth[RIGHT] != tooth[LEFT])
			{	
				left->TurnLeft(-1 * dir);
			}
		}

		if (right != nullptr)
		{
			if (right->tooth[LEFT] != tooth[RIGHT])
			{
				right->TurnRight(-1 * dir);
			}
		}
		Cycle(dir);
	}

};

vector<Gear> gears;


void PrintGears(vector<Gear> &gears)
{
	cout << "\n\n";
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << gears[i].tooth[j] << " ";

		}
		cout << endl;
	}
	cout << "\n\n";
}

int main(void)
{
	int T;
	cin >> T;

	for (int testCase = 0; testCase < T; testCase++)
	{
		gears.clear();
		int K;
		cin >> K;
		for (int gearNum = 0; gearNum < 4; gearNum++)
		{
			int input;
			vector<int> vi;
			for (int toothNum = 0; toothNum < 8; toothNum++)
			{
				cin >> input;
				vi.push_back(input);
			}
			gears.push_back(Gear(vi));
		}

		gears[0].left = nullptr;
		gears[0].right = &gears[1];

		gears[1].left = &gears[0];
		gears[1].right = &gears[2];

		gears[2].left = &gears[1];
		gears[2].right = &gears[3];

		gears[3].left = &gears[2];
		gears[3].right = nullptr;

		int gearNum, command;

		
		for (int i = 0; i < K; i++)
		{
			cin >> gearNum >> command;
			gearNum--;
			gears[gearNum].Turn(command);
		}		

		int result = 0;
		result += gears[0].tooth[0];
		result += 2 * gears[1].tooth[0];
		result += 4 * gears[2].tooth[0];
		result += 8 * gears[3].tooth[0];


		cout << "#" << testCase + 1 << " " << result << endl;

		/*
		gears[0].Turn(CLOCK);
		PrintGears(gears);

		gears[2].Turn(REVCLOCK);
		PrintGears(gears);
		*/
		/*
		gears[0].Cycle(CLOCK);
		gears[0].Cycle(CLOCK);
		gears[0].Cycle(REVCLOCK);
		gears[0].Cycle(REVCLOCK);
		*/
	}


}
