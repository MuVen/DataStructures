// Trees.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#define MAXSTACKSIZE 1000
#define INF 99999999
#define MINV -987654321
#define MAXV 987654321

inline int MAX(int a, int b){
	return a > b ? a : b;
}

struct lnode{
	int data;
	struct lnode* next;
	struct lnode* previous;
	lnode(int mdata){
		data = mdata;
		next = NULL;
		previous = NULL;
	}
};

lnode* createLNode(int val){
	return new lnode(val);
}

struct node{
	int data;
	struct node* left;
	struct node* right;
	struct node* parent;
	struct node* sibiling;
	int leftChilds;
	int rightChilds;
	/*used only for dll*/
	struct node* next;
	struct node* previous;
	/* used only for Balancing */
	bool isBalanced;
	/* used only for max BST */
	bool isBST;
	/* used only for max BST */
	int leftMin;
	int rightMax;
	/* used for AVL */
	int height;
	node(int mdata){
		data = mdata;
		left = right = NULL;
		sibiling = NULL;
		next = previous = NULL;
		leftChilds = rightChilds = 0;
		isBalanced = false;
		isBST = false;
		leftMin = MINV;
		rightMax = MAXV;
		height = 1;
	}
};

struct stack{
	int top;
	node* arr[MAXSTACKSIZE];
	stack(){
		top = -1;
	}
	bool isEmpty(){
		return (top == -1);
	}
	bool isFull(){
		return (top == MAXSTACKSIZE-1);
	}
	void push(node* data){
		if (isFull())
			return;

		arr[++top] = data;
	}
	node* pop(){
		if(isEmpty())
			return NULL;

		return arr[top--];
	}
	node* topD(){
		if(isEmpty())
			return NULL;

		return arr[top];
	}
};

struct queue{
	int front, rear;
	int msize;
	node* arr[MAXSTACKSIZE];
	queue(){
		rear = -1;
		front = 0;
		msize = 0;
	}
	int size(){
		return msize;
	}
	bool isEmpty(){
		if(rear == -1 && front == 0)
			return true;
		return false;
	}
	bool isFull(){
		if(rear == MAXSTACKSIZE-1)
			return true;
		return false;
	}
	void enQueue(node* data){
		if(isFull())
			return;

		msize++;
		arr[++rear] = data;
	}
	node* deQueue(){
		if(isEmpty())
			return NULL;

		node* temp;
		if(front == rear){
			temp = arr[front];
			rear = -1;
			front = 0;
			msize--;
			return temp;
		}

		msize--;
		temp = arr[front++];
		return temp;
	}
};

struct node* createNode(int val){
	return new node(val);
}

void inOrderL(lnode* root){
	if(root == NULL)
		return;
	
	inOrderL(root->previous);
	cout<<root->data<<" ";
	inOrderL(root->next);
}

void printTreeUsingNext(node* root) {
	if (root == NULL)
		return;

	while (root) {
		cout << " " << root->data;
		root = root->next;
	}

	cout << endl;
}

void printLMinAndRMax(node* rootm){
	if(rootm == NULL)
		return;
	
	printLMinAndRMax(rootm->left);
	printLMinAndRMax(rootm->right);
	cout<<"LM:"<<rootm->leftMin<<" N:"<<rootm->data<<" RM:"<<rootm->rightMax<<endl;
}

void inOrder(node* root){
	if(root == NULL)
		return;

	inOrder(root->left);
	cout<<root->data<<" ";
	inOrder(root->right);
}

void inOrderWithoutRecurr(node* root){
    if(root == NULL)
		return;

	stack s1;
    node* current = root;
	if(current)
		s1.push(current);

	while(!s1.isEmpty()){
		while(current){
			if(current->left)
				s1.push(current->left);
			current = current->left;
		}

		if(current == NULL && !s1.isEmpty()){
			node* temp = s1.pop();
			if(temp){
                cout<<temp->data<<" ";
				current = temp->right;
				if(current)
					s1.push(current);
			}
		}
	}
}

void preOrder(node* root){
	if(root == NULL)
		return;

	cout<<root->data<<" ";
	preOrder(root->left);
	preOrder(root->right);
}

void preOrderWithoutRecurr(node* root){
	if(root == NULL)
		return;

	stack s;
	s.push(root);
	while(!s.isEmpty()){
		node* temp = s.pop();
		if(temp){
		    cout<<temp->data<<" ";
		    s.push(temp->right);
		    s.push(temp->left);
		}
	}
}

void postOrder(node* root){
	if(root == NULL)
		return;

	postOrder(root->left);
	postOrder(root->right);
	cout<<root->data<<" ";
}

void postOrderWithoutRecurr(node* root){
	if(root == NULL)
		return;

	stack s1, s2;
	s1.push(root);
	while(!s1.isEmpty()){
		node* temp = s1.pop();
		s2.push(temp);
		if(temp){
			s1.push(temp->left);
			s1.push(temp->right);
		}
	}

	while(!s2.isEmpty()){
		node* temp = s2.pop();
		if(temp)
			cout<<temp->data<<" ";
	}
}

node* insert(node* root, int val){
	if(root == NULL)
		return createNode(val);

	if(val < root->data) {
		root->left = insert(root->left, val);
		root->leftChilds++;
	}

	if(val > root->data) {
		root->right = insert(root->right, val);
		root->rightChilds++;
	}

	if(root->left)
		root->left->parent = root;
	if(root->right)
		root->right->parent = root;

	return root;
}


node* insertByItr(node* root, int val){
	if(root == NULL)
		return createNode(val);

	node* croot = root;
	while(root){
		if(val < root->data){
			if(root->left) {
				root = root->left;
			} else {
				root->left = createNode(val);
			    break;
			}
		} else if( val > root->data){
			if(root->right){
				root = root->right;
			} else {
				root->right = createNode(val);
				break;
			}
		}
	}

	return croot;
}

node* getMinNode(node* root){
	if(root == NULL)
		return NULL;

	while(root){
		if(root->left)
		   root = root->left;
	    else
			break;
	}

	return root;
}

node* getMaxNode(node* root){
	if(root == NULL)
		return NULL;

	while(root){
		if(root->right)
			root = root->right;
		else
			break;
	}

	return root;
}

node* deleteNode(node* root, int val){
	if(root == NULL)
		return NULL;

	if(val < root->data)
		root->left = deleteNode(root->left, val);
	else if(val > root->data)
		root->right = deleteNode(root->right, val);
	else {
		if(root->left == NULL &&  root->right == NULL){
			delete root;
			return NULL;
		} else if(root->left != NULL && root->right == NULL){
			node* temp = root->left;
			temp->parent = root->parent;
			delete root;
			return temp;
		} else if(root->left == NULL && root->right != NULL){
			node* temp = root->right;
			temp->parent = root->parent;
			delete root;
			return temp;
		} else {
			node* min = getMinNode(root->right);
			root->data = min->data;
			root->right = deleteNode(root->right, min->data);
		}
	}
	return root;
}

void greaterSumTreeUtil(node* root, int& sum){
	if(root == NULL)
		return;

	greaterSumTreeUtil(root->right, sum);
	int val = root->data;
	root->data = sum;
	sum += val;
	greaterSumTreeUtil(root->left, sum);
}

void sumOfAllLeftLeavesBSTUtil(node* root, int& sum){
	if(root == NULL)
		return;

	sumOfAllLeftLeavesBSTUtil(root->left, sum);

	if(root->left && !root->right){
	    sum += root->left->data;
	}

	sumOfAllLeftLeavesBSTUtil(root->right, sum);
}

int convertBinaryTreeToSumTreeUtil(node* root){
	if(root == NULL)
		return 0;

	int mData = root->data;
	int lData = convertBinaryTreeToSumTreeUtil(root->left);
	int rData = convertBinaryTreeToSumTreeUtil(root->right);
	root->data = lData + rData;
	return mData+root->data;
}

node* findInBSTUtilReccur(node* root, int val){
	if(root == NULL)
		return NULL;

	if(root->data == val)
		return root;

	if(val < root->data)
		return findInBSTUtilReccur(root->left, val);

	return findInBSTUtilReccur(root->right, val);
}

node* findInBSTUtilItr(node* root, int val){
    if(root == NULL)
		return NULL;

	node* found = NULL;

	while(root){
		if(root->data == val){
			found = root;
			break;
		}

		if(val < root->data)
			root = root->left;
		else
			root = root->right;
	}

	return found;
}

void sizeOfTreeUtilByRecurr(node* root, int& size){
    if(root == NULL)
		return;

	size++;
	sizeOfTreeUtilByRecurr(root->left, size);
	sizeOfTreeUtilByRecurr(root->right, size);
}

void sizeOfTreeUtilWithoutRecurr(node* root, int& size){
	if(root == NULL)
		return;

	queue q;
	q.enQueue(root);
	size++;

	while(!q.isEmpty()){
		node* temp = q.deQueue();
		if(temp){
			if(temp->left){
				q.enQueue(temp->left);
				size++;
			}
			if(temp->right){
				q.enQueue(temp->right);
				size++;
			}
		}
	}
}

void BFSOfTreeUtil(node* root){
	if(root == NULL)
		return;

	queue q;
	q.enQueue(root);
	while(!q.isEmpty()){
		int size = q.size();
		while(size--){
		    node* temp = q.deQueue();
			cout<<temp->data<<" ";
			if(temp->left)
				q.enQueue(temp->left);
			if(temp->right)
				q.enQueue(temp->right);
		}
		cout<<endl;
	}
}

int getHeightOfTree(node* root){
	if(root == NULL)
		return 0;

	return MAX(getHeightOfTree(root->left), getHeightOfTree(root->right)) + 1;
}

int DiameterOfTreeUtil(node* root){
	if(root == NULL)
		return 0;

	return  MAX(getHeightOfTree(root->left)+getHeightOfTree(root->right)+1, MAX(DiameterOfTreeUtil(root->left), DiameterOfTreeUtil(root->right)));
}

struct DiameterAndHeight{
	int diameter;
	int height;
	DiameterAndHeight(){
		diameter = 0;
		height = 0;
	}
};

DiameterAndHeight DiameterOfTreeUtilOptimize(node* root){
	if(root == NULL)
		return DiameterAndHeight();

	DiameterAndHeight middle;
	DiameterAndHeight left = DiameterOfTreeUtilOptimize(root->left);
	DiameterAndHeight right = DiameterOfTreeUtilOptimize(root->right);

	middle.height = MAX(left.height, right.height) + 1;
	middle.diameter = MAX(left.height+right.height+1, MAX(left.diameter, right.diameter));
	return middle;
}

int maxElementOfTreeUtil(node* root, int& max){
    if(root == NULL)
		return 0;

	max = root->data > max ? root->data : max;
	maxElementOfTreeUtil(root->left, max);
	maxElementOfTreeUtil(root->right, max);
}

int maxElementOfTreeUtilByRecurr(node* root){
	if(root == NULL)
		return MINV;

	return MAX(root->data, MAX(maxElementOfTreeUtilByRecurr(root->left), maxElementOfTreeUtilByRecurr(root->right)));
}

bool mirrorTreeUtil(node* root, node* rootm){
	if(root == NULL && rootm == NULL)
		return true;

	if(root == NULL || rootm == NULL)
		return false;

	return (root->data == rootm->data) && mirrorTreeUtil(root->left, rootm->right) && mirrorTreeUtil(root->right, rootm->left);
}

void createMirrorTreeUtil(node* root){
	if(root == NULL)
		return;

	node* temp = root->left;
	root->left = root->right;
	root->right = temp;

	createMirrorTreeUtil(root->left);
	createMirrorTreeUtil(root->right);
}

