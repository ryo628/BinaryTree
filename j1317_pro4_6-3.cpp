#include<stdio.h>
#include<stdlib.h>

//連結リスト構造体
typedef struct node {
	int data;
	struct node *left,*right;
}TREEEL;

//ノードのはじめ
TREEEL *root;

//プロトタイプ宣言
void construct_tree();
void print_tree(int depth, TREEEL *p);
void insert_node(int num, TREEEL *p);
int delete_node(int num);

int main()
{
	//初期化
	int num;

	//木の初期化
	construct_tree();
	print_tree(0,root);

	//データ挿入
	printf("--- Insert Node ---\n");
	printf("Input insert Data >");
	scanf("%d", &num);
	insert_node(num,root);
	print_tree(0,root);

	//データ削除
	printf("--- Delete Node ---\n");
	printf("Input delete Data >");
	scanf("%d", &num);
	delete_node(num);
	print_tree(0,root);

	return 0;
}

//二分木の構築
void construct_tree()
{
	//変数
	TREEEL *p,*q;
	int i,k,num, no_index[50];
	char buf[100];

	while(1)
	{
		printf("Input Data >");
		fgets(buf, sizeof(buf), stdin);

		//抜け出し
		if(buf[0] == '\n') return;

		//ループ前初期化
		i=0;
		k=0;

		//1文字目
		if(buf[i] != ' ') no_index[k++] = i;

		//2文字目以降
		while(buf[i] != '\0')
		{
			i++;
			if(buf[i-1] == ' ' && buf[i] != ' ' && buf[i] != '\n') no_index[k++] = i;
		}

		//エラー
		if(buf[i-1] != '\n')
		{
			printf("Error:Too long input data!\n");
			exit(1);
		}

		//格納と木構築
		for(i=0; i<k; i++)
		{
			//エラー処理
			if(sscanf(&buf[ no_index[i] ], "%d", &num) != 1)
			{
				printf("Error:Non number input data!\n");
				continue;
			}

			/* 格納 */
			//根を作成時の処理
			if(i==0)
			{
				q = (TREEEL *)malloc( sizeof(TREEEL) );
				q->data = num;
				q->left = NULL;
				q->right = NULL;
				root = q;
			}
			//それ以降の処理
			else
			{
				//スタート戻し
				p = root;

				//降下ループ
				while(p != NULL)
				{
					//左のとき
					if(num < p->data)
					{
						//降りる処理
						if(p->left != NULL) p = p->left;
						//書き込み
						else
						{
							q = (TREEEL *)malloc( sizeof(TREEEL) );
							q->data = num;
							q->left = NULL;
							q->right = NULL;
							p->left = q;
							//抜け出し
							break;
						}
					}
					//右のとき
					else
					{
						//降りる処理
						if(p->right != NULL) p = p->right;
						//書き込み
						else
						{
							q = (TREEEL *)malloc( sizeof(TREEEL) );
							q->data = num;
							q->left = NULL;
							q->right = NULL;
							p->right = q;
							//抜け出し
							break;
						}
					}
				}
			}
		}
	}
}

//木データ出力
void print_tree(int depth, TREEEL *p)
{
	//木の存在確認
	if(p == NULL)return;

	//表示
	print_tree(depth+1, p->right);
	for(int i=0; i< depth; i++) printf("//");
	printf("%4d\n",p->data);
	print_tree(depth+1, p->left);
}

//データ挿入
void insert_node(int num, TREEEL *p)
{
	TREEEL *q;

	//エラー処理
	if(p == NULL)
	{
		printf("Error:There is no data!\n");
		return;
	}

	//左のとき(小さいとき)
	if(num < p->data)
	{
		//先にノードが存在するなら
		if(p->left != NULL) insert_node(num, p->left);
		//存在しないとき
		else
		{		
			//ノード作成
			q = (TREEEL *)malloc( sizeof(TREEEL) );
			q->data = num;
			q->left = NULL;
			q->right = NULL;
			p->left = q;
		}
	}
	//右のとき
	else
	{
		//先にノードが存在するなら
		if(p->right != NULL) insert_node(num, p->right);
		//存在しないとき
		else
		{		
			//ノード作成
			q = (TREEEL *)malloc( sizeof(TREEEL) );
			q->data = num;
			q->left = NULL;
			q->right = NULL;
			p->right = q;
		}
	}
}

//データ削除
int delete_node(int num)
{
	//変数宣言と初期化
	TREEEL *n, *p_n, *p;
	//降りる方向フラグ(true:左,false:右)
	bool flag = true;
	n = root;
	p_n = NULL;

	//木が空か確認
	if(n == NULL)
	{
		printf("Error:There is no data!\n");
		return -1;
	}

	//データ捜索
	while(n != NULL && n->data != num)
	{
		//削除したいデータが小さい時
		if(n->data > num)
		{
			//親を保存
			p_n = n;
			//左に降りる
			n = n->left;
			//方向フラグ
			flag = true;
		}
		//削除したいデータが大きい時
		else
		{
			//親を保存
			p_n = n;
			//左に降りる
			n = n->right;
			//方向フラグ
			flag = false;
		}
	}

	//見つからなかった時
	if(n == NULL)
	{
		printf("Error:Serched data not found!\n");
		return -1;
	}

	/* 削除 */
	//子がない時
	if(n->left == NULL && n->right == NULL)
	{
		if (flag) p_n->left = NULL;
		else p_n->right = NULL;
	}
	//子が2つある時
	else if(n->left != NULL && n->right != NULL)
	{
		//1回左に降りる
		p_n = p;
		p = n->left;
		//右に降りていく
		while (p->right != NULL)
		{
			p_n = p;
			p = p->right;
		}

		//データ入れ替え
		n->data = p->data;
		//削除
		p_n->right = NULL;
	}
	//子が1つの時
	else
	{
		/* 子の方向分岐 */
		//左に子がある時
		if(n->right == NULL)
		{
			//親の左の時
			if(flag) p_n->left = n->left;
			//親の右の時
			else p_n->right = n->left;
		}
		//右に子がある時
		else
		{
			//親の左の時
			if(flag) p_n->left = n->right;
			//親の右の時
			else p_n->right = n->right;
		}
	}

	return 1;
}