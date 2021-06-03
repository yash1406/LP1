#include<bits/stdc++.h>
using namespace std;
#define n 3

class Node
{
	public:
	int newx,newy,f,h;
	int modify[n][n];
	Node(int x,int y,int modify[n][n],int f,int h)
	{
		newx = x;
		newy = y;
		memcpy(this->modify,modify,n*n*sizeof(int));
		this->f = f;
		this->h = h;
	}	
};

int calculateh(int init[n][n],int res[n][n])
{
		int count = 0;
		for(int i = 0;i<n;i++)
		{
			for(int j = 0;j<n;j++)
			{
				if(init[i][j] != res[i][j] && init[i][j]!=0)
				{
					count++;
				}
			}
		}
		return count;
}

void print(int x[n][n])
{
	cout<<endl;
	for(int i = 0;i<n;i++)
	{
		for(int j = 0;j<n;j++)
		{
			cout<<x[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

Node* createNode(int init[n][n],int res[n][n],int x,int y,int newx,int newy,int g)
{
		int modify[n][n];
		memcpy(modify,init,n*n*sizeof(int));
		int temp = modify[newx][newy];
		modify[newx][newy] = modify[x][y];
		modify[x][y] = temp;
		int h = calculateh(modify,res);
		return new Node(newx,newy,modify,g+h,h);
}

Node* compare(Node* obj1,Node* obj2)
{
	if(obj1!=NULL)
	{
		if(obj1->f > obj2->f)
		{
			obj1 = obj2;
		}
	}
	else
	{
		obj1 = obj2;
	}
	return obj1;
}
void solve(int init[n][n],int res[n][n],int x,int y,int g)
{
	Node *obj1=NULL,*obj2=NULL,*obj3=NULL,*obj4=NULL;
	if(x+1<n&&y<n)
	{
		obj1 = createNode(init,res,x,y,x+1,y,g);
	}
	if(x<n&&y+1<n)
	{
		obj2 = createNode(init,res,x,y,x,y+1,g);
	}
	if(x-1>=0&&y<n)
	{
		obj3 = createNode(init,res,x,y,x-1,y,g);
	}
	if(x<n&&y-1>=0)
	{
		obj4 = createNode(init,res,x,y,x,y-1,g);
	}
	
	Node* obj = NULL;
	
	if(obj1!=NULL)
	{
		obj = compare(obj,obj1);
	}
	if(obj2!=NULL)
	{
		obj = compare(obj,obj2);
	}
	if(obj3!=NULL)
	{
		obj = compare(obj,obj3);
	}
	if(obj4!=NULL)
	{
		obj = compare(obj,obj4);
	}	
	
	print(obj->modify);
	
	if(obj->h!=0)
		solve(obj->modify,res,obj->newx,obj->newy,g+1);
}
int main()
{
	int init[n][n] ={
 				{1, 2, 3}, 
        			{0, 4, 6}, 
        			{7, 5, 8} 
        		};
	int res[n][n] = {
				{1, 2, 3}, 
				{4, 5, 6}, 
				{7, 8, 0} 
			};
	int x = 1,y = 0;
		
	print(init);
	
	solve(init,res,x,y,1);
	return 0;
}
