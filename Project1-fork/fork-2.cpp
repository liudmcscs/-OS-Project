#include  <iostream>
#include  <fstream>
#include  <cstdlib>
#include  <vector>
#include  <stdio.h>
#include  <sys/types.h>
#include  <unistd.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <sys/wait.h>
#include  <sys/time.h>
using namespace std;
int in = 0;
int out = 0;
int matsize;
struct timeval tv_begin, tv_end;
typedef struct items
{
	int **mat;
	int determinant[4];
} item ;
	int process_1(int processnum);
	int process_2(int processnum);
	int process_3(int processnum);
	int process_4(int processnum);
	int sum=0;
	int **mat;
	int det_part[4];
	int D1,D2,D3,D4;
int shmid,shmid2,shmid3,shmid4;
item *pro1,*pro2,*pro3,*pro4;
int main()
{
    ifstream fin;
    fin.open("input.txt");
    fin>>matsize;
    int sec,usec;
	int num;
    mat=new int *[matsize];
    for(int size=0;size<=matsize;size++)
    {
        mat[size]=new int[matsize];
    }   
    for(int rol=0;rol<matsize;rol++)
    {
        for(int col=0;col<matsize;col++)
        {
            if(col<matsize-1)
            {
            fin>>num;
            mat[rol][col]=num;
            }
            else if(col==(matsize-1))
            {
            fin>>num;
            mat[rol][col]=num;
            }
        }
    }

 
//  1
    gettimeofday(&tv_begin, NULL);        
    sum = process_1(1);
    gettimeofday(&tv_end, NULL);
    sec = tv_end.tv_sec - tv_begin.tv_sec;
    usec = tv_end.tv_usec - tv_begin.tv_usec;
    cout<<"Calculating determinant using 1 process"<<endl<<"Elapsed time: "<<sec + (usec/1000000.0)<<" sec,  determinant : "<<(int)sum<<endl;
 
//  2
    gettimeofday(&tv_begin, NULL);        
    sum = process_2(2);
    gettimeofday(&tv_end, NULL);
    sec = tv_end.tv_sec - tv_begin.tv_sec;
    usec = tv_end.tv_usec - tv_begin.tv_usec;
    cout<<"Calculating determinant using 2 process"<<endl<<"Elapsed time: "<<sec + (usec/1000000.0)<<" sec,  determinant : "<<(int)sum<<endl;
 
//  3
    gettimeofday(&tv_begin, NULL);        
    sum = process_3(3);
    gettimeofday(&tv_end, NULL);
    sec = tv_end.tv_sec - tv_begin.tv_sec;
    usec = tv_end.tv_usec - tv_begin.tv_usec;
    cout<<"Calculating determinant using 3 process"<<endl<<"Elapsed time: "<<sec + (usec/1000000.0)<<" sec,  determinant : "<<(int)sum<<endl;
 
//  4
    gettimeofday(&tv_begin, NULL);        
    sum = process_4(4);
    gettimeofday(&tv_end, NULL);
    sec = tv_end.tv_sec - tv_begin.tv_sec;
    usec = tv_end.tv_usec - tv_begin.tv_usec;
    cout<<"Calculating determinant using 4 process"<<endl<<"Elapsed time: "<<sec + (usec/1000000.0)<<" sec,  determinant : "<<(int)sum<<endl;
    exit(0); 
    fin.close();
    return 0;
}
void getcof_10(int mat[10][10], int temp[10][10], int p, int q, int n,int processnum)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col]; 
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
int determinant_10(int mat[10][10], int n,int processnum)
{
    int det_part_10 = 0;
    if (n == 1)
    return mat[0][0];
    int temp[10][10];
    int sign = 1;
 for (int f = 0; f < n; f++)
 {
 getcof_10(mat, temp, 0, f, n,processnum);
 det_part_10 += sign * mat[0][f] * determinant_10(temp, n - 1,processnum);
 sign = -sign;
 }
 return det_part_10;
}
void getcof_11(int mat[11][11], int temp[11][11], int p, int q, int n,int processnum)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col]; 
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
int determinant_11(int mat[11][11], int n,int processnum)
{
    int det_part_11 = 0;
    if (n == 1) return mat[0][0];
    int temp[11][11];
    int sign = 1;
	for (int f = 0; f < n; f++)
	{
		getcof_11(mat, temp, 0, f, n,processnum);
		det_part_11 += sign * mat[0][f] * determinant_11(temp, n - 1,processnum);
		sign = -sign;
	}
	 return det_part_11;
}
void getcof_12(int mat[12][12], int temp[12][12], int p, int q, int n,int processnum)
{
    int i = 0, j = 0;
    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col]; 
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}
int determinant_12(int mat[12][12], int n,int processnum)
{
    int det_part_12 = 0;
    if (n == 1) return mat[0][0];
    int temp[12][12];
    int sign = 1;
	 for (int f = 0; f < n; f++)
	 {
		 getcof_12(mat, temp, 0, f, n,processnum);
		 det_part_12 += sign * mat[0][f] * determinant_12(temp, n - 1,processnum);
		 sign = -sign;
	 }
	 return det_part_12;
}
 
