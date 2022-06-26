#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
typedef struct Treenode* Btree; 
typedef struct WordNode* word;

/* 
   Stemming word：
   This is the Porter stemming algorithm, coded up in ANSI C by the
   author. It may be be regarded as canonical, in that it follows the
   algorithm presented in

   Porter, 1980, An algorithm for suffix stripping, Program, Vol. 14,
   no. 3, pp 130-137,

   only differing from it at the points marked --DEPARTURE-- below.

   See also http://www.tartarus.org/~martin/PorterStemmer

   The algorithm as described in the paper could be exactly replicated
   by adjusting the points of DEPARTURE, but this is barely necessary,
   because (a) the points of DEPARTURE are definitely improvements, and
   (b) no encoding of the Porter stemmer I have seen is anything like
   as exact as this version, even with the points of DEPARTURE!

   You can compile it on Unix with 'gcc -O3 -o stem stem.c' after which
   'stem' takes a list of inputs and sends the stemmed equivalent to
   stdout.

   The algorithm as encoded here is particularly fast.

   Release 1: was many years ago
   Release 2: 11 Apr 2013
       fixes a bug noted by Matt Patenaude <matt@mattpatenaude.com>,

       case 'o': if (ends("\03" "ion") && (b[j] == 's' || b[j] == 't')) break;
           ==>
       case 'o': if (ends("\03" "ion") && j >= k0 && (b[j] == 's' || b[j] == 't')) break;

       to avoid accessing b[k0-1] when the word in b is "ion".
   Release 3: 25 Mar 2014
       fixes a similar bug noted by Klemens Baum <klemensbaum@gmail.com>,
       that if step1ab leaves a one letter result (ied -> i, aing -> a etc),
       step2 and step4 access the byte before the first letter. So we skip
       steps after step1ab unless k > k0.
*/

#include <string.h>  /* for memmove */

#define TRUE 1
#define FALSE 0
#define max_doc 100
#define max_que 10
#define threshold 10
/* The main part of the stemming algorithm starts here. b is a buffer
   holding a word to be stemmed. The letters are in b[k0], b[k0+1] ...
   ending at b[k]. In fact k0 = 0 in this demo program. k is readjusted
   downwards as the stemming progresses. Zero termination is not in fact
   used in the algorithm.

   Note that only lower case sequences are stemmed. Forcing to lower case
   should be done before stem(...) is called.
*/

static char * b;       /* buffer for word to be stemmed */
static int k,k0,j;     /* j is a general offset into the string */

/* cons(i) is TRUE <=> b[i] is a consonant. */

static int cons(int i)
{  switch (b[i])
   {  case 'a': case 'e': case 'i': case 'o': case 'u': return FALSE;
      case 'y': return (i==k0) ? TRUE : !cons(i-1);
      default: return TRUE;
   }
}

/* m() measures the number of consonant sequences between k0 and j. if c is
   a consonant sequence and v a vowel sequence, and <..> indicates arbitrary
   presence,

      <c><v>       gives 0
      <c>vc<v>     gives 1
      <c>vcvc<v>   gives 2
      <c>vcvcvc<v> gives 3
      ....
*/

static int m()
{  int n = 0;
   int i = k0;
   while(TRUE)
   {  if (i > j) return n;
      if (! cons(i)) break; i++;
   }
   i++;
   while(TRUE)
   {  while(TRUE)
      {  if (i > j) return n;
            if (cons(i)) break;
            i++;
      }
      i++;
      n++;
      while(TRUE)
      {  if (i > j) return n;
         if (! cons(i)) break;
         i++;
      }
      i++;
   }
}

/* vowelinstem() is TRUE <=> k0,...j contains a vowel */

static int vowelinstem()
{  int i; for (i = k0; i <= j; i++) if (! cons(i)) return TRUE;
   return FALSE;
}

/* doublec(j) is TRUE <=> j,(j-1) contain a double consonant. */

static int doublec(int j)
{  if (j < k0+1) return FALSE;
   if (b[j] != b[j-1]) return FALSE;
   return cons(j);
}

/* cvc(i) is TRUE <=> i-2,i-1,i has the form consonant - vowel - consonant
   and also if the second c is not w,x or y. this is used when trying to
   restore an e at the end of a short word. e.g.

      cav(e), lov(e), hop(e), crim(e), but
      snow, box, tray.

*/

