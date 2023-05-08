#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, const char * argv[]) {
    ifstream ifs;
    ofstream ofs;
    char c[256]={0};
    ifs.open(argv[1]);
    if(!ifs.is_open()){
        cout<<"failed to open file"<<endl;
        return 0;
    }
    else{
        ifs.read(c,sizeof(c));
        cout<<c;
        ifs.close();
    }
    int i=0;
    int input=0,output=0;
    char in[100],out[100];
    char table[9999][4];
    while(c[i]=='.'){
        if(c[i]=='.'){
            if(c[i+1]=='i'){
                if(c[i+2]==' '){
                    int j=0;
                    while(c[i+3+j]>=48&&c[i+3+j]<=57){
                        j++;
                    }
                    j--;
                    for(int k=0;k<=j;k++){
                        input+=((int)c[i+3+k]-48)*pow(10,j-k);
                    }
                    int k=0;
                    while((int)c[i+j+k+3]!=10){
                        k++;
                    }
                    i=i+j+k+4;
                }
                else if(c[i+2]=='l'&&c[i+3]=='b'&&c[i+4]==' '){
                    for(int j=0;j<input;j++){
                        in[j]=c[j*2+i+5];
                    }
                    int k=0;
                    while((int)c[i+input*2+k+5]!=10){
                        k++;
                    }
                    i=input*2+i+k+6;
                }
            }
            else if(c[i+1]=='o'){
                if(c[i+2]==' '){
                    int j=0;
                    while(c[i+3+j]>=48&&c[i+3+j]<=57){
                        j++;
                    }
                    j--;
                    for(int k=0;k<=j;k++){
                        output+=((int)c[i+3+k]-48)*pow(10,j-k);
                    }
                    int k=0;
                    while((int)c[i+j+k+3]!=10){
                        k++;
                    }
                    i=i+j+k+4;
                }
                else if(c[i+2]=='b'&&c[i+3]==' '){
                    for(int j=0;j<output;j++){
                        out[j]=c[j*2+i+4];
                    }
                    int k=0;
                    while((int)c[i+k+3]!=10){
                        k++;
                    }
                    i=output*2+i+2+k;
                }
            }
            else if(c[i+1]=='p'){
                int command=0;
                int j=0;
                while(c[i+3+j]>=48&&c[i+3+j]<=57){
                    j++;
                }
                j--;
                for(int k=0;k<=j;k++){
                    command+=((int)c[i+3+k]-48)*pow(10,j-k);
                }
                int k=0;
                while((int)c[i+j+k+3]!=10){
                    k++;
                }
                i=i+j+k+4;
                for(int j=0;j<=pow(2,input);j++){
                    table[j][0]=j+48;
                }
                table[0][1]='0';
                table[0][2]='-';
                table[0][3]='-';
                table[(int)pow(2,input)][1]='1';
                table[(int)pow(2,input)][2]='-';
                table[(int)pow(2,input)][3]='-';
                for(int j=0;j<input;j++){
                    for(int k=0;k<pow(2,j);k++){
                        table[(int)pow(2,j)+k][1]=in[j];
                    }
                }
                for(int j=1;j<pow(2,input-1);j++){
                    table[j][2]=((int)table[j][0]-48)*2+48;
                    table[j][3]=((int)table[j][0]-48)*2+49;
                }
                for(int j=pow(2,input-1);j<pow(2,input);j++){
                    table[j][2]='0';
                    table[j][3]='0';
                }
                for(int n=0;n<command;n++){
                    string s;
                    for(int j=0;j<input;j++){
                        s+=c[i+n*(input+3)+j];
                    }
                    int to[100]={0};
                    to[0]=1;
                    int k=0;
                    for(int j=0;j<input-1;j++){
                        k=0;
                        if(s[j]=='0'){
                            while(to[k]!=0){
                                k++;
                            }
                            for(int l=0;l<k;l++){
                                to[l]=(int)table[to[l]][2]-48;
                            }
                        }
                        else if(s[j]=='1'){
                            while(to[k]!=0){
                                k++;
                            }
                            for(int l=0;l<k;l++){
                                to[l]=(int)table[to[l]][3]-48;
                            }
                        }
                        else if(s[j]=='-'){
                            while(to[k]!=0){
                                k++;
                            }
                            int m=k;
                            for(int l=0;l<k;l++){
                                to[m]=(int)table[to[l]][3]-48;
                                to[l]=(int)table[to[l]][2]-48;
                                m++;
                            }
                        }
                    }
                    k=0;
                    if(s[input-1]=='0'){
                        while(to[k]!=0){
                            k++;
                        }
                        for(int l=0;l<k;l++){
                            table[to[l]][2]=pow(2,input)+48;
                        }
                    }
                    else if(s[input-1]=='1'){
                        while(to[k]!=0){
                            k++;
                        }
                        for(int l=0;l<k;l++){
                            table[to[l]][3]=pow(2,input)+48;
                        }
                    }
                    else if(s[input-1]=='-'){
                        while(to[k]!=0){
                            k++;
                        }
                        for(int l=0;l<k;l++){
                            table[to[l]][2]=pow(2,input)+48;
                            table[to[l]][3]=pow(2,input)+48;
                        }
                    }
                }
                int TF0=0,TF1=0;
                int column=pow(2,input);
                for(int j=1;j<column;j++){
                    if(table[j][2]==table[j][3]){
                        TF0=1;
                    }
                    else{
                        for(int k=j+1;k<column;k++){
                            if(table[j][1]==table[k][1]&&table[j][2]==table[k][2]&&table[j][3]==table[k][3]){
                                TF1=1;
                            }
                        }
                    }
                }
                while(TF0==1||TF1==1){
                    if(TF0==1){
                        for(int j=1;j<column;j++){
                            if(table[j][2]==table[j][3]){
                                for(int k=1;k<column;k++){
                                    if(table[k][2]==table[j][0]){
                                        table[k][2]=table[j][2];
                                    }
                                    if(table[k][3]==table[j][0]){
                                        table[k][3]=table[j][3];
                                    }
                                }
                                for(int k=j;k<column;k++){
                                    for(int l=0;l<4;l++){
                                        table[k][l]=table[k+1][l];
                                    }
                                }
                                j--;
                                column--;
                                TF0=0;
                                TF1=0;
                                goto here;
                            }
                        }
                    }
                    else if(TF1==1){
                        for(int j=1;j<column-1;j++){
                            for(int k=j+1;k<column;k++){
                                if(table[j][1]==table[k][1]&&table[j][2]==table[k][2]&&table[j][3]==table[k][3]){
                                    for(int l=1;l<column;l++){
                                        if(table[l][2]==table[k][0]){
                                            table[l][2]=table[j][0];
                                        }
                                        if(table[l][3]==table[k][0]){
                                            table[l][3]=table[j][0];
                                        }
                                    }
                                    for(int m=k;m<=column;m++){
                                        for(int n=0;n<4;n++){
                                            table[m][n]=table[m+1][n];
                                        }
                                    }
                                    j--;
                                    k--;
                                    column--;
                                    TF1=0;
                                    TF0=0;
                                    goto here;
                                }
                            }
                        }
                    }
                    here:;
                    for(int j=1;j<column;j++){
                        if(table[j][2]==table[j][3]){
                            TF0=1;
                        }
                        else{
                            for(int k=j+1;k<column;k++){
                                if(table[j][1]==table[k][1]&&table[j][2]==table[k][2]&&table[j][3]==table[k][3]){
                                    TF1=1;
                                }
                            }
                        }
                    }
                }
                for(int j=0;j<=column;j++){
                    for(int k=0;k<4;k++){
                        cout<<table[j][k]<<" ";
                    }
                    cout<<endl;
                }
            }
            else if(c[i+1]=='e'){
            }
        }
    }
    ofs.open(argv[2]);
    if(!ofs.is_open()){
        cout<<"Failed to open file"<<endl;
    }
    else{
        ofs<<"digraph ROBDD {"<<endl;
        int i=1;
        int j=0;
        while(table[i][1]!='1'){
            j=0;
            ofs<<"   {rank=same";
            while(table[i+j+1][1]==table[i+j][1]){
                j++;
            }
            for(int k=0;k<=j;k++){
                ofs<<" "<<(int)table[i+k][0]-48;
            }
            ofs<<"}"<<endl;
            i=i+j+1;
        }
        ofs<<endl;
        ofs<<"   0 [label=\"0\", shape=box];"<<endl;
        i=1;
        while(table[i][1]!='1'){
            ofs<<"   "<<(int)table[i][0]-48<<" [label=\""<<table[i][1]<<"\"]"<<endl;
            i++;
        }
        ofs<<"   "<<(int)table[i][0]-48<<" [label=\"1\", shape=box];"<<endl<<endl;
        i=1;
        while(table[i][1]!='1'){
            ofs<<"   "<<(int)table[i][0]-48<<" -> "<<(int)table[i][2]-48<<" [label=\"0\", style=dotted]"<<endl;
            ofs<<"   "<<(int)table[i][0]-48<<" -> "<<(int)table[i][3]-48<<" [label=\"1\", style=solid]"<<endl;
            i++;
        }
        ofs<<"}";
    }
    return 0;
}
