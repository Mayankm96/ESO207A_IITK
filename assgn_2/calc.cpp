#include <iostream>
#include <stdio.h>
#include <string>
#include <ctype.h>
#include <cstdint>

using namespace std;

struct Tokenizer{
  int TkType;
  int TkVal;
};

// fnv1 hashing code from
// https://github.com/elbeno/constexpr/blob/master/src/include/cx_fnv1.h
namespace fnv {
  constexpr uint64_t _(uint64_t h, const char* s) {
    return (*s == 0) ? h :
      _((h * 1099511628211ull) ^ static_cast<uint64_t>(*s), s+1);
  }
}

constexpr uint64_t _(const char* s) {
  return fnv::_(14695981039346656037ull, s);
}

uint64_t _(const std::string& s) {
  return fnv::_(14695981039346656037ull, s.data());
}

typedef Tokenizer tok;

tok identifyToken(string Op, tok T_p){
  tok T;
  switch(_(Op)){
    case _("+"): T.TkType = 0;
              T.TkVal = 1;
              break;
    case _("-"):
              T.TkType = 0;
              if (T_p.TkType == 0 || T_p.TkType == -1)
                T.TkVal = 8;
              else
                T.TkVal = 2;
              break;
    case _("*"): T.TkType = 0;
              T.TkVal = 3;
              break;
    case _("/"): T.TkType = 0;
              T.TkVal = 4;
              break;
    case _("%"): T.TkType = 0;
              T.TkVal = 5;
              break;
    case _("("): T.TkType = 0;
              T.TkVal = 6;
              break;
    case _(")"): T.TkType = 0;
              T.TkVal = 7;
              break;
    default: T.TkType = 1;
             T.TkVal = stoi(Op);
  }
  return T;
}

float calcOperation(tok operand, tok T1, tok T2){
  float output;
  switch(operand.TkVal){
    case 1: output = T1.TkVal + T2.TkVal;
            break;
    case 2: output = T1.TkVal - T2.TkVal;
            break;
    case 3: output = T1.TkVal * T2.TkVal;
            break;
    case 4: output = T2.TkVal / T1.TkVal;
            break;
    case 5: output = T2.TkVal % T1.TkVal;
            break;
  }
  return output;
}

class calcStack{
  private:
    tok * S;
    int top;
    double output;

  public:
    calcStack(int n = 1){
      S = new tok[n];
      top = -1;
    }
    void push(tok x){
      S[top + 1] = x;
      top++;
    }
    tok pop(){
      if(top == -1){
        cout << "Stack is empty!";
        exit (1);
      }
      top--;
      return S[top + 1];
    }
};

int main() {
   // Number of inputs into calculator
   int n;
   cin >> n;

   //stack for operators and operands
   calcStack Operands(n), Operators(n);

   tok T, T_p;
   T_p.TkType = -1;
   string Op;
   float result = 0;

   for (int i= 0; i< n; i++){
     cin >> Op;
     T = identifyToken(Op, T_p);
     T_p = T;

    if (T.TkType == 0)
      Operands.push(T);
    else
      Operators.push(T);
   }
   tok T1 = Operators.pop();
   tok T2 = Operators.pop();
   result = calcOperation(Operands.pop(), T1, T2);
   cout<<result;
   return 0;
}
