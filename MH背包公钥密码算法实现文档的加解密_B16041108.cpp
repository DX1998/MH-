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
#define N 6 //˽Կ���� 

using namespace std;

//unsigned long m,w;//��ʼ�������m��w 
//int w1;//��ʼ��w����Ԫ 
//int B[N];//��ʼ��˽Կ���� 
//int Bmax;//��ʼ��˽Կ�������ֵ 
//int A[N];//��ʼ����Կ����
//int kk;//����ʱ����ĸ���
//string zu[10000000];//���ܷ�������Ϣ 
//int sum[10000000];//���ܺ����Ϣ 
	//���������Ӣ����ĸ���ж�Ӧת���ɶ����� 
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

int gcd(int a,int b)//�ж�a��b�Ƿ��� 
{
	int temp;
	while(temp=a%b)
	{
		a=b;
		b=temp;
	}
	if(abs(b)==1){
		return 1;//���� 
	}
	else{return -1;}//������ 
 } 

//�ж�һ�����Ƿ�Ϊ���� 
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
//�������m
int random_mw1(int B)
{
	//int B=62;//��Կ���벿�ֲ����� 
	unsigned long a,b,x;
	srand((unsigned)time(NULL));
	do{
		 a=rand();
		 b=rand();
	
		
	}while(a<=2*B||gcd(a,b)==-1);
	cout<<"�����m="<<a<<endl;
	x=a;
	return x;
}

//�������w
int random_mw2(int B)
{
	//int B=62;//��Կ���벿�ֲ����� 
	unsigned long a,b,x;
	srand((unsigned)time(NULL));
	do{
		 a=rand();
		 b=rand();
		
	}while(a<=2*B||gcd(a,b)==-1);
	cout<<"�����w="<<b<<endl;
	x=b;
	return x;
}

//��˷���Ԫ 
int mod_reverse(int m,int n )//n*w1=1(modm),��n����Ԫw1
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

//���ļ��� 
int encry(string ming,int *A,char *p)//�ֱ��������ַ����͹�Կ�����βκͷ��ص����� 
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
				zu[n] = Smi;//zu���鼴����Ӧ�Ķ�������Ϣ 
			
				n++;
			}
		} 
	} 
	
	int sum[n];
	memset(sum,0,sizeof(sum));//��ʼ������ 
	for(int i=0;i<n;i++){
	
		for(int j=0;j<zu[i].length();j++){
			if(zu[i][j] == '1'){
				sum[i] += A[j];
				
			}
		}
		
	} 
	return *p;
	
	
}

//���� 
int decrypt(int *V,int kk,int w1,int m,int *B) //�ֱ�Ϊ�������飬�����С��w1,m,˽Կ���� 
{

    int ans[kk];
	string flag[kk];
	string answer;//��ʼ������ 

	//��ʼ����******************
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
		flag[i]=flag1;//���ܵ�ÿ����������Ӧ�Ķ�������Ϣ 
		//cout<<flag1<<" ";
	}
	for(int i=0;i<kk-1;i++){
		string flag11;
		flag11 = flag[i].substr(0,6);//���һ�����Ķ����Ƶ�string���� 
		//cout<<flag11<<" ";
		for(int i=0;i<38;i++){
			if(mi[i]==flag11){
				answer +=mm[i];
			}
		}
	
	}
	//endTime2 = clock();	
	//cout<<"�ļ�����ʱ��Ϊ��"<<(double)(endTime2-startTime2)/CLOCKS_PER_SEC<<"s"<<endl; 


	cout<<"���ܺ������Ϊ:"<<answer<<endl;
	cout<<endl;
   
	return 0; 
}