static int cvc(int i)
{  if (i < k0+2 || !cons(i) || cons(i-1) || !cons(i-2)) return FALSE;
   {  int ch = b[i];
      if (ch == 'w' || ch == 'x' || ch == 'y') return FALSE;
   }
   return TRUE;
}

/* ends(s) is TRUE <=> k0,...k ends with the string s. */

static int ends(char * s)
{  int length = s[0];
   if (s[length] != b[k]) return FALSE; /* tiny speed-up */
   if (length > k-k0+1) return FALSE;
   if (memcmp(b+k-length+1,s+1,length) != 0) return FALSE;
   j = k-length;
   return TRUE;
}

/* setto(s) sets (j+1),...k to the characters in the string s, readjusting
   k. */

static void setto(char * s)
{  int length = s[0];
   memmove(b+j+1,s+1,length);
   k = j+length;
}

/* r(s) is used further down. */

static void r(char * s) { if (m() > 0) setto(s); }

/* step1ab() gets rid of plurals and -ed or -ing. e.g.

       caresses  ->  caress
       ponies    ->  poni
       ties      ->  ti
       caress    ->  caress
       cats      ->  cat

       feed      ->  feed
       agreed    ->  agree
       disabled  ->  disable

       matting   ->  mat
       mating    ->  mate
       meeting   ->  meet
       milling   ->  mill
       messing   ->  mess

       meetings  ->  meet

*/

static void step1ab()
{  if (b[k] == 's')
   {  if (ends("\04" "sses")) k -= 2; else
      if (ends("\03" "ies")) setto("\01" "i"); else
      if (b[k-1] != 's') k--;
   }
   if (ends("\03" "eed")) { if (m() > 0) k--; } else
   if ((ends("\02" "ed") || ends("\03" "ing")) && vowelinstem())
   {  k = j;
      if (ends("\02" "at")) setto("\03" "ate"); else
      if (ends("\02" "bl")) setto("\03" "ble"); else
      if (ends("\02" "iz")) setto("\03" "ize"); else
      if (doublec(k))
      {  k--;
         {  int ch = b[k];
            if (ch == 'l' || ch == 's' || ch == 'z') k++;
         }
      }
      else if (m() == 1 && cvc(k)) setto("\01" "e");
   }
}

/* step1c() turns terminal y to i when there is another vowel in the stem. */

static void step1c() { if (ends("\01" "y") && vowelinstem()) b[k] = 'i'; }


/* step2() maps double suffices to single ones. so -ization ( = -ize plus
   -ation) maps to -ize etc. note that the string before the suffix must give
   m() > 0. */

static void step2() { switch (b[k-1])
{
    case 'a': if (ends("\07" "ational")) { r("\03" "ate"); break; }
              if (ends("\06" "tional")) { r("\04" "tion"); break; }
              break;
    case 'c': if (ends("\04" "enci")) { r("\04" "ence"); break; }
              if (ends("\04" "anci")) { r("\04" "ance"); break; }
              break;
    case 'e': if (ends("\04" "izer")) { r("\03" "ize"); break; }
              break;
    case 'l': if (ends("\03" "bli")) { r("\03" "ble"); break; } /*-DEPARTURE-*/

 /* To match the published algorithm, replace this line with
    case 'l': if (ends("\04" "abli")) { r("\04" "able"); break; } */

              if (ends("\04" "alli")) { r("\02" "al"); break; }
              if (ends("\05" "entli")) { r("\03" "ent"); break; }
              if (ends("\03" "eli")) { r("\01" "e"); break; }
              if (ends("\05" "ousli")) { r("\03" "ous"); break; }
              break;
    case 'o': if (ends("\07" "ization")) { r("\03" "ize"); break; }
              if (ends("\05" "ation")) { r("\03" "ate"); break; }
              if (ends("\04" "ator")) { r("\03" "ate"); break; }
              break;
    case 's': if (ends("\05" "alism")) { r("\02" "al"); break; }
              if (ends("\07" "iveness")) { r("\03" "ive"); break; }
              if (ends("\07" "fulness")) { r("\03" "ful"); break; }
              if (ends("\07" "ousness")) { r("\03" "ous"); break; }
              break;
    case 't': if (ends("\05" "aliti")) { r("\02" "al"); break; }
              if (ends("\05" "iviti")) { r("\03" "ive"); break; }
              if (ends("\06" "biliti")) { r("\03" "ble"); break; }
              break;
    case 'g': if (ends("\04" "logi")) { r("\03" "log"); break; } /*-DEPARTURE-*/

 /* To match the published algorithm, delete this line */
} }

