constexpr int factorial(int n){
  return (n<=1) ? 1 : n*factorial(n-1);
}

int main(){
  constexpr int three = 3;
	
  constexpr int a = factorial(three);

  constexpr int b = factorial(a);
  
  // not constexpr
  const int c = factorial(3);
  
  // not constexpr
  int d = factorial(a);

  return d;
}
