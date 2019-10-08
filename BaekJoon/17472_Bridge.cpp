#include<iostream>
#include<queue>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Node {
public:
	int x, y;
	
	Node() : Node(-1,-1)
	{	}

	Node(int x_, int y_) : x(x_), y(y_)
	{	}
};

class GraphNode {
public:
	int from, to, length;

	GraphNode() : GraphNode(-1,-1,-1)
	{	}

	GraphNode(int from_, int to_, int length_) : from(from_), to(to_), length(length_)
	{	}
};

int N, M;
bool orgBoard[105][105];
int moveX[4] = { 1,0,-1,0 };
int moveY[4] = { 0,1,0,-1 };
int board[105][105];
int graph[8][8];
int islandsCnt;
bool masks[10000];


vector<GraphNode> graphNodes;
void SetGraphNode() {
	graphNodes.clear();
	//graph의 정보를 바탕으로 graphNodes를 초기화 시킨다.
	for (int row = 0; row < islandsCnt; row++)
		for (int cul = row + 1; cul < islandsCnt; cul++) 
			if (graph[row][cul] != 9999)
				graphNodes.push_back(GraphNode(row, cul, graph[row][cul]));
}


void PrintBoard(int arr[][105]) {
	cout << "\n\n";
	for (int row = 0; row < N; row++) {
		for (int cul = 0; cul < M; cul++) {
			if (arr[row][cul] == -1)
				cout << " .";
			else
				cout << arr[row][cul] << " ";
		}
		cout << "\n";
	}
	cout << "\n\n";
}


void BFS(int cX, int cY, int index) {
	queue<Node> qu;
	qu.push(Node(cX, cY));
	board[cY][cX] = index;

	while (!qu.empty()) {
		Node cNode = qu.front();
		qu.pop();
		int nX, nY;
		for (int dir = 0; dir < 4; dir++) {
			nX = cNode.x + moveX[dir];
			nY = cNode.y + moveY[dir];

			if (nX < 0 || nX >= M || nY < 0 || nY >= N)
				continue;

			if (orgBoard[nY][nX] == 0 || board[nY][nX] != -1)
				continue;

			board[nY][nX] = index;
			qu.push(Node(nX, nY));
		}
	}
}



void GetIslands() {
	int index = 0;
	for (int row = 0; row < N; row++) {
		for (int cul = 0; cul < M; cul++) {
			if (orgBoard[row][cul] == true && board[row][cul] == -1)
			{
				BFS(cul, row, index);
				index++;
			}
		}
	}
	islandsCnt = index;
}



void SetGraph() {
	int length = 0, cIndex, nIndex;
	int nX, nY;
	for (int row = 0; row < N; row++) {
		for (int cul = 0; cul < M; cul++) {
			//row, cul 위치에서 다리를 만들기 시작한다.

			if (board[row][cul] != -1) {
				cIndex = board[row][cul];
				for (int dir = 0; dir < 4; dir++) {
					// dir 방향으로 다리를 뻗어가며 만든다.
					length = 1;
					nX = cul + moveX[dir];
					nY = row + moveY[dir];

					while (1) {
						if (nX < 0 || nX >= M || nY < 0 || nY >= N)
							break;

						if (board[nY][nX] != -1) {
							if (length - 1 >= 2) {
								nIndex = board[nY][nX];

								if (cIndex != nIndex) {
									//graph를 갱신한다.
									graph[cIndex][nIndex] = min(graph[cIndex][nIndex], length - 1);
									graph[nIndex][cIndex] = min(graph[nIndex][cIndex], length - 1);
								}
							}
							break;
						}

						length++;
						nX += moveX[dir];
						nY += moveY[dir];
					}
				}
			}
		}
	}
}


int TravelIslands() {
	int flag[1000] = { false, };
	queue<int> qu;
	qu.push(0);
	flag[0] = true;
	int cIndex;
	int score = 0, cnt = 0;
	cnt++;
	while (!qu.empty()) {
		cIndex = qu.front();
		qu.pop();

		for (int i = 0; i < islandsCnt; i++) {
			if (flag[i] == true)
				continue;

			if (graph[cIndex][i] == 9999)
				continue;

			flag[i] = true;
			qu.push(i);
			score += graph[cIndex][i];
			cnt++;
		}
	}
	
	if (cnt == islandsCnt)
		return score;
	else
		return 2000000000;
}


//masks에 맞추어 graphNodes의 정보를 graphs에 담는다.
void SetBridge() {
	for (int from = 0; from < islandsCnt; from++)
		for (int to = 0; to < islandsCnt; to++)
			graph[from][to] = 9999;

	int from, to, length;
	for (int i = 0; i < graphNodes.size(); i++) {
		if (masks[i] == true) {
			from = graphNodes[i].from;
			to = graphNodes[i].to;
			length = graphNodes[i].length;
			graph[from][to] = length;
			graph[to][from] = length;
		}
	}
}

//masks를 초기화 시킨다.(2 PI graphNodes.size())
int RPerm(int arrSize) {
	if (arrSize == graphNodes.size()) {
		SetBridge();
		int ret = TravelIslands();
		return ret;
	}

	int tmp, ret = 2000000000;

	masks[arrSize] = true;
	tmp = RPerm(arrSize + 1);
	ret = min(ret, tmp);
	
	masks[arrSize] = false;
	tmp = RPerm(arrSize + 1);
	ret = min(ret, tmp);

	return ret;
}



int main(void) {
	cin >> N >> M;

	for (int row = 0; row < N; row++) {
		for (int cul = 0; cul < M; cul++) {
			cin >> orgBoard[row][cul];
			board[row][cul] = -1;
		}
	}

	GetIslands();
	//PrintBoard(board);
	for (int row = 0; row < islandsCnt; row++)
		for (int cul = 0; cul < islandsCnt; cul++)
			graph[row][cul] = 9999;
			
	SetGraph();
	SetGraphNode();
	
	//TravelIslands(0);

	RPerm(0);

	int ret = RPerm(0);	
	if (ret < 1000000000)
		cout << ret << endl;
	else
		cout << -1 << endl;


	/*
	int ret = 2000000000, tmp;
	for (int i = 0; i < islandsCnt; i++) {
		tmp = DFS(0, i, 0);
		ret = min(ret, tmp);
	}
	
	if (ret < 1000000000)
		cout << ret << endl;
	else
		cout << -1 << endl;
	*/
	return 0;
}
