#include<iostream>
#include<vector>
#include<string>


using namespace std;



vector<vector<bool>> board;

int index = 0;
void UnCapsuled(string &str, int beginX, int endX, int beginY, int endY)
{
	if(str[index] == 'x')
	{
		index++;
		UnCapsuled(str,beginX,(beginX + endX)/2, beginY, (beginY + endY)/2);

		index++;
		UnCapsuled(str,(beginX + endX) /2 + 1, endX, beginY,(beginY + endY)/2);

		index++;
		UnCapsuled(str,beginX,(beginX+ endX)/2, (beginY + endY)/2 + 1, endY);

		index++;
		UnCapsuled(str,(beginX +endX) /2 + 1, endX, (beginY + endY)/2 + 1, endY);
	}
	else{
	
		for(int row = beginY; row<=endY; row++)
		{
			for(int cul = beginX; cul <= endX; cul++)
			{
				if(str[index] == 'b')
					board[row][cul] = true;
			}
		
		}
	}

}

void PrintBoard(int width, int height)
{
	cout<<"\n\n";
	for(int row = 0; row<height; row++)
	{
			for(int cul = 0; cul < width; cul++)
			{
				if(board[row][cul] == false)
					cout<<". ";
				else
					cout<<"■";
			}
			cout<<endl;	
	}
	cout<<"\n\n";
}


string Reverse(string &str)
{
	if(str[index] != 'x')
	{
		string tmpStr;
		tmpStr.push_back(str[index]);

		return tmpStr;
	}
	else
	{
		string tmpStr;
		
		index++;
		string leftUp = Reverse(str);
		
		index++;
		string rightUp = Reverse(str);
		
		index++;
		string leftDown = Reverse(str);
		
		index++;
		string rightDown = Reverse(str);

		tmpStr = string("x") + leftDown + rightDown + leftUp + rightUp;
	
		return tmpStr;
	}
}



int main(void)
{
	/*
	int length = 16;

	board.assign(length, vector<bool>(length,false));

	//string str = "xxwwwbxwxwbbbwwxxxwwbbbwwwwbb";
	string str = "xxbwwbxwbbwxbwwbxwbbw";

	UnCapsuled(str,0,length-1,0,length-1);
	PrintBoard(length,length);
	*/

	string str = "xxwwwbxwxwbbbwwxxxwwbbbwwwwbb";
	string result = Reverse(str);
	cout<<result<<endl;

	return 0;
}
