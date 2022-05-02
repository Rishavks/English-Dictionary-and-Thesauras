#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct dictNode
{
    char word[50], meaning[50], synonym[50], antonym[50], sentence[100];
    struct dictNode *left, *right;

} DictNode;

DictNode *root = NULL;

DictNode* NewNode()
{
    DictNode* newNodePtr=NULL;

    char Word[50], Meaning[50], Synonym[50], Antonym[50], Sentence[100];
    printf("Enter Word : ");
    scanf("%s",Word);
    printf("Enter Meaning : ");
    scanf("%s",Meaning);
    printf("Enter Synonym : ");
    scanf("%s",Synonym);
    printf("Enter Antonym : ");
    scanf("%s",Antonym);
    printf("Enter Sentence : ");
    scanf("%s",Sentence);

    newNodePtr = (DictNode*) malloc(sizeof(DictNode));
    newNodePtr->left=NULL;
    newNodePtr->right=NULL;

    strcpy(newNodePtr->word,Word);
    strcpy(newNodePtr->meaning,Meaning);
    strcpy(newNodePtr->synonym,Synonym);
    strcpy(newNodePtr->antonym,Antonym);
    strcpy(newNodePtr->sentence,Sentence);

    printf("%s\n",newNodePtr->word);

    return newNodePtr;
}

int strCompare(char str1[], char str2[])
{
    int i=0;

    while(str1[i]!='\0' && str2[i]!='\0')
    {
        if(str1[i]<str2[i])
            return -1;
        else if(str1[i]>str2[i])
                return 1;
        i++;
    }
    return 0;
}
void addWordSingle()
{
    DictNode* temp=NULL;
    DictNode* prev=NULL;
    DictNode* ptrNode=NULL;

    ptrNode= NewNode();
    if(root==NULL)
    {
        root = ptrNode;
    }
    else
    {
        temp = root;
        while(temp!=NULL)
        {
            prev=temp;
            if(strcmp(ptrNode->word,temp->word)>0)
                {
                    temp = temp->right;
                }
            else if(strcmp(ptrNode->word,temp->word)<0)
                        {
                            temp = temp->left;
                        }
            else
            {
                printf("Word already exists...");
                return;
            }
        }
        if(strcmp(ptrNode->word,prev->word)<0)
            prev->left=ptrNode;
        else
            prev->right=ptrNode;
    }
}

void addWordMulti()
{
    char Word[50], Meaning[50], Synonym[50], Antonym[50], Sentence[100];
    int count = 1;
    char filePath[100];
    FILE* fp;
    printf("Enter File Name : ");
    scanf("%s",filePath);
    fp = fopen(filePath,"r");
    if(fp==NULL)
    {
        printf("ERROR");
        return;
    }
    while(1)
    {
        if(count == 1)
        {
            if(fgets(Word,50,fp) == NULL)
                break;
        }
        else if(count == 2)
        {
            if(fgets(Meaning,50,fp) == NULL)
                {
                    printf("File format wrong...");
                    return;
                }
        }
        else if(count == 3)
        {
            if(fgets(Synonym,50,fp) == NULL)
                {
                    printf("File format wrong...");
                    return;
                }
        }
        else if(count == 4)
        {
            if(fgets(Antonym,50,fp) == NULL)
                {
                    printf("File format wrong...");
                    return;
                }
        }
        else if(count == 5)
        {
            if(fgets(Sentence,100,fp) == NULL)
                {
                    printf("File format wrong...");
                    return;
                }

            DictNode* newNodePtr=NULL;
            newNodePtr = (DictNode*) malloc(sizeof(DictNode));
            newNodePtr->left=NULL;
            newNodePtr->right=NULL;

            strcpy(newNodePtr->word,Word);
            strcpy(newNodePtr->meaning,Meaning);
            strcpy(newNodePtr->synonym,Synonym);
            strcpy(newNodePtr->antonym,Antonym);
            strcpy(newNodePtr->sentence,Sentence);

            DictNode* temp=NULL;
            DictNode* prev=NULL;
            if(root==NULL)
                {
                    root = newNodePtr;
                }
            else
                {
                    temp = root;
                    while(temp!=NULL)
                    {
                        prev=temp;
                        if(strcmp(newNodePtr->word,temp->word)>0)
                        {
                            temp = temp->right;
                        }
                    else if(strcmp(newNodePtr->word,temp->word)<0)
                            {
                                temp = temp->left;
                            }
                    else
                        {
                            printf("Word already exists...");
                            return;
                        }
                }
                if(strcmp(newNodePtr->word,prev->word)<0)
                    prev->left=newNodePtr;
                else
                    prev->right=newNodePtr;

                printf("Word entered in dictionary : %s\n",Word);
            }

        }
        count++;
        if( count > 5 )
        {
            count = 1;
        }
    }
    fclose(fp);
}

