#include<iostream>
#include<string.h>
#include<stdio.h>
#include<ctime>
#include<stdlib.h>
#include<fstream> 
#include<sstream>
#include<vector>
#include<algorithm>
#include<math.h> 
#define N 6 //私钥长度 

using namespace std;

//unsigned long m,w;//初始化随机数m和w 
//int w1;//初始化w的逆元 
//int B[N];//初始化私钥数组 
//int Bmax;//初始化私钥数组最大值 
//int A[N];//初始化公钥数组
//int kk;//加密时分组的个数
//string zu[10000000];//加密分组后的信息 
//int sum[10000000];//加密后的信息 
	//打表将数字与英文字母进行对应转换成二进制 
    string mi[38] = {"000000","000001","000010","000011","000100",
			 	     "000101","000110","000111","001000","001001",
			   	     "001010","001011","001100","001101","001110",
				     "001111","010000","010001","010010","010011",
				     "010100","010101","010110","010111","011000",
				     "011001","011010","011011","011100","011101",
				     "011110","011111","100000","100001","100010",
				     "100011","100100","100101"};

   char mm[38] = {' ','a','b','c','d',
			      'e','f','g','h','i',
			      'j','k','l','m','n',
			      'o','p','q','r','s',
			      't','u','v','w','x',
			      'y','z','0','1','2',
			      '3','4','5','6','7',
			      '8','9','\n'};

int gcd(int a,int b)//判断a，b是否互素 
{
	int temp;
	while(temp=a%b)
	{
		a=b;
		b=temp;
	}
	if(abs(b)==1){
		return 1;//互素 
	}
	else{return -1;}//不互素 
 } 

//判断一个数是否为素数 
int selfgcd(unsigned long a)
{
	int flag = 1;
	for(int i=2;i<a;i++){
		if(a%i == 0){
			flag = -1;
			break;
		}
	} 
	return flag;
}
//得随机数m
int random_mw1(int B)
{
	//int B=62;//密钥输入部分测试数 
	unsigned long a,b,x;
	srand((unsigned)time(NULL));
	do{
		 a=rand();
		 b=rand();
	
		
	}while(a<=2*B||gcd(a,b)==-1);
	cout<<"随机数m="<<a<<endl;
	x=a;
	return x;
}

//得随机数w
int random_mw2(int B)
{
	//int B=62;//密钥输入部分测试数 
	unsigned long a,b,x;
	srand((unsigned)time(NULL));
	do{
		 a=rand();
		 b=rand();
		
	}while(a<=2*B||gcd(a,b)==-1);
	cout<<"随机数w="<<b<<endl;
	x=b;
	return x;
}

//求乘法逆元 
int mod_reverse(int m,int n )//n*w1=1(modm),求n的逆元w1
{
	int a, q, b[100], my;
	q = 0;
	a = m%n;
	my = m;
	while(a!=0){
		a = m%n;
		b[q] = m/n;
		q++;
		m = n;
		n = a;
	}
	int bb[100], j=2, bbb;
	bb[0]=1;
	bb[1] = b[q-2];
	int nn;
	nn=q-2;
	for(int i=nn; i>0; i--){	
		bb[j] = b[i-1]*bb[j-1] + bb[j-2];
		bbb = bb[j];
		j++;
	}
 	if((q-1)%2==0) return(bbb);
 	else return (my-bbb);

 } 

//明文加密 
int encry(string ming,int *A,char *p)//分别是明文字符串和公钥数组形参和返回的数组 
{

	int L=ming.length();
	//cout<<L<<endl;
	string zu[L];
	int n=0;
    string Smi;
	for(int k=0;k<L;k++){
	    for(int j=0;j<38;j++){
			if(mm[j] == ming[k]){
				Smi = mi[j];
				zu[n] = Smi;//zu数组即所对应的二进制信息 
			
				n++;
			}
		} 
	} 
	
	int sum[n];
	memset(sum,0,sizeof(sum));//初始化数组 
	for(int i=0;i<n;i++){
	
		for(int j=0;j<zu[i].length();j++){
			if(zu[i][j] == '1'){
				sum[i] += A[j];
				
			}
		}
		
	} 
	return *p;
	
	
}

