//
//  list.c
//  LinkedList
//
//  Created by Sarvesh Ghautham on 2/22/14.
//

#include "list.h"

node * create(int list_id, int data)
{
    node *temp = NULL;
    temp = (node *)malloc(sizeof(struct node));
    if (temp == NULL)
    {
        perror("malloc");
        exit(1);
    }

    temp->data = data;
    temp->list_id = list_id;
    temp->next = NULL;
    
    return temp;
}

void insert (node **head, int list_id, int data)
{
    node *temp = NULL;
    node *newnode = NULL;
    newnode = create(list_id, data);

    if (newnode->data < (*head)->data)
    {
        newnode->next = *head;
        *head = newnode;
    }
    
    else if ((*head)->next == NULL)
    {
        (*head)->next = newnode;
        newnode->next = NULL;
    }
    else
    {
        temp = *head;
        while (temp->data < newnode->data)
        {
            if (temp->next == NULL || temp->next->data > newnode->data)
                break;
            temp = temp->next;

        }
        if (temp->next != NULL)
        {
            newnode->next = temp->next;
            temp->next = newnode;
        }
        else// (temp->next == NULL)
        {
            temp->next = newnode;
            newnode->next = NULL;
        }
    }
    
//    return head;
    
}

void display (node *head)
{
    printf ("\n Display \n");
    if (head == NULL)
    {
        printf("\n List is empty \n");
    }
    
    node *temp = NULL;
    temp = head;
    while (temp != NULL)
    {
        printf("\n Data: %d\n", temp->data);
        temp = temp->next;
    }
}

int remove_node (node **head, int data)
{
    node *temp=NULL;
    node *temp1=NULL;
    
    if (*head == NULL)
    {
        printf("\n List is empty \n");
    }
    else if ((*head)->data == data)
    {
        temp = (*head)->next;
        free(*head);
        *head = temp;
        return 1;
    }
    else
    {
        temp = *head;

        while (temp->next != NULL)
        {
            if (temp->next->data == data)
                break;
            else
                temp = temp->next;
        }
        
        temp1 = temp->next;
        temp->next = temp1->next;
        free(temp1);
        
        return 1;
    }
    
    return 0;
}

void remove_list (node *head)
{
    if (head != NULL)
    {
        node *temp = NULL;

        while (head != NULL)
        {
            temp = head;
            head = head->next;
            free(temp);
        }
    }
}

node * create_node_reconstruction(int list_id)
{
    node *temp = NULL;
    temp = (node *)malloc(sizeof(node));
    if (temp == NULL)
    {
        perror("malloc");
        exit(1);
    }

    temp->list_id = list_id;
    temp->next = NULL;
    return temp;
}

node * read_from_file_and_construct_list(FILE **fp, int list_id, long *list_length)
{
    char *token=NULL;
    node *head =NULL;
    node *temp = NULL;
    node *prev = NULL;
    char line_read[MAX_NODES_IN_LIST];
    int data=0;
    
    head = create_node_reconstruction(list_id);
    temp = create_node_reconstruction(list_id);
    
    *list_length = file_read(fp, "list.out", list_id, line_read);
    
    token = strtok(line_read, " ");
    token = strtok(NULL, " ");
    data = atoi(token);
    head->data = data;
    
    token = strtok(NULL, " ");
    if (token == NULL)
    {
        head->next = NULL;
    }
    else
    {
        head->next = temp;
        while (token != NULL)
        {
            data = atoi(token);            
            if (data == 0)
            {
                break;
            }
            temp->data = data;
            temp->next = NULL;
            if (prev != NULL)
            {
                prev->next = temp;
            }
            prev = temp;
            token = strtok(NULL, " ");
            if (token != NULL)
            {
                temp = create_node_reconstruction(list_id);
            }
        }
    }
    return head;
}

int load_in_memory (FILE **fp, node **head)
{
    if (file_open(fp, "list.out", "r"))
    {
        char line_read[MAX_NODES_IN_LIST];
        char *token;
        int i=0;
        int data=0;
        int list_id=0;
        node *temp=NULL;
        node *prev=NULL;
        
        while (fgets(line_read, MAX_NODES_IN_LIST, *fp))
        {
            token = strtok(line_read, " ");
            list_id = atoi(token);
            
            token = strtok(NULL, " ");
            data = atoi(token);
            (*(head+i)) = create_node_reconstruction(list_id);
            temp = create_node_reconstruction(list_id);
            (*(head+i))->data = data;
           
            token = strtok(NULL, " ");
            if (token == NULL)
            {
                (*(head+i))->next = NULL;
            }
            else
            {
                (*(head+i))->next = temp;
                while (token != NULL)
                {
                    data = atoi(token);
                    if (data == 0)
                    {
                        break;
                    }
                    temp->data = data;
                    temp->next = NULL;
                    if (prev != NULL)
                    {
                        prev->next = temp;
                    }
                    prev = temp;
                    token = strtok(NULL, " ");
                    if (token != NULL)
                    {
                        temp = create_node_reconstruction(list_id);
                    }
                }
            }
            prev = NULL;
            i++;
        }
        return i;
    }
    return 0;
}