bool isTreesSame(node* roota, node* rootb){
	if(roota == NULL && rootb == NULL)
		return true;

	if(roota == NULL || rootb == NULL)
		return false;

	return (roota->data == rootb->data) && isTreesSame(roota->left, rootb->left) && isTreesSame(roota->right, rootb->right);
}

void printAllPathsFromRootToLeafUtil(node* root, int& sum, int path[], int& pathIndex){
	if(root == NULL)
		return;

	path[pathIndex++] = root->data;
	sum = sum - root->data;

	if(sum == 0){
		for(int i = 0; i < pathIndex; i++)
			cout<<path[i]<<" ";
		cout<<endl;
		pathIndex--;
		sum = sum + root->data;
		return;
	}

	printAllPathsFromRootToLeafUtil(root->left, sum, path, pathIndex);
	printAllPathsFromRootToLeafUtil(root->right, sum, path, pathIndex);

	pathIndex--;
	sum = sum + root->data;
}

void reverseLevelOrderTraversalUtil(queue q){
    if(q.isEmpty())
		return;

	queue qel;
	while(!q.isEmpty()){
		node*temp = q.deQueue();
		if(temp){
			if(temp->left)
				qel.enQueue(temp->left);
			if(temp->right)
				qel.enQueue(temp->right);
		}
	}

	reverseLevelOrderTraversalUtil(qel);

	while(!qel.isEmpty()){
		node*temp = qel.deQueue();
		if(temp)
			cout<<temp->data<<" ";
	}

	cout<<endl;
}

int findHeightWithoutRecurrsionUtil(node* root){
	if(root == NULL)
		return 0;

	queue q;
	if(root)
	   q.enQueue(root);
   int height = 0;
   while(!q.isEmpty()){
	   int size = q.size();
	   height++;
	   while(size--){

		   node* temp = q.deQueue();
		   if(temp){
			   if(temp->left)
				   q.enQueue(temp->left);
			   if(temp->right)
				   q.enQueue(temp->right);
		   }
	   }
   }

   return height;
}

void printAllFullNodesInBTreeUtil(node* root){
	if(root == NULL)
		return;

	if(root->left && root->right)
		cout<<root->data<<" ";
	printAllFullNodesInBTreeUtil(root->left);
	printAllFullNodesInBTreeUtil(root->right);
}

void printBottomViewOfBSTUtil(node* root, int hd, map<int, node*>& bView){
	if(root == NULL)
		return;

	bView[hd] = root;
	printBottomViewOfBSTUtil(root->left, hd-1, bView);
	printBottomViewOfBSTUtil(root->right, hd+1, bView);
}

node* constructBSTFromPreOrderUtil(int arr[], int& preOrderIndex, int& preOrderVal, int min, int max, int size){
    if(preOrderIndex >= size)
		return NULL;

	node* root = NULL;

	if(preOrderVal > min && preOrderVal < max){
		root = createNode(preOrderVal);
		preOrderIndex++;
		root->left = constructBSTFromPreOrderUtil(arr, preOrderIndex, arr[preOrderIndex], min, preOrderVal, size);
		root->right = constructBSTFromPreOrderUtil(arr, preOrderIndex, arr[preOrderIndex], preOrderVal, max, size);
	}

	return root;
}

void printTopViewOfBSTUtil(node* root, int hd, map<int, node*>& tView){
	if(root == NULL)
		return;

    if(tView.find(hd) == tView.end()){
		tView[hd] = root;
	}

	printTopViewOfBSTUtil(root->left, hd - 1, tView);
	printTopViewOfBSTUtil(root->right, hd + 1, tView);
}

node* inOrderSuccessor(node* root){
	if(root == NULL)
		return NULL;

	if(root->right)
		return getMinNode(root->right);

	node* par = root->parent;
	while(par && (par->right == root)){
		root = par;
		par = par->parent;
	}

	return par;
}

node* inOrderPredecessor(node* root){
    if(root == NULL)
		return NULL;

	if (root->left)
		return getMaxNode(root->left);

	node* par = root->parent;
	while(par && (par->left == root)){
		root = par;
		par = par->parent;
	}

	return par;
}

int printHeightOfNodeInTreeUtil(node* root, node* find, int height){
	if(root == NULL && find == NULL)
		return 0;

	if(root == NULL || find == NULL)
		return 0;

	if(root->data == find->data){
		return height;
	}

	if(find->data < root->data)
	    return printHeightOfNodeInTreeUtil(root->left, find, height+1);

	return printHeightOfNodeInTreeUtil(root->right, find, height+1);
}

bool printIfTreeBalancedOrNotUtil(node* root){
    if(root == NULL)
		return true;

	int lHeight = getHeightOfTree(root->left);
	int rHeight = getHeightOfTree(root->right);

	if(((lHeight > rHeight) ? (lHeight-rHeight) : (rHeight-lHeight)) >= 2)
		return false;

	return printIfTreeBalancedOrNotUtil(root->left) && printIfTreeBalancedOrNotUtil(root->right);
}

int printIfTreeBalancedOrNotUtilOptimized(node* root){
    if(root == NULL)
		return 0;

	int lHeight = printIfTreeBalancedOrNotUtilOptimized(root->left);
	int rHeight = printIfTreeBalancedOrNotUtilOptimized(root->right);

	int aHeight = (lHeight>rHeight) ? (lHeight-rHeight) : (rHeight-lHeight);
	root->isBalanced = (aHeight >= 2) ? false : true;
    return MAX(lHeight, rHeight) + 1;
}

node* sortedArrayToBSTUtil(int arr[], int left, int right){
	if(left > right)
		return NULL;

	int mid = (left+right)/2;
	node* root = createNode(arr[mid]);
	root->left = sortedArrayToBSTUtil(arr, left, mid-1);
	root->right = sortedArrayToBSTUtil(arr, mid+1, right);
	return root;
}

void pathFromRootToNodeUtil(node* root, node* find, int path[], int& pathIndex, bool& found){
	if(root == NULL && find == NULL)
		return;

	if(root == NULL || find == NULL)
		return;

	if(found)
		return;

	path[pathIndex++] = root->data;

	if(find->data == root->data){
		for(int i = 0; i < pathIndex; i++){
			cout<<path[i]<<" ";
		}
		found = true;
		return;
	}

	if(find->data < root->data)
	    pathFromRootToNodeUtil(root->left, find, path, pathIndex, found);

	pathFromRootToNodeUtil(root->right, find, path, pathIndex, found);
}

int sizeOfTree2Util(node* root){
	if(root == NULL)
		return 0;

	return 1 + sizeOfTree2Util(root->left) + sizeOfTree2Util(root->right);
}

bool isBSTUtil(node* root){
	if(root == NULL)
		return true;

	if(root->left && root->data < root->left->data)
		return false;

	if(root->right && root->data > root->right->data )
		return false;

	return isBSTUtil(root->left) && isBSTUtil(root->right);
}
bool isBSTUtilByMinMax(node* root, int MIN, int MAX){
	if(root == NULL)
		return true;

	if(root->data < MIN)
		return false;

	if(root->data > MAX)
		return false;

	return isBSTUtilByMinMax(root->left, MIN, root->data) && isBSTUtilByMinMax(root->right, root->data, MAX);
}

int findMaxWidthOfTree(node* rootm){
	if(rootm == NULL)
		return MINV;

	queue q;
	int maxWidth = MINV;
	q.enQueue(rootm);

	while(!q.isEmpty()){
		int size = q.size();
		maxWidth = size > maxWidth ? size : maxWidth;
		while(size--){
			node*temp = q.deQueue();
			if(temp->left)
				q.enQueue(temp->left);
			if(temp->right)
				q.enQueue(temp->right);
		}
	}

	return maxWidth;
}

void printNodesBetweenTwoLevelsUtil(node* root, int l1, int l2){
	if(root == NULL)
		return;

	queue q;
	q.enQueue(root);
	int level = 0;
	while(!q.isEmpty()){
		int size = q.size();
		level++;
		while(size--){
			node* temp = q.deQueue();
			if(level >= l1 && level <= l2)
				cout<<temp->data<<" ";
			if(temp->left)
				q.enQueue(temp->left);
			if(temp->right)
				q.enQueue(temp->right);
		}
		cout<<endl;
	}
}

bool isBSTEqualUtil(node* root1, node* root2){
	if(root1 == NULL && root2 == NULL)
		return true;

	if(root1 != NULL && root2 == NULL)
		return false;

	if(root1 == NULL && root2 != NULL)
		return false;

	if(root1->data != root2->data)
		return false;

	return isBSTEqualUtil(root1->left, root2->left) && isBSTEqualUtil(root1->right, root2->right);
}

void printingRightViewUtil(node* root, int& currLevel, int level){
	if(root == NULL)
		return;

	if(level > currLevel){
		cout<<root->data<<" ";
		currLevel = level;
	}

	printingRightViewUtil(root->right, currLevel, level+1);
	printingRightViewUtil(root->left, currLevel, level+1);
}

void printingLeftViewUtil(node* root, int& currLevel, int level){
	if(root == NULL)
		return;

	if(level > currLevel){
		cout<<root->data<<" ";
		currLevel = level;
	}

	printingLeftViewUtil(root->left, currLevel, level+1);
	printingLeftViewUtil(root->right, currLevel, level+1);
}

node* LCABSTUtil(node* root, node* n1, node* n2){
	if(root == NULL)
		return NULL;

	if(n1 == NULL || n2 == NULL)
		return NULL;

	if(n1->data < root->data && n2->data > root->data)
		return root;

	if(n1->data < root->data && n2->data < root->data)
		return LCABSTUtil(root->left, n1, n2);

	return LCABSTUtil(root->right, n1, n2);
}

node* LCABTreeUtil(node* root, node* n1, node* n2){
	if(root == NULL)
		return NULL;

	if(n1 == NULL || n2 == NULL)
		return NULL;

	if(root == n1 || root == n2)
		return root;

	node* left = LCABTreeUtil(root->left, n1, n2);
	node* right = LCABTreeUtil(root->right, n1, n2);

	if(left && right)
		return root;

	return (left != NULL) ? left : right;
}

void verticalSumOfBST(node* root, int hd, map<int,int>& vSum){
	if(root == NULL)
		return;

	map<int, int>::iterator itr = vSum.find(hd);
	if(itr == vSum.end()){
		vSum[hd] = root->data;
	} else {
	    vSum[hd] = itr->second + root->data;
	}

	verticalSumOfBST(root->left, hd - 1, vSum);
	verticalSumOfBST(root->right, hd + 1, vSum);
}

void printTreeInVerticalOrderPathUtil(node* root, int hd, map<int, vector<node*> >& vOrder){
	if(root == NULL)
		return;

	vOrder[hd].push_back(root);
	printTreeInVerticalOrderPathUtil(root->left, hd - 1, vOrder);
	printTreeInVerticalOrderPathUtil(root->right, hd + 1, vOrder);
}

void printNodesThatDontHaveSibilingsUtils(node* root){
	if(root == NULL)
		return;

	if(root->left == NULL && root->right != NULL){
		cout<<root->right->data<<" ";
	}

	if(root->left != NULL && root->right == NULL){
		cout<<root->left->data<<" ";
	}

	printNodesThatDontHaveSibilingsUtils(root->left);
	printNodesThatDontHaveSibilingsUtils(root->right);
}