//解密 
int decrypt(int *V,int kk,int w1,int m,int *B) //分别为密文数组，数组大小，w1,m,私钥数组 
{

    int ans[kk];
	string flag[kk];
	string answer;//初始化明文 

	//开始解密******************
	//startTime2 = clock();
	for(int i=0;i<kk;i++){
		ans[i] = V[i]*w1%m;
		//cout<<ans[i]<<" ";
		string flag1;
		for(int j=5;j>=0;j--){
			if(ans[i]>=B[j]){
				flag1 += "1";
				ans[i] = ans[i] - B[j];
			}
			else flag1 += "0";
		}
		reverse(flag1.begin(),flag1.end());
		flag[i]=flag1;//解密得每个密文所对应的二进制信息 
		//cout<<flag1<<" ";
	}
	for(int i=0;i<kk-1;i++){
		string flag11;
		flag11 = flag[i].substr(0,6);//获得一个密文二进制的string类型 
		//cout<<flag11<<" ";
		for(int i=0;i<38;i++){
			if(mi[i]==flag11){
				answer +=mm[i];
			}
		}
	
	}
	//endTime2 = clock();	
	//cout<<"文件解密时间为："<<(double)(endTime2-startTime2)/CLOCKS_PER_SEC<<"s"<<endl; 


	cout<<"解密后的明文为:"<<answer<<endl;
	cout<<endl;
   
	return 0; 
}

//从文件读入到string里
string readfile(char *filename)
{
	ifstream ifile(filename);
	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch)){
		buf.put(ch);
	}
	return buf.str();
 } 

