#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int t;
int d;
int dataNodes;
int indexNodes;
class TreeNode
{
private:	
	bool isLeaf;
	vector<int> keys;
	vector<TreeNode*> children;
public:
	TreeNode(bool leaf);
	void insert(int key,int *val,TreeNode* &newEntry);
	void split(int *val,TreeNode* &newEntry);
	TreeNode* createRoot(int val,TreeNode* newEntry);
	void show();
};
void TreeNode::show()
{
	for(int i=0;i<keys.size();++i)
		cout<<keys[i]<<" ";
	cout<<endl;
}
TreeNode::TreeNode(bool leaf)
{
	isLeaf = leaf;
}
void TreeNode::split(int *val,TreeNode* &newEntry)
{
	newEntry = new TreeNode(false);
	++indexNodes;
	*val = this->keys[t];
	for(int i=t+1;i<=(2*t+1);++i)
		newEntry->keys.push_back(this->keys[i]);
	this->keys.resize(t);
	for(int i=t+1;i<=2*t+2;++i)
		newEntry->children.push_back(this->children[i]);
	this->children.resize(t+1);
}
void TreeNode::insert(int key,int *val,TreeNode* &newEntry)
{
	if(!isLeaf)
	{
		int i = 0;
		while(i<keys.size()&&keys[i]<key)
			++i;
		children[i]->insert(key,val,newEntry);
		if(newEntry==NULL)
			return;
		if(keys.size()<(2*t+1))
		{
			keys.insert(keys.begin()+i,*val);
			children.insert(children.begin()+1+i,newEntry);
			newEntry = NULL;
			return;
		}
		else
		{
			keys.insert(keys.begin()+i,*val);
			children.insert(children.begin()+1+i,newEntry);
			split(val,newEntry);
			return;
		}		
	}
	else
	{
		vector<int>::iterator it;
		it = lower_bound(keys.begin(),keys.end(),key);
		keys.insert(it,key);
		if(keys.size()==(2*d+1))
		{
			newEntry = new TreeNode(true);
			++dataNodes;
			*val = this->keys[d];
			for(int i =d;i<=2*d;++i)
				newEntry->keys.push_back(this->keys[i]);
			this->keys.resize(d);
		}
	}
}
TreeNode* TreeNode::createRoot(int val,TreeNode* newEntry)
{
	TreeNode* root = new TreeNode(false);
	++indexNodes;
	root->keys.push_back(val);
	root->children.push_back(this);
	root->children.push_back(newEntry);
	return root;
}
class Tree
{
private:	
	TreeNode* root;
public:
	Tree();
	void insert(int key);
	void display();
};
Tree::Tree()
{
	root = new TreeNode(true);
	++dataNodes;
}
void Tree::insert(int key)
{
	TreeNode* newEntry = NULL;
	int val = 0;
	root->insert(key,&val,newEntry);
	if(newEntry!=NULL)
		root = root->createRoot(val,newEntry);
}
void Tree::display()
{
	cout<<indexNodes<<" "<<dataNodes<<" ";
	root->show();
}
int main()
{
	cin>>d;
	cin>>t;
	dataNodes = 0;
	indexNodes = 0;
	Tree* myTree = new Tree();
	int x;
	while(true)
	{
		cin>>x;
		if(x==1)
		{
			int key;
			cin>>key;
			myTree->insert(key);
		}
		else if(x==2)
			myTree->display();
		else
			break;
	}
	return 0;
}