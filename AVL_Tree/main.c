#include "ALL.h"

Node* Parents;
int main()
{
	Parents = Create_new_AVL_node();
	
	Insert_AVL_node(Parents, 10);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 15);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 20);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 25);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 30);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 21);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 19);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 17);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 18);
	Print_Postorder(Parents); puts("");
	
	//Rotate_LR(Parents);
	//Print_Postorder(Parents); puts("");
}

/*
Insert_AVL_node(Parents, 20);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 15);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 3);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 12);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 5);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 11);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 6);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 40);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 25);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 18);
	Print_Postorder(Parents); puts("");

	Insert_AVL_node(top, 60);
	Insert_AVL_node(top, 18);
	Insert_AVL_node(top, 71);
	Insert_AVL_node(top, 15);
	Insert_AVL_node(top, 59);
	Insert_AVL_node(top, 5);
	Insert_AVL_node(top, 42);
	Insert_AVL_node(top, 92);
	Insert_AVL_node(top, 19);
	Insert_AVL_node(top, 22);
	
	
	Insert_AVL_node(Parents, 20);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 15);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 3);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 12);
	Print_Postorder(Parents); puts("");
	Insert_AVL_node(Parents, 5);
	Print_Postorder(Parents); puts("");
	*/