void output()
{   
    cout<<"***************************************************************"<<endl;
	cout<<"             欢迎来到MH背包公钥密码算法加解密系统              "<<endl;
	cout<<"..............................................................."<<endl;
	cout<<"           .           .              .           .            "<<endl;
	cout<<"          . .         . .             .           .            "<<endl;
	cout<<"         .   .       .   .            .           .            "<<endl;
	cout<<"        .     .     .     .           .............            "<<endl;
	cout<<"       .       .   .       .          .           .            "<<endl;
	cout<<"      .         . .         .         .           .            "<<endl;
	cout<<"     .           .           .        .           .            "<<endl;
	cout<<"..............................................................."<<endl;
	cout<<"                                         @B16041108 丁昕       "<<endl;
	cout<<"***************************************************************"<<endl;
	cout<<endl;
}
int main()
{

    output();
    clock_t startTime1,endTime1,startTime2,endTime2;//初始化时间变量 
    unsigned long m,w;//初始化随机数m和w 
    int w1;//初始化w的逆元 
   // int B[N];//初始化私钥数组 
	int Bmax;//初始化私钥数组最大值 
	int A[N];//初始化公钥数组
	
	//输入私钥**************** 
    ap:cout<<"请输入为超递增序列且长度为6的私钥序列:";
	//进行变量初始化 
    int B[N];//初始化私钥数组 
	memset(B,0,sizeof(B));
	int sum=0,sum2=0;
	int flag0=0;
	
	//输入 
    for(int i=0;i<N;i++)
    {
    	cin>>B[i];
    	sum++;
    	
	}
	
//	if(length>5){flag==-1;
//	}

	for(int n=1;n<sum;n++)
	{
		sum2+=B[n-1];
		if(B[n]<sum2){
			flag0=-1;	 	
		}
		
	}
	if(flag0==-1){
	cout<<"\n私钥序列不为超递增序列!请重新输入。"<<endl; 
	goto ap;}
	else{
		cout<<"输入成功！"<<endl;
	} 
	//输入结束******************** 
	
	Bmax=B[N-1];
	//cout<<Bmax<<endl;//测试：私钥最大数 
	//unsigned long a,b,x;
	srand((unsigned)time(NULL));
	do{
		 m=rand();
		 w=rand();
	
		
	}while(m<=2*Bmax||gcd(m,w)==-1||selfgcd(m)==-1||selfgcd(w)==-1);
	cout<<"随机数m="<<m<<endl;
	cout<<"随机数w="<<w<<endl;
	//m=random_mw1(Bmax);//得随机数m
	//w=random_mw2(Bmax);//得随机数w 
	w1=mod_reverse(m,w); 
    cout<<"w的逆元为:"<<mod_reverse(m,w)<<endl;
    
    //生成公钥******************* 
	for(int k=0;k<N;k++)//N=5 
	{
		A[k] = (B[k]*w)%m;
		
	}
	cout<<"生成的公钥为:[";
	for(int i=0;i<N;i++){
		cout<<A[i]<<" ";
	}
	cout<<"]"<<endl;
	cout<<endl;
	//生成公钥结束******************* 
	
	//打开文件 
	char fn[50];
	ifstream fp;
	cout<<"输入待加密文件名:";
    cin>>fn;
    if(!fp)cout<<"打开错误！"<<endl; 
    
    //明文加密********************* 
    string ming;
    ming=readfile(fn);
	int L=ming.length();
	string zu[L];
	int n=0;
    string Smi;
	for(int k=0;k<L;k++){
	    for(int j=0;j<38;j++){
			if(mm[j] == ming[k]){
				Smi = mi[j];
				zu[n] = Smi;//zu数组即所对应的二进制信息 
			
				n++;
			}
		} 
	} 
	
	int SUM[n];//初始化密文数组 
	memset(SUM,0,sizeof(SUM));//置零初始化数组 
	startTime1 = clock(); //计时开始 
	for(int i=0;i<n;i++){
	
		for(int j=0;j<zu[i].length();j++){
			if(zu[i][j] == '1'){
				SUM[i] += A[j];
				
			}
		}
		//cout<<SUM[i]<<" "; 
		
	}
	endTime1 = clock(); //计时结束 
	cout<<endl;
	cout<<"文件加密时间为："<<(double)(endTime1-startTime1)/CLOCKS_PER_SEC<<"s"<<endl; 
	//随机数密文

	for(int i=0;i<n;i++){
		
		SUM [i] += 2*i;
	} 
	//明文加密结束**************************** 
	 
	fp.close(); 
    
    
	//密文保存******************************** 
	char fd[50];
	cout<<endl;
	cout<<"输入待创建的密文文件名:";
	cin>>fd;
    ofstream out(fd);
    if(out.is_open())
    {
    	for(int i=0;i<n;i++){
		    out<<SUM[i]<<" ";
	}
	}
	cout<<"保存成功"<<endl; 
	out.close();
	cout<<endl;
	//关闭保存的密文文件*********************** 
	
	//打开密文文件**************************** 
	vector<int>V;
	
	char fn2[50];
	ifstream fp2;
	cout<<"输入待解密文件名:";
    cin>>fn2;
    if(!fp2)cout<<"打开错误！"<<endl; 
    fp2.open(fn2);
    int tmp;
	while(!fp2.eof()){
		fp2>>tmp;
		V.push_back(tmp);
	} 
	fp2.close();
	//密文文件关闭****************************** 
	
	 
	int kk=V.size();
	//decrypt(*V,kk,w1,m,*B); 
	cout<<"密文大小:"<<kk<<"个密文"<<endl;
	for(int i=0;i<kk;i++)
	{
		//cout<<V[i]<<" ";
		V[i] -= 2*i;
	}
	
	cout<<endl;
	
	int ans[kk];
	string flag[kk];
	string answer;//初始化明文 

	//开始解密******************
	startTime2 = clock();
	for(int i=0;i<kk;i++){
		ans[i] = V[i]*w1%m;
		//cout<<ans[i]<<" ";
		string flag1;
		for(int j=5;j>=0;j--){
			if(ans[i]>=B[j]){
				flag1 += "1";
				ans[i] = ans[i] - B[j];
			}
			else flag1 += "0";
		}
		reverse(flag1.begin(),flag1.end());
		flag[i]=flag1;//解密得每个密文所对应的二进制信息 
		//cout<<flag1<<" ";
	}
	for(int i=0;i<kk-1;i++){
		string flag11;
		flag11 = flag[i].substr(0,6);//获得一个密文二进制的string类型 
		//cout<<flag11<<" ";
		for(int i=0;i<38;i++){
			if(mi[i]==flag11){
				answer +=mm[i];
			}
		}
	
	}
	endTime2 = clock();
	cout<<endl; 
	cout<<"文件解密时间为："<<(double)(endTime2-startTime2)/CLOCKS_PER_SEC<<"s"<<endl; 

	cout<<"解密后的明文为:"<<answer<<endl;
	cout<<endl;
   
	return 0; 
}