int distanceOfNodeFromRootUtil(node* root, node* find, int dist){
	if(root == NULL && find == NULL)
		return 0;

	if(root == NULL || find == NULL)
		return 0;

	if(root->data == find->data){
		return dist;
	}

	if(find->data < root->data)
		return distanceOfNodeFromRootUtil(root->left, find, dist+1);

	return distanceOfNodeFromRootUtil(root->right, find, dist+1);
}

void printAllNodesAtDistanceDFromRootUtil(node* root, int dist, int dDist){
    if(root == NULL)
        return;

	if(dist == dDist){
		cout<<root->data<<" ";
	}

	printAllNodesAtDistanceDFromRootUtil(root->left, dist+1, dDist);
	printAllNodesAtDistanceDFromRootUtil(root->right, dist+1, dDist);
}

int distanceBetweenTwoNodesUtil(node* root, node* n1, node* n2){

	if(root == NULL)
		return 0;

	if(n1 == NULL && n2 == NULL)
		return 0;

	if(n1 == NULL && n2 != NULL)
		return distanceOfNodeFromRootUtil(root, n2, 0);

	if(n1 != NULL && n2 == NULL)
		return distanceOfNodeFromRootUtil(root, n1, 0);

    int nd1 = distanceOfNodeFromRootUtil(root, n1, 0);
	int nd2 = distanceOfNodeFromRootUtil(root, n2, 0);

	node* lca = LCABSTUtil(root, n1, n2);
	int nd3 = distanceOfNodeFromRootUtil(root, lca, 0);

	return ((nd1 + nd2) - (2 * (nd3)));
}

void maxSumFromRootToAllLeavesUtil(node* rootm, int sum, int& mSum){
	if(rootm == NULL)
		return;

	sum += rootm->data;
	if(rootm->left == NULL && rootm->right == NULL){
		mSum = sum > mSum ? sum : mSum;
		sum -= rootm->data;
		return;
	}

	maxSumFromRootToAllLeavesUtil(rootm->left, sum, mSum);
	maxSumFromRootToAllLeavesUtil(rootm->right, sum, mSum);
	sum -= rootm->data;
}

void printAllNodesAtDistanceDFromLeafUtil(node* rootm, int dist, int disk, int path[], int& pathIndex, bool pathp[])
{
	if(rootm == NULL)
		return;

	path[pathIndex] = rootm->data;
	pathp[pathIndex] = false;
	pathIndex++;

	if(rootm->left == NULL && rootm->right == NULL){
		int distance = dist - disk - 1;
		if(distance >= 0 && pathp[distance] == false){
			cout<<path[distance]<<" ";
			pathp[distance] = true;
		}
        pathIndex--;
		return;
	}

	printAllNodesAtDistanceDFromLeafUtil(rootm->left, dist+1, disk, path, pathIndex, pathp);
	printAllNodesAtDistanceDFromLeafUtil(rootm->right, dist+1, disk, path, pathIndex, pathp);
	pathIndex--;
}

void printBTreeInZigZagUtil(node* root){
	if(root == NULL)
		return;

	queue q;
	stack s;
	bool zigzag = false;
	q.enQueue(root);

	while(!q.isEmpty()){
	    int size = q.size();
        while(size--){
			node* temp = q.deQueue();
			if(!zigzag)
			    cout<<temp->data<<" ";
		    else
				s.push(temp);
			if(temp){
				if(temp->left)
					q.enQueue(temp->left);
				if(temp->right)
					q.enQueue(temp->right);
			}
		}

		while(!s.isEmpty()){
			node* temp = s.pop();
			if(temp)
				cout<<temp->data<<" ";
		}
		zigzag = !zigzag;
		cout<<endl;
	}
}

string itostr(int s){
	stringstream ss;
	ss<<s;
	return ss.str();
}

void subTreePreOrder(node* root, string& str){
	if(root == NULL) {
	    str.append("X");
	    return;
    }

	str.append(itostr(root->data));
	subTreePreOrder(root->left, str);
	subTreePreOrder(root->right, str);
}

bool printTreeIsSubTreeOfATreeUtil(node* rootm, node* roots){
	if(rootm == NULL && roots == NULL)
		return true;

	if(rootm == NULL || roots == NULL)
		return false;

	string mStr, sStr;
	subTreePreOrder(rootm, mStr);
	subTreePreOrder(roots, sStr);

	return mStr.find(sStr) != -1;
}

node* BSTFromInOrderPostOrderUtil(int post[], int& postIndex, int min, int max){
     if(postIndex < 0)
		 return NULL;

	 node* root = NULL;

	 if(post[postIndex] > min && post[postIndex] < max){
		 root = createNode(post[postIndex--]);
		 root->right = BSTFromInOrderPostOrderUtil(post, postIndex, root->data, max);
		 root->left = BSTFromInOrderPostOrderUtil(post, postIndex, min, root->data);
	 }

	return root;
}

node* bTreeFromInOrderPostOrderUtil(int in[], int post[], int& postIndex, int left, int right){
	if(left > right)
		return NULL;

	node* root = createNode(post[postIndex--]);

	if(left == right)
		return root;

	int index;
	for(index = left; index <= right; index++){
		if(root->data == in[index])
			break;
	}

	root->right = bTreeFromInOrderPostOrderUtil(in, post, postIndex, index+1, right);
	root->left = bTreeFromInOrderPostOrderUtil(in, post, postIndex, left, index-1);
	return root;
}

node* BSTFromInOrderPreOrderUtil(int pre[], int& preIndex, int min, int max, int size){
	if(preIndex > size)
		return NULL;

	node* root = NULL;

	if(pre[preIndex]>min && pre[preIndex]<max){
	    root = createNode(pre[preIndex++]);
	    root->left = BSTFromInOrderPreOrderUtil(pre, preIndex, min, root->data, size);
		root->right = BSTFromInOrderPreOrderUtil(pre, preIndex, root->data, max, size);
	}

	return root;
}

node* bTreeFromInOrderPreOrderUtil(int in[], int pre[], int& preIndex, int left, int right){
	if(left > right)
		return NULL;

	node* root = createNode(pre[preIndex++]);
	if(left == right)
		return root;

	int index;
	for(index = left; index <= right; index++){
		if(root->data == in[index])
			break;
	}

	root->left = bTreeFromInOrderPreOrderUtil(in, pre, preIndex, left, index-1);
	root->right = bTreeFromInOrderPreOrderUtil(in, pre, preIndex, index+1, right);
	return root;
}

bool isSibilingsUtil(node* root, node* n1, node* n2){
	if(root == NULL)
		return false;

	if(n1 == NULL && n2 == NULL)
		return true;

	if(n1 == NULL || n2 == NULL)
		return false;

	if(root->left && root->right){
	    if(root->left == n1 && root->right == n2)
			return true;
		if(root->left == n2 && root->right == n1)
			return true;
	}

	return isSibilingsUtil(root->left, n1, n2) || isSibilingsUtil(root->right, n1, n2);
}

bool distanceOfNodeFromRootInBTreeUtil(node* root, node* find, int dist, int& fDist){
    if(root == NULL)
		return false;

	if(find == NULL)
		return false;

	if(root->data == find->data){
		fDist = dist;
		return true;
	}

	if(distanceOfNodeFromRootInBTreeUtil(root->left, find, dist+1, fDist))
		return true;

	if(distanceOfNodeFromRootInBTreeUtil(root->right, find, dist+1, fDist))
		return true;

	return false;
}

bool isCousinsUtil(node* root, node* c1, node* c2){
	if(root == NULL)
		return false;

	if((c1 == NULL && c2 == NULL)||(c1 == NULL || c2 == NULL))
		return false;

	int c1level, c2level;
	if(!distanceOfNodeFromRootInBTreeUtil(root, c1, 0, c1level))
		return false;

	if(!distanceOfNodeFromRootInBTreeUtil(root, c2, 0, c2level))
		return false;

	if(c1level != c2level)
		return false;

	return !isSibilingsUtil(root, c1, c2);
}

void calcNextSiblings(node* root){
	if(root == NULL)
		return;

	queue q;
	stack s;
	q.enQueue(root);
	while(!q.isEmpty()){
		int size = q.size();
		while(size--){
			node* temp = q.deQueue();
			if(temp){
				s.push(temp);
				if(temp->left)
					q.enQueue(temp->left);
				if(temp->right)
					q.enQueue(temp->right);
			}
		}

		node* last = NULL;
		while(!s.isEmpty()){
			node* temp = s.pop();
			temp->sibiling = last;
			last = temp;
		}
	}
}

void printSibilingsOfNodeUtil(node* root){
    if(root == NULL)
		return;

	while(root){
		cout<<root->data<<" ";
		root = root->sibiling;
	}
}

node* inOrderWithoutParentUtil(node* root, node* find){
	if(root == NULL || find == NULL)
		return NULL;

	if(find->right)
		return getMinNode(find->right);

    if(find == getMaxNode(root))
    	return NULL;

	node* successor = NULL;
	while(root){
		if(find->data < root->data){
			successor = root;
			root = root->left;
		}else if(find->data > root->data){
			root = root->right;
		}else{
			break;
		}
	}

    return root ? successor : NULL;
}

node* linkedListToBSTUtil(lnode** head, int length){
	if(length <= 0)
		return NULL;

	node* left = linkedListToBSTUtil(head, length/2);
	node* root = createNode((*head)->data);
	(*head) = (*head)->next;
	root->left = left;
	root->right = linkedListToBSTUtil(head, length - length/2 - 1);
	return root;
}

node* doubleLinkedListToBSTUtil(lnode** head, int length){
	if(length <= 0)
		return NULL;
	
	node* left = doubleLinkedListToBSTUtil(head, length/2);
	node* root = createNode((*head)->data);(*head)=(*head)->next;
	root->left = left;
	root->right = doubleLinkedListToBSTUtil(head, length - length/2 - 1);
	return root;
}

lnode* doubleLinkedListToBSTInplaceUtil(lnode** head, int length){
	if(length <= 0)
		return NULL;
	
	lnode* left = doubleLinkedListToBSTInplaceUtil(head, length/2);
	lnode* root = *head; (*head) = (*head)->next;
	root->previous = left;
	root->next = doubleLinkedListToBSTInplaceUtil(head, length - length/2 -1);
	return root;
}

node* ceilInBSTUtil(node* root, int ceil){
	if(root == NULL)
		return NULL;
	
	if(root->data == ceil)
		return root;
	
	if(ceil > root->data)
		return ceilInBSTUtil(root->right, ceil);
	
	node* lCeil = ceilInBSTUtil(root->left, ceil);
	return (lCeil && (lCeil->data >= ceil)) ? lCeil : root;
}

node* floorInBSTUtil(node* root, int floor){
	if(root == NULL)
		return NULL;
	
	if(root->data == floor)
		return root;
	
	if(floor < root->data)
		return floorInBSTUtil(root->left, floor);
	
	node* lFloor = floorInBSTUtil(root->right, floor);
	return (lFloor && (lFloor->data <= floor)) ? lFloor : root;
}

node* btreeToDoubleLinkedListUtil(node* root) {
	if (root == NULL)
		return NULL;

	if (root->left) {
		node* left = btreeToDoubleLinkedListUtil(root->left);

		for (; left->right; left = left->right);

		left->next = root;

		root->previous = left;
	}

	if (root->right) {
		node* right = btreeToDoubleLinkedListUtil(root->right);

		for (; right->left; right = right->left);

		right->previous = root;

		root->next = right;
	}

	return root;
}

node* kthLargestElementUtil(node* root, int k) {
	if (root == NULL)
		return NULL;

	while (root) {
		if (k == (root->rightChilds + 1))
			return root;
		else if (k > (root->rightChilds + 1)) {
			k = k - (root->rightChilds + 1);
			root = root->left;
		}
		else
			root = root->right;
	}

	return root;
}

