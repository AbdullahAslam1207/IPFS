#include <iostream>
#include <string>
#include<bitset>
#include<cmath>
#include "sha1.h"

using namespace std;
//below is the implementation of btree class with btree node as its block to enter it contains both the name of the file and key


class SinglyNode
{
public:
    long double key;
    string a;
    SinglyNode* next;
    SinglyNode()
    {
        key = 0;
        a = "";
        next = nullptr;
    }


};
class Node {
    // make a pointer array for storing names as well beacause node means it can have 2  3  4...pair and that entire
    // node is named after a 
public:
    SinglyNode* pair;
    int max;
    Node** CHILDREN;
    int values;
    bool endnodes;
    //string a = "";

public:
    Node(int max, bool endnodes, string x) {
        this->max = max;
        this->endnodes = endnodes;
        pair = new SinglyNode[2 * max - 1];
        CHILDREN = new Node * [2 * max];
        values = 0;
        //a = x;
    }


    /* Insert non full condition */
    void nonempty1(long double k, string x, int& i)
    {
        while (i >= 0 && pair[i].key >= k) {
            pair[i + 1] = pair[i];
            i--;
        }

        pair[i + 1].key = k;
        pair[i + 1].a = x;
        values = values + 1;
    }
    void nonempty2(long double k, string x, int& i)
    {
        while (i >= 0 && pair[i].key > k)
            i--;

        if (CHILDREN[i + 1]->values == 2 * max - 1) {
            childsplit(i + 1, CHILDREN[i + 1], x);

            if (pair[i + 1].key < k)
                i++;
        }
        CHILDREN[i + 1]->nonempty(k, x);
    }
    void nonempty(long double  k, string x) {
        int i = values - 1;

        if (endnodes == true) {
            nonempty1(k, x, i);
        }
        else {
            nonempty2(k, x, i);
        }
    }

    /* split the child */
    void childsplit1(int i, Node* y, string x, Node* z)
    {
        z->values = max - 1;

        for (int j = 0; j < max - 1; j++)
            z->pair[j] = y->pair[j + max];

        if (y->endnodes == false) {
            for (int j = 0; j < max; j++)
                z->CHILDREN[j] = y->CHILDREN[j + max];
        }
    }
    void childsplit2(int i, Node* y, string x, Node* z)
    {
        y->values = max - 1;
        for (int j = values; j >= i + 1; j--)
            CHILDREN[j + 1] = CHILDREN[j];

        CHILDREN[i + 1] = z;

        for (int j = values - 1; j >= i; j--)
            pair[j + 1] = pair[j];

        pair[i] = y->pair[max - 1];
        values = values + 1;
    }
    void childsplit(int i, Node* y, string x) {
        Node* z = new Node(y->max, y->endnodes, x);
        childsplit1(i, y, x, z);

        childsplit2(i, y, x, z);

    }

    /* Traverse the nodes */
    void traverse() {
        int i;
        for (i = 0; i < values; i++) {
            if (endnodes == false)
                CHILDREN[i]->traverse();
            cout << "  KEY: " << pair[i].key << " VALUE : " << pair[i].a<<" NEXT PAIR -> ";

            /*SinglyNode* temp = pair;
            while (temp != nullptr)
            {
                cout << temp->key << " " << temp->a << " ";
                temp = temp->next;
            }*/
        }

        if (endnodes == false)
            CHILDREN[i]->traverse();
    }


    void singlynode_retrival(SinglyNode& obj, long double key, int id)
    { // in use for when user inputs machine manually and we need the data from the next machine 
        int i;
        for (i = 0; i < values; i++)
        {
            if (endnodes == false)
                CHILDREN[i]->singlynode_retrival(obj, key, id);
            //cout << " " << pair[i].key << " " << pair[i].a;
            if (pair[i].key == id)
            {

            }
            else if (pair[i].key <= key)
            {
                obj.key = pair[i].key;
                obj.a = pair[i].a;
                return;
            }


        }

        if (endnodes == false)
            CHILDREN[i]->singlynode_retrival(obj, key, id);
    }

    void singlynode_retrival_case1(SinglyNode& obj, long double key, int id)
    { // in use for when user inputs machine manually and we need the data from the next machine 
        int i;
        for (i = 0; i < values; i++)
        {
            if (endnodes == false)
                CHILDREN[i]->singlynode_retrival_case1(obj, key, id);
            //cout << " " << pair[i].key << " " << pair[i].a;
            if (pair[i].key == id)
            {

            }
            else if (pair[i].key > id || pair[i].key <= key)
            {
                obj.key = pair[i].key;
                obj.a = pair[i].a;
                return;
            }


        }

        if (endnodes == false)
            CHILDREN[i]->singlynode_retrival_case1(obj, key, id);
    }

    void singlynode_retrival_case2(SinglyNode& obj, long double key, int id)
    { // in use for when user inputs machine manually and we need the data from the next machine 
        int i;
        for (i = 0; i < values; i++)
        {
            if (endnodes == false)
                CHILDREN[i]->singlynode_retrival_case2(obj, key, id);
            //cout << " " << pair[i].key << " " << pair[i].a;
            if (pair[i].key == id)
            {

            }
            else if (pair[i].key > id && pair[i].key <= key)
            {
                obj.key = pair[i].key;
                obj.a = pair[i].a;
                return;
            }


        }

        if (endnodes == false)
            CHILDREN[i]->singlynode_retrival_case2(obj, key, id);
    }


    void countkeys_less(long double key, int& count, int id)  // for counting the number of elements that are less or equal to a specific key while inserting manually
    {
        int i;
        for (i = 0; i < values; i++)
        {
            if (endnodes == false)
                CHILDREN[i]->countkeys_less(key, count, id);
            //cout << " " << pair[i].key << " " << pair[i].a;
            if (pair[i].key == id)
            {

            }

            else if (pair[i].key <= key)
            {
                count++;
            }



        }

        if (endnodes == false)
            CHILDREN[i]->countkeys_less(key, count, id);
    }

    //  the below is for counting the keys that are used in insertion of case 1 
    void countkeys_less_case1(long double key, int& count, int id)  // for counting the number of elements that are less or equal to a specific key while inserting manually
    {
        int i;
        for (i = 0; i < values; i++)
        {
            if (endnodes == false)
                CHILDREN[i]->countkeys_less_case1(key, count, id);
            //cout << " " << pair[i].key << " " << pair[i].a;
            if (pair[i].key == id)
            {

            }

            else if (pair[i].key > id || pair[i].key<= key)
            {
                count++;
            }



        }

        if (endnodes == false)
            CHILDREN[i]->countkeys_less_case1(key, count, id);
    }
    void countkeys_less_case2(long double key, int& count, int id)  // for counting the number of elements that are less or equal to a specific key while inserting manually
    {
        int i;
        for (i = 0; i < values; i++)
        {
            if (endnodes == false)
                CHILDREN[i]->countkeys_less_case2(key, count, id);
            //cout << " " << pair[i].key << " " << pair[i].a;
            if (pair[i].key == id)
            {

            }

            else if (pair[i].key > id && pair[i].key <= key)
            {
                count++;
            }



        }

        if (endnodes == false)
            CHILDREN[i]->countkeys_less_case2(key, count, id);
    }

