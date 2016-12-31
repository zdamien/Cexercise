/* simple int-valued AVL tree.  Messy shitty code right now as I focused
 * on getting balancing working at all, lots of debug comments, and
 * 'height' is calculated as needed, not cached.  But the balancing does
 * work. */
   
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mine.h"

typedef struct node {
  struct node *left, *right, *parent;
  int key, value;
} Tree;

int validate(const Tree * tree) ;
int hvalidate(const Tree * tree) ;
Tree* balinsert(Tree* tree, int key, int value) ;
Tree* rotright(Tree* tree) ;
Tree* rotleft(Tree* tree) ;

Tree* insert(Tree* tree, int key, int value) {
    /* basic tree insertion. if a key already is present, the new value
     * is thrown away. The tree is returned. */

  //assert(tree);
  if (!tree) {
      /*note this will mean a leaf node more often than an empty tree*/
    Tree* node=0;
    node = calloc(1,sizeof(Tree));
    if (!node) return NULL;
    node->key=key;
    node->value=value;
    return node;
  } else if (key == tree->key) {
    return tree;
  } else if (key < tree->key) {
    tree->left = insert(tree->left, key, value);
    tree->left->parent=tree;
    /* left might have been NUll, in which case we must set the parent
     * of the new node */
  } else if (key > tree->key) {
    tree->right = insert(tree->right, key, value);
    tree->right->parent=tree;
  }
  return tree;
}

#define PREORDER -1
#define INORDER 0
#define POSTORDER 1

void traverse(const Tree* tree, int order) {
    // ordered traversals
  assert(tree);
  if (order == PREORDER)
    printf("key: %d, value %d, pointer %p\n",tree->key, tree->value, tree);
  if (tree->left)
    traverse(tree->left, order);
  if (order == INORDER)
    printf("key: %d, value %d, pointer %p\n",tree->key, tree->value, tree);
    //printf("key: %d, value %d\n",tree->key, tree->value);
  if (tree->right)
    traverse(tree->right, order);
  if (order == POSTORDER)
    printf("key: %d, value %d, pointer %p\n",tree->key, tree->value, tree);
}

int height(const Tree* tree) ;

void printtree(const Tree* tree, int parent) {
    //special printer, with parent attribute for clarity
    //prints root on the right; nodes of same height are aligned
    //prints parent key, current key, height
  if (!tree) return;
  printtree(tree->left, tree->key);
  int _height=height(tree);
  for (int i=0;i<_height; i++) 
    printf ("    ");
  printf("%d:%d::%d\n",parent,tree->key,_height);
  printtree(tree->right, tree->key);
}

void printtree2(const Tree* tree, int depth, int parent) {
    //special printer, with parent attribute for clarity
    //n is number of spaces of indentation for tree levels
    //prints root on left; children are aligned
    //prints parent key, current key, depth
  if (!tree) return;
  printtree2(tree->right, depth+1, tree->key);
  for (int i=0;i<depth; i++) 
    printf ("    ");
  printf("%d:%d::%d\n",parent, tree->key, depth);
  printtree2(tree->left, depth+1, tree->key);
}

Tree* leftmost(Tree* tree) {
  if (tree->left) return leftmost(tree->left);
  else return tree;
}

Tree* rightmost(Tree* tree) {
  if (tree->right) return rightmost(tree->right);
  else return tree;
}

int height(const Tree* tree) {
    if (!tree) return 0;
    else {
      int lh=height(tree->left);
      int rh=height(tree->right);
      int h=max(lh,rh)+1;
      //printf("key %d lh %d rh %d h %d\n",tree->key, lh, rh, h);
      return h;
    }
}

Tree* lookup(Tree* tree, int key) {
  if (!tree) return NULL;
  else if (tree->key == key) return tree;
  else if (key < tree->key) return lookup(tree->left, key);
  else if (key > tree->key) return lookup(tree->right, key);
  assert(!"end of lookup");
}

int leaf(const Tree* tree) {
  return (!tree->left) && (!tree->right);
}

#define ROOT 1
#define LEFT 2
#define RIGHT 3

int parenthood(const Tree* tree) {
    // are we root? if not, which child are we?
  if (tree->parent == NULL) return ROOT;
  else if (tree->parent->left == tree) return LEFT;
  else if (tree->parent->right == tree) return RIGHT;
  else assert(!"malformed tree in parenthood");
}