node* kthSmallestElementUtil(node* root, int k) {
	if (root == NULL)
		return NULL;

	while (root) {
		if (k == root->leftChilds + 1)
			return root;
		else if (k > (root->leftChilds + 1)) {
			k = k - (root->leftChilds + 1);
			root = root->right;
		}
		else {
			root = root->left;
		}
	}

	return root;
}

void recorrectSwappedNodesUtil(node* rootm, node** first, node** middle, node** last, node** previous) {
	if (rootm == NULL)
		return;

	recorrectSwappedNodesUtil(rootm->left, first, middle, last, previous);

	if ((*previous) && rootm->data < (*previous)->data) {
		if ((*first) == NULL) {
			(*first) = (*previous);
			(*middle) = rootm;
		}
		else {
			(*last) = rootm;
		}
	}

	*previous = rootm;
	recorrectSwappedNodesUtil(rootm->right, first, middle, last, previous);
}

void secondLargestNodeUtil(node* root, int& count, node** sNode){
   if(root == NULL)
      return;
  
   secondLargestNodeUtil(root->right, count, sNode);
   count++;
   if(count == 2)
	   *sNode = root;
   secondLargestNodeUtil(root->left, count, sNode);
}

void deepestNodeInBTreeUtil(node* rootm, int dist, int& dLevel, node** dNode){
	if(rootm == NULL)
		return;
	
	deepestNodeInBTreeUtil(rootm->left, dist+1, dLevel, dNode);
	
	if(dLevel < dist){
		*dNode = rootm;
		dLevel = dist;
	}

	deepestNodeInBTreeUtil(rootm->right, dist+1, dLevel, dNode);	
}

void deepestLeftNodeInBTreeUtil(node* rootm, int dist, int& dLevel, node** dNode){
	if(rootm == NULL)
		return;
	
	deepestLeftNodeInBTreeUtil(rootm->left, dist+1, dLevel, dNode);
	
	if(dLevel < dist){
		if((*dNode) == NULL && rootm->parent && rootm->parent->left == rootm)
	        (*dNode) = rootm;
        dLevel = dist;
	}
	
	deepestLeftNodeInBTreeUtil(rootm->right, dist+1, dLevel, dNode);
}

void createLinkedListAtEachLevelUtil(node* root){
	if(root == NULL)
		return;
	
	queue q;
	q.enQueue(root);
	while(!q.isEmpty()){
		int size = q.size();
		lnode* headC = NULL;
		lnode* headP = NULL;
		while(size--){
			node* temp = q.deQueue();
			if(temp->left)
				q.enQueue(temp->left);
			if(temp->right)
				q.enQueue(temp->right);
			lnode* llnode = createLNode(temp->data);
			if(headP)
				headP->next = llnode;
			if(headC == NULL)
				headC = llnode;
			headP = llnode;
		}
		
		while(headC){
			lnode* temp = headC;
			cout<<headC->data<<" ";
			headC = headC->next;
			delete temp;
		}

		delete headC;
		cout<<endl;
	}
}

void reverseAlternateLevelsOfBtreeUtil(node* rootm){
	if(rootm == NULL)
		return;
	
	int arr[100];
	int aIndex = 0;
	queue q;
	q.enQueue(rootm);
	bool alternative = true;
	
	while(!q.isEmpty()){
		int size = q.size();
		while(size--){
			node* temp = q.deQueue();
			if(!alternative)
			temp->data = arr[--aIndex];
            cout<<temp->data<<" ";
			if(temp->left){
				q.enQueue(temp->left);
				if(alternative)
				arr[aIndex++] = temp->left->data;
			}
			if(temp->right){
				q.enQueue(temp->right);
				if(alternative)
				arr[aIndex++] = temp->right->data;
			}
		}
		alternative = !alternative;
		cout<<endl;
	}
	
}

int maxSumBetweenAnyTwoLeavesUtil(node* root, int& maxSum){
	if(root == NULL)
		return 0;
	
	int leftMaxSum = maxSumBetweenAnyTwoLeavesUtil(root->left, maxSum);
	int rightMaxSum = maxSumBetweenAnyTwoLeavesUtil(root->right, maxSum);
	int max = MAX(MAX(leftMaxSum, rightMaxSum), leftMaxSum+rightMaxSum+root->data);
	maxSum = max > maxSum ? max : maxSum;
	return MAX(leftMaxSum, rightMaxSum)+root->data;
}

void updateNumberOfLeftAndRightChildsUtil(node* rootm, int& count){
    if(rootm == NULL){
		count--;
        return;
	}
    
	int lCount = count;
	updateNumberOfLeftAndRightChildsUtil(rootm->left, ++count);
	rootm->leftChilds = count - lCount;
	
	updateNumberOfLeftAndRightChildsUtil(rootm->right, ++count);
	rootm->rightChilds = count - lCount - rootm->leftChilds;
}

node* updateLeftMinAndRightMaxUtil(node* rootm)
{
	if(rootm == NULL)
		return NULL;

	node* left = updateLeftMinAndRightMaxUtil(rootm->left);
	node* right = updateLeftMinAndRightMaxUtil(rootm->right);
	
	rootm->leftMin = left ? left->leftMin : rootm->data;
	rootm->rightMax = right ? right->rightMax : rootm->data;
	return rootm;
}

node* largestBSTTreeinBTreeUtil(node* root, int& maxChilds, node** maxNode, int& count){
	if(root == NULL){
		count--;
		return NULL;
	}
	
	int lCount = count;
	node* left = largestBSTTreeinBTreeUtil(root->left, maxChilds, maxNode, ++count);
	root->leftChilds = count - lCount;
	
	node* right = largestBSTTreeinBTreeUtil(root->right, maxChilds, maxNode, ++count);
	root->rightChilds = count - lCount - root->leftChilds;
	
	root->leftMin = left ? left->leftMin : root->data;
	root->rightMax = right ? right->rightMax : root->data;
	
	if((root->left == NULL && root->right == NULL)||
	   (root->left != NULL && root->right == NULL && root->left->isBST && root->data > root->left->rightMax)||
	   (root->right != NULL && root->left == NULL && root->right->isBST && root->data < root->right->leftMin)||
	   (root->left != NULL && root->right != NULL && root->left->isBST && root->right->isBST && root->left->rightMax < root->data && root->right->leftMin > root->data)
		){
			root->isBST = true;
			if(root->leftChilds + root->rightChilds + 1 > maxChilds){
				maxChilds = root->leftChilds + root->rightChilds + 1;
				*maxNode = root;
			}
			
		}

	return root;
}

void swap(int& a, int& b){
    int c = a;
	a = b;
	b = c;
}

void maxHeapify(int* arr, int size, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if(left < size && arr[left] > arr[largest])	
		largest = left;
	
	if(right < size && arr[right] > arr[largest])
		largest = right;
	
	if(largest != i){
		swap(arr[i], arr[largest]);
		maxHeapify(arr, size, largest);
	}
}

void heapSortIncUtil(int* arr, int size)
{
	//Build Max-Heapify.
	for(int i = ((size/2) - 1) ; i >= 0; i--)
		maxHeapify(arr, size, i);
    
	for(int i = size-1; i >= 0; i--){
	    swap(arr[0], arr[i]);
		maxHeapify(arr, i, 0);
	}
	
	for(int i = 0; i < size; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}

void minHeapify(int* arr, int size, int i)
{
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	if(left < size && arr[left] < arr[smallest])
		smallest = left;
	if(right < size && arr[right] < arr[smallest])
	    smallest = right;
	
	if(smallest != i){
		swap(arr[i], arr[smallest]);
		minHeapify(arr, size, smallest);
	}
}

void heapSortDecUtil(int* arr, int size)
{
	//Build Min-Heapify
	for(int i = size/2-1; i >= 0; i--)
		minHeapify(arr, size, i);
	
	for(int i = size-1; i >= 0; i--){
		swap(arr[0], arr[i]);
		minHeapify(arr, i, 0);
	}
	
	for(int i = 0; i < size; i++)
		cout<<arr[i]<<" ";
	cout<<endl;
}

struct HeapNode{
	int data;
	int row;
	int col;
	HeapNode(){
		data = -1;
		row = -1;
		col = -1;
	}
	HeapNode(int mdata, int mrow, int mcol){
		data = mdata;
		row = mrow;
		col = mcol;
	}
};

void minHeapForKSortedArrayUtil(HeapNode* node, int size, int i){
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
   
    if(left < size && node[left].data < node[smallest].data)
		smallest = left;

	if(right < size && node[right].data < node[smallest].data)
		smallest = right;
    
    if(smallest != i){
		swap(node[i].data, node[smallest].data);
		swap(node[i].row, node[smallest].row);
		swap(node[i].col, node[smallest].col);
		minHeapForKSortedArrayUtil(node, size, smallest);
	}
}

void minHeapForKSortedArray(HeapNode* heap, int size){
	for(int i = size/2-1; i >= 0; i--)
		minHeapForKSortedArrayUtil(heap, size, i);
}

void mergeKSortedArraysUtil(int arr[4][4], int row, int col)
{
	HeapNode nodes[4][4];
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			nodes[i][j].data = arr[i][j];
			nodes[i][j].row = i;
			nodes[i][j].col = j;
		}
	}
    
	int result[row*col];
	int resultIndex = 0;

	HeapNode heap[row];
	for(int i = 0; i < row; i++)
		heap[i] = nodes[i][0];
	
	while(!(resultIndex >= row*col)){
		//minHeap
		minHeapForKSortedArray(heap, row);

		//min heap node
		HeapNode& min = heap[0];
		result[resultIndex++] = min.data;
		min = min.col < col - 1 ? nodes[min.row][min.col + 1] : HeapNode(INF, INF, INF);	
	}
	
	for(int i = 0; i < row*col; i++)
		cout<<result[i]<<" ";
	cout<<endl;
}

int nodeHeight(node* n){
	return n ? n->height : 0;
}

int getBalance(node* n){
	if(n == NULL)
		return 0;
	
	return nodeHeight(n->left) - nodeHeight(n->right);
}

node* rotateLeft(node* root){
	node* A = root;
	node* B = A->right;
	node* T2 = B->left;
	
	/*rotate*/
	B->left = A;
	A->right = T2;
	
	/*update Heights*/
	A->height = MAX(nodeHeight(A->left), nodeHeight(A->right)) + 1;
	B->height = MAX(nodeHeight(B->left), nodeHeight(B->right)) + 1;
	
	return B;
}

node* rotateRight(node* root){
	node* A = root;
	node* B = A->left;
	node* T2 = B->right;
	
	/*rotate*/
	B->right = A;
	A->left = T2;
	
	/*update Heights*/
	A->height = MAX(nodeHeight(A->left), nodeHeight(A->right)) + 1;
	B->height = MAX(nodeHeight(B->left), nodeHeight(B->right)) + 1;
	
	return B;
}

