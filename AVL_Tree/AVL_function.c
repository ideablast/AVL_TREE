#include "ALL.h"
extern Node* Parents;

Node* Create_new_AVL_node()
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->Link = (Node**)malloc(NUM_OF_LINK * sizeof(Node*));

	temp->Link[0] = NULL;
	temp->Link[1] = NULL;

	temp->nData = 0;

	return temp;
}

//완전이진트리를 만들기 위한 회전
//AVL을 만들기 위한 회전

void Insert_AVL_node(Node* cur_top, int nData)
{
	Node* C_temp;
	int BF;

	if (cur_top)
	{
		if (cur_top->nData == 0)
		{
			cur_top->nData = nData;
			return;
		}
		else
		{
			if (cur_top->nData > nData)
			{
				if (cur_top->Link[0])
				{
					Insert_AVL_node(cur_top->Link[0], nData);
				}
				else
				{
					C_temp = Create_new_AVL_node();
					C_temp->nData = nData;
					cur_top->Link[0] = C_temp;
				}
			}
			else
			{
				if (cur_top->Link[1])
				{
					Insert_AVL_node(cur_top->Link[1], nData);
				}
				else
				{
					C_temp = Create_new_AVL_node();
					C_temp->nData = nData;
					cur_top->Link[1] = C_temp;
				}
			}
		}
		//재귀 끝나고 나왔을때 반영이 안되는 문제점 이것은 Parents노드와 관련된 지점들에 관해서만 일어나는 문제인가?
		
		BF = Level_Check(cur_top);
		if (BF == 2 || BF == -2)
			Recursive_Rotation(cur_top,  BF);
		else
			return;	
	}
}


int Search_depth(Node* top)
{
	int cnt = 0;

	if (top)
	{
		cnt = Search_depth(top->Link[0]) > Search_depth(top->Link[1]) ? Search_depth(top->Link[0]) : Search_depth(top->Link[1]);
		cnt += 1;
	}
	return cnt;
}

int Level_Check(Node* Cur_Parents_node)
{
	int Balance_Factor = Search_depth(Cur_Parents_node->Link[0]) - Search_depth(Cur_Parents_node->Link[1]);

	return Balance_Factor;
}

void Rotation_System(Node* Cur_Parents_node, int BF)
{
	Node* Check_Point_L = Cur_Parents_node->Link[0];
	Node* Check_Point_R = Cur_Parents_node->Link[1];
	int shape_factor;

	switch (BF)
	{
	case 2:
		shape_factor = Level_Check(Check_Point_L);
		if (shape_factor == 1) // LL
			Rotate_LL(Cur_Parents_node);
		else
			Rotate_LR(Cur_Parents_node);
		break;
	case -2:
		shape_factor = Level_Check(Check_Point_R);
		if (shape_factor == -1) // LL
			Rotate_RR(Cur_Parents_node);
		else
			Rotate_RL(Cur_Parents_node);
		break;
	}
}

void Recursive_Rotation(Node* Cur_Parents_node, int BF)
{
	Node* Check_Point_L = Cur_Parents_node->Link[0];
	Node* Check_Point_R = Cur_Parents_node->Link[1];
	int shape_factor;

	if (BF != 0)
	{
		switch (BF)
		{
		case 2:
			shape_factor = Level_Check(Check_Point_L);
			if (shape_factor == 1) // LL
				Rotate_LL(Cur_Parents_node);
			else
				Rotate_LR(Cur_Parents_node);
			break;
		case -2:
			shape_factor = Level_Check(Check_Point_R);
			if (shape_factor == -1) // LL
				Rotate_RR(Cur_Parents_node);
			else
				Rotate_RL(Cur_Parents_node);
			break;
		}
	}
	else
	{

	}
	
}

void Rotate_L(Node* Cur_Parents_node)
{
	int temp;
	Node* temp_node;

	if (Cur_Parents_node->Link[1])
	{
		temp = Cur_Parents_node->nData;
		Cur_Parents_node->nData = Cur_Parents_node->Link[1]->nData;
		Cur_Parents_node->Link[1]->nData = temp;

		temp_node = Cur_Parents_node->Link[1];
		Cur_Parents_node->Link[1] = NULL;

		if (Cur_Parents_node->Link[0])
		{
			if (temp_node->Link[1])
			{
				Cur_Parents_node->Link[1] = temp_node->Link[1];
				temp_node->Link[1] = NULL;
			}

			if (temp_node->Link[0])
			{
				temp_node->Link[1] = temp_node->Link[0];
				temp_node->Link[0] = NULL;
			}

			temp_node->Link[0] = Cur_Parents_node->Link[0];
			Cur_Parents_node->Link[0] = temp_node;
						
		}
		else
		{
			if (temp_node->Link[1])
			{
				Cur_Parents_node->Link[1] = temp_node->Link[1];
				temp_node->Link[1] = NULL;
			}
			else
				Cur_Parents_node->Link[1] = NULL;

			Cur_Parents_node->Link[0] = temp_node;
		}
	}
}