    void count_total_keys(int& count)
    {
        int i;
        for (i = 0; i < values; i++)
        {
            if (endnodes == false)
                CHILDREN[i]->count_total_keys(count);
            //cout << " " << pair[i].key << " " << pair[i].a;
            count++;



        }

        if (endnodes == false)
            CHILDREN[i]->count_total_keys(count);
    }

    void store_elements_array(int& count, SinglyNode* arr)
    {
        int i;
        for (i = 0; i < values; i++)
        {
            if (endnodes == false)
                CHILDREN[i]->store_elements_array(count, arr);
            //cout << " " << pair[i].key << " " << pair[i].a;
            //count++;
            arr[count] = pair[i];

            //strcpy(arr[count].a, b);  
            //arr[count].a = b1;

            count++;



        }

        if (endnodes == false)
            CHILDREN[i]->store_elements_array(count, arr);
    }


    void insert_duplicate(long double key, string text)
    {
        int i;
        for (i = 0; i < values; i++) {
            if (endnodes == false)
                CHILDREN[i]->insert_duplicate(key, text);
            //cout << " " << pair[i].key << " " << pair[i].a;
            if (pair[i].key == key)
            {
                SinglyNode* newnode = new SinglyNode();
                newnode->key = key;
                newnode->a = text;
                SinglyNode* temp = pair;
                while (temp->next != nullptr)
                {
                    temp = temp->next;
                }
                temp->next = newnode;
                return;

            }
        }

        if (endnodes == false)
            CHILDREN[i]->insert_duplicate(key, text);
    }

    bool search_for_key(long double k)
    {
        if (pair == nullptr)
            return false;
        int i = 0;
        while (i < values && k > pair[i].key)
            i++;

        if (pair[i].key == k)
            return true;

        if (endnodes == true)
            return false;

        return CHILDREN[i]->search_for_key(k);
    }

    void  search_for_value(long double k, string& ans)
    {
        int i = 0;
        while (i < values && k > pair[i].key)
            i++;

        if (pair[i].key == k)
        {
            ans = pair[i].a;
            return ;
        }

        if (endnodes == true)
            return;

        return CHILDREN[i]->search_for_value(k, ans); 
    }


    int searchkey(long double  k)
    {
        int idx = 0;
        while (idx < values && pair[idx].key < k)
            ++idx;
        return idx;
    }
    void delete_btree1(long double k, int idx)
    {
        if (endnodes)
            leafremoval(idx);
        else
            nonleafremoval(idx);
    }
    void delete_btree2(long double k, int idx)
    {
        bool flag = ((idx == values) ? true : false);
        if (CHILDREN[idx]->values < max)
            fillnode(idx);
        if (flag && idx > values)
            CHILDREN[idx - 1]->delete_btree(k);
        else
            CHILDREN[idx]->delete_btree(k);
    }
    bool  delete_btree(long double k) {
        int idx = searchkey(k);
        if (idx < values && pair[idx].key == k) {
            delete_btree1(k, idx);
        }
        else {
            if (endnodes) {
                cout << "key " << k << " does not exist in the tree\values";
                return false;
            }
            delete_btree2(k, idx);
        }
        return true;
    }
    // Remove from the endnodes
    void leafremoval(int idx) {
        for (int i = idx + 1; i < values; ++i)
            pair[i - 1] = pair[i];
        values--;
        return;
    }
    // Delete from non endnodes node
    void nonleafremoval1(int idx)
    {
        int pred = predecessor(idx);
        pair[idx].key = pred;
        CHILDREN[idx]->delete_btree(pred);
    }
    void nonleafremoval2(int idx)
    {
        int succ = successor(idx);
        pair[idx].key = succ;
        CHILDREN[idx + 1]->delete_btree(succ);
    }
    void nonleafremoval(int idx) {
        int k = pair[idx].key;
        if (CHILDREN[idx]->values >= max) {
            nonleafremoval1(idx);
        }
        else if (CHILDREN[idx + 1]->values >= max) {
            nonleafremoval2(idx);
        }
        else {
            combine(idx);
            CHILDREN[idx]->delete_btree(k);
        }
        return;
    }

    int predecessor(int idx) {
        Node* cur = CHILDREN[idx];
        while (!cur->endnodes)
            cur = cur->CHILDREN[cur->values];
        return cur->pair[cur->values - 1].key;
    }
    int successor(int idx) {
        Node* cur = CHILDREN[idx + 1];
        while (!cur->endnodes)
            cur = cur->CHILDREN[0];
        return cur->pair[0].key;
    }
    void fillnode(int idx) {
        if (idx != 0 && CHILDREN[idx - 1]->values >= max)
            prevborrow(idx);
        else if (idx != values && CHILDREN[idx + 1]->values >= max)
            nextborrow(idx);
        else {
            if (idx != values)
                combine(idx);
            else
                combine(idx - 1);
        }
        return;
    }
    // Borrow from previous
    void prevborrow1(int idx, Node* child, Node* sibling)
    {
        child->pair[0] = pair[idx - 1];
        if (!child->endnodes)
            child->CHILDREN[0] = sibling->CHILDREN[sibling->values];
        pair[idx - 1] = sibling->pair[sibling->values - 1];
        child->values += 1;
        sibling->values -= 1;
    }
    void prevborrow(int idx) {
        Node* child = CHILDREN[idx];
        Node* sibling = CHILDREN[idx - 1];
        for (int i = child->values - 1; i >= 0; --i)
            child->pair[i + 1] = child->pair[i];
        if (!child->endnodes) {
            for (int i = child->values; i >= 0; --i)
                child->CHILDREN[i + 1] = child->CHILDREN[i];
        }
        prevborrow1(idx, child, sibling);
        return;
    }
    // Borrow from the next
    void nextborrow1(int idx, Node* child, Node* sibling)
    {
        pair[idx] = sibling->pair[0];
        for (int i = 1; i < sibling->values; ++i)
            sibling->pair[i - 1] = sibling->pair[i];
        if (!sibling->endnodes) {
            for (int i = 1; i <= sibling->values; ++i)
                sibling->CHILDREN[i - 1] = sibling->CHILDREN[i];
        }
        child->values += 1;
        sibling->values -= 1;
    }
    void nextborrow(int idx) {
        Node* child = CHILDREN[idx];
        Node* sibling = CHILDREN[idx + 1];
        child->pair[(child->values)] = pair[idx];
        if (!(child->endnodes))
            child->CHILDREN[(child->values) + 1] = sibling->CHILDREN[0];
        nextborrow1(idx, child, sibling);
        return;
    }
    void combine1(int idx, Node* child, Node* sibling)
    {
        if (!child->endnodes) {
            for (int i = 0; i <= sibling->values; ++i)
                child->CHILDREN[i + max] = sibling->CHILDREN[i];
        }
        for (int i = idx + 1; i < values; ++i)
            pair[i - 1] = pair[i];
        for (int i = idx + 2; i <= values; ++i)
            CHILDREN[i - 1] = CHILDREN[i];
        child->values += sibling->values + 1;
        values--;
        delete (sibling);
    }
    void combine(int idx) {
        Node* child = CHILDREN[idx];
        Node* sibling = CHILDREN[idx + 1];
        child->pair[max - 1] = pair[idx];
        for (int i = 0; i < sibling->values; ++i)
            child->pair[i + max] = sibling->pair[i];
        combine1(idx, child, sibling);
        return;
    }
    friend class BTree;

};