int process_1(int processnum)
{
    int result;
    void *shm=NULL;
    shmid=shmget(IPC_PRIVATE, sizeof(item), IPC_CREAT|0666);
    shm=(item*)shmat(shmid, NULL, 0);
    pro1=(item*)shm;
    pro1->mat=new int *[matsize];
    int matrixcom_10[10][10];
    int matrixcom_11[11][11];
    int matrixcom_12[12][12];
    for(int size=0;size<=matsize;size++)
    {
        pro1->mat[size]=new int[matsize];
    }
    for(int rol=0;rol<=matsize-1;rol++)
    {
        for(int col=0;col<=matsize-1;col++)
        {
            pro1->mat[rol][col]=mat[rol][col];
        }
    }
    if(matsize==10)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_10[rol][col]=pro1->mat[rol][col];
            }
        }
        D1=determinant_10(matrixcom_10, 10,1) ;
    }
    else if(matsize==11)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_11[rol][col]=pro1->mat[rol][col];
            }
        }
        D1=determinant_11(matrixcom_11, 11,1) ;
    }
    else if(matsize==12)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_12[rol][col]=pro1->mat[rol][col];
            }
        }
		D1=determinant_12(matrixcom_12, 12,1) ;
    }
    det_part[0]=D1;
    pro1->determinant[0]=det_part[0];
    result=pro1->determinant[0];
    shmdt(pro1);
    shmctl(shmid, IPC_RMID, 0);
	return result;
}

