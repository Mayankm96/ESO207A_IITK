#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdint>

using namespace std;

struct Tokenizer{
  int TkType;
  float TkVal;
};

typedef Tokenizer tok;

tok identifyToken(string Op, tok T_p){
  tok T;
  if (Op == "+"){
    T.TkType = 0;
    T.TkVal = 1;
  }
  else if (Op == "-"){
          T.TkType = 0;
          if (T_p.TkType == 0 || T_p.TkType == -1)
            T.TkVal = 8;
          else
            T.TkVal = 2;
       }
       else if (Op == "*"){
              T.TkType = 0;
              T.TkVal = 3;
            }
            else if (Op == "/"){
                    T.TkType = 0;
                    T.TkVal = 4;
                 }
                 else if (Op == "%"){
                        T.TkType = 0;
                        T.TkVal = 5;
                      }
                      else if (Op == "("){
                                T.TkType = 0;
                                T.TkVal = 6;
                            }
                            else if (Op == ")"){
                                    T.TkType = 0;
                                    T.TkVal = 7;
                                  }
                                  else {
                                    T.TkType = 1;
                                    T.TkVal = stoi(Op);
                                    if (T_p.TkType == 0 && T_p.TkVal == 8)
                                      T.TkVal = - T.TkVal;
                                  }
  return T;
}

float calcOperation(tok operator, tok T1, tok T2){
  float output;
  switch((int) operator.TkVal){
    case 1: output = T2.TkVal + T1.TkVal;
            break;
    case 2: output = T2.TkVal - T1.TkVal;
            break;
    case 3: output = T2.TkVal * T1.TkVal;
            break;
    case 4: output = T2.TkVal / T1.TkVal;
            break;
    case 5: output = ((int)T2.TkVal) % ((int)T1.TkVal);
            break;
  }
  return output;
}

class calcStack{
  private:
    tok * S;
    int TOP;

  public:
    calcStack(int n = 1){
      S = new tok[n];
      TOP = -1;
    }

    bool isEmpty(){
      if (TOP == -1)
        return 1;
      else
        return 0;
    }

    void push(tok x){
      TOP = TOP + 1;
      S[TOP] = x;
    }

    tok pop(){
      if(isEmpty()){
        cout << "Malformed expression";
        exit(1);
      }
      TOP = TOP - 1;
      return S[TOP + 1];
    }

    // Display all contents of Stack
    void displayStack(){
        cout<<"---------"<<endl;
        int i = TOP;
        if (i == -1){
          cout<<"Empty"<<endl;
          return;
        }
        tok T;
        while (i != -1){
          T = S[i];
          cout << T.TkType << " " << T.TkVal << endl;
          i = i - 1;
        }
    }

     // Used only for operator stack
     int valOperatorTop(){
       if (TOP == -1)
          return -1;
       tok T = S[TOP];
       return T.TkVal;
     }
};

//Priority array containg the priorities of operators numbered 1-8
int PRIORITY[] = {1, 1, 2, 3, 3, 0, 0, 5};

int checkPriority(float OpCode1, float OpCode2){
  int Op1 = (int) OpCode1 - 1;
  int Op2 = (int) OpCode2 - 1;
  if(PRIORITY[Op1] == PRIORITY[Op2])
    return 0 ;
  else if(PRIORITY[Op1] < PRIORITY[Op2])
          return 1;
       else
          return -1;
}

//Check if expression is valid or not for successive tokens T1 and T2
bool isInvalidExpression(tok T1, tok T2){
  if (T1.TkType == 1 && T2.TkType == 1){
      return 1;
  }
  else if (T1.TkType == 0 && T2.TkType == 0 && T2.TkVal != 6){
      return 1;
  }
  else if (T1.TkType == 1 && T2.TkType == 0 && T2.TkVal == 6){
      return 1;
  }
  else return 0;
}

int main() {
   // Number of inputs into calculator
   int n;
   cin >> n;

   //stack for Operands and Operators
   calcStack Operators(n), Operands(n);

   tok T, T_p, RES;

   T.TkType = -1;
   T.TkVal = 0;

   RES.TkType = 1;
   string Op;
   float result;

   for (int i= 0; i< n; i++){
     cin >> Op;

     T_p = T;
     T = identifyToken(Op, T_p);

     if (isInvalidExpression(T_p, T)){
       cout<<"Malformed expression";
       return -1;
     }

      if (T.TkType == 0){
        if (T.TkVal == 6)
                Operators.push(T);
        else if (T.TkVal == 7){
                while(Operators.valOperatorTop() != 6){
                  tok T1 = Operands.pop();
                  tok T2 = Operands.pop();
                  tok Opd = Operators.pop();
                  RES.TkVal = calcOperation(Opd, T1, T2);
                  Operands.push(RES);
                }
                tok Opd = Operators.pop();
            }
            else if (checkPriority(Operators.valOperatorTop(), T.TkVal) == -1){
                    tok T1 = Operands.pop();
                    tok T2 = Operands.pop();
                    tok Opd = Operators.pop();
                    RES.TkVal = calcOperation(Opd, T1, T2);
                    Operands.push(RES);
                    Operators.push(T);
                  }
                  else if (T.TkVal != 8)
                      Operators.push(T);
      }
      else
        Operands.push(T);

      //Operaands.displayStack();
      //Operators.displayStack();
   }

   while(! Operators.isEmpty()){
     tok T1 = Operands.pop();
     tok T2 = Operands.pop();
     tok Opd = Operators.pop();
     RES.TkVal = calcOperation(Opd, T1, T2);
     Operands.push(RES);
   }

   RES = Operands.pop();
   cout << RES.TkVal;
   return 0;
}