class BTree {
public:
    Node* root;
    int max;

public:
    BTree(int max = 3) {
        root = NULL;
        this->max = max;
    }

    void traverse() {
        if (root != NULL)
            root->traverse();
    }
    bool search_key(long double key)
    {
        if (root == nullptr)
            return false;
        bool a = root->search_for_key(key);
        return a;
    }


    /* Insert the node */
    void insert1(long double  k, string x)
    {
        if (root->values == 2 * max - 1) {
            Node* s = new Node(max, false, x);

            s->CHILDREN[0] = root;

            s->childsplit(0, root, x);

            int i = 0;
            if (s->pair[0].key < k)
                i++;
            s->CHILDREN[i]->nonempty(k, x);

            root = s;
        }
        else
            root->nonempty(k, x);
    }
    void insert2(long double  k, string x)
    {
        root = new Node(max, true, x);
        root->pair[0].key = k;
        root->pair[0].a = x;
        root->values = 1;
    }
    void insert(long double  k, string x) {
        if (root == NULL) {
            insert2(k, x);
        }
        else {
            insert1(k, x);
        }
    }

    void insert_duplicate(long double key, string text)
    {
        root->insert_duplicate(key, text);
    }

    bool delete_btree(long double k) {
        if (!root) {
            cout << "The tree is empty\values";
            return false;
        }
        bool val = root->delete_btree(k);
        if (root->values == 0) {
            Node* tmp = root;
            if (root->endnodes)
                root = NULL;
            else
                root = root->CHILDREN[0];
            delete tmp;
        }
        return val;
    }
    void  singlynode_retrival(SinglyNode& obj, long double key, int id)
    {
        root->singlynode_retrival(obj, key, id);
    }

    void  singlynode_retrival_case1(SinglyNode& obj, long double key, int id)
    {
        root->singlynode_retrival_case1(obj, key, id);
    }

    void  singlynode_retrival_case2(SinglyNode& obj, long double key, int id)
    {
        root->singlynode_retrival_case2(obj, key, id);
    }

    void countkeys_less(long double key, int& count, int id)
    {
        if (root == nullptr)
            return;
        root->countkeys_less(key, count, id);
    }
    void count_total_keys(int& count)
    {
        root->count_total_keys(count);
    }
    void store_elements_array(int& count, SinglyNode* arr)
    {
        root->store_elements_array(count, arr);
    }

    void search_for_value(long double k, string& ans)
    {
        root->search_for_value(k, ans);
    }
    void countkeys_less_case1(long double key, int& count, int id)
    {
        //cout << key << " " << id << "---------!!!!" << endl;
        if (root == nullptr)
            return;
        root->countkeys_less_case1(key, count, id);
    }

    void countkeys_less_case2(long double key, int& count, int id)
    {
        //cout << key << " " << id << "---------!!!!" << endl;
        if (root == nullptr)
            return;
        root->countkeys_less_case2(key, count, id);
    }

};


// below are the implementations of machine class ring dht and they contain the eouting table as well
class Machine
{
public:
    long double  ID;
    Machine* next;
    BTree btree;
    Machine** Routingtable;

    Machine()
    {
    }

    Machine(long double  val)
    {
        ID = val;
        next = nullptr;

    }
    void printtable(int bits)
    {
        cout << "--------------------------------" << endl;
        cout << "ID: " << ID << endl;
        for (int i = 0; i < bits; i++)
        {
            cout << "|     2^" << i << '=' << Routingtable[i]->ID << "      |" << endl;
        }
        cout << "---------------------------------" << endl;
    }
};


class RingDHT
{
public:
    Machine* head;
    long double Bits;
    long double count;
    long double total_machines;

    RingDHT()
    {
        head = nullptr;
        count = 0;
    }
    RingDHT(long double Bits)
    {
        head = nullptr;
        this->Bits = Bits;
        count = 0;
    }
    void insert1(Machine** head_ref, long double key, Machine* new_node) 
    {
        new_node->next = new_node;
        *head_ref = new_node;
    }
    void insert2(Machine** head_ref, long double key, Machine* new_node, Machine* current)
    {
        while (current->next != *head_ref)
            current = current->next;
        current->next = new_node;
        new_node->next = *head_ref;
        *head_ref = new_node;
    }
    void insert3(Machine** head_ref, long double key, Machine* new_node, Machine* current)
    {
        while (current->next != *head_ref &&
            (current->next->ID) < (new_node->ID))
            current = current->next;

        new_node->next = current->next;
        current->next = new_node;
    }

    void insert(Machine** head_ref, long double key)
    {
        Machine* new_node = new Machine(key); 
        Machine* current = *head_ref;

        
        if (current == NULL)
        {
            insert1(head_ref, key, new_node);
        }

         
        else if (current->ID >= new_node->ID)
        {
            
            insert2(head_ref, key, new_node, current);
        }

        
        else
        {
            
            insert3(head_ref, key, new_node, current);
        }
        count++;
        Make_Routing_Table();
        
    }