int subtrees(const Tree* tree) {
    //how many subtrees? 0, 1, or 2
  int subs=0;
  if (tree->left) subs++;
  if (tree->right) subs++;
  return subs;
}

Tree* trigger(Tree * tree) ;

Tree* delete(Tree *tree, int key) {
  printf("delete: %d %d\n",tree->key, key);
  validate(tree);
  printtree(tree,0);
  Tree* tp=lookup(tree,key);
  if (!tp) return tree;
  if (leaf(tp)) {
    assert(subtrees(tp)==0);
    if (parenthood(tp) == ROOT) {
        // tree has only one node, which we are deleting
      //printf("  delete: %d %d\n",tree->key, tp->key);
      assert(tp==tree);
      validate(tree);
      free(tree);
      return 0;
    }
    else if (parenthood(tp) == LEFT) {
      tp->parent->left=NULL;
    } else {
      tp->parent->right=NULL;
    }
    free(tp);
    validate(tree);
  } // end if leaf
  else if (subtrees(tp) == 1) {
    //printf("trace on\n");
    Tree* child=0;
    Tree* parent=tp->parent;
    if (tp->left)
      child=tp->left;
    else 
      child=tp->right;
    //printf(" i\n");
    //validate(tree);
    child->parent=parent;
    if (parenthood(tp)==LEFT)
      parent->left=child;
    else if (parenthood(tp)==RIGHT)
      parent->right=child;
    else {
      // deleting a root with one subtree
      //printf(" not  off\n");
      free(tp);
      //trigger(tree);
      return child;
    }
    //printf("tpk %d chkey %d park %d: trp %p tpp %p chp %p chpar %p parp %p parl %p parr %p\n",tp->key, child->key, parent->key, tree, tp, child, child->parent, parent, parent->left, parent->right);
    //printf(" 3\n");
    memset(tp, 0, sizeof(Tree)); //debugging thing?
    free(tp);
    //validate(tree);
    //printf(" trace off\n");
    //trigger(tree);
    //printf("trace off\n");
    //validate(tree);
  } // end subtrees(tp) == 1
  else {
    Tree* repl=rightmost(tp->left);
    tp->key=repl->key;
    tp->value=repl->value;
    delete(tp->left,repl->key);
    //tp->left=delete(tp->left,repl->key);

    //trigger(tree); // seems to make no difference
  }

  return tree;
}

// tree rotation functions.
// rotation through the root needs to have the return value captured.
Tree* oldrotright(Tree* tree) {
    // I thought this was so clever: rotate by pushing the root to the
    // right, copying up the rightmost left value, and deleting the
    // latter
  //printf("rotright 1\n");
  //printtree(tree,0);
  //printf("rotright 2\n");
  tree->right=balinsert(tree->right, tree->key, tree->value);
  tree->right->parent=tree;
  //printf("  %p %p %p\n",tree,tree->right, tree->right->parent);
  //printf("  %d %d %p\n",tree->key,tree->right->key, tree->left);
  //printtree(tree,0);
  //printf("rotright 3\n");

  validate(tree);
  Tree* repl=rightmost(tree->left);
  //printf("rotright 4\n");
  tree->key = repl->key;
  tree->value = repl->value;
  delete(tree->left, repl->key);
  trigger(tree->left);
  return tree;
}
Tree* oldrotleft(Tree* tree) {
    // I thought this was so clever: rotate by pushing the root to the
    // right, copying up the rightmost left value, and deleting the
    // latter
  //printf("rotright 1\n");
  //printtree(tree,0);
  //printf("rotright 2\n");
  tree->left=balinsert(tree->left, tree->key, tree->value);
  tree->left->parent=tree;
  //printf("  %p %p %p\n",tree,tree->right, tree->right->parent);
  //printf("  %d %d %p\n",tree->key,tree->right->key, tree->left);
  //printtree(tree,0);
  //printf("rotright 3\n");

  validate(tree);
  Tree* repl=leftmost(tree->right);
  //printf("rotright 4\n");
  tree->key = repl->key;
  tree->value = repl->value;
  delete(tree->right, repl->key);
  trigger(tree->right);
  return tree;
}