void Rotate_R(Node* Cur_Parents_node)
{

	int temp;
	Node* temp_node;

	if (Cur_Parents_node->Link[0])
	{
		temp = Cur_Parents_node->nData;
		Cur_Parents_node->nData = Cur_Parents_node->Link[0]->nData;
		Cur_Parents_node->Link[0]->nData = temp;


		temp_node = Cur_Parents_node->Link[0];
		Cur_Parents_node->Link[0] = NULL;

		if (Cur_Parents_node->Link[1])
		{
			if (temp_node->Link[0])
			{
				Cur_Parents_node->Link[0] = temp_node->Link[0];
				temp_node->Link[0] = NULL;
			}

			if (temp_node->Link[1])
			{
				temp_node->Link[0] = temp_node->Link[1];
				temp_node->Link[1] = NULL;
			}

			temp_node->Link[1] = Cur_Parents_node->Link[1];
			Cur_Parents_node->Link[1] = temp_node;

		}
		else
		{
			if (temp_node->Link[0])
			{
				Cur_Parents_node->Link[0] = temp_node->Link[0];
				temp_node->Link[0] = NULL;
			}
			else
				Cur_Parents_node->Link[0] = NULL;

			Cur_Parents_node->Link[1] = temp_node;
		}

	}
}

void Rotate_LL(Node* Cur_Parents_node)//LL모양을 균형 잡힌 트리로 만드는 회전
{
	Rotate_R(Cur_Parents_node);
}

void Rotate_RR(Node* Cur_Parents_node)
{
	Rotate_L(Cur_Parents_node);
}

void Rotate_LR(Node* Cur_Parents_node)//LL모양을 균형 잡힌 트리로 만드는 회전
{
	Rotate_L(Cur_Parents_node->Link[0]);
	Rotate_R(Cur_Parents_node);
}

void Rotate_RL(Node* Cur_Parents_node)
{
	Rotate_R(Cur_Parents_node->Link[1]);
	Rotate_L(Cur_Parents_node);
}