void findWordSingle()
{
    int x = 0;
    char Word[50];
    printf("Enter Word to be searched : ");
    scanf("%s",Word);
    DictNode* temp=NULL;
    DictNode* prev=NULL;
    if(root == NULL)
    {
        printf("Empty Dictionary...");
        return;
    }
    else
    {
        temp = root;
        while(temp!=NULL)
        {
            if(strCompare(Word,temp->word) > 0)
            {
                printf("%s\n",temp->word);
                temp = temp->right;
            }
            else if(strCompare(Word,temp->word) < 0)
                {
                    printf("%s\n",temp->word);
                    temp = temp->left;
                }
            else if(strCompare(Word,temp->word) == 0)
                {
                    printf("%s\n",temp->word);
                    x=1;
                    printf("Word found...printing info...\n");
                    printf("%s\n",temp->word);
                    printf("%s\n",temp->meaning);
                    printf("%s\n",temp->synonym);
                    printf("%s\n",temp->antonym);
                    printf("%s\n",temp->sentence);
                    break;
                }
        }

        if(x == 0)
            printf("Word not found...");
    }
}

void findWordMulti()
{
    int x = 0;
    char Word[50];
    char filePath[100];
    FILE* fp;
    FILE* fp1;
    printf("Enter File Name (File should contain a word at each line): ");
    scanf("%s",filePath);
    fp = fopen(filePath,"r");
    fp1 = fopen("WordsFound.txt","w");
    if(fp==NULL || fp1==NULL)
    {
        printf("ERROR");
        return;
    }
    while(fgets(Word,50,fp) != NULL)
    {
        DictNode* temp=NULL;
        DictNode* prev=NULL;
        if(root == NULL)
        {
            printf("Empty Dictionary...");
            return;
        }
        else
        {
            temp = root;
            while(temp!=NULL)
            {
                if(strCompare(Word,temp->word) > 0)
                {
                    temp = temp->right;
                }
                else if(strCompare(Word,temp->word) < 0)
                    {
                        temp = temp->left;
                    }
                else if(strCompare(Word,temp->word) == 0)
                    {
                        printf("%s\n",temp->word);
                        x=1;
                        printf("Word found...details have been saved\n");
                        fprintf(fp1,"%s",temp->word);
                        fprintf(fp1,"%s",temp->meaning);
                        fprintf(fp1,"%s",temp->synonym);
                        fprintf(fp1,"%s",temp->antonym);
                        fprintf(fp1,"%s\n",temp->sentence);
                        break;
                    }
            }

            if(x == 0)
                printf("Word not found...");
        }
    }

}