Tree* rotright(Tree* tree) {
    assert(tree->left);
    Tree* temp = tree;
    int parent = parenthood(tree);

    tree = temp->left;
    tree->parent = temp->parent;
    temp->left = tree->right;
    if (temp->left)
        temp->left->parent= temp;
    temp->parent = tree;
    tree->right = temp;

    if (parent == LEFT) 
        tree->parent->left = tree;
    else if (parent == RIGHT)
        tree->parent->right = tree;
    
  //tree=trigger(tree->right);
    return tree;
}

Tree* rotleft(Tree* tree) {
    assert(tree->right);
//    printf("rotleft----\n");
 //   printtree2(tree,0,0);
  //  printf("rotleft--\n");
    Tree* temp = tree;
    int parent = parenthood(tree);

    tree = temp->right;
    tree->parent = temp->parent;
    temp->right = tree->left;
    if (temp->right)
        temp->right->parent= temp;
    temp->parent = tree;
    tree->left = temp;

    if (parent == LEFT) 
        tree->parent->left = tree;
    else if (parent == RIGHT)
        tree->parent->right = tree;
    
  //trigger(tree->left);
  //  printtree2(tree,0,0);
   // printf("rotleft----\n");
    return tree;
}

/* not working
Tree* _balinsert(Tree* tree, int key, int value) {
  if (!tree)
    return insert(tree,key, value);
  else if (key<tree->key)
    tree->left=balinsert(tree->left, key, value);
  else if (key>tree->key)
    tree->right=balinsert(tree->right, key, value);
  else return tree;

  int hl=height(tree->left);
  int hr=height(tree->right);
  if (hl-hr>1) rotright(tree);
  if (hl-hr<-1) rotleft(tree);
  printf("here %d %d %d\n",tree->key, hl, hr);
  return tree;
} */

Tree* trigger(Tree * tree) {
  if (!tree) return tree;

  int hl=height(tree->left);
  int hr=height(tree->right);
  validate(tree);
  //printf("trigger 1: %d %d %d\n",tree->key, hl, hr);
  if (hl-hr>1) {
      int innerhr = height(tree->left->right);
      int sib_hl = height(tree->left->left);
      if (innerhr <= sib_hl) {
          tree=rotright(tree);
          tree->left->parent=tree;
          tree->right->parent=tree;
      } else {
          tree->left = rotleft(tree->left);
          tree = rotright(tree);
          tree->left->parent=tree;
          tree->right->parent=tree;
      }
  }
  else if (hl-hr<-1) {
      int innerhl = height(tree->right->left);
      int sib_hr = height(tree->right->right);
      if (innerhl <= sib_hr) { //simple
          tree=rotleft(tree);
          tree->left->parent=tree;
          tree->right->parent=tree;
      } else{
          tree->right = rotright(tree->right);
          tree = rotleft(tree);
          tree->left->parent=tree;
          tree->right->parent=tree;
      }
  }
  //printf("trigger 2: %d %d %d\n",tree->key, hl, hr);
    //printtree2(tree,0,0);
  validate(tree);
  hvalidate(tree);
  //printf("trigger 4: %d %d %d\n",tree->key, hl, hr);
  return tree;
}



Tree* balinsert(Tree* tree, int key, int value) {
  //assert(tree);
  if (!tree) {
    Tree* node = calloc(1,sizeof(Tree));
    if (!node) 
        assert(!"calloc failure");
    node->key=key;
    node->value=value;
    return node;
  } else if (key == tree->key) {
    return tree;
  } else if (key < tree->key) {
    tree->left = balinsert(tree->left, key, value);
    tree->left->parent=tree;
    //printf("valid l %d %p %p %p\n",tree->key,tree, tree->left,tree->left->parent);
  } else if (key > tree->key) {
    tree->right = balinsert(tree->right, key, value);
    tree->right->parent=tree;
    //printf("valid r %d %p %p %p\n",tree->key,tree, tree->right,tree->right->parent);
  }

  validate(tree);
  //printf("post valid %d\n",key);
  //printtree(tree,0);
  //printf("pre trigg %d\n",key);
  tree=trigger(tree);
  //printf("post trig 0 %d\n",key);
  validate(tree);
  hvalidate(tree);
  //printf("post trig 0 %d\n",key);
//  printf("pre valid %d\n",key);
 // validate(tree);
  //printf("post trigg %d\n",key);

  //printtree(tree,0);
  //printf("----\n");
  //printf("here 2 %d %d %d\n",tree->key, hl, hr);
  //validate(tree);
  //printf("here 3 %d %d %d\n",tree->key, hl, hr);
  return tree;
}