node* avlInsertionUtil(node* root, int data){
	/*1. Normal BST insertion*/
	if(root == NULL)
		return createNode(data);
	
	if(data < root->data){
		root->left = avlInsertionUtil(root->left, data);
	}else if(data > root->data){
		root->right = avlInsertionUtil(root->right, data);
	}else
		return root;

	/*2. Height of node */
	root->height = MAX(nodeHeight(root->left), nodeHeight(root->right)) + 1;
	
	/*3. Get Balance */
	int balance = getBalance(root);
	
	/*4. If Unbalanced Rotate Accordingly */
	/* right rotate */
	if(balance > 1 && data < root->left->data)
		return rotateRight(root);
	
	/* left rotate */
	if(balance < -1 && data > root->right->data)
		return rotateLeft(root);
	
	/* left right rotate */
	if(balance > 1 && data > root->left->data){
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	/* right left rotate */
	if(balance < -1 && data < root->right->data){
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	return root;
}

node* avlDeletionUtil(node* root, int data){
	if(root == NULL)
		return NULL;
	
	if(data < root->data){
		root->left = avlDeletionUtil(root->left, data);
	} else if(data > root->data){
		root->right = avlDeletionUtil(root->right, data);
	} else {
		if(root->right == NULL && root->left == NULL){
			delete root;
			return NULL;
		} else if(root->left != NULL && root->right == NULL){
			node* temp = root->left;
			temp->parent = root->parent;
			delete root;
			return temp;
		} else if(root->left == NULL && root->right != NULL){
			node* temp = root->right;
			temp->parent = root->parent;
			delete root;
			return temp;
		} else {
			node* minNode = getMinNode(root->right);
			root->data = minNode->data;
			root->right = avlDeletionUtil(root->right, minNode->data);
		}
	}
	
	/* 2. Update Height */
	root->height = MAX(nodeHeight(root->left), nodeHeight(root->right)) + 1;

	/* 3. get balance */
	int balance = getBalance(root);
	
	/* if unbalanced perform rotate operations */
	/*left - left unbalanced*/
    if(balance > 1 && getBalance(root->left) >= 0)
		return rotateRight(root);

	/*right - right unbalanced*/
	if(balance < -1 && getBalance(root->right) <= 0)
		return rotateLeft(root);

	/* left - right unbalanced*/
	if(balance > 1 && getBalance(root->left) < 0){
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	/* right - left unbalanced*/
	if(balance < -1 && getBalance(root->right) > 0){
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}

	return root;
}
/* MuVen ---------------------------------------------------------- */
void insertInToBST(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insert(root, arr[i]);
	}
	inOrder(root);
}

void insertInToBSTByItr(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insertByItr(root, arr[i]);
	}
	inOrder(root);
}

void preOrderBST(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insert(root, arr[i]);
	}
	preOrder(root);
}

void postOrderBST(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insert(root, arr[i]);
	}
	postOrder(root);
}

void inOrderBST(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insert(root, arr[i]);
	}
	inOrder(root);
}

void preOrderBSTWithoutRecurr(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insert(root, arr[i]);
	}
	preOrderWithoutRecurr(root);
}


void postOrderBSTWithoutRecurr(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insert(root, arr[i]);
	}
	postOrderWithoutRecurr(root);
}

void inOrderBSTWithoutRecurr(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insert(root, arr[i]);
	}
	inOrderWithoutRecurr(root);
}

void greaterSumTree(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};
	node* root = NULL;
	for(int i = 0; i < 7; i++){
		root = insert(root, arr[i]);
	}
	int sum = 0;
	greaterSumTreeUtil(root, sum);
	inOrder(root);
}

void sumOfAllLeftLeavesBST(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* root = NULL;
	for(int i = 0; i < 11; i++){
		root = insert(root, arr[i]);
	}

	int sumLeftLeaves = 0;
	sumOfAllLeftLeavesBSTUtil(root, sumLeftLeaves);
	cout<<"Sum of All Left Leaves "<<sumLeftLeaves;
}

void convertBinaryTreeToSumTree(){
	node* root = createNode(5);
	root->left = createNode(-1);
	root->left->left = createNode(-2);
	root->left->right = createNode(4);
	root->right = createNode(3);
	root->right->left = createNode(-6);
	root->right->right = createNode(10);

	convertBinaryTreeToSumTreeUtil(root);
	inOrder(root);
}

void deleteInBST(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* root = NULL;
	for(int i = 0; i < 11; i++){
		root = insert(root, arr[i]);
	}

	inOrder(root);cout<<endl;
	deleteNode(root, 50);
	inOrder(root);cout<<endl;
	deleteNode(root, 55);
	inOrder(root);
}

void findInBST(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* root = NULL;
	for(int i = 0; i < 11; i++){
		root = insert(root, arr[i]);
	}

    findInBSTUtilReccur(root, 30) ? cout<<"30 found in BST by Reccur" : cout<<"30 not found in BST";cout<<endl;
	findInBSTUtilReccur(root, 33) ? cout<<"33 found in BST by Reccur" : cout<<"33 not found in BST";cout<<endl;
	findInBSTUtilItr(root, 30) ? cout<<"30 found in BST by Itr" : cout<<"30 not found in BST";cout<<endl;
	findInBSTUtilItr(root, 33) ? cout<<"33 found in BST by Itr" : cout<<"33 not found in BST";
}

void sizeOfTree(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* root = NULL;
	for(int i = 0; i < 11; i++){
		root = insert(root, arr[i]);
	}

	int size = 0;
    sizeOfTreeUtilByRecurr(root, size);
	cout<<"size by recurr:"<<size<<endl;

	size = 0;
	sizeOfTreeUtilWithoutRecurr(root, size);
	cout<<"size without recurr:"<<size;
}

void BFSOfTree(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* root = NULL;
	for(int i = 0; i < 11; i++){
		root = insert(root, arr[i]);
	}

	BFSOfTreeUtil(root);
}

void diameterOfTree(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* root = NULL;
	for(int i = 0; i < 11; i++){
		root = insert(root, arr[i]);
	}

	cout<<"Diameter of tree:"<<DiameterOfTreeUtil(root);cout<<endl;
	cout<<"Diameter of tree(optimize):"<<DiameterOfTreeUtilOptimize(root).diameter;
}

void maxElementOfTree(){
	node* root = createNode(5);
	root->left = createNode(-1);
	root->left->left = createNode(-2);
	root->left->right = createNode(4);
	root->right = createNode(3);
	root->right->left = createNode(-6);
	root->right->right = createNode(10);

	int max = MINV;
	maxElementOfTreeUtil(root, max);
	cout<<"Max element of tree:"<<max;cout<<endl;
	cout<<"Max element of tree By Reccur:"<<maxElementOfTreeUtilByRecurr(root);
}

void mirrorTree(){
	node* root = createNode(5);
	root->left = createNode(-1);
	root->left->left = createNode(-2);
	root->left->right = createNode(4);
	root->right = createNode(3);
	root->right->left = createNode(-6);
	root->right->right = createNode(10);

	node* rootm = createNode(5);
	rootm->left = createNode(3);
	rootm->left->left = createNode(10);
	rootm->left->right = createNode(-6);
	rootm->right = createNode(-1);
	rootm->right->left = createNode(4);
	rootm->right->right = createNode(-2);

	mirrorTreeUtil(root, rootm) ? cout<<"Both trees are mirror to each other":cout<<"Both trees are not mirror to each other";
}

void createMirrorTree(){
	node* rootm = createNode(5);
	rootm->left = createNode(3);
	rootm->left->left = createNode(10);
	rootm->left->right = createNode(-6);
	rootm->right = createNode(-1);
	rootm->right->left = createNode(4);
	rootm->right->right = createNode(-2);

	node* mroot = createNode(5);
	mroot->left = createNode(-1);
	mroot->left->left = createNode(-2);
	mroot->left->right = createNode(4);
	mroot->right = createNode(3);
	mroot->right->left = createNode(-6);
	mroot->right->right = createNode(10);

	createMirrorTreeUtil(mroot);
	isTreesSame(mroot, rootm) ? cout<<"created mirror tree successfully":cout<<"Couldnt created mirror tree";
}

void printAllPathsFromRootToLeaf(){
	node* rootm = createNode(5);
	rootm->left = createNode(3);
	rootm->left->left = createNode(2);
	rootm->left->right = createNode(2);
	rootm->right = createNode(1);
	rootm->right->left = createNode(4);
	rootm->right->right = createNode(4);

	int path[100] = {0};
	int pathIndex = 0;
	int sum = 10;
	printAllPathsFromRootToLeafUtil(rootm, sum, path, pathIndex);
}

void reverseLevelOrderTraversal(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* rootm = NULL;
	for(int i = 0; i < 11; i++){
		rootm = insert(rootm, arr[i]);
	}

	queue q;
	if(rootm)
	    q.enQueue(rootm);
	reverseLevelOrderTraversalUtil(q);
	if(rootm)
	    cout<<rootm->data<<endl;
}

void findHeightWithoutRecurrsion(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* rootm = NULL;
	for(int i = 0; i < 11; i++){
		rootm = insert(rootm, arr[i]);
	}

	cout<<"Height of the tree without Recurrsion:"<<findHeightWithoutRecurrsionUtil(rootm);
}

void printAllFullNodesInBTree()
{
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* rootm = NULL;
	for(int i = 0; i < 11; i++){
		rootm = insert(rootm, arr[i]);
	}

	printAllFullNodesInBTreeUtil(rootm);
}

void printBottomViewOfBST(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* rootm = NULL;
	for(int i = 0; i < 11; i++){
		rootm = insert(rootm, arr[i]);
	}

	map<int, node*> bView;
	printBottomViewOfBSTUtil(rootm, 0, bView);

	for(map<int, node*>::iterator itr = bView.begin(); itr != bView.end(); ++itr){
		node* temp = itr->second;
		if(temp){
			cout<<temp->data<<" ";
		}
	}
}

void constructBSTFromPreOrder(){
	int arr[7] = {50, 30, 20, 40, 70, 60, 80};

	int preOrderIndex = 0;
    node* root = constructBSTFromPreOrderUtil(arr, preOrderIndex, arr[preOrderIndex], MINV, MAXV, 7);
	preOrder(root);
}

void printTopViewOfBST(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 35, 55, 75};
	node* rootm = NULL;
	for(int i = 0; i < 11; i++){
		rootm = insert(rootm, arr[i]);
	}

	map<int, node*> tView;
	printTopViewOfBSTUtil(rootm, 0, tView);
	for(map<int, node*>::iterator itr = tView.begin(); itr != tView.end(); ++itr){
		node* temp = itr->second;
		if(temp)
		    cout<<temp->data<<" ";
	}
}

void printInorderSuccessorAndPredecessor(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75};
	node* rootm = NULL;
	for(int i = 0; i < 11; i++){
		rootm = insert(rootm, arr[i]);
	}

	node* ioSuccessor = inOrderSuccessor(rootm->left->right->right);
	if(ioSuccessor)
	cout<<"Inorder Successor:"<<ioSuccessor->data<<endl;

	node* ioPredecessor = inOrderPredecessor(rootm->right->left->left);
	if(ioPredecessor)
	cout<<"Inorder Predecessor:"<<ioPredecessor->data;
}

void printHeightOfTree(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75};
	node* rootm = NULL;
	for(int i = 0; i < 11; i++){
		rootm = insert(rootm, arr[i]);
	}

   cout<<"Height Of Tree:"<<getHeightOfTree(rootm);
}

void printHeightOfNodeInTree(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	int height = printHeightOfNodeInTreeUtil(rootm, rootm->left->left->left->left, 0);
	cout<<"Node found at height:"<<height;
}