int process_2(int processnum)
{
    int temp_10[10][10];
    int temp_11[11][11]; 
    int temp_12[12][12];
    int result;
    void *shm2=NULL;
    int sign = 1;
    shmid2=shmget(IPC_PRIVATE, sizeof(item), IPC_CREAT|0666);
    shm2=(item*)shmat(shmid2, NULL, 0);
    pro2=(item*)shm2;
    pro2->mat=new int *[matsize];
    int matrixcom_10[10][10];
    int matrixcom_11[11][11];
    int matrixcom_12[12][12];
    for(int size=0;size<=matsize;size++)
    {
        pro2->mat[size]=new int[matsize];
    }
    for(int rol=0;rol<=matsize-1;rol++)
    {
        for(int col=0;col<=matsize-1;col++)
        {
            pro2->mat[rol][col]=mat[rol][col];
        }
    }
    if(matsize==10)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_10[rol][col]=pro2->mat[rol][col];
            }
        }
        pid_t pid2;
        pid2=fork();
        int status;
        if(pid2==0)
        {
            D1=0;
            for (int f = 0; f < 5; f++)
            {
				getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
				D1 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
				sign = -sign;
            }           
            det_part[0]=D1;
            pro2->determinant[0]=det_part[0];
            shmdt(pro2);
            exit(0);
        }
        else if(pid2>0)
        {  
			sign=-sign;
            D2=0;
            for (int f = 5; f < 10; f++)
            {
				getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
				D2 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
				sign = -sign;
            }           
            det_part[1]=D2;
            pro2->determinant[1]=det_part[1];
            wait(&status);   
            result=pro2->determinant[0]+pro2->determinant[1];
            shmdt(pro2);
            shmctl(shmid2, IPC_RMID, 0);
        }  
    }
    else if(matsize==11)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_11[rol][col]=pro2->mat[rol][col];
            }
        }
        pid_t pid2;
        pid2=fork();
        int status;
        if(pid2==0)
        {
            D1=0;
            for (int f = 0; f < 6; f++)
            {
				getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
				D1 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
				sign = -sign;
            }           
            det_part[0]=D1;
            pro2->determinant[0]=det_part[0];
            shmdt(pro2);
            exit(0);
        }
        else if(pid2>0)
        {  
            D2=0;
            for (int f = 6; f < 11; f++)
            {
				getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
				D2 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
				sign = -sign;
            }           
            det_part[1]=D2;
            pro2->determinant[1]=det_part[1];
            wait(&status);   
            result=pro2->determinant[0]+pro2->determinant[1];
            shmdt(pro2);
            shmctl(shmid2, IPC_RMID, 0);
        }    
    }
    else if(matsize==12)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_12[rol][col]=pro2->mat[rol][col];
            }
        }  
        pid_t pid2;
        pid2=fork();
        int status;
        if(pid2==0)
        {
            D1=0;
            for (int f = 0; f < 6; f++)
            {
				getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
				D1 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
				sign = -sign;
            }           
            det_part[0]=D1;
            pro2->determinant[0]=det_part[0];
            shmdt(pro2);
            exit(0);
        }
        else if(pid2>0)
        {  
            D2=0;
            for (int f = 6; f < 12; f++)
            {
				getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
				D2 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
				sign = -sign;
            }           
            det_part[1]=D2;
            pro2->determinant[1]=det_part[1];
            wait(&status);   
            result=pro2->determinant[0]+pro2->determinant[1];
            shmdt(pro2);
            shmctl(shmid2, IPC_RMID, 0);
        }
    }
 return result;
}
int process_3(int processnum)
{
    int temp_10[10][10];
    int temp_11[11][11]; 
    int temp_12[12][12];
    int result;
    void *shm3=NULL;
    int sign = 1;
    shmid3=shmget(IPC_PRIVATE, sizeof(item), IPC_CREAT|0666);
    shm3=(item*)shmat(shmid3, NULL, 0);
    pro3=(item*)shm3;
    pro3->mat=new int *[matsize];
    int matrixcom_10[10][10];
    int matrixcom_11[11][11];
    int matrixcom_12[12][12];
    for(int size=0;size<=matsize;size++)
    {
        pro3->mat[size]=new int[matsize];
    }
    for(int rol=0;rol<=matsize-1;rol++)
    {
        for(int col=0;col<=matsize-1;col++)
        {
            pro3->mat[rol][col]=mat[rol][col];
        }
    }
    if(matsize==10)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_10[rol][col]=pro3->mat[rol][col];
            }
        }
        pid_t pid3_1;
        pid3_1=fork();
        int status_1;
        if(pid3_1==0)
        {   
            pid_t pid3_2;
            pid3_2=fork();
            int status_2;
            if(pid3_2==0)
            {
                D1=0;
                for (int f = 0; f < 4; f++)
                {
					getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
					D1 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
					sign = -sign;
                }           
                det_part[0]=D1;
                pro3->determinant[0]=det_part[0];
                shmdt(pro3);
                exit(0);
            }
            else if(pid3_2>0)
            {
                D2=0;
                for (int f = 4; f < 8; f++)
                {
					getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
					D2 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
					sign = -sign;
                }           
                det_part[1]=D2;
                pro3->determinant[1]=det_part[1];
                wait(&status_2);
                shmdt(pro3);
                exit(0);
            }
        }
 
        else if(pid3_1>0)
        {  
            D3=0;
            for (int f = 8; f < 10; f++)
            {
				getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
				D3 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
				sign = -sign;
            }           
            det_part[2]=D3;
            pro3->determinant[2]=det_part[2];
            wait(&status_1);
            result=pro3->determinant[0]+pro3->determinant[1]+pro3->determinant[2];
            shmdt(pro3);
            shmctl(shmid3, IPC_RMID, 0);
        }
    }
    else if(matsize==11)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_11[rol][col]=pro3->mat[rol][col];
            }
        }
        pid_t pid3_1;
        pid3_1=fork();
        int status_1;
        if(pid3_1==0)
        {   
            pid_t pid3_2;
            pid3_2=fork();
            int status_2;
            if(pid3_2==0)
            {
                D1=0;
                for (int f = 0; f < 4; f++)
                {
					getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
					D1 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
					sign = -sign;
                }           
                det_part[0]=D1;
                pro3->determinant[0]=det_part[0];
                shmdt(pro3);
                exit(0);
            }
            else if(pid3_2>0)
            {
                D2=0;
                for (int f = 4; f < 8; f++)
                {
					getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
					D2 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
					sign = -sign;
                }           
                det_part[1]=D2;
                pro3->determinant[1]=det_part[1];
                wait(&status_2);
                shmdt(pro3);
                exit(0);
            }
        }
 
        else if(pid3_1>0)
        {  
            D3=0;
            for (int f = 8; f < 11; f++)
            {
				getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
				D3 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
				sign = -sign;
            }           
            det_part[2]=D3;
            pro3->determinant[2]=det_part[2];
            wait(&status_1);
            result=pro3->determinant[0]+pro3->determinant[1]+pro3->determinant[2];
            shmdt(pro3);
            shmctl(shmid3, IPC_RMID, 0);
        }
    }
    else if(matsize==12)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_12[rol][col]=pro3->mat[rol][col];
            }
        }  
        pid_t pid3_1;
        pid3_1=fork();
        int status_1;
        if(pid3_1==0)
        {   
            pid_t pid3_2;
            pid3_2=fork();
            int status_2;
            if(pid3_2==0)
            {
                D1=0;
                for (int f = 0; f < 4; f++)
                {
					getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
					D1 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
					sign = -sign;
                }           
                det_part[0]=D1;
                pro3->determinant[0]=det_part[0];
                shmdt(pro3);
                exit(0);
            }
            else if(pid3_2>0)
            {
                D2=0;
                for (int f = 4; f < 8; f++)
                {
					getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
					D2 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
					sign = -sign;
                }           
                det_part[1]=D2;
                pro3->determinant[1]=det_part[1];
                wait(&status_2);
                shmdt(pro3);
                exit(0);
            }
        }
 
        else if(pid3_1>0)
        {  
            D3=0;
            for (int f = 8; f < 12; f++)
            {
				getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
				D3 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
				sign = -sign;
            }           
            det_part[2]=D3;
            pro3->determinant[2]=det_part[2];
            wait(&status_1);
            result=pro3->determinant[0]+pro3->determinant[1]+pro3->determinant[2];
            shmdt(pro3);
            shmctl(shmid3, IPC_RMID, 0);
        }
    }
 return result;
}
 
