//Radixsort.cpp

# include <iostream.h>
# include <stdio.h>
# include <conio.h>
# define MAX_NUM_OF_KEY 8
# define RD 10
# define MAX_SPACE 10000
# define ERROR -1

typedef int KeyType;
typedef int InfoType;
typedef int ArrType[RD];

typedef struct SLCell
{  KeyType keys[MAX_NUM_OF_KEY];
   InfoType otheritems;
   int next;
}SLCell;

typedef struct SLList 
{  SLCell r[MAX_SPACE];
   int keynum;
   int recnum;
}SLList;

int Succ(int j)                             //Succ() function
{//To get the next function
   j++;
   return (j);   
}//end of Succ() function

int Ord(int KeyBit)                         //Ord() function
{
	int j;
	for(j=0;j<=RD-1&&j!=KeyBit;j++);
	if(j!=KeyBit) return(ERROR);            //KeyBit OVERFLOW THEN ERROR 
	   else return(j);
}//end of Ord() function

void OutExample(SLList L,int i)             //OutExample() function
{
////////////////////   Output ////////////////
     int temp,k;
	 printf("\nThe %d Collect result is:  ",i);
//	 temp=L.r[0].otheritems;
//	 printf("%d -> ",temp);
     temp=L.r[0].next;
	 printf("%d -> ",L.r[temp].otheritems);
	 for(k=0;k<L.recnum-2;k++)
	 { temp=L.r[temp].next;
	   printf("%d -> ",L.r[temp].otheritems);
	 }
	 printf("%d",L.r[L.r[temp].next].otheritems);
	 printf("\n");
//////////////////////////////////////////////
}//end of OutExample() function

void Distribute(SLList &L,int i,ArrType &f,ArrType &e)    //Distribute() function
{  int j,p;
   for(j=0;j<RD;j++)
      f[j]=0;
   for(p=L.r[0].next;p;p=L.r[p].next)
   {  j=Ord(L.r[p].keys[i]);                              //call Ord()
      if(!f[j])
	     f[j]=p;
      else
	     L.r[e[j]].next=p;
      e[j]=p;
   }//end of for 
}//end of Distrubute() function

void Collect(SLList &L,int i,ArrType f,ArrType e)         //Collect() function
{  int j,t; 
   for(j=0;!f[j];j=Succ(j));                              //Succ()
   L.r[0].next=f[j];
   t=e[j];
   while(j<RD-1)                                          
   {  for(j=Succ(j);j<RD-1&&!f[j];j=Succ(j));             
      if(f[j])
      {  L.r[t].next=f[j];
	     t=e[j];
	  }//end of if
   }//end of while
   L.r[t].next=0;    
   OutExample(L,i);                                       //Add Output Example function here
}//end of Collect() function

void RadixSort(SLList &L)
{  int i;
   ArrType f,e;

   for(i=0;i<L.recnum;i++)
   L.r[i].next=i+1;       
   L.r[L.recnum].next=0;  

   for(i=0;i<L.keynum;i++)
   {   Distribute(L,i,f,e);
       Collect(L,i,f,e);
   }//end of for
}//end of RadixSort() function

void InitExample(SLList &L)
{//Take SLList L for example  
	L.keynum=3;                  //total key number is 3
	L.recnum=7;                  //total current node is 10     
	L.r[1].otheritems=278;
	L.r[2].otheritems=109;
	L.r[3].otheritems=163;
	L.r[4].otheritems=930;
	L.r[5].otheritems=580;
	L.r[6].otheritems=184;
	L.r[7].otheritems=505;
	//L.r[7].otheritems=0;

	cout<<"The InitExample SLList L is: "<<"278->109->163->930->580->184->505"<<endl;
	
	L.r[1].keys[0]=8;
	L.r[1].keys[1]=7;
	L.r[1].keys[2]=2;

	L.r[2].keys[0]=9;
	L.r[2].keys[1]=0;
	L.r[2].keys[2]=1;

    L.r[3].keys[0]=3;
	L.r[3].keys[1]=6;
	L.r[3].keys[2]=1;

	L.r[4].keys[0]=0;
	L.r[4].keys[1]=3;
	L.r[4].keys[2]=9;

	L.r[5].keys[0]=0;
	L.r[5].keys[1]=8;
	L.r[5].keys[2]=5;

	L.r[6].keys[0]=4;
	L.r[6].keys[1]=8;
	L.r[6].keys[2]=1;

	L.r[7].keys[0]=5;
	L.r[7].keys[1]=0;
	L.r[7].keys[2]=5;
}

void main()		                 //main function
{
	SLList L;
    cout<<"RadixSort.cpp"<<endl<<"============="<<endl<<endl;
	InitExample(L);              //For example
	RadixSort(L);                //RadixSort
	cout<<endl;
    getch();
}