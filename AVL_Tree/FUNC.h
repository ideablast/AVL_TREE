#pragma once

#ifndef __FUNC_H__
#define __FUNC_H__

/*AVL_FUNCTION*/
Node *Create_new_AVL_node();
void Insert_AVL_node(Node* cur_top, int nData);
int Level_Check(Node* Cur_Parents_node);
int Search_depth(Node *top);
void Rotation_System(Node* Cur_Parents_node, int BF);
void Recursive_Rotation(Node* Cur_Parents_node, int BF);
/*SHAPE_DETECT*/

/*ROTATION*/
void Rotate_L(Node* Cur_Parents_node);
void Rotate_R(Node* Cur_Parents_node);
void Rotate_LL(Node* Cur_Parents_node);
void Rotate_RR(Node* Cur_Parents_node);
void Rotate_LR(Node* Cur_Parents_node);
void Rotate_RL(Node* Cur_Parents_node);

/*PRINT*/
void Print_Postorder(Node* top);


#endif

