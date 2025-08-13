%{

        #include<bits/stdc++.h>

        using namespace std;

        void yyerror(char *s);

        int yylex();

        typedef struct node

        {

                struct node *left,*right;

                string val;

                int label;

        }NODE;

        NODE* makeNode(string val, NODE* left , NODE* right)

        {

                NODE *temp=new NODE();

                temp->val=val;

                temp->left=left;

                temp->right=right;

                temp->label=0;

                return temp;

        }

        NODE* synTree;

%}

%token PL MI MUL DIV OP CL EQ ID VAL SC UNR POW

%union{

        typedef struct node NODE;

        char *str;

        NODE *node;

}

%type <node> s e t f g

%type <str> PL MI MUL DIV OP CL EQ ID VAL SC UNR POW

%%

s : e {$$=$1;synTree=$$;}

e : e PL t {$$=makeNode($2,$1,$3);} |

         e MI t {$$=makeNode($2,$1,$3);} |

          t {$$=$1;};

t : t MUL f {$$=makeNode($2,$1,$3);}|

         t DIV f {$$=makeNode($2,$1,$3);}|

          f {$$=$1;};

f : g POW f {$$=makeNode($2,$1,$3);} |

         g {$$=$1;};

g : OP e CL {$$=$2;} |

         ID{$$=makeNode($1,NULL,NULL);} |

          VAL{$$=makeNode($1,NULL,NULL);} /*|

           MI g{$$=makeNode($1,NULL,$2);} */;

%%

void inOrder(NODE* root)

{

        if(root)

        {

                inOrder(root->left);

                cout<<root->val<<" ";

                inOrder(root->right);

        }

}

void postOrder(NODE* root)

{

        if(root)

        {

                postOrder(root->left);

                postOrder(root->right);

                cout<<root->val<<" ";

        }

}



void preOrder(NODE* root)

{

        if(root)

        {

                cout<<root->val<<" ";

                preOrder(root->left);

                preOrder(root->right);

        }

}

void yyerror(char *s)

{

printf("%s\n",s);

}

int main(void)

{

        yyparse();

        cout<<"In Order:"<<endl;

        inOrder(synTree);

        cout<<endl<<"Pre Order:"<<endl;

        preOrder(synTree);

        cout<<endl<<"Post Order:"<<endl;

        postOrder(synTree);

        cout<<endl;

}