long get_list_id(FILE **fp, int *arr_list_id, int *count)
{
    
    if (file_open (fp, "list_ids.out", "r"))
    {
        int i=0;
        char lineread[MAX_LISTS];
        while(fgets(lineread, MAX_LISTS, *fp));
        if (strlen(lineread)!= 0)
        {
            char *tokens=NULL;
            
            tokens = strtok (lineread, " ");
            *(arr_list_id+i) = atoi(tokens);
            i++;
            tokens = strtok(NULL, " ");
            while (tokens != NULL)
            {
                *(arr_list_id+i) = atoi(tokens);
                i++;
                tokens = strtok(NULL, " ");
            }
            *count = i;
            file_close(fp);
            
            return strlen(lineread);
        }
    }
    
    return 0;
}

void write_to_file (node *head, FILE **fp)
{
    node *temp = NULL;
    temp = head;
    file_open(fp, "list.out", "a+");
    
    fprintf(*fp, "%d ", temp->list_id);
    while (temp->next != NULL)
    {
        fprintf(*fp, "%d ", temp->data);
        temp = temp->next;
    }
    fprintf(*fp, "%d\n", temp->data);
    file_close(fp);
}

void rewrite_to_file (node **head, FILE **fp, int list_id, int count)
{
    node *temp = NULL;
    int i = 0;
    
    if (file_open(fp, "list.out", "w+"))
    {
        for (i = 0; i < count; i++)
        {
            temp = head[i];
            
            if (temp != NULL)
            {
                fprintf(*fp, "%d ", temp->list_id);
                while (temp->next != NULL)
                {
                    fprintf(*fp, "%d ", temp->data);
                    temp = temp->next;
                }
                fprintf(*fp, "%d\n", temp->data);
            }
        }
    }
    file_close(fp);
}

int check_line_number(int *arr_list_id, int line_number, long count)
{
    int i = 0;
    
    for (i = 0; i < count; i++)
    {
        if (arr_list_id[i] == line_number)
        {
            return 1;
        }
    }
    return 0;
}

/* Writing the list_ids to a separate file */
void write_list_number_file(FILE **fp, int list_number, long list_length)
{
    if (file_open(fp, "list_ids.out", "a+"))
    {
        if (list_length == 0)
        {
            fprintf(*fp, "%d ", list_number);
        }
        else
        {
            fseek(*fp, list_length, SEEK_CUR);
            fprintf(*fp, "%d ", list_number);
        }
    }
}

void remove_from_listid_file(FILE **fp, int list_id)
{
    if (file_open(fp, "list_ids.out", "r"))
    {
        int arr_list_ids[MAX_LISTS];
        int i=0;
        int count = 0;
        char *tokens=NULL;
        char line_read[MAX_LISTS];
        while (fgets(line_read, MAX_LISTS, *fp));
        
        tokens = strtok(line_read, " ");
        arr_list_ids[count] = atoi(tokens);
        tokens = strtok(NULL, " ");
        count++;
        
        while (tokens != NULL)
        {
            arr_list_ids[count] = atoi(tokens);
            tokens = strtok(NULL, " ");
            count++;
        }
        
        for (i = 0; i < count; i++)
        {
            if (arr_list_ids[i] == list_id)
            {
                arr_list_ids[i] = -1;
            }
        }
        
        file_close(fp);
        
        file_open(fp, "list_ids.out", "w+");
        for (i = 0; i < count; i++)
        {
            if (arr_list_ids[i] != -1)
            {
                fprintf(*fp, "%d ", arr_list_ids[i]);
            }
            
        }
        file_close(fp);
    }
}

int check_node_present(node *head, int data)
{
    node *temp = NULL;
    
    temp = head;
    while(temp != NULL)
    {
        if (temp->data == data)
            return 1;
        temp = temp->next;
    }
    return 0;
}