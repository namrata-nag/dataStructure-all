/* 
 * File:   main.cpp
 * Author: ngupta94
 *
 * Created on February 21, 2014, 12:21 AM
 */

#include <cstdlib>
#include <iostream>
#define BTREE_M 5   //MAx number of subtrees in  node
#define MAXKEYS (BTREE_M-1)
#define MINKEYS (BTREE_M/2)
#define INVALIDKEY -1
using namespace std;

class Node {
public:
    int numOfKeys;
    int keys[BTREE_M - 1];
    Node *child[BTREE_M];
    Node *parent;

    Node() {
    }

    Node(int key) {
        int i;
        numOfKeys = 1;
        keys[0] = key;
        for (i = 1; i < MAXKEYS; i++) {
            keys[i] = INVALIDKEY;
        }
        for (i = 0; i < BTREE_M; i++) {
            child[i] = NULL;
        }
        parent = NULL;
    }

    void insert(Node *l, Node *r, int key) {
        int i;

        cout << "node inert: l = " << l << " r = " << r << endl;
        child[0] = l;
        child[1] = r;
        keys[0] = key;
        numOfKeys = 0;
        for (i = 1; i < MAXKEYS; i++) {
            keys[i] = INVALIDKEY;
        }
        for (i = 2; i < BTREE_M; i++) {
            child[i] = NULL;
        }
        parent = NULL;
        numOfKeys++;
    }

    void insert(Node *n, int key) {
        int i;
        i = 0;
        int tmp;
        Node *ntmp;


        cout << "insert 2 numOFKeys enter: " << numOfKeys << "node = " << n << "key = " << key << endl;
        cout << "child[0] = " << child[0];
        while (i < numOfKeys) {
            cout << "key[" << i << "] = " << keys[i] << " child[" << i + 1 << "] = " << child[i + 1] << endl;
            if (key < keys[i]) {
                tmp = keys[i];
                keys[i] = key;
                key = tmp;
                ntmp = child[i + 1];
                child[i + 1] = n;
                n = ntmp;
            }
            i++;
        }
        keys[i] = key;
        child[i + 1] = n;
        i++;
        numOfKeys++;
        while (i < MAXKEYS) {
            keys[i] = INVALIDKEY;
            child[i + 1] = NULL;
            i++;
        }

    }
};

class BTree {
public:
    Node *root;

    BTree() {
        root = NULL;
    }
    void insert(int key);
    Node *del(int key);
    Node *leafDel(Node *n, int key);
    Node *intDel(Node *n, int key);
    void display(Node *n);
    Node *rinsert(Node *s, int key);
    Node *findParent(Node * s, Node *p, int key);
    void deleteNode(Node *s, int key);
    void inTraverse(Node *s);
    void preTraverse(Node *s);
    void postTraverse(Node *s);
    void BFS(Node *s);
    Node *nsearch(Node *s, int key, int *pos);
    int treeSize(Node *s);
    Node *minTree(Node *s);
    Node *maxTree(Node *s);
    int maxDepth(Node *s);
    int minDepth(Node *s);
    void insertInFullLeafNode(Node *n, Node *m, Node *o, int key);
    Node *getLeafNode(Node *n, int key);
    Node *splitNode(Node *n, Node *rchild, int key, int *newKey);
    bool isitLeaf(Node *n);
    Node *borrowSibling(Node *n);
    void balanceUnderflow(Node *n);
    Node *getMaxsuccessor(Node *n);
    Node *getMinsuccessor(Node *n);
    void rmerge(Node *n, Node *par, Node *rsibling, int pos);
};

void BTree::display(Node *n) {
    int i;
    cout << endl << "enter display" << endl;
    if (n != NULL) {
        cout << endl << "node = " << n << "numOfKeys = " << n->numOfKeys << endl;
        for (i = 0; i <= n->numOfKeys; i++) {
            cout << "display: child[" << i << "] = " << n->child[i];
        }

        cout << endl;
        for (i = 0; i < n->numOfKeys; i++) {

            display(n->child[i]);
            cout << n->keys[i] << " ";
        }
        display(n->child[i]);

    }
}