    Machine* getHead()
    {
        return head;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    bool search(long double data)
    {
        if (head == nullptr)
            return false;
        Machine* temp = head;
        while (temp->next != head && temp->ID != data)
        {
            temp = temp->next;
        }
        return temp->ID == data;
        
    }
    Machine* search_to_return_machine(long double data)
    {
        if (head == nullptr)
            return nullptr;
        Machine* temp = head;
        while (temp->next != head && temp->ID != data)
        {
            temp = temp->next;
        }
        return temp;
    }

    

    void insertAtIndex(long double  data, int index)
    {
        int id = 0;
        Machine* temp = new Machine(data);
        Machine* ptr = head;
        Machine* newn = head;
        int i = 0;

        while (ptr->next != head && id < index)
        {
            if (i != 0)
            {
                newn = newn->next;
            }
            ptr = ptr->next;
            id++;
            i++;
        }

        if (id == index - 1)
        {
            ptr->next = temp;
            temp->next = head;
        }
        else if (id == index)
        {
            temp->next = ptr;
            newn->next = temp;
        }
    }

    void print()
    {
        if (head == nullptr)
            return;
        long double number = 1;
        Machine* temp = head;
        cout << "                        -------------------------------------" << endl;
        do
        {

            cout << "                        | MACHINE: " << number << "-> ID: " << temp->ID << "                |" << endl;
            number++;
            temp = temp->next;
        } while (temp != head);
        cout<<"                       ---------------------------------------" << endl;
    }
    void print_btree()
    {
        if (head == nullptr)
            return;
        long double number = 1;
        cout << "                        -------------------------------------" << endl;
        Machine* temp = head;
        do
        {

            cout << "                        | MACHINE: " << number << "-> ID: " << temp->ID << "   TREE--->";

            temp->btree.traverse() ;
            //cout << "                                                                                  |" << endl;
            temp = temp->next;

            number++;
            cout << endl;
        } while (temp != head);
        cout << "                       ---------------------------------------" << endl;
    }
    bool search_key(long double key)
    {
       Machine* temp = head;
       bool b = false;
       do
       {
           if (temp->btree.root != nullptr)
           {
                b = temp->btree.search_key(key);
                if (b)
                {
                    //cout << temp->ID << " ";
                    break;
                }
               //return b;
           }
           temp = temp->next;
       } while (temp != head);
       
       return b;
    }

    

    void counter()
    {
        Machine* temp = head;
        do
        {
            long double x = temp->ID;
            int count = 0;
            Machine* temp1 = head;
            do
            {
                if (x == temp1->ID)
                    count++;
                temp1 = temp1->next;
            } while (temp1 != head);
            cout << x << " " << count << endl;
            temp = temp->next;
        } while (temp != head);
    }

    void deleteData(long double  data)
    {
        if (isEmpty())
        {
            return;
        }

        Machine* temp = head;
        Machine* ptr = head;
        while (ptr->next != head)
        {
            ptr = ptr->next;
        }

        if (temp->ID == data)
        {
            Machine* newn = head;
            head = head->next;
            ptr->next = head;
            delete newn;
        }
        else
        {
            bool hello = false;
            while (temp->next != head)
            {
                if (temp->next->ID == data)
                {
                    hello = true;
                    break;
                }
                temp = temp->next;
            }

            if (hello)
            {
                if (temp->next->next == head)
                {
                    Machine* newn = temp->next;
                    temp->next = head;
                    delete newn;
                }
                else
                {
                    Machine* newn = temp->next;
                    temp->next = temp->next->next;
                    delete newn;
                }
            }
        }
        count--;
        if (count!=0)
            Make_Routing_Table();
    }

    void Print_Routing_Table()
    {
        Machine* current = head;
        do
        {
            current->printtable(Bits);
            current = current->next;

        } while (current != head);
    }
    void Make_Routing_Table()
    {
        Machine* current = head;
        do
        {
            Machine_Routing_Table(current);
            current = current->next;

        } while (current != head);
    }

    void Machine_Routing_Table(Machine* Head)
    {
        Head->Routingtable = new Machine * [Bits];

        for (int i = 0; i < Bits; i++)
        {
            Machine* current = Head->next;
            bool check = 0;
            long long int hash = Head->ID + pow(2, i);
            if (hash >= pow(2, Bits))
                check = true;

            long long int power = pow(2, Bits);
            hash = hash % power;
            //cout << "2^" << i << ' ' << hash << ' ' << Head->ID << endl;;
            if (current->ID > hash && !check)
            {
                Head->Routingtable[i] = current;
               // cout << "hheelo" << endl;

            }
            else
            {
                //cout << "hheelo1" << endl;

                if (!check)
                {
                    while (current->ID < hash)
                    {
                        if (current->ID <= Head->ID)
                            break;
                        current = current->next;
                        //cout << "hheelo111" << endl;

                    }
                    Head->Routingtable[i] = current;
                }
                else
                {
                    while (current->ID < hash || current->ID>Head->ID)
                    {
                        //cout << "hheelo222" << endl;

                        current = current->next;
                    }
                    Head->Routingtable[i] = current;
                }
            }

        }
        //cout << "hheelo" << endl;
    }
    Machine* searchMachine(long double hash, Machine* Head, long double machine_count)
    {
        if (Head->ID == hash)
            return head;
    Machine* temp = Head;
    Machine* temp2 = head;
    bool loopover = false;
    int count = 0;
    string ans = "";
    long double a =0;
    while (Head->ID < hash && !loopover)
    {
        //cout << Head->ID << "->" << endl;
        a = Head->ID;
        ans += to_string(a);
        ans += "->";
        for (int i = 0; i < Bits; i++)
        {
            if (Head->Routingtable[i]->ID <= hash)
            {
                while (temp->ID < Head->Routingtable[i]->ID)
                {
                    temp = Head->Routingtable[i];
                    break;
                }
            }
            if (Head->Routingtable[0]->ID >= hash)
            {
                Head = Head->Routingtable[0];
                //cout << "Machine:  " << Head->ID << endl;
                a = Head->ID;
                ans += to_string(a);
                cout << ans << endl;
                return Head;
            }
        }
        Head = temp;
        count++;
        if (count == machine_count)
            loopover = true;

    }
    if (loopover)
    {
        //cout << "Machine: " << head->ID << endl;
        ans = to_string(head->ID);
        cout << ans << endl;
        return head;
    }
    /* if (start->RTable[0]->id >= tofind)
     {
         return start;
     }*/
    if (Head->ID >= hash)
    {
        //cout << "Machine  " << Head->ID << endl;
        a = Head->ID;
        ans += to_string(a);
        cout << ans << endl;
        return Head;
    }


    // cout << " Machine: " << current->ID << endl;
     //return current;
    }
    void tail_value(long double& tail)
    {
        if (head == nullptr)
            return;
        //long double number = 1;
        Machine* temp = head;
        
        do
        {

                            
           // number++;
            temp = temp->next;
        } while (temp->next != head);
        tail = temp->ID;
        
    }
};



long double  binaryToInt(const string& binaryString) {
    bitset<32> bits(binaryString);  // Assuming a 32-bit integer, adjust as needed
    return static_cast<long double>(bits.to_ulong());
}
long double power(long double x, long double y)
{
    long double result = 1;
    for (int i = 0; i < y; i++)
    {
        result *= x;
    }
    return result;
}
long double  hash_func(string a, int bits, RingDHT& ring, long double& max_value, bool variable)
{
	int hexa = 0;
    if (bits % 4 ==  0)
    {
        hexa = bits / 4;
    }
    else
    {
        hexa = bits / 4;
        hexa += 1;
    }

    //cout << hexa << endl;
	string capture = "";
    //cout << a.length() << endl;
    //cout << a << endl;
   // bool flag = true;
    //cout << hexa << endl;
	for (int j = 0; j < hexa;j++)
	{
        capture+= a[j];
		    
            
    }
	//cout << capture << endl;
	string binary_string = "";
	for (int j = 0; capture[j] != '\0'; j++)
	{
		if (capture[j] == '0')
		{
			binary_string += "0000";
		}
		else if (capture[j] == '1')
		{
			binary_string += "0001";
		}
		else if (capture[j] == '2')
		{
			binary_string += "0010";
		}
		else if (capture[j] == '3')
		{
			binary_string += "0011";
		}
		else if (capture[j] == '4')
		{
			binary_string += "0100";
		}
		else if (capture[j] == '5')
		{
			binary_string += "0101";
		}
		else if (capture[j] == '6')
		{
			binary_string += "0110";

		}
		else if (capture[j] == '7')
		{
			binary_string += "0111";
		}
		else if (capture[j] == '8')
		{
			binary_string += "1000";
		}
		else if (capture[j] == '9')
		{
			binary_string += "1001";
		}
		else if (capture[j] == 'a' || capture[j] == 'A')
		{
			binary_string += "1010";
		}
		else if (capture[j] == 'b' || capture[j] == 'B')
		{
			binary_string += "1011";
		}
		else if (capture[j] == 'c' || capture[j] == 'C')
		{
			binary_string += "1100";
		}
		else if (capture[j] == 'd' || capture[j] == 'D')
		{
			binary_string += "1101";

		}
		else if (capture[j] == 'e' || capture[j] == 'E')
		{
			binary_string += "1110";
		}
		else
		{
			binary_string += "1111";
		}

	}
    //cout << binary_string << endl;
	string resultant_string = "";

	//cout << hexa << endl;
	for (int i = 0; i < bits; i++)
	{
		resultant_string += binary_string[i];
	}
	for (int i = 0, j = resultant_string.length() - 1; i < j; i++, j--) {
		// Swap characters at positions i and j
		swap(resultant_string[i], resultant_string[j]);
	}
    long double result = binaryToInt(resultant_string);
    if (variable)
    {
        bool flag = true;
        while (flag)
        {
            bool var = ring.search(result);
            if (!var)
                break;
            result += 1;
            if (result > max_value)
                result = 0;


        }
    }
    return result;
	//cout << resultant_string << endl;
	//int to_store_id = 0; // final id of machine after padding 
}
// to insert the data at the required machines ie only on ones
void insert_machines_data(long double key, string text, RingDHT& ring, long double max_value)
{
    /*bool repeated = false;
    repeated = ring.search_key(key);
    if (repeated)
    {
        Machine* temp = ring.search_key_machine(key);
        temp->btree.insert_duplicate(key, text);

    }*/
    //else
    //{
        bool variable = ring.search(key);
        if (variable)
        {
            Machine* temp = ring.search_to_return_machine(key);
            temp->btree.insert(key, text);
        }
        else
        {
            //long double key_copy = key + 1;
            ////cout << key_copy << endl;
            ////cout
            //if (key_copy > max_value)
            //    key_copy = 0;
            ////cout <<max_value << endl;
            //bool stop = false;
            //while (!stop)
            //{
            //    //cout << key_copy << endl;
            //    stop = ring.search(key_copy);
            //    if (stop)
            //        break;
            //    key_copy++;
            //    if (key_copy > max_value)
            //        key_copy = 0;
            //}

           // Machine* temp = ring.search_to_return_machine(key_copy);
            Machine* temp = ring.searchMachine(key+1,ring.head,ring.total_machines) ;
            temp->btree.insert(key, text);
        }
    //}
    return;
    
}

void update_machine_data(long double key, RingDHT& ring, long double max_value, long double machine_number, long double tail_value) 
{
    //cout << ring.count << "---------------------------------!!!!" << endl;
    if (ring.count == 2)
    {
        int count = 0;
        cout << tail_value << endl;
        //cout << ring.head->ID;
        if (key < tail_value)
        {
            long double key_copy = key + 1;
            if (key_copy > max_value)
            {
                key_copy = 0;
                //round = true;
            }
            //ring.head->btree.countkeys_less_case1(key, count, ring.head->ID); 
            Machine* temp = ring.searchMachine(key_copy, ring.head, machine_number);
            long double id = temp->ID;
            temp->btree.countkeys_less_case1(key, count, id); 
            SinglyNode obj; 
            for (int i = 0; i < count; i++) 
            {
                temp = ring.searchMachine(key_copy, ring.head, machine_number); 
                long double  id = temp->ID; 
                temp->btree.singlynode_retrival_case1(obj, key, id); 

                //cout << obj.key << endl;
                //if (obj.key != temp->ID)
                //{
                temp->btree.delete_btree(obj.key); 

                temp = ring.searchMachine(key, ring.head, machine_number -1); 
                temp->btree.insert(obj.key, obj.a); 
                //}
            } 
            

        }
        
        else if (key > ring.head->ID)
        {
            long double key_copy = key + 1;
            if (key_copy > max_value)
            {
                key_copy = 0;
                //round = true;
            }
            //ring.head->btree.countkeys_less_case1(key, count, ring.head->ID); 
            Machine* temp = ring.searchMachine(key_copy, ring.head, machine_number);
            long double id = temp->ID;
            temp->btree.countkeys_less_case2(key, count, id);
            SinglyNode obj;
            cout << count << endl;
            
            for (int i = 0; i < count; i++)
            {
                temp = ring.searchMachine(key_copy, ring.head, machine_number);
                long double  id = temp->ID;
                temp->btree.singlynode_retrival_case2(obj, key, id); 

                //cout << obj.key << endl;
                //if (obj.key != temp->ID)
                //{
                temp->btree.delete_btree(obj.key);

                temp = ring.searchMachine(key, ring.head, machine_number - 1);
                temp->btree.insert(obj.key, obj.a);
                //}
            }
        }
        //cout << count << endl;
    }
    else if (ring.count > 2)
    {

        long double key_copy = key + 1;
        if (key_copy > max_value)
            key_copy = 0;
        Machine* temp = ring.searchMachine(key_copy, ring.head, machine_number);
        int count = 0;
        if (temp->ID == ring.head->ID)
        {
            long double key_copy = key + 1;
            if (key_copy > max_value)
            {
                key_copy = 0;
                //round = true;
            }
            //ring.head->btree.countkeys_less_case1(key, count, ring.head->ID); 
            Machine* temp = ring.searchMachine(key_copy, ring.head, machine_number);
            long double id = temp->ID;
            temp->btree.countkeys_less_case2(key, count, id);
            SinglyNode obj;
            cout << count << endl;

            for (int i = 0; i < count; i++)
            {
                temp = ring.searchMachine(key_copy, ring.head, machine_number);
                long double  id = temp->ID;
                temp->btree.singlynode_retrival_case2(obj, key, id);

                //cout << obj.key << endl;
                //if (obj.key != temp->ID)
                //{
                temp->btree.delete_btree(obj.key);

                temp = ring.searchMachine(key, ring.head, machine_number - 1);
                temp->btree.insert(obj.key, obj.a);
                //}
            }
        }
        /*
        bool stop = false;
        bool round = false;
        while (!stop)
        {
            stop = ring.search(key_copy);
            if (stop)
                break;
            key_copy++;
            if (key_copy > max_value)
            {
                key_copy = 0;
                round = true;
            }
        }*/
        
        else
        {
            long double key_copy = key + 1;
            if (key_copy > max_value)
            {
                key_copy = 0;
                //round = true;
            }
            Machine* temp = ring.searchMachine(key_copy, ring.head, machine_number);

            //cout << temp->ID << "--------------------------------" << endl;
            int id = temp->ID;
            temp->btree.countkeys_less(key, count, id);
            //cout << count << endl;
            //if (round)
              //  count--; 

            //cout << count << endl;
            SinglyNode obj;
            for (int i = 0; i < count; i++)
            {
                temp = ring.searchMachine(key + 1, ring.head, machine_number);
                long double  id = temp->ID;
                temp->btree.singlynode_retrival(obj, key, id);

                //if (obj.key != temp->ID)
                //{
                temp->btree.delete_btree(obj.key);

                temp = ring.searchMachine(key, ring.head, machine_number - 1);
                temp->btree.insert(obj.key, obj.a);
                //}
            }
        }

    }
    //ring.insert(&ring.head, key);
    

    


    //temp->btree.traverse();

    //cout << temp->ID << endl;
}

// to delete a machie and shift its data to next machine 
void delete_machine_shift(long double key, RingDHT& ring, long double max_value, long double machine_number)
{
    
    if (ring.count > 1)
    {

        //Machine* temp1 = ring.search_to_return_machine(key); // contains the machine that needs to be deleted 
        //Machine* temp2 = temp1->next; // conatins the machine which will store the data of the machine that is to be deleted
        //cout << temp2->ID << endl;

        Machine* temp1 = ring.searchMachine(key, ring.head, machine_number);
        if (temp1->btree.root == nullptr)
        {
            ring.deleteData(key);
            return;
        }

        Machine* temp2 = ring.searchMachine(key+1, ring.head, machine_number);
        cout << temp1->ID << " " << temp2->ID << endl;



        int count = 0;
        temp1->btree.count_total_keys(count);
        //cout << count << endl;
        SinglyNode* array = new SinglyNode[count];// to store the elements of the machine to be deleted 
        //string* array1 = new string[count];


        count = 0;
        temp1->btree.store_elements_array(count, array);
        for (int i = 0; i < count; i++)
        {

            temp1->btree.delete_btree(array[i].key);
            temp2->btree.insert(array[i].key, array[i].a);
        }
        ring.deleteData(key);
        //ring.print_btree();
        //cout << count << endl;
    }
    else
        ring.deleteData(key);
    return;


    



}

//int visual(RingDHT ring) {
//
//    // Create a window
//    sf::RenderWindow window(sf::VideoMode(1000, 900), "SFML Background");
//    window.setSize(Vector2u(1280, 1280)); // Recommended for 2560x1440 (1440p) displays.
//    sf::Texture backgroundTexture;
//    if (!backgroundTexture.loadFromFile("Images/deda4bf8d4bb7ea1e493f3e0ed35b7697eab3335132750dee7a590c93f73d831a58a.jpg")) {
//        // Handle error if the texture fails to load
//        return 0;
//    }
//    ///////////////////////////////////////// Player_score
//    Font style;
//    style.loadFromFile("Images/Algerian Regular.ttf");
//    Text text;
//    text.setFont(style);
//    text.setCharacterSize(50);
//    text.setFillColor(sf::Color::Red);
//    text.setPosition(110, 90);
//    int num = ring.count;
//    string id = "MACHINE ID :";
//    Text* Player_score = new Text[num];
//    Machine* current = ring.head;
//    Texture t;
//    t.loadFromFile("Images/table.png");
//    Sprite Table(t);
//    Table.setScale(0.2, 0.2);
//    int j = 0;
//    bool clicked = 0;
//    do
//    {
//        id = "MACHINE ID :";
//        int sp = current->ID;
//        id += to_string(sp);
//        Player_score[j].setString(id);
//        current = current->next;
//        j++;
//    } while (current != ring.head);
//    /////////////////////////////for score text
//    for (int i = 0; i < num; i++)
//    {
//        Player_score[i].setFont(style);
//        Player_score[i].setCharacterSize(50);
//        Player_score[i].setFillColor(sf::Color::Red);
//        // Player_score[i].setString("MACHINE ID :3");
//        Player_score[i].setScale(0.3, 0.3);
//    }
//    // Create a sprite for the background
//    sf::Sprite backgroundSprite(backgroundTexture);
//    Texture mach;
//    mach.loadFromFile("Images/space-ship.png");
//    Sprite machine[10];
//    for (int i = 0; i < num; i++)
//    {
//        machine[i].setTexture(mach);
//        machine[i].setScale(0.1, 0.1);
//        // machine[i].setPosition(100, 100);
//    }
//
//    // Main loop
//    while (window.isOpen()) {
//        // Event handling
//        sf::Event event;
//        while (window.pollEvent(event)) {
//            if (event.type == sf::Event::Closed) {
//                window.close();
//            }
//            else if (event.type == sf::Event::MouseButtonPressed) {
//                // Check if the mouse button is pressed and if the cursor is over the sprite
//                if (event.mouseButton.button == sf::Mouse::Left) {
//                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
//                    sf::Vector2f spritePosition = machine[0].getPosition();
//                    sf::Vector2f spriteSize = static_cast<sf::Vector2f>(machine[0].getTexture()->getSize());
//
//                    if (mousePosition.x >= spritePosition.x &&
//                        mousePosition.x <= spritePosition.x + spriteSize.x &&
//                        mousePosition.y >= spritePosition.y &&
//                        mousePosition.y <= spritePosition.y + spriteSize.y) {
//                        // The mouse is over the sprite, perform interaction
//                        Table.setPosition(machine[0].getPosition().x + 60, machine[0].getPosition().y + 20);
//                        // window.draw(Table);
//                        clicked++;
//                        std::cout << "Sprite Clicked!" << std::endl;
//                    }
//                }
//            }
//        }
//        sf::Vector2f backgroundPosition(0.0f, 0.0f);
//        backgroundSprite.setPosition(backgroundPosition);
//
//        // Define the speed at which the background moves
//        float backgroundSpeed = 100.0f; // You can adjust the speed as needed
//
//        float deltaTime = 0.1f; // You should calculate the actual deltaTime
//        backgroundPosition.x += backgroundSpeed * deltaTime;
//
//        // Reset the background position when it goes beyond the window width
//        if (backgroundPosition.x > window.getSize().x + 50) {
//            backgroundPosition.x = 0.0f;
//        }
//
//        // Set the new position of the background sprite
//        backgroundSprite.setPosition(backgroundPosition);
//        circle(machine, Player_score, num);
//        // Clear the window
//        window.clear();
//
//        // Draw the background
//        window.draw(backgroundSprite);
//        for (int i = 0; i < num; i++)
//        {
//            window.draw(Player_score[i]);
//            window.draw(machine[i]);
//        }
//        if (clicked % 2 == 1)
//            window.draw(Table);
//        else
//        {
//            Table.setPosition(-100, -100);
//            window.draw(Table);
//
//
//        }
//        // Display the contents of the window
//        window.display();
//    }
//
//    return 0;
//}
//
//
//void circle(Sprite* machine, Text* sc, int num)
//{
//    int radius = 250; // set the radius of the circle
//    int numPositions = num; // set the number of positions in the circle
//    float centerX = 450; // set the x-coordinate of the center of the circle
//    float centerY = 350; // set the y-coordinate of the center of the circle
//    float angleStep = 360.0f / numPositions; // calculate the angle between each position in the circle
//
//    // loop through each position in the circle and calculate its x and y coordinates based on the angle
//    for (int i = 0; i < numPositions; i++)
//    {
//        float angle = i * angleStep;
//        float x = centerX + radius * cos(angle * 3.14159f / 180.0f);
//        float y = centerY + radius * sin(angle * 3.14159f / 180.0f);
//
//        // cout << x << "   " << y << endl;
//        sc[i].setPosition(x - 20, y - 15);
//
//        machine[i].setPosition(sf::Vector2f(x, y)); // set the position of the corresponding circle object
//        //enm[i].setScale(0.35, 0.35);
//
//
//
//    }
//}

int main()
{
    srand(time(0));
    int bits = 0;
    int total_machines = 0;
    //long double machine_id = 0; // to delete the machine id or to insert data at this machine 
    
    long double  machine_number = 1;
	
    
    bool inputstop = false;

    // to ask the user to input the indentifier space and also the total machines before beginning
    cout << "HELLO, BEFORE WE BEGIN , WE WOULD LIKE TO KNOW TO KNOW A COUPLE OF THINGS" << endl;
    cout << " PLEASE ENTER THE IDENTIFIER SPACE: " << endl;
    cin >> bits;
    cout << " PLEASE ENTER THE TOTAL NUMBER OF MACHINES YOU WOULD LIKE TO INPUT INITIALLY: " << endl; 
    cin >> total_machines;

    long double  max_value = power(2, bits) - 1;
    RingDHT ring(bits); 

    ring.total_machines = total_machines;
    //Machine* tail = nullptr;
    long double tail_value = 0; // to store the last element value of the RING
    while (!inputstop)
    {
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << "----------------------------MENU--------------------------------------------------" << endl;
        cout << " 1. INSERT A NEW MACHINE" << endl;         
        cout << " 2. INSERT FILES " << endl;
        cout << " 3. DELETE FILES " << endl;         
        cout << " 4. DISPLAY ROUTING TABLE " << endl; 
       
        cout << " 5. DELETE A MACHINE " << endl;
        cout << " 6. SEARCH FOR A FILE " << endl; 
        cout << " 7. PRINT BTREE " << endl;
        cout << " 8. PRINT THE FLY " << endl;
        cout << " 9. VISUAL DHT" << endl;
        cout << " 10. EXIT THE STRUCTURE " << endl;
        int choice = 0;
        cout << " PLEASE ENTER A CHOICE: " << endl;
        cin >> choice;
        while (choice <= 0 || choice >10)
        {
            cout << "PLEASE ENTER A VALID CHOICE: " << endl;
            cin >> choice;
        }
        if (choice == 1)
        {
            if (machine_number <= total_machines)
            {
                cout << " WOULD YOU LIKE TO ASSIGN ID MANULLAY OR AUTOMATICALLY? " << endl;
                int machine_choice = 0;
                cout << "1. MANUAL" << endl;
                cout << " 2. AUTOMATIC" << endl;
                cin >> machine_choice;
                while (machine_choice <= 0)
                {
                    cout << "PLEASE ENTER A VALID CHOICE: " << endl;
                    cin >> machine_choice;
                }
                if (machine_choice == 1)
                {
                    cout << "PLEASE ENTER THE KEY(ID) OF THE MACHINE: " << endl;
                    long double  machine_id = 0;
                    cin >> machine_id;
                    bool val = ring.search(machine_id);
                    while (val)
                    {
                        cout << "OOPS THIS KEY ALREADY EXISTS ON THE FLY, PLEASE ENTER ANOTHER ID " << endl;
                        cin >> machine_id;
                        val = ring.search(machine_id);
                    }
                    
                    //cout << ring.head->ID << endl;
                    cout << "MACHINE INPUT WAS A SUCCESS" << endl;
                    ring.insert(&ring.head, machine_id);
                    if (ring.count == 1)
                    {
                        tail_value = ring.head->ID;
                    }
                    else
                    {
                        ring.tail_value(tail_value); 
                    }
                    cout << tail_value << endl;
                    machine_number++;
                    update_machine_data(machine_id, ring, max_value, machine_number, tail_value); 
                    



                }

                else
                {
                    string a = "MACHINE";
                    string b = to_string(machine_number);
                    a += b;
                    a = sha1(a);
                    long double result = hash_func(a, bits, ring, max_value, true);
                    ring.insert(&ring.head,result);
                    if (ring.count == 1)
                    {
                        tail_value = ring.head->ID;
                    }
                    else
                    {
                        ring.tail_value(tail_value); 
                    }
                    //cout << result;
                    machine_number++;
                    cout << "MACHINE INPUT WAS A SUCCESS" << endl;
                    update_machine_data(result, ring, max_value, machine_number, tail_value); 
                }
            }
            else
                cout << " SORRY, MAX LIMIT HAS BEEN REACHED " << endl;
        }
        else if (choice == 2)
        {
            if (ring.head == nullptr)
                cout << "PLEASE ENTER A MACHINE SO AS TO ADD DATA" << endl;
            else
            {
                cout << "WOULD YOU LIKE TO SPECIFY THE KEY OF YOUR DATA?" << endl;
                cout << " 1. MANUAL" << endl;
                cout << " 2. AUTOMATIC" << endl;
                int choice2 = 0;
                cout << " PLEASE ENTER A CHOICE: " << endl;
                cin >> choice2;
                while (choice <= 0 || choice > 2)
                {
                    cout << "PLEASE ENTER A VALID CHOICE: " << endl;
                    cin >> choice2;
                }
                if (choice2 == 1)
                {
                    cout << " ENTER THE KEY OF THE MACHINE IN WHCIH YOU WANT TO INSERT DATA: " << endl;
                    long double key = 0;
                    cin >> key;
                    bool val = ring.search(key);
                    while (!val)
                    {
                        cout << "SORRY, THE KEY YOU ENTERED DOESN'T EXIST ON THE FLY: ";
                        cout << " PLEASE ENTER AGAIN: " << endl;
                        cin >> key;
                        val = ring.search(key);
                    }
                    string text = "";
                    cout << " ENTER THE DATA YOU WANT TO INSERT: " << endl;
                    cin >> text;
                    insert_machines_data(key, text, ring, max_value);
                    
                    cout << "DATA INPUT WAS A SUCCESS" << endl;
                }
                else
                {
                    string text = "";
                    cout << " ENTER THE DATA YOU WANT TO INSERT: " << endl;
                    cin >> text;
                    string text1 = sha1(text);
                    long double key = hash_func(text1, bits, ring, max_value, false);
                    insert_machines_data(key, text, ring, max_value);
                    
                    cout << "DATA INPUT WAS A SUCCESS" << endl;


                }
                
            }
            
        }
        else if (choice == 3)
        {
            if (ring.head == nullptr)
                cout << "PLEASE ENTER A MACHINE" << endl;
            else
            {
                ring.print_btree();
                cout << " PLEASE ENTER THE MACHINE ID FROM WHICH YOU WOULD LIKE TO DELETE THE DATA " << endl; 
                long double id = 0;
                cin >> id;
                bool val = ring.search(id);
                while (!val)
                {
                    cout << "THE ENTERED KEY IS NOT PRESENT ON THE FLY " << endl;
                    cout << " PLEASE ENTER A VALID KEY: ";
                    cin >> id;
                    bool val = ring.search(id); 
                }
                cout << " PLEASE ENTER THE KEY OF THE DATA YOU WOULD LIKE TO DELETE" << endl;
                long double key = 0;
                cin >> key;

                Machine* temp = ring.searchMachine(key, ring.head, machine_number);
                bool val1=temp->btree.delete_btree(key);
                if (val1)
                {
                    cout << " THE KEY DELETED IS: " << key << endl;
                }
                


            }
        }
        else if (choice == 4)
        {
            if (ring.head==nullptr)
                cout << "PLEASE ENTER A MACHINE" << endl;
            else
            {
                ring.Print_Routing_Table();
            }
        }
        else if (choice == 5)
        {
            cout << " PLEASE ENTER THE ID OF THE MACHINE YOU WANT TO DELETE: ";
            long double id = 0;
            cin >> id;
            bool val = ring.search(id); 
            while (!val)
            {
                cout << "THE ENTERED KEY IS NOT PRESENT ON THE FLY " << endl;
                cout << " PLEASE ENTER A VALID KEY: ";
                cin >> id;
                bool val = ring.search(id); 
            }
            //Machine* temp = ring.search_to_return_machine(id);
            delete_machine_shift(id, ring, max_value, machine_number);
            machine_number--;
            if (ring.count == 1) 
            {
                tail_value = ring.head->ID; 
            }
            else
            {
                ring.tail_value(tail_value); 
            } 
           // ring.deleteData(id);


        }
        else if (choice == 6)
        {
            //ring.print_btree();

            ring.print();
            ring.Print_Routing_Table();
            cout << " ENTER THE MACHINE FROM WHICH SEARCHING SHOULD BEGIN: " << endl;
            long double id = 0;
            cin >> id;
            Machine* temp = ring.searchMachine(id, ring.head, machine_number);
            cout << temp->ID << endl;

            cout << "ENTER THE ELEMENT TO BE SEARCHED: " << endl;
            long double key = 0;
            cin >> key;
            //Machine* temp1 = ring.search_to_return_machine(1);
             temp= ring.searchMachine(key, temp, machine_number);

            bool val = temp->btree.search_key(key); 
            if (val)
            {
                string ans = "";
                temp->btree.search_for_value(key, ans);
                cout << "VALUE IS FOUND: "<<ans << endl;
            }
            else
            {
                cout << "THE GIVEN VALUE DOESN'T EXIST AT THE BTREE" << endl;
            }
            //cout << temp->ID << endl;
        }
        else if (choice==7)
            ring.print_btree();
        else if (choice==8)
            ring.print();
       /* else if (choice == 9)
        {
            visual(ring);
        }*/
        else if (choice==10)
            inputstop = true;
        cout << "----------------------" << endl;
        //cin >> inputstop;



    }
    //ring.print();
    
    
	//for (int i = 0; i < total_machines; i++)
	//{
	//	string a = "Machine";
	//	string b = to_string(i);
	//	a += b;
	//	a = sha1(a);
 //       //int x = a.length() - 1-i;
 //       //int random = rand() % 30;
 //       //x -= random;

 //       long double result = hash_func(a, bits, ring, max_value, true);
 //       ring.insert(result);
	//	
	//}
    
    /*ring.insert(&ring.head, 4);   
    
    ring.insert(&ring.head, 7);   
    
    ring.insert(&ring.head, 1); */  
    
    //ring.print();
    
    //ring.insertAtIndex(7, 6);
    //ring.counter();
    // to insert data of any machine to the available next neartest on machine


    //bool stop_input = false;
    //while (!stop_input)
    //{
    //    string text = "";
    //    cout << "Enter the text you want to store in your file: ";
    //    cin >> text;
    //    string text1 = sha1(text);
    //    //cout << text << endl;
    //    long double key = hash_func(text1, bits, ring, max_value, false);
    //    //cout << key << endl;
    //    
    //    insert_machines_data(key, text, ring, max_value);
    //    cout << endl;
    //    cout << "DO YOU WANT TO INPUT MORE TEXT?: ";
    //    int x = 0;
    //    cin >> x;
    //    if (x == 0)
    //        stop_input = true;
    //    
    //}

    //cout << max_value << endl;
    /*insert_machines_data(5, "hello1", ring, max_value);  
    insert_machines_data(5, "hello1", ring, max_value); 
    insert_machines_data(7, "hello3", ring, max_value); 
    insert_machines_data(13, "hello3", ring, max_value); 
    insert_machines_data(14, "hello3", ring, max_value);  
    insert_machines_data(2, "hello3", ring, max_value);  
    insert_machines_data(1, "hello3", ring, max_value);  

    ring.print_btree(); */

    // to delete an element of the btree from any specified machine 
   /* long double machine_delete = 0;
    long double key = 0;
    cin >> machine_delete;
    cin >> key;
    Machine* temp = ring.search_to_return_machine(machine_delete);
    temp->btree.delete_btree(key);

    ring.print_btree();*/


    //insert_machines_data(4, "hello", ring, max_value);
    //ring.print_btree(); 
    //ring.print();
    //Machine* temp = head;
    //bool ans=ring.search_key(4);
    //cout << ans << endl;

    
    //ring.print_btree(); 
    /*ring.print_btree();

    cout << "ENTER THE KEY OF THE MACHINE YOU WANT TO INSERT: "; 
    long double  manual_key = 0; 
    cin >> manual_key;  
    ring.insert(&ring.head, manual_key);  

    update_machine_data(manual_key, ring, max_value, 3);
    cout << "-----------" << endl;
    ring.print_btree(); */

    //ring.print_btree();
    //long double machine_id = 0;
    //cout << "ENTER THE MACHINE ID YOU WANT TO DELETE: ";
    //
    //cin >> machine_id;
    //delete_machine_shift(machine_id, ring, max_value);

    ////ring.deleteData(7);
    //ring.print_btree();


    //ring.print_btree();
    //bool stop = true;
    //while (stop)
    //{
    //    ring.Print_Routing_Table();
    //    cout << "ENTER THE ELEMENT TO BE SEARCHED: " << endl;
    //    long double key = 0;
    //    cin >> key;
    //    //Machine* temp1 = ring.search_to_return_machine(1);
    //    Machine* temp = ring.searchMachine(key, ring.head, 3);
    //    bool val = temp->btree.search_key(key);
    //    cout << val << endl;
    //}
    //cout << temp->ID << endl;



    

	

    return 0;




}