//���ļ����뵽string��
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
	cout<<"             ��ӭ����MH������Կ�����㷨�ӽ���ϵͳ              "<<endl;
	cout<<"..............................................................."<<endl;
	cout<<"           .           .              .           .            "<<endl;
	cout<<"          . .         . .             .           .            "<<endl;
	cout<<"         .   .       .   .            .           .            "<<endl;
	cout<<"        .     .     .     .           .............            "<<endl;
	cout<<"       .       .   .       .          .           .            "<<endl;
	cout<<"      .         . .         .         .           .            "<<endl;
	cout<<"     .           .           .        .           .            "<<endl;
	cout<<"..............................................................."<<endl;
	cout<<"                                         @B16041108 ���       "<<endl;
	cout<<"***************************************************************"<<endl;
	cout<<endl;
}
int main()
{

    output();
    clock_t startTime1,endTime1,startTime2,endTime2;//��ʼ��ʱ����� 
    unsigned long m,w;//��ʼ�������m��w 
    int w1;//��ʼ��w����Ԫ 
   // int B[N];//��ʼ��˽Կ���� 
	int Bmax;//��ʼ��˽Կ�������ֵ 
	int A[N];//��ʼ����Կ����
	
	//����˽Կ**************** 
    ap:cout<<"������Ϊ�����������ҳ���Ϊ6��˽Կ����:";
	//���б�����ʼ�� 
    int B[N];//��ʼ��˽Կ���� 
	memset(B,0,sizeof(B));
	int sum=0,sum2=0;
	int flag0=0;
	
	//���� 
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
	cout<<"\n˽Կ���в�Ϊ����������!���������롣"<<endl; 
	goto ap;}
	else{
		cout<<"����ɹ���"<<endl;
	} 
	//�������******************** 
	
	Bmax=B[N-1];
	//cout<<Bmax<<endl;//���ԣ�˽Կ����� 
	//unsigned long a,b,x;
	srand((unsigned)time(NULL));
	do{
		 m=rand();
		 w=rand();
	
		
	}while(m<=2*Bmax||gcd(m,w)==-1||selfgcd(m)==-1||selfgcd(w)==-1);
	cout<<"�����m="<<m<<endl;
	cout<<"�����w="<<w<<endl;
	//m=random_mw1(Bmax);//�������m
	//w=random_mw2(Bmax);//�������w 
	w1=mod_reverse(m,w); 
    cout<<"w����ԪΪ:"<<mod_reverse(m,w)<<endl;
    
    //���ɹ�Կ******************* 
	for(int k=0;k<N;k++)//N=5 
	{
		A[k] = (B[k]*w)%m;
		
	}
	cout<<"���ɵĹ�ԿΪ:[";
	for(int i=0;i<N;i++){
		cout<<A[i]<<" ";
	}
	cout<<"]"<<endl;
	cout<<endl;
	//���ɹ�Կ����******************* 
	
	//���ļ� 
	char fn[50];
	ifstream fp;
	cout<<"����������ļ���:";
    cin>>fn;
    if(!fp)cout<<"�򿪴���"<<endl; 
    
    //���ļ���********************* 
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
				zu[n] = Smi;//zu���鼴����Ӧ�Ķ�������Ϣ 
			
				n++;
			}
		} 
	} 
	
	int SUM[n];//��ʼ���������� 
	memset(SUM,0,sizeof(SUM));//�����ʼ������ 
	startTime1 = clock(); //��ʱ��ʼ 
	for(int i=0;i<n;i++){
	
		for(int j=0;j<zu[i].length();j++){
			if(zu[i][j] == '1'){
				SUM[i] += A[j];
				
			}
		}
		//cout<<SUM[i]<<" "; 
		
	}
	endTime1 = clock(); //��ʱ���� 
	cout<<endl;
	cout<<"�ļ�����ʱ��Ϊ��"<<(double)(endTime1-startTime1)/CLOCKS_PER_SEC<<"s"<<endl; 
	//���������

	for(int i=0;i<n;i++){
		
		SUM [i] += 2*i;
	} 
	//���ļ��ܽ���**************************** 
	 
	fp.close(); 
    
    
	//���ı���******************************** 
	char fd[50];
	cout<<endl;
	cout<<"����������������ļ���:";
	cin>>fd;
    ofstream out(fd);
    if(out.is_open())
    {
    	for(int i=0;i<n;i++){
		    out<<SUM[i]<<" ";
	}
	}
	cout<<"����ɹ�"<<endl; 
	out.close();
	cout<<endl;
	//�رձ���������ļ�*********************** 
	
	//�������ļ�**************************** 
	vector<int>V;
	
	char fn2[50];
	ifstream fp2;
	cout<<"����������ļ���:";
    cin>>fn2;
    if(!fp2)cout<<"�򿪴���"<<endl; 
    fp2.open(fn2);
    int tmp;
	while(!fp2.eof()){
		fp2>>tmp;
		V.push_back(tmp);
	} 
	fp2.close();
	//�����ļ��ر�****************************** 
	
	 
	int kk=V.size();
	//decrypt(*V,kk,w1,m,*B); 
	cout<<"���Ĵ�С:"<<kk<<"������"<<endl;
	for(int i=0;i<kk;i++)
	{
		//cout<<V[i]<<" ";
		V[i] -= 2*i;
	}
	
	cout<<endl;
	
	int ans[kk];
	string flag[kk];
	string answer;//��ʼ������ 

	//��ʼ����******************
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
		flag[i]=flag1;//���ܵ�ÿ����������Ӧ�Ķ�������Ϣ 
		//cout<<flag1<<" ";
	}
	for(int i=0;i<kk-1;i++){
		string flag11;
		flag11 = flag[i].substr(0,6);//���һ�����Ķ����Ƶ�string���� 
		//cout<<flag11<<" ";
		for(int i=0;i<38;i++){
			if(mi[i]==flag11){
				answer +=mm[i];
			}
		}
	
	}
	endTime2 = clock();
	cout<<endl; 
	cout<<"�ļ�����ʱ��Ϊ��"<<(double)(endTime2-startTime2)/CLOCKS_PER_SEC<<"s"<<endl; 

	cout<<"���ܺ������Ϊ:"<<answer<<endl;
	cout<<endl;
   
	return 0; 
}
