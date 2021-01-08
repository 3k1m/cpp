constexpr int fun(int x) { return x*2; }

int main(){
	constexpr int a = 7;
	constexpr int b = a + fun(a);	
	
	return b;
}