void modifyDict()
{
    char tempMeaning[50], tempSynonym[50], tempAntonym[50], tempSentence[100];
    int ch;
    printf("          Submenu 3");
    printf("\n1. Word Modification");
    printf("\n2. Related Data Modification");
    printf("\nEnter your choice : ");
    scanf("%d",&ch);
    if(ch == 1)
    {
        int x = 0;
        char Word[50], Meaning[50], Synonym[50], Antonym[50], Sentence[100];
        printf("Enter Word to be Modified : ");
        scanf("%s",Word);
        DictNode* temp=NULL;
        DictNode* prev=NULL;
        if(root == NULL)
        {
            printf("Empty Dictionary...");
            return;
        }
        else
        {
            temp = root;
            while(temp!=NULL)
            {
                if(strCompare(Word,temp->word) > 0)
                {
                    prev = temp;
                    temp = temp->right;
                }
                else if(strCompare(Word,temp->word) < 0)
                    {
                        prev = temp;
                        temp = temp->left;
                    }
                else if(strCompare(Word,temp->word) == 0)
                    {
                        x=1;
                        strcpy(Meaning,temp->meaning);
                        strcpy(Synonym,temp->synonym);
                        strcpy(Antonym,temp->antonym);
                        strcpy(Sentence,temp->sentence);
                        printf("Word found...Enter New Details\n");
                        if(temp->left == NULL && temp->right == NULL)
                        {
                            if(temp != root)
                                free(temp);
                            else
                                root = NULL;

                            if(prev->left == temp)
                                prev->left = NULL;
                            else
                                prev->right = NULL;
                        }
                        else if(temp->left != NULL && temp->right != NULL)
                        {
                            DictNode* replace = temp->right;
                            DictNode* parent = NULL;
                            int flag = 0;
                            while(replace->left != NULL)
                            {
                                flag = 1;
                                parent = replace;
                                replace = replace->left;
                            }
                            strcpy(temp->word,replace->word);
                            strcpy(temp->meaning,replace->meaning);
                            strcpy(temp->synonym,replace->synonym);
                            strcpy(temp->antonym,replace->antonym);
                            strcpy(temp->sentence,replace->sentence);

                            if(flag == 0 && replace->right == NULL)
                                temp->right = NULL;
                            else if(flag == 0 && replace->right != NULL)
                            {
                                temp->right = replace->right;
                            }
                            else
                                parent->left = replace->right;
                            free(replace);
                        }
                        else if(temp->left != NULL || temp->right != NULL)
                        {
                            DictNode* replace = (temp->left != NULL)? temp->left:temp->right;
                            strcpy(temp->word,replace->word);
                            strcpy(temp->meaning,replace->meaning);
                            strcpy(temp->synonym,replace->synonym);
                            strcpy(temp->antonym,replace->antonym);
                            strcpy(temp->sentence,replace->sentence);
                            temp->left = NULL;
                            temp->right = NULL;
                            free(replace);
                        }
                        break;
                    }
            }

            if(x == 0)
                printf("Word not found...");
        }

        temp=NULL;
        prev=NULL;
        DictNode* ptrNode=NULL;

        ptrNode = (DictNode*) malloc(sizeof(DictNode));
        ptrNode->left=NULL;
        ptrNode->right=NULL;
        printf("Enter New Word : ");
        scanf("%s",ptrNode->word);
        strcpy(ptrNode->meaning,Meaning);
        strcpy(ptrNode->synonym,Synonym);
        strcpy(ptrNode->antonym,Antonym);
        strcpy(ptrNode->sentence,Sentence);

        if(root==NULL)
        {
            root = ptrNode;
        }
        else
        {
            temp = root;
            while(temp!=NULL)
            {
                prev=temp;
                if(strcmp(ptrNode->word,temp->word)>0)
                    {
                        temp = temp->right;
                    }
                else if(strcmp(ptrNode->word,temp->word)<0)
                            {
                                temp = temp->left;
                            }
                else
                {
                    printf("Word already exists...");
                    return;
                }
            }
            if(strcmp(ptrNode->word,prev->word)<0)
                prev->left=ptrNode;
            else
                prev->right=ptrNode;
        }

    }
    else if(ch == 2)
    {
        int x = 0;
        char Word[50];
        printf("Enter Word to be Modified : ");
        scanf("%s",Word);
        DictNode* temp=NULL;
        DictNode* prev=NULL;
        if(root == NULL)
        {
            printf("Empty Dictionary...");
            return;
        }
        else
        {
            temp = root;
            while(temp!=NULL)
            {
                if(strCompare(Word,temp->word) > 0)
                {
                    temp = temp->right;
                }
                else if(strCompare(Word,temp->word) < 0)
                    {
                        temp = temp->left;
                    }
                else if(strCompare(Word,temp->word) == 0)
                    {
                        x=1;
                        printf("Word found...Enter New Details\n");
                        printf("Enter new meaning : ");
                        scanf("%s",temp->meaning);
                        printf("Enter new synonym : ");
                        scanf("%s",temp->synonym);
                        printf("Enter new antonym : ");
                        scanf("%s",temp->antonym);
                        printf("Enter new sentence : ");
                        scanf("%s",temp->sentence);
                        break;
                    }
            }

            if(x == 0)
                printf("Word not found...");
        }
    }
        else
        {
            printf("Invalid choice...");
            return;
        }
}