void printIfTreeBalancedOrNot(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	int arr1[11] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75};
	node* rootm1 = NULL;
	for(int i = 0; i < 11; i++){
		rootm1 = insert(rootm1, arr1[i]);
	}

	printIfTreeBalancedOrNotUtil(rootm) ? cout<<"Tree is Balanced" : cout<<"Tree is not Balanced";cout<<endl;
	printIfTreeBalancedOrNotUtil(rootm1) ? cout<<"Tree is Balanced" : cout<<"Tree is not Balanced";cout<<endl;

	int arr2[7] = {10, 5, 15, 3, 7, 12, 20};
	node* rootm2 = NULL;
	for(int i = 0; i < 7; i++){
		rootm2 = insert(rootm2, arr2[i]);
	}
	printIfTreeBalancedOrNotUtilOptimized(rootm2);
    rootm2->isBalanced	? cout<<"Tree is Balanced" : cout<<"Tree is not Balanced";cout<<endl;

	int arr3[9] = {10, 5, 15, 3, 7, 12, 20, 1, 0};
	node* rootm3 = NULL;
	for(int i = 0; i < 9; i++){
		rootm3 = insert(rootm3, arr3[i]);
	}
	printIfTreeBalancedOrNotUtilOptimized(rootm3);
	rootm3->isBalanced ? cout<<"Tree is Balanced" : cout<<"Tree is not Balanced";cout<<endl;

	int arr4[3] = {10, 20, 30};
	node* rootm4 = NULL;
	for(int i = 0; i < 3; i++){
		rootm4 = insert(rootm4, arr4[i]);
	}
	printIfTreeBalancedOrNotUtilOptimized(rootm4);
	rootm4->isBalanced ? cout<<"Tree is Balanced" : cout<<"Tree is not Balanced";
}

void sortedArrayToBST(){
	int arr[9]={1,2,3,4,5,6,7,8,9};
	node* root = sortedArrayToBSTUtil(arr, 0, 8);
	cout<<"BST inorder:";
	inOrder(root);
}

void pathFromRootToNode(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	int path[100];
	int pathIndex = 0;
	bool found = false;
	pathFromRootToNodeUtil(rootm, rootm->left->left->left->left, path, pathIndex, found);
}

void sizeOfTree2(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

    cout<<"size of tree:"<<sizeOfTree2Util(rootm);
}

void isBST(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

    isBSTUtil(rootm) ? cout<<"Is Binary Search Tree" : cout<<"Not Binary Search Tree";cout<<endl;
	isBSTUtilByMinMax(rootm, MINV, MAXV) ? cout<<"Is Binary Search Tree" : cout<<"Not Binary Search Tree";cout<<endl;

	node* mroot = createNode(5);
	mroot->left = createNode(-1);
	mroot->left->left = createNode(-2);
	mroot->left->right = createNode(4);
	mroot->right = createNode(3);
	mroot->right->left = createNode(-6);
	mroot->right->right = createNode(10);
	isBSTUtil(mroot) ? cout<<"Is Binary Search Tree" : cout<<"Not Binary Search Tree";cout<<endl;
	isBSTUtilByMinMax(mroot, MINV, MAXV) ? cout<<"Is Binary Search Tree" : cout<<"Not Binary Search Tree";
}

void findMaxWidthOfTree(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	cout<<"Max width in the tree:"<<findMaxWidthOfTree(rootm);
}

void printNodesBetweenTwoLevels(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	printNodesBetweenTwoLevelsUtil(rootm, 2, 4);
}

void isBSTEqual(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	int arr2[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm2 = NULL;
	for(int i = 0; i < 12; i++){
		rootm2 = insert(rootm2, arr2[i]);
	}

	isBSTEqualUtil(rootm, rootm2) ? cout<<"Both Trees are equal":cout<<"Both Trees are not equal";
}

void printingRightView(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	int currLevel = 0;
	printingRightViewUtil(rootm, currLevel, 1);
}

void printingLeftView(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	int currLevel = 0;
	printingLeftViewUtil(rootm, currLevel, 1);
}

void LCABST(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	node* lca = LCABSTUtil(rootm, rootm->left->left, rootm->left->right);
	lca ? cout<<"LCA1:"<<lca->data: cout<<"No LCA found";cout<<endl;
	lca = LCABSTUtil(rootm, rootm->left->left, rootm->right->right);
	lca ? cout<<"LCA2:"<<lca->data: cout<<"No LCA found";cout<<endl;
	lca = LCABSTUtil(rootm, rootm->right->left, rootm->right->right);
	lca ? cout<<"LCA3:"<<lca->data: cout<<"No LCA found";cout<<endl;
	lca = LCABSTUtil(rootm, NULL, rootm->right->right);
	lca ? cout<<"LCA4:"<<lca->data: cout<<"No LCA found";
}

void LCABTree(){
	node* mroot = createNode(5);
	mroot->left = createNode(-1);
	mroot->left->left = createNode(-2);
	mroot->left->right = createNode(4);
	mroot->right = createNode(3);
	mroot->right->left = createNode(-6);
	mroot->right->right = createNode(10);

	node* lca = LCABTreeUtil(mroot, mroot->left->right, mroot->left->left);
	lca ? cout<<"LCA of BTree :"<<lca->data: cout<<"No LCA found";
}

void verticalSumOfBST(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	map<int, int> vSum;
	verticalSumOfBST(rootm,0, vSum);
	for(map<int, int>::iterator itr = vSum.begin(); itr != vSum.end(); ++itr){
		cout<<itr->second<<" ";
	}
}

void printTreeInVerticalOrderPath(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	map<int, vector<node*> > vOrder;
    printTreeInVerticalOrderPathUtil(rootm, 0, vOrder);
	for(map<int, vector<node*> >::iterator itr = vOrder.begin(); itr != vOrder.end(); ++itr){
		cout<<itr->first<<" ";
		vector<node*> temp = itr->second;
		for(vector<node*>::iterator itr = temp.begin(); itr != temp.end(); ++itr){
		    node* temp = *itr;
            cout<<temp->data<<" ";
		}
		cout<<endl;
	}
}

void printNodesThatDontHaveSibilings(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

    printNodesThatDontHaveSibilingsUtils(rootm);
}

void distanceOfNodeFromRoot(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	cout<<"Distance of node from root:"<<distanceOfNodeFromRootUtil(rootm, rootm->left->left->left->left, 0);
}

void printAllNodesAtDistanceDFromRoot(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	printAllNodesAtDistanceDFromRootUtil(rootm, 0, 3);
}

void distanceBetweenTwoNodes(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

 	cout<<"Distance between two nodes:"<<distanceBetweenTwoNodesUtil(rootm, rootm->left->left->left->left, rootm->right->right)<<endl;
	cout<<"Distance between two nodes:"<<distanceBetweenTwoNodesUtil(rootm, rootm->left->left->left->left, rootm->left->right->right)<<endl;
	cout<<"Distance between two nodes:"<<distanceBetweenTwoNodesUtil(rootm, rootm->left->left->left->left, rootm->right->right->left)<<endl;
	cout<<"Distance between two nodes:"<<distanceBetweenTwoNodesUtil(rootm, rootm->left->left->left->left, rootm->right->right->left->left);
}

void maxSumFromRootToAllLeaves(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	int mSum = MINV;
	maxSumFromRootToAllLeavesUtil(rootm, 0, mSum);
	cout<<"Max Sum is :"<<mSum;
}

void printAllNodesAtDistanceDFromLeaf(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	int path[100] = {0};
	int pathIndex = 0;
	bool pathp[100] = {false};
    printAllNodesAtDistanceDFromLeafUtil(rootm, 0, 2, path, pathIndex, pathp);
}

void printBTreeInZigZag(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

    printBTreeInZigZagUtil(rootm);
}

void printTreeIsSubTreeOfATree(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	node* roots = createNode(70);
	roots->right = createNode(80);
	roots->left = createNode(60);
	roots->left->left = createNode(55);
	roots->right->left = createNode(75);
	printTreeIsSubTreeOfATreeUtil(rootm, roots) ? cout<<"roots is subtree of rootm" : cout<<"roots is not subtree of rootm"; cout<<endl;

	roots->right->left->right = createNode(77);
	printTreeIsSubTreeOfATreeUtil(rootm, roots) ? cout<<"roots is subtree of rootm" : cout<<"roots is not subtree of rootm"; cout<<endl;

}

void bTreeFromInOrderPostOrder(){
    int in[12] = {5, 10, 20, 30, 40, 45, 50, 55, 60, 70, 75, 80};
	int post[12] = {5, 10, 20, 45, 40, 30, 55, 60, 75, 80, 70, 50};

	int postIndex = 11;
    node* bst = BSTFromInOrderPostOrderUtil(post, postIndex, MINV, MAXV);
	postIndex = 11;
	node* btree = bTreeFromInOrderPostOrderUtil(in, post, postIndex, 0, 11);

	inOrder(bst);cout<<endl;
	inOrder(btree);cout<<endl;
	postOrder(bst);cout<<endl;
	postOrder(btree);cout<<endl;
}

void bTreeFromInOrderPreOrder(){
    int in[12] = {5, 10, 20, 30, 40, 45, 50, 55, 60, 70, 75, 80};
    int pre[12] ={50, 30, 20, 10, 5, 40, 45, 70, 60, 55, 80, 75};

    int preIndex = 0;
    node* bst = BSTFromInOrderPreOrderUtil(pre, preIndex, MINV, MAXV, 11);

	preIndex = 0;
	node* btree = bTreeFromInOrderPreOrderUtil(in, pre, preIndex, 0, 11);

	inOrder(bst);cout<<endl;
	inOrder(btree);cout<<endl;
	preOrder(bst);cout<<endl;
	preOrder(btree);cout<<endl;
}

void isSibilings(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	isSibilingsUtil(rootm, rootm->left->left, rootm->left->right) ? cout<<"Both nodes are sibilings":cout<<"Both nodes are not sibilings";cout<<endl;
	isSibilingsUtil(rootm, rootm->left->left, rootm->right) ? cout<<"Both nodes are sibilings":cout<<"Both nodes are not sibilings";cout<<endl;
	isSibilingsUtil(rootm, rootm->right->right, rootm->right->left) ? cout<<"Both nodes are sibilings":cout<<"Both nodes are not sibilings";cout<<endl;
}

void isCousins(){
	node* root = createNode(1);
	root->left = createNode(2);
	root->right = createNode(3);
	root->left->left = createNode(4);
	root->left->left->left = createNode(7);
	root->right->left = createNode(6);
	root->right->left->left = createNode(8);
	root->right->left->right = createNode(9);

	isCousinsUtil(root, root->left->left->left, root->right->left->right) ?
	cout<<"Both Nodes are Cousins":cout<<"Both Nodes are not Cousins";cout<<endl;
	isCousinsUtil(root, root->left->left->left, root->right->left) ?
	cout<<"Both Nodes are Cousins":cout<<"Both Nodes are not Cousins";cout<<endl;
}

void printSibilingsOfNode(){
	node* root = createNode(1);
	root->left = createNode(2);
	root->right = createNode(3);
	root->left->left = createNode(4);
	root->left->left->left = createNode(7);
	root->right->left = createNode(6);
	root->right->left->left = createNode(8);
	root->right->left->right = createNode(9);
	calcNextSiblings(root);

	printSibilingsOfNodeUtil(root);cout<<endl;
	printSibilingsOfNodeUtil(root->left);cout<<endl;
	printSibilingsOfNodeUtil(root->left->left);cout<<endl;
	printSibilingsOfNodeUtil(root->left->left->left);
}

void inOrderWithoutParent(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

	node* io = inOrderWithoutParentUtil(rootm, rootm->left->right);
	io?cout<<"Inorder without parent:"<<io->data:cout<<"No IO Successor";cout<<endl;
	io = inOrderWithoutParentUtil(rootm, rootm->left->right->right);
	io?cout<<"Inorder without parent:"<<io->data:cout<<"No IO Successor";cout<<endl;
	io = inOrderWithoutParentUtil(rootm, rootm->right->right);
	io?cout<<"Inorder without parent:"<<io->data:cout<<"No IO Successor";cout<<endl;
	io = inOrderWithoutParentUtil(rootm, rootm->right->left->left);
	io?cout<<"Inorder without parent:"<<io->data:cout<<"No IO Successor";cout<<endl;
}

void linkedListToBST(){
	lnode* head = createLNode(1);
	head->next = createLNode(2);
	head->next->next = createLNode(3);
	head->next->next->next = createLNode(4);
	head->next->next->next->next = createLNode(5);
	head->next->next->next->next->next = createLNode(6);
	head->next->next->next->next->next->next = createLNode(7);
	head->next->next->next->next->next->next->next = createLNode(8);
	head->next->next->next->next->next->next->next->next = createLNode(9);

	node* root = linkedListToBSTUtil(&head, 9);
	inOrder(root);
}

void doubleLinkedListToBST(){
	lnode* head = createLNode(1);
	head->previous = NULL;
	
	head->next = createLNode(2);
	head->next->previous = head;
	
	head->next->next = createLNode(3);
	head->next->next->previous = head->next;
	
	head->next->next->next = createLNode(4);
	head->next->next->next->previous = head->next->next;
	
	head->next->next->next->next = createLNode(5);
	head->next->next->next->next->previous = head->next->next->next;
	
	head->next->next->next->next->next = createLNode(6);
	head->next->next->next->next->next->previous = head->next->next->next->next;
	
	head->next->next->next->next->next->next = createLNode(7);
	head->next->next->next->next->next->next->previous = head->next->next->next->next->next;
	
	head->next->next->next->next->next->next->next = createLNode(8);
	head->next->next->next->next->next->next->next->previous = head->next->next->next->next->next->next;
	
	head->next->next->next->next->next->next->next->next = createLNode(9);
	head->next->next->next->next->next->next->next->next->previous = head->next->next->next->next->next->next->next;

	node* root = doubleLinkedListToBSTUtil(&head, 9);
	inOrder(root);
}

void doubleLinkedListToBSTInplace(){
	lnode* head = createLNode(1);
	head->previous = NULL;
	
	head->next = createLNode(2);
	head->next->previous = head;
	
	head->next->next = createLNode(3);
	head->next->next->previous = head->next;
	
	head->next->next->next = createLNode(4);
	head->next->next->next->previous = head->next->next;
	
	head->next->next->next->next = createLNode(5);
	head->next->next->next->next->previous = head->next->next->next;
	
	head->next->next->next->next->next = createLNode(6);
	head->next->next->next->next->next->previous = head->next->next->next->next;
	
	head->next->next->next->next->next->next = createLNode(7);
	head->next->next->next->next->next->next->previous = head->next->next->next->next->next;
	
	head->next->next->next->next->next->next->next = createLNode(8);
	head->next->next->next->next->next->next->next->previous = head->next->next->next->next->next->next;
	
	head->next->next->next->next->next->next->next->next = createLNode(9);
	head->next->next->next->next->next->next->next->next->previous = head->next->next->next->next->next->next->next;

	lnode* iroot = doubleLinkedListToBSTInplaceUtil(&head, 9);
    inOrderL(iroot);	
}

void ceilInBST(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

    node* ceil = ceilInBSTUtil(rootm, 43);
	ceil ? cout<<"ceil is "<<ceil->data : cout<<"No Ceil";cout<<endl;
	ceil = ceilInBSTUtil(rootm, 45);
	ceil ? cout<<"ceil is "<<ceil->data : cout<<"No Ceil";cout<<endl;
	ceil = ceilInBSTUtil(rootm, 77);
	ceil ? cout<<"ceil is "<<ceil->data : cout<<"No Ceil";cout<<endl;	
	ceil = ceilInBSTUtil(rootm, 88);
	ceil ? cout<<"ceil is "<<ceil->data : cout<<"No Ceil";
}

void floorInBST(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}
    
    node* floor = floorInBSTUtil(rootm, 43);
	floor ? cout<<"floor is "<<floor->data : cout<<"No floor";cout<<endl;	
    floor = floorInBSTUtil(rootm, 45);
	floor ? cout<<"floor is "<<floor->data : cout<<"No floor";cout<<endl;	
    floor = floorInBSTUtil(rootm, 77);
	floor ? cout<<"floor is "<<floor->data : cout<<"No floor";cout<<endl;	
    floor = floorInBSTUtil(rootm, 88);
	floor ? cout<<"floor is "<<floor->data : cout<<"No floor";
}