/* step3() deals with -ic-, -full, -ness etc. similar strategy to step2. */

static void step3() { switch (b[k])
{
    case 'e': if (ends("\05" "icate")) { r("\02" "ic"); break; }
              if (ends("\05" "ative")) { r("\00" ""); break; }
              if (ends("\05" "alize")) { r("\02" "al"); break; }
              break;
    case 'i': if (ends("\05" "iciti")) { r("\02" "ic"); break; }
              break;
    case 'l': if (ends("\04" "ical")) { r("\02" "ic"); break; }
              if (ends("\03" "ful")) { r("\00" ""); break; }
              break;
    case 's': if (ends("\04" "ness")) { r("\00" ""); break; }
              break;
} }

/* step4() takes off -ant, -ence etc., in context <c>vcvc<v>. */

static void step4()
{  switch (b[k-1])
    {  case 'a': if (ends("\02" "al")) break; return;
       case 'c': if (ends("\04" "ance")) break;
                 if (ends("\04" "ence")) break; return;
       case 'e': if (ends("\02" "er")) break; return;
       case 'i': if (ends("\02" "ic")) break; return;
       case 'l': if (ends("\04" "able")) break;
                 if (ends("\04" "ible")) break; return;
       case 'n': if (ends("\03" "ant")) break;
                 if (ends("\05" "ement")) break;
                 if (ends("\04" "ment")) break;
                 if (ends("\03" "ent")) break; return;
       case 'o': if (ends("\03" "ion") && j >= k0 && (b[j] == 's' || b[j] == 't')) break;
                 if (ends("\02" "ou")) break; return;
                 /* takes care of -ous */
       case 's': if (ends("\03" "ism")) break; return;
       case 't': if (ends("\03" "ate")) break;
                 if (ends("\03" "iti")) break; return;
       case 'u': if (ends("\03" "ous")) break; return;
       case 'v': if (ends("\03" "ive")) break; return;
       case 'z': if (ends("\03" "ize")) break; return;
       default: return;
    }
    if (m() > 1) k = j;
}

/* step5() removes a final -e if m() > 1, and changes -ll to -l if
   m() > 1. */

static void step5()
{  j = k;
   if (b[k] == 'e')
   {  int a = m();
      if (a > 1 || a == 1 && !cvc(k-1)) k--;
   }
   if (b[k] == 'l' && doublec(k) && m() > 1) k--;
}

/* In stem(p,i,j), p is a char pointer, and the string to be stemmed is from
   p[i] to p[j] inclusive. Typically i is zero and j is the offset to the last
   character of a string, (p[j+1] == '\0'). The stemmer adjusts the
   characters p[i] ... p[j] and returns the new end-point of the string, k.
   Stemming never increases word length, so i <= k <= j. To turn the stemmer
   into a module, declare 'stem' as extern, and delete the remainder of this
   file.
*/

int stem(char * p, int i, int j)
{  b = p; k = j; k0 = i; /* copy the parameters into statics */
   if (k <= k0+1) return k; /*-DEPARTURE-*/

   /* With this line, strings of length 1 or 2 don't go through the
      stemming process, although no mention is made of this in the
      published algorithm. Remove the line to match the published
      algorithm. */

   step1ab();
   if (k > k0) {
       step1c(); step2(); step3(); step4(); step5();
   }
   return k;
}

struct WordNode //a structure of a word node
{
    Btree children;
    int frequency;
    string key_word;
};

    /////////////////////////
    //Treenode:the node of B+tree
    //key[i]:
    //store the key,in which is the subnode of this key, 
    //the contain of string,
    //and its frequency if it's a leaf node 
    //
    //key_num:the num of key
    //
    //parent: this node's parent
    //
    //next:if it's a leaf node,it points to the next leaf node
    //
    //is_leaf/root: if this node is a leaf or root
    /////////////////////////