Node *BTree::getLeafNode(Node* n, int key) {
    int i;
    i = 0;
    if (n == NULL) {
        cout << "ERROR" << endl;
    }
    if (n->child[0] == NULL) {
        // leaf node
        return ( n);
    }
    while (i < (n->numOfKeys)) {
        if (key < n->keys[i]) {
            if (n->child[i] != NULL) {
                return ( getLeafNode(n->child[i], key));
            } else {
                cout << "getLeafNode: ERROR" << endl;
            }
        }
        i++;
    }
    if (n->child[i] != NULL) {
        return ( getLeafNode(n->child[i], key));
    } else {
        cout << "getLeafNode: ERROR1" << endl;
    }

}

Node *BTree::nsearch(Node * node, int key, int *pos) {
    int i;

    if (node == NULL) {
        return (NULL);
    }
    i = 0;
    while (i < node->numOfKeys) {
        if (key == node->keys[i]) {
            *pos = i;
            return (node);
        } else if (key < node->keys[i]) {
            return ( nsearch(node->child[i], key, pos));
        }
        i++;
    }
    return ( nsearch(node->child[i], key, pos));
}

bool BTree::isitLeaf(Node *n) {
    if (n->child[0] == NULL) {
        return (true);
    } else {
        return (false);
    }
}

Node *BTree::leafDel(Node *node, int pos) {
    int i;

    if (pos == node->numOfKeys) {
        cout << "leafDel: ERROR" << endl;
    }
    //  move all keys to the right
    for (i = pos; i < node->numOfKeys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }
    node->keys[node->numOfKeys - 1] = INVALIDKEY;
    node->numOfKeys--;
    return (NULL);
}

Node *BTree::getMaxsuccessor(Node *n) {
    if (n->child[0] == NULL) {
        return (n);
    } else {
        return ( getMaxsuccessor(n->child[n->numOfKeys]));
    }

}

Node *BTree::getMinsuccessor(Node *n) {
    if (n->child[0] == NULL) {
        return (n);
    } else {
        return ( getMinsuccessor(n->child[0]));
    }

}
// delete fro Interior node

Node *BTree::intDel(Node *node, int pos) {
    Node *lleaf;
    Node *rleaf;

    lleaf = getMaxsuccessor(node->child[pos]);
    rleaf = getMinsuccessor(node->child[pos + 1]);

    if (lleaf->numOfKeys > MINKEYS) {
        node->keys[pos] = lleaf->keys[lleaf->numOfKeys - 1];
        leafDel(lleaf, lleaf->numOfKeys - 1);
        return ( lleaf);
    }
    node->keys[pos] = rleaf->keys[0];
    leafDel(rleaf, 0);

    return ( rleaf);

}

Node *BTree::borrowSibling(Node *node) {

}

void rotateRt(Node *n, Node *par, Node *sib, int pos) {
    int i;

    cout << "rotatRt: pos = " << pos << endl;
    //    insertInNodeRt(n, par->keys[par->numOfKeys-1], sib->child[0] );
    n->keys[n->numOfKeys] = par->keys[pos];
    n->child[n->numOfKeys] = sib->child[0];
    if ( n->child[n->numOfKeys] != NULL ) {
        n->child[n->numOfKeys]->parent = n;
    }
    
    n->numOfKeys++;
    cout << "rotate RT: pa key = " << par->keys[par->numOfKeys-1] << endl;
    par->keys[pos] = sib->keys[0];
    for (i = 0; i < sib->numOfKeys - 1; i++) {
        sib->keys[i] = sib->keys[i + 1];
        sib->child[i] = sib->child[i + 1];
    }
    sib->child[i] = sib->child[i + 1];
    sib->keys[sib->numOfKeys - 1] = INVALIDKEY;
    sib->child[sib->numOfKeys] = NULL;
    sib->numOfKeys--;

}

void insertInNodeRt(Node *n, int key, Node* child) {
    n->keys[n->numOfKeys] = key;
    n->child[n->numOfKeys + 1] = child;
    n->numOfKeys++;

}

void rotateLft(Node *n, Node *par, Node *sib, int pos) {
    int i;
    
    cout << "rotateLft: pos = " << pos << endl;
    //    insertInNodeLft(n, par->keys[0], sib->child[sib->numOfKeys] );
    for (i = n->numOfKeys-1; i >= 0; i++) {
        n->keys[i+1] = n->keys[i];
    }
    for ( i = n->numOfKeys; i >=0; i++ ) {
        n->child[i+1] = n->child[i];
    }
    n->keys[0] = par->keys[pos];
    n->child[0] = sib->child[sib->numOfKeys];
    n->child[0]->parent = n;
    n->numOfKeys++;
    par->keys[pos] = sib->keys[sib->numOfKeys - 1];
    sib->keys[sib->numOfKeys - 1] = INVALIDKEY;
    sib->child[sib->numOfKeys] = NULL;
    sib->numOfKeys--;

}