void btreeToDoubleLinkedList() {
	int arr[12] = { 50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5 };
	node* rootm = NULL;
	for (int i = 0; i < 12; i++) {
		rootm = insert(rootm, arr[i]);
	}

	rootm = btreeToDoubleLinkedListUtil(rootm);
	while (rootm) {
		if (rootm->left)
			rootm = rootm->left;
		else
			break;
	}

	printTreeUsingNext(rootm);
}

void kthLargestElement() {
	int arr[12] = { 50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5 };
	node* rootm = NULL;
	for (int i = 0; i < 12; i++) {
		rootm = insert(rootm, arr[i]);
	}

	inOrder(rootm); cout << endl;
	node* n = kthLargestElementUtil(rootm, 5);
	n ? cout << n->data : cout << "No Larger element"; cout << endl;
	n = kthLargestElementUtil(rootm, 1);
	n ? cout << n->data : cout << "No Larger element"; cout << endl;
	n = kthLargestElementUtil(rootm, 12);
	n ? cout << n->data : cout << "No Larger element"; cout << endl;
	n = kthLargestElementUtil(rootm, 11);
	n ? cout << n->data : cout << "No Larger element"; cout << endl;

}

void kthSmallestElement() {
	int arr[12] = { 50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5 };
	node* rootm = NULL;
	for (int i = 0; i < 12; i++) {
		rootm = insert(rootm, arr[i]);
	}
	inOrder(rootm); cout << endl;
	node* n = kthSmallestElementUtil(rootm, 5);
	n ? cout << n->data : cout << "No Smaller element"; cout << endl;
	n = kthSmallestElementUtil(rootm, 1);
	n ? cout << n->data : cout << "No Smaller element"; cout << endl;
	n = kthSmallestElementUtil(rootm, 12);
	n ? cout << n->data : cout << "No Smaller element"; cout << endl;
	n = kthSmallestElementUtil(rootm, 11);
	n ? cout << n->data : cout << "No Smaller element"; cout << endl;
}

void recorrectSwappedNodes() {
	int arr[12] = { 50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5 };
	node* rootm = NULL;
	for (int i = 0; i < 12; i++) {
		rootm = insert(rootm, arr[i]);
	}

	rootm->left->data = 70;
	rootm->right->data = 30;

	cout << "Before correction" << endl; inOrder(rootm); cout << endl;
	node* first = NULL, *middle = NULL, *last = NULL, *previous = NULL;
	recorrectSwappedNodesUtil(rootm, &first, &middle, &last, &previous);

	if (first && last) {
		int temp = first->data;
		first->data = last->data;
		last->data = temp;
	}
	else {
		int temp = first->data;
		first->data = middle->data;
		middle->data = temp;
	}

	cout << "After correction" << endl; inOrder(rootm); cout << endl;


	rootm->left->data = 50;
	rootm->data = 30;

	cout << "Before correction" << endl; inOrder(rootm); cout << endl;
	node *firsts = NULL, *middles = NULL, *lasts = NULL, *previouss = NULL;
	recorrectSwappedNodesUtil(rootm, &firsts, &middles, &lasts, &previouss);

	if (firsts && lasts) {
		int temp = firsts->data;
		firsts->data = lasts->data;
		lasts->data = temp;
	}
	else {
		int temp = firsts->data;
		firsts->data = middles->data;
		middles->data = temp;
	}

	cout << "After correction" << endl; inOrder(rootm); cout << endl;

	rootm->left->left->data = 30;
	rootm->left->data = 20;
	cout << "Before correction" << endl; inOrder(rootm); cout << endl;
	node *firstt = NULL, *middlet = NULL, *lastt = NULL, *previoust = NULL;
	recorrectSwappedNodesUtil(rootm, &firstt, &middlet, &lastt, &previoust);

	if (firstt && lastt) {
		int temp = firstt->data;
		firstt->data = lastt->data;
		lastt->data = temp;
	}
	else {
		int temp = firstt->data;
		firstt->data = middlet->data;
		middlet->data = temp;
	}

	cout << "After correction" << endl; inOrder(rootm);
}

void secondLargestNode(){
	int arr[12] = { 50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5 };
	node* rootm = NULL;
	for (int i = 0; i < 12; i++) {
		rootm = insert(rootm, arr[i]);
	}
	
	int count = 0;
	node* sCount = NULL;
	secondLargestNodeUtil(rootm, count, &sCount);
	sCount ? cout<<"Second Largest Node:"<<sCount->data:cout<<"No Second Largest Node";
}

void deepestNodeInBTree(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}

    int dLevel = 0;
	node* dNode = NULL;
	deepestNodeInBTreeUtil(rootm, 1, dLevel, &dNode);
	dNode ? cout<<"Deepest node is :"<<dNode->data:cout<<"No Deepest Node found";
}

void deepestLeftNodeInBTree(){
	int arr[11] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75};
	node* rootm = NULL;
	for(int i = 0; i < 11; i++){
		rootm = insert(rootm, arr[i]);
	}

    int dLevel = 0;
    node* dNode = NULL;	
	deepestLeftNodeInBTreeUtil(rootm, 1, dLevel, &dNode);
	dNode ? cout<<"Deepest Left node is :"<<dNode->data:cout<<"No Deepest Left Node found";	
}

void createLinkedListAtEachLevel(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}
	
	createLinkedListAtEachLevelUtil(rootm);
}

void reverseAlternateLevelsOfBtree(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}
	
	reverseAlternateLevelsOfBtreeUtil(rootm);
}

void maxSumBetweenAnyTwoLeaves(){
	int arr[12] = {50, 30, 20, 40, 70, 60, 80, 10, 45, 55, 75, 5};
	node* rootm = NULL;
	for(int i = 0; i < 12; i++){
		rootm = insert(rootm, arr[i]);
	}
	
	int maxSum = MINV;
	maxSumBetweenAnyTwoLeavesUtil(rootm, maxSum);
	cout<<"Max Sum is:"<<maxSum;
}

void updateNumberOfLeftAndRightChilds(){
	node* rootm = createNode(50);
	rootm->left = createNode(10);
	rootm->left->left = createNode(5);
	rootm->left->left->left = createNode(4);
	rootm->left->left->left->left = createNode(3);
	rootm->left->left->left->left->left = createNode(2);
	rootm->left->left->left->left->left->left = createNode(1);
	rootm->left->left->left->left->left->left->left = createNode(0);
	rootm->left->right = createNode(20);
	rootm->right = createNode(60);
	rootm->right->left = createNode(55);
	rootm->right->left->left = createNode(45);
	rootm->right->left->left->left = createNode(35);
	rootm->right->left->left->left->left = createNode(30);
	rootm->right->left->left->left->left->left = createNode(10);
	rootm->right->left->left->left->left->right = createNode(32);
	rootm->right->left->left->left->right = createNode(40);
	rootm->right->right = createNode(70);
	rootm->right->right->left = createNode(65);
	rootm->right->right->right = createNode(80);
	rootm->right->right->right->right = createNode(90);
	int nChilds = 0;
  	updateNumberOfLeftAndRightChildsUtil(rootm, nChilds);
}