struct Treenode
{
    word key[4];
    int key_num;
    int level;//used for BFS print
    Btree parent;
    Btree next;
    bool is_leaf;
    bool is_root;
};

Btree Word_Dictionary;
Btree Stop_Word;
long long total_word_num;
//two compare function used in searching to pick out the more relevent one 
bool cmp_1(word a,word b)
{
    return a->frequency<b->frequency;
}
bool cmp_2(word a,word b)
{
    return a->frequency>b->frequency;
}
////////////////////////////////////////////////
//Index(Btree T,string val,Btree new_child):
//to insert a key with string val and its children into a B+ tree node
//and the key in the same node is ordered
////////////////////////////////////////////////
void Index(Btree T,string val,Btree new_child)
{
    T->key_num++;
    word index=new(struct WordNode);
    //cout<<"!"<<index<<" "<<
    index->key_word=val;
    if(!new_child)index->frequency=1;
    //cout<<"!";
    index->children=new_child;//initialize the inserted key
    for(int i=0;i<T->key_num;i++)
    {
       if(i==T->key_num-1||index->key_word<T->key[i]->key_word)
        {
            word temp=index;
            index=T->key[i];
            T->key[i]=temp;
        }
        //find the correct location in this node to insert
        //and make it order
     }
    return;
}

//find_leaf(Btree root, string val):to find the correct leaf to insert  word val in B+tree root
Btree find_leaf(Btree root, string val)
{
    Btree T=root;
    while(!T->is_leaf)//reach the leaf
    {
        if(val<T->key[0]->key_word)T->key[0]->key_word=val;
        //Update the most left index along the path each time we insert
        for(int i=1;i<=3;i++)
        if(i==T->key_num||val<T->key[i]->key_word)
        {
           T=T->key[i-1]->children;
           break;
        }
    }
    return T;
}
//////////////////////////////////////////////
//find_word(Btree T, string val):
//to find the correct location of word val in a leafnode T
//It means, one node contain at most four key/word 
//////////////////////////////////////////////
word find_word(Btree T, string val)
{
    for(int i=0;i<T->key_num;i++)
    {
        if(T->key[i]->key_word==val)
        {
            return T->key[i];
        }
    }
    return NULL;
}
//////////////////////////////////////////////
//insert(Btree root, string val, Btree leaf_contain):
//insert a new element val into the B+tree root 
//the leaf_contain means the leaf_node's children 
//(For example, the leaf_contain of the dictionary is a B+tree containing the document names)
//this function includes find,insert and split from down to top
//////////////////////////////////////////////
Btree insert(Btree root, string val, Btree leaf_contain)
{
    Btree T=find_leaf(root,val);
    word repe=find_word(T,val);
    
    if(repe)//if the word had in the tree, add up its frequency and return 
    {
        repe->frequency++;
        return root;
    }
    Index(T,val,leaf_contain);//insert the val into the leaf node
    while(T->key_num>3)//the Index if full
        {
            Btree new_sibling=new(struct Treenode);
            for(int i=0;i<4;i++)new_sibling->key[i]=new(struct WordNode);//initialize
            if(T->is_leaf){
                new_sibling->is_leaf=1;
                new_sibling->next=T->next;
                T->next=new_sibling;
            }
            else new_sibling->is_leaf=0;
            new_sibling->key[0]=T->key[2];//split
            new_sibling->key[1]=T->key[3];
            new_sibling->level=T->level;
            new_sibling->is_root=0;
            if(!T->is_leaf){
                T->key[2]->children->parent=new_sibling;
                T->key[3]->children->parent=new_sibling;
            }
            T->key_num-=2;
            new_sibling->key_num=2;
            ///////////////////////////
            //initialize the new_sibiling
            //and split the origin node
            ///////////////////////////
            if(T->is_root)
            {
                Btree new_root=new(struct Treenode);
                T->is_root=0;
                new_root->key_num=0;
                new_root->next=T->is_leaf?T:T->next;
                new_root->is_root=1;
                new_root->parent=T->parent;
                T->parent=new_root;
                Index(new_root,T->key[0]->key_word,T);
                new_root->key[0]->children=T;
                new_root->level=T->level+1;
                new_root->is_leaf=0;
                root=new_root;
            }
            ///////////////////////////
            //if the root index is full
            //build the new root and initialize it
            //Remember to update the root(the parameter)
            //////////////////////////
            new_sibling->parent=T->parent;
            T=T->parent;//from down to top
            Index(T,new_sibling->key[0]->key_word,new_sibling);//add the index_key to its parent
    }
    return root;
}

