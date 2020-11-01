//
//  main.cpp
//  HammingCode
//
//  Created by Ivanna Vasilkova on 01.11.2020.
//  Copyright © 2020 Ivanna Vasilkova. All rights reserved.
//
#include <sstream>


#include <iostream>
#define Map map<string, size_t>
#define print(a) cout << a << endl;
#define print2(a, b) cout << a << ' ' << b << endl;
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <tuple>
void Decode (std::vector <bool> withZeroSeq);
std::tuple<std::vector<bool>, int> isPowOfTwo(std::vector<bool> initialSeq) {
    int count = 0;
    int pow = 1;
    for (int j = 0; j < initialSeq.size(); j++)
        if (j == pow){ count++; initialSeq.insert(initialSeq.begin() + (j-1), 0); pow*=2;}
    return  std::make_tuple(initialSeq,count);
}

void insertCheckBeat(std::vector<bool> &withZeroSeq, std::vector<bool> &sumCont) {
    std::vector<bool>::iterator it = sumCont.begin();
    for (int i = 1; i < withZeroSeq.size(); i*=2)
        withZeroSeq[i-1] = *it++;
    
}
void toInvert(std::vector <bool> &withZeroSeq, int index){
    if(withZeroSeq[index] == 1) withZeroSeq[index] = 0;
    else withZeroSeq[index] = 1;
}


void Encode (std::vector <bool> initialSeq){
    std::vector <bool> withZeroSeq;
    std::vector <bool> sumCont;
    
    int countByte = 0;
    int sumControl = 0;
    std::tie(withZeroSeq, countByte) =  isPowOfTwo(initialSeq);
    for (int i = 1; i <= withZeroSeq.size(); i++)
        if (withZeroSeq[i-1] == 1)
            sumControl ^= i;
    
    for (int i = 0; i < countByte; i++)
        sumCont.push_back((sumControl >> i) & 1);
    
    insertCheckBeat(withZeroSeq, sumCont);
    for (auto i : withZeroSeq)
        std::cout<<i;
    
}
void menu(std::vector <bool> withZeroSeq){
    int index = 0;
    std::cout<<"Enter index"<< std::endl;
    std::cin >> index;
    toInvert(withZeroSeq, index);
    Decode(withZeroSeq);
}

void Decode (std::vector <bool> withZeroSeq){
    std::vector <bool> finalSeq;
    int sumControl = 0;
    for (int i = 1; i <= withZeroSeq.size(); i++)
        if (withZeroSeq[i - 1] == 1)
            sumControl ^= i;
    
    if (sumControl == 0){
        int answer = 0;
        std::cout << "The sequence has no errors" << std::endl;
        std::cout << " Do you want to mess up the sequence? \n Enter 1 if yes, 0 is no" << std::endl;
        std::cin >> answer;
        if (answer){
            menu(withZeroSeq);
        }
    }
    else {
        for (auto i : withZeroSeq)
            std::cout << i;
        std::cout << "\n Mistake in:  "<<sumControl - 1<< std::endl;
        withZeroSeq[sumControl - 1] = !withZeroSeq[sumControl - 1];
        
        int pow = 1;
        for (int j = 1; j <= withZeroSeq.size(); j++){
            if (j == pow) pow*=2;
            else  finalSeq.push_back(withZeroSeq[j-1]);
        }
        
        
    }
    for (auto i : finalSeq)
        std::cout << i;
}




int main(int argc, const char * argv[]) {
    //    std::vector<bool> initialSeq = {0,0,1,0,0,0};
    //    std::vector<bool> initialSeq = {0,1,0,1,0,1,0,0,0,0};
    
    
    std::string initialSeq(argv[1]);
    std::cout <<"initialSeq     "<<initialSeq<<std::endl;
    
    
    std::vector<char> initial(initialSeq.begin(),initialSeq.end());
    std::vector<bool> boolka;
    for (auto i : initial)
        boolka.push_back(i-'0');
    
    for (auto i : boolka)
        std::cout << i<<" ";
    
    
    
    if((std::string(argv[2]) == "-e") || (std::string(argv[2]) == "-E")){
        std::cout <<"e or d"<< std::string(argv[2])<<std::endl;
        Encode(boolka);
        return 0;
    }
    if((std::string(argv[2]) == "-d") || (std::string(argv[2]) == "-D")){
        std::cout <<"e or d"<< std::string(argv[2])<<std::endl;
        Decode(boolka);
        return 0;
    }
    
    
    
}