void updateLeftMinAndRightMax(){
	node* rootm = createNode(50);
	rootm->left = createNode(10);
	rootm->left->left = createNode(5);
	rootm->left->left->left = createNode(4);
	rootm->left->left->left->left = createNode(3);
	rootm->left->left->left->left->left = createNode(2);
	rootm->left->left->left->left->left->left = createNode(1);
	rootm->left->left->left->left->left->left->left = createNode(0);
	rootm->left->right = createNode(20);
	rootm->right = createNode(60);
	rootm->right->left = createNode(55);
	rootm->right->left->left = createNode(45);
	rootm->right->left->left->left = createNode(35);
	rootm->right->left->left->left->left = createNode(30);
	rootm->right->left->left->left->left->left = createNode(10);
	rootm->right->left->left->left->left->right = createNode(32);
	rootm->right->left->left->left->right = createNode(40);
	rootm->right->right = createNode(70);
	rootm->right->right->left = createNode(65);
	rootm->right->right->right = createNode(80);
	rootm->right->right->right->right = createNode(90);
	updateLeftMinAndRightMaxUtil(rootm);
	printLMinAndRMax(rootm);
}

void largestBSTTreeinBTree(){
	node* rootm = createNode(50);
	rootm->left = createNode(10);
	rootm->left->left = createNode(5);
	rootm->left->left->left = createNode(4);
	rootm->left->left->left->left = createNode(3);
	rootm->left->left->left->left->left = createNode(2);
	rootm->left->left->left->left->left->left = createNode(1);
	rootm->left->left->left->left->left->left->left = createNode(0);
	rootm->left->right = createNode(20);
	rootm->right = createNode(60);
	rootm->right->left = createNode(55);
	rootm->right->left->left = createNode(45);
	rootm->right->left->left->left = createNode(35);
	rootm->right->left->left->left->left = createNode(30);
	rootm->right->left->left->left->left->left = createNode(10);
	rootm->right->left->left->left->left->right = createNode(32);
	rootm->right->left->left->left->right = createNode(40);
	rootm->right->right = createNode(70);
	rootm->right->right->left = createNode(65);
	rootm->right->right->right = createNode(80);
	rootm->right->right->right->right = createNode(90);
			  /* 50
			   /    \ 
			 10     60
			/ \	    / \
		   5  20  55  70
		  /		 /    / \
		 4	   45    65  80
		/	  /           \
	   3	 35            90
	  /		/ \
	 2	   30 40
	/	  / \
   1	 10 32	
  /
 0            */

	int maxChilds = MINV;
	node* maxNode = NULL;
	int count = 0;
	largestBSTTreeinBTreeUtil(rootm, maxChilds, &maxNode, count);
	inOrder(maxNode);
}

void heapSort(){
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    
	cout<<"Increasing: ";heapSortIncUtil(arr, n);
	cout<<"Decreasing: ";heapSortDecUtil(arr, n);
}

void mergeKSortedArrays(){
	int arr[4][4] ={{1, 5, 8, 9},
					{2, 3, 7, 10},
					{4, 6, 11, 15},
					{2, 4, 6, 9}};

	mergeKSortedArraysUtil(arr, 4, 4);
}

void avlInsertion(){
	node* rootm = NULL;
    for(int i = 0; i < 20; i++)
		rootm = avlInsertionUtil(rootm, i);

	BFSOfTreeUtil(rootm);
}

void avlDeletion(){
	node* rootm = NULL;
    for(int i = 0; i <= 20; i++)
		rootm = avlInsertionUtil(rootm, i);

    BFSOfTreeUtil(rootm);
	cout<<endl;

	for(int i = 3; i >= 0; i--){
	    rootm = avlDeletionUtil(rootm, i);
	    BFSOfTreeUtil(rootm);
		printIfTreeBalancedOrNotUtilOptimized(rootm);
		rootm->isBalanced	? cout<<"Tree is Balanced" : cout<<"Tree is not Balanced";cout<<endl;
		cout<<endl;
	}
}

// Need to Implement
// 1.Con­struct a binary tree from given Inorder and Level Order Traversal.
// 2.Con­struct Binary Search Tree from a given Pre­order Tra­ver­sal Using Stack (With­out Recur­sion)
// 3.Red-Black Trees.
// 4.B-Trees.
// 5.Segment Trees.
// 6.Threaded Trees.

int main(){
	cout<<"\n\n1.Insert in to BST \n";insertInToBST();
	cout<<"\n\n2.Insert in to BST by ITR \n";insertInToBSTByItr();
	cout<<"\n\n3.PreOrder BST \n";preOrderBST();
	cout<<"\n\n4.PostOrder BST \n";postOrderBST();
	cout<<"\n\n5.InOrder BST \n";inOrderBST();
	cout<<"\n\n6.PreOrder BST without Recurr\n";preOrderBSTWithoutRecurr();
	cout<<"\n\n7.PostOrder BST without Recurr\n";postOrderBSTWithoutRecurr();
	cout<<"\n\n8.InOrder BST without Recurr\n";inOrderBSTWithoutRecurr();
	cout<<"\n\n9.Greater Sum BST \n";greaterSumTree();
	cout<<"\n\n10.Sum of all left leaves in BST \n";sumOfAllLeftLeavesBST();
	cout<<"\n\n11.Convert Binary Tree to its Sum tree \n";convertBinaryTreeToSumTree();
	cout<<"\n\n12.delete in to BST \n";deleteInBST();
	cout<<"\n\n13.find in to BST \n";findInBST();
	cout<<"\n\n14.size of BST \n";sizeOfTree();
	cout<<"\n\n15.BFS of BST \n";BFSOfTree();
	cout<<"\n\n16.Diameter of BST \n";diameterOfTree();
	cout<<"\n\n17.Max element in BinaryTree \n";maxElementOfTree();
	cout<<"\n\n18.Mirror Tree \n";mirrorTree();
	cout<<"\n\n19.Create Mirror Tree \n";createMirrorTree();
	cout<<"\n\n20.Print All paths from root to leaf whose Sum is X \n";printAllPathsFromRootToLeaf();
	cout<<"\n\n21.Reverse Level Order Traversal \n";reverseLevelOrderTraversal();
	cout<<"\n\n22.Find Height of BST without Recurrsion\n";findHeightWithoutRecurrsion();
	cout<<"\n\n23.Print All Full Node in BTree\n";printAllFullNodesInBTree();
    cout<<"\n\n24.Print Bottom View of BST\n";printBottomViewOfBST();
	cout<<"\n\n25.Construct BST from PreOrder Traversal using Recursion\n";constructBSTFromPreOrder();
	cout<<"\n\n26.Print Top View of a Tree\n";printTopViewOfBST();
	cout<<"\n\n27.Inorder Successor & Predecessor Tree\n";printInorderSuccessorAndPredecessor();
	cout<<"\n\n28.Height of Tree\n";printHeightOfTree();
	cout<<"\n\n29.Get Height of a node in a tree\n";printHeightOfNodeInTree();
	cout<<"\n\n30.Find whether tree is balanced or not\n";printIfTreeBalancedOrNot();
	cout<<"\n\n31.Sorted Array to BST of MinimalHeight\n";sortedArrayToBST();
	cout<<"\n\n32.Path from root to the node\n";pathFromRootToNode();
	cout<<"\n\n33.Size of Tree\n";sizeOfTree2();
	cout<<"\n\n34.Is BST ?\n";isBST();
    cout<<"\n\n34.Max Width In Tree\n";findMaxWidthOfTree();
    cout<<"\n\n35.Print All Node Between Two Levels\n";printNodesBetweenTwoLevels();
	cout<<"\n\n36.Is BST equal ?\n";isBSTEqual();
	cout<<"\n\n37.Printing RightView\n";printingRightView();
	cout<<"\n\n38.Printing LeftView\n";printingLeftView();
	cout<<"\n\n39.LCA of BST\n";LCABST();
	cout<<"\n\n40.LCA of BTree\n";LCABTree();
	cout<<"\n\n41.Vertical Sum of BST\n";verticalSumOfBST();
	cout<<"\n\n42.Print Tree in Vertical Order Path\n";printTreeInVerticalOrderPath();
	cout<<"\n\n43.Print Nodes That Dont have Siblings\n";printNodesThatDontHaveSibilings();
	cout<<"\n\n44.Find Distance Of Node From Root\n";distanceOfNodeFromRoot();
	cout<<"\n\n45.Print All Nodes at Distance d from root\n";printAllNodesAtDistanceDFromRoot();
	cout<<"\n\n46.Distance between two nodes\n";distanceBetweenTwoNodes();
	cout<<"\n\n47.Maximum Sum From root to all leaf's\n";maxSumFromRootToAllLeaves();
	cout<<"\n\n48.Print All Nodes at Distance d from leaf\n";printAllNodesAtDistanceDFromLeaf();
	cout<<"\n\n49.Print BTree in zig-zag fashion\n";printBTreeInZigZag();
	cout<<"\n\n50.Print If Tree is SubTree of Tree\n";printTreeIsSubTreeOfATree();
	cout<<"\n\n51.Construct Binary Tree from inorder and postorder\n";bTreeFromInOrderPostOrder();
	cout<<"\n\n52.Construct Binary Tree from inorder and preorder\n";bTreeFromInOrderPreOrder();
	cout<<"\n\n53.Are two nodes sibilings to each other ?\n";isSibilings();
	cout<<"\n\n54.Are two nodes cousins to each other ?\n";isCousins();
	cout<<"\n\n55.Print next Sibilings of a node\n";printSibilingsOfNode();
	cout<<"\n\n56.Inorder without parent link\n";inOrderWithoutParent();
	cout<<"\n\n57.Convert Linked List to BST\n";linkedListToBST();
	cout<<"\n\n58.Convert Double Linked List to BST\n";doubleLinkedListToBST();
	cout<<"\n\n59.Convert Double Linked List to BST InPlace\n";doubleLinkedListToBSTInplace();
	cout<< "\n\n60.Convert BTree to Double Linked LIst\n"; btreeToDoubleLinkedList();
	cout<< "\n\n61.Ceil Of BST\n"; ceilInBST();
	cout<< "\n\n62.Floor Of BST\n"; floorInBST();
	cout<< "\n\n63.Kth Largest Element of BST\n"; kthLargestElement();
	cout<< "\n\n64.Kth Smallest Element of BST\n"; kthSmallestElement();
	cout<< "\n\n65.Recorret Swapped Nodes\n"; recorrectSwappedNodes();
	cout<< "\n\n66.Second Largest Node\n"; secondLargestNode();	
	cout<<"\n\n67.Deepest Node in BTree\n";deepestNodeInBTree();
	cout<<"\n\n68.Deepest Left Node in BTree\n";deepestLeftNodeInBTree();
	cout<<"\n\n69.Create Linked Lists of all node level\n";createLinkedListAtEachLevel();
	cout<<"\n\n70.Reverse Alternate levels of a BTree\n";reverseAlternateLevelsOfBtree();
	cout<<"\n\n71.Max Sum Between Any Two Leaves\n";maxSumBetweenAnyTwoLeaves();
    cout<<"\n\n72.Update Number of Left And Right Childs in a Tree\n";updateNumberOfLeftAndRightChilds();	
    cout<<"\n\n73.Update Left Min and Right Max of every node\n";updateLeftMinAndRightMax();		
	cout<<"\n\n74.Largest BST tree in Binary Tree\n";largestBSTTreeinBTree();
	cout<<"\n\n75.HeapSort\n";heapSort();
    cout<<"\n\n76.Merge K-Sorted Arrays\n";mergeKSortedArrays();	
	cout<<"\n\n77.AVL insertion\n";avlInsertion();
	cout<<"\n\n78.AVL deletion\n";avlDeletion();
 	cout<<endl;
}