//initial():return an empty B+tree root
Btree initial()
{
    //Btree root=(Btree)malloc(sizeof(struct Treenode));
    Btree leaf=new(struct Treenode);
    leaf->is_root=1;
    leaf->parent=leaf;
    //root->level=1;
    for(int i=0;i<4;i++){
        leaf->key[i]=(word)new(struct WordNode);
    }
    leaf->level=0;
    leaf->is_leaf=1;
    leaf->key_num=0;
    leaf->next=NULL;
    return leaf;
}

//BFS():print out the B+tree including the index and leaves 
void BFS(Btree root)
{
    Btree queue[10005];
    int head=0,tail=0;
    queue[tail++]=root;
    //use queue to print it in height order
    int print_level=root->level;
    while(head<tail)
    {
        Btree now_node=queue[head++];
        if(now_node->level<print_level)
        {
            print_level--;
            printf("\n");
        }
        printf("[");
        for(int i=0;i<now_node->key_num;i++)
        {
            if(now_node->is_leaf&&i||i>1)printf(",");//In index node, the first key is not shown 
            if(now_node->is_leaf||i)cout<<now_node->key[i]->key_word;
            if(!now_node->is_leaf)queue[tail++]=now_node->key[i]->children;
        }
        //if(!now_node->is_leaf)queue[tail++]=now_node->children[now_node->key_num];
        printf("]");
    }
    printf("\n");
    return;
}
///////////////////////////
//Stop_Word_Insert():
//Normal read_in program:get each word in the text until read '#'
//use stem function to get its stem
//and insert each stem_word into stop_word list
///////////////////////////
void Stop_Word_Insert()
{
    ifstream fin;
    fin.open("Stop Word.txt");
    char ch;
    fin.get(ch);
    while(ch!='#')
    {
        char str[500];
        int i=0;
        while(ch!='#'&&!(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'))fin.get(ch);
        while(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
        {
            if(ch>='A'&&ch<='Z')ch=ch-'A'+'a';
            str[i++]=ch;
            fin.get(ch);
        }
        if(!i)continue;
        int end=stem(str,0,i-1);
        str[end+1]='\0';
        string wrd=str;
        Stop_Word=insert(Stop_Word,wrd,NULL);
    }
    return;
}
///////////////////////////
//Document_Insert():
//Normal read_in program:get each word in the text until read '#'
//use stem function to get its stem
//if it's not a stop word and it's still not in dictionary, insert it into dictionary
//else add the document_name into this word's document list
///////////////////////////
void Document_Insert()
{
    ifstream fin;
    fin.open("The Complete Works of William Shakespeare.txt");
    int n=0;
    fin>>n;
    for(int i=0;i<n;i++){
        string  Document_Name;
        fin>>Document_Name;
        char ch;
        fin.get(ch);
        while(ch!='#')
        {
            char str[500];
            int i=0;
            while(ch!='#'&&!(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'))fin.get(ch);
            while(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
            {
                if(ch>='A'&&ch<='Z')ch=ch-'A'+'a';
                str[i++]=ch;
                fin.get(ch);
            }
            if(!i)continue;
            total_word_num++;
            int end=stem(str,0,i-1);
            str[end+1]='\0';
            string wrd=str;
            // cout<<wrd<<endl;
            word is_stop=find_word(find_leaf(Stop_Word,wrd),wrd);
            if(is_stop)continue;//if it's stop word
            word str_find=find_word(find_leaf(Word_Dictionary,wrd),wrd);
            if(str_find)//if it has in the dictionary, add the doucment name into the document list
            str_find->children=insert(str_find->children, Document_Name, NULL);
            else{
                /////////////////////////////////////////////
                //if it's not in the dictionary
                //initialize a document list
                //and add the document_name into this word's document list
                //and insert the word into dictionary
                /////////////////////////////////////////////
                Btree Doc_list=new(struct Treenode);
                Doc_list=initial();
                Doc_list=insert(Doc_list, Document_Name, NULL);
                Word_Dictionary=insert(Word_Dictionary,wrd,Doc_list);
            }
        }
    }
    //Dictionary_root=insert(Dictionary_root, wrd, NULL);
    // BFS(Word_Dictionary);
    fin.close();
    return;
}
//print(root):print out the dictionary with its document list
void print(Btree root)
{
    Btree T=root;
    if(!T->is_leaf)T=T->next;
    while(T)
    {
        for(int i=0;i<T->key_num;i++)
        {
            if(T->key[i]->children)
            {
                cout<<T->key[i]->key_word<<":";
                print(T->key[i]->children);
                cout<<endl;
            }
            else cout<<T->key[i]->key_word<<" ";
        }
        T=T->next;
    }
    return;
}
/////////////////////////////////
//search():
//Normal read_in program:get each word in the text until read '#'
//(there is constant max_query to limit the read_in word's number)
//use stem function to get its stem
//sort it in order(frequncey low->high)
//find the word one by one in dictionary and add its document_list into anwser array in order(frequncey high->low)
//until it finish finding or the array is over threshold(also a constant defined on the top)
/////////////////////////////////
void search()
{
    word query_sort_arr[max_que];//the array to store the query
    int query_num=0;
    char ch=getchar();
    while(ch!='#')
    {
        char str[50];
        int i=0;
        while(ch!='#'&&!(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z'))ch=getchar();
        while(ch>='A'&&ch<='Z'||ch>='a'&&ch<='z')
        {
            if(ch>='A'&&ch<='Z')ch=ch-'A'+'a';
            str[i++]=ch;
            ch=getchar();
        }
        if(!i)continue;
        int end=stem(str,0,i-1);
        str[end+1]='\0';
        string wrd=str;
        //cout<<wrd<<endl;
        word is_stop=find_word(find_leaf(Stop_Word,wrd),wrd);
        if(is_stop)continue;
        word str_find=find_word(find_leaf(Word_Dictionary,wrd),wrd);
        if(!str_find)continue;
        query_sort_arr[query_num++]=str_find;
        //if it's not a stop word and can be found in dictionary 
        //add it into query array
    }
    if(!query_num){cout<<"Not Found!"<<endl;return;}//if there is no result
    sort(query_sort_arr,query_sort_arr+query_num,cmp_1);//quick sort
    int now_query=0;
    int now_item=0;
    word doc_sort_arr[max_doc];//the finally answer array store the document name
    while(now_query<query_num&&now_item<threshold)
    {
        int tmp=now_item;
        Btree T=query_sort_arr[now_query++]->children;//iterate the document_list of query's word in order
        if(!T->is_leaf)T=T->next;
        while(T)
        {
            for(int i=0;i<T->key_num;i++){
            int flag=0;
            for(int j=0;j<now_item;j++)if(doc_sort_arr[j]->key_word==T->key[i]->key_word){flag=1;break;}
            //pass the competive document
            if(!flag){doc_sort_arr[now_item++]=T->key[i];}//add the document name into answer array
            if(now_item>threshold)break;}
            if(now_item>threshold)break;
            T=T->next;
        }
        sort(doc_sort_arr+tmp,doc_sort_arr+now_item,cmp_2);//quick sort
    }
    cout<<"Searching result: the document name that contain the search query (threshold="<<threshold<<")"<<endl;
    for(int i=0;i<threshold&&i<now_item;i++)cout<<doc_sort_arr[i]->key_word<<endl;
    cout<<"___________________________________________________"<<endl;
    //print out the answer array
    return;
}
void print_word_num()
{
    cout<<"The total words in Shakespeare works is "<<total_word_num<<endl;
    cout<<"___________________________________________________"<<endl;
}
int main()
{
    Stop_Word=initial();
    Stop_Word_Insert();
    Word_Dictionary=initial();
    Document_Insert();
    // print(Word_Dictionary);
    int m=0;
    cin>>m;
    for(int i=0;i<m;i++){
        char ch;
        cin>>ch;
        if(ch=='s')search();//searching program
        else if(ch=='c')print(Word_Dictionary);//print out the index and document list
        else if(ch=='n')print_word_num();}//counting the total num of words in Shakespeare works.
    return 0;
}
