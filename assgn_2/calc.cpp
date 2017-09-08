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

// class calcStack{
//   private:
//     char S[100];
//     double output;
//
//   public:
//     void push(char x);
//     char pop();
//
// };

int main()
{
   int n;
   tok T, T_p;
   T_p.TkType = -1;
   cin >> n;
   string Op;
   for (int i= 0; i< n; i++){
     cin >> Op;
     T = identifyToken(Op, T_p);
     T_p = T;
     cout << T.TkType<<" "<<T.TkVal<<endl;
   }
   return 0;
}
