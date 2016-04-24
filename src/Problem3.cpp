/*
Given a Tree which consists of operands and operators ,Solve the Tree and return the result
The tree will have special nodes of type enode which will have 3 fields
data => String of 5 chars .which can be either a operator or operand 
If its a operator its values will be one of the 3 following strings "+" , "-" , "*".
If its a operand its values will be any number from -9999 to 99999 in its respective string format;
Left and Right pointers will point to either NULL or another enode
Only the leaf nodes will have operand values .

Example 1:
    +
   / \
  4   5 
The Result expression is : 4+5 ,Ans is 9

Example 2:
        *
       / \
      -   5
     / \
    7   2

The Result expression is : (7-2) * 5  ,Ans is 25

Example 3:
       +
     /   \
    *     -  
   / \   / \
  7   2  4  *
           / \
          2   1
  
The Result expression is : (7*2) + (4-(2*1)) =>14+2 =>16 ,Ans is 16 

Constraints : 
Total number of enodes will be <=20 for 50% of Test cases
Data value will only have "0"<=data<="99999" values for 50% of cases .
Data value for operators will have sign as first character and \0 as next character .

Input :
Root node of a Tree of type enode
Output :
Return Final answer or -1 for Null inputs

Note :
->Dont Create an Extra Array/String ,or else your solution would receive 20%-40% Cut in the Marks you got .

Difficulty : Medium
*/
#include <stdlib.h>;
#include <stdio.h>
int solve_tree_rec(struct enode *root);
//data can be accessed using root->data;
struct enode{
	char data[6];
	struct enode *left;
	struct enode *right;
};
int isOperator(char *);
int isOperand(char *);

/*
Helper Functions are optional to write 
*/
//Helper Functions Start
int isOperator(char *data){
	if (data==NULL)
	return 0;
	if (data[0] == '+' || data[0] == '-' || data[0] == '*')
		return 1;
	else return 0;
}
int isOperand(char *data){
	if (data==NULL)
	return 0;
	int i = 0;
	while (data[i] != NULL)
	{
		if (data[0] == '-'&&data[1] != '\0')
			i++;
		else if (data[i] >= 48 && data[i] <= 57)
			i++;
		else
			return 0;
	}
	return 1;
}
int getOperand(char *data){
	if (data==NULL)
	return 0;
	int i = 0,res=0;

	while (data[i] != '\0')
		i++;
	for (int j = i - 1; j >= 0; j--)
	{
		res = res * 10 + ((int)data[i] - 48);
	}
	return res;
}
//Helper Functions end
int solve_tree(struct enode *root){
	if (root==NULL)
    return -1;
	if (isOperator(root->data)==1)
	{
		if (isOperand(root->left->data) && isOperand(root->right->data)==1)
		{
			if (root->data == "+")
				return (getOperand(root->left->data) + getOperand(root->right->data));
			else if (root->data == "-")
				return (getOperand(root->left->data) - getOperand(root->right->data));
			else if (root->data == "*")
				return (getOperand(root->left->data) * getOperand(root->right->data));
		}

		int left_value = solve_tree_rec(root->left);
		int right_value = solve_tree_rec(root->right);
		if (root->data == "+")
			return left_value + right_value;
		else if (root->data == "-")
			return left_value - right_value;
		else if (root->data == "*")
			return left_value*right_value;
	}
	else
		return -1;


}
int solve_tree_rec(struct enode *root)
{
	
	if (root != NULL)
	{
		solve_tree_rec(root->left);
		if (isOperator(root->data))
		{
			int op1, op2;
			if (isOperand(root->left->data))
				op1 = getOperand(root->left->data);
			if (isOperand(root->right->data))
				op2= getOperand(root->right->data);
			if (root->data == "+")
				return op1 + op2;
			else if (root->data == "-")
				return op1 - op2;
			else if (root->data == "*")
				return op1*op2;
		}
		solve_tree_rec(root->right);
	}
}