void insertInNodeLft(Node *n, int key, Node* child) {
    int i;
    for (i = n->numOfKeys; i > 0; i--) {
        n->keys[i] = n->keys[i - 1];
        n->child[i + 1] = n->child[i];
    }
    n->child[1] = n->child[0];
    n->keys[0] = key;
    n->child[0] = child;
    n->numOfKeys++;

}

// Delete a key from the node and move other keys and children to left
void delKey( Node *n, int keyPos, int childPos ) {
    int i;
    
    cout << "delKey keys = " << n->numOfKeys << endl;
    for ( i = keyPos; i < n->numOfKeys-1; i++ ) {
        n->keys[i] = n->keys[i+1];
    }
    n->keys[n->numOfKeys-1] = INVALIDKEY;
    for ( i = childPos; i < n->numOfKeys; i++ ) {
        n->child[i] = n->child[i+1];
    }
    n->child[n->numOfKeys] = NULL;
    n->numOfKeys--;
}
void BTree::rmerge(Node *n, Node *par, Node *rsibling, int pos) {
    int i;
    
    cout << "rmerge enter  pos = " << pos << endl;
    cout << "enter n keys = " << n->numOfKeys << endl;
    cout << "rmerge: rsibling keys = " << rsibling->numOfKeys << endl;
    
    n->keys[n->numOfKeys] = par->keys[pos];
    n->numOfKeys++;
    n->child[n->numOfKeys] = rsibling->child[0];
    if ( rsibling->child[0] != NULL ) {
        rsibling->child[0]->parent = n;
    }

    cout << "n keys = " << n->numOfKeys << endl;
    
    delKey(par, pos, pos+1);
    cout << "rmerge: par key = " << par->numOfKeys << endl;
    
    for ( i = 0; i < rsibling->numOfKeys; i++ ) {
        n->keys[n->numOfKeys] = rsibling->keys[i];
        n->child[n->numOfKeys+1] = rsibling->child[i+1];
        n->numOfKeys++;
        if ( n->child[n->numOfKeys] != NULL ) {
            n->child[n->numOfKeys]->parent = n;
        }
    }
    cout << "rmerge: n keys = " << n->numOfKeys << endl;
    
    display(n->parent);
    
    cout << "rmerge back" << endl;
    delete(rsibling);
}
void BTree::balanceUnderflow(Node* n) {
    Node *par;
    Node *lsibling;
    Node *rsibling;
    Node *bnode;
    Node *mnode;
    int bkey;
    int i;
    int pos = -1;

    if ( n == NULL ) {
        cout << " Underflow: ERROR 1" << endl;
    }
    cout << "undrflow enter" << endl;
    cout << endl << endl;
    
  
    par = n->parent;
    
     display(par);
    
    cout << "back tounderflow" << endl;
    
    
    cout << "underflow: n keys = " << n->numOfKeys << endl;
    cout << "underflow: par keys = " << par->numOfKeys << endl;
    cout << "underflow: par 0 key = " << par->keys[0] << endl;
    for (i = 0; i < n->numOfKeys; i++) {
        cout << "balanceUnderflow:nkey[ = " << i << "]" << n->keys[i] << endl;
    }
    cout << "balanceUnderflow:node = " << n << endl;
    cout << "balanceUnderflow:parent = " << par << endl;
   
    for (i = 0; i < par->numOfKeys + 1; i++) {
        if (i < par->numOfKeys)
            cout << "balanceUnderflow:key[ = " << i << "]" << par->keys[i] << endl;
        cout << "balanceUnderflow:child[ = " << i << "]" << par->child[i] << endl;
        if (par->child[i] == n) {
            pos = i;
        }
    }
    cout << "underflow: pos = " << pos << endl;
    if (pos == -1) {
        cout << "balanceUnderflow: INTERNL ERROR" << endl;
    } else if (pos == 0) {
        cout << "underflow: only right sibling" << endl;
        lsibling = NULL;
        rsibling = par->child[1];
    } else if (pos == par->numOfKeys ) {
        cout << "underflow: only left sibling" << endl;
        lsibling = par->child[pos - 1];
        rsibling = NULL;
    } else {
        cout << "underflow: both siblings" << endl;
        lsibling = par->child[pos - 1];
        rsibling = par->child[pos + 1];
    }
    if (lsibling != NULL) {
        if (lsibling->numOfKeys > MINKEYS) {
            bkey = lsibling->keys[lsibling->numOfKeys - 1];
            bnode = lsibling;
            rotateLft(n, par, lsibling, pos-1);
            return;

        } 
    }
    if (rsibling != NULL) {
        if (rsibling->numOfKeys > MINKEYS) {
            bnode = rsibling;
            cout << "underflow: rsibling !NULL 1" << endl;
            rotateRt(n, par, rsibling, pos);
            return;
        }
    }

    // we cannot rotate.  So merge
    if (lsibling != NULL) {
        cout << "underflow: merge left par keys = " << par->numOfKeys << endl;
        rmerge( lsibling, par, n, pos-1 );
        mnode = lsibling;
    }
    else if (rsibling != NULL ) {
        cout << "underflow: merge right" << endl;
        rmerge(n, par, rsibling, pos);
        mnode = n;
    }
    else {
        cout << "underflow: ERROR" << endl;
    }
    if ( par->numOfKeys == 0 ) {
        root = mnode;
    }
    else if (par->numOfKeys < MINKEYS) { //underflow
        cout << "underflow: it is underflow" << endl;
        balanceUnderflow(par);
    }
}

