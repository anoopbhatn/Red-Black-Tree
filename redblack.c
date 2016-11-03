#include<stdio.h>
#include<stdlib.h>

struct node
{
	int info,color;
	struct node *llink,*rlink,*p;
};
typedef struct node *NODE;

//   color : 0 for black 
//	     1 for red


NODE getNode();
NODE insert(NODE,int);
NODE insertfix(NODE,NODE);
NODE leftrotate(NODE,NODE);
NODE rightrotate(NODE,NODE);

NODE TNULL;
void init()
{
	TNULL=getNode();
	TNULL->info=0;
	TNULL->color=0;
	TNULL->llink=TNULL;
	TNULL->rlink=TNULL;
	TNULL->p=TNULL;
}

void preorderDotDump (NODE root, FILE* outputFile)
{
	if (root != TNULL) 
	{
		if(root->color == 0)
			fprintf (outputFile, "%d [label=%d,color=black];\n",root->info, root->info);
		else
			fprintf (outputFile, "%d [label=%d,color=red];\n",root->info, root->info);
		if (root->llink != TNULL) 
		         fprintf (outputFile, "%d -> %d ;\n", root->info, (root->llink)->info);
		
        	if (root->rlink != TNULL)
            		fprintf (outputFile, "%d -> %d;\n", root->info, root->rlink->info);
        	preorderDotDump (root->rlink, outputFile);
        	preorderDotDump (root->llink, outputFile);
    }
}
void dotDump(NODE root, FILE *outFile)
{
	fprintf (outFile, "digraph REDBLACKTREE {\n");
	preorderDotDump (root, outFile);
    	fprintf (outFile, "}\n");
}
FILE *outputFile;
void main()
{
	init();
	FILE *pipe;
	NODE root=TNULL;
	outputFile = fopen ("rb.dot", "w");
    	fclose (outputFile);
	int ch,val;
	
	for(;;)
	{
		printf("1.Insert\n2.Display\n");
			scanf("%d",&ch);
		switch(ch)
		{
			case 1: printf("Enter the value\n");
						scanf("%d",&val);
					root=insert(root,val);
					outputFile = fopen ("rb.dot", "a");
					if (outputFile != NULL) 
						dotDump (root,  outputFile);
					fclose (outputFile);
					break;
			case 2: pipe=popen("dot -Tps rb.dot -o rb.ps","w");
					pclose(pipe);	
					pipe=popen("evince rb.ps","r"); 
					pclose(pipe);
					break;
			default: exit(1);
		}
	}
}
NODE getNode()
{
	NODE NN;
	NN=(NODE)malloc(sizeof(struct node));
	if(NN==NULL)
		exit(1);
	NN->llink=NN->rlink=TNULL;
	NN->p=TNULL;
	return NN;
}
NODE insert(NODE root,int val)
{
	NODE NN=getNode(),x,y=TNULL;
	NN->info=val;
	x=root;
	while(x!=TNULL)
	{
		y=x;
		if(NN->info < x->info)
			x=x->llink;
		else
			x=x->rlink;
	}
	NN->p=y;
	if(y==TNULL)
		root=NN;
	else if(NN->info < y->info)
		y->llink=NN;
	else
		y->rlink=NN;
	NN->color=1;
	root=insertfix(root,NN);
	return root;
}
NODE insertfix(NODE root,NODE NN)
{
	NODE y=TNULL;
	while(NN!=TNULL && NN->p->color==1)
	{
		if(NN->p == NN->p->p->llink)
		{
			y=NN->p->p->rlink;
			if(y->color == 1)
			{
				NN->p->color=0;
				y->color=0;
				NN->p->p->color=1;
				NN=NN->p->p;
			}
			else if(NN == NN->p->rlink)
			{
				NN=NN->p;
				root=leftrotate(root,NN);
				NN->p->color=0;
				NN->p->p->color=1;
				root=rightrotate(root,NN->p->p);
			}
		}
		else
		{
			y=NN->p->p->llink;
			if(y->color == 1)
			{
				NN->p->color=0;
				y->color=0;
				NN->p->p->color=1;
				NN=NN->p->p;
			}
			else if(NN == NN->p->llink)
			{
				NN=NN->p;
				root=rightrotate(root,NN);
				NN->p->color=0;
				NN->p->p->color=1;
				root=leftrotate(root,NN->p->p);
			}
		}
	}
	root->color=0;
	return root;
}
NODE leftrotate(NODE root,NODE NN)
{
	NODE y;
	y=NN->rlink;
	NN->rlink=y->llink;
	if(y->llink != TNULL)
		y->llink->p=NN;
	y->p=NN->p;
	if(NN->p==TNULL)
		root=y;
	else if(NN == NN->p->llink)
		NN->p->llink=y;
	else
		NN->p->rlink=y;
	y->llink=NN;
	NN->p=y;
	return root;
}
NODE rightrotate(NODE root,NODE NN)
{
	NODE y;
	y=NN->llink;
	NN->llink=y->rlink;
	if(y->rlink != TNULL)
		y->rlink->p=NN;
	y->p=NN->p;
	if(NN->p==TNULL)
		root=y;
	else if(NN == NN->p->rlink)
		NN->p->rlink=y;
	else
		NN->p->llink=y;
	y->rlink=NN;
	NN->p=y;
	return root;
}
