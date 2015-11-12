#include<stdio.h>
#include<stdlib.h>

//�A�����X�g�\����
typedef struct node {
	int data;
	struct node *left,*right;
}TREEEL;

//�m�[�h�̂͂���
TREEEL *root;

//�v���g�^�C�v�錾
void construct_tree();
void print_tree(int depth, TREEEL *p);
void insert_node(int num, TREEEL *p);
int delete_node(int num);

int main()
{
	//������
	int num;

	//�؂̏�����
	construct_tree();
	print_tree(0,root);

	//�f�[�^�}��
	printf("--- Insert Node ---\n");
	printf("Input insert Data >");
	scanf("%d", &num);
	insert_node(num,root);
	print_tree(0,root);

	//�f�[�^�폜
	printf("--- Delete Node ---\n");
	printf("Input delete Data >");
	scanf("%d", &num);
	delete_node(num);
	print_tree(0,root);

	return 0;
}

//�񕪖؂̍\�z
void construct_tree()
{
	//�ϐ�
	TREEEL *p,*q;
	int i,k,num, no_index[50];
	char buf[100];

	while(1)
	{
		printf("Input Data >");
		fgets(buf, sizeof(buf), stdin);

		//�����o��
		if(buf[0] == '\n') return;

		//���[�v�O������
		i=0;
		k=0;

		//1������
		if(buf[i] != ' ') no_index[k++] = i;

		//2�����ڈȍ~
		while(buf[i] != '\0')
		{
			i++;
			if(buf[i-1] == ' ' && buf[i] != ' ' && buf[i] != '\n') no_index[k++] = i;
		}

		//�G���[
		if(buf[i-1] != '\n')
		{
			printf("Error:Too long input data!\n");
			exit(1);
		}

		//�i�[�Ɩ؍\�z
		for(i=0; i<k; i++)
		{
			//�G���[����
			if(sscanf(&buf[ no_index[i] ], "%d", &num) != 1)
			{
				printf("Error:Non number input data!\n");
				continue;
			}

			/* �i�[ */
			//�����쐬���̏���
			if(i==0)
			{
				q = (TREEEL *)malloc( sizeof(TREEEL) );
				q->data = num;
				q->left = NULL;
				q->right = NULL;
				root = q;
			}
			//����ȍ~�̏���
			else
			{
				//�X�^�[�g�߂�
				p = root;

				//�~�����[�v
				while(p != NULL)
				{
					//���̂Ƃ�
					if(num < p->data)
					{
						//�~��鏈��
						if(p->left != NULL) p = p->left;
						//��������
						else
						{
							q = (TREEEL *)malloc( sizeof(TREEEL) );
							q->data = num;
							q->left = NULL;
							q->right = NULL;
							p->left = q;
							//�����o��
							break;
						}
					}
					//�E�̂Ƃ�
					else
					{
						//�~��鏈��
						if(p->right != NULL) p = p->right;
						//��������
						else
						{
							q = (TREEEL *)malloc( sizeof(TREEEL) );
							q->data = num;
							q->left = NULL;
							q->right = NULL;
							p->right = q;
							//�����o��
							break;
						}
					}
				}
			}
		}
	}
}

//�؃f�[�^�o��
void print_tree(int depth, TREEEL *p)
{
	//�؂̑��݊m�F
	if(p == NULL)return;

	//�\��
	print_tree(depth+1, p->right);
	for(int i=0; i< depth; i++) printf("//");
	printf("%4d\n",p->data);
	print_tree(depth+1, p->left);
}

//�f�[�^�}��
void insert_node(int num, TREEEL *p)
{
	TREEEL *q;

	//�G���[����
	if(p == NULL)
	{
		printf("Error:There is no data!\n");
		return;
	}

	//���̂Ƃ�(�������Ƃ�)
	if(num < p->data)
	{
		//��Ƀm�[�h�����݂���Ȃ�
		if(p->left != NULL) insert_node(num, p->left);
		//���݂��Ȃ��Ƃ�
		else
		{		
			//�m�[�h�쐬
			q = (TREEEL *)malloc( sizeof(TREEEL) );
			q->data = num;
			q->left = NULL;
			q->right = NULL;
			p->left = q;
		}
	}
	//�E�̂Ƃ�
	else
	{
		//��Ƀm�[�h�����݂���Ȃ�
		if(p->right != NULL) insert_node(num, p->right);
		//���݂��Ȃ��Ƃ�
		else
		{		
			//�m�[�h�쐬
			q = (TREEEL *)malloc( sizeof(TREEEL) );
			q->data = num;
			q->left = NULL;
			q->right = NULL;
			p->right = q;
		}
	}
}

//�f�[�^�폜
int delete_node(int num)
{
	//�ϐ��錾�Ə�����
	TREEEL *n, *p_n, *p;
	//�~�������t���O(true:��,false:�E)
	bool flag = true;
	n = root;
	p_n = NULL;

	//�؂��󂩊m�F
	if(n == NULL)
	{
		printf("Error:There is no data!\n");
		return -1;
	}

	//�f�[�^�{��
	while(n == NULL && n->data == num)
	{
		//�폜�������f�[�^����������
		if(n->data > num)
		{
			//�e��ۑ�
			p_n = n;
			//���ɍ~���
			n = n->left;
			//�����t���O
			flag = true;
		}
		//�폜�������f�[�^���傫����
		else
		{
			//�e��ۑ�
			p_n = n;
			//���ɍ~���
			n = n->right;
			//�����t���O
			flag = false;
		}
	}

	//������Ȃ�������
	if(n == NULL)
	{
		printf("Error:Serched data not found!\n");
		return -1;
	}

	//�������
	/* �폜 */
	//�q���Ȃ���
	if(n->left == NULL && n->right == NULL)
	{
		if(flag) p_n->left = NULL;
		else p_n->right = NULL;
	}
	//�q��2���鎞
	else if(n->left != NULL && n->right != NULL)
	{
		//1�񍶂ɍ~���
		p_n = p;
		p = p->left;
		//�E�ɍ~��Ă���
		while(p != NULL)
		{
			p_n = p;
			p = p->right;
		}

		//�f�[�^����ւ�
		n->data = p->data;
		//�폜
		p_n->right = NULL;
	}
	//�q��1�̎�
	else
	{
		/* �q�̕������� */
		//���Ɏq�����鎞
		if(n->right == NULL)
		{
			//�e�̍��̎�
			if(flag) p_n->left = n->left;
			//�e�̉E�̎�
			else p_n->right = n->left;
		}
		//�E�Ɏq�����鎞
		else
		{
			//�e�̍��̎�
			if(flag) p_n->left = n->right;
			//�e�̉E�̎�
			else p_n->right = n->right;
		}
	}

	return 1;
}