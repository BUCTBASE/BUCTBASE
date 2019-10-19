//HuffmanCoding.cpp
//This function is to create HuffmanTree code
# include <stdio.h>
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# include <string.h>

# define MAX_LENGTH 100
typedef char **HuffmanCode;

typedef struct			//define structure HuffmanTree
{  unsigned int weight;
   unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

void Select(HuffmanTree HT,int i,int &s1,int &s2)  //Select sub-function
{  int j,k=1;                	//s1 is the least of HT[].weight
   while(HT[k].parent!=0)	//s2 is the second least of HT[].weight
       k++;
   s1=k;
   for(j=1;j<=i;++j)
      if(HT[j].parent==0&&HT[j].weight<HT[s1].weight)
	  s1=j;
   k=1;
   while((HT[k].parent!=0||k==s1))
      k++;
   s2=k;
   for(j=1;j<=i;++j)
      if(HT[j].parent==0&&HT[j].weight<HT[s2].weight&&j!=s1)
	  s2=j;
} //Select() end

void HuffmanCoding(HuffmanTree &HT,HuffmanCode&HC,int *w,int n) //sub-function
{  int m,i,s1,s2,start,c,f;
   HuffmanTree p;
   if(n<=1)
	return;
   m=2*n-1;
   HT=(HuffmanTree)malloc((m+1)*sizeof(HTNode));
   for(p=HT+1,i=1;i<=n;++i,++p,++w)	//initial HT[1...n]
     {  p->weight=*w;
	cout<<endl<<"HT["<<i<<"].weight="<<p->weight<<"  ";
	p->parent=0;
	p->lchild=0;
	p->rchild=0;
     }
   for(;i<=m;++i,++p)			//initial HT[n+1...2*n1]
     {  p->weight=0;
	p->parent=0;
	p->lchild=0;
	p->rchild=0;
     }
   cout<<endl<<endl<<"HuffmanTree is created in folowing order :";
   for(i=n+1;i<=m;++i)
   {  Select(HT,i-1,s1,s2);	//s1 is the least, s2 is the second least
      HT[s1].parent=i;
      HT[s2].parent=i;
      HT[i].lchild=s1;
      HT[i].rchild=s2;
      HT[i].weight=HT[s1].weight+HT[s2].weight;
      cout<<endl<<"HT["<<s1<<"] and HT["<<s2<<"] create";
      cout<<" HT["<<i<<"], weight="<<HT[i].weight;
   }
   HC=(HuffmanCode)malloc((n+1)*sizeof(char *));
   char *cd;
   cd=(char *)malloc(n*sizeof(char));
   cd[n-1]='\0';
   cout<<endl<<endl<<"HuffmanTree Code is as follows :"<<endl;
   for(i=1;i<=n;++i)
   {  start=n-1;
      for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
	 if(HT[f].lchild==c)
	    cd[--start]='0';
	 else
	    cd[--start]='1';
      HC[i]=(char*)malloc((n-start)*sizeof(char));
      strcpy(HC[i],&cd[start]);
      printf("\nHT[%d] node's Huffman code is: %s",i,HC[i]);
   }
   free(cd);
} //HuffmanCoding() end

void main()            		//main() function
{  HuffmanTree HT;
   HuffmanCode HC;
   int n,i;
   int *w,W[MAX_LENGTH];;
   cout<<endl<<endl<<"HuffmanCoding.cpp";
   cout<<endl<<"================="<<endl;
   cout<<endl<<"Please input the number of the element of HuffmanTree (eg,5): ";
   cin>>n;
   for(i=0;i<n;++i)
   {  cout<<"Please input the weight of the "<<i+1<<"th element (eg,8): ";
      cin>>W[i];
   }
   w=W;
   HuffmanCoding(HT,HC,w,n);	//call HuffmanCoding()
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end