int process_4(int processnum)
{
    int temp_10[10][10];
    int temp_11[11][11]; 
    int temp_12[12][12];
    int result;
    void *shm4=NULL;
    int sign = 1;
    shmid4=shmget(IPC_PRIVATE, sizeof(item), IPC_CREAT|0666);
    shm4=(item*)shmat(shmid4, NULL, 0);
    pro4=(item*)shm4;
    pro4->mat=new int *[matsize];
    int matrixcom_10[10][10];
    int matrixcom_11[11][11];
    int matrixcom_12[12][12];
    for(int size=0;size<=matsize;size++)
    {
        pro4->mat[size]=new int[matsize];
    }
    for(int rol=0;rol<=matsize-1;rol++)
    {
        for(int col=0;col<=matsize-1;col++)
        {
            pro4->mat[rol][col]=mat[rol][col];
        }
    }
    if(matsize==10)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_10[rol][col]=pro4->mat[rol][col];
            }
        }  
        pid_t pid4_1;
        pid4_1=fork();
        int status_1;
        if(pid4_1==0)
        {   
            pid_t pid4_2;
            pid4_2=fork();
            int status_2;
            if(pid4_2==0)
            {
                D1=0;
                for (int f = 0; f < 3; f++)
                {
					getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
					D1 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
					sign = -sign;
                }           
                det_part[0]=D1;
                pro4->determinant[0]=det_part[0];               
                shmdt(pro4);
                exit(0);
            }
            else if(pid4_2>0)
            {
                sign=-1;
                D2=0;
                for (int f = 3; f < 6; f++)
                {
					getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
					D2 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
					sign = -sign;
                }           
                det_part[1]=D2;
                pro4->determinant[1]=det_part[1];
                wait(&status_2);
                shmdt(pro4);
                exit(0);
            }
        }
 
        else if(pid4_1>0)
        {
            pid_t pid4_3;
            pid4_3=fork();
            int status_3;  
            if(pid4_3==0)
            {
                D3=0;
                for (int f = 6; f < 9; f++)
                {
					getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
					D3 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
					sign = -sign;
                }           
                det_part[2]=D3;
                pro4->determinant[2]=det_part[2];
                shmdt(pro4);
                exit(0);
            }
            else if(pid4_3>0)
            {
                sign=-1;
                D4=0;
                for (int f = 9; f < 10; f++)
                {
					getcof_10(matrixcom_10, temp_10, 0, f, 10,processnum);
					D4 += sign * matrixcom_10[0][f] * determinant_10(temp_10, 10 - 1,processnum);
					sign = -sign;
                }           
                det_part[3]=D4;
                pro4->determinant[3]=det_part[3];
                wait(&status_1);
                wait(&status_3);
                result=pro4->determinant[0]+pro4->determinant[1]+pro4->determinant[2]+pro4->determinant[3];
                shmdt(pro4);
                shmctl(shmid4, IPC_RMID, 0);              
            }
        }
    }
    else if(matsize==11)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_11[rol][col]=pro4->mat[rol][col];
            }
        }
        pid_t pid4_1;
        pid4_1=fork();
        int status_1;
        if(pid4_1==0)
        {   
            pid_t pid4_2;
            pid4_2=fork();
            int status_2;
            if(pid4_2==0)
            {
                D1=0;
                for (int f = 0; f < 3; f++)
                {
					getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
					D1 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
					sign = -sign;
                }           
                det_part[0]=D1;
                pro4->determinant[0]=det_part[0];               
                shmdt(pro4);
                exit(0);
            }
            else if(pid4_2>0)
            {
                sign=-1;
                D2=0;
                for (int f = 3; f < 6; f++)
                {
					getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
					D2 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
					sign = -sign;
                }           
                det_part[1]=D2;
                pro4->determinant[1]=det_part[1];
                wait(&status_2);
                shmdt(pro4);
                exit(0);
            }
        }
 
        else if(pid4_1>0)
        {
            pid_t pid4_3;
            pid4_3=fork();
            int status_3;  
            if(pid4_3==0)
            {
                D3=0;
                for (int f = 6; f < 9; f++)
                {
					getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
					D3 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
					sign = -sign;
                }           
                det_part[2]=D3;
                pro4->determinant[2]=det_part[2];
                shmdt(pro4);
                exit(0);
            }
            else if(pid4_3>0)
            {
                sign=-1;
                D4=0;
                for (int f = 9; f < 11; f++)
                {
					getcof_11(matrixcom_11, temp_11, 0, f, 11,processnum);
					D4 += sign * matrixcom_11[0][f] * determinant_11(temp_11, 11 - 1,processnum);
					sign = -sign;
                }           
                det_part[3]=D4;
                pro4->determinant[3]=det_part[3];
                wait(&status_1);
                wait(&status_3);
                result=pro4->determinant[0]+pro4->determinant[1]+pro4->determinant[2]+pro4->determinant[3];
                shmdt(pro4);
                shmctl(shmid4, IPC_RMID, 0);
               
            }
        }
    }
    else if(matsize==12)
    {
        for(int rol=0;rol<=matsize-1;rol++)
        {
            for(int col=0;col<=matsize-1;col++)
            {
                matrixcom_12[rol][col]=pro4->mat[rol][col];
            }
        }  
        pid_t pid4_1;
        pid4_1=fork();
        int status_1;
        if(pid4_1==0)
        {   
            pid_t pid4_2;
            pid4_2=fork();
            int status_2;
            if(pid4_2==0)
            {
                D1=0;
                for (int f = 0; f < 3; f++)
                {
					getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
					D1 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
					sign = -sign;
                }           
                det_part[0]=D1;
                pro4->determinant[0]=det_part[0];               
                shmdt(pro4);
                exit(0);
            }
            else if(pid4_2>0)
            {
                sign=-1;
                D2=0;
                for (int f = 3; f < 6; f++)
                {
					getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
					D2 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
					sign = -sign;
                }           
                det_part[1]=D2;
                pro4->determinant[1]=det_part[1];
                wait(&status_2);
                shmdt(pro4);
                exit(0);
            }
        }
 
        else if(pid4_1>0)
        {
            pid_t pid4_3;
            pid4_3=fork();
            int status_3;  
            if(pid4_3==0)
            {
                D3=0;
                for (int f = 6; f < 9; f++)
                {
					getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
					D3 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
					sign = -sign;
                }           
                det_part[2]=D3;
                pro4->determinant[2]=det_part[2];
                shmdt(pro4);
                exit(0);
            }
            else if(pid4_3>0)
            {
                sign=-1;
                D4=0;
                for (int f = 9; f < 12; f++)
                {
					getcof_12(matrixcom_12, temp_12, 0, f, 12,processnum);
					D4 += sign * matrixcom_12[0][f] * determinant_12(temp_12, 12 - 1,processnum);
					sign = -sign;
                }           
                det_part[3]=D4;
                pro4->determinant[3]=det_part[3];
                wait(&status_1);
                wait(&status_3);
                result=pro4->determinant[0]+pro4->determinant[1]+pro4->determinant[2]+pro4->determinant[3];
                shmdt(pro4);
                shmctl(shmid4, IPC_RMID, 0);
               
            }
        }
    }
 
 return result;
}