void Print_Postorder(Node* top)
{
	if (top)
	{
		Print_Postorder(top->Link[0]);
		Print_Postorder(top->Link[1]);
		printf("%d ", top->nData);
	}
}
/*



			if (Cur_Parents_node->Link[0]->Link[0])
			{
				Cur_Parents_node->Link[0]->Link[0]->Link[0] = temp_node;
				temp = temp_node->nData;
				temp_node->nData = Cur_Parents_node->Link[0]->Link[0]->nData;
				Cur_Parents_node->Link[0]->Link[0]->nData = Cur_Parents_node->Link[0]->nData;
				Cur_Parents_node->Link[0]->nData = temp;
			}
			else
			{
				Cur_Parents_node->Link[0]->Link[0] = temp_node;
				temp = Cur_Parents_node->Link[0]->nData;
				Cur_Parents_node->Link[0]->nData = Cur_Parents_node->Link[0]->Link[0]->nData;
				Cur_Parents_node->Link[0]->Link[0]->nData = temp;
			}
Node* Create_new_AVL_node()
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->Link = (Node**)malloc(NUM_OF_LINK * sizeof(Node*));

	temp->Link[0] = NULL;
	temp->Link[1] = NULL;

	temp->nData = 0;

	return temp;
}

//완전이진트리를 만들기 위한 회전
//AVL을 만들기 위한 회전

void Insert_AVL_node(Node* cur_top, int nData)
{
	Node* C_temp;
	Node* R_temp;
	int BF;

	if (cur_top)
	{
		if (cur_top->nData == 0)
		{
			cur_top->nData = nData;
			return;
		}
		else
		{
			if (cur_top->nData > nData)
			{
				if (cur_top->Link[0])
				{
					Insert_AVL_node(cur_top->Link[0], nData);
				}
				else
				{
					C_temp = Create_new_AVL_node();
					C_temp->nData = nData;
					cur_top->Link[0] = C_temp;
				}
				//재귀 끝나고 나왔을때 반영이 안되는 문제점 이것은 Parents노드와 관련된 지점들에 관해서만 일어나는 문제인가?
				BF = Level_Check(cur_top);
				if (BF == 2 || BF == -2)
				{
					R_temp = Rotation_System(cur_top, Detect_Shape(cur_top, BF));
					if (cur_top == Parents)
					{
						memcpy(Parents, R_temp, _msize(R_temp));

					}
					else
					{
						cur_top->nData = R_temp->nData;
						cur_top->Link[0] = R_temp->Link[0];
						cur_top->Link[1] = R_temp->Link[1];
					}

				}
				else
					return;


			}
			else
			{
				if (cur_top->Link[1])
				{
					Insert_AVL_node(cur_top->Link[1], nData);
				}
				else
				{
					C_temp = Create_new_AVL_node();
					C_temp->nData = nData;
					cur_top->Link[1] = C_temp;
				}

				BF = Level_Check(cur_top);
				if (BF == 2 || BF == -2)
				{
					R_temp = Rotation_System(cur_top, Detect_Shape(cur_top, BF));
					if (cur_top == Parents)
					{
						Parents->nData = R_temp->nData;
						Parents->Link[0] = R_temp->Link[0];
						Parents->Link[1] = R_temp->Link[1];
					}
					else
					{
						cur_top->nData = R_temp->nData;
						cur_top->Link[0] = R_temp->Link[0];
						cur_top->Link[1] = R_temp->Link[1];
					}
				}
				else
					return;
			}
		}
	}

}

int Search_depth(Node* top)
{
	int cnt = 0;

	if (top)
	{
		cnt = Search_depth(top->Link[0]) > Search_depth(top->Link[1]) ? Search_depth(top->Link[0]) : Search_depth(top->Link[1]);
		cnt += 1;
	}
	return cnt;
}

int Level_Check(Node* Cur_Parents_node)
{
	int Balance_Factor = Search_depth(Cur_Parents_node->Link[0]) - Search_depth(Cur_Parents_node->Link[1]);

	return Balance_Factor;
}

int Detect_Shape(Node* Cur_Parents_node, int BF)
{
	Node* Check_Point_L = Cur_Parents_node->Link[0];
	Node* Check_Point_R = Cur_Parents_node->Link[1];

	int result = 0;

	switch (BF)
	{
	case 2:
		if (Level_Check(Check_Point_L) == 1)
			result = LL;
		else
			result = LR;
		break;
	case -2:
		if (Level_Check(Check_Point_R) == -1)
			result = RR;
		else
			result = RL;
		break;
	case 1:
		if (Level_Check(Check_Point_L) == 1)
			result = CBT_LL;
		else
			result = CBT_LR;
		break;
	case -1:
		if (Level_Check(Check_Point_R) == -1)
			result = CBT_RR;
		else
			result = CBT_RL;
		break;
	}

	return result;
}

Node* Rotation_System(Node* Cur_Parents_node, int shape)
{
	switch (shape)
	{
	case LL:
		Cur_Parents_node = Rotate_LL(Cur_Parents_node);
		break;
	case LR:
		Cur_Parents_node = Rotate_LR(Cur_Parents_node);
		break;
	case RL:
		Cur_Parents_node = Rotate_RL(Cur_Parents_node);
		break;
	case RR:
		Cur_Parents_node = Rotate_RR(Cur_Parents_node);
		break;
	case CBT_LL:
		break;
	case CBT_LR:
		Rotate_L(Cur_Parents_node->Link[0]);
		break;
	case CBT_RL:
		Rotate_R(Cur_Parents_node->Link[1]);
		Cur_Parents_node = Rotate_RR(Cur_Parents_node);
		break;
	case CBT_RR:
		Cur_Parents_node = Rotate_RR(Cur_Parents_node);
		break;

	}

	return Cur_Parents_node;
}

void Rotate_L(Node* Cur_Parents_node)
{
	int temp;
	Cur_Parents_node->Link[0] = Cur_Parents_node->Link[1];
	Cur_Parents_node->Link[1] = NULL;

	temp = Cur_Parents_node->nData;
	Cur_Parents_node->nData = Cur_Parents_node->Link[0]->nData;
	Cur_Parents_node->Link[0]->nData = temp;
}

void Rotate_R(Node* Cur_Parents_node)
{
	int temp;
	Cur_Parents_node->Link[1] = Cur_Parents_node->Link[0];
	Cur_Parents_node->Link[0] = NULL;

	temp = Cur_Parents_node->nData;
	Cur_Parents_node->nData = Cur_Parents_node->Link[1]->nData;
	Cur_Parents_node->Link[1]->nData = temp;
}

Node* Rotate_LL(Node* Cur_Parents_node)//LL모양을 균형 잡힌 트리로 만드는 회전
{
	Node* New_Parents_node = Cur_Parents_node->Link[0];

	New_Parents_node->Link[1] = Cur_Parents_node;
	Cur_Parents_node->Link[0] = NULL;
	Cur_Parents_node = New_Parents_node;

	return Cur_Parents_node;
}


Node* Rotate_RR(Node* Cur_Parents_node)
{
	Node* New_Parents_node = Cur_Parents_node->Link[1];

	New_Parents_node->Link[0] = Cur_Parents_node;
	Cur_Parents_node->Link[1] = NULL;
	Cur_Parents_node = New_Parents_node;

	return Cur_Parents_node;
}

Node* Rotate_LR(Node* Cur_Parents_node)//LL모양을 균형 잡힌 트리로 만드는 회전
{

	Node* New_Parents_node = Cur_Parents_node->Link[0];
	int temp;

	New_Parents_node->Link[0] = New_Parents_node->Link[1];
	New_Parents_node->Link[1] = NULL;

	temp = New_Parents_node->nData;
	New_Parents_node->nData = New_Parents_node->Link[0]->nData;
	New_Parents_node->Link[0]->nData = temp;

	New_Parents_node->Link[1] = Cur_Parents_node;
	Cur_Parents_node->Link[0] = NULL;
	Cur_Parents_node = New_Parents_node;

	return Cur_Parents_node;
}

Node* Rotate_RL(Node* Cur_Parents_node)
{
	Node* New_Parents_node = Cur_Parents_node->Link[1];
	int temp;

	New_Parents_node->Link[1] = New_Parents_node->Link[0];
	New_Parents_node->Link[0] = NULL;

	temp = New_Parents_node->nData;
	New_Parents_node->nData = New_Parents_node->Link[1]->nData;
	New_Parents_node->Link[1]->nData = temp;

	New_Parents_node->Link[0] = Cur_Parents_node;
	Cur_Parents_node->Link[1] = NULL;
	Cur_Parents_node = New_Parents_node;

	return Cur_Parents_node;
}


void Print_Postorder(Node* top)
{
	if (top)
	{
		Print_Postorder(top->Link[0]);
		Print_Postorder(top->Link[1]);
		printf("%d ", top->nData);
	}
}
int Detect_Shape(Node* Cur_Parents_node, int level_check)
{
	Node* Check_Point_L = Cur_Parents_node->Link[0];
	Node* Check_Point_R = Cur_Parents_node->Link[1];

	int result;

	switch (level_check)
	{
	case 2:
		if (Check_Point_L->Link[0])
			result = LL;
		else if (Check_Point_L->Link[1])
			result = LR;
		break;
	case -2:
		if (Check_Point_R->Link[1])
			result = RR;
		else if (Check_Point_R->Link[0])
			result = RL;
		break;
	case 1:
		if (Check_Point_L->Link[0])
			result = CBT_LL;
		else if (Check_Point_L->Link[1])
			result = CBT_LR;
		break;
	case -1:
		if (Check_Point_R->Link[1])
			result = CBT_RR;
		else if (Check_Point_R->Link[0])
			result = CBT_RL;
		break;
	}

	return result;
}


if (top == cur_top)
{
	temp_top = Rotation_System(cur_top, Detect_Shape(cur_top, Level_Check(cur_top)));
	top->nData = temp_top->nData;
	top->Link[0] = temp_top->Link[0];
	top->Link[1] = temp_top->Link[1];
}
else

if (top == cur_top)
{
	temp_top = Rotation_System(cur_top, Detect_Shape(cur_top, Level_Check(cur_top)));
	top->nData = temp_top->nData;
	top->Link[0] = temp_top->Link[0];
	top->Link[1] = temp_top->Link[1];
}
else



Node* Create_new_AVL_node()
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->Link = (Node**)malloc(NUM_OF_LINK * sizeof(Node*));

	temp->Link[0] = NULL;
	temp->Link[1] = NULL;

	temp->nData = 0;

	return temp;
}

//완전이진트리를 만들기 위한 회전
//AVL을 만들기 위한 회전

void Insert_AVL_node(Node* cur_top, int nData)
{
	Node* C_temp;
	int BF;

	if (cur_top)
	{
		if (cur_top->nData == 0)
		{
			cur_top->nData = nData;
			return;
		}
		else
		{
			if (cur_top->nData > nData)
			{
				if (cur_top->Link[0])
				{
					Insert_AVL_node(cur_top->Link[0], nData);
				}
				else
				{
					C_temp = Create_new_AVL_node();
					C_temp->nData = nData;
					cur_top->Link[0] = C_temp;
				}
			}
			else
			{
				if (cur_top->Link[1])
				{
					Insert_AVL_node(cur_top->Link[1], nData);
				}
				else
				{
					C_temp = Create_new_AVL_node();
					C_temp->nData = nData;
					cur_top->Link[1] = C_temp;
				}
			}
		}
		//재귀 끝나고 나왔을때 반영이 안되는 문제점 이것은 Parents노드와 관련된 지점들에 관해서만 일어나는 문제인가?

		BF = Level_Check(cur_top);
		if (BF == 2 || BF == -2)
			Rotation_System(cur_top, Detect_Shape(cur_top, BF));
		else
			return;
	}
}


int Search_depth(Node* top)
{
	int cnt = 0;

	if (top)
	{
		cnt = Search_depth(top->Link[0]) > Search_depth(top->Link[1]) ? Search_depth(top->Link[0]) : Search_depth(top->Link[1]);
		cnt += 1;
	}
	return cnt;
}

int Level_Check(Node* Cur_Parents_node)
{
	int Balance_Factor = Search_depth(Cur_Parents_node->Link[0]) - Search_depth(Cur_Parents_node->Link[1]);

	return Balance_Factor;
}

int Detect_Shape(Node* Cur_Parents_node, int BF)
{
	Node* Check_Point_L = Cur_Parents_node->Link[0];
	Node* Check_Point_R = Cur_Parents_node->Link[1];

	int result = 0;

	switch (BF)
	{
	case 2:
		if(Level_Check(Check_Point_L) == 1)
			result = LL;
		else
			result = LR;
		break;
	case -2:
		if (Level_Check(Check_Point_R) == -1)
			result = RR;
		else
			result = RL;
		break;
	case 1:
		if (Level_Check(Check_Point_L) == 1)
			result = CBT_LL;
		else
			result = CBT_LR;
		break;
	case -1:
		if (Level_Check(Check_Point_R) == -1)
			result = CBT_RR;
		else
			result = CBT_RL;
		break;
	}

	return result;
}

void Rotation_System(Node* Cur_Parents_node, int shape)
{
	switch (shape)
	{
	case LL:
		 Rotate_LL(Cur_Parents_node);
		break;
	case LR:
		 Rotate_LR(Cur_Parents_node);
		break;
	case RL:
		Rotate_RL(Cur_Parents_node);
		break;
	case RR:
		 Rotate_RR(Cur_Parents_node);
		break;
		case CBT_LL:
		break;
	case CBT_LR:
		Rotate_L(Cur_Parents_node->Link[0]);
		break;
	case CBT_RL:
		Rotate_R(Cur_Parents_node->Link[1]);
		Rotate_RR(Cur_Parents_node);
		break;
	case CBT_RR:
		Rotate_RR(Cur_Parents_node);
		break;

	}
}

void Rotate_L(Node* Cur_Parents_node)
{
	int temp;
	Cur_Parents_node->Link[0] = Cur_Parents_node->Link[1];
	Cur_Parents_node->Link[1] = NULL;

	temp = Cur_Parents_node->nData;
	Cur_Parents_node->nData = Cur_Parents_node->Link[0]->nData;
	Cur_Parents_node->Link[0]->nData = temp;
}

void Rotate_R(Node* Cur_Parents_node)
{
	int temp;
	Cur_Parents_node->Link[1] = Cur_Parents_node->Link[0];
	Cur_Parents_node->Link[0] = NULL;

	temp = Cur_Parents_node->nData;
	Cur_Parents_node->nData = Cur_Parents_node->Link[1]->nData;
	Cur_Parents_node->Link[1]->nData = temp;
}

Node* Rotate_LL(Node* Cur_Parents_node)//LL모양을 균형 잡힌 트리로 만드는 회전
{
	int temp;
	Node* New_Parents_node = Cur_Parents_node->Link[0];

	if (Cur_Parents_node == Parents)
	{
		temp = Cur_Parents_node->nData;
		Cur_Parents_node->nData = Cur_Parents_node->Link[0]->nData;
		Cur_Parents_node->Link[0]->nData = Cur_Parents_node->Link[0]->Link[0]->nData;
		Cur_Parents_node->Link[0]->Link[0]->nData = temp;

		Cur_Parents_node->Link[1] = Cur_Parents_node->Link[0]->Link[0];
		Cur_Parents_node->Link[0]->Link[0] = NULL;
	}
	else
	{
		New_Parents_node->Link[1] = Cur_Parents_node;
		Cur_Parents_node->Link[0] = NULL;
		Cur_Parents_node = New_Parents_node;
	}
}


Node* Rotate_RR(Node* Cur_Parents_node)
{
	int temp;
	Node* New_Parents_node = Cur_Parents_node->Link[1];

	if (Cur_Parents_node == Parents)
	{
		temp = Cur_Parents_node->nData;
		Cur_Parents_node->nData = Cur_Parents_node->Link[1]->nData;
		Cur_Parents_node->Link[1]->nData = Cur_Parents_node->Link[1]->Link[1]->nData;
		Cur_Parents_node->Link[1]->Link[1]->nData = temp;

		Cur_Parents_node->Link[0] = Cur_Parents_node->Link[1]->Link[1];
		Cur_Parents_node->Link[1]->Link[1] = NULL;
	}
	else
	{
		New_Parents_node->Link[0] = Cur_Parents_node;
		Cur_Parents_node->Link[1] = NULL;
		Cur_Parents_node = New_Parents_node;
	}

}

void Rotate_LR(Node* Cur_Parents_node)//LL모양을 균형 잡힌 트리로 만드는 회전
{
	Node* New_Parents_node = Cur_Parents_node->Link[0];

	Rotate_L(New_Parents_node);
	//Rotate_LL(Cur_Parents_node);
}

void Rotate_RL(Node* Cur_Parents_node)
{
	Node* New_Parents_node = Cur_Parents_node->Link[1];

	Rotate_R(New_Parents_node);
	//Rotate_RR(Cur_Parents_node);
}


void Print_Postorder(Node* top)
{
	if (top)
	{
		Print_Postorder(top->Link[0]);
		Print_Postorder(top->Link[1]);
		printf("%d ", top->nData);
	}
}
Node* Create_new_AVL_node()
{
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->Link = (Node**)malloc(NUM_OF_LINK * sizeof(Node*));

	temp->Link[0] = NULL;
	temp->Link[1] = NULL;

	temp->nData = 0;

	return temp;
}

//완전이진트리를 만들기 위한 회전
//AVL을 만들기 위한 회전

void Insert_AVL_node(Node* cur_top, int nData)
{
	Node* C_temp;
	Node* R_temp;
	int BF;

	if (cur_top)
	{
		if (cur_top->nData == 0)
		{
			cur_top->nData = nData;
			return;
		}
		else
		{
			if (cur_top->nData > nData)
			{
				if (cur_top->Link[0])
				{
					Insert_AVL_node(cur_top->Link[0], nData);
				}
				else
				{
					C_temp = Create_new_AVL_node();
					C_temp->nData = nData;
					cur_top->Link[0] = C_temp;
				}
				//재귀 끝나고 나왔을때 반영이 안되는 문제점 이것은 Parents노드와 관련된 지점들에 관해서만 일어나는 문제인가?
				BF = Level_Check(cur_top);
				if (BF == 2 || BF == -2)
				{
					R_temp = Rotation_System(cur_top, Detect_Shape(cur_top, BF));
					if (cur_top == Parents)
					{
						memcpy(Parents, R_temp, _msize(R_temp));

					}
					else
					{
						cur_top->nData = R_temp->nData;
						cur_top->Link[0] = R_temp->Link[0];
						cur_top->Link[1] = R_temp->Link[1];
					}

				}
				else
					return;


			}
			else
			{
				if (cur_top->Link[1])
				{
					Insert_AVL_node(cur_top->Link[1], nData);
				}
				else
				{
					C_temp = Create_new_AVL_node();
					C_temp->nData = nData;
					cur_top->Link[1] = C_temp;
				}

				BF = Level_Check(cur_top);
				if (BF == 2 || BF == -2)
				{
					R_temp = Rotation_System(cur_top, Detect_Shape(cur_top, BF));
					if (cur_top == Parents)
					{
						Parents->nData = R_temp->nData;
						Parents->Link[0] = R_temp->Link[0];
						Parents->Link[1] = R_temp->Link[1];
					}
					else
					{
						cur_top->nData = R_temp->nData;
						cur_top->Link[0] = R_temp->Link[0];
						cur_top->Link[1] = R_temp->Link[1];
					}

				}
				else
					return;
			}
		}
	}

}

int Search_depth(Node* top)
{
	int cnt = 0;

	if (top)
	{
		cnt = Search_depth(top->Link[0]) > Search_depth(top->Link[1]) ? Search_depth(top->Link[0]) : Search_depth(top->Link[1]);
		cnt += 1;
	}
	return cnt;
}

int Level_Check(Node* Cur_Parents_node)
{
	int Balance_Factor = Search_depth(Cur_Parents_node->Link[0]) - Search_depth(Cur_Parents_node->Link[1]);

	return Balance_Factor;
}

int Detect_Shape(Node* Cur_Parents_node, int BF)
{
	Node* Check_Point_L = Cur_Parents_node->Link[0];
	Node* Check_Point_R = Cur_Parents_node->Link[1];

	int result = 0;

	switch (BF)
	{
	case 2:
		if(Level_Check(Check_Point_L) == 1)
			result = LL;
		else
			result = LR;
		break;
	case -2:
		if (Level_Check(Check_Point_R) == -1)
			result = RR;
		else
			result = RL;
		break;
	case 1:
		if (Level_Check(Check_Point_L) == 1)
			result = CBT_LL;
		else
			result = CBT_LR;
		break;
	case -1:
		if (Level_Check(Check_Point_R) == -1)
			result = CBT_RR;
		else
			result = CBT_RL;
		break;
	}

	return result;
}

Node* Rotation_System(Node* Cur_Parents_node, int shape)
{
	switch (shape)
	{
	case LL:
		Cur_Parents_node = Rotate_LL(Cur_Parents_node);
		break;
	case LR:
		Cur_Parents_node = Rotate_LR(Cur_Parents_node);
		break;
	case RL:
		Cur_Parents_node = Rotate_RL(Cur_Parents_node);
		break;
	case RR:
		Cur_Parents_node = Rotate_RR(Cur_Parents_node);
		break;
		case CBT_LL:
		break;
	case CBT_LR:
		Rotate_L(Cur_Parents_node->Link[0]);
		break;
	case CBT_RL:
		Rotate_R(Cur_Parents_node->Link[1]);
		Cur_Parents_node = Rotate_RR(Cur_Parents_node);
		break;
	case CBT_RR:
		Cur_Parents_node = Rotate_RR(Cur_Parents_node);
		break;

	}

	return Cur_Parents_node;
}

void Rotate_L(Node* Cur_Parents_node)
{
	int temp;
	Cur_Parents_node->Link[0] = Cur_Parents_node->Link[1];
	Cur_Parents_node->Link[1] = NULL;

	temp = Cur_Parents_node->nData;
	Cur_Parents_node->nData = Cur_Parents_node->Link[0]->nData;
	Cur_Parents_node->Link[0]->nData = temp;
}

void Rotate_R(Node* Cur_Parents_node)
{
	int temp;
	Cur_Parents_node->Link[1] = Cur_Parents_node->Link[0];
	Cur_Parents_node->Link[0] = NULL;

	temp = Cur_Parents_node->nData;
	Cur_Parents_node->nData = Cur_Parents_node->Link[1]->nData;
	Cur_Parents_node->Link[1]->nData = temp;
}

Node* Rotate_LL(Node* Cur_Parents_node)//LL모양을 균형 잡힌 트리로 만드는 회전
{
	Node* New_Parents_node = Cur_Parents_node->Link[0];

	New_Parents_node->Link[1] = Cur_Parents_node;
	Cur_Parents_node->Link[0] = NULL;
	Cur_Parents_node = New_Parents_node;

	return Cur_Parents_node;
}


Node* Rotate_RR(Node* Cur_Parents_node)
{
	Node* New_Parents_node = Cur_Parents_node->Link[1];

	New_Parents_node->Link[0] = Cur_Parents_node;
	Cur_Parents_node->Link[1] = NULL;
	Cur_Parents_node = New_Parents_node;

	return Cur_Parents_node;
}

Node* Rotate_LR(Node* Cur_Parents_node)//LL모양을 균형 잡힌 트리로 만드는 회전
{

	Node* New_Parents_node = Cur_Parents_node->Link[0];
	int temp;

	New_Parents_node->Link[0] = New_Parents_node->Link[1];
	New_Parents_node->Link[1] = NULL;

	temp = New_Parents_node->nData;
	New_Parents_node->nData = New_Parents_node->Link[0]->nData;
	New_Parents_node->Link[0]->nData = temp;

	New_Parents_node->Link[1] = Cur_Parents_node;
	Cur_Parents_node->Link[0] = NULL;
	Cur_Parents_node = New_Parents_node;

	return Cur_Parents_node;
}

Node* Rotate_RL(Node* Cur_Parents_node)
{
	Node* New_Parents_node = Cur_Parents_node->Link[1];
	int temp;

	New_Parents_node->Link[1] = New_Parents_node->Link[0];
	New_Parents_node->Link[0] = NULL;

	temp = New_Parents_node->nData;
	New_Parents_node->nData = New_Parents_node->Link[1]->nData;
	New_Parents_node->Link[1]->nData = temp;

	New_Parents_node->Link[0] = Cur_Parents_node;
	Cur_Parents_node->Link[1] = NULL;
	Cur_Parents_node = New_Parents_node;

	return Cur_Parents_node;
}


void Print_Postorder(Node* top)
{
	if (top)
	{
		Print_Postorder(top->Link[0]);
		Print_Postorder(top->Link[1]);
		printf("%d ", top->nData);
	}
}


int Detect_Shape(Node* Cur_Parents_node, int level_check)
{
	Node* Check_Point_L = Cur_Parents_node->Link[0];
	Node* Check_Point_R = Cur_Parents_node->Link[1];

	int result;

	switch (level_check)
	{
	case 2:
		if (Check_Point_L->Link[0])
			result = LL;
		else if (Check_Point_L->Link[1])
			result = LR;
		break;
	case -2:
		if (Check_Point_R->Link[1])
			result = RR;
		else if (Check_Point_R->Link[0])
			result = RL;
		break;
	case 1:
		if (Check_Point_L->Link[0])
			result = CBT_LL;
		else if (Check_Point_L->Link[1])
			result = CBT_LR;
		break;
	case -1:
		if (Check_Point_R->Link[1])
			result = CBT_RR;
		else if (Check_Point_R->Link[0])
			result = CBT_RL;
		break;
	}

	return result;
}


if (top == cur_top)
						{
							temp_top = Rotation_System(cur_top, Detect_Shape(cur_top, Level_Check(cur_top)));
							top->nData = temp_top->nData;
							top->Link[0] = temp_top->Link[0];
							top->Link[1] = temp_top->Link[1];
						}
						else

						if (top == cur_top)
						{
							temp_top = Rotation_System(cur_top, Detect_Shape(cur_top, Level_Check(cur_top)));
							top->nData = temp_top->nData;
							top->Link[0] = temp_top->Link[0];
							top->Link[1] = temp_top->Link[1];
						}
						else

*/
/*
void Insert_AVL_node(Node* top, int nData)
{
	Node* temp;

	if (top)
	{
		if (top->nData == 0)
		{
			top->nData = nData;
			return;
		}
		else
		{

			if (top->nData > nData)
			{
				if (top->Link[0])
				{
					Insert_AVL_node(top->Link[0], nData);
					if (Level_Check(top) == 2||Level_Check(top) == -2)
						top = Rotation_System(top, Detect_Shape(top, Level_Check(top)));

				}
				else
				{
					temp = Create_new_AVL_node();
					temp->nData = nData;
					top->Link[0] = temp;
					return;
				}
			}
			else
			{
				if (top->Link[1])
				{
					Insert_AVL_node(top->Link[1], nData);
					if (Level_Check(top) == 2 || Level_Check(top) == -2)
						top = Rotation_System(top, Detect_Shape(top, Level_Check(top)));
				}
				else
				{
					temp = Create_new_AVL_node();
					temp->nData = nData;
					top->Link[1] = temp;
					return;
				}
			}

		}
	}
}


void Insert_AVL_node(Node* top, int nData)
{
	Node* temp;

	if (top)
	{
		if (top->nData == 0)
		{
			top->nData = nData;
			return;
		}
		else
		{
			if (top->nData > nData)
			{
				if (top->Link[0])
					Insert_AVL_node(top->Link[0], nData);
				else
				{
					temp = Create_new_AVL_node();
					temp->nData = nData;
					top->Link[0] = temp;
					return;
				}
			}
			else
			{
				if (top->Link[1])
					Insert_AVL_node(top->Link[1], nData);
				else
				{
					temp = Create_new_AVL_node();
					temp->nData = nData;
					top->Link[1] = temp;
					return;
				}
			}

		}
	}
}
*/