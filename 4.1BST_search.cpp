//
// Created by sohne on 2020/12/4.
//

Postion Find(ElementType X, BinTree BST){
    if (!BST) return NULL;/*查找失败*/
    if (X > BST->Data){
        return Find(X, BST->right);
    } else if (X<BST->Data){
        return Find(X, BST->left);
    } else{
        return BST;
    }
}

Position IterFind( ElementType X, BinTree BST ){
    while (BST){
        if (X > BST->Data){
            BST = BST->right;
        } else if (X < BST->Data){
            BST = BST->left;
        } else {
            return BST;
        }
    }
    return NULL;
}//查找的效率决定于树的高度

Position FindMin(BinTree BST){
    if (!BST) return NULL;
    else if (!BST->left) return BST;
    else FindMin(BST->left);
} /*找到最左叶结点并返回*/


Position FindMax(BinTree BST){
    if (BST)
        while (BST->right){BST = BST->right;}
    return BST;
}//查找最大元素的迭代函数

BinTree Insert(Element X, BinTree BST){
    if (!BST){
        X = malloc(sizeof(struct TreeNode));
        X->Data = X;
        X->left = X->right = NULL;
    }else{
        if (X < BST->Data){
            BST->left = Insert(X, BST->left);
        } else if (X > BST->Data){
            BST->right = Insert(X, BST->right);
        }
    }
    return BST
}

BinTree Delete( ElementType X, BinTree BST ){
    Position Tmp;
    if (!BST) prinf("要删除的元素删除");
    else if (X < BST->Data){
        BST->left = Delete(X, BST->left);
    } else if (X > BST->Data){
        BST->right = Delete(X, BST->right);
    } else {
        if (BST->right && BST->left){
            Tmp = FindMin(BST->right);
            BST->Data = Tmp->Data;
            BST->right = Delete(X, BST->right);
        }else{
            Tmp = BST;
            if (!BST->left){
                BST = BST->right;
            } else if (!BST->right){
                BST = BST->left;
            }
            free(Tmp)
        }
    }
    return BST;
}