int validate(const Tree * tree) {
    // makes sure all children and parents match
  if (!tree) return 1;
  int res=1;

  if (tree->left) {
    //printf("validleft %p %p %p\n",tree, tree->left, tree->left->parent);
    assert(tree->left->parent == tree);
    res&=validate(tree->left);
  }
  if (tree->right) {
    //printf("validright %p %p %p\n",tree, tree->right, tree->right->parent);
    assert(tree->right->parent == tree);
    res&=validate(tree->right);
  }
  return res;
}

int hvalidate(const Tree* tree){
  if (!tree) return 1;
  int res=0;
  int hl=height(tree->left);
  int hr=height(tree->right);
  assert(abs(hl-hr)<=1);
  if (tree->left) 
      res&=hvalidate(tree->left);
  if (tree->right) 
      res&=hvalidate(tree->right);
  return res;
}

void destroy ( Tree * tree) {
    if (tree) {
        destroy (tree->left);
        destroy (tree->right);
    }
    free (tree);

}

int main() {
  Tree* tree = 0;
  //tree->key=50; tree->value=11;
  //int keys[]=  {50};
  //int values[]={1};
//  int keys[]=  {1,2,3,4,5,6,7};
 // int values[]={1,2,10,4,5,6,7};
  //int values[]=  {50,20,80,40,70,30,90,10,60, 35, 32, 55, 65, 45,20,19,18,17,16,15};
  //int keys[]={1,2,3,4,5,6,7,8,9, 10, 11, 12, 13, 14,-20,-19,-18,-17,-16,-15};
  int keys[]={1,2,3,4,5,6,7,8,9, 10, 11, 12, -13, 14, 15, 16, 17, 18, 19,
      20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, -32, -33, -34};
  int values[]={1,2,3,4,5,6,7,8,9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34};

  for (int i=0; i< sizeof(keys)/sizeof(keys[0]); i++) {
    //printf("inserting step %d %d:%d\n",i, keys[i], values[i]);
    tree=balinsert(tree,keys[i],values[i]);
    validate(tree);
    hvalidate(tree);

    //printf("\n======= main loop \n");
    //printtree(tree,0);
    //printf("-----\n");
    //printtree2(tree,0,0);
    //printf("======= main loop end \n");
  }
  printf("=======PRE\n");
  traverse(tree, PREORDER);
  printf("=======1\n");
  printtree(tree,0);
  printf("=======2\n");
  printtree2(tree,0,0);
  printf("\n");

  /*
  tree=rotleft(tree);

  printf("=======PRE\n");
  traverse(tree, PREORDER);
  printf("=======1\n");
  printtree(tree,0);
  printf("=======2\n");
  printtree2(tree,0,0);
  printf("\n");
  */

  /*
  traverse(tree, INORDER);
  printf("\n");
  traverse(tree, POSTORDER);
  */
  //printf("%d\n",parenthood(lookup(tree, 90)));

  delete(tree,40);
  //delete(tree,70);
  //tree=delete(tree,50);
//  rotleft(lookup(tree,5));
 // rotleft(lookup(tree,9));
  //rotleft(lookup(tree,8));
  //rotleft(lookup(tree,8));
  //rotright(lookup(tree,80));
  //rotright(lookup(tree,70));
   // validate(tree);
//  printf("====\n");
 // printtree(tree,0);
//  printf("=======\n");
//  printtree2(tree,0,0);
  //traverse(tree, PREORDER);
  //tree=rotright(tree);

  /*
  printf("look %d\n",lookup(tree,5)->value);
  printf("look %d\n",lookup(tree,1)->value);
  printf("look %d\n",lookup(tree,6)->value);
  Tree* tp= leftmost(tree);
  printf("%d, %d\n", tp->key, tp->value);
  tp=rightmost(tree);
  printf("%d, %d\n", tp->key, tp->value);

  printf("max 3 4 is %d\n",max(3,4));
  printf("max 3 2 is %d\n",max(3,2));
  printf("height tree is %d\n",height(tree));
  */

  destroy (tree);
}