Node *BTree::del(int key) {
    Node *node;
    Node *snode;
    bool leaf;
    bool rsibling;
    bool lsibling;
    int pos;

    cout << "enter del key = " << (char)key << key << endl;
    node = nsearch(root, key, &pos);
    if (node == NULL) {
        cout << "key = " << key << " not found" << endl;
        return (NULL);
    } else {
        cout << "keynode = " << node << endl;
    }
    leaf = isitLeaf(node);
    if (leaf == true) {
        cout << "del: it is leaf" << endl;
        leafDel(node, pos);
    } else {
        node = intDel(node, pos);
    }
    if (node->numOfKeys < MINKEYS) { //underflow
        cout << "del: it is underflow" << endl;
        balanceUnderflow(node);
    }
    return (NULL);
}

Node *BTree::splitNode(Node *n, Node *rchild, int key, int *newKey) {
    int nkey[BTREE_M];
    Node * nchild[BTREE_M + 1];
    Node *newNode;
    Node *ntmp;
    bool done = false;
    int mid;
    int i, j;
    int tmp;
    i = 0;
    j = 0;

    cout << "splitNode enter node dispaly = " << n->numOfKeys << endl;

    /* make a temporary node with BTREE_M keys.  Then we split this node */
    nchild[0] = n->child[0];
    while (j < n->numOfKeys) {
        if (done == false) {
            if (key < n->keys[j]) {
                nkey[i] = key;
                nchild[i + 1] = rchild;
                done = true;
                i++;
                continue;
            }
        }
        nkey[i] = n->keys[j];
        nchild[i + 1] = n->child[j + 1];
        i++;
        j++;
    }
    if (done == false) {
        nkey[i] = key;
        nchild[i + 1] = rchild;
    }
    cout << "split new node = ";
    for (i = 0; i < BTREE_M; i++) {
        cout << nkey[i] << " ";
    }
    for (i = 0; i <= BTREE_M; i++) {
        cout << "child[" << i << "]=" << nchild[i] << endl;
        if (nchild[i] != NULL) {
            for (j = 0; j < nchild[i]->numOfKeys; j++) {
                cout << "key[" << j << "]=" << nchild[i]->keys[j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
    mid = BTREE_M / 2;
    newNode = new Node();
    cout << "splitNode: ne node created:" << newNode << endl;
    i = 0;
    j = 0;
    newNode->child[j] = nchild[mid + 1];
    newNode->numOfKeys = 0;
    for (i = mid + 1; i < BTREE_M; i++) {
        newNode->keys[j] = nkey[i];
        newNode->child[j + 1] = nchild[i + 1];
        newNode->numOfKeys++;
        j++;
    }
    for (i = j; i < MAXKEYS; i++) {
        newNode->keys[i] = INVALIDKEY;
        newNode->child[i + 1] = NULL;
    }
    n->child[0] = nchild[0];
    n->numOfKeys = 0;
    for (i = 0; i < mid; i++) {
        n->keys[i] = nkey[i];
        n->child[i + 1] = nchild[i + 1];
        n->numOfKeys++;
    }
    for (i = mid; i < MAXKEYS; i++) {
        n->keys[i] = INVALIDKEY;
        n->child[i + 1] = NULL;
    }
    *newKey = nkey[mid];
    cout << "split new node 1 = ";
    for (i = 0; i < BTREE_M - 1; i++) {
        cout << n->keys[i] << " ";
    }
    cout << "split new node 2 = ";
    for (i = 0; i < MAXKEYS; i++) {
        cout << newNode->keys[i] << " ";
    }
    for (i = 0; i < BTREE_M; i++) {

        if (newNode->child[i] != NULL) {
            cout << "child[" << i << "]=" << newNode->child[i] << "keys = " << newNode->child[i]->numOfKeys << endl;
             for ( j = 0; j < newNode->child[i]->numOfKeys; j++ ) {
                 cout << "key["<<j<<"]="<<newNode->child[i]->keys[j] << " ";
             }
            newNode->child[i]->parent = newNode;
             cout << endl;
        }
    }
    cout << endl;
    return (newNode);

}

void BTree::insertInFullLeafNode(Node *cur, Node *lchild, Node *rchild, int key) {
    Node *newNode;
    int newKey;
    cout << "enter insertInFullLNode" << endl;
    if (cur != NULL) {
        cout << "insertFullLNode: key = " << key << "numOfKEy = " << cur->numOfKeys << endl;
    }
    if (cur == NULL) {
        // New Root added old node split into two children
        newNode = new Node();
        cout << "insertFullLNode: adding Root: lchildadd = " << lchild << "rchild = " << rchild;
        cout << "root = " << newNode << endl;
        newNode->insert(lchild, rchild, key);

        root = newNode;
        lchild->parent = root;
        rchild->parent = root;
        cout << "return after new root in insertFullLNode" << endl;
    } else if (cur->numOfKeys < BTREE_M - 1) {
        // jst insert the key, the node is not full
        cout << "insertFullLNode: cur-insert called - rchild =" << rchild << "key =" << key << endl;
        cur->insert(rchild, key);
    } else {
        // else node is full and we need to split the current node
        newNode = splitNode(cur, rchild, key, &newKey);
        cout << "insertFullLNode: newKey = " << newKey << endl;
        if (newNode == NULL) {
            cout << "insertFullLNode: newNode returned NULL" << endl;
        } else {
            cout << "insertFullLNode: newNodeNumOfKeys = " << newNode->numOfKeys << endl;
            cout << "insertFullLNode: curNode NumOfKeys = " << cur->numOfKeys << endl;
            cout << "inertFullLNode: newNodeADDR = " << newNode << endl;
            cout << "inertFullLNode: parentnewNodeADDR = " << cur->parent << endl;
        }
        newNode->parent = cur->parent;
        
        // after split, the middle key moves upto parent. so insert in parent
        insertInFullLeafNode(cur->parent, cur, newNode, newKey);
    }
}

void BTree::insert(int key) {
    Node *leaf;

    if (root == NULL) {
        root = new Node(key);
        return;
    }
    // insert starts at leaf node
    leaf = getLeafNode(root, key);
    cout << "leafNode found; numOfKEys = " << leaf->numOfKeys << endl;
    if (leaf->numOfKeys < BTREE_M - 1) {
        leaf->insert(NULL, key);
    } else {
        insertInFullLeafNode(leaf, NULL, NULL, key);
    }




}

/*
 * 
 */
int main(int argc, char** argv) {
    BTree bt;

    bt.insert('C');
    bt.insert('N');
    bt.insert('G');
    bt.insert('A');
    bt.insert('H');
    bt.insert('E');
    bt.insert('K');
    bt.insert('Q');
    bt.insert('M');
    bt.insert('F');
    bt.insert('W');
    bt.insert('L');
    bt.insert('T');
    bt.insert('Z');
    bt.insert('D');
    bt.insert('P');
    bt.insert('R');
    bt.insert('X');
    bt.insert('Y');
    bt.insert('S');
    bt.del('H');
    bt.del('T');
    cout << endl;
    cout << endl;
    bt.del('R');
    bt.del('E');
    cout << "main: to display" << endl;
    bt.display(bt.root);
    return 0;
}
