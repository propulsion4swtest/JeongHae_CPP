#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int A,B,C;

//양수로 받아야한다.
int GCD(int a, int b){
	if(a < b)
		swap(a,b);

	int r = a % b;
	if(r == 0)
		return b;
	else
		return GCD(b, r);
}

//AX + BY = C 의 해를 구한다
bool Solve(int &x_sol, int &y_sol){
	//A와 B의 gcd와 C가 서로간의 배수가 아니면 해가 없다.
	bool is_x_minus = false, is_y_minus = false;
	int gcd = GCD(abs(A), abs(B));
	if(C % gcd != 0 && gcd % C != 0)
		return false;

	if(A < 0){
		is_x_minus = true;
		A = -1 * A;
	}

	if(B < 0){
		is_y_minus = true;
		B = -1 * B;
	}

	int div = GCD(abs(A), abs(B));
	div = GCD(div, abs(C));
	A /= div;
	B /= div;
	C /= div;
	int a[3],b[3], r[3], q;
	a[2] = 1,a[1] = 0, a[0];
	b[2] = 0,b[1]=1;
	r[2] = A;
	r[1] = B;
	r[0]=0;

	while(1){
		q = r[2] / r[1];
		a[0] = a[2] - (a[1] * q);
		b[0] = b[2] - (b[1] * q);
		r[0] = r[2] % r[1];
		if(r[0] == 1)
			break;
		a[2]=a[1];
		a[1]=a[0];
		b[2]=b[1];
		b[1]=b[0];
		r[2] = r[1];
		r[1] = r[0];
	}

	x_sol = a[0]*C;
	y_sol = b[0]*C;
		
	//음수였던 값의 해가 양수가 될때까지 mod를 더해준다.
	if(is_x_minus == true)
		x_sol = -1 * x_sol;
	if(is_y_minus == true)
		y_sol = -1 * y_sol;

	//이렇게 얻은 해의 정보는 특정 수치를 더하고 뺌으로써 나머지 해를 얻을 수 있다.
	//x_sol_set = x_sol + i * B
	//y_sol_set = y_sol + i * A

	return true;
}


int main(void){
	cin >> A>>B>>C;
	int x_sol, y_sol;
	bool ret = Solve(x_sol, y_sol);
	
	if(ret == false)
		cout << "there is no solution\n";
	else{
		cout << "X : " << x_sol << "\n";
		cout << "Y : " << y_sol << "\n";
	}

	return 0;
}