void printWords(DictNode* node)
{
    if(root==NULL)
        {
            printf("Empty Dictionary...");
            return;
        }
    else
        {
            if(node==NULL)
               return;
            printWords(node->left);
            printf("\n%s",node->word);
            //printf("\n%s",node->meaning);
            //printf("\n%s",node->synonym);
            //printf("\n%s",node->antonym);
            //printf("\n%s",node->sentence);
            printWords(node->right);
        }
}

void freeBst(DictNode* node)
{
    if(node!=NULL)
    {
        freeBst(node->left);
        freeBst(node->right);
        free(node);
        printf("free node 1\n");
    }
}


void printBT(struct dictNode *root, int space)
{
    if (root == NULL)
        return;

    space += 10;
    printBT(root->right, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%s\n", root->word);

    printBT(root->left, space);
}


int main()
{
    int ch;
    int ans = 1;
    int ansSub = 1;
    while(ans == 1)
    {
        printf("        MENU\n");
        printf("1.Add Word(s) to the Dictionary\n");
        printf("2.Find Word(s) in the Dictionary\n");
        printf("3.Modify the existing Dictionary\n");
        printf("4.Print the existing Dictionary\n");
        printf("\nEnter your Choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1 : ansSub = 1;
                     while(ansSub == 1)
                     {
                         printf("       Submenu 1\n");
                         printf("1.Add a Single Word\n");
                         printf("2.Add Multiple Words(through a file: each word and their related data at each line)\n");
                         printf("Enter your Choice : ");
                         scanf("%d",&ch);
                         switch(ch)
                         {
                             case 1 : addWordSingle();
                                      break;
                             case 2 : addWordMulti();
                                      break;
                             default : printf("Invalid Choice...");
                         }
                         printf("\nDo you want to continue Adding words???(1/0) : ");
                         scanf("%d",&ansSub);
                     }
                     break;

            case 2 : ansSub = 1;
                     while(ansSub == 1)
                     {
                         printf("       Submenu 2\n");
                         printf("1.Find a Single Word\n");
                         printf("2.Find Multiple Words(through a file)\n");
                         printf("Enter your Choice : ");
                         scanf("%d",&ch);
                         switch(ch)
                         {
                             case 1 : findWordSingle();
                                      break;
                             case 2 : findWordMulti();
                                      break;
                             default : printf("Invalid Choice...");
                         }
                         printf("\nDo you want to continue Finding words???(1/0) : ");
                         scanf(" %d",&ansSub);
                     }
                     break;

            case 3 : ansSub = 'y';
                     while(ansSub == 'y')
                     {
                         modifyDict();
                         printf("\nDo you want to continue Modifying words???(1/0) : ");
                         scanf("%d",&ansSub);
                     }
                     break;
            case 4 : printBT(root,0);
                     break;
            default : printf("Invalid Choice...");
        }
        printf("\nDo you want to continue with the MENU???(1/0) : ");
        scanf("%d",&ans);
    }

    return 0;
}
